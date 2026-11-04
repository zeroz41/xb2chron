#include "classes/gf/GfGameTarget.h"
#include "classes/gf/GfGameTarget/StateDriverNotActive.h"
#include "classes/gf/GfGameTarget/StateAutoTarget.h"
#include "classes/gf/GfGameTarget/StateEnemyTarget.h"
#include "classes/gf/GfGameTarget/StateBattleTarget.h"
#include "classes/btl/BattleGlobal.h"
#include "classes/btl/UIManager.h"
#include "classes/gf/GfMenuManager.h"
#include "classes/gf/GfGameManager.h"
#include "classes/gf/GfGameObj.h"
#include "classes/gf/GfObj.h"
#include "classes/gf/GfGameSearchObj.h"
#include "gf/GfObjUtil.h"
#include "gf/MsgGameChangeTarget.h"
#include "gf/MsgGameDebugTarget.h"
#include "gf/MsgUnk_1000058.h"
#include "gf/GfSearchInfo.h"
#include "fw/Allocator.h"
#include "fw/Reflection.h"
#include "classes/fw/ParamManager.h"
#include "classes/fw/ReferenceFrame.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfComTransform.h"
#include "classes/gf/GfEvent.h"
#include "classes/gf/GfGameInsideBattleLock.h"
#include "classes/gf/GfGamePlayerCamera.h"
#include "classes/gf/GfGameVisible.h"
#include "classes/gf/GfObjProperty.h"
#include "classes/gf/SCOM_TARGET_UI.h"
#include "fw/UpdateInfo.h"
#include "gf/GfSearchParam.h"
#include "gf/GfTargetProperty.h"
#include "gf/MsgPcFieldGetAccessType.h"
#include "mm/Math.h"

namespace gf {

namespace {
typedef mm::mtl::FixedList<GfSearchInfo*, 256> SearchList;

// whether the object behind handle may be targeted: it exists, lies inside a held battle lock (when one holds), has
// its flag bit 2 and is visible or the target is locked (inline: the name is not the original's)
inline bool isTargetable(GF_OBJ_HANDLE* handle) {
    GfObj* obj = GfObjUtil::getObj(handle);
    if (obj == nullptr) {
        return false;
    }
    if (GfGameInsideBattleLock::get()->m_hasLock && !GfGameInsideBattleLock::isInside(handle)) {
        return false;
    }
    bool flag = (obj->pad_110 & 4) != 0;
    bool visible = GfGameVisible::isVisible(handle);
    bool locked = GfGameTarget::testLockTarget();
    return flag && (visible || locked);
}

// whether an unlocked target is gone: no object, not targetable or destroyed (inline: the name is not the original's)
inline bool isLostTarget(GF_OBJ_HANDLE* handle) {
    bool unlocked = !GfGameTarget::testLockTarget();
    GfObj* obj = GfObjUtil::getObj(handle);
    bool unflagged = obj == nullptr || (obj->pad_110 & 4) == 0;
    bool destroyed = GfGameObj::isDestroyGameObj(handle);
    return unlocked && (unflagged || destroyed);
}

// 1.0.0's GfGameTarget::isSwimPlayer and isWaterHole (inline in 3.0.1)
inline bool isSwimPlayer() {
    GfObjProperty* property = GfObjUtil::getProperty(GfGameManager::getControlMover());
    bool swim;
    bool valid = false;
    if (property != nullptr && property->m_target != nullptr) {
        valid = true;
        swim = property->m_target->m_state == 2;
    }
    return valid && swim;
}
}  // namespace

// 1.0.0's (name from its symbols); 3.0.1's linker dropped it as unused, leaving its strings in this file's .rodata.
void GfGameTarget::Param::createReflection(fw::Reflection* reflection, const char* name, unsigned int index) {
#line 40
    fw::ReflectionValueStruct* value = new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__)
        fw::ReflectionValueStruct(name, sizeof(Param), __alignof__(Param));
#line 41
    value->addValue(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__)
                        fw::ReflectionValueF32("nearRadius", 0, 0.0f, 10000.0f, 3.0f));
#line 42
    value->addValue(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__)
                        fw::ReflectionValueF32("nearAngle", 4, 0.0f, 180.0f, 90.0f));
#line 43
    value->addValue(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__)
                        fw::ReflectionValueF32("fadeTime", 8, 0.0f, 10.0f, 1.0f));
#line 44
    value->addValue(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__)
                        fw::ReflectionValueF32("resetKeyTime", 12, 0.0f, 10.0f, 0.5f));
    reflection->setReflectionStruct(index, value);
}

// 1.0.0's (name from its symbols); 3.0.1's linker dropped it as unused.
fw::Reflection* GfGameTarget::createReflection() {
#line 61
    fw::Reflection* reflection = new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__)
        fw::Reflection(fw::Allocator::getDebAllocator());
    reflection->m_structs.resize(1, nullptr);
    Param::createReflection(reflection, "target", 0);
    return reflection;
}

bool GfGameTarget::recieveMessage(fw::MessageObject* sender, fw::Message& msg) {
    switch (msg.m_id) {
    case MsgGameChangeTarget::ID:
        setTarget(static_cast<MsgGameChangeTarget&>(msg).m_target);
        notifyTarget();
        return true;
    case MsgGameDebugTarget::ID:
        procMsgGameDebugTarget(sender, static_cast<MsgGameDebugTarget&>(msg));
        return true;
    }
    return false;
}

void GfGameTarget::build(const GfSetupParam& param) {
#line 442
    GfGameTarget* target = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) GfGameTarget();
    target->setup(param);
}

void GfGameTarget::setup(const GfSetupParam& param) {
    m_paramList = fw::ParamManager::get()->m_paramLists[0];
    m_fsm.beginSetup(this, 4);
    m_fsm.registerState<StateDriverNotActive>(0);
    m_fsm.registerState<StateAutoTarget>(1);
    m_fsm.registerState<StateEnemyTarget>(2);
    m_fsm.registerState<StateBattleTarget>(3);
    m_fsm.endSetup();
    m_fsm.setState(0);
    m_padRelay.bind(0, 3, getAllocator(ALLOCATOR(0)));
    m_padRelay.bindAction("change_mode", this, &GfGameTarget::changeMode);
    m_padRelay.bindAction("select_right", this, &GfGameTarget::selectRight);
    m_padRelay.bindAction("select_left", this, &GfGameTarget::selectLeft);
    m_padRelay.bindAction("close_target_on", this, &GfGameTarget::startNearTarget);
    m_padRelay.bindAction("close_target_off", this, &GfGameTarget::judgeNearTarget);
    GfEvent::addEventCallback(this);
}

void GfGameTarget::destroy() {
    GfGameTarget* target = get();
    target->cleanup();
    delete target;
}

void GfGameTarget::cleanup() {
    GfEvent::removeEventCallback(this);
    m_padRelay.unbind();
    m_fsm.cleanup();
    destroySearchObj();
    m_paramList = nullptr;
}

void GfGameTarget::update(const fw::UpdateInfo& info) {
    get()->updateImpl(info);
}

void GfGameTarget::updateImpl(const fw::UpdateInfo& info) {
    if (m_nearHold) {
        m_nearTimer = info.m_deltaTime + m_nearTimer;
        const Param* param = static_cast<const Param*>(m_paramList->m_entries->m_data);
        if (m_nearTimer >= param->m_resetKeyTime) {
            btl::BattleGlobal::get()->NotifyShiftTimeOver();
        }
    }
    m_reqChangeMode = false;
    m_reqSelectRight = false;
    m_reqSelectLeft = false;
    m_reqNearTarget = false;
    m_padRelay.update();
    if (!GfGameManager::isEnableFieldBattleTarget() && m_fsm.m_pState != nullptr && m_fsm.m_pState->m_stateID != 0) {
        resetTarget();
        notifyTarget();
        m_fsm.setState(0);
    }
    const Param* param = getParam();
    if (m_fading) {
        m_fadeTimer = info.m_deltaTime + m_fadeTimer;
        if (m_fadeTimer >= param->m_fadeTime) {
            resetTarget();
        }
    }
    m_fsm.update(&info);
    notifyTarget();
}

bool GfGameTarget::testActive() {
    ai::State* state = get()->m_fsm.m_pState;
    return state != nullptr && state->m_stateID != 0;
}

GfGameTarget::GfGameTarget()
    : m_fsm(getAllocator(ALLOCATOR(0))), m_enemySearch(reinterpret_cast<GF_SEARCH_OBJ*>(-1)),
      m_autoSearch(reinterpret_cast<GF_SEARCH_OBJ*>(-1)), m_player(reinterpret_cast<GF_OBJ_HANDLE*>(-1)),
      m_target(reinterpret_cast<GF_OBJ_HANDLE*>(-1)), m_changed(false), m_lock(false), m_fading(false),
      m_fadeTimer(0.0f), m_reqChangeMode(false), m_reqSelectRight(false), m_reqSelectLeft(false),
      m_reqNearTarget(false), m_nearHold(false), m_nearTimer(0.0f) {}

GfGameTarget::~GfGameTarget() {}

void GfGameTarget::changeMode() {
    if (!btl::UIManager::get()->pad_bit15) {
        m_reqChangeMode = true;
        m_nearHold = false;
    }
}

void GfGameTarget::selectRight() {
    if (btl::BattleGlobal::get()->IsPause(-1) || GfMenuManager::isOpenCommonWindow()) {
        return;
    }
    if (btl::UIManager::get()->pad_bit15) {
        btl::BattleGlobal* global = btl::BattleGlobal::get();
        if (!global->pad_bit40 || testLockTarget() || global->fn_71000068F8()) {
            return;
        }
    }
    if (m_target != reinterpret_cast<GF_OBJ_HANDLE*>(-1)) {
        m_reqSelectRight = true;
    } else {
        m_reqNearTarget = true;
    }
    m_nearHold = false;
    btl::UIManager::get()->NotifyInput(static_cast<btl::UIManager::INPUT_TYPE>(5), 0);
}

void GfGameTarget::selectLeft() {
    if (btl::BattleGlobal::get()->IsPause(-1) || GfMenuManager::isOpenCommonWindow()) {
        return;
    }
    if (btl::UIManager::get()->pad_bit15) {
        btl::BattleGlobal* global = btl::BattleGlobal::get();
        if (!global->pad_bit40 || testLockTarget() || global->fn_71000068F8()) {
            return;
        }
    }
    if (m_target != reinterpret_cast<GF_OBJ_HANDLE*>(-1)) {
        m_reqSelectLeft = true;
    } else {
        m_reqNearTarget = true;
    }
    m_nearHold = false;
    btl::UIManager::get()->NotifyInput(static_cast<btl::UIManager::INPUT_TYPE>(4), 0);
}

void GfGameTarget::startNearTarget() {
    if (btl::UIManager::get()->pad_bit15 && btl::BattleGlobal::get()->fn_71000068F8()) {
        return;
    }
    if (btl::BattleGlobal::get()->IsPause(-1) || GfMenuManager::isOpenCommonWindow()) {
        return;
    }
    if (!m_reqChangeMode) {
        m_nearTimer = 0.0f;
        m_nearHold = true;
    }
}

void GfGameTarget::judgeNearTarget() {
    if (m_nearHold) {
        const Param* param = static_cast<const Param*>(m_paramList->m_entries->m_data);
        if (m_nearTimer < param->m_resetKeyTime) {
            if (!(btl::UIManager::get()->pad_bit15 && btl::BattleGlobal::get()->fn_71000068F8()) &&
                !btl::BattleGlobal::get()->IsPause(-1) && !GfMenuManager::isOpenCommonWindow()) {
                m_reqNearTarget = true;
            }
        }
        m_nearHold = false;
    }
    btl::BattleGlobal::get()->NotifyShiftNone();
}

void GfGameTarget::notifyTarget() {
    if (m_changed) {
        if (GfObj* obj = GfObjUtil::getObj(m_player)) {
            MsgGameChangeTarget msg(m_target);
            sendMessage(obj, msg);
        }
        GfGamePlayerCamera::setTargetObject(m_target);
        SCOM_TARGET_UI::create(m_target);
        if (GfObj* obj = GfObjUtil::getObj(m_target)) {
            if (GfObjUtil::getObjType(m_target) == 5) {
                MsgUnk_1000058 msg;
                sendMessage(obj, msg);
            }
        }
        m_changed = false;
    }
}

bool GfGameTarget::setTargetNearest(const SearchList& list) {
    const Param* param = getParam();
    bool swim = isSwimPlayer();
    for (SearchList::const_iterator it = list.begin(); it != list.end(); ++it) {
        GfSearchInfo* info = *it;
        if (!isTargetable(info->m_handle) || !info->m_visible) {
            continue;
        }
        if (GfObjUtil::getObjType(info->m_handle) != 5 && mm::fabs(info->m_height) > param->m_nearAngle) {
            continue;
        }
        if (swim) {
            GF_OBJ_HANDLE* handle = info->m_handle;
            MsgPcFieldGetAccessType msg;
            GfObj* obj = GfObjUtil::getObj(handle);
            if (obj == nullptr) {
                continue;
            }
            sendMessage(obj, msg);
            if (msg.m_type != 4) {
                continue;
            }
        }
        setTarget(info->m_handle);
        return true;
    }
    return false;
}

bool GfGameTarget::setTargetNearestEnemy(const SearchList& list) {
    GfSearchInfo* hidden = nullptr;
    for (SearchList::const_iterator it = list.begin(); it != list.end(); ++it) {
        GfSearchInfo* info = *it;
        if (!isTargetable(info->m_handle)) {
            continue;
        }
        if (GfGameVisible::isVisible(info->m_handle)) {
            setTarget(info->m_handle);
            return true;
        }
        if (hidden == nullptr) {
            hidden = info;
        }
    }
    if (hidden != nullptr) {
        setTarget(hidden->m_handle);
        return true;
    }
    resetTarget();
    return false;
}

bool GfGameTarget::setTargetNearestEnemyBattle(const SearchList& list) {
    GF_OBJ_HANDLE* hidden = reinterpret_cast<GF_OBJ_HANDLE*>(-1);
    for (SearchList::const_iterator it = list.begin(); it != list.end(); ++it) {
        GfSearchInfo* info = *it;
        GF_OBJ_HANDLE* handle = info->m_handle;
        GfObj* obj = GfObjUtil::getObj(handle);
        if (obj == nullptr) {
            continue;
        }
        if (GfGameInsideBattleLock::get()->m_hasLock && !GfGameInsideBattleLock::isInside(handle)) {
            continue;
        }
        if ((obj->pad_110 & 4) == 0 || !GfObjUtil::isBattle(info->m_handle)) {
            continue;
        }
        if (GfGameVisible::isVisible(info->m_handle)) {
            setTarget(info->m_handle);
            return true;
        }
        if (hidden == reinterpret_cast<GF_OBJ_HANDLE*>(-1)) {
            hidden = info->m_handle;
        }
    }
    if (hidden != reinterpret_cast<GF_OBJ_HANDLE*>(-1)) {
        setTarget(hidden);
        return true;
    }
    return false;
}

void GfGameTarget::gevChangeLeader(GF_OBJ_HANDLE* leader) {
    if (m_fsm.m_pState != nullptr && m_fsm.m_pState->m_stateID != 0) {
        resetTarget();
        m_fsm.setState(0);
    }
}

void GfGameTarget::gevSwapFormation(unsigned int, unsigned int) {
    if (m_fsm.m_pState != nullptr && m_fsm.m_pState->m_stateID != 0) {
        GF_OBJ_HANDLE* mover = GfGameManager::getControlMover();
        if (GfObj* obj = GfObjUtil::getObj(m_player)) {
            MsgGameChangeTarget msg(reinterpret_cast<GF_OBJ_HANDLE*>(-1));
            sendMessage(obj, msg);
        }
        if (GfObj* obj = GfObjUtil::getObj(mover)) {
            MsgGameChangeTarget msg(m_target);
            sendMessage(obj, msg);
        }
        m_player = mover;
        if (GfObj* obj = GfObjUtil::getObj(mover)) {
            mm::mtl::IntrusivePtr<fw::ReferenceFrame> frame = obj->getComponent<GfComTransform>(0)->getFrame();
            GfGameSearchObj::getInfo(m_enemySearch)->m_frame = frame;
            GfGameSearchObj::getInfo(m_autoSearch)->m_frame = frame;
        }
    }
}

void GfGameTarget::changeBattleTarget(bool battle) {
    unsigned int state = m_fsm.m_pState->m_stateID;
    if (battle) {
        if (state != 3) {
            m_fsm.setState(3);
        }
    } else if (state == 3) {
        m_fsm.setState(1);
    }
    notifyTarget();
}

void GfGameTarget::disableTargetWithoutEnemy() {
    if (GfGameTarget* target = get()) {
        GfGameSearchObj::setEnable(target->m_autoSearch, false);
    }
}

void GfGameTarget::lockTarget(bool lock) {
    if (GfGameTarget* target = get()) {
        target->m_lock = lock;
    }
}

inline void GfGameTarget::destroySearchObj() {
    if (m_enemySearch != reinterpret_cast<GF_SEARCH_OBJ*>(-1)) {
        GfGameSearchObj::destroyObj(m_enemySearch);
        m_enemySearch = reinterpret_cast<GF_SEARCH_OBJ*>(-1);
    }
    if (m_autoSearch != reinterpret_cast<GF_SEARCH_OBJ*>(-1)) {
        GfGameSearchObj::destroyObj(m_autoSearch);
        m_autoSearch = reinterpret_cast<GF_SEARCH_OBJ*>(-1);
    }
}

const char* GfGameTarget::StateDriverNotActive::getName() const {
    return "StateDriverNotActive";
}

void GfGameTarget::StateDriverNotActive::onEnter(void* owner, ai::State* prev) {
    GfGameTarget* target = static_cast<GfGameTarget*>(owner);
    target->destroySearchObj();
    target->m_player = reinterpret_cast<GF_OBJ_HANDLE*>(-1);
}

void GfGameTarget::StateDriverNotActive::onLeave(void* owner, ai::State* next) {
    if (next != nullptr) {
        static_cast<GfGameTarget*>(owner)->createSearchObj();
    }
}

void GfGameTarget::StateDriverNotActive::onStep(void* owner, const void* arg) {
    if (GfGameManager::isEnableFieldBattleTarget()) {
        GF_OBJ_HANDLE* mover = GfGameManager::getControlMover();
        if (GfObj* obj = GfObjUtil::getObj(mover)) {
            if (obj->getComponent<GfComTransform>(0) != nullptr) {
                static_cast<GfGameTarget*>(owner)->m_player = mover;
                requestState(1);
            }
        }
    }
}

const char* GfGameTarget::StateAutoTarget::getName() const {
    return "StateAutoTarget";
}

void GfGameTarget::StateAutoTarget::onEnter(void* owner, ai::State* prev) {
    GfGameTarget* target = static_cast<GfGameTarget*>(owner);
    GfGameSearchObj::setEnable(target->m_autoSearch, true);
    if (!target->setTargetNearest(*GfGameSearchObj::getObj(target->m_autoSearch))) {
        target->resetTarget();
    }
}

void GfGameTarget::StateAutoTarget::onLeave(void* owner, ai::State* next) {
    GfGameTarget* target = static_cast<GfGameTarget*>(owner);
    GfGameSearchObj::setEnable(target->m_autoSearch, false);
    target->resetTarget();
}

void GfGameTarget::StateAutoTarget::onStep(void* owner, const void* arg) {
    update(static_cast<GfGameTarget*>(owner), *static_cast<const fw::UpdateInfo*>(arg));
}

void GfGameTarget::StateAutoTarget::update(GfGameTarget* owner, const fw::UpdateInfo& info) {
    if (owner->m_reqSelectLeft | owner->m_reqSelectRight | owner->m_reqNearTarget) {
        owner->setTargetNearestEnemy(*GfGameSearchObj::getObj(owner->m_enemySearch));
        if (owner->m_target != reinterpret_cast<GF_OBJ_HANDLE*>(-1)) {
            requestState(2);
            return;
        }
    }
    if (owner->setTargetNearest(*GfGameSearchObj::getObj(owner->m_autoSearch))) {
        return;
    }
    GF_OBJ_HANDLE* target = owner->m_target;
    if (target == reinterpret_cast<GF_OBJ_HANDLE*>(-1)) {
        return;
    }
    GfObjUtil::getObj(target);
    if (!GfGameObj::isDestroyGameObj(target) && isTargetable(target)) {
        if (isSwimPlayer()) {
            GF_OBJ_HANDLE* current = owner->m_target;
            MsgPcFieldGetAccessType msg;
            GfObj* obj = GfObjUtil::getObj(current);
            if (obj == nullptr) {
                owner->resetTarget();
                return;
            }
            owner->sendMessage(obj, msg);
            if (msg.m_type != 4) {
                owner->resetTarget();
                return;
            }
        }
        if (owner->m_target != reinterpret_cast<GF_OBJ_HANDLE*>(-1) && !owner->m_fading) {
            owner->m_fading = true;
            owner->m_fadeTimer = 0.0f;
        }
        return;
    }
    owner->resetTarget();
}

const char* GfGameTarget::StateEnemyTarget::getName() const {
    return "StateEnemyTarget";
}

void GfGameTarget::StateEnemyTarget::onEnter(void* owner, ai::State* prev) {
    GfGameTarget* target = static_cast<GfGameTarget*>(owner);
    if (target->m_target == reinterpret_cast<GF_OBJ_HANDLE*>(-1)) {
        SearchList* list = GfGameSearchObj::getObj(target->m_enemySearch);
        if (!target->setTargetNearestEnemyBattle(*list)) {
            target->setTargetNearestEnemy(*list);
        }
    }
}

void GfGameTarget::StateEnemyTarget::onLeave(void* owner, ai::State* next) {}

void GfGameTarget::StateEnemyTarget::onStep(void* owner, const void* arg) {
    update(static_cast<GfGameTarget*>(owner), *static_cast<const fw::UpdateInfo*>(arg));
}

void GfGameTarget::StateEnemyTarget::update(GfGameTarget* owner, const fw::UpdateInfo& info) {
    if (!owner->m_reqChangeMode) {
        SearchList* list = GfGameSearchObj::getObj(owner->m_enemySearch);
        if (owner->m_reqNearTarget) {
            owner->setTargetNearestEnemy(*list);
        }
        owner->selectTarget(*list);
        if (isLostTarget(owner->m_target) != true) {
            return;
        }
    }
    requestState(1);
}

const char* GfGameTarget::StateBattleTarget::getName() const {
    return "StateBattleTarget";
}

void GfGameTarget::StateBattleTarget::onEnter(void* owner, ai::State* prev) {
    GfGameTarget* target = static_cast<GfGameTarget*>(owner);
    if (target->m_target == reinterpret_cast<GF_OBJ_HANDLE*>(-1)) {
        SearchList* list = GfGameSearchObj::getObj(target->m_enemySearch);
        if (!target->setTargetNearestEnemyBattle(*list)) {
            target->setTargetNearestEnemy(*list);
        }
    }
    target->m_lock = false;
}

void GfGameTarget::StateBattleTarget::onLeave(void* owner, ai::State* next) {
    GfGameTarget* target = static_cast<GfGameTarget*>(owner);
    target->resetTarget();
    target->m_lock = false;
}

void GfGameTarget::StateBattleTarget::onStep(void* owner, const void* arg) {
    update(static_cast<GfGameTarget*>(owner), *static_cast<const fw::UpdateInfo*>(arg));
}

}  // namespace gf

#include "gf/FileStaticVec3.h"
#include "classes/gf/GfInitParamBlade.h"
#include "classes/gf/SCOM_OBJ_WARP_POS.h"
#include "gf/GfGameUtil.h"
#include "classes/gf/GfEvtModel.h"
#include "classes/gf/GfEvtModelDriver.h"
#include "classes/gf/GfEvtModelBlade.h"
#include "classes/gf/GfEvtModelEnemy.h"
#include "classes/gf/GfEvtModelNpc.h"
#include "classes/gf/GfEvtModelSalvage.h"
#include "classes/gf/GfEvtModelWeapon.h"
#include "classes/gf/GfEvtModelEvent.h"
#include "classes/gf/GfGameEvent.h"
#include "gf/GfObjAcc.h"
#include "classes/gf/GfInitParam.h"
#include "classes/gf/GfInitParamDriver.h"
#include "classes/gf/GfEvtModel.h"
#include "classes/gf/GfEvtModelDriver.h"
#include "classes/gf/GfGameManager.h"
#include "classes/event/Manager.h"
#include "classes/gf/DataParamAcc.h"
#include "gf/GfGameUtil.h"
#include "classes/gf/GfEvtModelDriver/StateIdleField.h"
#include "classes/gf/GfEvtModelDriver/StateIdleBattle.h"
#include "classes/gf/GfEvtModelDriver/StateStartBattle.h"
#include "classes/gf/GfEvtModelDriver/StateEndBattle.h"
#include "gf/GfObjFactory.h"
#include "classes/gf/GfInitParamBlade.h"
#include "classes/gf/GfInitParamEnemy.h"
#include "classes/gf/GfEvtModelBlade.h"
#include "classes/gf/GfEvtModelBlade/StateIdleField.h"
#include "classes/gf/GfEvtModelBlade/StateIdleBattle.h"
#include "classes/gf/GfEvtModelBlade/StateStartBattle.h"
#include "classes/gf/GfEvtModelBlade/StateEndBattle.h"
#include "classes/gf/GfEvtModelEnemy.h"
#include "classes/gf/GfEvtModelEnemy/StateIdleField.h"
#include "classes/gf/GfEvtModelEnemy/StateIdleBattle.h"
#include "classes/gf/GfEvtModelEnemy/StateStartBattle.h"
#include "classes/gf/GfEvtModelEnemy/StateEndBattle.h"
#include "ai/Fsm.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfManager.h"
#include "classes/gf/GfMenuManager.h"
#include "classes/mm/mtl/PtrSingleton.h"
#include "gf/GfObjFactory.h"
#include "gf/GfObjUtil.h"
#include "classes/gf/GfObjManager.h"
#include "classes/gf/GfMountManager.h"
#include "classes/gf/GfWeapon.h"
#include "classes/gf/GfComPackAnim.h"
#include "classes/gf/GfObj.h"
#include "classes/gf/GfComAsm.h"
#include "classes/gf/GfGameObj.h"
#include "classes/gf/GfBdatChrBl.h"
#include "classes/gf/GfComEvtAnim.h"
#include "classes/gf/GfComTransform.h"
#include "classes/gf/SCOM_OBJ_ALPHA.h"
#include "gf/GfDataDriver.h"
#include "mm/Vec3.h"
#include <string.h>

namespace gf {

void GfEvtModel::destroy() {
    GfGameEvent::destroyEvtModel(this);
    while (!m_mountList.empty()) {
        m_mountList.front()->resetMount(this);
    }
    if (pad_28 != nullptr) {
        ::mm::mtl::ReferenceObject* object = pad_28;
        pad_28 = nullptr;
        object->release();
    }
    GfObjUtil::destroy(m_handle);
    m_handle = reinterpret_cast<GF_OBJ_HANDLE*>(-1);
}

GfEvtModel::~GfEvtModel() {
    destroy();
    GfObjManager::removeListener(this);
}

bool GfEvtModel::isBusy(mm::mtl::FixStr<128>*) const {
    mm::mtl::FixStr<128> error;
    if (m_handle == reinterpret_cast<GF_OBJ_HANDLE*>(-1)) {
        return false;
    }
    for (int attach = 0; attach < 4; attach++) {
        if (GfAppendHandles* handles = GfMountManager::getAppendHandles(m_handle, static_cast<GFATTACH>(attach))) {
            for (unsigned long i = 0; i < 10; i++) {
                GF_OBJ_HANDLE* handle = handles->getObjHandles()[i];
                if (handle != reinterpret_cast<GF_OBJ_HANDLE*>(-1) && GfObjUtil::getObj(handle) != nullptr &&
                    !GfGameObj::isValidGameObj(handle, true, &error)) {
                    return true;
                }
            }
        }
    }
    return !GfGameObj::isValidGameObj(m_handle, true, &error);
}

void GfEvtModel::resetMount(GfEvtModel* model) {
    if (model == nullptr || pad_28 == nullptr) {
        return;
    }
    if (GfObjUtil::getParentHandle(m_handle) == model->m_handle) {
        GfObjUtil::unmountFromBone(m_handle);
    }
    if (strcmp(pad_30.m_str, "MT_met") == 0) {
        GfMountManager::setMountType(m_handle, static_cast<GFATTACH>(1), static_cast<OPTMNT>(2));
    }
    pad_30 = "";
    pad_28 = nullptr;
    release();
    model->m_mountList.erase(model->m_mountList.find(this));
}

void GfEvtModel::setMount(GfEvtModel* model, const char* bone) {
    setMount(model, bone, mm::Vec3::zero, mm::Vec3::zero);
}

void GfEvtModel::setMount(GfEvtModel* model, const char* bone, const mm::Vec3& pos, const mm::Vec3& rot) {
    if (pad_28 != nullptr) {
        return;
    }
    if (model->m_mountList.find(this) != model->m_mountList.end()) {
        return;
    }
    model->m_mountList.push_back(this);
    addRef();
    pad_28 = model;
    pad_30 = bone;
    model->execMount(this, pos, rot);
}

void GfEvtModel::execMount(GfEvtModel* model, const mm::Vec3& pos, const mm::Vec3& rot) {
    GfObjAcc acc(model->m_handle);
    if (GfComTransform* transform = acc.getObj()->getComponent<GfComTransform>(0)) {
        // rot as Euler angles (x, y, z) turned into a quaternion from the half angles
        mm::Vec3 angle = rot;
        float x = angle.x * 0.5f;
        float y = angle.y * 0.5f;
        float z = angle.z * 0.5f;
        float sx = sinf(x);
        float cx = cosf(x);
        float sy = sinf(y);
        float cy = cosf(y);
        float sz = sinf(z);
        float cz = cosf(z);
        mm::Quat q;
        q.x = sx * cy * cz - cx * sy * sz;
        q.y = cx * sy * cz + sx * cy * sz;
        q.z = cx * cy * sz - sx * sy * cz;
        q.w = cx * cy * cz + sx * sy * sz;
        transform->setPosition(pos);
        transform->setRotation(q);
        transform->syncFrame();
        if (GfObjUtil::getParentHandle(model->m_handle) != m_handle && !model->isBusy(nullptr)) {
            if (strcmp(model->pad_30.m_str, "MT_met") == 0) {
                GfMountManager::execMount(m_handle, static_cast<GFATTACH>(1), static_cast<OPTMNT>(0));
            }
            GfObjUtil::mountToBone(model->m_handle, m_handle, model->pad_30.m_str);
        }
    }
}

void GfEvtModel::listenerGfObj(IGfObjListener::OBJEVT event, GF_OBJ_HANDLE* handle, unsigned int) {
    if (m_handle != handle) {
        return;
    }
    if (event == static_cast<IGfObjListener::OBJEVT>(2)) {
        // the object is in: the models mounted on it and this one go back on their bones
        for (mm::mtl::FixedList<GfEvtModel*, 32>::iterator it = m_mountList.begin(); it != m_mountList.end(); ++it) {
            GfEvtModel* model = *it;
            if (GfObjUtil::getParentHandle(model->m_handle) != m_handle && !model->isBusy(nullptr)) {
                if (strcmp(model->pad_30.m_str, "MT_met") == 0) {
                    GfMountManager::execMount(m_handle, static_cast<GFATTACH>(1), static_cast<OPTMNT>(0));
                }
                GfObjUtil::mountToBone(model->m_handle, m_handle, model->pad_30.m_str);
            }
        }
        if (pad_28 != nullptr && !pad_28->isBusy(nullptr)) {
            GfEvtModel* parent = pad_28;
            if (GfObjUtil::getParentHandle(m_handle) != parent->m_handle && !isBusy(nullptr)) {
                if (strcmp(pad_30.m_str, "MT_met") == 0) {
                    GfMountManager::execMount(parent->m_handle, static_cast<GFATTACH>(1), static_cast<OPTMNT>(0));
                }
                GfObjUtil::mountToBone(m_handle, parent->m_handle, pad_30.m_str);
            }
        }
    } else if (event == static_cast<IGfObjListener::OBJEVT>(3)) {
        // the object is going: the models mounted on it and this one leave their bones
        for (mm::mtl::FixedList<GfEvtModel*, 32>::iterator it = m_mountList.begin(); it != m_mountList.end(); ++it) {
            GfEvtModel* model = *it;
            if (GfObjUtil::getParentHandle(model->m_handle) == m_handle) {
                GfObjUtil::unmountFromBone(model->m_handle);
            }
        }
        if (pad_28 != nullptr && !pad_28->isBusy(nullptr)) {
            GfEvtModel* parent = pad_28;
            if (GfObjUtil::getParentHandle(m_handle) == parent->m_handle) {
                GfObjUtil::unmountFromBone(m_handle);
            }
            pad_28 = nullptr;
        }
    }
}

unsigned int GfEvtModel::changeLayerUI(unsigned int layer) {
    switch (layer) {
    case 7:
        return 10;
    case 8:
        return 11;
    case 9:
        return 12;
    }
    return layer;
}

GfEvtModelDriver::GfEvtModelDriver(GfInitParamDriver& param)
    : GfEvtModel(0, param.m_objId), m_fsm(getAllocator(ALLOCATOR(0))) {
    m_bladeId = param.m_bladeId;
    if (GfManager::isExecModeThater() ? mm::mtl::PtrSingleton<event::Manager>::sys()->pad_294 != 0
                                      : GfMenuManager::isOpenFullScreen() &&
                                            GfGameManager::isInnerState(static_cast<GF_STATE>(6))) {
        int type = param.pad_40;
        if (static_cast<unsigned int>(type - 7) < 3) {
            type += 3;
        }
        param.pad_40 = type;
    }
    m_handle = GfObjFactory::createDriver(param);
    m_fsm.beginSetup(this, 4);
    m_fsm.registerState<StateIdleField>(0);
    m_fsm.registerState<StateIdleBattle>(1);
    m_fsm.registerState<StateStartBattle>(2);
    m_fsm.registerState<StateEndBattle>(3);
    m_fsm.endSetup();
    m_fsm.setState(0);
    if (m_bladeId == 0) {
        DataParamAcc acc(3, param.m_objId, static_cast<GimmickType>(0));
        m_bladeId = acc.getBlade(-1, false);
    }
}

GfEvtModelBlade::GfEvtModelBlade(GfInitParamBlade& param)
    : GfEvtModel(1, param.m_objId), m_fsm(getAllocator(ALLOCATOR(0))) {
    if (GfManager::isExecModeThater() ? mm::mtl::PtrSingleton<event::Manager>::sys()->pad_294 != 0
                                      : GfMenuManager::isOpenFullScreen() &&
                                            GfGameManager::isInnerState(static_cast<GF_STATE>(6))) {
        int type = param.pad_40;
        if (static_cast<unsigned int>(type - 7) < 3) {
            type += 3;
        }
        param.pad_40 = type;
    }
    if (param.getBladeID() == 0x451) {
        param.pad_a5 = true;
    }
    m_handle = GfObjFactory::createBlade(param);
    m_fsm.beginSetup(this, 4);
    m_fsm.registerState<StateIdleField>(0);
    m_fsm.registerState<StateIdleBattle>(1);
    m_fsm.registerState<StateStartBattle>(2);
    m_fsm.registerState<StateEndBattle>(3);
    m_fsm.endSetup();
    m_fsm.setState(0);
}

GfEvtModelEnemy::GfEvtModelEnemy(GfInitParamEnemy& param)
    : GfEvtModel(5, param.m_objId), m_fsm(getAllocator(ALLOCATOR(0))) {
    if (GfManager::isExecModeThater() ? mm::mtl::PtrSingleton<event::Manager>::sys()->pad_294 != 0
                                      : GfMenuManager::isOpenFullScreen() &&
                                            GfGameManager::isInnerState(static_cast<GF_STATE>(6))) {
        int type = param.pad_40;
        if (static_cast<unsigned int>(type - 7) < 3) {
            type += 3;
        }
        param.pad_40 = type;
    }
    m_handle = GfObjFactory::createEnemy(param);
    m_fsm.beginSetup(this, 4);
    m_fsm.registerState<StateIdleField>(0);
    m_fsm.registerState<StateIdleBattle>(1);
    m_fsm.registerState<StateStartBattle>(2);
    m_fsm.registerState<StateEndBattle>(3);
    m_fsm.endSetup();
    m_fsm.setState(0);
}

}  // namespace gf

namespace gf {

GfEvtModelDriver::~GfEvtModelDriver() {
    m_fsm.cleanup();
}

// GEN driver begin
GfEvtModelDriver* GfEvtModelDriver::create(GfInitParamDriver& param) {
#line 403
    GfEvtModelDriver* model = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) GfEvtModelDriver(param);
    model->addRef();
    return model;
}

void GfEvtModelDriver::update(fw::UpdateInfo const& info) {
    m_fsm.update(&info);
}

void GfEvtModelDriver::setWeaponBattleCommand() {
    m_fsm.setState(2);
}

void GfEvtModelDriver::setWeaponFieldCommand() {
    m_fsm.setState(3);
}

void GfEvtModelDriver::setWeaponBattleState() {
    setWeaponBattleMount();
    mm::mtl::FixStr<32> weaponState;
    mm::mtl::FixStr<32> state;
    GfGameUtil::makeWeaponStateIdle(weaponState, m_handle, true);
    GfGameUtil::makeStateIdleByBlade(state, m_bladeId, true);
    if (GfObj* obj = GfObjUtil::getObj(m_handle)) {
        if (GfComEvtAnim* anim = obj->getComponent<GfComEvtAnim>(2)) {
            anim->setState(state.m_str);
        }
    }
    if (GfAppendHandles* handles = GfMountManager::getAppendHandles(m_handle, static_cast<GFATTACH>(0))) {
        for (int i = 0; i < 10; i++) {
            GF_OBJ_HANDLE* handle = handles->getObjHandles()[i];
            if (handle != reinterpret_cast<GF_OBJ_HANDLE*>(-1)) {
                if (GfComAsm* com = GfObjUtil::getObj(handle)->getComponent<GfComAsm>(2)) {
                    com->setState(weaponState.m_str, static_cast<AnimLayer>(0));
                }
            }
        }
    }
    if (GfDataDriver::fn_710023F9A8(m_objId) && GfDataDriver::fn_7100241660(m_objId)) {
        SCOM_OBJ_ALPHA::createWeapon(m_handle, 0.0f, 1.0f);
    }
}

void GfEvtModelDriver::setWeaponFieldState() {
    GfMountManager::execMount(m_handle, static_cast<GFATTACH>(0), static_cast<OPTMNT>(2));
    mm::mtl::FixStr<32> weaponState;
    mm::mtl::FixStr<32> state;
    GfGameUtil::makeWeaponStateIdle(weaponState, m_handle, false);
    GfGameUtil::makeStateIdleByBlade(state, m_bladeId, false);
    if (GfObj* obj = GfObjUtil::getObj(m_handle)) {
        if (GfComEvtAnim* anim = obj->getComponent<GfComEvtAnim>(2)) {
            anim->setState(state.m_str);
        }
    }
    if (GfAppendHandles* handles = GfMountManager::getAppendHandles(m_handle, static_cast<GFATTACH>(0))) {
        for (int i = 0; i < 10; i++) {
            GF_OBJ_HANDLE* handle = handles->getObjHandles()[i];
            if (handle != reinterpret_cast<GF_OBJ_HANDLE*>(-1)) {
                if (GfComAsm* com = GfObjUtil::getObj(handle)->getComponent<GfComAsm>(2)) {
                    com->setState(weaponState.m_str, static_cast<AnimLayer>(0));
                }
            }
        }
    }
    if (GfDataDriver::fn_710023F9A8(m_objId) && GfDataDriver::fn_7100241660(m_objId)) {
        SCOM_OBJ_ALPHA::createWeapon(m_handle, 0.0f, 0.0f);
    }
}

void GfEvtModelDriver::setWeaponBattleMount() {
    GfMountManager::execMount(m_handle, static_cast<GFATTACH>(0), static_cast<OPTMNT>(1));
}

void GfEvtModelDriver::setWeaponFieldMount() {
    GfMountManager::execMount(m_handle, static_cast<GFATTACH>(0), static_cast<OPTMNT>(2));
}

void GfEvtModelDriver::setDispWeapon(bool disp) {
    GfAppendHandles* weapons = GfMountManager::getAppendHandles(m_handle, static_cast<GFATTACH>(0));
    for (int i = 0; i < 10; i++) {
        GfObjAcc acc(weapons->getObjHandles()[i]);
        if (acc.m_obj != nullptr) {
            acc.setDisp(static_cast<OBJDISP>(2), disp);
        }
    }
}

void GfEvtModelDriver::setDispWeapon(bool left, bool disp) {
    GfWeapon* weapon = GfMountManager::getGfWeapon(m_handle, static_cast<GFATTACH>(0));
    if (weapon != nullptr) {
        GF_OBJ_HANDLE* const* handles = weapon->getObjHandles();
        GfObjAcc acc(left ? handles[1] : handles[0]);
        if (acc.m_obj != nullptr) {
            acc.setDisp(static_cast<OBJDISP>(2), disp);
        }
    }
}

GF_OBJ_HANDLE* GfEvtModelDriver::getWeaponHandleRight() const {
    GfWeapon* weapon = GfMountManager::getGfWeapon(m_handle, static_cast<GFATTACH>(0));
    if (weapon != nullptr) {
        return weapon->getObjHandles()[0];
    }
    return reinterpret_cast<GF_OBJ_HANDLE*>(-1);
}

GF_OBJ_HANDLE* GfEvtModelDriver::getWeaponHandleLeft() const {
    GfWeapon* weapon = GfMountManager::getGfWeapon(m_handle, static_cast<GFATTACH>(0));
    if (weapon != nullptr) {
        return weapon->getObjHandles()[1];
    }
    return reinterpret_cast<GF_OBJ_HANDLE*>(-1);
}
// GEN driver end

void GfEvtModelDriver::StateStartBattle::enter(GfEvtModelDriver* owner, ai::State* prev) {
    if (GfMountManager::getMountType(owner->m_handle, static_cast<GFATTACH>(0)) != 1) {
        owner->setWeaponBattleMount();
    }
    mm::mtl::FixStr<32> weaponCommand;
    mm::mtl::FixStr<32> command;
    GfGameUtil::makeWeaponCommandBattle(weaponCommand, owner->m_handle, true, false);
    GfGameUtil::makeCommandBattle(command, true);
    mm::mtl::FixStr<32> state;
    GfGameUtil::makeStateBattleByBlade(state, owner->m_bladeId, true);
    fn_710029C9B4(owner->m_handle, command, state);
    if (GfAppendHandles* handles = GfMountManager::getAppendHandles(owner->m_handle, static_cast<GFATTACH>(0))) {
        for (int i = 0; i < 10; i++) {
            GF_OBJ_HANDLE* handle = handles->getObjHandles()[i];
            if (handle != reinterpret_cast<GF_OBJ_HANDLE*>(-1)) {
                if (GfComAsm* com = GfObjUtil::getObj(handle)->getComponent<GfComAsm>(2)) {
                    com->execCmd(weaponCommand.m_str, static_cast<AnimLayer>(0));
                }
            }
        }
    }
    if (GfDataDriver::fn_710023F9A8(owner->m_objId) && GfDataDriver::fn_7100241660(owner->m_objId)) {
        SCOM_OBJ_ALPHA::createWeapon(owner->m_handle, 0.5f, 1.0f);
    }
}

// Placeholder name (see its declaration in GfEvtModel.h): runs the battle command on the object's event animation
// and sets the state when the animation is not in it already
void fn_710029C9B4(GF_OBJ_HANDLE* handle, mm::mtl::FixStr<32>& command, mm::mtl::FixStr<32>& state) {
    if (GfObj* obj = GfObjUtil::getObj(handle)) {
        if (GfComEvtAnim* anim = obj->getComponent<GfComEvtAnim>(2)) {
            anim->execCmd(command.m_str);
            if (strcmp(anim->getStateName() ? anim->getStateName() : "", state.m_str) != 0) {
                anim->setState(state.m_str);
            }
        }
    }
}

void GfEvtModelDriver::StateStartBattle::update(GfEvtModelDriver* owner, const fw::UpdateInfo& info) {
    GfComEvtAnim* anim = GfObjUtil::getObj(owner->m_handle)->getComponent<GfComEvtAnim>(2);
    if (anim == nullptr || anim->isEnd(static_cast<AnimLayer>(0))) {
        if (GfObj* obj = GfObjUtil::getObj(owner->m_handle)) {
            if (GfComEvtAnim* evtAnim = obj->getComponent<GfComEvtAnim>(2)) {
                evtAnim->execCmd("C_btidle");
            }
        }
        requestState(1);
    }
}

void GfEvtModelDriver::StateEndBattle::enter(GfEvtModelDriver* owner, ai::State* prev) {
    if (GfMountManager::getMountType(owner->m_handle, static_cast<GFATTACH>(0)) == 2) {
        return;
    }
    mm::mtl::FixStr<32> weaponCommand;
    mm::mtl::FixStr<32> command;
    GfGameUtil::makeWeaponCommandBattle(weaponCommand, owner->m_handle, false, false);
    GfGameUtil::makeCommandBattle(command, false);
    mm::mtl::FixStr<32> state;
    GfGameUtil::makeStateBattleByBlade(state, owner->m_bladeId, false);
    fn_710029C9B4(owner->m_handle, command, state);
    if (GfAppendHandles* handles = GfMountManager::getAppendHandles(owner->m_handle, static_cast<GFATTACH>(0))) {
        for (int i = 0; i < 10; i++) {
            GF_OBJ_HANDLE* handle = handles->getObjHandles()[i];
            if (handle != reinterpret_cast<GF_OBJ_HANDLE*>(-1)) {
                if (GfComAsm* com = GfObjUtil::getObj(handle)->getComponent<GfComAsm>(2)) {
                    com->execCmd(weaponCommand.m_str, static_cast<AnimLayer>(0));
                }
            }
        }
    }
    if (GfDataDriver::fn_710023F9A8(owner->m_objId) && GfDataDriver::fn_7100241660(owner->m_objId)) {
        SCOM_OBJ_ALPHA::createWeapon(owner->m_handle, 0.5f, 0.0f);
    }
}

void GfEvtModelDriver::StateEndBattle::update(GfEvtModelDriver* owner, const fw::UpdateInfo& info) {
    GfComEvtAnim* anim = GfObjUtil::getObj(owner->m_handle)->getComponent<GfComEvtAnim>(2);
    if (anim == nullptr || anim->isEnd(static_cast<AnimLayer>(0))) {
        if (GfObj* obj = GfObjUtil::getObj(owner->m_handle)) {
            if (GfComEvtAnim* evtAnim = obj->getComponent<GfComEvtAnim>(2)) {
                evtAnim->execCmd("C_idle");
            }
        }
        mm::mtl::FixStr<32> weaponState;
        GfGameUtil::makeWeaponStateIdle(weaponState, owner->m_handle, false);
        if (GfAppendHandles* handles = GfMountManager::getAppendHandles(owner->m_handle, static_cast<GFATTACH>(0))) {
            for (int i = 0; i < 10; i++) {
                GF_OBJ_HANDLE* handle = handles->getObjHandles()[i];
                if (handle != reinterpret_cast<GF_OBJ_HANDLE*>(-1)) {
                    if (GfComAsm* com = GfObjUtil::getObj(handle)->getComponent<GfComAsm>(2)) {
                        com->setState(weaponState.m_str, static_cast<AnimLayer>(0));
                    }
                }
            }
        }
        requestState(0);
    }
}

GfEvtModelSalvage* GfEvtModelSalvage::create(GfInitParamDriver& param) {
#line 734
    GfEvtModelSalvage* model = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) GfEvtModelSalvage(param);
    model->addRef();
    return model;
}

GfEvtModelBlade* GfEvtModelBlade::create(GfInitParamBlade& param) {
    if (GfGameEvent::getPlayEventId() == 0x4A3A && param.m_objId == 0x3F0) {
        param.m_weaponId = mm::mtl::PtrSingleton<GfBdatChrBl>::sys()->getChrBlDefWeapon(0x3F0);
    }
#line 810
    GfEvtModelBlade* model = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) GfEvtModelBlade(param);
    model->addRef();
    return model;
}

void GfEvtModelDriver::setDispJiji(bool disp) {
    GfAppendHandles* jiji = GfMountManager::getAppendHandles(m_handle, static_cast<GFATTACH>(1));
    if (jiji != nullptr) {
        for (int i = 0; i < 10; i++) {
            GfObjAcc acc(jiji->getObjHandles()[i]);
            if (acc.m_obj != nullptr) {
                acc.setAlphaNormal(disp ? 1.0f : 0.0f);
            }
        }
    }
}

// GEN driveranim begin
void GfEvtModelDriver::playAnimWeaponRightCS(const char* name) {
    GfWeapon* weapon = GfMountManager::getGfWeapon(m_handle, static_cast<GFATTACH>(0));
    if (weapon != nullptr) {
        if (GfObj* obj = GfObjUtil::getObj(weapon->getObjHandles()[0])) {
            if (GfComPackAnim* anim = obj->getComponent<GfComPackAnim>(2)) {
                anim->play(name);
            }
        }
    }
}

bool GfEvtModelDriver::isPlayEndAnimWeaponRightCS() {
    GfWeapon* weapon = GfMountManager::getGfWeapon(m_handle, static_cast<GFATTACH>(0));
    if (weapon != nullptr) {
        if (GfObj* obj = GfObjUtil::getObj(weapon->getObjHandles()[0])) {
            if (GfComPackAnim* anim = obj->getComponent<GfComPackAnim>(2)) {
                if (!anim->isPlayEnd()) {
                    return false;
                }
            }
        }
    }
    return true;
}

void GfEvtModelDriver::setAnimSpeedWeaponRightCS(float speed) {
    GfWeapon* weapon = GfMountManager::getGfWeapon(m_handle, static_cast<GFATTACH>(0));
    if (weapon != nullptr) {
        if (GfObj* obj = GfObjUtil::getObj(weapon->getObjHandles()[0])) {
            if (GfComPackAnim* anim = obj->getComponent<GfComPackAnim>(2)) {
                anim->setSpeed(speed);
            }
        }
    }
}

void GfEvtModelDriver::playAnimWeaponLeftCS(const char* name) {
    GfWeapon* weapon = GfMountManager::getGfWeapon(m_handle, static_cast<GFATTACH>(0));
    if (weapon != nullptr) {
        if (GfObj* obj = GfObjUtil::getObj(weapon->getObjHandles()[1])) {
            if (GfComPackAnim* anim = obj->getComponent<GfComPackAnim>(2)) {
                anim->play(name);
            }
        }
    }
}

bool GfEvtModelDriver::isPlayEndAnimWeaponLeftCS() {
    GfWeapon* weapon = GfMountManager::getGfWeapon(m_handle, static_cast<GFATTACH>(0));
    if (weapon != nullptr) {
        if (GfObj* obj = GfObjUtil::getObj(weapon->getObjHandles()[1])) {
            if (GfComPackAnim* anim = obj->getComponent<GfComPackAnim>(2)) {
                if (!anim->isPlayEnd()) {
                    return false;
                }
            }
        }
    }
    return true;
}

void GfEvtModelDriver::setAnimSpeedWeaponLeftCS(float speed) {
    GfWeapon* weapon = GfMountManager::getGfWeapon(m_handle, static_cast<GFATTACH>(0));
    if (weapon != nullptr) {
        if (GfObj* obj = GfObjUtil::getObj(weapon->getObjHandles()[1])) {
            if (GfComPackAnim* anim = obj->getComponent<GfComPackAnim>(2)) {
                anim->setSpeed(speed);
            }
        }
    }
}
// GEN driveranim end

GfEvtModelBlade::~GfEvtModelBlade() {
    m_fsm.cleanup();
}

// GEN blade begin
void GfEvtModelBlade::update(fw::UpdateInfo const& info) {
    m_fsm.update(&info);
}

void GfEvtModelBlade::setWeaponBattleCommand() {
    m_fsm.setState(2);
}

void GfEvtModelBlade::setWeaponFieldCommand() {
    m_fsm.setState(3);
}

void GfEvtModelBlade::setWeaponBattleState() {
    GfMountManager::execMount(m_handle, static_cast<GFATTACH>(0), static_cast<OPTMNT>(1));
    mm::mtl::FixStr<32> state;
    GfGameUtil::makeStateIdle(state, m_handle, true);
    if (GfObj* obj = GfObjUtil::getObj(m_handle)) {
        if (GfComEvtAnim* anim = obj->getComponent<GfComEvtAnim>(2)) {
            anim->setState(state.m_str);
        }
    }
}

void GfEvtModelBlade::setWeaponFieldState() {
    GfMountManager::execMount(m_handle, static_cast<GFATTACH>(0), static_cast<OPTMNT>(2));
    mm::mtl::FixStr<32> state;
    GfGameUtil::makeStateIdle(state, m_handle, false);
    if (GfObj* obj = GfObjUtil::getObj(m_handle)) {
        if (GfComEvtAnim* anim = obj->getComponent<GfComEvtAnim>(2)) {
            anim->setState(state.m_str);
        }
    }
}

void GfEvtModelBlade::setWeaponBattleMount() {
    GfMountManager::execMount(m_handle, static_cast<GFATTACH>(0), static_cast<OPTMNT>(1));
}

void GfEvtModelBlade::setWeaponFieldMount() {
    GfMountManager::execMount(m_handle, static_cast<GFATTACH>(0), static_cast<OPTMNT>(2));
}

void GfEvtModelBlade::setDispWeapon(bool disp) {
    GfAppendHandles* weapons = GfMountManager::getAppendHandles(m_handle, static_cast<GFATTACH>(0));
    for (int i = 0; i < 10; i++) {
        GfObjAcc acc(weapons->getObjHandles()[i]);
        if (acc.m_obj != nullptr) {
            acc.setDisp(static_cast<OBJDISP>(2), disp);
        }
    }
}

void GfEvtModelBlade::setDispWeapon(bool left, bool disp) {
    GfWeapon* weapon = GfMountManager::getGfWeapon(m_handle, static_cast<GFATTACH>(0));
    if (weapon != nullptr) {
        GF_OBJ_HANDLE* const* handles = weapon->getObjHandles();
        GfObjAcc acc(left ? handles[1] : handles[0]);
        if (acc.m_obj != nullptr) {
            acc.setDisp(static_cast<OBJDISP>(2), disp);
        }
    }
}

GF_OBJ_HANDLE* GfEvtModelBlade::getWeaponHandleRight() const {
    GfWeapon* weapon = GfMountManager::getGfWeapon(m_handle, static_cast<GFATTACH>(0));
    if (weapon != nullptr) {
        return weapon->getObjHandles()[0];
    }
    return reinterpret_cast<GF_OBJ_HANDLE*>(-1);
}

GF_OBJ_HANDLE* GfEvtModelBlade::getWeaponHandleLeft() const {
    GfWeapon* weapon = GfMountManager::getGfWeapon(m_handle, static_cast<GFATTACH>(0));
    if (weapon != nullptr) {
        return weapon->getObjHandles()[1];
    }
    return reinterpret_cast<GF_OBJ_HANDLE*>(-1);
}

void GfEvtModelBlade::playAnimWeaponRightCS(const char* name) {
    GfWeapon* weapon = GfMountManager::getGfWeapon(m_handle, static_cast<GFATTACH>(0));
    if (weapon != nullptr) {
        if (GfObj* obj = GfObjUtil::getObj(weapon->getObjHandles()[0])) {
            if (GfComPackAnim* anim = obj->getComponent<GfComPackAnim>(2)) {
                anim->play(name);
            }
        }
    }
}

bool GfEvtModelBlade::isPlayEndAnimWeaponRightCS() {
    GfWeapon* weapon = GfMountManager::getGfWeapon(m_handle, static_cast<GFATTACH>(0));
    if (weapon != nullptr) {
        if (GfObj* obj = GfObjUtil::getObj(weapon->getObjHandles()[0])) {
            if (GfComPackAnim* anim = obj->getComponent<GfComPackAnim>(2)) {
                if (!anim->isPlayEnd()) {
                    return false;
                }
            }
        }
    }
    return true;
}

void GfEvtModelBlade::setAnimSpeedWeaponRightCS(float speed) {
    GfWeapon* weapon = GfMountManager::getGfWeapon(m_handle, static_cast<GFATTACH>(0));
    if (weapon != nullptr) {
        if (GfObj* obj = GfObjUtil::getObj(weapon->getObjHandles()[0])) {
            if (GfComPackAnim* anim = obj->getComponent<GfComPackAnim>(2)) {
                anim->setSpeed(speed);
            }
        }
    }
}

void GfEvtModelBlade::playAnimWeaponLeftCS(const char* name) {
    GfWeapon* weapon = GfMountManager::getGfWeapon(m_handle, static_cast<GFATTACH>(0));
    if (weapon != nullptr) {
        if (GfObj* obj = GfObjUtil::getObj(weapon->getObjHandles()[1])) {
            if (GfComPackAnim* anim = obj->getComponent<GfComPackAnim>(2)) {
                anim->play(name);
            }
        }
    }
}

bool GfEvtModelBlade::isPlayEndAnimWeaponLeftCS() {
    GfWeapon* weapon = GfMountManager::getGfWeapon(m_handle, static_cast<GFATTACH>(0));
    if (weapon != nullptr) {
        if (GfObj* obj = GfObjUtil::getObj(weapon->getObjHandles()[1])) {
            if (GfComPackAnim* anim = obj->getComponent<GfComPackAnim>(2)) {
                if (!anim->isPlayEnd()) {
                    return false;
                }
            }
        }
    }
    return true;
}

void GfEvtModelBlade::setAnimSpeedWeaponLeftCS(float speed) {
    GfWeapon* weapon = GfMountManager::getGfWeapon(m_handle, static_cast<GFATTACH>(0));
    if (weapon != nullptr) {
        if (GfObj* obj = GfObjUtil::getObj(weapon->getObjHandles()[1])) {
            if (GfComPackAnim* anim = obj->getComponent<GfComPackAnim>(2)) {
                anim->setSpeed(speed);
            }
        }
    }
}
// GEN blade end

void GfEvtModelBlade::StateStartBattle::update(GfEvtModelBlade* owner, const fw::UpdateInfo& info) {
    GfComEvtAnim* anim = GfObjUtil::getObj(owner->m_handle)->getComponent<GfComEvtAnim>(2);
    if (anim == nullptr || anim->isEnd(static_cast<AnimLayer>(0))) {
        if (GfObj* obj = GfObjUtil::getObj(owner->m_handle)) {
            if (GfComEvtAnim* evtAnim = obj->getComponent<GfComEvtAnim>(2)) {
                evtAnim->execCmd("C_btidle");
            }
        }
        requestState(1);
    }
}

void GfEvtModelBlade::StateEndBattle::update(GfEvtModelBlade* owner, const fw::UpdateInfo& info) {
    GfComEvtAnim* anim = GfObjUtil::getObj(owner->m_handle)->getComponent<GfComEvtAnim>(2);
    if (anim == nullptr || anim->isEnd(static_cast<AnimLayer>(0))) {
        if (GfObj* obj = GfObjUtil::getObj(owner->m_handle)) {
            if (GfComEvtAnim* evtAnim = obj->getComponent<GfComEvtAnim>(2)) {
                evtAnim->execCmd("C_idle");
            }
        }
        requestState(0);
    }
}

GfEvtModelEnemy::~GfEvtModelEnemy() {
    m_fsm.cleanup();
}

// GEN enemy begin
GfEvtModelEnemy* GfEvtModelEnemy::create(GfInitParamEnemy& param) {
#line 1120
    GfEvtModelEnemy* model = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) GfEvtModelEnemy(param);
    model->addRef();
    return model;
}

void GfEvtModelEnemy::update(fw::UpdateInfo const& info) {
    m_fsm.update(&info);
}

void GfEvtModelEnemy::setWeaponBattleCommand() {
    m_fsm.setState(2);
}

void GfEvtModelEnemy::setWeaponFieldCommand() {
    m_fsm.setState(3);
}

void GfEvtModelEnemy::setWeaponBattleState() {
    setWeaponBattleMount();
    mm::mtl::FixStr<32> weaponState;
    mm::mtl::FixStr<32> state;
    GfGameUtil::makeWeaponStateIdle(weaponState, m_handle, true);
    GfGameUtil::makeStateIdle(state, m_handle, true);
    if (GfObj* obj = GfObjUtil::getObj(m_handle)) {
        if (GfComEvtAnim* anim = obj->getComponent<GfComEvtAnim>(2)) {
            anim->setState(state.m_str);
        }
    }
    if (GfAppendHandles* handles = GfMountManager::getAppendHandles(m_handle, static_cast<GFATTACH>(0))) {
        for (int i = 0; i < 10; i++) {
            GF_OBJ_HANDLE* handle = handles->getObjHandles()[i];
            if (handle != reinterpret_cast<GF_OBJ_HANDLE*>(-1)) {
                if (GfComAsm* com = GfObjUtil::getObj(handle)->getComponent<GfComAsm>(2)) {
                    com->setState(weaponState.m_str, static_cast<AnimLayer>(0));
                }
            }
        }
    }
}

void GfEvtModelEnemy::setWeaponFieldState() {
    GfMountManager::execMount(m_handle, static_cast<GFATTACH>(0), static_cast<OPTMNT>(2));
    mm::mtl::FixStr<32> weaponState;
    mm::mtl::FixStr<32> state;
    GfGameUtil::makeWeaponStateIdle(weaponState, m_handle, false);
    GfGameUtil::makeStateIdle(state, m_handle, false);
    if (GfObj* obj = GfObjUtil::getObj(m_handle)) {
        if (GfComEvtAnim* anim = obj->getComponent<GfComEvtAnim>(2)) {
            anim->setState(state.m_str);
        }
    }
    if (GfAppendHandles* handles = GfMountManager::getAppendHandles(m_handle, static_cast<GFATTACH>(0))) {
        for (int i = 0; i < 10; i++) {
            GF_OBJ_HANDLE* handle = handles->getObjHandles()[i];
            if (handle != reinterpret_cast<GF_OBJ_HANDLE*>(-1)) {
                if (GfComAsm* com = GfObjUtil::getObj(handle)->getComponent<GfComAsm>(2)) {
                    com->setState(weaponState.m_str, static_cast<AnimLayer>(0));
                }
            }
        }
    }
}

void GfEvtModelEnemy::setWeaponBattleMount() {
    GfMountManager::execMount(m_handle, static_cast<GFATTACH>(0), static_cast<OPTMNT>(1));
}

void GfEvtModelEnemy::setWeaponFieldMount() {
    GfMountManager::execMount(m_handle, static_cast<GFATTACH>(0), static_cast<OPTMNT>(2));
}

void GfEvtModelEnemy::setDispWeapon(bool disp) {
    GfAppendHandles* weapons = GfMountManager::getAppendHandles(m_handle, static_cast<GFATTACH>(0));
    for (int i = 0; i < 10; i++) {
        GfObjAcc acc(weapons->getObjHandles()[i]);
        if (acc.m_obj != nullptr) {
            acc.setDisp(static_cast<OBJDISP>(2), disp);
        }
    }
}

void GfEvtModelEnemy::setDispWeapon(bool left, bool disp) {
    GfWeapon* weapon = GfMountManager::getGfWeapon(m_handle, static_cast<GFATTACH>(0));
    if (weapon != nullptr) {
        GF_OBJ_HANDLE* const* handles = weapon->getObjHandles();
        GfObjAcc acc(left ? handles[1] : handles[0]);
        if (acc.m_obj != nullptr) {
            acc.setDisp(static_cast<OBJDISP>(2), disp);
        }
    }
}

GF_OBJ_HANDLE* GfEvtModelEnemy::getWeaponHandleRight() const {
    GfWeapon* weapon = GfMountManager::getGfWeapon(m_handle, static_cast<GFATTACH>(0));
    if (weapon != nullptr) {
        return weapon->getObjHandles()[0];
    }
    return reinterpret_cast<GF_OBJ_HANDLE*>(-1);
}

GF_OBJ_HANDLE* GfEvtModelEnemy::getWeaponHandleLeft() const {
    GfWeapon* weapon = GfMountManager::getGfWeapon(m_handle, static_cast<GFATTACH>(0));
    if (weapon != nullptr) {
        return weapon->getObjHandles()[1];
    }
    return reinterpret_cast<GF_OBJ_HANDLE*>(-1);
}
// GEN enemy end

void GfEvtModelEnemy::StateStartBattle::enter(GfEvtModelEnemy* owner, ai::State* prev) {
    mm::mtl::FixStr<32> weaponCommand;
    mm::mtl::FixStr<32> command;
    GfGameUtil::makeWeaponCommandBattle(weaponCommand, owner->m_handle, true, true);
    GfGameUtil::makeCommandBattle(command, true);
    mm::mtl::FixStr<32> state;
    GfGameUtil::makeStateBattle(state, owner->m_handle, true);
    fn_710029C9B4(owner->m_handle, command, state);
    if (GfAppendHandles* handles = GfMountManager::getAppendHandles(owner->m_handle, static_cast<GFATTACH>(0))) {
        for (int i = 0; i < 10; i++) {
            GF_OBJ_HANDLE* handle = handles->getObjHandles()[i];
            if (handle != reinterpret_cast<GF_OBJ_HANDLE*>(-1)) {
                if (GfComAsm* com = GfObjUtil::getObj(handle)->getComponent<GfComAsm>(2)) {
                    com->execCmd(weaponCommand.m_str, static_cast<AnimLayer>(0));
                }
            }
        }
    }
    if (GfMountManager::getMountType(owner->m_handle, static_cast<GFATTACH>(0)) != 1) {
        owner->setWeaponBattleMount();
    }
}

void GfEvtModelEnemy::StateStartBattle::update(GfEvtModelEnemy* owner, const fw::UpdateInfo& info) {
    GfComEvtAnim* anim = GfObjUtil::getObj(owner->m_handle)->getComponent<GfComEvtAnim>(2);
    if (anim == nullptr || anim->isEnd(static_cast<AnimLayer>(0))) {
        if (GfObj* obj = GfObjUtil::getObj(owner->m_handle)) {
            if (GfComEvtAnim* evtAnim = obj->getComponent<GfComEvtAnim>(2)) {
                evtAnim->execCmd("C_btidle");
            }
        }
        requestState(1);
    }
}

void GfEvtModelEnemy::StateEndBattle::enter(GfEvtModelEnemy* owner, ai::State* prev) {
    if (GfMountManager::getMountType(owner->m_handle, static_cast<GFATTACH>(0)) == 2) {
        return;
    }
    mm::mtl::FixStr<32> weaponCommand;
    mm::mtl::FixStr<32> command;
    GfGameUtil::makeWeaponCommandBattle(weaponCommand, owner->m_handle, false, true);
    GfGameUtil::makeCommandBattle(command, false);
    mm::mtl::FixStr<32> state;
    GfGameUtil::makeStateBattle(state, owner->m_handle, false);
    fn_710029C9B4(owner->m_handle, command, state);
    if (GfAppendHandles* handles = GfMountManager::getAppendHandles(owner->m_handle, static_cast<GFATTACH>(0))) {
        for (int i = 0; i < 10; i++) {
            GF_OBJ_HANDLE* handle = handles->getObjHandles()[i];
            if (handle != reinterpret_cast<GF_OBJ_HANDLE*>(-1)) {
                if (GfComAsm* com = GfObjUtil::getObj(handle)->getComponent<GfComAsm>(2)) {
                    com->execCmd(weaponCommand.m_str, static_cast<AnimLayer>(0));
                }
            }
        }
    }
}

void GfEvtModelEnemy::StateEndBattle::update(GfEvtModelEnemy* owner, const fw::UpdateInfo& info) {
    GfComEvtAnim* anim = GfObjUtil::getObj(owner->m_handle)->getComponent<GfComEvtAnim>(2);
    if (anim == nullptr || anim->isEnd(static_cast<AnimLayer>(0))) {
        if (GfObj* obj = GfObjUtil::getObj(owner->m_handle)) {
            if (GfComEvtAnim* evtAnim = obj->getComponent<GfComEvtAnim>(2)) {
                evtAnim->execCmd("C_idle");
            }
        }
        requestState(0);
    }
}

GfEvtModelNpc::GfEvtModelNpc(GfInitParamNpc& param) : GfEvtModel(4, param.m_objId) {
    if (GfManager::isExecModeThater() ? mm::mtl::PtrSingleton<event::Manager>::sys()->pad_294 != 0
                                      : GfMenuManager::isOpenFullScreen() &&
                                            GfGameManager::isInnerState(static_cast<GF_STATE>(6))) {
        int type = param.pad_40;
        if (static_cast<unsigned int>(type - 7) < 3) {
            type += 3;
        }
        param.pad_40 = type;
    } else if (param.m_objId == 0x7D1) {
        param.pad_40 = 9;
    }
    param.pad_44 = 1;
    m_handle = GfObjFactory::createNpc(param);
}

// GEN npc begin
GfEvtModelNpc* GfEvtModelNpc::create(GfInitParamNpc& param) {
#line 1086
    GfEvtModelNpc* model = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) GfEvtModelNpc(param);
    model->addRef();
    return model;
}
// GEN npc end

GfEvtModelWeapon::GfEvtModelWeapon(GfInitParamWeapon& param) : GfEvtModel(2, param.m_objId) {
    m_weaponId = param.pad_128;
    // the UI layer while the theater or a full-screen menu shows the event, else layer 9
    bool ui = GfManager::isExecModeThater() ? mm::mtl::PtrSingleton<event::Manager>::sys()->pad_294 != 0
                                            : GfMenuManager::isOpenFullScreen() &&
                                                  GfGameManager::isInnerState(static_cast<GF_STATE>(6));
    int& layer = param.pad_40;
    layer = ui ? changeLayerUI(layer) : 9;
    m_weapons = *GfObjFactory::createDriverWeapon(param);
    for (int i = 0; i < 10; i++) {
        GF_OBJ_HANDLE* handle = m_weapons.getObjHandles()[i];
        if (handle != reinterpret_cast<GF_OBJ_HANDLE*>(-1)) {
            m_handle = handle;
            break;
        }
    }
}


// GEN weapon begin
GfEvtModelWeapon* GfEvtModelWeapon::create(GfInitParamWeapon& param) {
#line 1356
    GfEvtModelWeapon* model = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) GfEvtModelWeapon(param);
    model->addRef();
    return model;
}
// GEN weapon end

GfEvtModelWeapon::~GfEvtModelWeapon() {
    for (int i = 0; i < 10; i++) {
        GfObjUtil::destroy(m_weapons.getObjHandles()[i]);
    }
}

void GfEvtModelWeapon::playAnimData(void* data) {
    if (GfObj* obj = GfObjUtil::getObj(m_handle)) {
        if (GfComPackAnim* anim = obj->getComponent<GfComPackAnim>(2)) {
            anim->play(data);
        }
    }
}

void GfEvtModelWeapon::setScale(float scale) {
    GfObjAcc acc(m_handle);
    acc.setModelScale(scale);
}

void GfEvtModelWeapon::playAnimCS(const char* name) {
    if (GfObj* obj = GfObjUtil::getObj(m_handle)) {
        if (GfComPackAnim* anim = obj->getComponent<GfComPackAnim>(2)) {
            anim->play(name);
        }
    }
}

bool GfEvtModelWeapon::isPlayEndAnimCS() {
    if (GfObj* obj = GfObjUtil::getObj(m_handle)) {
        if (GfComPackAnim* anim = obj->getComponent<GfComPackAnim>(2)) {
            if (!anim->isPlayEnd()) {
                return false;
            }
        }
    }
    return true;
}

void GfEvtModelWeapon::setAnimSpeedCS(float speed) {
    if (GfObj* obj = GfObjUtil::getObj(m_handle)) {
        if (GfComPackAnim* anim = obj->getComponent<GfComPackAnim>(2)) {
            anim->setSpeed(speed);
        }
    }
}

void GfEvtModelWeapon::setWeaponBattleCommand() {
    mm::mtl::FixStr<32> command;
    GfGameUtil::makeWeaponCommandBattle(command, m_weaponId, true, false);
    for (int i = 0; i < 10; i++) {
        GF_OBJ_HANDLE* handle = m_weapons.getObjHandles()[i];
        if (handle != reinterpret_cast<GF_OBJ_HANDLE*>(-1)) {
            if (GfComAsm* com = GfObjUtil::getObj(handle)->getComponent<GfComAsm>(2)) {
                com->execCmd(command.m_str, static_cast<AnimLayer>(0));
            }
        }
    }
}

void GfEvtModelWeapon::setWeaponFieldCommand() {
    mm::mtl::FixStr<32> command;
    GfGameUtil::makeWeaponCommandBattle(command, m_weaponId, false, false);
    for (int i = 0; i < 10; i++) {
        GF_OBJ_HANDLE* handle = m_weapons.getObjHandles()[i];
        if (handle != reinterpret_cast<GF_OBJ_HANDLE*>(-1)) {
            if (GfComAsm* com = GfObjUtil::getObj(handle)->getComponent<GfComAsm>(2)) {
                com->execCmd(command.m_str, static_cast<AnimLayer>(0));
            }
        }
    }
}

void GfEvtModelWeapon::setWeaponBattleState() {
    mm::mtl::FixStr<32> state;
    GfGameUtil::makeWeaponStateIdle(state, m_weaponId, true);
    for (int i = 0; i < 10; i++) {
        GF_OBJ_HANDLE* handle = m_weapons.getObjHandles()[i];
        if (handle != reinterpret_cast<GF_OBJ_HANDLE*>(-1)) {
            if (GfComAsm* com = GfObjUtil::getObj(handle)->getComponent<GfComAsm>(2)) {
                com->setState(state.m_str, static_cast<AnimLayer>(0));
            }
        }
    }
}

void GfEvtModelWeapon::setWeaponFieldState() {
    mm::mtl::FixStr<32> state;
    GfGameUtil::makeWeaponStateIdle(state, m_weaponId, false);
    for (int i = 0; i < 10; i++) {
        GF_OBJ_HANDLE* handle = m_weapons.getObjHandles()[i];
        if (handle != reinterpret_cast<GF_OBJ_HANDLE*>(-1)) {
            if (GfComAsm* com = GfObjUtil::getObj(handle)->getComponent<GfComAsm>(2)) {
                com->setState(state.m_str, static_cast<AnimLayer>(0));
            }
        }
    }
}

void GfEvtModelSalvage::setTransform(const mm::Vec3& pos, float rotY) {
    if (GfGameObj::isValidGameObj(m_handle, false, nullptr)) {
        SCOM_OBJ_WARP_POS::create(m_handle, pos, mm::Vec3(0.0f, rotY * 0.017453292f, 0.0f), false);
    }
}

bool GfEvtModelSalvage::isValid() const {
    return GfGameObj::isValidGameObj(m_handle, false, nullptr);
}

GfEvtModelEvent::GfEvtModelEvent(GfInitParamEventObj& param) : GfEvtModel(3, param.m_objId) {
    if (GfManager::isExecModeThater() ? mm::mtl::PtrSingleton<event::Manager>::sys()->pad_294 != 0
                                      : GfMenuManager::isOpenFullScreen() &&
                                            GfGameManager::isInnerState(static_cast<GF_STATE>(6))) {
        int type = param.pad_40;
        if (static_cast<unsigned int>(type - 7) < 3) {
            type += 3;
        }
        param.pad_40 = type;
    }
    m_handle = GfObjFactory::createEventObj(param);
}

// GEN event begin
GfEvtModelEvent* GfEvtModelEvent::create(GfInitParamEventObj& param) {
#line 1522
    GfEvtModelEvent* model = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) GfEvtModelEvent(param);
    model->addRef();
    return model;
}
// GEN event end

void GfEvtModel::update(fw::UpdateInfo const&) {}
void GfEvtModel::setDispWeapon(bool) {}
void GfEvtModel::setDispWeapon(bool, bool) {}
GF_OBJ_HANDLE* GfEvtModel::getWeaponHandleRight() const {
    return reinterpret_cast<GF_OBJ_HANDLE*>(-1);
}
GF_OBJ_HANDLE* GfEvtModel::getWeaponHandleLeft() const {
    return reinterpret_cast<GF_OBJ_HANDLE*>(-1);
}
void GfEvtModel::setWeaponBattleCommand() {}
void GfEvtModel::setWeaponFieldCommand() {}
void GfEvtModel::setWeaponBattleState() {}
void GfEvtModel::setWeaponFieldState() {}
void GfEvtModel::setWeaponBattleMount() {}
void GfEvtModel::setWeaponFieldMount() {}

mm::mtl::RTTI GfEvtModel::m_rtti("GfEvtModel", nullptr, nullptr);
mm::mtl::RTTI GfEvtModelDriver::m_rtti("GfEvtModelDriver", &GfEvtModel::m_rtti, nullptr);
mm::mtl::RTTI GfEvtModelSalvage::m_rtti("GfEvtModelSalvage", &GfEvtModel::m_rtti, nullptr);
mm::mtl::RTTI GfEvtModelBlade::m_rtti("GfEvtModelBlade", &GfEvtModel::m_rtti, nullptr);
mm::mtl::RTTI GfEvtModelNpc::m_rtti("GfEvtModelNpc", &GfEvtModel::m_rtti, nullptr);
mm::mtl::RTTI GfEvtModelEnemy::m_rtti("GfEvtModelEnemy", &GfEvtModel::m_rtti, nullptr);
mm::mtl::RTTI GfEvtModelWeapon::m_rtti("GfEvtModelWeapon", &GfEvtModel::m_rtti, nullptr);
mm::mtl::RTTI GfEvtModelEvent::m_rtti("GfEvtModelEvent", &GfEvtModel::m_rtti, nullptr);

}  // namespace gf

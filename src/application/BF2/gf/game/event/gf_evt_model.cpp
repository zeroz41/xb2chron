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

// GEN npc begin
GfEvtModelNpc* GfEvtModelNpc::create(GfInitParamNpc& param) {
#line 1086
    GfEvtModelNpc* model = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) GfEvtModelNpc(param);
    model->addRef();
    return model;
}
// GEN npc end

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

bool GfEvtModelSalvage::isValid() const {
    return GfGameObj::isValidGameObj(m_handle, false, nullptr);
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

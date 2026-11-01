#include "classes/fw/IColiEventListener.h"
#include "classes/gf/GfComBehaviorEnemy.h"
#include "classes/gf/GfFieldEnemySensor.h"
#include "classes/gf/GfObjSetupEnemy.h"
#include "classes/gf/TFieldExecCmd.h"
#include "classes/gf/GfComBehaviorEnemy.h"
#include "classes/gf/enemy/StateBattle.h"
#include "classes/gf/enemy/StateFieldIdle.h"
#include "classes/gf/enemy/StateFieldSpawn.h"
#include "classes/gf/enemy/StateFieldAreaWalk.h"
#include "classes/gf/enemy/StateFieldWalk.h"
#include "classes/gf/enemy/StateFieldHome.h"
#include "classes/gf/enemy/StateFieldSquadMember.h"
#include "classes/gf/enemy/StateFieldBlade.h"
#include "classes/gf/GfComBehaviorEnemy/Listener.h"
#include "classes/gf/GfObj.h"
#include "classes/gf/GfComTransform.h"
#include "classes/fw/ReferenceFrame.h"
#include "classes/gf/DataParamAcc.h"
#include "gf/SDataEnemy.h"
#include "classes/gmk/AGmkBase.h"
#include "fw/UpdateInfo.h"
#include "classes/fw/ColiObject.h"
#include "classes/gf/GfObjManager.h"
#include "classes/gf/GfObjSetupEnemy.h"
#include "classes/gf/GfDataBdat.h"
#include "classes/gf/GfMenuObjTargetInfo.h"
#include "classes/gf/GfMenuCallContext.h"
#include "gf/GfObjInfo.h"
#include "plugin/Bdat.h"
#include "classes/gmk/GmkBattleLock.h"
#include "classes/gmk/GmkRoutedEnemy.h"
#include "classes/gf/GfStateBase.h"
#include "gf/MsgObjectNotifyAsmCallback.h"
#include "gf/CallBackCache.h"
#include "gf/GfParamEnemyReflection.h"
#include "gf/GfObjAcc.h"
#include "classes/gf/GfComCollider.h"
#include "classes/fw/ColiMoveObject.h"
#include "classes/gf/GfFieldLocalSteer.h"
#include "classes/gmk/GmkEnemy.h"
#include "classes/navi/NvmshAcObj.h"
#include "gf/GfMenuBdat.h"
#include "gf/GfGameUtil.h"
#include "math.h"

namespace gf {

fw::ColiMoveObject* GfBehaviorEnemyField::getColiObject() const {
    GfObjAcc acc(m_handle);
    GfObj* obj = acc.getObj();
    if (obj != nullptr) {
        const GfComCollider* collider = obj->getComponent<GfComCollider>(4);
        if (collider != nullptr) {
            fw::ColiObject* coli = collider->m_coliObjects[0];
            if (coli != nullptr) {
                return coli->getRTTI()->isKindOf(&fw::ColiMoveObject::m_rtti) ? static_cast<fw::ColiMoveObject*>(coli)
                                                                             : nullptr;
            }
        }
    }
    return nullptr;
}

gmk::GmkRouteNavi* GfBehaviorEnemyField::getGmkRouteNavi() const {
    gmk::AGmkBase* gmk = gmk::getBindedGmkInst(m_handle);
    if (gmk != nullptr && gmk->getGmkType() == gmk::GmkRoutedEnemy::TYPE) {
        return static_cast<gmk::GmkRoutedEnemy*>(gmk)->findRouteNavi(m_handle);
    }
    return nullptr;
}

bool GfBehaviorEnemyField::isArrivedToGoal() const {
    if (m_localSteer.isTimeOutCollide()) {
        return true;
    }
    const mm::Vec3& pos = m_owner->getTransform().position;
    float dy = m_goalPos.y - pos.y;
    if (pad_1c < dy) {
        return false;
    }
    float dx = m_goalPos.x - pos.x;
    float dz = m_goalPos.z - pos.z;
    if (pad_20 != 3) {
        dy = 0.0f;
    }
    float dist = dx * dx + dy * dy + dz * dz;
    return !(pad_18 * pad_18 < dist);
}

void GfBehaviorEnemyField::applyFieldMoveSpeed(enemy::STATE_ID state, GfComBehaviorEnemy& owner) {
    applyFieldMoveSpeed(getFieldMoveSpeedType(state), owner);
}

void GfBehaviorEnemyField::applyFieldMoveSpeed(MoveSpeed speed, GfComBehaviorEnemy& owner) {
    MoveSpeed current = MoveSpeed(0);
    if (owner.m_turnCmd.pad_6c) {
        current = getFieldMoveSpeedType(owner.getStateId());
    }
    applyFieldMoveSpeed(current, speed, owner);
}

void GfBehaviorEnemyField::applyFieldMoveSpeed(MoveSpeed from, MoveSpeed to, GfComBehaviorEnemy&) {
    float speed = getWalkSpeed();
    switch (to) {
    case 0:
        speed = m_moveSpeed.m_speedMin;
        break;
    case 1:
        speed = getWalkSpeed();
        break;
    case 2:
        speed = getRunSpeed();
        break;
    }
    const EnemeyMoveParam* param = getEnemeyMoveParam(pad_36);
    float rate;
    switch (from) {
    case 0:
        rate = to == 1 ? param->pad_0 : param->pad_8;
        break;
    case 1:
        rate = to == 0 ? param->pad_10 : param->pad_4;
        break;
    case 2:
        rate = to == 0 ? param->pad_14 : param->pad_c;
        break;
    default:
        rate = 0.0f;
        break;
    }
    m_moveSpeed.setSpeedKmph(speed, rate);
}

GfComBehaviorEnemy::~GfComBehaviorEnemy() {
    if (pad_54e0) {
        pad_54e0 = false;
        if (m_field.m_sensor.m_gmkAcc.isValid()) {
            static_cast<gmk::GmkBattleLock*>(m_field.m_sensor.m_gmkAcc.m_gmk)->pad_c4--;
        }
    }
    cleanup();
}

void GfComBehaviorEnemy::cleanup() {
    m_field.dispose();
    disposeFsm();
    disposeMenuObj();
    m_pluginManager.cleanup();
    pad_138 = nullptr;
}

GfBehaviorEnemyField::~GfBehaviorEnemyField() {
    dispose();
}

// GfComBehavior's own empty virtuals (its table is emitted here: changeLayer is its key function)
const fw::Transform& GfComBehaviorEnemy::getTransformToSearchPlayer() const {
    if (pad_138.get() != nullptr) {
        return pad_138.get()->getWorldTransform();
    }
    return getTransform();
}

fw::ColiMoveObject* GfComBehaviorEnemy::getColiObject() const {
    const GfComCollider* collider = m_owner->getComponent<GfComCollider>(4);
    if (collider != nullptr) {
        fw::ColiObject* coli = collider->m_coliObjects[0];
        if (coli != nullptr) {
            return coli->getRTTI()->isKindOf(&fw::ColiMoveObject::m_rtti) ? static_cast<fw::ColiMoveObject*>(coli)
                                                                         : nullptr;
        }
    }
    return nullptr;
}

void GfComBehavior::changeLayer(unsigned int, unsigned int) {}

void GfComBehavior::procAnimCallback(GfComAsm*, const CallBackCache&) {}

gmk::AGmkBase* GfComBehaviorEnemy::getBindedGmkInst() const {
    return gmk::getBindedGmkInst(static_cast<GfObj*>(m_owner)->m_handle);
}

const fw::Transform& GfComBehaviorEnemy::getTransform() const {
    GfComTransform* transform = static_cast<GfObj*>(m_owner)->getComponent<GfComTransform>(0);
    return transform->getFrame()->getWorldTransform();
}

bool GfComBehaviorEnemy::isFly() const {
    DataParamAcc acc(static_cast<GfObj*>(m_owner)->m_handle);
    return acc.getSDataEnemy()->m_actType == 3;
}

bool GfComBehaviorEnemy::isWater() const {
    DataParamAcc acc(static_cast<GfObj*>(m_owner)->m_handle);
    return acc.getSDataEnemy()->m_actType == 1;
}

void GfComBehaviorEnemy::createFsm() {
    if (!m_buildingFsm) {
        m_buildingFsm = true;
        m_hfsm.cleanup();
    }
    m_hfsm.beginSetup(this, 16, 3);
    m_hfsm.registerState<enemy::StateBattle>(0, -1);
    m_hfsm.registerState<enemy::StateFieldIdle>(1, -1);
    m_hfsm.registerState<enemy::StateFieldIdle>(2, -1);
    m_hfsm.registerState<enemy::StateFieldIdle>(3, -1);
    m_hfsm.registerState<enemy::StateFieldIdle>(4, -1);
    m_hfsm.registerState<enemy::StateFieldIdle>(5, -1);
    m_hfsm.registerState<enemy::StateFieldSpawn>(6, -1);
    m_hfsm.registerState<enemy::StateFieldSpawn>(7, -1);
    m_hfsm.registerState<enemy::StateFieldAreaWalk>(8, -1);
    m_hfsm.registerState<enemy::StateFieldWalk>(9, -1);
    m_hfsm.registerState<enemy::StateFieldAreaWalk>(10, -1);
    m_hfsm.registerState<enemy::StateFieldWalk>(11, -1);
    m_hfsm.registerState<enemy::StateFieldHome>(13, -1);
    m_hfsm.registerState<enemy::StateFieldSquadMember>(14, -1);
    m_hfsm.registerState<enemy::StateFieldBlade>(15, -1);
    m_hfsm.endSetup();
    m_buildingFsm = false;
}

void GfComBehaviorEnemy::createMenuObj() {
    disposeMenuObj();
    m_menuContext = GfMenuCallContext::create();
    GfMenuObjTargetInfo::OpenEnemyParam param;
    MenuOffset& offset = param.m_offset;
    param.m_obj = static_cast<GfObj*>(m_owner)->m_handle;
    int offsetId = GfGameUtil::getUiOffsetId(param.m_obj);
    offset.m_bone = nullptr;
    offset.m_offset = mm::Vec3::zero;
    GfMenuBdat::getMenuOffset(offsetId, offset);
    GfMenuObjTargetInfo::openEnemy(m_menuContext, param);
}

float GfComBehaviorEnemy::getCollisionRadius() const {
    const GfComCollider* collider = m_owner->getComponent<GfComCollider>(4);
    mm::Vec3 min;
    mm::Vec3 max;
    if (collider->m_coliObjects[0]->getAABB(min, max)) {
        return (max - min).length() * 0.5f;
    }
    return 0.0f;
}

void GfFieldEnemySensor::enter(const fw::IColiEventListener::EnterInfo& info) {
    if (m_coli == info.m_self) {
        m_coliHit = true;
    } else if (m_coli2 == info.m_self) {
        m_coli2Hit = true;
    }
}

void GfFieldEnemySensor::leave(const fw::IColiEventListener::LeaveInfo& info) {
    if (m_coli == info.m_self) {
        m_coliHit = false;
    } else if (m_coli2 == info.m_self) {
        m_coli2Hit = false;
    }
}

enemy::STATE_ID GfComBehaviorEnemy::getStateId() const {
    if (m_hfsm.m_pState != nullptr) {
        return static_cast<enemy::STATE_ID>(m_hfsm.m_pState->m_stateID);
    }
    return static_cast<enemy::STATE_ID>(-1);
}

bool GfComBehaviorEnemy::isFlyInsect() const {
    if (!isFly()) {
        return false;
    }
    unsigned char* fp = GfDataBdat::getFP(0x6e);
    GfObjSetupEnemy* setup = mm::mtl::rttiCast<GfObjSetupEnemy>(GfObjManager::getObjInfo(static_cast<GfObj*>(m_owner)->m_handle)->m_setup);
    if (setup->m_actMoveId == 0) {
        return false;
    }
    return Bdat::getValCheck(fp, "actMove_Atr", setup->m_actMoveId, 1) & 1;
}

bool GfComBehaviorEnemy::isFlyCircle() const {
    if (!isFly()) {
        return false;
    }
    unsigned char* fp = GfDataBdat::getFP(0x6e);
    GfObjSetupEnemy* setup = mm::mtl::rttiCast<GfObjSetupEnemy>(GfObjManager::getObjInfo(static_cast<GfObj*>(m_owner)->m_handle)->m_setup);
    if (setup->m_actMoveId == 0) {
        return false;
    }
    return (Bdat::getValCheck(fp, "actMove_Atr", setup->m_actMoveId, 1) >> 1) & 1;
}

unsigned int GfComBehaviorEnemy::getBdatId_CHR_EnArrange() const {
    GfObjSetupEnemy* setup = mm::mtl::rttiCast<GfObjSetupEnemy>(GfObjManager::getObjInfo(static_cast<GfObj*>(m_owner)->m_handle)->m_setup);
    return setup->m_enArrangeId;
}

void GfComBehaviorEnemy::disposeMenuObj() {
    if (m_menuContext != nullptr) {
        GfMenuObjTargetInfo::close(m_menuContext);
        if (m_menuContext != nullptr) {
            m_menuContext->release();
            m_menuContext = nullptr;
        }
    }
}

bool GfComBehaviorEnemy::isStateCondMatch(enemy::STATE_ID state) const {
    switch (state) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
        return true;
    case 8:
        return enemy::StateFieldAreaWalk::isCondMatch(*this);
    case 9:
        return enemy::StateFieldWalk::isCondMatch(*this);
    case 10:
        return enemy::StateFieldAreaWalk::isCondMatch(*this);
    case 11:
        return enemy::StateFieldWalk::isCondMatch(*this);
    case 13:
        return enemy::StateFieldHome::isCondMatch(*this);
    case 14:
        return enemy::StateFieldSquadMember::isCondMatch(*this);
    case 6:
    case 7:
    case 12:
    case 15:
        return false;
    default:
        return false;
    }
}

void GfComBehaviorEnemy::moveProc(mm::Vec3& dir) {
    const GfComCollider* collider = m_owner->getComponent<GfComCollider>(4);
    if (collider != nullptr) {
        fw::ColiObject* coli = collider->m_coliObjects[0];
        if (coli != nullptr) {
            coli->setDir(dir);
        }
    }
}

void GfComBehaviorEnemy::execTurnCmd(float rotY) {
    getTransform();
    TFieldExecCmdTurn<GfComAsm>::CreateInfo info;
    info.handle = static_cast<GfObj*>(m_owner)->m_handle;
    info.pad_8 = m_field.m_localSteer.getCurAngle() + rotY;
    info.pad_c = m_field.pad_30;
    m_turnCmd.create(info);
    if (!m_turnCmd.pad_6c) {
        m_field.m_moveSpeed.setSpeedKmph(m_field.m_moveSpeed.m_speedMin, 0.0f);
    }
}

void GfComBehaviorEnemy::execTurnCmd(float rotY, float speed, float threshold, float delay) {
    TFieldExecCmdTurn<GfComAsm>::CreateInfo info;
    info.handle = static_cast<GfObj*>(m_owner)->m_handle;
    info.pad_8 = m_field.m_localSteer.getCurAngle() + rotY;
    info.pad_c = threshold;
    info.pad_14 = speed;
    info.pad_18 = delay;
    m_turnCmd.create(info);
    if (!m_turnCmd.pad_6c) {
        m_field.m_moveSpeed.setSpeedKmph(m_field.m_moveSpeed.m_speedMin, 0.0f);
    }
}

void GfComBehaviorEnemy::execTurnCmdAccurately(float rotY) {
    getTransform();
    TFieldExecCmdTurn<GfComAsm>::CreateInfo info;
    info.handle = static_cast<GfObj*>(m_owner)->m_handle;
    info.pad_8 = m_field.m_localSteer.getCurAngle() + rotY;
    info.pad_c = 0.0f;
    m_turnCmd.create(info);
    if (!m_turnCmd.pad_6c) {
        m_field.m_moveSpeed.setSpeedKmph(m_field.m_moveSpeed.m_speedMin, 0.0f);
    }
}

void GfComBehaviorEnemy::execTurnCmdToGoal() {
    mm::Vec3 dir;
    m_field.getMoveDir(dir);
    dir.y = 0.0f;
    dir.normalize();
    execTurnCmd(::atan2f(dir.x, dir.z));
}

bool GfComBehaviorEnemy::isOtherMemberHome() const {
    return isOtherMemberHome<gmk::GmkEnemy>() || isOtherMemberHome<gmk::GmkRoutedEnemy>();
}

template <typename T>
bool GfComBehaviorEnemy::isOtherMemberHome() const {
    if (!m_field.pad_37) {
        return false;
    }
    gmk::AGmkBase* gmk = gmk::getBindedGmkInst(static_cast<GfObj*>(m_owner)->m_handle);
    if (gmk == nullptr || gmk->getGmkType() != T::TYPE) {
        return false;
    }
    const T* members = static_cast<const T*>(gmk);
    GF_OBJ_HANDLE* self = static_cast<GfObj*>(m_owner)->m_handle;
    unsigned int num = members->getGobInstNum();
    for (unsigned int i = 0; i < num; i++) {
        GF_OBJ_HANDLE* handle = members->getGobInst(i);
        if (self == handle) {
            continue;
        }
        GfObjAcc acc(handle);
        GfObj* obj = acc.getObj();
        if (obj == nullptr) {
            continue;
        }
        const GfComBehaviorEnemy* behavior = obj->getComponent<GfComBehaviorEnemy>(6);
        if (behavior != nullptr && behavior->getStateId() == 13) {
            return true;
        }
    }
    return false;
}

void GfComBehaviorEnemy::reqChangeBattle() {
    if (getStateId() != 0) {
        m_reqChangeBattle = true;
    }
}

void GfComBehaviorEnemy::fn_71004C1D20() {
    if (getStateId() != 0) {
        pad_54e2 = true;
    }
}

void GfComBehaviorEnemy::procAnimCallback(GfComAsm* asmCom, const CallBackCache& cache) {
    MsgObjectNotifyAsmCallback msg(asmCom, cache.m_event);
    GfStateBase::MessageEvent event = {static_cast<GfObj*>(m_owner), &msg};
    m_hfsm.execEvent(&event);
}

void GfComBehaviorEnemy::Listener::onWkStandbyLogout() {
    m_owner->pad_54e8 = nullptr;
}

}  // namespace gf

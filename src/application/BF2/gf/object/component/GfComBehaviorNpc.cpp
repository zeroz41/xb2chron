#include "gf/FileStaticVec3.h"
#include "classes/gf/TFieldExecCmd.h"
#include "classes/gf/TFieldExecCmdTurn.h"
#include "classes/gf/GfFieldLocalSteer.h"
#include "classes/gf/GfComBehaviorNpc.h"
#include "classes/gf/GfComBehaviorNpc.h"
#include "classes/gf/npc/StateIdle.h"
#include "classes/gf/npc/StateWalk.h"
#include "classes/gf/npc/StateAreaMove.h"
#include "classes/gf/npc/StateApproachPc.h"
#include "classes/gf/npc/StateReaction.h"
#include "classes/gf/npc/StateBattle.h"
#include "classes/gf/npc/StateBattle.h"
#include "classes/gf/npc/StateTalk.h"
#include "classes/gf/GfComBehaviorNpc/Listener.h"
#include "classes/gf/GfComBehaviorNpc/LocalSteerIsTargetNotPlayer.h"
#include "classes/gf/GfGameManager.h"
#include "classes/gf/GfComAsm.h"
#include "classes/gf/GfObj.h"
#include "gf/GfObjAcc.h"
#include "gf/GfDataBlade.h"
#include "gf/GfDataBlade.h"
#include "classes/gf/GfDataBdat.h"
#include "classes/gf/SCOM_DESTROY_GAME_OBJ.h"
#include "classes/gmk/AGmkBase.h"
#include "fw/UpdateInfo.h"
#include "classes/gf/GfComTransform.h"
#include "classes/fw/UpdatableObject.h"
#include "classes/fw/ReferenceFrame.h"
#include "plugin/Bdat.h"
#include "gf/MsgGameLipAction.h"
#include "classes/gf/LipSyncPlugin.h"
#include "math.h"
#include "ml/MTRand.h"
#include "classes/fw/NaviManager.h"
#include "classes/navi/NvmshAcObj.h"
#include "classes/gf/GfComCollider.h"
#include "classes/fw/ColiObject.h"
#include "classes/fw/ColiMoveObject.h"
#include "classes/gf/GfComModel.h"
#include "classes/gf/GfMenuObjTargetInfo.h"
#include "classes/gf/GfMenuCallContext.h"
#include "classes/gmk/GmkRoutedNpc.h"
#include "classes/gmk/Lvlb.h"
#include "gf/GfDataNpc.h"
#include "fw/NaviUtil.h"
#include "gf/MsgPcGetLookPoint.h"
#include "gf/MsgPcFieldGetAccessType.h"
#include "gf/MsgPcFieldNotifyAction.h"
#include "gf/MsgGameTalkAction.h"
#include "gf/MsgUnk_1000030.h"
#include "gf/MsgObjectGetVelocity.h"
#include "classes/gf/GfObjManager.h"
#include "classes/gf/GfObjSetupNpc.h"
#include "gf/GfObjInfo.h"
#include "gf/GfMenuBdat.h"
#include "gf/GfGameUtil.h"
#include "gf/MenuOffset.h"
#include "classes/gf/EyeBlinkPlugin.h"
#include "gf/GfObjUtil.h"
#include "classes/ai/State.h"
#include "classes/gmk/GmkNpc.h"
#include "classes/gmk/GmkBlade.h"
#include "classes/gmk/GmkBattleChallengePortal.h"

namespace gf {

float GfComBehaviorNpc::BdatInfo::getDistYThreshold() {
    return 2.0f;
}

bool GfComBehaviorNpc::BdatInfo::isIconTalkBonus() const {
    if (!pad_1a) {
        return false;
    }
    unsigned char* fp = GfDataBdat::getFP(0xeb);
    return !GfDataNpc::isTalkBonusFlag(m_talkEventId + 41878 - Bdat::getIdTop(fp));
}

void GfComBehaviorNpc::BdatInfo::setTalkBonusFlag() const {
    unsigned char* fp = GfDataBdat::getFP(0xeb);
    GfDataNpc::setTalkBonusFlag(m_talkEventId + 41878 - Bdat::getIdTop(fp), 1);
}

bool GfComBehaviorNpc::LocalSteerIsTargetNotPlayer::operator()(const GfFieldLocalSteer& steer,
                                                                GF_OBJ_HANDLE* target) const {
    return GfGameManager::getPartyLeader() != target;
}

gmk::AGmkBase* GfComBehaviorNpc::getBindedGmkInst() const {
    return gmk::getBindedGmkInst(static_cast<GfObj*>(m_owner)->m_handle);
}

bool GfComBehaviorNpc::recieveMessage(fw::MessageObject* from, fw::Message& msg) {
    bool result = false;
    switch (msg.m_id) {
    case 0x1000003:
        result = true;
        break;
    case 0x1000008:
        result = true;
        if (fw::ReferenceFrame* frame = pad_1b8.get()) {
            static_cast<MsgPcGetLookPoint&>(msg).m_point = frame->getWorldTransform().position;
            static_cast<MsgPcGetLookPoint&>(msg).m_found = true;
        }
        break;
    case 0x100000C:
        procMsgPcFieldGetAccessType(from, static_cast<MsgPcFieldGetAccessType&>(msg));
        result = true;
        break;
    case 0x100000D: {
        MsgPcFieldNotifyAction& action = static_cast<MsgPcFieldNotifyAction&>(msg);
        switch (action.m_action) {
        case 0:
            if (!pad_100 && GfGameManager::isTalkOK() &&
                (m_hfsm.m_pState == nullptr || m_hfsm.m_pState->m_stateID != 6)) {
                pad_100 = true;
                m_depopMeter.pad_20 = false;
                if (m_hfsm.m_pState == nullptr || m_hfsm.m_pState->m_stateID != 6) {
                    m_hfsm.setState(6);
                    validateLocalSteer(static_cast<npc::STATE_ID>(6));
                }
            }
            break;
        case 1:
            if (pad_100) {
                pad_100 = false;
                m_depopMeter.pad_20 = true;
            }
            break;
        }
        result = true;
        break;
    }
    case 0x100002E:
        procMsgGameTalkAction(from, static_cast<MsgGameTalkAction&>(msg));
        result = true;
        break;
    case 0x100002F:
        procMsgGameLipAction(from, static_cast<MsgGameLipAction&>(msg));
        result = true;
        break;
    case 0x1000030:
        if (LipSyncPlugin* lipSync = getPlugin<LipSyncPlugin>(2)) {
            lipSync->setWeight(static_cast<MsgUnk_1000030&>(msg).m_weight);
        }
        result = true;
        break;
    case 0x1000049:
        static_cast<MsgObjectGetVelocity&>(msg).m_velocity = pad_f0;
        result = true;
        break;
    }
    return result;
}

void GfComBehaviorNpc::procMsgPcFieldGetAccessType(fw::MessageObject* from, MsgPcFieldGetAccessType& msg) {
    msg.m_type = 2;
    msg.m_enable = false;
    if (pad_100 || !GfGameManager::isTalkOK()) {
        return;
    }
    if (m_hfsm.m_pState != nullptr && m_hfsm.m_pState->m_stateID == 6) {
        return;
    }
    gmk::AGmkBase* gmk = getBindedGmkInst();
    if (gmk == nullptr) {
        return;
    }
    switch (gmk->getGmkType()) {
    case 3:
        msg.m_enable = static_cast<gmk::GmkNpc*>(gmk)->isPopCondMatchedExceptDist();
        break;
    case 4:
        msg.m_enable = static_cast<gmk::GmkRoutedNpc*>(gmk)->isPopCondMatchedExceptDist();
        break;
    case 0x2F:
        msg.m_enable = gmk->isValid()
                           ? static_cast<const gmk::GmkBlade::BdatInfo*>(gmk->m_createInfo.m_bdatInfo)
                                 ->isPopCommonCondMatched()
                           : false;
        break;
    case 0x3D:
        msg.m_enable = static_cast<gmk::GmkBattleChallengePortal*>(gmk)->isPopCondMatchedExceptDist();
        break;
    }
}

// the talk motions MsgGameTalkAction's action picks (the same strings as StateFieldTalk's tables)
static const char* const sTalkStateNames[4] = {"S_talkA_00", "S_talkA_01", "S_talkA_02", "S_idle"};
static const char* const sTalkCmdNames[4] = {"C_talkA_00", nullptr, "C_talkA_02", nullptr};

void GfComBehaviorNpc::procMsgGameTalkAction(fw::MessageObject* from, MsgGameTalkAction& msg) {
    GfComAsm* com = m_owner->getComponent<GfComAsm>(2);
    if (com == nullptr) {
        return;
    }
    if (msg.m_setState) {
        msg.m_result = com->setState(sTalkStateNames[msg.m_action], AnimLayer(0));
        return;
    }
    if (sTalkCmdNames[msg.m_action] != nullptr) {
        msg.m_result = com->execCmd(sTalkCmdNames[msg.m_action], AnimLayer(0));
    }
    if (!msg.m_result) {
        if (com->getStateName(AnimLayer(0)) != nullptr) {
            com->getStateName(AnimLayer(0));
        }
        if (sTalkCmdNames[msg.m_action] != nullptr) {
            msg.m_result = com->setState(sTalkStateNames[msg.m_action], AnimLayer(0));
        }
    }
}

void GfComBehaviorNpc::procMsgGameLipAction(fw::MessageObject* from, MsgGameLipAction& msg) {
    if (msg.m_action == 0) {
        if (LipSyncPlugin* lipSync = getPlugin<LipSyncPlugin>(2)) {
            lipSync->m_forcePlay = true;
        }
    } else if (msg.m_action == 1) {
        if (LipSyncPlugin* lipSync = getPlugin<LipSyncPlugin>(2)) {
            lipSync->m_forcePlay = false;
        }
    }
}

mm::mtl::RTTI GfComBehaviorNpc::m_rtti("GfComBehaviorNpc", &GfComBehavior::m_rtti, nullptr);

GfComBehaviorNpc::GfComBehaviorNpc()
    : pad_b8(nullptr), m_goalPos(mm::Vec3::zero), m_reactionRot(mm::Quat::identity), m_playerDistSq(1e12f),
      m_playerDistYSq(1e12f), pad_f0(mm::Vec3::zero), pad_100(false), pad_101(false),
      m_hfsm(fw::Allocator::getProcAllocator()), m_buildingFsm(true), pad_198(nullptr), m_menuContext(nullptr),
      m_stuckMeter(nullptr), m_depopMeter(nullptr), m_moveSpeed(nullptr),
      m_lookIk(reinterpret_cast<GF_OBJ_HANDLE*>(-1)), m_localSteer(nullptr) {
    fw::NaviManager::sys()->releaseObject(pad_b8);
    pad_b8 = nullptr;
    pad_b8 = fw::NaviManager::sys()->createObject();
    if (pad_b8 != nullptr) {
        pad_b8->setMeshNum(0);
        pad_b8->m_flags |= 2;
    }
}

GfComBehaviorNpc::~GfComBehaviorNpc() {
    cleanup();
    fw::NaviManager::sys()->releaseObject(pad_b8);
    pad_b8 = nullptr;
}

void GfComBehaviorNpc::cleanup() {
    disposeFsm();
    if (m_menuContext != nullptr) {
        GfMenuObjTargetInfo::close(m_menuContext);
        if (m_menuContext != nullptr) {
            m_menuContext->release();
            m_menuContext = nullptr;
        }
    }
    if (pad_1b8.get() != nullptr) {
        if (GfComModel* model = m_owner->getComponent<GfComModel>(1)) {
            if (model->getBoneReferenceFrame("JU_neck").get() != nullptr) {
                model->destroyBoneReferenceFrame("JU_neck");
            } else if (model->getBoneReferenceFrame("JU_spA").get() != nullptr) {
                model->destroyBoneReferenceFrame("JU_spA");
            }
        }
        pad_1b8 = nullptr;
    }
    m_pluginManager.cleanup();
}

gmk::GmkRouteNavi* GfComBehaviorNpc::getGmkRouteNavi() const {
    gmk::AGmkBase* gmk = getBindedGmkInst();
    if (gmk != nullptr && gmk->getGmkType() == 4) {
        return static_cast<gmk::GmkRoutedNpc*>(gmk)->m_navi;
    }
    return nullptr;
}

fw::ColiMoveObject* GfComBehaviorNpc::getColiObject() const {
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

void GfComBehaviorNpc::updateNaviMeshObj(float deltaTime) {
    if (pad_b8 != nullptr && (pad_b8->m_flags & 2)) {
        const mm::Vec3& pos = getPos();
        pad_b8->setBeginPos(pos);
        pad_b8->setEndPos(m_goalPos);
        pad_b8->setMoveSpd(m_bdatInfo.m_moveSpeed * deltaTime);
    }
}

void GfComBehaviorNpc::update(const fw::UpdateInfo& info) {
    if (!pad_100) {
        m_lookIk.update(info.m_deltaTime);
    }
    pad_f0.z = 0.0f;
    pad_f0.x = 0.0f;
    fw::ColiMoveObject* coli = getColiObject();
    if (coli != nullptr && !coli->testAttribute(static_cast<fw::ColiAtrr>(0)) && coli->m_followType != 0) {
        pad_f0.y += info.m_deltaTime * -9.8f;
    } else {
        pad_f0.y = 0.0f;
    }
    if (gmk::isPlayerExist()) {
        GfObjAcc acc(static_cast<GfObj*>(m_owner));
        const mm::Vec3& pos = acc.getWorldTransform().position;
        mm::Vec3 diff = gmk::getPlayerPos() - pos;
        m_playerDistYSq = diff.y * diff.y;
        diff.y = 0.0f;
        m_playerDistSq = diff.dot(diff);
    }
    if (npc::StateBattle<GfComBehaviorNpc>::isCondMatch(*this) &&
        (m_hfsm.m_pState == nullptr || m_hfsm.m_pState->m_stateID != 5)) {
        m_hfsm.setState(5);
        validateLocalSteer(static_cast<npc::STATE_ID>(5));
    }
    if (GfGameManager::isBattle() && m_bdatInfo.m_battleReaction == 1) {
        GfObjAcc acc(static_cast<GfObj*>(m_owner)->m_handle);
        if (!acc.testFlag(0x11)) {
            SCOM_DESTROY_GAME_OBJ::create(static_cast<GfObj*>(m_owner)->m_handle, 1.0f, 0);
        }
    }
    m_hfsm.update(&info);
    if (fw::ColiMoveObject* moving = getColiObject()) {
        moving->setDir(info.m_deltaTime * pad_f0);
    }
    m_stuckMeter.update(info.m_deltaTime);
    m_turnCmd.update(info.m_deltaTime);
    m_pluginManager.update(info);
    if (pad_f0.x != 0.0f && pad_f0.z != 0.0f) {
        GfFieldLocalSteer::UpdateInfo steerInfo;
        steerInfo.pad_0 = m_goalPos;
        steerInfo.pad_10 = info.m_deltaTime;
        m_localSteer.castRay(m_goalPos);
        m_localSteer.update(steerInfo);
    } else {
        m_localSteer.m_angle.m_from = 0.0f;
        m_localSteer.m_angle.m_to = 0.0f;
        m_localSteer.m_angle.m_duration = 0.0f;
        m_localSteer.m_angle.m_time = 0.0f;
    }
    updateNaviMeshObj(info.m_deltaTime);
}

void GfComBehaviorNpc::setup() {
    cleanup();
    m_pluginManager.beginSetup(*this, 4);
    m_pluginManager.setCreator(1, &EyeBlinkPlugin::create, true);
    m_pluginManager.setCreator(2, &LipSyncPlugin::create, true);
    m_pluginManager.endSetup();
    if (Plugin* lipSync = m_pluginManager.m_plugins[2]) {
        lipSync->setActivate(true);
    }
    gmk::AGmkBase* gmk = getBindedGmkInst();
    if (gmk != nullptr && gmk::hasEyeBlink(*gmk)) {
        GfObjUtil::setEnableEyeBlink(static_cast<GfObj*>(m_owner)->m_handle, true);
    }
    init(false);
    createFsm();
    m_moveSpeed.create({static_cast<GfObj*>(m_owner)->m_handle});
    validateBindedGmkInstInfo(false);
    if (fw::ColiMoveObject* coli = getColiObject()) {
        GfGameStuckMeter::CreateInfo stuckInfo;
        stuckInfo.m_minSpeedSq = 0.0f;  // the original stores 0 before setColiObj, then the square below
        stuckInfo.setColiObj(coli);
        stuckInfo.m_minSpeedSq = stuckInfo.pad_0 * stuckInfo.pad_0;
        m_stuckMeter.create(stuckInfo);
    }
    GfGameDepopMeter::CreateInfo depopInfo;
    depopInfo.pad_8 = true;
    depopInfo.m_handle = static_cast<GfObj*>(m_owner)->m_handle;
    m_depopMeter.create(depopInfo);
}

void GfComBehaviorNpc::init(bool moving) {
    if (fw::ColiMoveObject* coli = getColiObject()) {
        coli->setState(static_cast<fw::ColiState>(1));
        if (moving) {
            coli->setColiType(static_cast<fw::ColiType>(1));
            coli->setPriority(200);
            coli->setState(static_cast<fw::ColiState>(0));
        } else {
            coli->setColiType(static_cast<fw::ColiType>(0));
            coli->setPriority(900);
            coli->clearState(static_cast<fw::ColiState>(0));
        }
        if (coli->m_shape.get() != nullptr && coli->m_shape->m_kind == 5) {
            coli->setPriority(900);
        }
    }
    if (pad_b8 != nullptr) {
        if (moving) {
            pad_b8->m_flags |= 2;
        } else {
            pad_b8->m_flags &= ~2;
        }
    }
}

void GfComBehaviorNpc::validateLocalSteer(npc::STATE_ID state) {
    GfFieldLocalSteer::CreateInfo info;
    info.m_handle = static_cast<GfObj*>(m_owner)->m_handle;
    info.pad_18 = state == 3 ? &m_steerFilter : nullptr;
    m_localSteer.create(info);
}

// walks toward m_goalPos as GfComBehaviorMob::moveToGoal does: the speed and navigation object first, the
// velocity's ground part into pad_f0, then a tenth of the way turned into m_reactionRot, which goes to the frame
void GfComBehaviorNpc::moveToGoal(float deltaTime) {
    m_moveSpeed.update(deltaTime);
    updateNaviMeshObj(deltaTime);
    mm::Vec3 dir(0.0f, 0.0f, 0.0f);
    if (!getMoveVec(dir, pad_b8)) {
        const mm::Vec3& pos = getPos();
        dir = m_goalPos - pos;
        dir.y = 0.0f;
    }
    if (!dir.isZero()) {
        float length = dir.length();
        if (length <= 1e-6f) {
            dir = mm::Vec3::zero;
        } else {
            float scale = 1.0f / length;
            dir.x = scale * dir.x;
            dir.y = scale * dir.y;
            dir.z = scale * dir.z;
        }
        GfObjSetup* setup = GfObjManager::getObjInfo(static_cast<GfObj*>(m_owner)->m_handle)->m_setup;
        const GfObjSetupNpc* npc =
            setup->getRTTI()->isKindOf(&GfObjSetupNpc::m_rtti) ? static_cast<GfObjSetupNpc*>(setup) : nullptr;
        float speed = m_moveSpeed.m_speed * 0.2777778f * npc->m_initialScale.x;
        dir.x *= speed;
        dir.y *= speed;
        dir.z *= speed;
    }
    pad_f0.x = dir.x;
    pad_f0.z = dir.z;
    if (m_localSteer.m_info.m_handle != reinterpret_cast<GF_OBJ_HANDLE*>(-1)) {
        m_localSteer.apply(pad_f0, pad_f0);
    }
    float goal = atan2f(pad_f0.x, pad_f0.z);
    fw::Transform& transform = m_owner->getComponent<GfComTransform>(0)->getFrame()->getWorldTransformForWrite();
    mm::Vec3 front = transform.rotation.rotate(mm::Vec3::unitZ);
    float cur = atan2f(front.x, front.z);
    float half = (cur + mm::normalizeRadian(goal - cur) * 0.1f) * 0.5f;
    m_reactionRot.y = sinf(half);
    m_reactionRot.w = cosf(half);
    m_reactionRot.x = 0.0f;
    m_reactionRot.z = 0.0f;
    m_owner->getComponent<GfComTransform>(0)->getFrame()->getWorldTransformForWrite().rotation = m_reactionRot;
}

void GfComBehaviorNpc::createFsm() {
    if (!m_buildingFsm) {
        m_buildingFsm = true;
        m_hfsm.cleanup();
    }
    m_hfsm.beginSetup(this, 7, 1);
    m_hfsm.registerState<npc::StateIdle>(0, -1);
    m_hfsm.registerState<npc::StateWalk>(1, -1);
    m_hfsm.registerState<npc::StateAreaMove<GfComBehaviorNpc> >(2, -1);
    m_hfsm.registerState<npc::StateApproachPc>(3, -1);
    m_hfsm.registerState<npc::StateReaction<GfComBehaviorNpc> >(4, -1);
    m_hfsm.registerState<npc::StateBattle<GfComBehaviorNpc> >(5, -1);
    m_hfsm.registerState<npc::StateTalk>(6, -1);
    m_hfsm.endSetup();
    m_buildingFsm = false;
}

GfComAsm* GfComBehaviorNpc::getComAsm() const {
    return m_owner->getComponent<GfComAsm>(2);
}

void GfComBehaviorNpc::setGoalPos(const mm::Vec3& pos) {
    m_goalPos = pos;
}

const mm::Vec3& GfComBehaviorNpc::getPos() const {
    return m_owner->getComponent<GfComTransform>(0)->getFrame()->getWorldTransform().position;
}

void GfComBehaviorNpc::execTurnCmd(float rotY) {
    float steer = m_localSteer.m_info.m_handle != reinterpret_cast<GF_OBJ_HANDLE*>(-1) ? m_localSteer.getCurAngle() : 0.0f;
    TFieldExecCmdTurn<GfComAsm>::CreateInfo info(static_cast<GfObj*>(m_owner)->m_handle, steer + rotY);
    m_turnCmd.create(info);
}

void GfComBehaviorNpc::execTurnCmd(float rotY, float speed, float threshold, float delay) {
    TFieldExecCmdTurn<GfComAsm>::CreateInfo info;
    info.handle = static_cast<GfObj*>(m_owner)->m_handle;
    float steer = m_localSteer.m_info.m_handle != reinterpret_cast<GF_OBJ_HANDLE*>(-1) ? m_localSteer.getCurAngle() : 0.0f;
    info.pad_8 = steer + rotY;
    info.pad_c = threshold;
    info.pad_14 = speed;
    info.pad_18 = delay;
    m_turnCmd.create(info);
}

void GfComBehaviorNpc::execTurnCmdToPos(const mm::Vec3& pos) {
    const mm::Vec3& cur = getPos();
    float angle = atan2f(pos.x - cur.x, pos.z - cur.z);
    float steer = m_localSteer.m_info.m_handle != reinterpret_cast<GF_OBJ_HANDLE*>(-1) ? m_localSteer.getCurAngle() : 0.0f;
    TFieldExecCmdTurn<GfComAsm>::CreateInfo info(static_cast<GfObj*>(m_owner)->m_handle, angle + steer);
    m_turnCmd.create(info);
}

void GfComBehaviorNpc::execTurnCmdToGoal() {
    mm::Vec3 pos;
    if (getMoveVec(pos, pad_b8)) {
        pos += getPos();
    } else {
        pos = m_goalPos;
    }
    execTurnCmdToPos(pos);
}

bool GfComBehaviorNpc::isArrivedToGoal() const {
    if (m_localSteer.isTimeOutCollide()) {
        return true;
    }
    fw::ColiMoveObject* coli = getColiObject();
    if (coli == nullptr) {
        return false;
    }
    float height;
    float radius;
    const fw::ColiShape* shape = coli->m_shape.get();
    if (shape != nullptr && shape->m_kind == 3) {
        height = static_cast<const fw::ColiShapeCharacter*>(shape)->m_height;
        radius = static_cast<const fw::ColiShapeCharacter*>(shape)->m_radius;
    } else {
        mm::Vec3 min;
        mm::Vec3 max;
        coli->getAABB(min, max);
        float dx = max.x - min.x;
        float dz = max.z - min.z;
        radius = sqrtf(dx * dx + dz * dz) * 0.5f;
        height = max.y - min.y;
    }
    const mm::Vec3& pos = getPos();
    if (height < m_goalPos.y - pos.y) {
        return false;
    }
    mm::Vec3 diff(m_goalPos.x - pos.x, 0.0f, m_goalPos.z - pos.z);
    float distSq = diff.dot(diff);
    return !(radius * radius < distSq);
}

void GfComBehaviorNpc::Listener::onWkStandbyLogout() {
    m_owner->pad_198 = nullptr;
}

namespace npc {

template <typename T>
void StateAreaMove<T>::onEnter(void* p, ai::State*) {
    T& owner = *static_cast<T*>(p);
    gmk::AGmkBase* gmk = owner.getBindedGmkInst();
    if (gmk != nullptr) {
        int type = gmk->getGmkType();
        if ((type == 3 || type == 0x12) && gmk->m_info->m_shape != 1) {
            m_seq = &StateAreaMove::seqInitGoalPos;
            return;
        }
    }
    requestState(0);
}

// a goal inside the bound gimmick's shape, snapped onto the ground and reachable on the navigation mesh within half
// the shape's height (m_pos[2] is the gimmick's scale, see AGmkBase::getYSnapRayLength)
template <typename T>
void StateAreaMove<T>::seqInitGoalPos(T& owner, const fw::UpdateInfo&) {
    gmk::AGmkBase* gmk = owner.getBindedGmkInst();
    if (gmk == nullptr) {
        return;
    }
    mm::Vec3 pos;
    gmk::AGmkBase* shape = owner.getBindedGmkInst();
    if (shape == nullptr) {
        return;
    }
    shape->getPositionInShape(pos, false);
    if (!shape->getPositionAppliedYSnap(pos, pos, true)) {
        return;
    }
    float range = gmk->m_pos[2].y * 0.5f;
    if (fw::NaviUtil::testNaviFindPos(owner.getPos(), range, range, 0.1f, pos, range, range, 0.1f, 0) != 3) {
        return;
    }
    owner.init(true);
    owner.setGoalPos(pos);
    owner.execTurnCmdToPos(pos);
    m_seq = &StateAreaMove::seqWaitTurnEnd;
}

template <typename T>
void StateAreaMove<T>::seqWaitTurnEnd(T& owner, const fw::UpdateInfo&) {
    if (owner.m_turnCmd.pad_6c) {
        m_execCmd.create(TFieldExecCmd<GfComAsm>::CreateInfo(static_cast<GfObj*>(owner.m_owner)->m_handle, "C_move"));
        m_seq = &StateAreaMove::seqMoveToGoal;
    }
}

template <typename T>
void StateAreaMove<T>::seqMoveToGoal(T& owner, const fw::UpdateInfo& info) {
    m_execCmd.update(info.m_deltaTime);
    if (m_execCmd.m_done) {
        if (!canGetMoveVec(owner.pad_b8)) {
            m_seq = &StateAreaMove::seqInitGoalPos;
            return;
        }
        if (owner.isArrivedToGoal()) {
            owner.m_moveSpeed.setSpeedKmph(owner.m_moveSpeed.m_speedMin, 0.5f);
            m_execCmd.create(
                TFieldExecCmd<GfComAsm>::CreateInfo(static_cast<GfObj*>(owner.m_owner)->m_handle, "C_walkend"));
            m_seq = &StateAreaMove::seqWaitMoveEnd;
        }
        owner.moveToGoal(info.m_deltaTime);
    }
}

template <typename T>
void StateAreaMove<T>::seqWaitMoveEnd(T& owner, const fw::UpdateInfo& info) {
    m_execCmd.update(info.m_deltaTime);
    if (m_execCmd.m_done) {
        pad_60 = ml::mtRandf1(3.0f, 5.0f);
        pad_64 = 0.0f;
        owner.init(false);
        m_seq = &StateAreaMove::seqIdle;
    }
}

template <typename T>
void StateAreaMove<T>::seqIdle(T&, const fw::UpdateInfo& info) {
    pad_64 += info.m_deltaTime;
    if (!(pad_64 < pad_60)) {
        m_seq = &StateAreaMove::seqInitGoalPos;
    }
}

template <typename T>
void StateReaction<T>::seqTurnToPc(T& owner, const fw::UpdateInfo&) {
    if (gmk::isPlayerExist()) {
        owner.init(false);
        owner.execTurnCmdToPos(gmk::getPlayerPos());
        m_seq = &StateReaction::seqWaitTurnToPcEnd;
    }
}

template <typename T>
void StateReaction<T>::seqWaitTurnToPcEnd(T& owner, const fw::UpdateInfo&) {
    if (owner.m_turnCmd.pad_6c) {
        beginReaction(owner);
        m_seq = &StateReaction::seqUpdateMove;
    }
}

template <typename T>
void StateReaction<T>::beginReaction(const T& owner) {
    const char* name = reinterpret_cast<const char*>(Bdat::getValCheck(
        Bdat::getFP("FLD_NpcMobMotionId"), "cmdName", owner.m_bdatInfo.m_reactionMot, 7));
    m_execCmd.create(TFieldExecCmd<GfComAsm>::CreateInfo(static_cast<GfObj*>(owner.m_owner)->m_handle, name));
}

template <typename T>
void StateReaction<T>::seqUpdateMove(T& owner, const fw::UpdateInfo&) {
    if (m_execCmd.m_done) {
        if (gmk::isPlayerExist() && owner.m_bdatInfo.m_reactionRangeSq > 0.0f &&
            owner.m_bdatInfo.m_reactionMot != 0 && owner.m_bdatInfo.m_reactionPercent != 0 &&
            !(owner.m_bdatInfo.m_reactionRangeSq < owner.m_playerDistSq) && !(owner.m_playerDistYSq > 4.0f)) {
            return;
        }
        endReaction(owner);
        m_seq = &StateReaction::seqTurnToPrev;
    }
}

// the reaction's closing motion: the row's command name with its last character made '2'
template <typename T>
void StateReaction<T>::endReaction(const T& owner) {
    mm::mtl::FixStr<32> name(reinterpret_cast<const char*>(Bdat::getValCheck(
        Bdat::getFP("FLD_NpcMobMotionId"), "cmdName", owner.m_bdatInfo.m_reactionMot, 7)));
    name.m_str[name.length() - 1] = '2';
    m_execCmd.create(TFieldExecCmd<GfComAsm>::CreateInfo(static_cast<GfObj*>(owner.m_owner)->m_handle, name.m_str));
}

// turns back to the bound gimmick's facing: a point one unit ahead of it along its rotation (m_pos[1] is the
// gimmick's euler rotation, m_pos[0] its position), or toward the origin when it is bound to none
template <typename T>
void StateReaction<T>::seqTurnToPrev(T& owner, const fw::UpdateInfo&) {
    if (m_execCmd.m_done) {
        mm::Vec3 pos = mm::Vec3::zero;
        if (gmk::AGmkBase* gmk = owner.getBindedGmkInst()) {
            mm::Vec3 front = mm::Vec3::unitZ;
            mm::Vec3 rot = gmk->m_pos[1];
            mm::Vec3 half = rot * 0.5f;
            float sx = sinf(half.x);
            float cx = cosf(half.x);
            float sy = sinf(half.y);
            float cy = cosf(half.y);
            float sz = sinf(half.z);
            float cz = cosf(half.z);
            mm::Quat q(sx * cy * cz - cx * sy * sz, cx * sy * cz + sx * cy * sz, cx * cy * sz - sx * sy * cz,
                       cx * cy * cz + sx * sy * sz);
            pos = gmk->m_pos[0] + q.rotate(front);
        }
        owner.execTurnCmdToPos(pos);
        m_seq = &StateReaction::seqWaitTurnToPrevEnd;
    }
}

template <typename T>
void StateReaction<T>::seqWaitTurnToPrevEnd(T& owner, const fw::UpdateInfo&) {
    if (owner.m_turnCmd.pad_6c) {
        requestState(0);
    }
}

template <typename T>
void StateBattle<T>::onEnter(void* p, ai::State*) {
    T& owner = *static_cast<T*>(p);
    owner.init(true);
    unsigned short mot = owner.m_bdatInfo.m_battleMot;
    m_seq = mot != 0 ? &StateBattle::seqApplyBattleMot : &StateBattle::seqTurnPc;
    if (mot != 0 && owner.m_bdatInfo.m_battleReaction != 2) {
        owner.getBindedGmkInst();
    }
    pad_60 = 0;
}

template <typename T>
void StateBattle<T>::seqApplyBattleMot(T& owner, const fw::UpdateInfo&) {
    const char* name = reinterpret_cast<const char*>(Bdat::getValCheck(
        Bdat::getFP("FLD_NpcMobMotionId"), "cmdName", owner.m_bdatInfo.m_battleMot, 7));
    m_execCmd.create(TFieldExecCmd<GfComAsm>::CreateInfo(static_cast<GfObj*>(owner.m_owner)->m_handle, name));
    m_seq = &StateBattle::seqUpdateBattleMot;
}

template <typename T>
void StateBattle<T>::seqTurnPc(T& owner, const fw::UpdateInfo&) {
    if (gmk::isPlayerExist()) {
        mm::Vec3 pos;
        if (findGoalPos(pos, owner)) {
            owner.setGoalPos(pos);
            owner.execTurnCmdToPos(pos);
            m_seq = &StateBattle::seqWaitTurnEnd;
        }
    }
}

template <typename T>
void StateBattle<T>::seqUpdateBattleMot(T&, const fw::UpdateInfo&) {
    if (!GfGameManager::isBattle()) {
        requestState(0);
    }
}

template <typename T>
void StateBattle<T>::seqWaitTurnEnd(T& owner, const fw::UpdateInfo&) {
    if (owner.m_turnCmd.pad_6c) {
        m_execCmd.create(TFieldExecCmd<GfComAsm>::CreateInfo(static_cast<GfObj*>(owner.m_owner)->m_handle, "C_move"));
        m_seq = &StateBattle::seqUpdateMove;
    }
}

template <typename T>
void StateBattle<T>::seqUpdateMove(T& owner, const fw::UpdateInfo& info) {
    if (m_execCmd.m_done) {
        if (m_execCmd.m_executed) {
            owner.m_moveSpeed.setSpeedKmph(owner.m_moveSpeed.m_speedMax, 1.0f);
            owner.init(true);
        }
        if (!GfGameManager::isBattle()) {
            requestState(1);
            owner.m_moveSpeed.setSpeedKmph(owner.m_moveSpeed.m_speedMin, 1.0f);
            return;
        }
        if (owner.m_bdatInfo.m_battleReaction == 0) {
            mm::Vec3 goal;
            if (findGoalPos(goal, owner)) {
                owner.setGoalPos(goal);
            }
            owner.moveToGoal(info.m_deltaTime);
            pad_60 += info.m_deltaTime;
            if (pad_60 > 2.0f) {
                SCOM_DESTROY_GAME_OBJ::create(static_cast<GfObj*>(owner.m_owner)->m_handle, 1.0f, 0);
            }
        }
    }
}
}  // namespace npc
}  // namespace gf

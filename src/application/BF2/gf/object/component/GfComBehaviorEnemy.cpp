#include "gf/FileStaticVec3.h"
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
#include "classes/gf/GfBdatRsc.h"
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
#include "classes/gf/GfFieldLocalSteer/TIsTargetNotSameSquad.h"
#include "classes/gmk/GmkEnemy.h"
#include "classes/navi/NvmshAcObj.h"
#include "gf/GfMenuBdat.h"
#include "gf/GfGameUtil.h"
#include "math.h"
#include "mm/Math.h"
#include "classes/fw/Camera.h"
#include "btl/siren_battle_manager.h"
#include "classes/gmk/GmkSet.h"
#include "classes/gmk/IGmkList.h"
#include "classes/btl/CharacterManager.h"
#include "classes/btl/BattleCharacter.h"
#include "classes/btl/CharacterParameter.h"
#include "gf/GfObjUtil.h"
#include "mm/mtl/Delegate.h"
#include "gf/MsgPcGetLookPoint.h"
#include "gf/MsgObjectDamage.h"
#include "gf/MsgObjectGetVelocity.h"
#include "gf/MsgUnk_100003A.h"
#include "gf/MsgObjectNotifyDead.h"
#include "classes/fw/NaviManager.h"
#include "classes/fw/ParamManager.h"
#include "classes/fw/ParamList.h"
#include "classes/gf/GfComPropertyEnemy.h"
#include "classes/gf/GfGameManager.h"
#include "classes/gf/GfComAsm.h"

namespace gf {

mm::mtl::RTTI GfComBehaviorEnemy::m_rtti("GfComBehaviorEnemy", &GfComBehavior::m_rtti, nullptr);

void GfFieldEnemySensor::createBy_CHR_EnArrange() {
    unsigned char* fp = GfDataBdat::getFP(0x8B);
    int id = pad_54;
    if (pad_60 & 1) {
        int range = Bdat::getValCheckU16(fp, "SearchRange", id);
        if (range != 0) {
            m_rangeSq = range * range;
            float angle = Bdat::getValCheckU16(fp, "SearchAngle", id) * 0.0174532924f;
            m_cosHalfAngle = cosf(angle * 0.5f);
        }
    }
    if (pad_60 & 2) {
        int radius = Bdat::getValCheckU8(fp, "SearchRadius", id);
        if (radius != 0) {
            m_radiusSq = radius * radius;
        }
    }
}

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

void GfBehaviorEnemyField::dispose() {
    m_pitchRoll.dispose();
    m_localSteer.dispose();
    m_moveSpeed.dispose();
    m_sensor.dispose();
    m_squadNavi.dispose();
    fw::NaviManager::sys()->releaseObject(pad_40);
    pad_40 = nullptr;
    m_owner = nullptr;
    m_handle = reinterpret_cast<GF_OBJ_HANDLE*>(-1);
    pad_18 = 1.0f;
    pad_1c = 2.0f;
    pad_20 = 0;
}

namespace {
// an enemy's setup when its object's info holds one of its own kind (5), as gf_game_obj's _gfgob::getEnemySetup
// (inline; the name is not the original's)
inline GfObjSetupEnemy* getEnemySetup(GF_OBJ_HANDLE* handle) {
    GFOBJ_INFO* info = GfObjManager::getObjInfo(handle);
    if (info != nullptr && info->m_setup != nullptr && info->m_setup->m_type == info->m_obj->m_type &&
        info->m_obj->m_type == 5) {
        return mm::mtl::rttiCast<GfObjSetupEnemy>(info->m_setup);
    }
    return nullptr;
}
}  // namespace

void GfBehaviorEnemyField::createSquadNavi() {
    m_squadNavi.dispose();
    gmk::AGmkBase* gmk = gmk::getBindedGmkInst(m_handle);
    if (gmk == nullptr) {
        return;
    }
    gmk::GmkSquadNavi::CreateInfo info;
    switch (gmk->getGmkType()) {
    case gmk::GmkEnemy::TYPE:
        info.m_squad = static_cast<gmk::GmkEnemy*>(gmk)->m_insts.m_squad;
        break;
    case gmk::GmkRoutedEnemy::TYPE:
        info.m_squad = static_cast<gmk::GmkRoutedEnemy*>(gmk)->m_insts.m_squad;
        break;
    default:
        break;
    }
    info.m_handle = m_handle;
    // the setup is looked up but not used
    GfObjSetupEnemy* setup = getEnemySetup(m_handle);
    (void)setup;
    if (info.m_squad != nullptr && info.m_handle != reinterpret_cast<GF_OBJ_HANDLE*>(-1)) {
        m_squadNavi.create(info);
    }
}

void GfBehaviorEnemyField::update(float dt) {
    if (m_owner == nullptr || m_handle == reinterpret_cast<GF_OBJ_HANDLE*>(-1)) {
        return;
    }
    m_velocity.z = 0.0f;
    m_velocity.x = 0.0f;
    fw::ColiMoveObject* coli = getColiObject();
    if (coli != nullptr && !coli->testAttribute(fw::ColiAtrr(0)) && coli->m_followType != 0 && pad_90) {
        m_velocity.y += dt * -9.8f;
    } else {
        m_velocity.y = 0.0f;
    }
    pad_b0 = 0.0f;
    updateNaviMeshObj(dt);
    m_sensor.update(m_handle, *m_owner);
    m_moveSpeed.update(dt);
    GfFieldLocalSteer::UpdateInfo info;
    info.pad_0 = m_goalPos;
    info.pad_10 = dt;
    m_localSteer.update(info);
    if (pad_52a4 < pad_52a0) {
        pad_52a4 += dt;
    }
    GfObjAcc acc(m_handle);
    GfObj* obj = acc.getObj();
    if (obj == nullptr) {
        return;
    }
    const GfComPropertyEnemy* property = obj->getComponent<GfComPropertyEnemy>(5);
    float water = 0.0f;
    bool inWater = property->getWaterHeight(water);
    float chest = property->getChestHeight();
    if (!GfGameManager::isControlFree() || acc.isEnemyBlade()) {
        pad_52a9 = false;
        return;
    }
    DataParamAcc param(m_handle);
    switch (param.getSDataEnemy()->m_actType) {
    case 0:
        pad_52a9 = inWater;
        break;
    case 1:
        pad_52a9 = !inWater;
        if (water < chest) {
            pad_90 = true;
        } else {
            pad_90 = false;
            m_velocity.y = (water - chest) * 0.1f;
        }
        break;
    case 2:
        pad_52a9 = inWater && chest < water;
        break;
    }
}

void GfBehaviorEnemyField::updateNaviMeshObj(float dt) {
    if (pad_40 != nullptr && (pad_40->m_flags & 2) && m_moveSpeed.m_handle != reinterpret_cast<GF_OBJ_HANDLE*>(-1) &&
        !isArrivedToGoal()) {
        const mm::Vec3& pos = m_owner->getTransform().position;
        pad_40->setBeginPos(pos);
        pad_40->setEndPos(m_goalPos);
        float speed = m_moveSpeed.m_speed * 0.2777778f;
        pad_40->setMoveSpd(speed * dt);
        mm::Vec3 dir;
        getMoveDir(dir);
    }
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

void GfBehaviorEnemyField::moveToGoal(float) {
    float speed = m_moveSpeed.m_speed * 0.2777778f;
    GfObjSetup* setup = GfObjManager::getObjInfo(m_handle)->m_setup;
    const GfObjSetupEnemy* enemy =
        setup->getRTTI()->isKindOf(&GfObjSetupEnemy::m_rtti) ? static_cast<GfObjSetupEnemy*>(setup) : nullptr;
    float scale = enemy->m_initialScale.x;
    {
        mm::Vec3 dir;
        getMoveDir(dir);
        m_velocity += dir * speed * scale;
    }
    if (m_localSteer.m_info.m_handle != reinterpret_cast<GF_OBJ_HANDLE*>(-1)) {
        m_localSteer.apply(m_velocity, m_velocity);
    }
    if (getColiObject() != nullptr) {
        float goal = atan2f(m_velocity.x, m_velocity.z);
        GfObjAcc acc(m_handle);
        float cur = 0.0f;
        if (acc.isValidTransform()) {
            mm::Vec3 front = acc.getWorldTransform().rotation.rotate(mm::Vec3::unitZ);
            front.y = 0.0f;
            if (!front.isZero()) {
                float length = front.length();
                if (length <= 1e-6f) {
                    front = mm::Vec3::zero;
                } else {
                    float inv = 1.0f / length;
                    front.x = inv * front.x;
                    front.y = inv * front.y;
                    front.z = inv * front.z;
                }
                cur = atan2f(front.x, front.z);
            }
        }
        float diff = mm::normalizeRadian(goal - cur);
        pad_b0 = diff * 0.1f;
        if (pad_2c < fabsf(diff) && fabsf(diff) <= pad_30) {
            float half = mm::normalizeRadian(cur + diff * 0.1f - goal) * 0.5f;
            mm::Quat rot(0.0f, sinf(half), 0.0f, cosf(half));
            m_velocity = rot.rotate(m_velocity);
        }
    }
}

void GfBehaviorEnemyField::applyLinearVelocityAndRotY(float dt) {
    if (!(dt <= 1e-6f)) {
        if (fw::ColiMoveObject* coli = getColiObject()) {
            if (m_velocity.y < 0.0f) {
                mm::mtl::IntrusivePtr<fw::ParamList> list = fw::ParamManager::sys()->m_paramLists[8];
                if (const FallParam* param = list->getAdapter(0).get<FallParam>()) {
                    float limit = -(param->pad_4 - 0.1f);
                    if (m_velocity.y * dt < limit) {
                        m_velocity.y = limit / dt;
                    }
                }
            }
            coli->setDir(m_velocity * dt);
        }
        GfObjAcc acc(m_handle);
        if (GfObj* obj = acc.getObj()) {
            GfComTransform* transform = obj->getComponent<GfComTransform>(0);
            mm::Quat& q = transform->getFrame()->getWorldTransformForWrite().rotation;
            float half = pad_b0 * 0.5f;
            float s = ::sinf(half);
            float c = ::cosf(half);
            float x = s * q.z + c * q.x;
            float y = s * q.w + c * q.y;
            q.z = c * q.z - s * q.x;
            q.w = c * q.w - s * q.y;
            q.x = x;
            q.y = y;
        }
    }
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

bool GfComBehaviorEnemy::recieveMessage(fw::MessageObject* sender, fw::Message& msg) {
    switch (msg.m_id) {
    case 0x1000003:
        break;
    case 0x1000008:
        if (fw::ReferenceFrame* frame = pad_138.get()) {
            static_cast<MsgPcGetLookPoint&>(msg).m_point = frame->getWorldTransform().position;
            static_cast<MsgPcGetLookPoint&>(msg).m_found = true;
        }
        return true;
    case 0x100003A:
        procMsgObjectNotifyDamage(sender, static_cast<MsgObjectNotifyDamage&>(msg));
        break;
    case 0x100003B:
        procMsgObjectNotifyDead(sender, static_cast<MsgObjectNotifyDead&>(msg));
        break;
    case 0x1000044:
        if (sender != nullptr) {
            pad_54e4 = true;
            MsgObjectDamage damage(1, 0);
            damage.pad_2c[2] = 1;
            sender->sendMessage(static_cast<GfObj*>(m_owner), damage);
        }
        return true;
    case 0x1000049:
        static_cast<MsgObjectGetVelocity&>(msg).m_velocity = pad_54d0;
        break;
    default:
        return false;
    }
    return true;
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

bool GfComBehaviorEnemy::getGmkBattleLockInfo(int& setId, int& lockId) const {
    gmk::AGmkBase* gmk = gmk::getBindedGmkInst(static_cast<GfObj*>(m_owner)->m_handle);
    if (gmk == nullptr) {
        return false;
    }
    setId = static_cast<const gmk::GmkSet*>(gmk->m_list->getCreateInfo().m_param)->m_createInfo.m_bdatId;
    unsigned char* fp = gmk->getBindedBdatFp();
    if (fp == nullptr) {
        return false;
    }
    lockId = Bdat::getValCheckU16(fp, "battlelockname", gmk->m_createInfo.m_bdatId) - 1;
    return true;
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

void GfComBehaviorEnemy::createBehField() {
    m_field.dispose();
    GF_OBJ_HANDLE* handle = static_cast<GfObj*>(m_owner)->m_handle;
    const GfObjSetupEnemy* setup = getEnemySetup(handle);
    GfBehaviorEnemyField::CreateInfo info;
    info.m_owner = this;
    info.m_handle = static_cast<GfObj*>(m_owner)->m_handle;
    {
        const GfComCollider* collider = m_owner->getComponent<GfComCollider>(4);
        mm::Vec3 min;
        mm::Vec3 max;
        float radius;
        float height;
        if (collider->m_coliObjects[0]->getAABB(min, max)) {
            float dx = max.x - min.x;
            float dz = max.z - min.z;
            radius = ::sqrtf(dx * dx + dz * dz) * 0.5f;
            height = max.y - min.y;
        } else {
            radius = mm::mtl::PtrSingleton<GfBdatRsc>::sys()->getRscEnCharColli(setup->m_bdatId);
            height = radius + radius;
        }
        info.m_radius = radius;
        info.m_height = height;
    }
    if (info.m_radius < 1.0f) {
        info.m_radius = 1.0f;
    }
    if (info.m_height < 2.0f) {
        info.m_height = 2.0f;
    }
    {
        DataParamAcc acc(static_cast<GfObj*>(m_owner)->m_handle);
        info.m_actType = acc.getSDataEnemy()->m_actType;
    }
    m_field.create(info);
    m_field.pad_52a0 = setup->pad_ac;
    m_field.pad_52a4 = 0.0f;
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

void GfComBehaviorEnemy::rotProc(float rotY) {
    GfComTransform* transform = static_cast<GfObj*>(m_owner)->getComponent<GfComTransform>(0);
    mm::Quat& q = transform->getFrame()->getWorldTransformForWrite().rotation;
    float half = rotY * 0.5f;
    float s = ::sinf(half);
    float c = ::cosf(half);
    float x = s * q.z + c * q.x;
    float y = s * q.w + c * q.y;
    q.z = c * q.z - s * q.x;
    q.w = c * q.w - s * q.y;
    q.x = x;
    q.y = y;
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

void GfComBehaviorEnemy::updateField(const fw::UpdateInfo& info) {
    m_field.update(info.m_deltaTime);
    GfObjAcc acc(static_cast<GfObj*>(m_owner)->m_handle);
    if (acc.isEnemyBlade()) {
        GF_OBJ_HANDLE* driverHandle = btl::CharacterManager::sys()
                                          ->GetCharacterConst(static_cast<GfObj*>(m_owner)->m_handle)
                                          ->GetCharacterParameterConst(true)
                                          ->m_driverHandle;
        const btl::BattleCharacter* driver = btl::CharacterManager::sys()->GetCharacterConst(driverHandle);
        if (driver != nullptr && driver->IsBattle()) {
            setStateId(static_cast<enemy::STATE_ID>(0));
        }
    }
    if (getStateId() != 13 && m_field.pad_52a9) {
        m_hfsm.setState(13);
    }
}

void GfComBehaviorEnemy::updateInvincible() {
    bool invincible;
    bool target;
    {
        DataParamAcc acc(static_cast<GfObj*>(m_owner)->m_handle);
        if (!acc.isEnbaleTarget()) {
            target = false;
            invincible = true;
        } else {
            switch (getStateId()) {
            case 6:
            case 7:
            case 13:
                target = false;
                invincible = true;
                break;
            default: {
                gmk::AGmkBase* gmk = gmk::getBindedGmkInst(static_cast<GfObj*>(m_owner)->m_handle);
                if (gmk == nullptr) {
                    target = true;
                    invincible = false;
                    break;
                }
                switch (gmk->getGmkType()) {
                case gmk::GmkEnemy::TYPE: {
                    int lockId = m_field.m_sensor.pad_58;
                    int lockIndex = m_field.m_sensor.pad_5c;
                    if (lockId >= 0 && lockIndex >= 0 && !pad_550c) {
                        target = true;
                        invincible = true;
                    } else {
                        invincible = static_cast<gmk::GmkEnemy*>(gmk)->m_insts.m_bdatInfo.isInvincibleCondMatched();
                        target = !invincible;
                    }
                    break;
                }
                case gmk::GmkRoutedEnemy::TYPE:
                    invincible = static_cast<gmk::GmkRoutedEnemy*>(gmk)->m_insts.m_bdatInfo.isInvincibleCondMatched();
                    target = !invincible;
                    break;
                default:
                    target = true;
                    invincible = false;
                    break;
                }
                break;
            }
            }
        }
    }
    GfObj* obj = static_cast<GfObj*>(m_owner);
    if (target) {
        obj->pad_110 |= 4;
    } else {
        obj->pad_110 &= ~4;
    }
    m_field.pad_52a8 = target;
    GfObjUtil::setInvincible(static_cast<GfObj*>(m_owner)->m_handle, invincible, false);
}

void GfComBehaviorEnemy::setStateId(enemy::STATE_ID state) {
    if (state == 0) {
        pad_54e2 = false;
        m_reqChangeBattle = false;
        pad_5508 = 0;
        m_field.m_pitchRoll.pad_30 = true;
        m_field.m_pitchRoll.pad_31 = true;
        GfObjSetupEnemy* setup =
            mm::mtl::rttiCast<GfObjSetupEnemy>(GfObjManager::getObjInfo(static_cast<GfObj*>(m_owner)->m_handle)->m_setup);
        btl::SirenBattleManager* siren = btl::SirenBattleManager::sys();
        if (siren->m_params[0].m_arrangeID != setup->m_enArrangeId &&
            siren->m_params[1].m_arrangeID != setup->m_enArrangeId) {
            static_cast<GfObj*>(m_owner)->pad_110 |= 4;
            GfObjUtil::setInvincible(static_cast<GfObj*>(m_owner)->m_handle, false, false);
        }
        if (m_field.pad_37) {
            reqChangeBattleToOtherMember<gmk::GmkEnemy>();
            reqChangeBattleToOtherMember<gmk::GmkRoutedEnemy>();
        }
    }
    m_hfsm.setState(state);
}

template <typename T>
void GfComBehaviorEnemy::reqChangeBattleToOtherMember() const {
    gmk::AGmkBase* gmk = gmk::getBindedGmkInst(static_cast<GfObj*>(m_owner)->m_handle);
    if (gmk == nullptr || gmk->getGmkType() != T::TYPE) {
        return;
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
        if (obj == nullptr || acc.isBattle()) {
            continue;
        }
        GfComBehaviorEnemy* behavior = obj->getComponent<GfComBehaviorEnemy>(6);
        if (behavior != nullptr && behavior->getStateId() != 13) {
            behavior->reqChangeBattle();
        }
    }
}

template <typename T>
bool GfComBehaviorEnemy::isOtherMemberBattle() const {
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
        if (acc.getObj() != nullptr && acc.isBattle()) {
            return true;
        }
    }
    return false;
}

void GfComBehaviorEnemy::onPopped() {
    createBehField();
    GfObjSetupEnemy* setup = nullptr;
    GFOBJ_INFO* info = GfObjManager::getObjInfo(static_cast<GfObj*>(m_owner)->m_handle);
    if (info != nullptr && info->m_setup != nullptr && info->m_setup->m_type == info->m_obj->m_type &&
        info->m_obj->m_type == 5) {
        setup = mm::mtl::rttiCast<GfObjSetupEnemy>(info->m_setup);
    }
    btl::SirenBattleManager* siren = btl::SirenBattleManager::sys();
    unsigned int arrangeId = setup->m_enArrangeId;
    enemy::STATE_ID state;
    if (siren->m_params[0].m_arrangeID == arrangeId || siren->m_params[1].m_arrangeID == arrangeId) {
        state = static_cast<enemy::STATE_ID>(0);
    } else {
        GfObjAcc acc(static_cast<GfObj*>(m_owner)->m_handle);
        if (acc.isEnemyBlade()) {
            state = static_cast<enemy::STATE_ID>(15);
        } else {
            gmk::AGmkBase* gmk = gmk::getBindedGmkInst(static_cast<GfObj*>(m_owner)->m_handle);
            if (gmk == nullptr) {
                state = static_cast<enemy::STATE_ID>(1);
                if (setup->pad_b2) {
                    pad_54e2 = true;
                }
            } else {
                unsigned char* fp = gmk->getBindedBdatFp();
                unsigned char popType = fp != nullptr ? Bdat::getValCheckU8(fp, "pop_act_type", gmk->m_createInfo.m_bdatId) : 0;
                switch (popType) {
                case 0:
                    state = setup->pad_b1 ? static_cast<enemy::STATE_ID>(0) : getNextFieldStateId();
                    break;
                case 1:
                    state = static_cast<enemy::STATE_ID>(4);
                    break;
                case 2:
                    state = static_cast<enemy::STATE_ID>(5);
                    break;
                case 3:
                case 5:
                    state = static_cast<enemy::STATE_ID>(6);
                    break;
                case 4:
                case 6:
                    state = static_cast<enemy::STATE_ID>(7);
                    break;
                default:
                    state = static_cast<enemy::STATE_ID>(1);
                    break;
                }
                pad_550d = popType == 5 || popType == 6;
                if (m_field.pad_37 &&
                    (isOtherMemberBattle<gmk::GmkEnemy>() || isOtherMemberBattle<gmk::GmkRoutedEnemy>())) {
                    state = static_cast<enemy::STATE_ID>(0);
                }
                switch (popType) {
                case 3:
                case 4:
                case 5:
                case 6:
                    if (setup->pad_b1) {
                        pad_54e2 = true;
                    }
                    break;
                }
            }
        }
    }
    setStateId(state);
}

void GfComBehaviorEnemy::reqChangeBattle() {
    if (getStateId() != 0) {
        m_reqChangeBattle = true;
    }
}

void GfComBehaviorEnemy::reqChangeBattleAfterIdle() {
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
// turns the object by at most the turn's step this frame toward m_info.pad_8 (about the y axis)
template <typename T>
void TFieldExecCmdTurn<T>::applyDeltaRotY(GfComTransform& transform, float dt) {
    float step = m_info.pad_14 * (pad_58 / pad_64 * dt);
    mm::Vec3 front = transform.getRotation().rotate(mm::Vec3::unitZ);
    float cur = atan2f(front.x, front.z);
    float diff = mm::normalizeRadian(m_info.pad_8 - cur);
    float delta = fabsf(diff) < fabsf(step) ? diff : step;
    mm::Quat rot = transform.getRotation();
    float half = delta * 0.5f;
    float s = sinf(half);
    float c = cosf(half);
    float x = s * rot.z + c * rot.x;
    float y = s * rot.w + c * rot.y;
    rot.z = c * rot.z - s * rot.x;
    rot.w = c * rot.w - s * rot.y;
    rot.x = x;
    rot.y = y;
    transform.setRotation(rot);
}

// TFieldExecCmdTurn<GfComAsm>::update's (not written yet)
template void TFieldExecCmdTurn<GfComAsm>::applyDeltaRotY(GfComTransform& transform, float dt);

}  // namespace gf

// the steer filter's operator (its table is GfBehaviorEnemyField's, which GfComBehaviorEnemy's constructor installs)
template bool gf::GfFieldLocalSteer::TIsTargetNotSameSquad<gf::GfComBehaviorEnemy>::operator()(
    const gf::GfFieldLocalSteer&, gf::GF_OBJ_HANDLE*) const;

template void mm::mtl::Delegate<void(gf::GfComAsm*, const gf::CallBackCache&)>::memberFuncInvoker<gf::GfComBehavior>(const mm::mtl::Delegate<void(gf::GfComAsm*, const gf::CallBackCache&)>*, gf::GfComAsm*, const gf::CallBackCache&);

template void mm::mtl::Delegate<void(gf::GfComAsm*, const gf::CallBackCache&)>::memberFuncInvoker<gf::GfComBehaviorEnemy>(const mm::mtl::Delegate<void(gf::GfComAsm*, const gf::CallBackCache&)>*, gf::GfComAsm*, const gf::CallBackCache&);

namespace gf {

}  // namespace gf

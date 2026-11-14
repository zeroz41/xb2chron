#include "classes/fw/AnimVolumeFadeModifier.h"
#include "classes/anm/Skeleton.h"
#include "classes/fw/AnimPoseModifier.h"
#include "classes/gf/GfComModel.h"
#include "mm/mtl/IntrusivePtr.h"
#include "classes/fw/ReferenceFrame.h"
#include "classes/gf/GfComModel.h"
#include "classes/gf/GfComBehaviorMob.h"
#include "classes/gf/mob/StateApproachPc.h"
#include "classes/gf/mob/StateIdle.h"
#include "classes/gf/mob/StateMove.h"
#include "classes/gf/mob/StateSquadMember.h"
#include "classes/fw/AnimPoseModifier.h"
#include "classes/fw/AnimVolumeFadeModifier.h"
#include "classes/gf/GfComModel.h"
#include "classes/gf/GfComModel/ViewerListener.h"
#include "classes/gf/GfComBehaviorMob.h"
#include "classes/gf/mob/StateApproachPc.h"
#include "classes/gf/mob/StateIdle.h"
#include "classes/gf/mob/StateMove.h"
#include "classes/gf/mob/StateSquadMember.h"
#include "gf/GfExecSchedule.h"
#include "classes/gf/GfObj.h"
#include "classes/gmk/AGmkBase.h"
#include "classes/fw/ModelObject.h"
#include "gf/GfObjUtil.h"
#include "fw/Message.h"
#include "fw/UpdateInfo.h"
#include "math.h"
#include "classes/gf/GfComTransform.h"
#include "classes/gf/GfAllocator.h"
#include "classes/anm/Skeleton.h"
#include "classes/anm/Pose.h"
#include "classes/anm/ExtraTruckBuffer.h"
#include "mm/mtl/Delegate.h"
#include "classes/gf/GfObjManager.h"
#include "classes/gf/GfObjSetupMob.h"
#include "classes/gf/GfComAsm.h"
#include "gf/GfObjInfo.h"
#include "gf/GfObjAcc.h"
#include "mm/mtl/RTTI.h"
#include "mm/mtl/FixStr.h"
#include "anm/TransformUtil.h"
#include "classes/gf/GfAssetManager.h"
#include "classes/gf/GfAssetResource.h"
#include "classes/gf/GfManager.h"
#include "gf/GfSetupParam.h"
#include "anm/Factory.h"
#include "ml/ScnObjAccEtcParams.h"
#include "classes/fw/AnimationManager.h"
#include <string.h>

namespace gf {
namespace {
// a mob's setup when its info holds one of its own kind (7), as gf_game_obj.cpp's enemy setup (inline, the name is
// not the original's)
inline GfObjSetupMob* getMobSetup(GF_OBJ_HANDLE* handle) {
    GFOBJ_INFO* info = GfObjManager::getObjInfo(handle);
    if (info != nullptr && info->m_setup != nullptr && info->m_setup->m_type == info->m_obj->m_type &&
        info->m_obj->m_type == 7) {
        return mm::mtl::rttiCast<GfObjSetupMob>(info->m_setup);
    }
    return nullptr;
}
}  // namespace

namespace mob {

void StateApproachPc::enter(GfComBehaviorMob* owner, ai::State*) {
    owner->pad_53d9 = true;
    m_seq = &StateApproachPc::seqTurnPc;
}

void StateApproachPc::seqTurnPc(GfComBehaviorMob& owner, const fw::UpdateInfo&) {
    if (gmk::isPlayerExist()) {
        owner.execTurnCmdToPos(gmk::getPlayerPos());
        m_seq = &StateApproachPc::seqWaitTurnEnd;
    }
}

void StateApproachPc::seqWaitTurnEnd(GfComBehaviorMob& owner, const fw::UpdateInfo&) {
    if (owner.m_turnCmd.pad_6c) {
        m_execCmd.create(TFieldExecCmd<GfComAsm>::CreateInfo(static_cast<GfObj*>(owner.m_owner)->m_handle, "C_move"));
        m_seq = &StateApproachPc::seqApproachPc;
    }
}

void StateApproachPc::leave(GfComBehaviorMob*, ai::State*) { m_seq = nullptr; }

void StateApproachPc::update(GfComBehaviorMob* owner, const fw::UpdateInfo& info) {
    m_execCmd.update(info.m_deltaTime);
    if (m_seq) {
        (this->*m_seq)(*owner, info);
    }
}

void StateApproachPc::seqApproachPc(GfComBehaviorMob& owner, const fw::UpdateInfo& info) {
    if (!m_execCmd.m_done) {
        return;
    }
    if (m_execCmd.m_executed) {
        owner.init(true);
    }
    if (!gmk::isPlayerExist()) {
        return;
    }
    gmk::AGmkBase* gmk = owner.getBindedGmkInst();
    if (gmk == nullptr) {
        return;
    }
    owner.setGoalPos(gmk::getPlayerPos());
    if (!isCondMatch(owner)) {
        owner.pad_53d9 = false;
        requestState(1);
        return;
    }
    bool far;
    {
        GfObjAcc acc(static_cast<GfObj*>(owner.m_owner));
        const mm::Vec3& pos = acc.getWorldTransform().position;
        const mm::Vec3& playerPos = gmk::getPlayerPos();
        mm::Vec3 toPlayer = playerPos - pos;
        toPlayer.y = 0.0f;
        far = !(playerPos.y - pos.y < 1.0f && toPlayer.dot(toPlayer) < 1.0f);
    }
    if (far) {
        GfObjAcc acc(static_cast<GfObj*>(owner.m_owner));
        const mm::Vec3& mobPos = acc.getWorldTransform().position;
        mm::Vec3 gmkPos = *gmk->m_pos;
        mm::Vec3 toGmk = mobPos - gmkPos;
        float dy = toGmk.y;
        toGmk.y = 0.0f;
        float distSq = toGmk.dot(toGmk);
        if (!(2.0f < dy) && !(owner.m_bdatInfo.m_approachDistSq < distSq)) {
            owner.moveToGoal(info.m_deltaTime);
            return;
        }
    }
    TFieldExecCmd<GfComAsm>::CreateInfo idle;
    idle.handle = static_cast<GfObj*>(owner.m_owner)->m_handle;
    idle.cmdName = "C_idle";
    idle.timeout = 5.0f;
    m_execCmd.create(idle);
    m_seq = &StateApproachPc::seqApproachPcIdle;
}

bool StateApproachPc::isCondMatch(const GfComBehaviorMob& owner) {
    bool result = false;
    if (gmk::isPlayerExist() && owner.m_bdatInfo.m_approachDistSq > 0.0f && !(owner.pad_53d4 > 4.0f) &&
        !(owner.m_bdatInfo.m_approachDistSq < owner.pad_53d0)) {
        result = true;
    }
    return result;
}

void StateApproachPc::seqApproachPcIdle(GfComBehaviorMob& owner, const fw::UpdateInfo&) {
    if (m_execCmd.m_executed) {
        owner.init(false);
    }
    if (!isCondMatch(owner)) {
        owner.pad_53d9 = false;
        requestState(1);
    }
}

void StateIdle::enter(GfComBehaviorMob* owner, ai::State* prev) {
    if (prev != nullptr) {
        execEndSchedule(*owner);
    }
    GfComAsm* com = owner->m_owner->getComponent<GfComAsm>(2);
    const char* state = com != nullptr ? com->getStateName(AnimLayer(0)) : nullptr;
    const char* idle = getMobSetup(static_cast<GfObj*>(owner->m_owner)->m_handle)->m_stateName.m_str;
    if (state == nullptr || strcmp(idle, state) != 0) {
        mm::mtl::FixStr<32> cmd(idle);
        cmd[0] = 'C';
        m_execCmd.create(TFieldExecCmd<GfComAsm>::CreateInfo(static_cast<GfObj*>(owner->m_owner)->m_handle, cmd.m_str));
    }
    owner->pad_53d9 = true;
}

void StateIdle::leave(GfComBehaviorMob* owner, ai::State*) { execEndSchedule(*owner); }

void StateSquadMember::enter(GfComBehaviorMob* owner, ai::State*) {
    m_execCmd.create(TFieldExecCmd<GfComAsm>::CreateInfo(static_cast<GfObj*>(owner->m_owner)->m_handle, "C_move"));
    m_seq = &StateSquadMember::seqUpdateMove;
    owner->init(true);
}

void StateSquadMember::seqUpdateIdle(GfComBehaviorMob& owner, const fw::UpdateInfo&) {
    const mm::Vec3& pos = owner.getPos();
    float dx = owner.pad_110.x - pos.x;
    float dz = owner.pad_110.z - pos.z;
    float dist = sqrtf(dx * dx + dz * dz);
    if (pad_18 <= dist) {
        m_execCmd.create(TFieldExecCmd<GfComAsm>::CreateInfo(static_cast<GfObj*>(owner.m_owner)->m_handle, "C_move"));
        m_seq = &StateSquadMember::seqUpdateMove;
        owner.init(true);
    }
}

void StateSquadMember::seqUpdateMove(GfComBehaviorMob& owner, const fw::UpdateInfo& info) {
    if (m_execCmd.m_info.handle != reinterpret_cast<GF_OBJ_HANDLE*>(-1) && m_execCmd.m_info.cmdName.length() != 0 &&
        !m_execCmd.m_done) {
        return;
    }
    const mm::Vec3& pos = owner.getPos();
    float dx = owner.pad_110.x - pos.x;
    float dz = owner.pad_110.z - pos.z;
    float dist = sqrtf(dx * dx + dz * dz);
    GfFieldMoveSpeed& speed = owner.m_moveSpeed;
    float rate;
    if (dist < pad_18) {
        if (!pad_68) {
            m_execCmd.create(TFieldExecCmd<GfComAsm>::CreateInfo(static_cast<GfObj*>(owner.m_owner)->m_handle, "C_idle"));
            m_seq = &StateSquadMember::seqUpdateIdle;
            owner.initMoveSpeed(0.5f);
            owner.init(false);
            return;
        }
        rate = (dist - 0.1f) / pad_18;
        rate = rate < 0.0f ? 0.0f : rate;
    } else if (dist < 1.0f) {
        float t = (dist - pad_18) / (1.0f - pad_18);
        float max = speed.m_speedMin < 1e-6f ? 0.0f : speed.m_speedMax / speed.m_speedMin;
        rate = 1.0f + (max - 1.0f) * t;
    } else {
        rate = speed.m_speedMin < 1e-6f ? 0.0f : speed.m_speedMax / speed.m_speedMin;
    }
    speed.setSpeedKmph(rate * speed.m_speedMin, 0.5f);
    owner.moveToGoal(info.m_deltaTime);
}

void StateSquadMember::leave(GfComBehaviorMob*, ai::State*) {}

void StateSquadMember::update(GfComBehaviorMob* owner, const fw::UpdateInfo& info) {
    if (!(owner->m_squadNavi.isInSquad() && owner->m_squadNavi.m_index != 0)) {
        requestState(0);
        owner->initMoveSpeed(0.5f);
        return;
    }
    mm::Vec3 pos;
    float rotY;
    if (owner->m_squadNavi.getPosRotY(pos, rotY)) {
        mm::Vec3 prev = owner->pad_110;
        owner->setGoalPos(pos);
        float dx = pos.x - prev.x;
        float dz = pos.z - prev.z;
        pad_68 = dx * dx + dz * dz > 0.0001f;
        m_execCmd.update(info.m_deltaTime);
        if (m_seq) {
            (this->*m_seq)(*owner, info);
        }
    }
}

bool StateSquadMember::isCondMatch(const GfComBehaviorMob& owner) { return owner.isSquadMember(); }

void StateMove::enter(GfComBehaviorMob* owner, ai::State*) {
    execEndSchedule(*owner);
    owner->init(true);
    m_execCmd.create(TFieldExecCmd<GfComAsm>::CreateInfo(static_cast<GfObj*>(owner->m_owner)->m_handle, "C_move"));
    m_seq = &StateMove::seqUpdateMove;
}

void StateMove::seqWaitMoveEnd(GfComBehaviorMob& owner, const fw::UpdateInfo& info) {
    m_execCmd.update(info.m_deltaTime);
    if (m_execCmd.m_done) {
        if (gmk::AGmkBase* gmk = owner.getBindedGmkInst()) {
            mm::Vec3 half = gmk->m_pos[1];
            half = half * 0.5f;
            float sx = sinf(half.x);
            float cx = cosf(half.x);
            float sy = sinf(half.y);
            float cy = cosf(half.y);
            float sz = sinf(half.z);
            float cz = cosf(half.z);
            mm::Quat rot;
            rot.x = sx * cy * cz - cx * sy * sz;
            rot.y = cx * sy * cz + sx * cy * sz;
            rot.z = cx * cy * sz - sx * sy * cz;
            rot.w = cx * cy * cz + sx * sy * sz;
            mm::Vec3 front = rot.rotate(mm::Vec3::unitZ);
            owner.execTurnCmd(atan2f(front.x, front.z));
            m_seq = &StateMove::seqInterpPosRotToGoal;
            pad_60 = 0.0f;
        }
    }
}

void StateMove::seqWaitTurnEnd(GfComBehaviorMob& owner, const fw::UpdateInfo&) {
    if (owner.m_turnCmd.pad_6c) {
        owner.init(true);
        m_execCmd.create(TFieldExecCmd<GfComAsm>::CreateInfo(static_cast<GfObj*>(owner.m_owner)->m_handle, "C_move"));
        m_seq = &StateMove::seqUpdateMove;
    }
}

void StateMove::leave(GfComBehaviorMob*, ai::State*) {}

void StateMove::update(GfComBehaviorMob* owner, const fw::UpdateInfo& info) {
    if (owner->m_squadNavi.isInSquad() && owner->m_squadNavi.m_index != 0) {
        requestState(3);
        return;
    }
    if (m_seq) {
        (this->*m_seq)(*owner, info);
    }
}

void StateMove::seqInterpPosRotToGoal(GfComBehaviorMob& owner, const fw::UpdateInfo& info) {
    if (owner.m_turnCmd.pad_6c && owner.getBindedGmkInst() != nullptr) {
        fw::Transform& transform = owner.m_owner->getComponent<GfComTransform>(0)->getFrame()->getWorldTransformForWrite();
        transform.position += (owner.pad_110 - transform.position) * (info.m_deltaTime / 0.5f);
        pad_60 += info.m_deltaTime;
        if (pad_60 >= 0.5f) {
            transform.position = owner.pad_110;
            requestState(0);
        }
    }
}

bool StateMove::isCondMatch(const GfComBehaviorMob& owner) { return owner.pad_b8 != nullptr; }

}  // namespace mob

GfComModel::~GfComModel() {}

void GfComModel::setup(const SetupInfo& info) {
    if (info.m_handle == reinterpret_cast<GF_ASSET_HANDLE*>(-1)) {
        return;
    }
    pad_10 = info.m_handle;
    m_scale = info.m_scale;
    fw::ModelObject::ModelSetup modelSetup;
    if (GfAssetResource* resource = GfAssetManager::getResource(pad_10, info.m_file, static_cast<GfAssetType>(0))) {
        modelSetup.name = resource->getAssetName();
        modelSetup.resource = resource->getAssetData();
        modelSetup.scn = GfManager::getSetupParam().m_scn;
        modelSetup.layer = getLayer();
        modelSetup.arg = info.m_arg;
        modelSetup.keepScale = info.m_keepScale;
        modelSetup.scale = info.m_scale;
        m_model = fw::ModelObject::create(getAllocator(ALLOCATOR(0)), modelSetup);
        if (GfComTransform* transform = m_owner->getComponent<GfComTransform>(0)) {
            m_frame = transform->getFrame();
            m_model->m_frame = m_frame;
        }
        if (info.pad_20) {
            ml::ScnObjAccEtcParams params(m_model->getInterface());
            params.setRimBloom(false);
        }
    }
    if (m_model != nullptr && info.m_skeleton != nullptr) {
        m_skeleton = info.m_skeleton;
        m_skeleton->addRef();
        m_pose = anm::Factory::createPose(m_skeleton, getAllocator(ALLOCATOR(0)));
        m_pose->setReferencePose();
        anm::Pose* pose = m_pose;
        pose->syncLocalSpace();
        pose->syncModelSpace();
        m_extraTruckBuffer = anm::Factory::createExtraTruckBuffer(m_skeleton, "EX_extraControl", getAllocator(ALLOCATOR(0)));
        m_poseModifier.bind(m_pose, m_model, m_extraTruckBuffer, getAllocator(ALLOCATOR(0)));
        mm::mtl::PtrSingleton<fw::AnimationManager>::sys()->addPoseModifier(getLayer(), m_poseModifier);
        if (!info.pad_20) {
            m_volumeFade.bind(m_model);
            m_volumeFade.m_condition.set(this, &GfComModel::isVolumeFadeForUser);
            mm::mtl::PtrSingleton<fw::AnimationManager>::sys()->addAfterModifier(getLayer(), m_volumeFade);
        }
    }
    if (info.m_boneFrameCount != 0) {
        m_boneFrames.setAllocator(getAllocator(ALLOCATOR(0)));
        m_boneFrames.reserve(info.m_boneFrameCount);
        pad_1168.setAllocator(getAllocator(ALLOCATOR(0)));
        pad_1168.reserve(info.m_boneFrameCount);
    }
}

void GfComModel::cleanup() {
    if (m_boneFrames.capacity() != 0) {
        for (unsigned int i = 0; i < m_boneFrames.size(); i++) {
            BoneFrameInfo& info = m_boneFrames[i];
            m_poseModifier.unbindReferenceFrame(info.frame);
            if (GfComTransform* transform = m_owner->getComponent<GfComTransform>(0)) {
                transform->getFrame().get()->removeChild(*info.frame.get());
            }
            fw::ReferenceFrame* frame = m_boneFrames[i].frame.get();
            fw::ReferenceFrame::unlinkParent(*frame);
            fw::ReferenceFrame::unlinkChild(*frame);
        }
        m_boneFrames.destroy();
    }
    if (m_poseModifier.isBound()) {
        m_poseModifier.unbind();
        mm::mtl::PtrSingleton<fw::AnimationManager>::sys()->removePoseModifier(getLayer(), m_poseModifier);
    }
    if (m_volumeFade.m_model != nullptr) {
        m_volumeFade.m_condition.m_invoker = nullptr;
        m_volumeFade.unbind();
        mm::mtl::PtrSingleton<fw::AnimationManager>::sys()->removeAfterModifier(getLayer(), m_volumeFade);
    }
    if (m_extraTruckBuffer != nullptr) {
        m_extraTruckBuffer->release();
        m_extraTruckBuffer = nullptr;
    }
    if (m_pose != nullptr) {
        m_pose->release();
        m_pose = nullptr;
    }
    if (m_skeleton != nullptr) {
        m_skeleton->release();
        m_skeleton = nullptr;
    }
    m_frame = nullptr;
    if (m_model != nullptr) {
        m_model->release();
        m_model = nullptr;
    }
    pad_10 = reinterpret_cast<GF_ASSET_HANDLE*>(-1);
}

bool GfComModel::recieveMessage(fw::MessageObject*, fw::Message& msg) {
    switch (msg.m_id) {
    case 0x01000003:
    case 0x0100003A:
    case 0x0100003B:
        return true;
    }
    return false;
}

GfComModel::GfComModel()
    : pad_10(reinterpret_cast<GF_ASSET_HANDLE*>(-1)), m_model(nullptr), m_skeleton(nullptr), m_pose(nullptr), m_extraTruckBuffer(nullptr), m_scale(1.0f),
      m_pViewer(nullptr) {
    m_viewerListener.m_pOwner = this;
}

bool GfComModel::isVolumeFadeForUser() const { return GfObjUtil::isVolumeFadeForUser(static_cast<GfObj*>(m_owner)->m_handle); }

bool GfComModel::isRender() const {
    if (m_model != nullptr) {
        return m_model->isRender();
    }
    return false;
}

void GfComModel::setModelScale(float scale) {
    m_scale = scale;
    if (m_model != nullptr) {
        m_model->setScale(scale);
    }
}

void GfComModel::ViewerListener::onWkStandbyLogout() {
    if (m_pOwner != nullptr) {
        m_pOwner->m_pViewer = nullptr;
    }
}
}  // namespace gf

template bool mm::mtl::Delegate<bool()>::memberFuncInvoker<gf::GfComModel>(const mm::mtl::Delegate<bool()>*);

namespace gf {

namespace {
// the index of the skeleton's mount named name, 0xFFFF when none is (the name is not the original's)
inline unsigned short getMountIndex(const anm::Skeleton* skeleton, const char* name) {
    for (unsigned int i = 0; i < skeleton->m_mountNames.size(); i++) {
        if (strcmp(name, skeleton->m_mountNames[i]) == 0) {
            return i;
        }
    }
    return 0xFFFF;
}

// the first of model's bone frames made on bone, the end when none is (the name is not the original's)
inline GfComModel::BoneFrameInfo* findBoneFrame(GfComModel& model, unsigned short bone) {
    GfComModel::BoneFrameInfo* it = model.m_boneFrames.begin();
    GfComModel::BoneFrameInfo* end = model.m_boneFrames.end();
    for (; it != end; ++it) {
        if (it->bone == bone) {
            break;
        }
    }
    return it;
}

// the first of model's mount frames made on mount, the end when none is (the name is not the original's)
inline GfComModel::BoneFrameInfo* findMountFrame(GfComModel& model, unsigned short mount) {
    GfComModel::BoneFrameInfo* it = model.pad_1168.begin();
    GfComModel::BoneFrameInfo* end = model.pad_1168.end();
    for (; it != end; ++it) {
        if (it->bone == mount) {
            break;
        }
    }
    return it;
}
// the frame its object's transform places it by (the name is not the original's)
inline fw::ReferenceFrame* getTransformFrame(GfComModel& model) {
    GfComTransform* com_trans = model.m_owner->getComponent<GfComTransform>(0);
#line 618
    MM_ASSERT(com_trans != NULL);
    return com_trans->getFrame().get();
}
}  // namespace

mm::mtl::IntrusivePtr<fw::ReferenceFrame> GfComModel::createBoneReferenceFrame(const char* bone) {
    mm::mtl::IntrusivePtr<fw::ReferenceFrame> frame;
    if (m_skeleton == nullptr) {
        return frame;
    }
    unsigned short index = 0xFFFF;
    if (bone != nullptr) {
        index = m_skeleton->getBoneIndex(bone);
    }
    if (index != 0xFFFF) {
        BoneFrameInfo* it = findBoneFrame(*this, index);
        if (it != m_boneFrames.end()) {
            it->count++;
            frame = it->frame;
        } else {
            frame = createBoneReferenceFrameImpl(index);
            BoneFrameInfo info;
            info.bone = index;
            info.frame = frame;
            info.count = 1;
            m_boneFrames.push_back(info);
        }
        return frame;
    }
    const anm::Skeleton* skeleton = m_skeleton;
    index = getMountIndex(skeleton, bone);
    if (index == 0xFFFF) {
        return frame;
    }
    unsigned short parent = skeleton->m_mountBones[index];
    mm::mtl::IntrusivePtr<fw::ReferenceFrame> parentFrame;
    if (parent != 0xFFFF) {
        BoneFrameInfo* it = findBoneFrame(*this, parent);
        if (it != m_boneFrames.end()) {
            it->count++;
            parentFrame = it->frame;
        } else {
            parentFrame = createBoneReferenceFrameImpl(parent);
            BoneFrameInfo info;
            info.bone = parent;
            info.frame = parentFrame;
            info.count = 1;
            m_boneFrames.push_back(info);
        }
    }
    BoneFrameInfo* it = findMountFrame(*this, index);
    if (it != pad_1168.end()) {
        it->count++;
        frame = it->frame;
    } else {
        frame = createMountReferenceFrameImpl(index);
        BoneFrameInfo info;
        info.bone = index;
        info.frame = frame;
        info.count = 1;
        pad_1168.push_back(info);
    }
    if (parentFrame) {
        parentFrame->addChild(*frame);
    }
    return frame;
}

mm::mtl::IntrusivePtr<fw::ReferenceFrame> GfComModel::createBoneReferenceFrameImpl(unsigned short index) {
#line 544
    mm::mtl::IntrusivePtr<fw::ReferenceFrame> frame(new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) fw::ReferenceFrame);
    m_poseModifier.bindReferenceFrameToBone(index, frame);
    getTransformFrame(*this)->addChild(*frame.get());
    GfComTransform* com_trans = m_owner->getComponent<GfComTransform>(0);
#line 549
    MM_ASSERT(com_trans != NULL);
    com_trans->addReferenceFrame(frame);
    return frame;
}

mm::mtl::IntrusivePtr<fw::ReferenceFrame> GfComModel::createMountReferenceFrameImpl(unsigned short index) {
#line 580
    mm::mtl::IntrusivePtr<fw::ReferenceFrame> frame(new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) fw::ReferenceFrame);
    GfComTransform* com_trans = m_owner->getComponent<GfComTransform>(0);
#line 583
    MM_ASSERT(com_trans != NULL);
    com_trans->addAfterReferenceFrame(frame);
    const anm::Skeleton* skeleton = m_skeleton;
    if (skeleton != nullptr) {
        fw::Transform& local = frame->getLocalTransformForWrite();
        const anm::QsTransform& mount = skeleton->m_mountTransforms[index];
        local.position = mm::Vec3(mount.m_translation.x, mount.m_translation.y, mount.m_translation.z);
        local.rotation = mount.m_rotation;
    }
    return frame;
}

mm::mtl::IntrusivePtr<fw::ReferenceFrame> GfComModel::getBoneReferenceFrame(const char* bone) {
    if (m_skeleton == nullptr) {
        return nullptr;
    }
    unsigned short index = 0xFFFF;
    if (bone != nullptr) {
        index = m_skeleton->getBoneIndex(bone);
    }
    if (index != 0xFFFF) {
        BoneFrameInfo* it = findBoneFrame(*this, index);
        if (it == m_boneFrames.end()) {
            return nullptr;
        }
        return it->frame;
    }
    index = getMountIndex(m_skeleton, bone);
    if (index != 0xFFFF) {
        BoneFrameInfo* it = findMountFrame(*this, index);
        if (it == pad_1168.end()) {
            return nullptr;
        }
        return it->frame;
    }
    return nullptr;
}

bool GfComModel::addBoneReferenceFrame(const char* bone, mm::mtl::IntrusivePtr<fw::ReferenceFrame>& frame) {
    mm::mtl::IntrusivePtr<fw::ReferenceFrame> boneFrame = createBoneReferenceFrame(bone);
    if (boneFrame) {
        boneFrame->addChild(*frame.get());
        return true;
    }
    return false;
}

void GfComModel::removeBoneReferenceFrame(const char* bone, mm::mtl::IntrusivePtr<fw::ReferenceFrame>& frame) {
    mm::mtl::IntrusivePtr<fw::ReferenceFrame> boneFrame = getBoneReferenceFrame(bone);
    if (boneFrame) {
        boneFrame->removeChild(*frame);
        destroyBoneReferenceFrame(bone);
    }
}

void GfComModel::destroyBoneReferenceFrameImpl(mm::mtl::IntrusivePtr<fw::ReferenceFrame> frame) {
    GfComTransform* com_trans = m_owner->getComponent<GfComTransform>(0);
#line 564
    MM_ASSERT(com_trans != NULL);
    com_trans->removeReferenceFrame(frame);
    m_poseModifier.unbindReferenceFrame(frame);
    if (GfComTransform* transform = m_owner->getComponent<GfComTransform>(0)) {
        transform->getFrame().get()->removeChild(*frame.get());
    }
}

void GfComModel::destroyMountReferenceFrameImpl(mm::mtl::IntrusivePtr<fw::ReferenceFrame> frame) {
    GfComTransform* com_trans = m_owner->getComponent<GfComTransform>(0);
#line 604
    MM_ASSERT(com_trans != NULL);
    com_trans->removeAfterReferenceFrame(frame);
}

bool GfComModel::clacBoneRotateMS(unsigned short bone, mm::Quat* rot) const {
    const anm::Skeleton* skeleton = m_skeleton;
    if (skeleton == nullptr || bone >= skeleton->m_referencePose.size()) {
        return false;
    }
    anm::QsTransform transform = skeleton->m_referencePose[bone];
    for (short parent = m_skeleton->getParentIndex(bone); parent != -1; parent = m_skeleton->getParentIndex(parent)) {
        anm::TransformUtil::mul(skeleton->m_referencePose[parent], transform, &transform);
    }
    *rot = transform.m_rotation;
    return true;
}

void GfComModel::changeLayer(unsigned int oldLayer, unsigned int layer) {
    if (oldLayer == layer) {
        return;
    }
    fw::AnimationManager* manager = mm::mtl::PtrSingleton<fw::AnimationManager>::sys();
    if (manager != nullptr && m_model != nullptr && m_skeleton != nullptr) {
        manager->removePoseModifier(getLayer(), m_poseModifier);
        manager->addPoseModifier(layer, m_poseModifier);
        manager->removeAfterModifier(getLayer(), m_volumeFade);
        manager->addAfterModifier(layer, m_volumeFade);
    }
    m_model->changeLayer(layer);
}

mm::mtl::RTTI GfComModel::m_rtti("GfComModel", &GfComponent::m_rtti, nullptr);

}  // namespace gf

// destroyBoneReferenceFrame (not identical yet) erases bone and mount frames
template mm::mtl::Vector<gf::GfComModel::BoneFrameInfo>::iterator mm::mtl::Vector<gf::GfComModel::BoneFrameInfo>::erase(mm::mtl::Vector<gf::GfComModel::BoneFrameInfo>::iterator);

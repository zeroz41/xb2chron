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

namespace gf {
namespace mob {

void StateApproachPc::fn_71004D70EC(GfComBehaviorMob* owner, ai::State*) {
    owner->pad_53d9 = true;
    m_seq = &StateApproachPc::fn_71004D7108;
}

void StateApproachPc::fn_71004D7108(GfComBehaviorMob& owner, const fw::UpdateInfo&) {
    if (gmk::isPlayerExist()) {
        owner.execTurnCmdToPos(gmk::getPlayerPos());
        m_seq = &StateApproachPc::fn_71004D71C4;
    }
}

void StateApproachPc::fn_71004D71C4(GfComBehaviorMob& owner, const fw::UpdateInfo&) {
    if (owner.m_turnCmd.pad_6c) {
        m_execCmd.create(TFieldExecCmd<GfComAsm>::CreateInfo(static_cast<GfObj*>(owner.m_owner)->m_handle, "C_move"));
        m_seq = &StateApproachPc::fn_71004D723C;
    }
}

void StateApproachPc::fn_71004D714C(GfComBehaviorMob*, ai::State*) { m_seq = nullptr; }

void StateApproachPc::fn_71004D7154(GfComBehaviorMob* owner, const fw::UpdateInfo& info) {
    m_execCmd.update(info.m_deltaTime);
    if (m_seq) {
        (this->*m_seq)(*owner, info);
    }
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

void StateSquadMember::leave(GfComBehaviorMob*, ai::State*) {}

bool StateSquadMember::isCondMatch(const GfComBehaviorMob& owner) { return owner.isSquadMember(); }

void StateMove::enter(GfComBehaviorMob* owner, ai::State*) {
    execEndSchedule(*owner);
    owner->init(true);
    m_execCmd.create(TFieldExecCmd<GfComAsm>::CreateInfo(static_cast<GfObj*>(owner->m_owner)->m_handle, "C_move"));
    m_seq = &StateMove::seqUpdateMove;
}

void StateMove::seqWaitTurnEnd(GfComBehaviorMob& owner, const fw::UpdateInfo&) {
    if (owner.m_turnCmd.pad_6c) {
        owner.init(true);
        m_execCmd.create(TFieldExecCmd<GfComAsm>::CreateInfo(static_cast<GfObj*>(owner.m_owner)->m_handle, "C_move"));
        m_seq = &StateMove::seqUpdateMove;
    }
}

void StateMove::leave(GfComBehaviorMob*, ai::State*) {}

bool StateMove::isCondMatch(const GfComBehaviorMob& owner) { return owner.pad_b8 != nullptr; }

}  // namespace mob

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
    : pad_10(-1), m_model(nullptr), m_skeleton(nullptr), m_pose(nullptr), m_extraTruckBuffer(nullptr), m_scale(1.0f),
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

mm::mtl::RTTI GfComModel::m_rtti("GfComModel", &GfComponent::m_rtti, nullptr);

}  // namespace gf

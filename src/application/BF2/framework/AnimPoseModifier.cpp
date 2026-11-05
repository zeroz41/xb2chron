#include "classes/fw/AnimPoseModifier.h"
#include "classes/fw/ModelObject.h"
#include "classes/anm/Pose.h"
#include "classes/anm/ExtraTruckBuffer.h"
#include "ml/ScnObjAccResNode.h"
#include "ml/ScnObjAccEtcParams.h"
#include "mm/mtl/Vector.h"
#include "classes/anm/Skeleton.h"
#include "anm/Array.h"
#include "algorithm"
#include "string.h"

namespace anm {

short ExtraTruckSlot::getTruckID(const char* name) const {
    if (m_truckNames.size() != 0) {
        ArrayIterartor<const char* const> it =
            std::lower_bound(m_truckNames.begin(), m_truckNames.end(), name, CompTruck());
        if (it != m_truckNames.end() && strcmp(*it, name) == 0) {
            return std::distance(m_truckNames.begin(), it);
        }
    }
    return -1;
}

}  // namespace anm

namespace fw {

AnimPoseModifier::AnimPoseModifier() : m_pose(nullptr), m_model(nullptr), m_extra(nullptr) {}

AnimPoseModifier::~AnimPoseModifier() {
    unbind();
}

void AnimPoseModifier::unbind() {
    if (m_pose != nullptr) {
        m_pose->release();
        m_pose = nullptr;
    }
    if (m_model != nullptr) {
        m_model->release();
        m_model = nullptr;
    }
    m_boneIndices.clear();
    m_boneBinds.clear();
    if (m_extra != nullptr) {
        m_extra->release();
        m_extra = nullptr;
    }
    m_extraTruckIDs.clear();
}

void AnimPoseModifier::bind(anm::Pose* pose, ModelObject* model, anm::ExtraTruckBuffer* extra,
                            mm::mtl::IAllocator* allocator) {
    unbind();
    m_pose = pose;
    pose->addRef();
    m_model = model;
    model->addRef();
    m_boneIndices.setAllocator(allocator);
    ml::ScnObjAccResNode resNode(m_model->getInterface());
    int boneMax = resNode.getBoneMax();
    m_boneIndices.resize(boneMax);
    const anm::Skeleton* skeleton = pose->m_pSkeleton;
    for (int i = 0; i < boneMax; i++) {
        const char* name = resNode.getBoneName(i);
        unsigned short bone = 0xFFFF;
        if (name != nullptr) {
            bone = skeleton->getBoneIndex(name);
        }
        m_boneIndices[i] = bone;
    }
    if (extra != nullptr) {
        m_extra = extra;
        extra->addRef();
        m_extraTruckIDs.setAllocator(allocator);
        ml::ScnObjAccEtcParams etcParams(m_model->getInterface());
        unsigned int max = etcParams.getMax();
        m_extraTruckIDs.resize(max, -1);
        const anm::ExtraTruckSlot* slot = m_extra->m_pSlot;
        for (unsigned int i = 0; i < max; i++) {
            m_extraTruckIDs[i] = slot->getTruckID(etcParams.getName(i));
        }
    }
}

void AnimPoseModifier::apply() {
    m_pose->syncModelSpace();
    ml::ScnObjAccResNode resNode(m_model->getInterface());
    mm::Mat44* mat = resNode.getBoneMatPtr(0);
    int boneMax = m_boneIndices.size();
    for (int i = 0; i < boneMax; i++, mat++) {
        short bone = m_boneIndices[i];
        if (bone > 0) {
            m_pose->calcMatrixModelSpace(bone, mat);
        }
    }
    if (m_boneBinds.size() != 0) {
        float scale = m_model->m_scale;
        for (unsigned int i = 0; i < m_boneBinds.size(); i++) {
            Transform& local = m_boneBinds[i].m_frame.get()->getLocalTransformForWrite();
            const anm::QsTransform& bone = m_pose->getBoneModelSpace(m_boneBinds[i].m_bone);
            // read z first: the original loads it before x and y
            float z = bone.m_translation.z;
            float y = bone.m_translation.y;
            float x = bone.m_translation.x;
            local.position.x = scale * x;
            local.position.y = scale * y;
            local.position.z = scale * z;
            local.rotation = bone.m_rotation;
            float sx = bone.m_scale.x;
            float sy = bone.m_scale.y;
            float sz = bone.m_scale.z;
            m_boneBinds[i].m_frame->m_scaleX = sx;
            m_boneBinds[i].m_frame->m_scaleY = sy;
            m_boneBinds[i].m_frame->m_scaleZ = sz;
        }
    }
    if (m_extra != nullptr) {
        ml::ScnObjAccEtcParams etcParams(m_model->getInterface());
        for (unsigned int i = 0; i < m_extraTruckIDs.size(); i++) {
            short truck = m_extraTruckIDs[i];
            if (truck != -1) {
                etcParams.setParams(i, m_extra->m_values[truck]);
            }
        }
    }
}

void AnimPoseModifier::unbindReferenceFrame(mm::mtl::IntrusivePtr<ReferenceFrame>& frame) {
    for (BoneBindInfo* it = m_boneBinds.begin(); it != m_boneBinds.end(); ++it) {
        if (it->m_frame == frame) {
            m_boneBinds.erase(it);
            return;
        }
    }
}

void AnimPoseModifier::bindReferenceFrameToBone(unsigned short bone, mm::mtl::IntrusivePtr<ReferenceFrame>& frame) {
    BoneBindInfo info = {frame, bone};
    m_boneBinds.push_back(info);
    if (frame) {
        frame->m_scaleX = 1.0f;
        frame->m_scaleY = 1.0f;
        frame->m_scaleZ = 1.0f;
    }
}

}  // namespace fw

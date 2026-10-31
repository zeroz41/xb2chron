#include "classes/anm/Pose.h"

#include <string.h>
#include "anm/TransformUtil.h"
#include "classes/anm/Skeleton.h"
#include "mm/Mat44.h"

namespace anm {

inline bool Pose::testBoneFlag(unsigned short boneID, BoneFlag flag) const {
    unsigned int index = m_pSkeleton->m_bones.size() * flag + boneID;
    return m_boneFlags.getLocal(index);
}

inline void Pose::setBoneFlag(unsigned short boneID, BoneFlag flag, bool on) {
    unsigned int index = m_pSkeleton->m_bones.size() * flag + boneID;
    m_boneFlags.setLocal(index, on);
}

Pose::Pose(const Skeleton* pSkeleton, mm::mtl::IAllocator* pAllocator)
    : ReferenceObject(pAllocator),
      m_pSkeleton(pSkeleton),
      m_localSpace(pAllocator),
      m_modelSpace(pAllocator),
      m_flags() {
#line 36
    MM_ASSERT(m_pSkeleton);
    m_pSkeleton->addRef();
    unsigned int boneCount = m_pSkeleton->m_bones.size();
    m_localSpace.reserve(boneCount);
    m_modelSpace.reserve(boneCount);
    m_boneFlags.initialize(pAllocator, boneCount * 3);
    m_localSpace.resize(boneCount);
    m_modelSpace.resize(boneCount);
    m_boneFlags.set(0, boneCount * 2, true);
    m_boneFlags.set(boneCount * 2, boneCount * 3, false);
    m_flags.set(POSE_LOCAL_SPACE_SYNCED, false);
    m_flags.set(POSE_MODEL_SPACE_SYNCED, false);
}

Pose::~Pose() {
    if (m_pSkeleton != nullptr) {
        m_pSkeleton->release();
        m_pSkeleton = nullptr;
    }
}

const QsTransform& Pose::getBoneLocalSpace(unsigned short boneID) {
    if (testBoneFlag(boneID, BONE_LOCAL_SPACE_DIRTY)) {
#line 129
        MM_ASSERT(!testBoneFlag(boneID, BONE_MODEL_SPACE_DIRTY));
        const QsTransform& modelSpace = m_modelSpace[boneID];
        short parentID = m_pSkeleton->m_parents[boneID];
        if (parentID == -1) {
            m_localSpace[boneID] = m_modelSpace[boneID];
        } else {
            const QsTransform& parentSpace = getBoneModelSpace(parentID);
            QsTransform& localSpace = m_localSpace[boneID];
            QsTransform inverse;
            TransformUtil::invert(parentSpace, &inverse);
            TransformUtil::mul(inverse, modelSpace, &localSpace);
        }
        setBoneFlag(boneID, BONE_LOCAL_SPACE_DIRTY, false);
    }
    return m_localSpace[boneID];
}

const QsTransform& Pose::getBoneModelSpace(unsigned short boneID) {
    if (testBoneFlag(boneID, BONE_MODEL_SPACE_DIRTY)) {
        calcBoneModelSpace(boneID);
    }
    return m_modelSpace[boneID];
}

void Pose::setBoneLocalSpace(unsigned short boneID, QsTransform const& transform) {
    makeAllChildrenLocalSpace(boneID);
    m_localSpace[boneID] = transform;
    setBoneFlag(boneID, BONE_MODEL_SPACE_DIRTY, true);
    m_flags.set(POSE_MODEL_SPACE_SYNCED, false);
}

void Pose::makeAllChildrenLocalSpace(unsigned short boneID) {
    unsigned int boneCount = m_pSkeleton->m_bones.size();
    setBoneFlag(boneID, BONE_FLAG_2, true);
    for (unsigned short i = boneID + 1; i < boneCount; i++) {
        short parentID = m_pSkeleton->m_parents[i];
        if (parentID != -1 && testBoneFlag(parentID, BONE_FLAG_2)) {
            getBoneLocalSpace(i);
            setBoneFlag(i, BONE_FLAG_2, true);
            m_flags.set(POSE_MODEL_SPACE_SYNCED, false);
        }
    }
    for (unsigned short i = boneID + 1; i < boneCount; i++) {
        if (testBoneFlag(i, BONE_FLAG_2)) {
            setBoneFlag(i, BONE_FLAG_2, false);
            setBoneFlag(i, BONE_MODEL_SPACE_DIRTY, true);
        }
    }
    setBoneFlag(boneID, BONE_FLAG_2, false);
}

void Pose::setBoneModelSpace(unsigned short boneID, QsTransform const& transform, PROPAGATE_TYPE propagate) {
    if (propagate == 0) {
        makeAllChildrenModelSpace(boneID);
    } else {
        makeAllChildrenLocalSpace(boneID);
    }
    m_modelSpace[boneID] = transform;
    setBoneFlag(boneID, BONE_LOCAL_SPACE_DIRTY, true);
    m_flags.set(POSE_LOCAL_SPACE_SYNCED, false);
}

void Pose::makeAllChildrenModelSpace(unsigned short boneID) {
    unsigned int boneCount = m_pSkeleton->m_bones.size();
    for (unsigned short i = boneID + 1; i < boneCount; i++) {
        if (m_pSkeleton->m_parents[i] == boneID) {
            getBoneModelSpace(i);
            setBoneFlag(i, BONE_LOCAL_SPACE_DIRTY, true);
            m_flags.set(POSE_LOCAL_SPACE_SYNCED, false);
        }
    }
}

QsTransform& Pose::accessBoneModelSpace(unsigned short boneID, PROPAGATE_TYPE propagate) {
    if (propagate == 0) {
        makeAllChildrenModelSpace(boneID);
    } else {
        makeAllChildrenLocalSpace(boneID);
    }
    getBoneModelSpace(boneID);
    setBoneFlag(boneID, BONE_LOCAL_SPACE_DIRTY, true);
    m_flags.set(POSE_LOCAL_SPACE_SYNCED, false);
    return m_modelSpace[boneID];
}

void Pose::syncLocalSpace() {
    if (!m_flags.test(POSE_LOCAL_SPACE_SYNCED)) {
        unsigned int boneCount = m_pSkeleton->m_bones.size();
        for (unsigned short i = 0; i < boneCount; i++) {
            if (testBoneFlag(i, BONE_LOCAL_SPACE_DIRTY)) {
#line 275
                MM_ASSERT(!testBoneFlag(i, BONE_MODEL_SPACE_DIRTY));
                const QsTransform& modelSpace = m_modelSpace[i];
                short parentID = m_pSkeleton->m_parents[i];
                if (parentID == -1) {
                    m_localSpace[i] = m_modelSpace[i];
                } else {
#line 281
                    MM_ASSERT(!testBoneFlag(parentID, BONE_MODEL_SPACE_DIRTY));
                    const QsTransform& parentSpace = m_modelSpace[parentID];
                    QsTransform& localSpace = m_localSpace[i];
                    QsTransform inverse;
                    TransformUtil::invert(parentSpace, &inverse);
                    TransformUtil::mul(inverse, modelSpace, &localSpace);
                }
                setBoneFlag(i, BONE_LOCAL_SPACE_DIRTY, false);
            }
        }
        m_flags.set(POSE_LOCAL_SPACE_SYNCED, true);
    }
}

void Pose::syncModelSpace() {
    if (!m_flags.test(POSE_MODEL_SPACE_SYNCED)) {
        unsigned int boneCount = m_pSkeleton->m_bones.size();
        for (unsigned short i = 0; i < boneCount; i++) {
            if (testBoneFlag(i, BONE_MODEL_SPACE_DIRTY)) {
#line 315
                MM_ASSERT(!testBoneFlag(i, BONE_LOCAL_SPACE_DIRTY));
                const QsTransform& localSpace = m_localSpace[i];
                short parentID = m_pSkeleton->m_parents[i];
                if (parentID == -1) {
                    m_modelSpace[i] = m_localSpace[i];
                } else {
#line 321
                    MM_ASSERT(!testBoneFlag(parentID, BONE_MODEL_SPACE_DIRTY));
                    TransformUtil::mul(m_modelSpace[parentID], localSpace, &m_modelSpace[i]);
                }
                setBoneFlag(i, BONE_MODEL_SPACE_DIRTY, false);
            }
        }
        m_flags.set(POSE_MODEL_SPACE_SYNCED, true);
    }
}

void Pose::setReferencePose() {
    unsigned int boneCount = m_pSkeleton->m_bones.size();
    memcpy(m_localSpace.data(), m_pSkeleton->m_referencePose.m_pElements, boneCount * sizeof(QsTransform));
    for (unsigned short i = 0; i < boneCount; i++) {
        setBoneFlag(i, BONE_MODEL_SPACE_DIRTY, true);
        setBoneFlag(i, BONE_LOCAL_SPACE_DIRTY, false);
    }
    m_flags.set(POSE_LOCAL_SPACE_SYNCED, true);
    m_flags.set(POSE_MODEL_SPACE_SYNCED, false);
}

void Pose::calcMatrixModelSpace(unsigned short boneID, mm::Mat44* pDst) {
#line 554
    MM_ASSERT(pDst);
    if (m_flags.test(POSE_MODEL_SPACE_SYNCED)) {
        TransformUtil::calcMatrix(m_modelSpace[boneID], pDst);
    }
}

void TransformUtil::calcMatrix(const QsTransform& t, mm::Mat44* pOut) {
    pOut->setScale(mm::Vec3(t.m_scale.x, t.m_scale.y, t.m_scale.z));
    const mm::Quat& q = t.m_rotation;
    const float x2 = q.x + q.x;
    const float y2 = q.y + q.y;
    const float z2 = q.z + q.z;
    const float xx = q.x * x2;
    const float xz = q.x * z2;
    const float yy = q.y * y2;
    const float xy = q.x * y2;
    const float wx = x2 * q.w;
    const float wy = y2 * q.w;
    const float wz = q.w * z2;
    const float zz = q.z * z2;
    const float yz = q.y * z2;
    mm::Mat44 rotation;
    rotation.m[0][0] = 1.0f - (yy + zz);
    rotation.m[0][1] = xy + wz;
    rotation.m[0][2] = xz - wy;
    rotation.m[0][3] = 0.0f;
    rotation.m[1][0] = xy - wz;
    rotation.m[1][1] = 1.0f - (xx + zz);
    rotation.m[1][2] = yz + wx;
    rotation.m[1][3] = 0.0f;
    rotation.m[2][0] = xz + wy;
    rotation.m[2][1] = yz - wx;
    rotation.m[2][2] = 1.0f - (xx + yy);
    rotation.m[2][3] = 0.0f;
    rotation.m[3][0] = 0.0f;
    rotation.m[3][1] = 0.0f;
    rotation.m[3][2] = 0.0f;
    rotation.m[3][3] = 1.0f;
    *pOut = *pOut * rotation;
    memcpy(pOut->m[3], &t.m_translation, sizeof(float) * 3);
}

mm::mtl::Vector<QsTransform>& Pose::accessSyncedPoseLocalSpace() {
    syncLocalSpace();
    unsigned int boneCount = m_pSkeleton->m_bones.size();
    for (unsigned int i = 0; i < boneCount; i++) {
        setBoneFlag(i, BONE_MODEL_SPACE_DIRTY, true);
    }
    m_flags.set(POSE_LOCAL_SPACE_SYNCED, true);
    m_flags.set(POSE_MODEL_SPACE_SYNCED, false);
    return m_localSpace;
}

mm::mtl::Vector<QsTransform>& Pose::accessSyncedPoseModelSpace() {
    syncModelSpace();
    unsigned int boneCount = m_pSkeleton->m_bones.size();
    for (unsigned int i = 0; i < boneCount; i++) {
        setBoneFlag(i, BONE_LOCAL_SPACE_DIRTY, true);
    }
    m_flags.set(POSE_LOCAL_SPACE_SYNCED, false);
    m_flags.set(POSE_MODEL_SPACE_SYNCED, true);
    return m_modelSpace;
}

}  // namespace anm

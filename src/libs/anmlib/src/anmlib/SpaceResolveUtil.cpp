#include "anm/SpaceResolveUtil.h"
#include "anm/Array.h"
#include "anm/QsTransform.h"
#include "anm/TransformUtil.h"
#include "classes/anm/Binding.h"
#include "classes/anm/Skeleton.h"
#include "mm/Quat.h"
#include "mm/Vec4.h"

namespace anm {

bool SpaceResolveUtil::clacPoseMSNoTruck(const Binding* pBinding, const Skeleton* pSkeleton, QsTransform* pPose) {
    unsigned int count = pBinding->m_indexTable.size();
    if (count != pSkeleton->m_bones.size()) {
        return false;
    }
    for (unsigned int i = 0; i < count; i++) {
        if (pBinding->m_indexTable[i] < 0) {
            short parent = pSkeleton->getParentIndex(i);
            if (parent == -1) {
                pPose[i] = pSkeleton->m_referencePose[i];
            } else {
                TransformUtil::mul(pPose[parent], pSkeleton->m_referencePose[i], &pPose[i]);
            }
        }
    }
    return true;
}

void SpaceResolveUtil::convertMStoLS(const Skeleton* pSkeleton, QsTransform* pPose) {
    for (unsigned int i = pSkeleton->m_bones.size() - 1; i != 0; i--) {
        short parent = pSkeleton->getParentIndex(i);
        if (parent != -1) {
            QsTransform inverse;
            TransformUtil::invert(pPose[parent], &inverse);
            TransformUtil::mul(inverse, pPose[i], &pPose[i]);
        }
    }
}

void SpaceResolveUtil::convertMStoLSPartial(const Skeleton* pSkeleton, const bool* pFlags, QsTransform* pPose) {
    for (unsigned int i = pSkeleton->m_bones.size() - 1; i != 0; i--) {
        short parent = pSkeleton->getParentIndex(i);
        if (pFlags[i] && parent != -1) {
            QsTransform inverse;
            TransformUtil::invert(pPose[parent], &inverse);
            TransformUtil::mul(inverse, pPose[i], &pPose[i]);
        }
    }
}

bool SpaceResolveUtil::setReferencePoseNoTruck(const Binding* pBinding, const Skeleton* pSkeleton,
                                               QsTransform* pPose) {
    unsigned int count = pBinding->m_indexTable.size();
    if (count != pSkeleton->m_bones.size()) {
        return false;
    }
    for (unsigned int i = 0; i < count; i++) {
        if (pBinding->m_indexTable[i] < 0) {
            pPose[i] = pSkeleton->m_referencePose[i];
        }
    }
    return true;
}

void SpaceResolveUtil::convertLStoMS(const Skeleton* pSkeleton, QsTransform* pPose) {
    unsigned int count = pSkeleton->m_bones.size();
    for (unsigned int i = 0; i < count; i++) {
        short parent = pSkeleton->getParentIndex(i);
        if (parent != -1) {
            TransformUtil::mul(pPose[parent], pPose[i], &pPose[i]);
        }
    }
}

void SpaceResolveUtil::convertLStoMSPartial(const Skeleton* pSkeleton, const bool* pFlags, QsTransform* pPose) {
    unsigned int count = pSkeleton->m_bones.size();
    for (unsigned int i = 0; i < count; i++) {
        short parent = pSkeleton->getParentIndex(i);
        if (pFlags[i] && parent != -1) {
            TransformUtil::mul(pPose[parent], pPose[i], &pPose[i]);
        }
    }
}

}  // namespace anm

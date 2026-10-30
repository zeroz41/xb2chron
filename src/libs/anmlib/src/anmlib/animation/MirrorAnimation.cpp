#include "mm/mtl/Vector.h"
#include "classes/anm/MirrorMapper.h"
#include "classes/anm/MirrorAnimation.h"
#include "classes/anm/MirrorAnimation.h"
#include "anm/AnimationObject.h"
#include "classes/anm/Animation.h"
#include "classes/anm/Binding.h"
#include "classes/anm/MirrorMapper.h"
#include "classes/anm/ReferenceObject.h"
#include "classes/anm/Skeleton.h"
#include "anm/Array.h"
#include "anm/QsTransform.h"
#include "mm/MMStdBase.h"
#include "mm/mtl/Vector.h"

namespace anm {

MirrorAnimation::~MirrorAnimation() {
    if (m_pMapper != nullptr) {
        m_pMapper->release();
        m_pMapper = nullptr;
    }
    if (m_pOriginal != nullptr) {
        m_pOriginal->release();
        m_pOriginal = nullptr;
    }
}

void MirrorAnimation::sampleTrucks(float time, const anm::Binding& binding, anm::QsTransform* pOut) const {
    mm::mtl::Vector<QsTransform> pose(m_pAllocator);
    unsigned int count = m_pOriginal->m_indexTable.size();
    pose.resize(count);
    const Skeleton* pSkeleton = m_pMapper->m_pSkeleton;
    for (unsigned int i = 0; i < count; i++) {
        if (m_pOriginal->m_indexTable[i] < 0) {
            pose[i] = pSkeleton->m_referencePose[i];
        }
    }
    m_pOriginal->m_pAnimation->sampleTrucks(time, *m_pOriginal, pose.data());
    m_pMapper->mirrorPose(*m_pOriginal, binding, pose.data(), pOut);
}

bool MirrorAnimation::getExtractMotion(float time, anm::QsTransform* pOut) const {
    QsTransform motion;
    if (m_pOriginal->m_pAnimation->getExtractMotion(time, &motion)) {
        m_pMapper->mirrorExtractMotion(motion, pOut);
        return true;
    }
    return false;
}

bool MirrorAnimation::getDeltaExtractMotion(float time, float delta, bool loop, anm::QsTransform* pOut) const {
    QsTransform motion;
    if (m_pOriginal->m_pAnimation->getDeltaExtractMotion(time, delta, loop, &motion)) {
        m_pMapper->mirrorExtractMotion(motion, pOut);
        return true;
    }
    return false;
}

int MirrorAnimation::getImplType() const {
    return m_pOriginal->m_pAnimation->getImplType();
}

}  // namespace anm

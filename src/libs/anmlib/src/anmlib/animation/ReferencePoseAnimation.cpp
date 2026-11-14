#include "classes/anm/ReferencePoseAnimation.h"
#include "anm/AnimationObject.h"
#include "classes/anm/Animation.h"
#include "classes/anm/Binding.h"
#include "classes/anm/Skeleton.h"
#include "mm/MMStdBase.h"

namespace anm {

ReferencePoseAnimation::~ReferencePoseAnimation() {
    if (m_pSkeleton != nullptr) {
        m_pSkeleton->release();
        m_pSkeleton = nullptr;
    }
}

void ReferencePoseAnimation::sampleTrucks(float, const Binding& binding, QsTransform* pOut) const {
    unsigned int count = binding.m_indexTable.size();
    const Array<QsTransform> referencePose = m_pSkeleton->m_referencePose;
    for (unsigned int i = 0; i < count; i++) {
        short bone = binding.m_indexTable[i];
        if (bone >= 0) {
            pOut[i] = referencePose[bone];
        }
    }
}

int ReferencePoseAnimation::getImplType() const {
    return -4;
}

}  // namespace anm

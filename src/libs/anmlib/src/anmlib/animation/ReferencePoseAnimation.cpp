#include "classes/anm/ReferencePoseAnimation.h"
#include "anm/AnimationObject.h"
#include "classes/anm/Animation.h"
#include "classes/anm/Skeleton.h"
#include "mm/MMStdBase.h"

namespace anm {

ReferencePoseAnimation::~ReferencePoseAnimation() {
    if (m_pSkeleton != nullptr) {
        m_pSkeleton->release();
        m_pSkeleton = nullptr;
    }
}

int ReferencePoseAnimation::getImplType() const {
    return -4;
}

}  // namespace anm

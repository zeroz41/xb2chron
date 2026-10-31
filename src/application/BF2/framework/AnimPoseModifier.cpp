#include "classes/fw/AnimPoseModifier.h"

namespace fw {

void AnimPoseModifier::unbindReferenceFrame(mm::mtl::IntrusivePtr<ReferenceFrame>& frame) {
    for (BoneBindInfo* it = m_boneBinds.begin(); it != m_boneBinds.end(); ++it) {
        if (it->m_frame == frame) {
            m_boneBinds.erase(it);
            return;
        }
    }
}

}  // namespace fw

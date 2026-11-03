#include "classes/fw/AnimPoseModifier.h"
#include "mm/mtl/Vector.h"

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

// a short vector's resize (its user is not written yet)
template void mm::mtl::Vector<short>::resize(size_t);

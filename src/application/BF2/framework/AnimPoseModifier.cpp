#include "classes/fw/AnimPoseModifier.h"
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

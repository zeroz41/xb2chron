#ifndef GF_GFSLOTMAPPING_H
#define GF_GFSLOTMAPPING_H

namespace gf {
// the asset slots' layout (application/BF2/gf/asset/gf_slot_mapping.cpp)
class GfSlotMapping {
public:
    // the bytes all slots take (GfMemManager::initializeCore makes the asset memory that size)
    static unsigned long getAllSize();
};
}  // namespace gf

#endif

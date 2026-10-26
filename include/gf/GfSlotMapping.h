#ifndef GF_GFSLOTMAPPING_H
#define GF_GFSLOTMAPPING_H

namespace fw { class UpdateInfo; }
namespace gf { class GF_SLOT_HANDLE; }
namespace gf { class GfAssetPack; }
namespace gf { class GfSetupParam; }
namespace gf { class GfAllocator; }

namespace gf {
// the asset slots' layout (application/BF2/gf/asset/gf_slot_mapping.cpp)
class GfSlotMapping {
public:
    // the bytes all slots take (GfMemManager::initializeCore makes the asset memory that size)
    static unsigned long getAllSize();
    GfSlotMapping();
    // lays the slots out in `size` bytes of the allocator's memory (GfAssetManager::initialize passes the largest
    // block rounded down to 0x2000)
    void setup(const GfSetupParam& param, GfAllocator* allocator, unsigned long size);
    void update(const fw::UpdateInfo& info);
    // gives a slot GfAssetManager::releaseSlotHandle is handed back
    void releaseSlot(GF_SLOT_HANDLE* handle);
    // whether a slot is requested for the pack (GfAssetPack::isCached: a requested pack is not cached)
    bool isRequest(const GfAssetPack* pack) const;

    unsigned char pad_0[0x1828];  // GfAssetManager::initialize allocates 0x1828 bytes
};
}  // namespace gf

#endif

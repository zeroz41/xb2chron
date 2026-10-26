#ifndef GF_GFSLOTMAPPING_H
#define GF_GFSLOTMAPPING_H

namespace fw { class UpdateInfo; }
namespace gf { class GF_SLOT_HANDLE; }
namespace gf { class GfAssetPack; }

namespace gf {
// the asset slots' layout (application/BF2/gf/asset/gf_slot_mapping.cpp)
class GfSlotMapping {
public:
    // the bytes all slots take (GfMemManager::initializeCore makes the asset memory that size)
    static unsigned long getAllSize();
    void update(const fw::UpdateInfo& info);
    // gives a slot GfAssetManager::releaseSlotHandle is handed back
    void releaseSlot(GF_SLOT_HANDLE* handle);
    // whether a slot is requested for the pack (GfAssetPack::isCached: a requested pack is not cached)
    bool isRequest(const GfAssetPack* pack) const;
};
}  // namespace gf

#endif

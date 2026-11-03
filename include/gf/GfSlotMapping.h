#ifndef GF_GFSLOTMAPPING_H
#define GF_GFSLOTMAPPING_H

namespace fw { class UpdateInfo; }
namespace gf { class GF_SLOT_HANDLE; }
namespace gf { class GfAssetPack; }
namespace gf { class GfSetupParam; }
namespace gf { class GfAllocator; }
namespace gf { class GfSlotAllocator; }
namespace gf { class GfSlotAll; }

#include "mm/mtl/FixedVector.h"

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
    ~GfSlotMapping();
    void destroy();
    void updateSlotRequest(const fw::UpdateInfo& info);
    // from the slot allocator's memory (type 18 of m_slotAll's)
    void* allocateSize(unsigned long size, unsigned long alignment);
    // false when memory is outside the asset memory [m_memTop, m_memEnd)
    bool deallocateSize(void* memory);
    void createMapping(const GfSetupParam& param);

    // a requested slot load (the names are not the original's: updateSlotRequest shows what each does)
    struct REQ {
        void* m_handle;
        GfAssetPack* m_pack;
        unsigned int m_prio;
        float m_timeout;  // seconds left; at 0 the pack changes to its backup asset type or times out
    };
    // orders requests by their pack's priority, biggest first (requestSlotLoad's std::sort)
    struct BiggerPrio {
        inline bool operator()(const REQ& a, const REQ& b) const;
    };

    GfSlotAllocator* m_slotAllocator;  // the slots' memory (not the original's)
    GfSlotAll* m_slotAll;               // (not the original's)
    mm::mtl::FixedVector<REQ, 256> m_requests;  // (not the original's)
    unsigned long m_memTop;  // allocator 3's memory: its start (not the original's)
    unsigned long m_memEnd;  // and its end (not the original's)
};
}  // namespace gf

#endif

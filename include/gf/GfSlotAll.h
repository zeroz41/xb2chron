#ifndef GF_GFSLOTALL_H
#define GF_GFSLOTALL_H

#include "mm/mtl/FixedArray.h"
#include "mm/mtl/FixedVector.h"

namespace gf { class GF_SLOT_HANDLE; }
namespace gf { class GfSlotBase; }

namespace gf {
// every slot by asset type: GfSlotMapping owns one (0x2b550 bytes, its constructor news it). Its functions are
// application/BF2/gf/asset/gf_slot.cpp's; the constructor and destructor are inline (GfSlotMapping's hold them)
class GfSlotAll {
public:
    GfSlotAll() : m_reserved(0) {}
    void releaseSlot(GF_SLOT_HANDLE* handle);
    void deallocateSize(void* memory);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because GfSlotMapping hands it
    // its m_slotAll as this. What it does: GfSlotMapping::allocateSize hands it type 18 and the size and alignment.
    void* fn_71001C77B8(int type, unsigned long size, unsigned long alignment);

    void* m_reserved;  // 0 from the constructor (not the original's)
    mm::mtl::FixedArray<mm::mtl::FixedVector<GfSlotBase*, 1304>, 17> m_slots;  // per asset type (not the original's)
};
}  // namespace gf

#endif

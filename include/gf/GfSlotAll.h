#ifndef GF_GFSLOTALL_H
#define GF_GFSLOTALL_H

#include "mm/mtl/FixedArray.h"
#include "mm/mtl/FixedVector.h"

namespace gf { class GF_SLOT_HANDLE; }
namespace gf { class GfSlotBase; class GfSlotAllocator; }
namespace gf { enum GfAssetType : int; }
namespace mm { namespace mtl { class IAllocator; } }

namespace gf {
// every slot by asset type: GfSlotMapping owns one (0x2b550 bytes, its constructor news it). Its functions are
// application/BF2/gf/asset/gf_slot.cpp's; the constructor and destructor are inline (GfSlotMapping's hold them)
class GfSlotAll {
public:
    GfSlotAll() : m_handleCounter(0) {}
    GfSlotBase* getSlot(GF_SLOT_HANDLE* handle) const;
    void destroyMapping();
    void destroy(mm::mtl::FixedVector<GfSlotBase*, 1304>& slots);  // out of line in 1.0.0, inline in 3.0.1
    unsigned long getBlockSize(GfAssetType type) const;
    // GfSlotMapping::setupFreeSlot keeps the handle it returns
    GF_SLOT_HANDLE* setupSlotByte(GfAssetType type, unsigned long size, unsigned int param);
    unsigned int getSlotNumByByteSize(GfAssetType type, unsigned long size) const;
    GF_SLOT_HANDLE* setupSlotNum(GfAssetType type, unsigned int num, unsigned int param);
    GF_SLOT_HANDLE* createSlotHandle(GfAssetType type, unsigned int index);  // out of line in 1.0.0, inline in 3.0.1
    GF_SLOT_HANDLE* setupSlotNumTail(GfAssetType type, unsigned int num, unsigned int param);
    void releaseSlot(GF_SLOT_HANDLE* handle);
    // 2.0.0's symbols name it (its size and its caller, GfSlotMapping::isExistData, are 2.0.0's isExistData's)
    bool isExistData(GF_SLOT_HANDLE* handle) const;
    void createSlot(GfAssetType type, unsigned int count, const char* name, unsigned int size,
                    GfSlotAllocator* parent, bool memoryDebug);
    unsigned long getByteSizeBySlotNum(GfAssetType type, unsigned int num) const;
    bool isMemoryDebug(GfAssetType type) const;
    bool getSlotInfo(mm::mtl::IAllocator*& allocator, void*& buffer, unsigned long& size, GF_SLOT_HANDLE* handle);
    bool getSlotInfo(void*& buffer, unsigned long& size, GfAssetType type);
    void* allocateSize(GfAssetType type, unsigned long size, unsigned long alignment);
    void deallocateSize(void* memory);

    unsigned long m_handleCounter;  // 0 from the constructor; 1.0.0's createSlotHandle counts handles in it
    mm::mtl::FixedArray<mm::mtl::FixedVector<GfSlotBase*, 1304>, 17> m_slots;  // per asset type (not the original's)
};
}  // namespace gf

#endif

#ifndef CLASSES_GF_GFSLOTBASE_H
#define CLASSES_GF_GFSLOTBASE_H

#include "classes/mm/mtl/IAllocator.h"
#include "classes/gf/GfSlotAllocator.h"
#include "ml/CriticalSection.h"

namespace gf { class GF_SLOT_HANDLE; }

namespace gf {
// table 0x7100B45978: one slot of an asset type (GfSlotAll holds them). An IAllocator by its table (slots ~, ~,
// allocate, deallocate, getName as IAllocator's; 1.0.0's symbols name them) that hands the calls to its own
// GfSlotAllocator. In 3.0.1 every member locks the file's critical section (gf_slot.cpp). The field names are not the
// original's: they are what 1.0.0's accessors (getSlotHandle, getSlotSize, setParentSlot, getMultiSlot) read.
class GfSlotBase : public mm::mtl::IAllocator {
public:
    // inline in 3.0.1 (GfSlotAll::createSlot holds it; out of line in 1.0.0)
    GfSlotBase(const char* name, GfSlotAllocator* parent, unsigned int size, bool memoryDebug)
        : m_slotHandle(reinterpret_cast<GF_SLOT_HANDLE*>(-1)), m_slotSize(size), m_parentSlot(nullptr),
          m_multiSlot(1), m_slotParam(0), m_memoryDebug(memoryDebug) {
        m_allocator.setup(name, parent, size, 0x2000, memoryDebug);
    }
    virtual ~GfSlotBase();  // slot 0
    virtual void* allocate(unsigned long size, unsigned long alignment);  // slot 2
    virtual void deallocate(void* memory);  // slot 3
    virtual const char* getName() const;  // slot 4

    // 2.0.0's symbols name it (defined in gf_slot.cpp): locks every GfSlotBase and GfSlotAll member in 3.0.1
    static ml::CriticalSection s_section;

    void destroy();  // out of line in 1.0.0, inline in 3.0.1
    void releaseSlot();
    void setMultiSlot(unsigned int count);
    unsigned long getBlockSize() const {
        ml::CS lock(s_section);
        return m_allocator.getBlockSize();
    }
    unsigned long getSlotSize() const {
        ml::CS lock(s_section);
        return m_slotSize;
    }
    void* getBuffer() {
        ml::CS lock(s_section);
        return m_allocator.getBuffer();
    }
    unsigned long getBufferSize() const {
        ml::CS lock(s_section);
        return m_allocator.getBufferSize();
    }
    GF_SLOT_HANDLE* getSlotHandle() const {
        ml::CS lock(s_section);
        return m_slotHandle;
    }
    void setSlotHandle(GF_SLOT_HANDLE* handle, unsigned int param) {
        ml::CS lock(s_section);
        m_slotHandle = handle;
        m_slotParam = param;
    }
    void setParentSlot(GfSlotBase* parent) {
        ml::CS lock(s_section);
        m_parentSlot = parent;
    }
    bool isExistAsset() const {
        ml::CS lock(s_section);
        return m_allocator.getAllocs() != 0;
    }
    unsigned int getMultiSlot() const {
        ml::CS lock(s_section);
        return m_multiSlot;
    }

    GF_SLOT_HANDLE* m_slotHandle;  // 0x8, ~0 when none
    unsigned long m_slotSize;  // 0x10
    GfSlotAllocator m_allocator;  // 0x18
    GfSlotBase* m_parentSlot;  // 0x308
    unsigned int m_multiSlot;  // 0x310
    unsigned int m_slotParam;  // 0x314, setSlotHandle's second argument
    bool m_memoryDebug;  // 0x318, the constructor's last argument (GfSlotAll::isMemoryDebug returns it)
};
}  // namespace gf

#endif

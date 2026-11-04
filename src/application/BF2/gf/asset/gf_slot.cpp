#include "mm/mtl/FixedList.h"
#include "classes/gf/GfSizeAlloc.h"
#include "classes/gf/GfSlotBase.h"
#include "gf/GfSlotAll.h"
#include "classes/gf/GfAllocator.h"
#include <string.h>

namespace gf {

// 2.0.0's symbols name it
ml::CriticalSection GfSlotBase::s_section;

void GfSizeAlloc::setup(mm::mtl::IAllocator* allocator, unsigned int blockSize, void* buffer,
                        unsigned long bufferSize) {
    if (m_blocks != nullptr) {
        delete m_blocks;
        m_blocks = nullptr;
    }
    m_blockSize = blockSize;
    m_buffer = buffer;
    m_bufferSize = bufferSize;
    m_allocs = 0;
    m_blockNum = bufferSize / m_blockSize;
    memset(buffer, 0xFD, bufferSize);
    m_blocks = static_cast<unsigned int*>(allocator->allocate(static_cast<unsigned long>(m_blockNum) * 4, 4));
    memset(m_blocks, 0, static_cast<unsigned long>(m_blockNum) * 4);
    m_allocs = 0;
    m_list.push_back(0);
    m_blocks[0] = m_blockNum;
    m_allocator = allocator;
}

void GfSizeAlloc::destroy() {
    if (m_blocks != nullptr) {
        delete m_blocks;
        m_blocks = nullptr;
    }
    m_allocs = 0;
    m_blockNum = 0;
    m_buffer = nullptr;
    m_bufferSize = 0;
}

void GfSizeAlloc::resize(unsigned long bufferSize) {
    unsigned int blockNum = bufferSize / m_blockSize;
    m_bufferSize = bufferSize;
    m_blockNum = blockNum;
    memset(m_buffer, 0xFD, bufferSize);
    if (m_blocks != nullptr) {
        delete m_blocks;
        m_blocks = nullptr;
    }
    m_blocks = static_cast<unsigned int*>(m_allocator->allocate(static_cast<unsigned long>(m_blockNum) * 4, 4));
    memset(m_blocks, 0, static_cast<unsigned long>(m_blockNum) * 4);
    m_blocks[0] = m_blockNum;
}
}  // namespace gf

// instantiated for gf::GfSizeAlloc::alloc, gf::GfSizeAlloc::free (not written yet)
template mm::mtl::FixedList<unsigned int, 64>::iterator mm::mtl::FixedList<unsigned int, 64>::erase(mm::mtl::FixedList<unsigned int, 64>::iterator);

namespace gf {

// alloc and free (and the FixedList<unsigned int, 64>::erase they instantiate): not written yet (not identical)

inline void GfSlotBase::destroy() {
    ml::CS lock(GfSlotBase::s_section);
    m_allocator.destroy();
}

GfSlotBase::~GfSlotBase() {
    destroy();
}

void* GfSlotBase::allocate(unsigned long size, unsigned long alignment) {
    ml::CS lock(GfSlotBase::s_section);
    return m_allocator.allocate(size, alignment);
}

void GfSlotBase::deallocate(void* memory) {
    ml::CS lock(GfSlotBase::s_section);
    m_allocator.deallocate(memory);
}

const char* GfSlotBase::getName() const {
    ml::CS lock(GfSlotBase::s_section);
    return m_allocator.m_name.m_str;
}

void GfSlotBase::releaseSlot() {
    ml::CS lock(GfSlotBase::s_section);
    {
        // a locked block whose body the release build compiles out (as the original's code shows: lock, unlock)
        ml::CS check(GfSlotBase::s_section);
    }
    {
        // a locked block whose body the release build compiles out (as the original's code shows: lock, unlock)
        ml::CS check(GfSlotBase::s_section);
    }
    m_slotHandle = reinterpret_cast<GF_SLOT_HANDLE*>(-1);
    m_parentSlot = nullptr;
    m_multiSlot = 1;
    m_allocator.resize(m_slotSize);
}

void GfSlotBase::setMultiSlot(unsigned int count) {
    ml::CS lock(GfSlotBase::s_section);
    if (m_allocator.getAllocs() == 0) {
        m_multiSlot = count;
        m_allocator.resize(m_slotSize * count);
    }
    {
        // a locked block whose body the release build compiles out (as the original's code shows: lock, unlock)
        ml::CS check(GfSlotBase::s_section);
    }
}

GfSlotBase* GfSlotAll::getSlot(GF_SLOT_HANDLE* handle) const {
    unsigned long value = reinterpret_cast<unsigned long>(handle);
    unsigned long index = value & 0xFFFF;
    return m_slots[(value >> 16 & 0xFFFF) - 3][index];
}

inline void GfSlotAll::destroy(mm::mtl::FixedVector<GfSlotBase*, 1304>& slots) {
    for (GfSlotBase** it = slots.begin(); it != slots.end(); ++it) {
        if (*it != nullptr) {
            delete *it;
            *it = nullptr;
        }
    }
    slots.clear();
}

void GfSlotAll::destroyMapping() {
    for (mm::mtl::FixedVector<GfSlotBase*, 1304>* it = m_slots.begin(); it != m_slots.end(); ++it) {
        destroy(*it);
    }
}

unsigned long GfSlotAll::getBlockSize(GfAssetType type) const {
    if (type == 0) {
        return 0x8000;
    }
    return m_slots[type - 3][0]->getBlockSize();
}

void GfSlotAll::setupSlotByte(GfAssetType type, unsigned long size, unsigned int param) {
    setupSlotNum(type, getSlotNumByByteSize(type, size), param);
}

unsigned int GfSlotAll::getSlotNumByByteSize(GfAssetType type, unsigned long size) const {
    const mm::mtl::FixedVector<GfSlotBase*, 1304>& slots = m_slots[type - 3];
    if (slots.empty()) {
        return 0;
    }
    unsigned long slotSize = slots[0]->getSlotSize();
    unsigned int num = size / slotSize;
    if (num == 0 || size % slotSize != 0) {
        num++;
    }
    return num;
}

inline GF_SLOT_HANDLE* GfSlotAll::createSlotHandle(GfAssetType type, unsigned int index) {
    unsigned long id = m_handleCounter++;
    if (id >> 32 != 0) {
        id = m_handleCounter++;
    }
    return reinterpret_cast<GF_SLOT_HANDLE*>(id << 32 | static_cast<long>(type << 16) | index);
}

GF_SLOT_HANDLE* GfSlotAll::setupSlotNum(GfAssetType type, unsigned int num, unsigned int param) {
    mm::mtl::FixedVector<GfSlotBase*, 1304>& slots = m_slots[type - 3];
    GF_SLOT_HANDLE* handle = reinterpret_cast<GF_SLOT_HANDLE*>(-1);
    if (slots.empty()) {
        return handle;
    }
    for (unsigned int start = 0; start < slots.size(); start++) {
        if (start + num > slots.size()) {
            break;
        }
        bool found = false;
        for (unsigned int i = start; i < start + num; i++) {
            if (slots[i]->getSlotHandle() != reinterpret_cast<GF_SLOT_HANDLE*>(-1)) {
                break;
            }
            if (i == start + num - 1) {
                found = true;
                break;
            }
        }
        if (found) {
            handle = createSlotHandle(type, start);
            for (unsigned int i = start; i < start + num; i++) {
                slots[i]->setSlotHandle(handle, param);
                if (i > start) {
                    slots[i]->setParentSlot(slots[start]);
                }
            }
            slots[start]->setMultiSlot(num);
            break;
        }
    }
    return handle;
}

void GfSlotAll::releaseSlot(GF_SLOT_HANDLE* handle) {
    unsigned long value = reinterpret_cast<unsigned long>(handle);
    unsigned int index = value & 0xFFFF;
    mm::mtl::FixedVector<GfSlotBase*, 1304>& slots = m_slots[(value >> 16 & 0xFFFF) - 3];
    unsigned int multiSlot = slots[index]->getMultiSlot();
    for (unsigned int i = index + 1; i < index + multiSlot; i++) {
        slots[i]->releaseSlot();
    }
    slots[index]->releaseSlot();
}

bool GfSlotAll::isExistData(GF_SLOT_HANDLE* handle) const {
    if (handle == reinterpret_cast<GF_SLOT_HANDLE*>(-1)) {
        return false;
    }
    unsigned long value = reinterpret_cast<unsigned long>(handle);
    unsigned int index = value & 0xFFFF;
    const mm::mtl::FixedVector<GfSlotBase*, 1304>& slots = m_slots[(value >> 16 & 0xFFFF) - 3];
    unsigned int multiSlot = slots[index]->getMultiSlot();
    for (unsigned int i = index + 1; i < index + multiSlot; i++) {
        if (slots[i]->isExistAsset()) {
            return true;
        }
    }
    return slots[index]->isExistAsset();
}

void GfSlotAll::createSlot(GfAssetType type, unsigned int count, const char* name, unsigned int size,
                           GfSlotAllocator* parent, bool memoryDebug) {
    mm::mtl::FixedVector<GfSlotBase*, 1304>& slots = m_slots[type - 3];
    for (unsigned int i = 0; i < count; i++) {
        mm::mtl::FixStr<16> slotName;
        slotName.format("%s%d", name, i + 1);
#line 562
        GfSlotBase* slot = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8)
            GfSlotBase(slotName.m_str, parent, size, memoryDebug);
        slots.push_back(slot);
    }
}

unsigned long GfSlotAll::getByteSizeBySlotNum(GfAssetType type, unsigned int num) const {
    return m_slots[type - 3][0]->getSlotSize() * num;
}

bool GfSlotAll::isMemoryDebug(GfAssetType type) const {
    return m_slots[type - 3][0]->m_memoryDebug;
}

bool GfSlotAll::getSlotInfo(mm::mtl::IAllocator*& allocator, void*& buffer, unsigned long& size,
                            GF_SLOT_HANDLE* handle) {
    if (handle == reinterpret_cast<GF_SLOT_HANDLE*>(-1)) {
        return false;
    }
    unsigned long value = reinterpret_cast<unsigned long>(handle);
    unsigned long index = value & 0xFFFF;
    mm::mtl::FixedVector<GfSlotBase*, 1304>& slots = m_slots[(value >> 16 & 0xFFFF) - 3];
    buffer = slots[index]->getBuffer();
    size = slots[index]->getBufferSize() * slots[index]->getMultiSlot();
    allocator = slots[index];
    return true;
}

bool GfSlotAll::getSlotInfo(void*& buffer, unsigned long& size, GfAssetType type) {
    mm::mtl::FixedVector<GfSlotBase*, 1304>& slots = m_slots[type - 3];
    if (slots.empty()) {
        return false;
    }
    buffer = slots[0]->getBuffer();
    size = slots[0]->getBufferSize() * slots.size();
    return true;
}

void* GfSlotAll::allocateSize(GfAssetType type, unsigned long size, unsigned long alignment) {
    unsigned int num = getSlotNumByByteSize(type, size);
    if (num == 0) {
        return nullptr;
    }
    GF_SLOT_HANDLE* handle = setupSlotNumTail(type, num, 0);
    if (handle == reinterpret_cast<GF_SLOT_HANDLE*>(-1)) {
        return nullptr;
    }
    mm::mtl::IAllocator* allocator;
    void* buffer = nullptr;
    unsigned long bufferSize;
    getSlotInfo(allocator, buffer, bufferSize, handle);
    return buffer;
}

}  // namespace gf

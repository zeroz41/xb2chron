#include "classes/mm/mtl/HeapAllocator.h"
#include "mm/mtl/Hash.h"
#include "mm/mtl/HeapAllocUtil.h"

namespace mm { namespace mtl {

HeapAllocator::HeapAllocator() {
    destroy(false);  // starts out as destroy() leaves it
}

HeapAllocator::~HeapAllocator() {
    destroy(false);
}

void HeapAllocator::destroy(bool removePool) {
    if (m_buffer != nullptr && removePool) {
        HeapAllocUtil::heap_remove_pool(m_control, m_buffer);
        HeapAllocUtil::heap_destroy(m_control);
#line 75
        MM_ASSERT(m_allocated == 0);
    }
    m_buffer = nullptr;
    m_control = nullptr;
    m_allocated = 0;
    m_bufferSize = 0;
    m_nameHash = 0;
    m_name = "";
}

void HeapAllocator::create(void* buffer, unsigned long bufferSize, const char* name) {
#line 53
    MM_ASSERT(buffer != nullptr);
    MM_ASSERT(bufferSize > 0);
    MM_ASSERT(name != nullptr);
    m_control = HeapAllocUtil::heap_create(m_controlBuffer);
#line 58
    MM_ASSERT(m_control != 0);
    m_buffer = HeapAllocUtil::heap_add_pool(m_control, buffer, bufferSize);
#line 60
    MM_ASSERT(m_buffer != 0);
    m_name = name;
    m_nameHash = hashStrCrc(m_name.m_str);
    m_bufferSize = bufferSize;
    m_allocated = 0;
}

const char* HeapAllocator::getName() const {
    return m_name.m_str;
}

void* HeapAllocator::allocate(unsigned long size, unsigned long alignment) {
#line 99
    MM_ASSERT(m_buffer != 0 && "allocator is not create");
    void* memory;
    if (alignment > 8) {
        memory = HeapAllocUtil::heap_memalign(m_control, alignment, size);
    } else {
        memory = HeapAllocUtil::heap_malloc(m_control, size);
    }
    if (memory != nullptr) {
        m_allocated++;
    }
    return memory;
}

void* HeapAllocator::allocate(unsigned long size, unsigned long alignment, const char* file, int line) {
#line 117
    MM_ASSERT(m_buffer != nullptr && "allocator is not create");
    void* memory;
    if (alignment > 8) {
        memory = HeapAllocUtil::heap_memalign(m_control, alignment, size);
    } else {
        memory = HeapAllocUtil::heap_malloc(m_control, size);
    }
    if (memory != nullptr) {
        m_allocated++;
    }
    return memory;
}

void HeapAllocator::deallocate(void* memory) {
    if (memory == nullptr) {
        return;
    }
#line 143
    MM_ASSERT(m_buffer != nullptr && "allocator is not create");
    HeapAllocUtil::heap_free(m_control, memory);
    m_allocated--;
}

}}  // namespace mm::mtl

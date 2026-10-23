#define MM_LIB_FROM_EFLIB
#include "mm/mtl/FixStr.h"
#include "mm/Vec3NA.h"
#include "ptlib/math/KeyFrameIP.h"
#include "classes/ptlib/HeapAllocator.h"
#include "mm/MMStdBase.h"
#include "mm/Vec3.h"
#include "mm/mtl/Hash.h"
#include "mm/mtl/HeapAllocUtil.h"
#include "ptlib/ParticleSystem.h"
#include "math.h"
#include "string.h"
#include <new>

namespace ptlib { namespace math {

// the library's random sequence (fxMath_RandI; the symbols leave it unnamed, the name is not the original's)
static unsigned int s_randSeed;

float fxMath_rsqrt(float x) {
    float half = x * -0.5f;
    union {
        float f;
        unsigned int u;
    } bits;
    bits.f = x;
    bits.u = 0x5F3759DF - (bits.u >> 1);
    float y = bits.f;
    return y * (y * (half * y) + 1.5f);
}

unsigned int fxMath_RandI() {
    return fxMath_RandI(s_randSeed);
}

float randf2() {
    return randf2(s_randSeed);
}

void KeyFrameIP::setup_keyrand(EPkey* key, int count, unsigned int& seed) {
    unsigned short id0 = static_cast<int>(m_key0[-1]);
    unsigned short id1 = static_cast<int>(m_key1[-1]);
    if (key->m_id[0] != id0) {
        unsigned short old = key->m_id[1];
        key->m_id[0] = id0;
        if (old == id0) {
            key->m_seed[0] = key->m_seed[1];
        } else {
            key->m_seed[0] = fxMath_RandI(seed);
            for (int i = 1; i < count; ++i) {
                fxMath_RandI(seed);
            }
        }
    }
    if (key->m_id[1] != id1) {
        key->m_id[1] = id1;
        key->m_seed[1] = fxMath_RandI(seed);
        for (int i = 1; i < count; ++i) {
            fxMath_RandI(seed);
        }
    }
    m_seed0 = key->m_seed[0];
    m_seed1 = key->m_seed[1];
}

// get_ip1, get_ip2, get_ip3_col, fn_7100853550, mul_ip3_col, keyrand_get_ip1 and both keyrand_get_ip3 (and
// keyrand_mul_ip3, which calls one) are not identical yet: see the report

}}  // namespace ptlib::math

namespace ptlib {

HeapAllocator* HeapAllocaterManager::s_pIns;

void HeapAllocaterManager::init() {
    if (s_pIns != nullptr) {
        ParticleManager::sysFree(s_pIns);
        s_pIns = nullptr;
    }
#line 24
    s_pIns = static_cast<HeapAllocator*>(ParticleManager::sysAlloc(HEAP_OFFSET + HEAP_SIZE, 16, __FILE__, __LINE__));
    if (s_pIns != nullptr) {
        new (s_pIns) HeapAllocator();
        s_pIns->create(reinterpret_cast<char*>(s_pIns) + HEAP_OFFSET, HEAP_SIZE, "EfctHeap");
    }
}

void HeapAllocaterManager::term() {
    if (s_pIns != nullptr) {
        ParticleManager::sysFree(s_pIns);
        s_pIns = nullptr;
    }
}

void HeapAllocator::create(void* buffer, unsigned long bufferSize, const char* name) {
#line 148
    MM_ASSERT(buffer != nullptr);
    MM_ASSERT(bufferSize > 0);
    MM_ASSERT(name != nullptr);
    m_control = mm::mtl::HeapAllocUtil::heap_create(m_controlBuffer);
#line 153
    MM_ASSERT(m_control != 0);
    m_buffer = mm::mtl::HeapAllocUtil::heap_add_pool(m_control, buffer, bufferSize);
#line 155
    MM_ASSERT(m_buffer != 0);
    m_name = name;
    m_nameHash = mm::mtl::hashStrCrc(m_name.m_str);
    m_bufferSize = bufferSize;
    m_allocated = 0;
}

void* HeapAllocator::allocate(unsigned long size, unsigned long alignment) {
#line 194
    MM_ASSERT(m_buffer != 0 && "allocator is not create");
    void* memory;
    if (alignment > 8) {
        memory = mm::mtl::HeapAllocUtil::heap_memalign(m_control, alignment, size);
    } else {
        memory = mm::mtl::HeapAllocUtil::heap_malloc(m_control, size);
    }
    if (memory != nullptr) {
        m_allocated++;
    } else {
        efMsg("%d", m_allocated);
#line 206
        MM_ASSERT(0);
    }
    return memory;
}

void* HeapAllocator::allocate(unsigned long size, unsigned long alignment, const char* file, int line) {
#line 217
    MM_ASSERT(m_buffer != nullptr && "allocator is not create");
    void* memory;
    if (alignment > 8) {
        memory = mm::mtl::HeapAllocUtil::heap_memalign(m_control, alignment, size);
    } else {
        memory = mm::mtl::HeapAllocUtil::heap_malloc(m_control, size);
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
#line 243
    MM_ASSERT(m_buffer != nullptr && "allocator is not create");
    mm::mtl::HeapAllocUtil::heap_free(m_control, memory);
    m_allocated--;
}

unsigned long HeapAllocator::getBlockNum() {
    return m_allocated;
}

HeapAllocator::~HeapAllocator() {
    if (m_buffer != nullptr) {
        mm::mtl::HeapAllocUtil::heap_remove_pool(m_control, m_buffer);
        mm::mtl::HeapAllocUtil::heap_destroy(m_control);
#line 170
        MM_ASSERT(m_allocated == 0);
    }
    m_buffer = nullptr;
    m_control = nullptr;
    m_allocated = 0;
    m_bufferSize = 0;
    m_nameHash = 0;
    m_name.clear();
}

const char* HeapAllocator::getName() const {
    return m_name.m_str;
}

bool HeapAllocator::insideArea(const void* memory) const {
#line 263
    MM_ASSERT(m_buffer != 0 && "allocator is not create");
    unsigned long p = reinterpret_cast<unsigned long>(memory);
    unsigned long buffer = reinterpret_cast<unsigned long>(m_buffer);
    return buffer < p && p < buffer + m_bufferSize;
}

bool HeapAllocator::hasMemory(const void* memory) const {
#line 279
    MM_ASSERT(m_buffer != 0 && "allocator is not create");
    return insideArea(memory);
}

unsigned long HeapAllocator::getBlockSize(const void* adr) const {
    if (adr == nullptr) {
        return 0;
    }
#line 303
    MM_ASSERT(m_buffer != 0 && "allocator is not create");
#line 305
    MM_ASSERT(hasMemory(adr) && "pointer is not exist!!");
    return mm::mtl::HeapAllocUtil::heap_block_size(adr);
}

unsigned int HeapAllocator::getNameHash() const {
    return m_nameHash;
}

}  // namespace ptlib

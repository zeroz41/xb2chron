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

// the library's random sequence (fxMath_RandI, randf2). Proposed name, not the original's: the symbols leave it
// unnamed (lbl_71015E9D50)
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

// a key's value drawn from seed: the base values, then their ranges scaled by randf2 (KeyFrameIP's get_ functions;
// the names are not the original's)
inline float randKey1(const float* key, unsigned int& seed) {
    return key[0] + key[1] * randf2(seed);
}
inline void randKey2(vec2f* out, const float* key, unsigned int& seed) {
    out->x = key[0] + key[2] * randf2(seed);
    out->y = key[1] + key[3] * randf2(seed);
}
inline void randKey3(mm::Vec3NA* out, const float* key, unsigned int& seed) {
    out->x = key[0] + key[3] * randf2(seed);
    out->y = key[1] + key[4] * randf2(seed);
    out->z = key[2] + key[5] * randf2(seed);
}

float KeyFrameIP::get_ip1(int index) {
    float value0 = randKey1(m_key0 + index, m_seed0);
    float value1 = randKey1(m_key1 + index, m_seed1);
    float rate = m_rate;
    return rate * value1 + (1.0f - rate) * value0;
}

void KeyFrameIP::get_ip2(vec2f* out, int index) {
    vec2f value0;
    vec2f value1;
    randKey2(&value0, m_key0 + index, m_seed0);
    randKey2(&value1, m_key1 + index, m_seed1);
    float rate = m_rate;
    float inv = 1.0f - rate;
    out->x = value0.x * inv + rate * value1.x;
    out->y = value0.y * inv + rate * value1.y;
}

void KeyFrameIP::get_ip3(mm::Vec3NA* out, int index) {
    mm::Vec3NA value0;
    mm::Vec3NA value1;
    randKey3(&value0, m_key0 + index, m_seed0);
    randKey3(&value1, m_key1 + index, m_seed1);
    float rate = m_rate;
    float inv = 1.0f - rate;
    out->x = value0.x * inv + value1.x * rate;
    out->y = value0.y * inv + rate * value1.y;
    out->z = value0.z * inv + rate * value1.z;
}

void KeyFrameIP::get_ip3(mm::Vec3* out, int index) {
    mm::Vec3NA value0;
    mm::Vec3NA value1;
    randKey3(&value0, m_key0 + index, m_seed0);
    randKey3(&value1, m_key1 + index, m_seed1);
    float rate = m_rate;
    float inv = 1.0f - rate;
    out->x = value0.x * inv + value1.x * rate;
    out->y = value0.y * inv + rate * value1.y;
    out->z = value0.z * inv + rate * value1.z;
}

void KeyFrameIP::get_ip3_col(mm::Vec3* out, int index) {
    mm::Vec3 color0;
    mm::Vec3 color1;
    fn_7100853550(&color0, m_key0 + index, m_seed0);
    fn_7100853550(&color1, m_key1 + index, m_seed1);
    float rate = m_rate;
    float inv = 1.0f - rate;
    out->x = inv * color0.x + rate * color1.x;
    out->y = inv * color0.y + rate * color1.y;
    out->z = inv * color0.z + rate * color1.z;
}

// a value drawn between a and b from seed (fn_7100853550's; the name is not the original's)
inline float randRange(float a, float b, unsigned int& seed) {
    return a + fabsf(randf2(seed)) * (b - a);
}

// Placeholder name: 1.0.0 has it unnamed too (fn_710092F800, called by get_ip3_col and mul_ip3_col). What it
// does: a hue, saturation and value each drawn between the key's two values (key[0..2] and key[3..5]; the hues
// the shorter way round the circle) from seed, converted to red, green and blue in out.
// A sector of 6 (a hue of exactly 1) is sector 0 again; past that (NaN) the color is black.
void fn_7100853550(mm::Vec3* out, const float* key, unsigned int& seed) {
    float h1, h0;
    h0 = key[0];
    h1 = key[3];
    if (fabsf(h0 - h1) > 0.5f) {
        if (h1 < h0) {
            h1 += 1.0f;
        } else {
            h0 += 1.0f;
        }
    }
    float h = randRange(h0, h1, seed);
    float s = randRange(key[1], key[4], seed);
    float v = randRange(key[2], key[5], seed);
    if (h > 1.0f) {
        h -= 1.0f;
    }
    float h6 = h * 6.0f;
    int sector = static_cast<int>(floorf(h6));
    float f = h6 - sector;
    float p = (1.0f - s) * v;
    float q = v * (1.0f - s * f);
    float t = v * (1.0f - s * (1.0f - f));
    switch (sector) {
    case 0:
        out->x = v;
        out->y = t;
        out->z = p;
        break;
    case 1:
        out->x = q;
        out->y = v;
        out->z = p;
        break;
    case 2:
        out->x = p;
        out->y = v;
        out->z = t;
        break;
    case 3:
        out->x = p;
        out->y = q;
        out->z = v;
        break;
    case 4:
        out->x = t;
        out->y = p;
        out->z = v;
        break;
    case 5:
        out->x = v;
        out->y = p;
        out->z = q;
        break;
    case 6:
        out->x = v;
        out->y = t;
        out->z = p;
        break;
    default:
        out->x = 0.0f;
        out->y = 0.0f;
        out->z = 0.0f;
        break;
    }
}

void KeyFrameIP::mul_ip3_col(mm::Vec3* out, int index) {
    mm::Vec3 color;
    get_ip3_col(&color, index);
    out->x = color.x * out->x;
    out->y = color.y * out->y;
    out->z = color.z * out->z;
}

float KeyFrameIP::keyrand_get_ip1(EPkey* key, unsigned int& seed) {
    setup_keyrand(key, 1, seed);
    return get_ip1(0);
}

void KeyFrameIP::keyrand_get_ip3(mm::Vec3NA* out, EPkey* key, unsigned int& seed) {
    setup_keyrand(key, 3, seed);
    get_ip3(out, 0);
}

void KeyFrameIP::keyrand_get_ip3(mm::Vec3* out, EPkey* key, unsigned int& seed) {
    setup_keyrand(key, 3, seed);
    get_ip3(out, 0);
}

void KeyFrameIP::keyrand_mul_ip3(mm::Vec3NA* out, EPkey* key, unsigned int& seed) {
    mm::Vec3NA value;
    keyrand_get_ip3(&value, key, seed);
    out->x = value.x * out->x;
    out->y = value.y * out->y;
    out->z = value.z * out->z;
}

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

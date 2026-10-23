#ifndef PTLIB_MATH_KEYFRAMEIP_H
#define PTLIB_MATH_KEYFRAMEIP_H

namespace mm { class Vec3; }
namespace mm { struct Vec3NA; }

namespace ptlib {
// two floats (KeyFrameIP::get_ip2 writes x and y)
struct vec2f {
    float x;
    float y;
};
}  // namespace ptlib

namespace ptlib { namespace math {

// the effect library's math helpers (particle_heap_allocater.cpp)
float fxMath_rsqrt(float x);
// the next value of the library's random sequence (a linear congruential generator)
unsigned int fxMath_RandI();
// a random float in [-1, 1) from the library's sequence
float randf2();

// the next value of a random sequence kept by the caller, and a float in [-1, 1) from it (KeyFrameIP inlines
// these; the names are not the original's)
inline unsigned int fxMath_RandI(unsigned int& seed) {
    seed = seed * 0x41C64E6D + 12345;
    return seed;
}
inline float randf2(unsigned int& seed) {
    union {
        unsigned int u;
        float f;
    } bits;
    bits.u = (fxMath_RandI(seed) & 0x7FFFFF) | 0x40000000;
    return bits.f - 3.0f;
}

// what an emitter keeps per key pair for KeyFrameIP's keyrand_ functions: the keys' ids and the random seeds
// drawn for them (the names are not the original's: setup_keyrand draws a seed again when an id changes)
struct EPkey {
    unsigned short m_id[2];
    unsigned int m_seed[2];
};

// an interpolation between two keys of key-frame data: each key is base and range values (a float before them
// holds the key's id), blended by m_rate; the ranges are scaled by random values from m_seed. The names of the
// members are not the original's.
class KeyFrameIP {
public:
    void setup_keyrand(EPkey* key, int count, unsigned int& seed);
    float get_ip1(int index);
    void get_ip2(vec2f* out, int index);
    // 1.0.0 has these out of line; 3.0.1 only inlines get_ip3 into keyrand_get_ip3
    void get_ip3(mm::Vec3NA* out, int index);
    void get_ip3(mm::Vec3* out, int index);
    void get_ip3_col(mm::Vec3* out, int index);
    void mul_ip3(mm::Vec3NA* out, int index);
    void mul_ip3(mm::Vec3* out, int index);
    void mul_ip3_col(mm::Vec3* out, int index);
    float keyrand_get_ip1(EPkey* key, unsigned int& seed);
    void keyrand_get_ip3(mm::Vec3NA* out, EPkey* key, unsigned int& seed);
    void keyrand_get_ip3(mm::Vec3* out, EPkey* key, unsigned int& seed);
    void keyrand_mul_ip3(mm::Vec3NA* out, EPkey* key, unsigned int& seed);
    void keyrand_mul_ip3(mm::Vec3* out, EPkey* key, unsigned int& seed);

    const float* m_key0;
    const float* m_key1;
    float m_rate;  // 0 is m_key0, 1 is m_key1
    unsigned int m_seed0;
    unsigned int m_seed1;
};

}}  // namespace ptlib::math

#endif

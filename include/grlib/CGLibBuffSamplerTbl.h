#ifndef GRLIB_CGLIBBUFFSAMPLERTBL_H
#define GRLIB_CGLIBBUFFSAMPLERTBL_H

#include "grlib/GrlTypes.h"
#include "mm/Col4.h"

namespace grlib {

// a sampler's state (0x18 bytes), what CGLibBuffSamplerTbl::allocSampler shares a sampler object by. The bit
// positions are CGLibSampler's setters'; the field names are not the original's.
struct CGLibWkrSamplerParams {
    CGLibWkrSamplerParams() : m_clampS(0), m_clampT(0), m_clampR(0), m_compare(0), m_magFilter(0), m_minFilter(0),
        m_aniso(0), m_border(0), m_pad(0), m_borderColor(1.0f, 1.0f, 1.0f, 1.0f), m_lod(0.0f) {}

    unsigned int m_clampS : 4;     // bits 0..3
    unsigned int m_clampT : 4;     // bits 4..7
    unsigned int m_clampR : 4;     // bits 8..11
    unsigned int m_compare : 4;    // bits 12..15: setDepthCompare
    unsigned int m_magFilter : 1;  // bit 16
    unsigned int m_minFilter : 5;  // bits 17..21
    unsigned int m_aniso : 4;      // bits 22..25
    unsigned int m_border : 1;     // bit 26: a clamp mode above 5 (the border modes) is in use
    unsigned int m_pad : 5;        // bits 27..31: unused
    mm::Col4 m_borderColor;        // 0x04
    float m_lod;                   // 0x14: setLOD
};

class CGLibBuffResSamObj;

// the shared sampler objects (CGLibSystemContext holds one at 0x608; the size, 0x830, is the room to the next
// field the context's constructor builds)
class CGLibBuffSamplerTbl {
public:
    CGLibBuffSamplerTbl();
    CGLibBuffResSamObj* allocSampler(const CGLibWkrSamplerParams& params);
    // drops a reference to the object (and clears the pointer)
    void freeSampler(CGLibBuffResSamObj*& pObj);

    unsigned char pad_0[0x830];
};

}  // namespace grlib

#endif

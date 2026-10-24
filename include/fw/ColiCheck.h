#ifndef FW_COLICHECK_H
#define FW_COLICHECK_H

#include "mm/Vec3.h"
#include "mm/mtl/FixedVector.h"

namespace fw {

// what a collision test looks for (fw::ColiCheck::testCapsule reads it; StateFieldIdle::checkSpace and
// fw::ColiCheck::getSnapPos fill it on the stack). The field names are not the original's.
struct ColiCheckConfig {
    // the defaults getSnapPos keeps (checkSpace changes m_mode and m_option); both set m_flags and m_mask after it
    ColiCheckConfig() : m_radius(0.0f), pad_c(), m_mode(1), m_option(true), m_callbackParam(false) {}

    unsigned int m_flags;  // bits 0, 1, 3: test the collision (IDColiDef); bit 2: test the phantoms
    unsigned int m_mask;   // the collision groups to hit (testCapsule hands on its complement)
    float m_radius;        // testCapsule hands on its square
    unsigned char pad_c[0x4];
    unsigned int m_mode;   // 0, 1 or 2 (2: with result buffers)
    bool m_option;         // getSnapPos sets it, checkSpace clears it; testLine and testCapsule do not read it
    bool m_callbackParam;  // testLine and testCapsule copy it into their ColiCheckCallback
};

// a collision test's hits: room for N in place, their count, how many were found and whether any was
// (testCapsule clears all three first). The element's layout is not known; the field names are not the original's.
template <unsigned int N>
class TColiCheckResult {
public:
    struct Hit {
        unsigned char pad_0[0x50];
    } __attribute__((aligned(16)));

    TColiCheckResult() : m_count(0), m_hit(false) {}

    mm::mtl::FixedVector<Hit, N> m_hits;
    unsigned int m_count;
    bool m_hit;
};

class ColiCheck {
public:
    static bool testCapsule(TColiCheckResult<256>& result, const mm::Vec3& start, const mm::Vec3& end, float radius,
                            const ColiCheckConfig& config);
};

}  // namespace fw

#endif

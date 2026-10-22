#ifndef ANM_LOCOMOTION_H
#define ANM_LOCOMOTION_H

#include "anm/Array.h"
#include "mm/Vec3.h"
#include "mm/Vec4.h"

namespace anm { class QsTransform; }

namespace anm {
// an animation's root motion as keys at a fixed interval: per key a position along and a turn about one axis
// (anm_locomotion.cpp). The fields' names are not the original's
class Locomotion {
public:
    // the root's transform at `time`, from the start
    void getReference(float time, QsTransform* pDst) const;
    // the root's motion from `time` to `time + delta` within [start, end], wrapping around when `loop`
    void getDeltaReference(float time, float delta, float start, float end, bool loop, QsTransform* pDst) const;

    mm::Vec3 m_axis;             // the turns' axis
    float m_interval;            // the time between two keys
    unsigned char pad_14[0x4];
    Array<mm::Vec4> m_keys;      // x, y, z: the position; w: the turn
};
}  // namespace anm

#endif

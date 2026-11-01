#ifndef FW_RIMBLOOMCALC_H
#define FW_RIMBLOOMCALC_H

#include "mm/Col3.h"
#include "mm/mtl/FixedVector.h"

namespace fw {
// one rim bloom (commonLoaded reads them from rimbloom/<RimName>.rimb, BTL_HitEffectRim's rows); EffectManager keeps
// 64 (its constructor clears 0x0/0x10/0x418 of each 0x420 curve and 0xC80). sizeof 0xC88
class RimBloomCalc {
public:
    // one key of a curve: its frame and value, then two floats getVal's cubic reads as the key's slopes (the names
    // are not the original's)
    struct Key {
        float m_frame;
        float m_value;
        float m_slope0;
        float m_slope1;
    };
    // a curve's keys by frame (the names are not the original's)
    struct Curve {
        unsigned char pad_0[0x18];  // EffectManager's constructor clears 0x0 and 0x10
        mm::mtl::FixedVector<Key, 64> m_keys;
    };

    // the end frame: the last key's frame of the curve that ends last, if later than m_endFrame
    void calcEndFrame();
    // the curve index's value at frame: the first key's before its frame, the last key's after its frame, else
    // calcValFromCurve's (the parameter names are not the original's)
    float getVal(float frame, unsigned int index) const;
    // the curve index's cubic through the two keys around frame
    float calcValFromCurve(float frame, unsigned int index) const;

    Curve m_curves[3];  // getVal's and calcValFromCurve's index picks one (the name is not the original's)
    // what EffectManager::getAfterImageParams hands on as an after image's colour and the three floats after it (the
    // names are not the original's)
    mm::Col3 m_color;
    float m_params[3];
    unsigned char pad_c78[0x8];
    float m_endFrame;  // calcEndFrame stores it (the name is not the original's)
    unsigned char pad_c84[0x4];
};
}  // namespace fw

#endif

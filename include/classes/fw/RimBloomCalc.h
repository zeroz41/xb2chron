#ifndef FW_RIMBLOOMCALC_H
#define FW_RIMBLOOMCALC_H

#include "mm/Col3.h"

namespace fw {
// one rim bloom (commonLoaded reads them from rimbloom/<RimName>.rimb, BTL_HitEffectRim's rows); EffectManager keeps
// 64 (its constructor clears 0x0/0x10/0x418 of each 0x420 block, 0xC58 and 0xC80). sizeof 0xC88
class RimBloomCalc {
public:
    unsigned char pad_0[0xC60];
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

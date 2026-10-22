#ifndef FW_VOLUMEFADEPARAMS_H
#define FW_VOLUMEFADEPARAMS_H

#include "mm/Col3.h"

namespace fw {

// a volume fade (vanish) effect's parameters as fw::EffectManager loads them from a .dprm file: what
// ml::VolumeFadeParams carries, then its key frames. The file carries no field names, so none of these is the
// original's.
struct VolumeFadeParams {
    mm::Col3 m_colors[5];
    mm::Col3 m_color0;
    mm::Col3 m_color1;
    float m_values0[5];
    float m_values1[5];
    float m_values2[5];
    float m_value0;
    float m_value1;
    float m_value2;
    float m_keyFrames[4];  // the keys' times in frames (up to the last nonzero one)
    float m_keyFades[4];   // 1 - each key's fade ratio
};

}  // namespace fw

#endif

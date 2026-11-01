#ifndef ML_DRFOGMAN_H
#define ML_DRFOGMAN_H

#include "mm/Col3.h"

namespace ml { class DrMan; }
namespace ml { class DrFogObjGbl; }

namespace ml {
// Not polymorphic: the constructor stores no table. Only what its functions in DrEnvironmentAnim.cpp read is
// declared; the field names are not the original's.
class DrFogMan {
public:
    DrFogMan(DrMan* drMan);
    ~DrFogMan();
    void releaseAll();
    void update();
    bool isFogOn() const;

    DrMan* m_drMan;  // 0x0, the constructor stores its argument
    DrFogObjGbl* m_head;  // 0x8, releaseAll deletes the list from here
    DrFogObjGbl* m_tail;  // 0x10
    // 0x18..0x60: update copies them from the first DrFogObjGbl's 0x20..0x68
    mm::Col3 m_color;  // 0x18, constructor 0.5f
    mm::Col3 m_sideColor;  // 0x24
    mm::Col3 m_sunColor;  // 0x30
    float m_near;  // 0x3C, constructor 0.1f
    float m_far;  // 0x40, constructor 10000.0f
    float m_str;  // 0x44
    float m_parmA;  // 0x48
    float m_pow;  // 0x4C
    float m_parmB[4];  // 0x50
    unsigned char pad_60[0x70];
    bool m_fogOn;  // 0xD0, isFogOn (the constructor clears it)
    bool m_enable;  // 0xD1, the constructor sets it
};
}  // namespace ml

#endif

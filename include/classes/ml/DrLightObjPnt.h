#ifndef CLASSES_ML_DRLIGHTOBJPNT_H
#define CLASSES_ML_DRLIGHTOBJPNT_H

#include "classes/ml/DrLightObj.h"

namespace mm { class Vec3; }
namespace mm { class Mat44; }

namespace ml {
// table 0x7100B7B5A8
class DrLightObjPnt : public ::ml::DrLightObj {
public:
    virtual ~DrLightObjPnt();  // slot 0


    // 1.0.0 has both out of line; 3.0.1 only inlines them into the destructor
    void releasePnt();
    void deletePntShadow();
    void setMat(const mm::Mat44& mtx);
    void setPos(const mm::Vec3& pos);

    unsigned char pad_30[0x40];
    // the names below are not the original's (DrShdLgtTileBasedDr::stockPntList copies them into its light entry)
    float m_pos[3];  // 0x70, transformed by the view matrix
    unsigned char pad_7c[0x14];
    float m_color[3];  // 0x90
    float m_size;  // 0x9C, set by DrEnvironmentAnim::envlgt_pnt_size (the name is not the original's)
    bool m_bLightFlag;  // 0xA0, packed into bit 31 of the entry's word 10
    unsigned char pad_a1[0x3];
    float m_lightParam;  // 0xA4, the entry's last word
    unsigned char pad_a8[0x8];
    float m_speIntensity;  // 0xB0, set by DrEnvironmentAnim::envlgt_pnt_spe_Intensity (the name is not the original's)
    float m_lightParam2;  // 0xB4, the entry's word 3
    float m_lightRate;  // 0xB8, times 255 in the low 31 bits of the entry's word 10
};
}  // namespace ml

#endif

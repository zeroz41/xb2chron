#ifndef CLASSES_ML_DRLIGHTOBJPNT_H
#define CLASSES_ML_DRLIGHTOBJPNT_H

#include "classes/ml/DrLightObj.h"
#include "mm/Col3.h"
#include "mm/Mat44.h"
#include "mm/Vec3.h"

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
    // DrEnvironmentObjLgt::setupPoint's copy of the resource's matrix (inline; DrLightObjDir and DrLightObjSpt have
    // an out-of-line setMat(const float*))
    void setMat(const float* mtx) {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                m_mat.m[i][j] = mtx[i * 4 + j];
            }
        }
        m_pos = m_mat.getTrans();
    }

    // the names below are not the original's (DrShdLgtTileBasedDr::stockPntList copies them into its light entry)
    mm::Mat44 m_mat;  // 0x30, setMat copies it whole; setPos writes its translation row
    // 0x70, transformed by the view matrix. An mm::Vec3 (16-aligned): its copies from setMat/setPos load x and y
    // as one 64-bit word (ldr x; lsr), which only a 16-aligned x allows
    mm::Vec3 m_pos;
    unsigned char pad_80[0x10];
    mm::Col3 m_color;  // 0x90, DrShdLgtMan::renderDebugPnt passes it as renderDebug's mm::Col3
    float m_size;  // 0x9C, set by DrEnvironmentAnim::envlgt_pnt_size (the name is not the original's)
    bool m_bLightFlag;  // 0xA0, packed into bit 31 of the entry's word 10
    unsigned char pad_a1[0x3];
    float m_lightParam;  // 0xA4, the entry's last word
    unsigned char pad_a8[0x4];
    float m_paramC;  // 0xAC, DrEnvironmentObjLgt::setupPoint copies the light's parameter record's +0xC (name inferred)
    float m_speIntensity;  // 0xB0, set by DrEnvironmentAnim::envlgt_pnt_spe_Intensity (the name is not the original's)
    float m_lightParam2;  // 0xB4, the entry's word 3
    float m_lightRate;  // 0xB8, times 255 in the low 31 bits of the entry's word 10
};
}  // namespace ml

#endif

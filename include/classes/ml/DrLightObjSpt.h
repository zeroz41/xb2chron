#ifndef CLASSES_ML_DRLIGHTOBJSPT_H
#define CLASSES_ML_DRLIGHTOBJSPT_H

#include "classes/ml/DrLightObj.h"
#include "mm/Col3.h"
#include "mm/Mat44.h"
#include "mm/Vec3.h"

namespace ml {
// table 0x7100B7B5D0
class DrLightObjSpt : public ::ml::DrLightObj {
public:
    virtual ~DrLightObjSpt();  // slot 0


    // 1.0.0 has both out of line; 3.0.1 only inlines them into the destructor
    void releaseSpt();
    void deleteSptShadow();
    void setMat(const mm::Mat44& mtx);
    void setMat(const float* mtx);
    void setPos(const mm::Vec3& pos);

    // the names below are not the original's
    mm::Mat44 m_mat;  // 0x30, setMat copies it whole; setPos writes its translation row
    mm::Vec3 m_pos;  // 0x70, setMat's translation row
    unsigned char pad_80[0x10];
    mm::Vec3 m_dir;  // 0x90, setMat's -z axis, normalized
    unsigned char pad_a0[0x10];
    // 0xB0, set by fw::EffectManager::setLgtParam; DrShdLgtMan::renderDebugSpt passes it as renderDebug's mm::Col3
    // (the name is not the original's)
    mm::Col3 m_color;
    float m_angle;  // 0xBC, set by DrEnvironmentAnim::envlgt_spt_angle (the name is not the original's)
    float m_size;  // 0xC0, set by DrEnvironmentAnim::envlgt_spt_size (the name is not the original's)
    unsigned char pad_c4[0x4];
    float m_lightParam;  // 0xC8, set by fw::EffectManager::setLgtParam (the name is not the original's)
    unsigned char pad_cc[0x4];
    float m_paramC;  // 0xD0, DrEnvironmentObjLgt::setupSpot copies the light's parameter record's +0xC (name inferred)
    float m_speIntensity;  // 0xD4, set by DrEnvironmentAnim::envlgt_spt_spe_Intensity (the name is not the original's)
    float m_falloff;  // 0xD8, setupSpot copies the parameter record's +0x1C, 4 when not above 0 (name inferred)
    float m_lightParam2;  // 0xDC, set by fw::EffectManager::setLgtParam (the name is not the original's)
    float pad_e0;  // set by fw::EffectManager::setLgtParam
    float m_spotParam;  // 0xE4, setupSpot copies the parameter record's +0x14 (name inferred)
    unsigned char pad_e8[0x8];  // DrLightMan::createInstantSptLight allocates 0xF0
};
}  // namespace ml

#endif

#ifndef ML_DRLIGHTOBJGLOBALIBL_H
#define ML_DRLIGHTOBJGLOBALIBL_H

#include "grlib/CGLibTextureBuffer.h"
#include "mm/Mat44.h"
#include "mm/Vec3.h"

namespace ml {
// A global IBL light (DrGlobalIBLPack::resourceInit makes them). Only what DrRequetIBL's getters read is declared;
// the field names follow those getters (DrRequetIBL::getVersion, getTextureNum, getTexture, getAdditionalAmbient,
// getSkyIntensity, getDirLightIntensity, getSHMatrix) and are not the original's.
class DrLightObjGlobalIBL {
public:
    DrLightObjGlobalIBL();
    ~DrLightObjGlobalIBL();
    unsigned int getPriority() const;

    unsigned char pad_0[0x8];
    unsigned int m_version;  // 0x8
    unsigned int m_priority;  // 0xC, getPriority (the name follows it)
    unsigned char pad_10[0x4];
    unsigned int m_textureNum;  // 0x14
    unsigned char pad_18[0x60];
    grlib::CGLibTextureBuffer m_texture[7];  // 0x78, the constructor builds seven
    unsigned char pad_388[0x18];
    mm::Vec3 m_additionalAmbient;  // 0x3A0
    float m_skyIntensity;  // 0x3B0
    float m_dirLightIntensity;  // 0x3B4
    unsigned char pad_3b8[0x488];
    mm::Mat44 m_shMatrix[4];  // 0x840, by index * 4 + term (getSHMatrix); the bound is not proven
};
}  // namespace ml

#endif

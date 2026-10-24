#ifndef ML_MDOWRKMATRES_H
#define ML_MDOWRKMATRES_H

#include "mm/Col3.h"

namespace grlib { class CGLibTextureBuffer; }

namespace ml {
class DrResMdoMat;
struct MdsMatInfoHeader;

// The material callback list DrMdoMat::updateMatCallBack walks; offsets are from MdoWrkMatRes::m_pMatData. The
// type and field names are not the original's.
struct MdsMatCallBackTbl {
    unsigned int m_callOfs;  // 0x0, (s_pCallMatVal index, uniform slot) u16 pairs; a material's start at m_callBackIdx
    unsigned int pad_4;
    unsigned int m_matListOfs;  // 0x8, u16 material indices
    int m_matListNum;  // 0xC
};

// The per-model accent values DrMdlObj::setAceColor / setAceVal write (1.0.0 names those setters); the type name
// and the field names are not the original's.
struct MdoWrkMatAce {
    mm::Col3 m_color[4];  // 0x00, setAceColor(int, const mm::Col3&)
    float m_val[4];  // 0x30, setAceVal(int, float)
};

// ml::MdoWrkMatRes is 1.0.0's name (DrMdoCtlSeamInstMap::beginResAll(MdoWrkMatRes*) stores its argument at
// DrMdoMat+0x30). Only the fields DrMdoMat's material callbacks use are known; their names are not the original's.
// A model's avatar textures (1.0.0's ScnObjAccResAvatar::resetAvatarTexture(i) puts the dummy texture in
// m_faceTex[i] and clears bit 16+i of the first word). The type and field names are not the original's.
struct MdoWrkAvatarTbl {
    unsigned int m_flags;  // 0x0
    unsigned char pad_4[0x4];
    grlib::CGLibTextureBuffer* m_faceTex[2];  // 0x8, varStTex_AvatarFaceMap1/2
    unsigned char pad_18[0x10];
    grlib::CGLibTextureBuffer* m_eyeTex;  // 0x28, varStTex_AvatarEyeTex
};

struct MdoWrkMatRes {
    unsigned char pad_0[0x10];
    const unsigned char* m_pMatData;  // 0x10, base of the offsets in m_pCallBackTbl
    unsigned char pad_18[0x10];
    const MdsMatInfoHeader* m_pMatInfo;  // 0x28, DrMdlObj::getMaterialHeader returns it
    int m_matNum;  // 0x30, ... and this as the count
    unsigned char pad_34[0x4];
    float* m_pMatVal;  // 0x38, the material values the callbacks read
    const MdsMatCallBackTbl* m_pCallBackTbl;  // 0x40, read by DrMdoMat::updateMatCallBack
    unsigned char pad_48[0x78];
    DrResMdoMat* m_pResMat;  // 0xC0, DrMdlObj::getMaterialRes(int) returns &m_pResMat[i]
    unsigned char pad_C8[0x30];
    float* m_pUniformVal;  // 0xF8, the uniform values the callbacks write
    unsigned char pad_100[0x10];
    MdoWrkAvatarTbl* m_pAvatarTbl;  // 0x110, DrMdoSetup::varStTex_Avatar* bind its textures
    MdoWrkMatAce* m_pAce;  // 0x118
};
}  // namespace ml

#endif

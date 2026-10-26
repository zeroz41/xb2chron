#ifndef ML_MDOWRKMATRES_H
#define ML_MDOWRKMATRES_H

#include "mm/Col3.h"

#include "grlib/CGLibUniformArray.h"

namespace grlib { class CGLibDblUniformBlock; }
namespace grlib { class CGLibOneUniformBlock; }

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
    unsigned char pad_30[0x10];
    grlib::CGLibOneUniformBlock* m_charBlock;  // 0x40, DrMdoSetup::uniformBlock_AvatarChar binds it
    grlib::CGLibOneUniformBlock* m_dollBlock;  // 0x48, DrMdoSetup::uniformBlock_AvatarDoll binds it
};

// The model data MdoWrkMatRes+0x20 points to: ScnObjAccResSubMesh's constructor adds m_subMeshOfs to its address.
// The type and field names are not the original's.
struct MdoMdlData {
    unsigned int m_flags;  // 0x0, 0x2000: DrMdoMat::getVanishEffectMax reads m_vanishEffectMax
    unsigned char pad_4[0x60];
    unsigned int m_subMeshOfs;  // 0x64
    unsigned char pad_68[0x2C];
    unsigned char m_vanishEffectMax;  // 0x94, DrMdoMat::getVanishEffectMax returns at least 1
};

// One volume fade (vanish effect) work entry, 0xE0 bytes: DrMdoMat::getVanishEffectWrk(index, bank) returns entry
// index * 3 + bank of the array at MdoWrkMatRes+0x158 (banks: DrMan::s_nDblIdx, s_nDblStockIdx, 2). The type and
// field names are not the original's.
struct MdoVanishEffectWrk {
    unsigned char pad_0[0xA4];
    float m_ratio;  // 0xA4, ScnObjAccVolumeFade::setRatio/getRatio
    int m_volumeTexIdx;  // 0xA8, DrMdoSetup::varStTex_VolumeTex00 binds DrIniSys::m_texture[7 + this] (bank 2)
    unsigned char pad_AC[0x28];
    unsigned int m_flags;  // 0xD4, 0x100: m_ratio was set
    unsigned char pad_D8[0x8];
};

// One rim bloom work entry, 0x20 bytes: DrMdlObj::getRimBloomWrk(bank) returns entry bank of the array at
// MdoWrkMatRes+0x160. The type and field names are not the original's.
struct MdoRimBloomWrk {
    mm::Col3 m_color;  // 0x0
    float m_power;  // 0xC
    float m_blackRatio;  // 0x10
    float m_emissive;  // 0x14
    unsigned char pad_18[0x4];
    unsigned int m_flags;  // 0x1C, which values were set: 1 color, 2 power, 4 black ratio, 8 emissive
};

// The initial vertex bounds MdoWrkMatRes+0x170 points to, unaligned float triples: DrMdlObj::getInitialVertexAABBMax
// reads 0xC, getInitialVertexAABBMin 0x18. The type and field names are not the original's.
struct MdoInitialVertexAABB {
    unsigned char pad_0[0xC];
    float m_max[3];  // 0xC
    float m_min[3];  // 0x18
};

struct MdoWrkMatRes {
    unsigned char pad_0[0x10];
    const unsigned char* m_pMatData;  // 0x10, base of the offsets in m_pCallBackTbl
    unsigned char pad_18[0x8];
    const MdoMdlData* m_pMdlData;  // 0x20
    const MdsMatInfoHeader* m_pMatInfo;  // 0x28, DrMdlObj::getMaterialHeader returns it
    int m_matNum;  // 0x30, ... and this as the count
    unsigned char pad_34[0x4];
    float* m_pMatVal;  // 0x38, the material values the callbacks read
    const MdsMatCallBackTbl* m_pCallBackTbl;  // 0x40, read by DrMdoMat::updateMatCallBack
    unsigned char pad_48[0x48];
    // 0x90, per-material blocks: DrMdoSetup::uniformBlock_Material binds the material's (the name is not the original's)
    grlib::CGLibUniformArray<grlib::CGLibDblUniformBlock>* m_pMatUniformArray;
    unsigned char pad_98[0x8];
    // 0xA0: DrResMdoSeamWrkEnv::setupWork hands it the triangle uniform array; the name is not the original's
    grlib::CGLibTriUniformArray* m_pTriUniformArray;
    unsigned char pad_A8[0x8];
    // 0xB0 and 0xB8: DrMdoSetup::uniformBlock_VolTexCalc and uniformBlock_RimBloomCalc bind one of their blocks
    // (the names are not the original's)
    grlib::CGLibUniformArray<grlib::CGLibDblUniformBlock>* m_pVolTexUniformArray;
    grlib::CGLibUniformArray<grlib::CGLibDblUniformBlock>* m_pRimBloomUniformArray;
    DrResMdoMat* m_pResMat;  // 0xC0, DrMdlObj::getMaterialRes(int) returns &m_pResMat[i]
    unsigned char pad_C8[0x30];
    float* m_pUniformVal;  // 0xF8, the uniform values the callbacks write
    unsigned char pad_100[0x10];
    MdoWrkAvatarTbl* m_pAvatarTbl;  // 0x110, DrMdoSetup::varStTex_Avatar* bind its textures
    MdoWrkMatAce* m_pAce;  // 0x118
    unsigned char pad_120[0x38];
    MdoVanishEffectWrk* m_pVanishEffectWrk;  // 0x158, three banks per material (DrMdoMat::getVanishEffectWrk)
    MdoRimBloomWrk* m_pRimBloomWrk;  // 0x160, DrMdlObj::getRimBloomWrk (the name is not the original's)
    unsigned char pad_168[0x8];
    MdoInitialVertexAABB* m_pInitialAABB;  // 0x170 (the name is not the original's)
};
}  // namespace ml

#endif

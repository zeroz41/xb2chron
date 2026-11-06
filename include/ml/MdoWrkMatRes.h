#ifndef ML_MDOWRKMATRES_H
#define ML_MDOWRKMATRES_H

#include "mm/Col3.h"

#include "grlib/CGLibUniformArray.h"

namespace grlib { class CGLibDblUniformBlock; }
namespace grlib { class CGLibOneUniformBlock; }

namespace grlib { class CGLibTextureBuffer; }
namespace grlib { class CGLibSampler; }

namespace ml {
class DrResMdoMat;
class DrResMdoSampler;
class DrResMdoTexList;
class DrResMdoVertex;
class DrResMpfSampler;
class DrShdMdoDecShdObj;
struct MdsMatInfoHeader;
struct MdsFixAnmInf;
struct MdsMatTechnique;
struct MdsFixAnmKey;

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
    unsigned char pad_30[0x8];
    // 0x38: while set, DrMdoMat::updateAvatarTbl writes alpha 0 into the doll colours instead of 1 (the name is
    // not the original's)
    unsigned char m_dollAlphaOff;
    unsigned char pad_39[0x7];
    grlib::CGLibOneUniformBlock* m_charBlock;  // 0x40, DrMdoSetup::uniformBlock_AvatarChar binds it
    grlib::CGLibOneUniformBlock* m_dollBlock;  // 0x48, DrMdoSetup::uniformBlock_AvatarDoll binds it
    // m_charBlock and m_dollBlock each hold sixteen mm::Col4 (DrMdoMat::setupAvatarTbl fills them)
};

// The model data MdoWrkMatRes+0x20 points to: ScnObjAccResSubMesh's constructor adds m_subMeshOfs to its address.
// The type and field names are not the original's.
// The model's node (bone) table at MdoMdlData + m_nodeTblOfs: m_entryOfs (from the table) leads to the 0x18-byte
// entries, each naming its node by an offset from the table (DrMdoNode::getNodeName/getNodeIdx). The names are not the
// original's.
struct MdsNodeEntry {
    unsigned int m_nameOfs;
    unsigned char pad_4[0x14];
};
struct MdsNodeTable {
    unsigned char pad_0[0x8];
    unsigned int m_entryOfs;  // 0x8
};

struct MdoMdlData {
    unsigned int m_flags;  // 0x0, 0x2000: DrMdoMat::getVanishEffectMax reads m_vanishEffectMax
    unsigned char pad_4[0x24];
    unsigned int m_nodeTblOfs;  // 0x28, from this header (the name is not the original's)
    unsigned char pad_2C[0x28];
    // 0x54: DrMdoCtlMpf::setupMpf keeps a 4-byte render list entry per one (the name is not the original's)
    unsigned int m_infoTotal;
    unsigned char pad_58[0xC];
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

// One model top header, 0x44 bytes (the type name is the symbols': DrMdoCtlNom::nomRender(const MdsMdlTopHeader*, ...)
// is given &MdoWrkMatRes::m_pMdlTop[i]). Its bounds are unaligned float triples: DrMdlObj::getInitialVertexAABBMax
// reads the first header's 0xC, getInitialVertexAABBMin 0x18. The field names are not the original's.
struct MdsMdlTopHeader {
    // 0x0: from MdoWrkMatRes::m_pMdlInfo, this header's MdsMdlInfoHeader array (DrMdoCtlNom::shwRender)
    unsigned int m_infoOfs;
    // 0x4: how many MdsMdlInfoHeaders follow m_infoOfs (DrMdoCtlSeamEnvMap's passes walk them; the name is not the
    // original's)
    unsigned int m_infoNum;
    unsigned char pad_8[0x4];
    float m_max[3];  // 0xC
    float m_min[3];  // 0x18
    unsigned char pad_24[0x20];
};

// One model part, 0x30 bytes (the struct name is from DrMdoCtl::partsShadowRender's mangling): the check lists of
// DrMdoCtlNom's passes index a top header's array of them. The field names are not the original's.
struct MdsMdlInfoHeader {
    unsigned int m_flags;  // 0x0, bit 8: m_meshNo names a DrResMdoMeshObj part
    union {
        // 0x4 as one word: DrMdoCtlSeamInstMap::createInstThicknessPassDisplayList tests bit 15 (m_shadowFlags bit 7)
        // through a byte load the backend narrows from it (the name is not the original's)
        unsigned int m_drawFlags;
        struct {
            // 0x4: the passes the part is drawn in; DrMdoCtlSeamEnvMap's passes test bit 0 (render), 3 (gbuffer),
            // 5 (light pre-pass), 1 (alpha), 6 (sp alpha), 2 (refraction). The name is not the original's.
            unsigned char m_passFlags;
            // 0x5, bit 6: the part casts a shadow (DrMdoCtl::partsShadowBaseRender and the partsPos*ShadowRender
            // passes draw only these; the name is not the original's)
            unsigned char m_shadowFlags;
            unsigned char pad_6[0x2];
        };
    };
    // 0x8: the DrResMdoVertex bind entry (setVertexBind's index); 0xA/0xC: the DrResMdoVertex::render index, 0xC
    // while m_flags bit 13 is set (the names are not the original's)
    unsigned short m_vtxBindIdx;
    unsigned short m_renderIdx[2];
    // 0xE: index into MdoWrkMatRes::m_pResMat; the part is drawn while that material's alpha is above 0 (the name
    // is not the original's)
    unsigned short m_matIdx;
    unsigned char pad_10[0x6];
    unsigned short m_meshNo;  // 0x16
    unsigned char pad_18[0x4];
    unsigned short m_shaderOfs;  // 0x1C, added to the shadow shader index (plus 1 with nodes) when there is no part
    unsigned char pad_1E[0x12];
};

// The material data MdoWrkMatRes::m_pMatData points to; only the offset DrMdoShdSet::setOneTexShaderSet reads is
// known. The type and field names are not the original's.
struct MdsMatDataHeader {
    unsigned char pad_0[0x3C];
    unsigned int m_texEntryOfs;  // 0x3C, from the header's start: the MdsMatTexEntry array
};
// One texture entry of the material data, 8 bytes: DrMdoShdSet::setOneTexShaderSet binds texture m_texIdx with
// sampler m_samplerMip when the texture has mipmaps, else m_samplerNoMip. The type and field names are not the
// original's.
struct MdsMatTexEntry {
    unsigned short m_texIdx;        // 0x0, index into MdoWrkMatRes::m_ppTexture
    unsigned short m_samplerMip;    // 0x2
    unsigned short m_samplerNoMip;  // 0x4
    unsigned short pad_6;
};
// One material's avatar map entry, 4 bytes: three indices into DrMdoMat::m_pAvatarColor (DrMdoSetup::
// unimate_AvatarMapWrk). The type and field names are not the original's.
struct MdsMatAvatarMap {
    unsigned char m_colorIdx[3];
    unsigned char pad_3;
};
// The flag wave data DrMdoMat::getFlagWaveRes reads (the type and field names are not the original's).
struct MdsFlagWaveHeader {
    unsigned int m_dataOfs;  // 0x0, from the header's base
    unsigned int m_paramOfs;  // 0x4, m_num 0x30-byte wave parameters
    int m_num;  // 0x8
};
// The flag wave work DrMdoMat::getFlagWaveRes builds in its buffer: this, m_num phases and the uniform array (one
// triple-buffered block per wave); updateFlagWaveTbl animates it. The type and field names are not the original's.
struct MdoFlagWaveRes {
    // 0x0: the wave block index per material (DrMdoShdSetPrePass::preshd_Fw* bind m_pUniformArray's block by it)
    const unsigned short* m_pData;
    const unsigned char* m_pParam;  // 0x8
    int m_num;  // 0x10
    bool m_first;  // 0x14, updateFlagWaveTbl copies the first frame into the old buffer too
    grlib::CGLibTriUniformArray* m_pUniformArray;  // 0x18, after the phases
    float* m_pPhase;  // 0x20, at 0x28: a random phase in [0, 100) per wave
};
// The material block of a seam instance map's data (MdsSeamInstMapHead::m_dataOfs[2]); the names are not the
// original's
struct MdsSeamInstMatBlock {
    unsigned char pad_0[0x14];
    unsigned int m_ofs0;  // 0x14
    unsigned char pad_18[0x4];
    unsigned int m_ofs1;  // 0x1C
    unsigned char pad_20[0x4];
    unsigned int m_ofs2;  // 0x24
};
struct MdoWrkMatRes {
    const MdsMatTexEntry* getTexEntries() const {
        return reinterpret_cast<const MdsMatTexEntry*>(
            m_pMatData + reinterpret_cast<const MdsMatDataHeader*>(m_pMatData)->m_texEntryOfs);
    }

    // 0x0 and 0x8: the vertex and texture data DrMdoMat::setupMpfResource gets the resources of (the names are not
    // the original's)
    const unsigned char* m_pVertexData;
    const unsigned char* m_pTexData;
    const unsigned char* m_pMatData;  // 0x10, base of the offsets in m_pCallBackTbl
    // 0x18: base of MdsMdlTopHeader::m_infoOfs (the name is not the original's)
    const unsigned char* m_pMdlInfo;
    const MdoMdlData* m_pMdlData;  // 0x20
    const MdsMatInfoHeader* m_pMatInfo;  // 0x28, DrMdlObj::getMaterialHeader returns it
    int m_matNum;  // 0x30, ... and this as the count
    unsigned char pad_34[0x4];
    float* m_pMatVal;  // 0x38, the material values the callbacks read
    const MdsMatCallBackTbl* m_pCallBackTbl;  // 0x40, read by DrMdoMat::updateMatCallBack
    // 0x48, by MdsMatInfoHeader::m_avatarMapIdx: DrMdoSetup::unimate_AvatarMapWrk's colour indices (the name is not
    // the original's)
    const MdsMatAvatarMap* m_pAvatarMap;
    // 0x50: a seam instance map's MdsSeamInstMatBlock (DrMdoCtlSeamInstMap::initInstMapParts) (the name is not the
    // original's)
    const unsigned char* m_pSeamMatBlock;
    // 0x58/0x60: the fixed animation's values and keys (DrMdoAnim::calcAnim, getHermiteAttr); seam instance maps
    // point them and 0x68 into their block (the names are not the original's)
    const MdsFixAnmInf* m_pFixAnmInf;
    const MdsFixAnmKey* m_pFixAnmKey;
    const unsigned char* m_pSeamMatData;
    // 0x70: the material techniques; 0x78: the data their offsets start from (DrMdoSetup::createUniformBlock) (the
    // names are not the original's)
    const MdsMatTechnique* m_pTechnique;
    const unsigned char* m_pTechData;
    // 0x80: the material's shader object; DrMdoMat::release*SeamMat delete it (the name is not the original's)
    DrShdMdoDecShdObj* m_pDecShdObj;
    // 0x88: cleared together with m_pDecShdObj (the name and the type are not the original's)
    const void* m_pDecShdData;
    // 0x90, per-material blocks: DrMdoSetup::uniformBlock_Material binds the material's (the name is not the original's)
    grlib::CGLibUniformArray<grlib::CGLibDblUniformBlock>* m_pMatUniformArray;
    unsigned char pad_98[0x8];
    // 0xA0: DrResMdoSeamWrkEnv::setupWork hands it the triangle uniform array; the name is not the original's
    grlib::CGLibTriUniformArray* m_pTriUniformArray;
    // 0xA8: DrMdoCtl::partsShadowRender binds it through DrResMdoVertex::setMofBlendVertexBind for parts with
    // MdsMdlInfoHeader::m_flags bit 24 (the name is not the original's)
    grlib::CGLibOneUniformArray* m_pMofBlendArray;
    // 0xB0 and 0xB8: DrMdoSetup::uniformBlock_VolTexCalc and uniformBlock_RimBloomCalc bind one of their blocks
    // (the names are not the original's)
    grlib::CGLibUniformArray<grlib::CGLibDblUniformBlock>* m_pVolTexUniformArray;
    grlib::CGLibUniformArray<grlib::CGLibDblUniformBlock>* m_pRimBloomUniformArray;
    DrResMdoMat* m_pResMat;  // 0xC0, DrMdlObj::getMaterialRes(int) returns &m_pResMat[i]
    // 0xC8: the vertex resource being set up; DrResMdoSeamWrkBase::selectVertex switches it (the name is not the
    // original's)
    DrResMdoVertex* m_pVertex;
    DrResMdoTexList* m_pTexList;  // 0xD0 (the name is not the original's)
    // 0xD8: in DrMdoSamplerMan's list (DrMdoMat::release*SeamMat unlink and delete it); DrMdoShdSet::
    // setOneTexShaderSet indexes its samplers by MdsMatTexEntry::m_samplerMip/m_samplerNoMip (the name is not the
    // original's)
    DrResMdoSampler* m_pSampler;
    // 0xE0: one per material (m_matNum), destroyed in place by DrMdoMat::releaseMpfMapSeamMat (the name is not the
    // original's)
    DrResMpfSampler* m_pMpfSampler;
    // 0xE8: one texture per index; DrMdoShdSetMpf::mpfshd_drw_* bind MdsMpfMatInfoHeader::m_texIdx's (the name is
    // not the original's)
    grlib::CGLibTextureBuffer** m_ppTexture;
    int m_texNum;  // 0xF0, setupMpfResource gets the texture list only when it is set (the name is not the original's)
    unsigned char pad_F4[0x4];
    float* m_pUniformVal;  // 0xF8, the uniform values the callbacks write
    // 0x100: by MdsFixAnmInf, its current frame; DrMdoAnim::calcAnim advances it (the name is not the original's)
    float* m_pFixAnmFrame;
    unsigned char pad_108[0x8];
    MdoWrkAvatarTbl* m_pAvatarTbl;  // 0x110, DrMdoSetup::varStTex_Avatar* bind its textures
    MdoWrkMatAce* m_pAce;  // 0x118
    // 0x120: DrMdoMat::release*SeamMat release the uniform array at its +8 (the type and the name are not the
    // original's)
    struct ExtUniform {
        void* pad_0;
        grlib::CGLibUniformArray<grlib::CGLibDblUniformBlock>* m_pUniformArray;  // 0x8
    }* m_pExtUniform;
    unsigned char pad_128[0x18];
    MdoFlagWaveRes* m_pFlagWave;  // 0x140, DrMdoMat::getFlagWaveRes (the name is not the original's)
    unsigned char pad_148[0x10];
    MdoVanishEffectWrk* m_pVanishEffectWrk;  // 0x158, three banks per material (DrMdoMat::getVanishEffectWrk)
    MdoRimBloomWrk* m_pRimBloomWrk;  // 0x160, DrMdlObj::getRimBloomWrk (the name is not the original's)
    unsigned char pad_168[0x8];
    // 0x170/0x178: the model's top headers and their count; DrMdoCtlNom's alpha passes walk them (the names are not
    // the original's)
    const MdsMdlTopHeader* m_pMdlTop;
    int m_mdlTopNum;
    unsigned char pad_17C[0x4];
};
}  // namespace ml

#endif

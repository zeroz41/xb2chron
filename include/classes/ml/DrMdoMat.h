#ifndef CLASSES_ML_DRMDOMAT_H
#define CLASSES_ML_DRMDOMAT_H

#include "classes/ml/DrMdlBase.h"
#include "mm/Col3.h"
#include "mm/Mat44.h"
#include "mm/Vec3.h"

namespace ml { class DrMan; }
namespace ml { class DrShdMdoDecExtTbl; }
namespace ml { class DrMdoSmlShadowObj; }
namespace ml { struct MdoWrkMatRes; }
namespace ml { struct MdoVanishEffectWrk; }
namespace ml { struct MdsMatInfoHeader; }
namespace ml { struct MdsMatTopHeader; }

namespace ml {
// table 0x7100B7BD30
class DrMdoMat : public ::ml::DrMdlBase {
public:
    // inline in DrMdoCtl's constructor (1.0.0's DrMdoNode and DrMdoCtl constructors store its table first)
    explicit DrMdoMat(int viewNum)
        : DrMdlBase(viewNum), m_pWrkMatRes(nullptr), m_matrix(mm::Mat44::identity), m_offsetPos(0.0f, 0.0f, 0.0f),
          pad_C0(0.0f, 0.0f, 0.0f), m_colorScale(1.0f), m_speed(1.0f), m_singleAlpha(1.0f), m_outLineDist(0.0f) {
        m_alpha[0] = 1.0f;
        m_alpha[1] = 1.0f;
        // the original zeroes 0x40..0x70 after the identity copy (the body, not the initializer list)
        m_pAvatarColor = nullptr;
        pad_48 = nullptr;
        m_pResData = nullptr;
        m_pSmlShadowObj = nullptr;
        m_pNodeMats[0] = nullptr;
        m_pNodeMats[1] = nullptr;
    }
    virtual ~DrMdoMat() {}  // slot 0

    void updateMatCallBack(const unsigned int* dispBits);
    // DrMdoCtlSeamRead::waitMpfMdlStream passes four blocks of an MdsSeamMpfMapHead (the return type is not known)
    void initMpfMaterial(const unsigned char*, const unsigned char*, const unsigned char*, const unsigned char*, bool);

    // Material value callbacks: s_pCallMatVal[id] is called with the material's header, the uniform slot (from
    // info->m_uniformOfs) the callback fills and the material's index.
    void matCall_MatxView(const MdsMatInfoHeader* info, int slot, int matIdx);
    void matCall_EmissiveTime(const MdsMatInfoHeader* info, int slot, int matIdx);
    void matCall_RgbTime(const MdsMatInfoHeader* info, int slot, int matIdx);
    void matCall_RTime(const MdsMatInfoHeader* info, int slot, int matIdx);
    void matCall_AccRgb1(const MdsMatInfoHeader* info, int slot, int matIdx);
    void matCall_AccRgb2(const MdsMatInfoHeader* info, int slot, int matIdx);
    void matCall_AccRgb3(const MdsMatInfoHeader* info, int slot, int matIdx);
    void matCall_AccRgb4(const MdsMatInfoHeader* info, int slot, int matIdx);
    void matCall_AccMulRgb1(const MdsMatInfoHeader* info, int slot, int matIdx);
    void matCall_AccMulRgb2(const MdsMatInfoHeader* info, int slot, int matIdx);
    void matCall_AccMulRgb3(const MdsMatInfoHeader* info, int slot, int matIdx);
    void matCall_AccMulRgb4(const MdsMatInfoHeader* info, int slot, int matIdx);
    void matCall_AccVal1(const MdsMatInfoHeader* info, int slot, int matIdx);
    void matCall_AccVal2(const MdsMatInfoHeader* info, int slot, int matIdx);
    void matCall_AccVal3(const MdsMatInfoHeader* info, int slot, int matIdx);
    void matCall_AccVal4(const MdsMatInfoHeader* info, int slot, int matIdx);
    void matCall_AccMulVal1(const MdsMatInfoHeader* info, int slot, int matIdx);
    void matCall_AccMulVal2(const MdsMatInfoHeader* info, int slot, int matIdx);
    void matCall_AccMulVal3(const MdsMatInfoHeader* info, int slot, int matIdx);
    void matCall_AccMulVal4(const MdsMatInfoHeader* info, int slot, int matIdx);
    void matCall_WaterFog(const MdsMatInfoHeader* info, int slot, int matIdx);
    void matCall_MatxInvView(const MdsMatInfoHeader* info, int slot, int matIdx);
    void matCall_FurShader(const MdsMatInfoHeader* info, int slot, int matIdx);
    void matCall_CalcBloom(const MdsMatInfoHeader* info, int slot, int matIdx);
    void matCall_CalcColor(const MdsMatInfoHeader* info, int slot, int matIdx);
    void matCall_OutLineVal(const MdsMatInfoHeader* info, int slot, int matIdx);
    void matCall_ToonId(const MdsMatInfoHeader* info, int slot, int matIdx);
    void matCall_VolumeTest(const MdsMatInfoHeader* info, int slot, int matIdx);
    void matCall_BaseColor(const MdsMatInfoHeader* info, int slot, int matIdx);
    void matCall_BaseVal(const MdsMatInfoHeader* info, int slot, int matIdx);
    void matCall_TransVal(const MdsMatInfoHeader* info, int slot, int matIdx);
    // 2.0.0's symbols name them. What they do: large material-value callbacks (0xEB4, 0x10A0, 0x5B38 and 0xF8 bytes)
    // not yet read.
    void matCall_CalcPrjView(const MdsMatInfoHeader* info, int slot, int matIdx);
    void matCall_CalcPrjChgView(const MdsMatInfoHeader* info, int slot, int matIdx);
    void matCall_CalcPrjDefCall(const MdsMatInfoHeader* info, int slot, int matIdx);
    void matCall_CalcPrjAlpha(const MdsMatInfoHeader* info, int slot, int matIdx);

    int getVanishEffectMax() const;
    // DrMdoCtlDammy's destructor releases the material through it
    void releaseMat();
    void setupResource(bool);
    // DrMdoCtlMpf::resourceInit
    void setupMpfResource();
    MdoVanishEffectWrk* getVanishEffectWrk(unsigned int index, unsigned int bank);
    // updates the avatar colour blocks: doll alphas and m_colorScale
    void updateAvatarTbl();
    // fills the avatar colour blocks with their defaults (and the header's first colour)
    void setupAvatarTbl(const MdsMatTopHeader* top);
    // free a seam material's resources: vertex, textures, samplers, shader object and uniform arrays
    void releaseBaseMapSeamMat(MdoWrkMatRes* res);
    void releaseInstMapSeamMat(MdoWrkMatRes* res);
    void initInstMapMaterial(MdoWrkMatRes*& res, const unsigned char*, const unsigned char*, const unsigned char*,
                             const unsigned char*, int);
    void resetInstMapMaterial(MdoWrkMatRes* res, const unsigned char*, const unsigned char*, const unsigned char*,
                              const unsigned char*, int);
    void releaseMpfMapSeamMat(MdoWrkMatRes* res);
    // builds the flag wave work of data + ofs in buf (when given) and hands it to res; returns the bytes it takes
    int getFlagWaveRes(const unsigned char* data, unsigned int ofs, unsigned char* buf, MdoWrkMatRes* res);

    static void (DrMdoMat::*s_pCallMatVal[35])(const MdsMatInfoHeader*, int, int);

    DrMan* m_pDrMan;  // 0x28, set by 1.0.0's setDrMan(DrMan*) (the field name is not the original's)
    MdoWrkMatRes* m_pWrkMatRes;  // 0x30 (the field name is not the original's)
    // 0x38, the uniformBlock_ callbacks ask it for the location of their global parameter (the name is not the
    // original's)
    DrShdMdoDecExtTbl* m_pDecExtTbl;
    // 0x40, zeroed by the constructor: the colours DrMdoSetup::unimate_AvatarMapWrk picks by MdsMatAvatarMap's
    // indices (the name and the element type are not the original's)
    mm::Col3* m_pAvatarColor;
    void* pad_48;
    // 0x50: the resource data DrMdoCtlDammy's constructor is given (the name is not the original's)
    const void* m_pResData;
    // DrMdlObj::chageShadowObject hands it to DrMdoSmlShadowMan::changeViewNum (the name is not the original's)
    DrMdoSmlShadowObj* m_pSmlShadowObj;  // 0x58
    // 0x60, by DrMan::s_nDblStockIdx: the node matrices DrMdoNode::getNodeMatrix/setNodeMatrix index (the name is
    // not the original's)
    mm::Mat44* m_pNodeMats[2];
    mm::Mat44 m_matrix;  // 0x70, DrMdoCtl::setMatrix (the name is not the original's)
    mm::Vec3 m_offsetPos;  // 0xB0, DrMdoCtl::setOffsetPos (the name is not the original's)
    mm::Vec3 pad_C0;  // 0xC0, zeroed by the constructor
    // 0xD0, by s_nDblStockIdx: DrMdlObj::setAlpha/getAlpha while double-buffered alpha is on (the name is not the
    // original's)
    float m_alpha[2];
    float m_colorScale;  // 0xD8, 1.0f from the constructor; scales CalcBloom/CalcColor (name inferred)
    // the effect library's model speed: fw::EffectManager::setMdlSpeed stores it (the name is not the original's)
    float m_speed;
    // 0xE0: DrMdlObj::setAlpha/getAlpha while double-buffered alpha is off (the name is not the original's)
    float m_singleAlpha;
    // 0xE4, matCall_OutLineVal fades the outline between DrPixlPostParm::m_outLineNear and m_outLineFar by it
    // (1.0.0's DrMdoMat reads the same offset there; the name is not the original's)
    float m_outLineDist;
};
}  // namespace ml

#endif

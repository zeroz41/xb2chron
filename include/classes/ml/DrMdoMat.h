#ifndef CLASSES_ML_DRMDOMAT_H
#define CLASSES_ML_DRMDOMAT_H

#include "classes/ml/DrMdlBase.h"

namespace ml { class DrMan; }
namespace ml { class DrShdMdoDecExtTbl; }
namespace ml { class DrMdoSmlShadowObj; }
namespace ml { struct MdoWrkMatRes; }
namespace ml { struct MdoVanishEffectWrk; }
namespace ml { struct MdsMatInfoHeader; }

namespace ml {
// table 0x7100B7BD30
class DrMdoMat : public ::ml::DrMdlBase {
public:
    virtual ~DrMdoMat() {}  // slot 0

    void updateMatCallBack(const unsigned int* dispBits);

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
    // Placeholder names: new in 3.0.1 (s_pCallMatVal slots 31-34; 1.0.0's table has 31 entries), nothing in
    // 1.0.0's place names them. Members because s_pCallMatVal holds them as DrMdoMat member pointers, called by
    // updateMatCallBack like the named matCall_ callbacks. What they do: large material-value callbacks (0xEB4,
    // 0x10A0, 0x5B38 and 0xF8 bytes) not yet read.
    void fn_71007701FC(const MdsMatInfoHeader* info, int slot, int matIdx);
    void fn_71007710B0(const MdsMatInfoHeader* info, int slot, int matIdx);
    void fn_7100772150(const MdsMatInfoHeader* info, int slot, int matIdx);
    void fn_7100777C88(const MdsMatInfoHeader* info, int slot, int matIdx);

    int getVanishEffectMax() const;
    MdoVanishEffectWrk* getVanishEffectWrk(unsigned int index, unsigned int bank);

    static void (DrMdoMat::*s_pCallMatVal[35])(const MdsMatInfoHeader*, int, int);

    DrMan* m_pDrMan;  // 0x28, set by 1.0.0's setDrMan(DrMan*) (the field name is not the original's)
    MdoWrkMatRes* m_pWrkMatRes;  // 0x30 (the field name is not the original's)
    // 0x38, the uniformBlock_ callbacks ask it for the location of their global parameter (the name is not the
    // original's)
    DrShdMdoDecExtTbl* m_pDecExtTbl;
    unsigned char pad_40[0x18];
    // DrMdlObj::chageShadowObject hands it to DrMdoSmlShadowMan::changeViewNum (the name is not the original's)
    DrMdoSmlShadowObj* m_pSmlShadowObj;  // 0x58
    unsigned char pad_60[0x70];
    // 0xD0, by s_nDblStockIdx: DrMdlObj::setAlpha/getAlpha while double-buffered alpha is on (the name is not the
    // original's)
    float m_alpha[2];
    float m_colorScale;  // 0xD8, 1.0f from the constructor; scales CalcBloom/CalcColor (name inferred)
    unsigned char pad_DC[0x4];
    // 0xE0: DrMdlObj::setAlpha/getAlpha while double-buffered alpha is off (the name is not the original's)
    float m_singleAlpha;
    // 0xE4, matCall_OutLineVal fades the outline between DrPixlPostParm::m_outLineNear and m_outLineFar by it
    // (1.0.0's DrMdoMat reads the same offset there; the name is not the original's)
    float m_outLineDist;
};
}  // namespace ml

#endif

#ifndef ML_DRMDOSETUP_H
#define ML_DRMDOSETUP_H

#include "classes/ml/DrMdoMat.h"

namespace ml { struct MdsMatInfoHeader; }

namespace ml {
// A DrMdoMat that sets up a material's shader resources (1.0.0: DrMdoSetup(int) stores DrMdoMat's table, then
// its own; 3.0.1 keeps no table of its own).
class DrMdoSetup : public ::ml::DrMdoMat {
public:
    // Static texture callbacks: s_pStaticTexture[id] binds texture id at the shader location.
    void varStTex_ColorTex(const MdsMatInfoHeader* info, unsigned int location, unsigned int matIdx);
    void varStTex_NormalTex(const MdsMatInfoHeader* info, unsigned int location, unsigned int matIdx);
    void varStTex_LightTex(const MdsMatInfoHeader* info, unsigned int location, unsigned int matIdx);
    void varStTex_DepthTex(const MdsMatInfoHeader* info, unsigned int location, unsigned int matIdx);
    void varStTex_RefTex(const MdsMatInfoHeader* info, unsigned int location, unsigned int matIdx);
    void varStTex_ShadowMap(const MdsMatInfoHeader* info, unsigned int location, unsigned int matIdx);
    void varStTex_AvatarFaceMap1(const MdsMatInfoHeader* info, unsigned int location, unsigned int matIdx);
    void varStTex_Capture1(const MdsMatInfoHeader* info, unsigned int location, unsigned int matIdx);
    void varStTex_Capture2(const MdsMatInfoHeader* info, unsigned int location, unsigned int matIdx);
    void varStTex_Capture3(const MdsMatInfoHeader* info, unsigned int location, unsigned int matIdx);
    void varStTex_Capture4(const MdsMatInfoHeader* info, unsigned int location, unsigned int matIdx);
    void varStTex_RefractionMap(const MdsMatInfoHeader* info, unsigned int location, unsigned int matIdx);
    void varStTex_ColorDepTex(const MdsMatInfoHeader* info, unsigned int location, unsigned int matIdx);
    void varStTex_AvatarFaceMap2(const MdsMatInfoHeader* info, unsigned int location, unsigned int matIdx);
    void varStTex_AvatarEyeTex(const MdsMatInfoHeader* info, unsigned int location, unsigned int matIdx);
    void varStTex_CaptureMain(const MdsMatInfoHeader* info, unsigned int location, unsigned int matIdx);
    void varStTex_BaseColorTex(const MdsMatInfoHeader* info, unsigned int location, unsigned int matIdx);
    void varStTex_SpecularIBLTex(const MdsMatInfoHeader* info, unsigned int location, unsigned int matIdx);
    void varStTex_AmbBRDFTex(const MdsMatInfoHeader* info, unsigned int location, unsigned int matIdx);
    void varStTex_ScreenCapTex(const MdsMatInfoHeader* info, unsigned int location, unsigned int matIdx);
    void varStTex_ToonGradTex(const MdsMatInfoHeader* info, unsigned int location, unsigned int matIdx);
    void varStTex_ToonRimTex(const MdsMatInfoHeader* info, unsigned int location, unsigned int matIdx);
    void varStTex_DitherTex(const MdsMatInfoHeader* info, unsigned int location, unsigned int matIdx);
    void varStTex_RefLightTex(const MdsMatInfoHeader* info, unsigned int location, unsigned int matIdx);
    void varStTex_VolumeTex00(const MdsMatInfoHeader* info, unsigned int location, unsigned int matIdx);
    void varStTex_VolumeTex01(const MdsMatInfoHeader* info, unsigned int location, unsigned int matIdx);
    void varStTex_GlobalIBLIndexTex(const MdsMatInfoHeader* info, unsigned int location, unsigned int matIdx);
    void varStTex_BackFaceDepthTex(const MdsMatInfoHeader* info, unsigned int location, unsigned int matIdx);
    void varStTex_DownDepthTex(const MdsMatInfoHeader* info, unsigned int location, unsigned int matIdx);
    void varStTex_ClusterIdxListTex(const MdsMatInfoHeader* info, unsigned int location, unsigned int matIdx);
    void varStTex_VelocityTex(const MdsMatInfoHeader* info, unsigned int location, unsigned int matIdx);
    void varStTex_RefractionAfterTex(const MdsMatInfoHeader* info, unsigned int location, unsigned int matIdx);
    void varStTex_Movie0(const MdsMatInfoHeader* info, unsigned int location, unsigned int matIdx);
    void varStTex_Movie1(const MdsMatInfoHeader* info, unsigned int location, unsigned int matIdx);
    void varStTex_Movie2(const MdsMatInfoHeader* info, unsigned int location, unsigned int matIdx);
    void varStTex_Movie3(const MdsMatInfoHeader* info, unsigned int location, unsigned int matIdx);
    void varStTex_DiffuseIBL(const MdsMatInfoHeader* info, unsigned int location, unsigned int matIdx);
    void varStTex_DownBaseColorTex(const MdsMatInfoHeader* info, unsigned int location, unsigned int matIdx);
    void varStTex_AOTex(const MdsMatInfoHeader* info, unsigned int location, unsigned int matIdx);
    void varStTex_OrientationTex(const MdsMatInfoHeader* info, unsigned int location, unsigned int matIdx);
    void varStTex_FlagWaveTex0(const MdsMatInfoHeader* info, unsigned int location, unsigned int matIdx);
    void varStTex_FlagWaveTex1(const MdsMatInfoHeader* info, unsigned int location, unsigned int matIdx);
    void varStTex_EtcTex(const MdsMatInfoHeader* info, unsigned int location, unsigned int matIdx);
    void varStTex_ToonDarkGradTex(const MdsMatInfoHeader* info, unsigned int location, unsigned int matIdx);
    // Placeholder names: new in 3.0.1 (s_pStaticTexture slots 44-45; 1.0.0's table has 44 entries), nothing in
    // 1.0.0's place names them. Members because s_pStaticTexture holds them as DrMdoSetup member pointers like the
    // varStTex_ callbacks. What they do: 0x710077C23C binds DrPixlMan::getDepthObj()'s texture at +0x130 (sampling
    // 2, 0); 0x710077C294 binds DrIniSys texture [1] or [2] by bit 2 of this+0xF9 (sampling 2, 0).
    void fn_710077C23C(const MdsMatInfoHeader* info, unsigned int location, unsigned int matIdx);
    void fn_710077C294(const MdsMatInfoHeader* info, unsigned int location, unsigned int matIdx);

    static void (DrMdoSetup::*s_pStaticTexture[46])(const MdsMatInfoHeader*, unsigned int, unsigned int);
};
}  // namespace ml

#endif

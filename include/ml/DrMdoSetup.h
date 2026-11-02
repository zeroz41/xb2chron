#ifndef ML_DRMDOSETUP_H
#define ML_DRMDOSETUP_H

#include "classes/ml/DrMdoMat.h"
#include "mm/Vec3.h"

namespace grlib { class CGLibEtcUniformBlock; }

namespace ml { struct MdsMatInfoHeader; }
namespace ml { struct MdsMatValShaderCate; }
namespace ml { struct MdsMatVariableTbl; }
namespace ml { class DrResMdoMat; }

namespace ml {
// A DrMdoMat that sets up a material's shader resources (1.0.0: DrMdoSetup(int) stores DrMdoMat's table, then
// its own; 3.0.1 keeps no table of its own). DrMdoNode derives from it: 1.0.0's DrMdoSetup(int) (0x71007F0C10)
// initializes the same fields 0xE8..0x188 as DrMdoNode(int) (0x710082B03C, the same 0x104 bytes), and its
// uniformBlock_OldMdl/OldBone and unimate_matColor read them (0x169, 0xF4).
class DrMdoSetup : public ::ml::DrMdoMat {
public:
    // inline in DrMdoNode's constructor
    explicit DrMdoSetup(int viewNum)
        : DrMdoMat(viewNum), m_scale(1.0f), pad_EC(0), m_gpuRender(false), m_renderPass(0), m_stateFlags(0),
          m_ctlFlags(0), m_ctlFlags2(0), m_aabbMax(0.5f, 0.5f, 0.5f), m_aabbMin(-0.5f, -0.5f, -0.5f),
          m_center(0.0f, 0.0f, 0.0f), pad_140(1.0f, 1.0f, 1.0f), pad_150(0.0f, 0.0f, 0.0f), m_length(0.0f), pad_164(0),
          m_mdlFlags(0), pad_16A(0), pad_16B(0), m_nodeMax(0), pad_182(0), pad_184(0), pad_188(0) {}

    void updateMpfMatUniformBlock();

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

    // Static image callbacks: s_pStaticImage[id] binds DrPixlMan pixl object id's texture as a UAV image.
    void varStImg_BaseColor(const MdsMatInfoHeader* info, unsigned int location, unsigned int matIdx);
    void varStImg_Etc(const MdsMatInfoHeader* info, unsigned int location, unsigned int matIdx);
    void varStImg_Normal(const MdsMatInfoHeader* info, unsigned int location, unsigned int matIdx);
    void varStImg_Velocity(const MdsMatInfoHeader* info, unsigned int location, unsigned int matIdx);
    void varStImg_ZBuff(const MdsMatInfoHeader* info, unsigned int location, unsigned int matIdx);

    // Uniform block callbacks: bind one uniform block (or storage buffer) at the location of global parameter
    // paramIdx. The parameter names are not the original's.
    void uniformBlock_no(const MdsMatValShaderCate* cate, int paramIdx, int mdlIdx, int matIdx, bool flag, unsigned int texIdx);
    void uniformBlock_Static(const MdsMatValShaderCate* cate, int paramIdx, int mdlIdx, int matIdx, bool flag, unsigned int texIdx);
    void uniformBlock_Material(const MdsMatValShaderCate* cate, int paramIdx, int mdlIdx, int matIdx, bool flag, unsigned int texIdx);
    void uniformBlock_Light(const MdsMatValShaderCate* cate, int paramIdx, int mdlIdx, int matIdx, bool flag, unsigned int texIdx);
    void uniformBlock_Mdl(const MdsMatValShaderCate* cate, int paramIdx, int mdlIdx, int matIdx, bool flag, unsigned int texIdx);
    void uniformBlock_Bone(const MdsMatValShaderCate* cate, int paramIdx, int mdlIdx, int matIdx, bool flag, unsigned int texIdx);
    void uniformBlock_OldMdl(const MdsMatValShaderCate* cate, int paramIdx, int mdlIdx, int matIdx, bool flag, unsigned int texIdx);
    void uniformBlock_OldBone(const MdsMatValShaderCate* cate, int paramIdx, int mdlIdx, int matIdx, bool flag, unsigned int texIdx);
    void uniformBlock_AvatarChar(const MdsMatValShaderCate* cate, int paramIdx, int mdlIdx, int matIdx, bool flag, unsigned int texIdx);
    void uniformBlock_AvatarDoll(const MdsMatValShaderCate* cate, int paramIdx, int mdlIdx, int matIdx, bool flag, unsigned int texIdx);
    void uniformBlock_Fog(const MdsMatValShaderCate* cate, int paramIdx, int mdlIdx, int matIdx, bool flag, unsigned int texIdx);
    void uniformBlock_Toon(const MdsMatValShaderCate* cate, int paramIdx, int mdlIdx, int matIdx, bool flag, unsigned int texIdx);
    void uniformBlock_VolTexCalc(const MdsMatValShaderCate* cate, int paramIdx, int mdlIdx, int matIdx, bool flag, unsigned int texIdx);
    void uniformBlock_GlobalIBL(const MdsMatValShaderCate* cate, int paramIdx, int mdlIdx, int matIdx, bool flag, unsigned int texIdx);
    void uniformBlock_ClusterParam(const MdsMatValShaderCate* cate, int paramIdx, int mdlIdx, int matIdx, bool flag, unsigned int texIdx);
    void uniformBlock_ClusterPntList(const MdsMatValShaderCate* cate, int paramIdx, int mdlIdx, int matIdx, bool flag, unsigned int texIdx);
    void uniformBlock_ClusterSptList(const MdsMatValShaderCate* cate, int paramIdx, int mdlIdx, int matIdx, bool flag, unsigned int texIdx);
    void uniformBlock_ClusterIdxList(const MdsMatValShaderCate* cate, int paramIdx, int mdlIdx, int matIdx, bool flag, unsigned int texIdx);
    void uniformBlock_ClusterAddressList(const MdsMatValShaderCate* cate, int paramIdx, int mdlIdx, int matIdx, bool flag, unsigned int texIdx);
    void uniformBlock_RimBloomCalc(const MdsMatValShaderCate* cate, int paramIdx, int mdlIdx, int matIdx, bool flag, unsigned int texIdx);
    void uniformBlock_Toon2(const MdsMatValShaderCate* cate, int paramIdx, int mdlIdx, int matIdx, bool flag, unsigned int texIdx);

    // Stock material callbacks: s_pStockMaterial[id] writes one stock variable's values to the uniform buffer and
    // returns the bytes written (a DrResMdoUniformBlock::s_nVarSizeTbl entry per value).
    int unimate_depthRatio(float* out, DrResMdoMat* mat, const MdsMatInfoHeader* info, const MdsMatVariableTbl* var);
    int unimate_texMatrix(float* out, DrResMdoMat* mat, const MdsMatInfoHeader* info, const MdsMatVariableTbl* var);
    int unimate_workFloat4(float* out, DrResMdoMat* mat, const MdsMatInfoHeader* info, const MdsMatVariableTbl* var);
    int unimate_workColor(float* out, DrResMdoMat* mat, const MdsMatInfoHeader* info, const MdsMatVariableTbl* var);
    int unimate_ProjectionMat(float* out, DrResMdoMat* mat, const MdsMatInfoHeader* info, const MdsMatVariableTbl* var);
    int unimate_alphaInfo(float* out, DrResMdoMat* mat, const MdsMatInfoHeader* info, const MdsMatVariableTbl* var);
    int unimate_matColor(float* out, DrResMdoMat* mat, const MdsMatInfoHeader* info, const MdsMatVariableTbl* var);
    int unimate_NomProjectionMat(float* out, DrResMdoMat* mat, const MdsMatInfoHeader* info, const MdsMatVariableTbl* var);
    int unimate_DollTexWork(float* out, DrResMdoMat* mat, const MdsMatInfoHeader* info, const MdsMatVariableTbl* var);
    int unimate_AvatarMapWrk(float* out, DrResMdoMat* mat, const MdsMatInfoHeader* info, const MdsMatVariableTbl* var);

    // by MdsMatValShaderCate's block id; unused ids hold uniformBlock_no
    static void (DrMdoSetup::*s_pUniBkMat[31])(const MdsMatValShaderCate*, int, int, int, bool, unsigned int);
    static void (DrMdoSetup::*s_pStaticTexture[46])(const MdsMatInfoHeader*, unsigned int, unsigned int);
    static void (DrMdoSetup::*s_pStaticImage[5])(const MdsMatInfoHeader*, unsigned int, unsigned int);
    static int (DrMdoSetup::*s_pStockMaterial[10])(float*, DrResMdoMat*, const MdsMatInfoHeader*, const MdsMatVariableTbl*);

    // the names are not the original's
    float m_scale;  // 0xE8: DrMdlObj::getInitialVertexAABBMax/Min scale by it on request (the name is not the original's)
    unsigned int pad_EC;
    bool m_gpuRender;  // 0xF0, isGpuRender
    unsigned char pad_F1[0x1];
    // 0xF2: the technique index partsDefRender looks up in the material's technique list; every call*Render pass
    // sets it (7 gbuffer, 4 light pre-pass, 8 refraction, 1 alpha, 0 opaque) (the name is not the original's)
    short m_renderTech;
    // 0xF4: the pass the call*Render functions start (0 opaque, 1 gbuffer, 2 refraction, 3 light pre-pass,
    // 4 alpha, 5 sp-alpha: the bit of m_stateFlags they test) (the name is not the original's)
    short m_renderPass;
    unsigned char pad_F6[0x2];
    unsigned int m_stateFlags;  // 0xF8: DrMdoGrpObj's render passes skip an object without bit 7
    unsigned int m_ctlFlags;  // 0xFC: setAlwaysTexStm, setGpuClip, setOcclusionQuery... each own a bit
    unsigned int m_ctlFlags2;  // 0x100: setDblBuffAlpha's bit
    unsigned char pad_104[0xC];
    mm::Vec3 m_aabbMax;  // 0x110, (0.5, 0.5, 0.5) from the constructor
    mm::Vec3 m_aabbMin;  // 0x120, (-0.5, -0.5, -0.5) from the constructor
    mm::Vec3 m_center;  // 0x130
    mm::Vec3 pad_140;  // 0x140, (1, 1, 1) from the constructor
    mm::Vec3 pad_150;  // 0x150, zeroed by the constructor
    float m_length;  // 0x160
    unsigned int pad_164;
    // 0x168, bit 9: uniformBlock_OldMdl/OldBone bind this frame's blocks instead of last frame's (the name is not
    // the original's)
    short m_mdlFlags;
    unsigned char pad_16A;
    unsigned char pad_16B;
    unsigned char pad_16C[0x4];
    // 0x170, the DrMdoShdSetShadow *Inst setters bind it while m_bindFlags[0] bit 1 is set (the name is not the
    // original's)
    grlib::CGLibEtcUniformBlock* m_pEtcBlock;
    // 0x178: partsDefRender's bind flags (bit 0: shader changed, bit 4: m_curBindIdx changed); every pass starts
    // with 0x10, 0 (the name is not the original's)
    unsigned char m_bindFlags[2];
    // 0x17A: the triangle uniform block index the shadow and pre-pass shader setters last bound (the name is not
    // the original's)
    short m_curTriBlockIdx;
    // 0x17C/0x17E: the shader and bind index partsDefRender last set; -1 at the start of every pass (the names are
    // not the original's)
    short m_curShaderIdx;
    short m_curBindIdx;
    short m_nodeMax;  // 0x180, getNodeIdx/setNodeMatrix bound by it (the name is not the original's)
    short pad_182;
    unsigned int pad_184;
    unsigned int pad_188;  // 1.0.0's DrMdoNode(int) zeroes it after storing its table
};
}  // namespace ml

#endif

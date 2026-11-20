#ifndef ML_DRCALCVIEWWORK_H
#define ML_DRCALCVIEWWORK_H

#include "classes/ml/DrCalcClipWorkViewPlane.h"
#include "classes/ml/DrCalcClipWorkViewPoli.h"
#include "grlib/CGLibDblUniformBlock.h"
#include "mm/Mat44.h"
#include "mm/Vec3.h"
#include "mm/Vec4.h"

namespace ml {
class DrMan;

// One view's camera state for rendering. The layout below covers what the uniform stock functions read; the
// rest of the class is not recovered yet. Field names are inferred from the stock functions that write them into
// the shader uniforms (unistatic_<name>, unistatic_mpf_<name>); they are not the original's.
class DrCalcViewWork {
public:
    typedef int (DrCalcViewWork::*StockStaticFunc)(float*, bool);
    typedef int (DrCalcViewWork::*StockFunc)(float*);

    DrCalcViewWork(DrMan* drMan);
    void begin(int);
    void end();
    // the shadow pass's billboard: the light's matrix without its translation (DrCalcMan::shadowEnd restores it)
    void shadowBegin(const mm::Mat44& mtx);
    // m_ditherMatrix from an 8x8 Bayer matrix (the constructor and begin call it)
    void updateDitherMatrix();
    static void GenerateBayerDitherMatrix(unsigned int* pDst, unsigned int size);

    int unistatic_view(float* pDst, bool bJitter);
    int unistatic_proj(float* pDst, bool bJitter);
    int unistatic_viewproj(float* pDst, bool bJitter);
    int unistatic_invview(float* pDst, bool bJitter);
    int unistatic_billborad_Def(float* pDst, bool bJitter);
    int unistatic_billborad_YVec(float* pDst, bool bJitter);
    int unistatic_etcParm(float* pDst, bool bJitter);
    int unistatic_viewYvec(float* pDst, bool bJitter);
    int unistatic_depth_change(float* pDst, bool bJitter);
    int unistatic_digher_val(float* pDst, bool bJitter);
    int unistatic_preProjMat(float* pDst, bool bJitter);
    int unistatic_screenSize(float* pDst, bool bJitter);
    int unistatic_jitter(float* pDst, bool bJitter);
    int unistatic_dither_tmaa_val(float* pDst, bool bJitter);
    int unistatic_proj_non_jitter(float* pDst, bool bJitter);
    int unistatic_diff_pre_orijmat(float* pDst, bool bJitter);
    int unitoon_rim_lgt(float* pDst);
    int unitoon_rim_mat(float* pDst);
    int unitoon_param(float* pDst);
    int unitoon_param2(float* pDst);
    int unistatic_lightDir(float* pDst);
    int unistatic_lightCol(float* pDst);
    int unistatic_lightAmb(float* pDst);
    int unistatic_lightNotUse(float* pDst);
    int unistatic_diffuseIBL(float* pDst);
    int unistatic_specularIBL(float* pDst);
    int unistatic_mpf_ViewProj(float* pDst);
    int unistatic_mpf_OldViewProj(float* pDst);
    int unistatic_mpf_View(float* pDst);
    int unistatic_mpf_BiiMat(float* pDst);
    int unistatic_mpf_OldBiiMat(float* pDst);
    int unistatic_mpf_DepthParm(float* pDst);
    int unistatic_mpf_Dither(float* pDst);
    int unistatic_mpf_ViewYVec(float* pDst);
    int unistatic_mpf_ViewPos(float* pDst);
    int unistatic_mpf_OldViewPos(float* pDst);
    int unistatic_mpf_Fade(float* pDst);
    int unistatic_dither_matrix(float* pDst);
    int unistatic_dither_param(float* pDst);
    int unistatic_inv_dither_matrix(float* pDst);
    int unistatic_inv_dither_param(float* pDst);

    static StockStaticFunc s_pStockStatic[16];
    static StockFunc s_pStockToon[3];
    static StockFunc s_pStockToon2[1];
    static StockFunc s_pStockLight[6];
    static StockFunc s_pStockMpf[11];
    static StockFunc s_pStockDither[2];
    static StockFunc s_pStockInvDither[2];

    mm::Mat44 m_invView;            // 0x0
    mm::Mat44 m_view;               // 0x40
    unsigned char pad_80[0x40];
    mm::Mat44 m_billboard;          // 0xC0
    mm::Mat44 m_oldBillboard;       // 0x100
    mm::Mat44 m_saveBillboard;      // 0x140: DrCalcMan::shadowEnd restores m_billboard from it (the name is not the original's)
    mm::Mat44 m_proj;               // 0x180
    mm::Mat44 m_godRayProj;         // 0x1C0: DrPixlSkyDome::godRayRender sends it as "proj" (name inferred)
    mm::Mat44 m_viewProj;           // 0x200
    mm::Mat44 m_billboardYVec;      // 0x240
    mm::Mat44 m_oldView;            // 0x280: m_view as DrCalcMan::renderEnd leaves it (the name is not the original's)
    mm::Mat44 m_oldViewProj;        // 0x2C0
    mm::Mat44 m_diffPreOrijMat;     // 0x300
    mm::Mat44 m_viewProjNonJitter;  // 0x340
    mm::Mat44 m_projNonJitter;      // 0x380
    unsigned char pad_3C0[0x40];
    mm::Vec3 m_viewPos;             // 0x400
    unsigned char pad_410[0x20];
    mm::Vec3 m_depthParm;           // 0x430
    unsigned char pad_440[0x20];
    mm::Vec3 m_viewYVec;            // 0x460
    unsigned char pad_470[0x20];
    float m_fade[12];               // 0x490
    float pad_4C0;                  // 0x4C0: DrPixlShadowRaytrace::temporalFiltering scales tanf(m_fovY * 0.5f) by it (aspect ratio?)
    float m_fovY;                   // 0x4C4: DrShdLgtClustered::stockEnd takes tanf of half of it (the name is not the original's)
    float m_near;                   // 0x4C8: 0.1 from the constructor (the name is not the original's)
    unsigned char pad_4CC[0x14];
    DrCalcClipWorkViewPlane m_clipPlane;  // 0x4E0: set from m_proj by the constructor (the name is not the original's)
    // 0x590: DrPixlShadowMan::clipDirShadowChk tests the shadow direction's line against it (the name is not the
    // original's)
    DrCalcClipWorkViewPoli m_clipPoli;
    unsigned char pad_5A0[0x160];
    DrMan* m_pDrMan;                // 0x700
    unsigned char pad_708[0x68];
    mm::Vec3 m_oldViewPos;          // 0x770
    unsigned char pad_780[0x30];
    // view uniform blocks DrMdoSetup's uniformBlock_ callbacks bind (names from those callbacks, not the original's)
    grlib::CGLibDblUniformBlock m_staticBlock;  // 0x7B0
    grlib::CGLibDblUniformBlock m_staticNonJitterBlock;  // 0x7E8: end stocks s_pStockStatic with bJitter false
    grlib::CGLibDblUniformBlock m_fogBlock;     // 0x820
    grlib::CGLibDblUniformBlock m_toonBlock;    // 0x858
    grlib::CGLibDblUniformBlock m_toon2Block;   // 0x890
    grlib::CGLibDblUniformBlock m_lightBlock;   // 0x8C8
    // 0x900: DrMdoShdSetMpf::mpfshd_* bind it first for every mpf shader (the name is not the original's)
    grlib::CGLibDblUniformBlock m_mpfBlock;
    grlib::CGLibDblUniformBlock m_ditherBlock;     // 0x938: end stocks s_pStockDither into it
    grlib::CGLibDblUniformBlock m_invDitherBlock;  // 0x970: end stocks s_pStockInvDither into it
    unsigned char pad_9A8[0x1];
    // 0x9A9, DrPixlPostObjMotionBlur::render skips calcVelocityBlur while set (the name is not the original's)
    bool m_velocityBlurOff;
    // DrGpuCheckObj::setWorldPos/update treat every check object as visible while it is set (the name is not the
    // original's)
    bool m_gpuCheckAllVisible;      // 0x9AA
    // 0x9AB: DrMdoCtlMpf::calcMpfRenderList passes it as DrMdoCtlMpfAuto::autoMpfCalc's first flag
    bool pad_9AB;
    bool pad_9AC;  // 0x9AC, DrEnvColiMan::update resets its fade while set
    bool m_renderReq;               // 0x9AD: DrCalcMan::renderEnd clears it (the name is not the original's)
    unsigned char pad_9AE[0x132];
    float m_jitter[2];              // 0xAE0
    unsigned char pad_AE8[0x8];
    float m_oldJitter[2];           // 0xAF0
    unsigned char pad_AF8[0x8];
    float m_ditherTmaaVal[4];       // 0xB00
    float m_ditherParam[2];         // 0xB10
    unsigned char pad_B18[0x8];
    // 0xB20: updateDitherMatrix's Bayer values (0..63); unistatic_dither_matrix / unistatic_inv_dither_matrix hand
    // them to the shader as four 4x4 matrices (the name is not the original's)
    unsigned int m_ditherMatrix[8][8];
    unsigned char pad_C20[0x40];  // DrCalcMan news 0xC60 bytes
};
}  // namespace ml

#endif

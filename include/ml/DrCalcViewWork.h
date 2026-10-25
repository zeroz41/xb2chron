#ifndef ML_DRCALCVIEWWORK_H
#define ML_DRCALCVIEWWORK_H

#include "classes/ml/DrCalcClipWorkViewPlane.h"
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

    void begin(int);
    void end();

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
    unsigned char pad_140[0x40];
    mm::Mat44 m_proj;               // 0x180
    unsigned char pad_1C0[0x40];
    mm::Mat44 m_viewProj;           // 0x200
    mm::Mat44 m_billboardYVec;      // 0x240
    unsigned char pad_280[0x40];
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
    unsigned char pad_4C0[0x8];
    float m_near;                   // 0x4C8: 0.1 from the constructor (the name is not the original's)
    unsigned char pad_4CC[0x14];
    DrCalcClipWorkViewPlane m_clipPlane;  // 0x4E0: set from m_proj by the constructor (the name is not the original's)
    unsigned char pad_4E8[0x218];
    DrMan* m_pDrMan;                // 0x700
    unsigned char pad_708[0x68];
    mm::Vec3 m_oldViewPos;          // 0x770
    unsigned char pad_780[0x22A];
    // DrGpuCheckObj::setWorldPos/update treat every check object as visible while it is set (the name is not the
    // original's)
    bool m_gpuCheckAllVisible;      // 0x9AA
    unsigned char pad_9AB[0x135];
    float m_jitter[2];              // 0xAE0
    unsigned char pad_AE8[0x8];
    float m_oldJitter[2];           // 0xAF0
    unsigned char pad_AF8[0x8];
    float m_ditherTmaaVal[4];       // 0xB00
    float m_ditherParam[2];         // 0xB10
};
}  // namespace ml

#endif

#ifndef CLASSES_ML_DRMAN_H
#define CLASSES_ML_DRMAN_H

#include "mtl/AllocHandle.h"
#include "classes/ml/IWorkBackground.h"
#include "mm/Vec3.h"

namespace cloud { class CloudMan; }
namespace grlib { class CGLibTextureBuffer; }
namespace ml { class DrAPCache; }
namespace ml { class DrPixlTileParm; }
namespace ml { class DrPixlMdlSampler; }
namespace ml { class DrCalcMan; }
namespace ml { class DrShdMan; }
namespace ml { class DrLightMan; }
namespace ml { class DrGlobalIBLMan; }
namespace ml { class DrCalcTexStreamMan; }
namespace ml { class DrIniSys; }
namespace ml { class DrPixlMan; }
namespace ml { class DrMdlMan; }
namespace ml { class DrPixlPostParm; }
namespace ml { class IDrDrawCallback; }
namespace ml { class WinProc; }
namespace ml { class CriticalSection; }

namespace ml {
// what ScnRenderDrSysParmAcc::createAddRenderView builds from a ScnRenderDrViewCtrl
struct DR_VIEW_PARAM;
class DrEnvironmentMan;

// a texture a scene's models are drawn with (ScnRenderDrSysParmAcc::setModelTexture builds it; the field names are
// not the original's)
struct DR_MODEL_TEXTURE {
    grlib::CGLibTextureBuffer* m_texture;
    bool m_enable;
};

// table 0x7100B7ABB0
class DrMan : public ::ml::IWorkBackground {
public:
    virtual ~DrMan();  // slot 0
    virtual void bkgHomeMenu(bool);  // slot 2

    // both read s_pTop
    static DrMan* getIns();
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member: `this` is the DrMan
    // (ScnRenderDrSysParmAcc::getWeatherFrame passes its m_drMan), its code is in the DrMan unit. What it does: sets the
    // byte at 0x1CC0 + s_nDblStockIdx to 1 (a double-buffered bool flag).
    void fn_710071E620();
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member: `this` is the DrMan
    // (ScnRenderDrSysParmAcc::fn_710070A0DC passes its m_drMan), its code is in the DrMan unit. What it does: returns
    // the byte at 0x1DBC + s_nDblStockIdx (a double-buffered bool flag).
    bool fn_710071E77C();
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member: `this` is the DrMan
    // (DrEnvColiMan::update, DrEnvironmentTime::setWeatherNum(DrMan*, ...), DrMdoMat::updateTimerCalc pass one), its
    // code is in the DrMan unit. What it does: returns the byte at 0x1CC0 + s_nDblIdx != 0 (the flag fn_710071E620
    // sets).
    bool fn_710071E640();
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member: `this` is the DrMan
    // (DrMdoCtlSeam::calcBegin passes one), its code is in the DrMan unit. What it does: sets the byte at
    // 0x1DBC + s_nDblIdx to 1 (the flag fn_710071E77C reads).
    void fn_710071E75C();
    static CriticalSection* getCriticalSection();
    bool isTemporalUPSToGlobalIBL() const;
    void setAllMiddelTexStmChk(bool check);
    void setAlphaRenderTarget();
    static DrMan* get();
    static bool isSRGBMode();
    static bool isFogSRGB();

    void begin();
    void end();
    bool loopCnt();
    void apply(int);
    void render(int);
    void tail();
    void setCallBack(IDrDrawCallback* callback);
    void releaseCallBack(IDrDrawCallback* callback);
    void openPixelDebugWindow(WinProc* proc);
    void openHistgramDebugWindow(WinProc* proc);
    void setTimeVal(float time);
    void setAutoReduction(bool enable);
    void setGlobalWind(const mm::Vec3& power);
    const mm::Vec3& getGlobalWind() const;
    bool isIBLHalfRes() const;
    void setSeamMapStmOk(bool ok);
    void setGblIdx(int index);
    void offGblIdx(int index);
    bool isAllMiddelTexStmChk() const;
    bool isSeamMapStmOk() const;
    bool isIBLSkip() const;
    void createAddRenderSystem(DR_VIEW_PARAM* param);
    void deleteAddRenderSystem(unsigned int index);
    void setModelTexture(DR_MODEL_TEXTURE* texture, unsigned int slot);
    void resetModelTexture(unsigned int slot);

    static int s_nDblIdx;
    static int s_nDblStockIdx;
    static DrMan* s_pTop;
    static int s_nDblNowIdx;
    static int s_nDblMemIdx;
    static bool s_bSRGBMode;
    static bool s_bFogSRGB;

    unsigned char pad_8[0x4];
    // 0xC, DrMdoZSortMan's constructor allocates its buckets from it (the name is not the original's)
    mtl::ALLOC_HANDLE m_workHandle;
    mtl::ALLOC_HANDLE m_resHandle;      // 0x10, DrResMpfSampler news its samplers from it (the name is not the original's)
    mtl::ALLOC_HANDLE m_allocHandle;    // 0x14, DrResOccUniformObj/DrResEtcUniformObj allocate from it (the name is not the original's)
    unsigned char pad_18[0x4];
    // 0x1C, DrShdLgtMan::reloadShader reads its shader file into it (the name is not the original's)
    mtl::ALLOC_HANDLE m_fileHandle;
    unsigned char pad_20[0x50];
    DrIniSys* m_iniSys;                 // the constructor makes it (0x1BA0 bytes)
    DrPixlMan* m_pixlMan;               // 0x78, DrMdoSetup::varStTex_* call DrPixlMan methods on it (the name is not the original's)
    DrShdMan* m_shdMan;                 // 0x80, DrMdoSetup::uniformBlock_Bone/Cluster* read it (the name is not the original's)
    DrMdlMan* m_mdlMan;                 // 0x88, DrCreator's model calls go to it
    unsigned char pad_90[0x10];
    // one per view: DrCreator::createClipObj takes the view's clip manager from it (the name is not the original's)
    DrCalcMan* m_viewCalcMan[4];        // 0xA0
    // one per view: ScnObjLightDrSys's constructor releases the view's fast light with it (the name is not the
    // original's)
    DrLightMan* m_viewLightMan[4];      // 0xC0
    unsigned char pad_E0[0x20];
    // the constructor makes one per view (index 0 here), after the DrLightMan/DrFogMan it is built from
    DrEnvironmentMan* m_envMan[4];
    DrPixlPostParm* m_postParm[4];      // the constructor makes them; ScnRenderDrSysParmAcc takes one per view
    unsigned char pad_140[0x20];
    // one per view: ScnObjIBLDr makes and releases its IBL pack with it (the name is not the original's)
    DrGlobalIBLMan* m_iblMan[4];        // 0x160
    // 0x180: DrMdoCtlSeamAll::callRenderSeamAll brackets the seam mpf display list with its begin/end (the name is
    // not the original's)
    DrPixlTileParm* m_tileParm;
    // 0x188: DrMdoSamplerMan::begin sets its samplers up when update reports a change (the name is not the original's)
    DrPixlMdlSampler* m_pMdlSampler;
    unsigned char pad_190[0x2E8];
    // 0x478: one 0x40-byte record per view; DrShdLgtGlobalIBL::update updates a view other than 0 only when bit 0 of
    // its first byte is set (the type and names are not the original's)
    struct ViewUpdate {
        bool m_enable : 1;
        unsigned char pad_1[0x3F];
    };
    ViewUpdate m_viewUpdate[4];
    unsigned char pad_578[0x8];
    // the current view's DrCalcMan: beginSetup stores the one it makes at 0xA0 + index * 8 here too (the name is
    // not the original's)
    DrCalcMan* m_calcMan;               // 0x580
    DrLightMan* m_lightMan;             // 0x588, DrResMdoLight makes and releases its lights with it (the name is not the original's)
    unsigned char pad_590[0x8];
    // 0x598: the current view's DrEnvironmentMan (DrResMdoSeamWrkLight::setupWork makes its environment object with
    // it; the name is not the original's)
    DrEnvironmentMan* m_curEnvMan;
    unsigned char pad_5A0[0x10];
    DrCalcTexStreamMan* m_texStreamMan;  // 0x5B0, DrStmReadCheck makes its stream lists with it (the name is not the original's)
    // 0x5B8: the constructor points it at its record at 0x440 (0x40 bytes per view, the same records
    // m_viewUpdate reads) and stores the main screen size in it; DrPixlMan::setMainViewPort makes the viewport from
    // that size (the type and names are not the original's)
    struct ViewInfo {
        unsigned char pad_0[0x18];
        int m_width;   // 0x18, DrAPGxType::getMainScreenSize
        int m_height;  // 0x1C
        // 0x20: the constructor copies the screen size here too; DrPixlMan::setMainRenderTarget's viewport uses it
        int m_renderWidth;
        int m_renderHeight;  // 0x24
    };
    ViewInfo* m_curViewInfo;
    DrAPCache* m_apCache;               // 0x5C0, DrMdoSetup::varStTex_* bind textures through it (the name is not the original's)
    bool* m_pAutoReduction;             // 0x5C8, setAutoReduction writes through it
    unsigned char pad_5D0[0x8];
    IDrDrawCallback* m_callBack[16];    // 0x5D8, setCallBack/releaseCallBack
    int m_callBackNum;                  // 0x658
    unsigned char pad_65C[0x1604];
    // 0x1C60: DrPixlTileParm::update turns tiled caching on (table 1) while it is 0, and
    // DrPixlPostParm::getTMAASharpness then reads its second table (the name is not the original's)
    int m_qualityMode;
    unsigned char pad_1C64[0xC];
    // the field names below are not the original's: each is named after the ScnRenderDrSys/ScnRenderDrSysParmAcc
    // setter that writes it
    mm::Vec3 m_seamMapReadPos;
    bool m_seamMapAddPosMode;
    unsigned char m_captureMode[2];     // by s_nDblStockIdx: 1 on, 2 off
    unsigned char pad_1C83[0x1];
    float m_glbSpd;
    unsigned char pad_1C88[0x8];
    float m_gamma;
    unsigned char pad_1C94[0x4];
    int m_postParmIdx;                  // 0x1C98, DrMdoMat::matCall_OutLineVal reads m_postParm[this] (name inferred)
    unsigned int m_viewRenderSkip;      // a bit per view
    unsigned char pad_1CA0[0x4];
    float m_timeVal[2];                 // 0x1CA4, by s_nDblStockIdx: setTimeVal clamps to [0, 1] (name inferred)
    unsigned char pad_1CAC[0x14];
    // 0x1CC0: fn_710071E620 (ScnRenderDrSysParmAcc::getWeatherFrame's call) sets [s_nDblStockIdx], fn_710071E640 reads
    // [s_nDblIdx] (the name is not the original's)
    // a byte, not a bool: fn_710071E640 compares it with 0
    unsigned char m_weatherFrameReq[2];
    bool m_homeMenu;                    // 0x1CC2, bkgHomeMenu(true) sets it
    bool m_autoResetScene;
    unsigned char pad_1CC4[0x38];
    // 0x1CFC: while >= 1, DrMdoCtlSeamRead::wait*Stream also set bit 10 of a seam model's flags when its stream
    // ends without data (the name is not the original's)
    int m_seamReadErrMode;
    unsigned char pad_1D00[0x20];
    unsigned int* m_dispOffBits;  // 0x1D20: a bit per display index, set = hidden (ScnObjAccPartsEtcPos::isDisp; name inferred)
    unsigned char pad_1D28[0x8];
    mm::Vec3 m_globalWind[2];           // 0x1D30, by s_nDblNowIdx (getGlobalWind)
    unsigned char pad_1D50[0x2D];
    // 0x1D7D: DrMdoCtlSeamAll's render passes return at once while set (the name is not the original's)
    bool m_seamRenderOff;
    unsigned char pad_1D7E[0x6];
    // 0x1D84: DrMdlMan::shadowRender renders nothing while set (the name is not the original's)
    bool m_mdlShadowOff;
    unsigned char pad_1D85[0x7];
    // 0x1D8C: DrShdLgtHybrid::render skips the clustered lights' render while set (the name is not the original's)
    bool m_clusteredRenderOff;
    unsigned char pad_1D8D[0x4];
    bool m_iblSkip;                     // 0x1D91: isIBLSkip is true, isTemporalUPSToGlobalIBL false while set (name inferred)
    unsigned char pad_1D92[0x4];
    // 0x1D96: DrMdlMan::shadowRender renders nothing while set (the name is not the original's)
    bool m_shadowRenderOff;
    bool m_mdlDblPause;
    unsigned char pad_1D98[0x20];
    bool m_allMiddelTexStmChk[2];       // 0x1DB8, by s_nDblStockIdx
    bool m_seamMapStmOk[2];             // 0x1DBA, setSeamMapStmOk writes [s_nDblIdx]
    // 0x1DBC: fn_710071E75C (DrMdoCtlSeam::calcBegin's call) sets [s_nDblIdx], fn_710071E77C reads [s_nDblStockIdx]
    // (the name is not the original's)
    bool m_seamCalc[2];
    bool m_cameraLight;
    unsigned char pad_1DBF[0x1];
    // 0x1DC0: DrShdLgtHybrid renders the tile-based lights for 0, the clustered ones for 1, none otherwise (the name
    // is not the original's)
    int m_shdLgtType;
    unsigned char pad_1DC4[0x4C];
    cloud::CloudMan* m_cloudMan;        // setPlaneCloudNum hands it the cloud count
    bool m_toonDirLightScale;
    unsigned char pad_1E19[0x3];
    int m_toonAmbient;                  // 3 on, 0 off
    // 0x1E20: DrPixlPostObjUnbranchToDepth::render adds its quarter pass while set (the name is not the original's)
    bool m_unbranchQuater;
    unsigned char pad_1E21[0xF];
};
}  // namespace ml

#endif

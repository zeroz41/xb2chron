#ifndef CLASSES_ML_DRMAN_H
#define CLASSES_ML_DRMAN_H

#include "mtl/AllocHandle.h"
#include "classes/ml/IWorkBackground.h"
#include "mm/Vec3.h"
#include "classes/ml/IDrDrawWorkInfo.h"

namespace cloud { class CloudMan; }
namespace grlib { class CGLibTextureBuffer; }
namespace ml { class DrAPCache; }
namespace ml { enum FILE_PRIO : int; }
namespace ml { class DrResFilterData; }
namespace ml { class DrPixlTileParm; }
namespace ml { class DrPixlMdlSampler; }
namespace ml { class DrCalcMan; }
namespace ml { class DrShdMan; }
namespace ml { class DrLightMan; }
namespace ml { class DrFogMan; }
namespace ml { class DrGlobalIBLMan; }
namespace ml { class DrCalcTexStreamMan; }
namespace ml { class DrIniSys; }
namespace ml { class DrIrrVolMan; }
namespace ml { class DrPixlMan; }
namespace ml { class DrMdlMan; }
namespace ml { class DrPixlPostParm; }
namespace ml { class IDrDrawCallback; }
namespace ml { class WinProc; }
namespace ml { class CriticalSection; }
namespace ml { class Scn; }

namespace ml {
// what ScnRenderDrSysParmAcc::createAddRenderView builds from a ScnRenderDrViewCtrl; createAddRenderSystem copies
// its 0x38 bytes into the double-buffered list (the field names are not the original's: each is named after the
// ScnRenderDrViewCtrl field it is built from)
struct DR_VIEW_PARAM {
    unsigned int m_width;
    unsigned int m_height;
    int m_viewNo;  // the view's render system index (ScnRenderDrViewCtrl::m_viewIndex + 1)
    bool m_clear;
    bool m_flagA;
    bool m_flagB;
    float* m_color;
    bool* m_isReady;
    float* m_scaleX;
    float* m_scaleY;
    grlib::CGLibTextureBuffer** m_texture;
};
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
    // ScnRenderDrSys::thDrSysInitialize news it (0x1E30 bytes) with the scene's handle
    DrMan(Scn* scn);
    virtual ~DrMan();  // slot 0
    virtual void bkgHomeMenu(bool);  // slot 2

    // both read s_pTop
    static DrMan* getIns();
    void blurCallBackRender();
    // 2.0.0's symbols name it. What it does: sets the byte at 0x1CC0 + s_nDblStockIdx to 1 (a double-buffered bool
    // flag).
    void weatherFrmEnd();
    // 2.0.0's symbols name it. A member: `this` is the DrMan (ScnRenderDrSysParmAcc::isSeamMapOn passes its
    // m_drMan), its code is in the DrMan unit. What it does: returns the byte at 0x1DBC + s_nDblStockIdx (a
    // double-buffered bool flag).
    bool isSeamMapOn() const;
    // 2.0.0's symbols name it. What it does: returns the byte at 0x1CC0 + s_nDblIdx != 0 (the flag weatherFrmEnd sets).
    bool isWeatherFrmEnd();
    // 2.0.0's symbols name it. What it does: sets the byte at 0x1DBC + s_nDblIdx to 1 (the flag isSeamMapOn reads).
    void setSeamMapOn();
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
    // tail steps it 0, 1, 2, 0 (a triple-buffer index)
    static int s_nTriNowIdx;
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
    // 0x20, DrPixlOccQuery's constructor allocates its query pool from it (the name is not the original's)
    mtl::ALLOC_HANDLE m_queryHandle;
    unsigned char pad_24[0x4C];
    DrIniSys* m_iniSys;                 // the constructor makes it (0x1BA0 bytes)
    DrPixlMan* m_pixlMan;               // 0x78, DrMdoSetup::varStTex_* call DrPixlMan methods on it (the name is not the original's)
    DrShdMan* m_shdMan;                 // 0x80, DrMdoSetup::uniformBlock_Bone/Cluster* read it (the name is not the original's)
    DrMdlMan* m_mdlMan;                 // 0x88, DrCreator's model calls go to it
    // 0x90: tail calls its tail, the destructor deletes it (the name is not the original's)
    DrIrrVolMan* m_irrVolMan;
    DrResFilterData* m_filterData;  // 0x98, DrIniSys::loadFilterLutTexture hands it the filter LUT (name inferred)
    // one per view: DrCreator::createClipObj takes the view's clip manager from it (the name is not the original's)
    DrCalcMan* m_viewCalcMan[4];        // 0xA0
    // one per view: ScnObjLightDrSys's constructor releases the view's fast light with it (the name is not the
    // original's)
    DrLightMan* m_viewLightMan[4];      // 0xC0
    // one per view: the destructor deletes them with ~DrFogMan; end makes [0] the current one (the name is not the
    // original's)
    DrFogMan* m_viewFogMan[4];          // 0xE0
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
    // 0x190: by s_nDblStockIdx: the views createAddRenderSystem queued (the names are not the original's)
    DR_VIEW_PARAM m_addViewParam[2][4];
    int m_addViewNum[2];                // 0x350
    // 0x358: by s_nDblStockIdx: the view indices deleteAddRenderSystem queued (the names are not the original's)
    unsigned int m_delViewIdx[2][4];
    int m_delViewNum[2];                // 0x378
    unsigned char pad_380[0x38];
    // 0x3B8: by s_nDblStockIdx, then slot: setModelTexture/resetModelTexture write it (the name is not the original's)
    DR_MODEL_TEXTURE m_modelTexture[2][4];
    // 0x438: by s_nDblStockIdx, a bit per slot setModelTexture/resetModelTexture changed (the name is not the
    // original's)
    unsigned int m_modelTextureReq[2];
    // 0x440: one 0x40-byte record per view (the type and names are not the original's). The constructor points
    // m_curViewInfo at [0] and stores the main screen size in it; DrPixlMan::setMainViewPort makes the viewport from
    // that size. DrShdLgtGlobalIBL::update updates a view other than 0 only when bit 0 of its byte 0x38 is set.
    struct ViewInfo {
        unsigned char pad_0[0x18];
        int m_width;   // 0x18, DrAPGxType::getMainScreenSize
        int m_height;  // 0x1C
        // 0x20: the constructor copies the screen size here too; DrPixlMan::setMainRenderTarget's viewport uses it
        int m_renderWidth;
        int m_renderHeight;  // 0x24
        // 0x28: DrPixlPostObjCapture::update sizes its capture target from it (the names are not the original's)
        int m_captureWidth;
        int m_captureHeight;  // 0x2C
        unsigned char pad_30[0x8];
        bool m_enable : 1;  // 0x38
        unsigned char pad_39[0x7];
    };
    ViewInfo m_viewInfo[4];
    unsigned char pad_540[0x40];
    // the current view's DrCalcMan: beginSetup stores the one it makes at 0xA0 + index * 8 here too (the name is
    // not the original's)
    DrCalcMan* m_calcMan;               // 0x580
    DrLightMan* m_lightMan;             // 0x588, DrResMdoLight makes and releases its lights with it (the name is not the original's)
    DrFogMan* m_fogMan;                 // 0x590, the current view's (end sets m_viewFogMan[0]; the name is not the original's)
    // 0x598: the current view's DrEnvironmentMan (DrResMdoSeamWrkLight::setupWork makes its environment object with
    // it; the name is not the original's)
    DrEnvironmentMan* m_curEnvMan;
    unsigned char pad_5A0[0x10];
    DrCalcTexStreamMan* m_texStreamMan;  // 0x5B0, DrStmReadCheck makes its stream lists with it (the name is not the original's)
    // 0x5B8: the current view's record in m_viewInfo (end resets it to [0]; the name is not the original's)
    ViewInfo* m_curViewInfo;
    DrAPCache* m_apCache;               // 0x5C0, DrMdoSetup::varStTex_* bind textures through it (the name is not the original's)
    bool* m_pAutoReduction;             // 0x5C8, setAutoReduction writes through it
    unsigned char pad_5D0[0x8];
    IDrDrawCallback* m_callBack[16];    // 0x5D8, setCallBack/releaseCallBack
    int m_callBackNum;                  // 0x658
    unsigned char pad_65C[0x4];
    // 0x660: one per view; DrResMdoSortCloud::alphaRender hands the one m_postParmIdx selects to
    // cloud::CloudMan::alphaRender (the name is not the original's)
    IDrDrawWorkInfo m_drawWorkInfo[4];
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
    unsigned char pad_1C88[0x4];
    // 0x1C8C: DrMdoMpfMan::update scales its wind calculators' update by it (the name is not the original's)
    float m_mpfWindPower;
    float m_gamma;
    unsigned char pad_1C94[0x4];
    int m_postParmIdx;                  // 0x1C98, DrMdoMat::matCall_OutLineVal reads m_postParm[this] (name inferred)
    unsigned int m_viewRenderSkip;      // a bit per view
    unsigned char pad_1CA0[0x4];
    float m_timeVal[2];                 // 0x1CA4, by s_nDblStockIdx: setTimeVal clamps to [0, 1] (name inferred)
    int m_hour;  // 0x1CAC, DrEnvironmentObjLgt::update copies it to its DrEnvironmentTime (name inferred)
    unsigned char pad_1CB0[0x10];
    // 0x1CC0: weatherFrmEnd (ScnRenderDrSysParmAcc::weatherFrmEnd's call) sets [s_nDblStockIdx], isWeatherFrmEnd reads
    // [s_nDblIdx] (the name is not the original's)
    // a byte, not a bool: isWeatherFrmEnd compares it with 0
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
    // 0x1D50: ScnRenderDrSysParmAcc::setRenderTexMode stores its flag here (fw::CommonResource passes it); what reads
    // it is not known (the name is not the original's)
    int m_commonFlag;
    // 0x1D54: 1 makes DrIniSys load the DLC toon gradients and filter LUT (the name is not the original's)
    int m_dlcShaderMode;
    unsigned char pad_1D58[0x25];
    // 0x1D7D: DrMdoCtlSeamAll's render passes return at once while set (the name is not the original's)
    bool m_seamRenderOff;
    unsigned char pad_1D7E[0x6];
    // 0x1D84: DrMdlMan::shadowRender renders nothing while set (the name is not the original's)
    bool m_mdlShadowOff;
    // 0x1D85: DrMdoCtlSeamBaseMap::callShadowMapRenderSeamBaseMap renders nothing while set (the name is not the
    // original's)
    bool m_seamBaseShadowOff;
    // 0x1D86: DrMdoCtlSeamAll::occRender renders nothing while set (the name is not the original's)
    bool m_seamOccRenderOff;
    unsigned char pad_1D87[0x1];
    // 0x1D88: DrMdoCtlSeamEnvMap's render passes draw nothing while set (the name is not the original's)
    bool m_seamEnvRenderOff;
    unsigned char pad_1D89[0x3];
    // 0x1D8C: DrShdLgtHybrid::render skips the clustered lights' render while set (the name is not the original's)
    bool m_clusteredRenderOff;
    unsigned char pad_1D8D[0x4];
    bool m_iblSkip;                     // 0x1D91: isIBLSkip is true, isTemporalUPSToGlobalIBL false while set (name inferred)
    unsigned char pad_1D92[0x4];
    // 0x1D96: DrMdlMan::shadowRender renders nothing while set (the name is not the original's)
    bool m_shadowRenderOff;
    bool m_mdlDblPause;
    // 0x1D98: DrMdoMpfMan::update skips the wind calculators while set (the name is not the original's)
    bool m_mpfWindStop;
    unsigned char pad_1D99[0xF];
    // 0x1DA8: end copies it to the next byte (the names are not the original's)
    bool m_endFlagReq;
    bool m_endFlag;                     // 0x1DA9
    unsigned char pad_1DAA[0x6];
    // 0x1DB0: the priority DrResMdoSeamRead::read gives its reads (the name is not the original's)
    FILE_PRIO m_seamReadPrio;
    unsigned char pad_1DB4[0x4];
    bool m_allMiddelTexStmChk[2];       // 0x1DB8, by s_nDblStockIdx
    bool m_seamMapStmOk[2];             // 0x1DBA, setSeamMapStmOk writes [s_nDblIdx]
    // 0x1DBC: setSeamMapOn (DrMdoCtlSeam::calcBegin's call) sets [s_nDblIdx], isSeamMapOn reads [s_nDblStockIdx]
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

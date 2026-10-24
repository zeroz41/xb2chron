#ifndef CLASSES_ML_DRMAN_H
#define CLASSES_ML_DRMAN_H

#include "classes/ml/IWorkBackground.h"
#include "mm/Vec3.h"

namespace cloud { class CloudMan; }
namespace grlib { class CGLibTextureBuffer; }
namespace ml { class DrAPCache; }
namespace ml { class DrIniSys; }
namespace ml { class DrPixlMan; }
namespace ml { class DrMdlMan; }
namespace ml { class DrPixlPostParm; }
namespace ml { class IDrDrawCallback; }
namespace ml { class WinProc; }

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
    static bool s_bSRGBMode;
    static bool s_bFogSRGB;

    unsigned char pad_8[0x68];
    DrIniSys* m_iniSys;                 // the constructor makes it (0x1BA0 bytes)
    DrPixlMan* m_pixlMan;               // 0x78, DrMdoSetup::varStTex_* call DrPixlMan methods on it (the name is not the original's)
    unsigned char pad_80[0x8];
    DrMdlMan* m_mdlMan;                 // 0x88, DrCreator's model calls go to it
    unsigned char pad_90[0x70];
    // the constructor makes one per view (index 0 here), after the DrLightMan/DrFogMan it is built from
    DrEnvironmentMan* m_envMan[4];
    DrPixlPostParm* m_postParm[4];      // the constructor makes them; ScnRenderDrSysParmAcc takes one per view
    unsigned char pad_140[0x480];
    DrAPCache* m_apCache;               // 0x5C0, DrMdoSetup::varStTex_* bind textures through it (the name is not the original's)
    bool* m_pAutoReduction;             // 0x5C8, setAutoReduction writes through it
    unsigned char pad_5D0[0x8];
    IDrDrawCallback* m_callBack[16];    // 0x5D8, setCallBack/releaseCallBack
    int m_callBackNum;                  // 0x658
    unsigned char pad_65C[0x1614];
    // the field names below are not the original's: each is named after the ScnRenderDrSys/ScnRenderDrSysParmAcc
    // setter that writes it
    mm::Vec3 m_seamMapReadPos;
    bool m_seamMapAddPosMode;
    unsigned char m_captureMode[2];     // by s_nDblStockIdx: 1 on, 2 off
    unsigned char pad_1C83[0x1];
    float m_glbSpd;
    unsigned char pad_1C88[0x8];
    float m_gamma;
    unsigned char pad_1C94[0x8];
    unsigned int m_viewRenderSkip;      // a bit per view
    unsigned char pad_1CA0[0x22];
    bool m_homeMenu;                    // 0x1CC2, bkgHomeMenu(true) sets it
    bool m_autoResetScene;
    unsigned char pad_1CC4[0x6C];
    mm::Vec3 m_globalWind[2];           // 0x1D30, by s_nDblNowIdx (getGlobalWind)
    unsigned char pad_1D50[0x47];
    bool m_mdlDblPause;
    unsigned char pad_1D98[0x20];
    bool m_allMiddelTexStmChk[2];       // 0x1DB8, by s_nDblStockIdx
    bool m_seamMapStmOk[2];             // 0x1DBA, setSeamMapStmOk writes [s_nDblIdx]
    unsigned char pad_1DBC[0x2];
    bool m_cameraLight;
    unsigned char pad_1DBF[0x51];
    cloud::CloudMan* m_cloudMan;        // setPlaneCloudNum hands it the cloud count
    bool m_toonDirLightScale;
    unsigned char pad_1E19[0x3];
    int m_toonAmbient;                  // 3 on, 0 off
    unsigned char pad_1E20[0x10];
};
}  // namespace ml

#endif

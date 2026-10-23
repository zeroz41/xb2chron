#ifndef CLASSES_ML_DRMAN_H
#define CLASSES_ML_DRMAN_H

#include "classes/ml/IWorkBackground.h"
#include "mm/Vec3.h"

namespace cloud { class CloudMan; }
namespace grlib { class CGLibTextureBuffer; }
namespace ml { class DrIniSys; }
namespace ml { class DrPixlPostParm; }
namespace ml { class IDrDrawCallback; }
namespace ml { class WinProc; }

namespace ml {
// what ScnRenderDrSysParmAcc::createAddRenderView builds from a ScnRenderDrViewCtrl
struct DR_VIEW_PARAM;

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

    void begin();
    void end();
    void loopCnt();
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
    void setGblIdx(int index);
    void offGblIdx(int index);
    bool isAllMiddelTexStmChk() const;
    bool isSeamMapStmOk() const;
    void createAddRenderSystem(DR_VIEW_PARAM* param);
    void deleteAddRenderSystem(unsigned int index);
    void setModelTexture(DR_MODEL_TEXTURE* texture, unsigned int slot);
    void resetModelTexture(unsigned int slot);

    static int s_nDblStockIdx;

    unsigned char pad_8[0x68];
    DrIniSys* m_iniSys;                 // the constructor makes it (0x1BA0 bytes)
    unsigned char pad_78[0xA8];
    DrPixlPostParm* m_postParm[4];      // the constructor makes them; ScnRenderDrSysParmAcc takes one per view
    unsigned char pad_140[0x1B30];
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
    unsigned char pad_1CA0[0x23];
    bool m_autoResetScene;
    unsigned char pad_1CC4[0xD3];
    bool m_mdlDblPause;
    unsigned char pad_1D98[0x26];
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

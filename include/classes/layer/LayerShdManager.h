#ifndef CLASSES_LAYER_LAYERSHDMANAGER_H
#define CLASSES_LAYER_LAYERSHDMANAGER_H

#include "classes/ml/IWorkEvent.h"
#include "classes/grlib/CGLibShdListData.h"
#include "grlib/CGLibDecShader.h"
#include "grlib/CGLibSampler.h"
#include "grlib/CGLibTextureBuffer.h"
#include "grlib/CGLibVtxFetch.h"
#include "grlib/CGLibVtxIndex.h"
#include "grlib/CGLibVtxVertex.h"

namespace ml { class EventFileTh; class IDrDrawWorkInfo; }
namespace grlib { class CGLibDblUniformBlock; class CGLibRenderTarget; class CGLibVtxInstans; class CGLibVtxOneInstans; }

namespace layer {
class LayerManager;
class LayerObjTopMaskObj;
class LayerResSecTexture;
class LayerTextureMan;
class LayerVertexMan;
class LayerResViewPortInfo;
class LayerVertexObj;

// the sampler and default vertex buffer a draw selects (LayerShdManager::setupTexture/setupVertex index arrays with
// them); no value has a name yet
enum LayerSamplerType {};
enum LayerDefVertType {};

// where one shader's declarations sit (LayerShdManager's init functions store CGLibDecShader::getDeclarationOfs for
// the names; the names are not the original's)
struct LayerShdDeclOfs {
    unsigned short m_gaugeType;    // "MENU_GAUGE_TYPE"
    unsigned short m_worldType;    // "MENU_WORLD_TYPE"
    unsigned short m_iconType;     // "MENU_ICON_TYPE"
    unsigned short m_option;       // "MENU_FILBLEND_TYPE", "MENU_USE_TEX" or "MENU_DECODE_TYPE" by shader
    unsigned short m_maskObjType;  // "MENU_MASKOBJ_TYPE"
    unsigned short m_secTexType;   // "MENU_SECTEX_TYPE"
};

// the shader type and declaration values a draw selects (LayerShdManager's select functions compare m_select with
// m_current field by field and set the changed declarations; the names are not the original's)
struct LayerShdSelect {
    short m_shaderType;
    short m_gaugeType;
    short m_worldType;    // set3DSpaceMode sets 2, setDepthBufferCheckOn/Off 1
    short m_iconType;
    short m_option;
    short m_maskObjType;  // setShaderMaskMode sets 2, setShaderMaskOff 1
    short m_secTexType;   // setSecTexture: 2 with a texture, else 1
};

// table 0x7100B80360
class LayerShdManager : public ::ml::IWorkEvent {
public:
    LayerShdManager(LayerManager* manager);
    virtual ~LayerShdManager();  // slot 0
    virtual bool OnFileEvent(ml::EventFileTh*);  // slot 7

    void shaderRelease();
    void readShader();
    bool setupUpdate();  // whether the shaders are ready (LayerManager::loadWait waits for it)
    void createRenderWork();
    void beginShader(const ml::IDrDrawWorkInfo* info);
    void resetViewPort();
    void endShader(const ml::IDrDrawWorkInfo* info);
    void setupMainRenderTarget();
    void setViewPort(LayerResViewPortInfo* info);
    void setShaderMaskMode(const LayerObjTopMaskObj* maskObj);
    void setSecTexture(LayerResSecTexture* texture);
    void setShaderMaskOff();
    void setDepthBufferCheckOn();
    void setDepthBufferCheckOff();
    void set3DSpaceMode(grlib::CGLibDblUniformBlock* block);
    void setupShader(grlib::CGLibDblUniformBlock* block);
    void setupTexture(const grlib::CGLibTextureBuffer& texture, LayerSamplerType sampler, unsigned int location);
    grlib::CGLibDecShader* setupShader();
    grlib::CGLibRenderTarget* getDefRenderTarget();
    void setupVertex(LayerVertexObj* obj, unsigned int index);
    void setupVertex(LayerDefVertType type);
    void setupInstaceVertex(grlib::CGLibVtxInstans& vertex, unsigned int first, unsigned int count);
    void setupInstaceVertex(grlib::CGLibVtxOneInstans& vertex, unsigned int first, unsigned int count);
    void renderQuadsIndex();
    void renderInstaceQuadsIndex(unsigned int instances);
    static void setupBlendDef();
    static void setupBlendSwf();
    static void setupBlendNo();
    static void setupBlendAdd();
    static void setupBlendAddSwf();
    static void setupBlendSub();
    static void setupBlendSubSwf();
    static void setupBlendMul();
    void initColor(unsigned int idx);
    void initTex(unsigned int idx);
    void initFont(unsigned int idx);
    void initWin(unsigned int idx);
    void initNumber(unsigned int idx);
    void initPoly(unsigned int idx);
    void initGsBlur(unsigned int idx);
    void initFlowMap(unsigned int idx);
    void initMemWrite(unsigned int idx);
    void initGamma(unsigned int idx);
    void initDebug(unsigned int idx);
    void initTest(unsigned int idx);
    grlib::CGLibDecShader* selectColor();
    grlib::CGLibDecShader* selectTex();
    grlib::CGLibDecShader* selectFont();
    grlib::CGLibDecShader* selectWin();
    grlib::CGLibDecShader* selectIcon();
    grlib::CGLibDecShader* selectNumber();
    grlib::CGLibDecShader* selectPoly();
    grlib::CGLibDecShader* selectGsBlur();
    grlib::CGLibDecShader* selectFlowMap();
    grlib::CGLibDecShader* selectMemWrite();
    grlib::CGLibDecShader* selectGamma();
    grlib::CGLibDecShader* selectDebug();
    grlib::CGLibDecShader* selectTest();

    // per shader type (m_shaderType): its init function (handed the shader's index), its select function
    static void (LayerShdManager::*s_CallSetup[13])(unsigned int);
    static grlib::CGLibDecShader* (LayerShdManager::*s_CallSelect[13])();
    // the vertex fetch (m_fetches index) each shader type draws with (LayerObj's .rodata holds it)
    static const unsigned int s_eFetchTbl[13];
    // the blend modes' setup functions (LayerObj's draws call them)
    static void (*s_CallBlend[8])();

    // Field names are not the original's: they follow the accessors and functions that read and write them.
    unsigned char pad_08[0x30];
    // the constructor creates both (new, over the manager's work handle); the names are not the original's
    LayerVertexMan* m_vertexMan;    // 0x38
    LayerTextureMan* m_textureMan;  // 0x40: LayerResAddTexObj/LayerResSecTexture share its texture objects
    LayerShdDeclOfs* m_pDeclOfs;  // 0x48, one per shader (the init functions fill it)
    const LayerObjTopMaskObj* m_pMaskObj;  // 0x50, setShaderMaskMode
    unsigned char pad_58[0x18];  // 0x58, 0x60: setSecTexture stores the texture and the resource's +0x18
    grlib::CGLibVtxFetch m_fetches[5];  // 0x70
    grlib::CGLibSampler m_samplers[9];  // 0xC0, setupTexture by LayerSamplerType
    grlib::CGLibShdListData m_shdList;  // 0x1E0, the shaders (the init functions read their declarations)
    grlib::CGLibVtxVertex m_defVertices[5];  // 0x238, setupVertex by LayerDefVertType
    grlib::CGLibVtxIndex m_quadIndices[2];  // 0x300, renderQuadsIndex draws the first
    grlib::CGLibDblUniformBlock* m_p3DSpaceBlock;  // 0x350, set3DSpaceMode (null after setDepthBufferCheckOn/Off)
    void* m_pMaskWork;  // 0x358, cleared whenever the mask mode changes (what sets it is not known yet)
    grlib::CGLibRenderTarget* m_pRenderTarget;  // 0x360, getDefRenderTarget (the main one when null)
    unsigned char pad_368[0x188];
    LayerShdSelect m_select;   // 0x4F0, what the next draw asks for (setupShader selects by its shader type)
    LayerShdSelect m_current;  // 0x4FE, what the select functions last set the shader up with
    unsigned char pad_50C[0x1D];
    bool m_depthCheck;  // 0x529, whether the depth test is on (setDepthBufferCheckOn/Off)
    unsigned char pad_52A[0x6];
    float m_screenWidth;  // LayerAccManager::getScreenWidth
    float m_screenHeight;  // LayerAccManager::getScreenHeight
    float m_screenDivWidth;  // LayerManager::getScreenDivWidth
    unsigned char pad_53C[0x4];
    float m_screenCalcPosWidth;  // LayerManager::getScreenCalcPosWidth
    float m_screenCalcPosHeight;  // LayerManager::getScreenCalcPosHeight
    float m_screenCalcSclWidth;  // LayerManager::getScreenCalcSclWidth
    float m_screenCalcSclHeight;  // LayerManager::getScreenCalcSclHeight
    unsigned char pad_550[0x28];
    float m_gamma;  // LayerAccManager::setGamma
    unsigned char pad_57C[0x4];
};
}  // namespace layer

#endif

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
#include "layer/LayerResViewPortInfo.h"

namespace ml { class EventFileTh; class FileHandleTh; class IDrDrawWorkInfo; }
namespace grlib { class CGLibDblUniformBlock; class CGLibRenderTarget; class CGLibVtxInstans; class CGLibVtxOneInstans; }

namespace layer {
class LayerManager;
class LayerObjTopMaskObj;
class LayerResSecTexture;
class LayerTextureMan;
class LayerVertexMan;
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
// the m_cur* members field by field and set the changed declarations; the names are not the original's)
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
    // sets the viewport of a rectangle unless it is the one set (inline in setViewPort and setShaderMaskMode; the name
    // is not the original's)
    void setViewPortRect(const LayerShdViewPort& viewPort);
    void setSecTexture(LayerResSecTexture* texture);
    void setShaderMaskOff();
    void setDepthBufferCheckOn();
    void setDepthBufferCheckOff();
    void set3DSpaceMode(grlib::CGLibDblUniformBlock* block);
    // selects the shader of m_select's type and binds the blocks and textures of the mask and the second texture
    grlib::CGLibDecShader* setupShader(grlib::CGLibDblUniformBlock* block);
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
    void* m_pShdData;  // 0x08: "/monolib/shader/shd_layout.wishp" (OnFileEvent takes it, shaderRelease frees it)
    void* m_pLutData;  // 0x10: "/monolib/shader/layer_lut.witx"
    int m_lutSize;     // 0x18: the lut read's m_result
    LayerManager* m_pManager;  // 0x20, the constructor's argument (readShader reads with its data handle)
    ml::FileHandleTh* m_hShdFile;  // 0x28, readShader's reads (null once OnFileEvent took the data)
    ml::FileHandleTh* m_hLutFile;  // 0x30
    // the constructor creates both (new, over the manager's work handle); the names are not the original's
    LayerVertexMan* m_vertexMan;    // 0x38
    LayerTextureMan* m_textureMan;  // 0x40: LayerResAddTexObj/LayerResSecTexture share its texture objects
    LayerShdDeclOfs* m_pDeclOfs;  // 0x48, one per shader (the init functions fill it)
    const LayerObjTopMaskObj* m_pMaskObj;  // 0x50, setShaderMaskMode
    grlib::CGLibTextureBuffer* m_pSecTexture;  // 0x58, setSecTexture (null: none)
    grlib::CGLibDblUniformBlock* m_pSecUniform;  // 0x60, the LayerResSecTexture's block
    bool m_renderWorkCreated;  // 0x68, createRenderWork sets it (setupUpdate creates the work once)
    unsigned char pad_69[0x7];
    grlib::CGLibVtxFetch m_fetches[5];  // 0x70
    grlib::CGLibSampler m_samplers[9];  // 0xC0, setupTexture by LayerSamplerType
    grlib::CGLibShdListData m_shdList;  // 0x1E0, the shaders (the init functions read their declarations)
    grlib::CGLibVtxVertex m_defVertices[5];  // 0x238, setupVertex by LayerDefVertType
    grlib::CGLibVtxIndex m_quadIndex;  // 0x300, renderQuadsIndex/renderInstaceQuadsIndex draw it
    grlib::CGLibVtxIndex m_quadIndex2;  // 0x328, a second index buffer (the destructor destroys it on its own: not an array)
    grlib::CGLibDblUniformBlock* m_p3DSpaceBlock;  // 0x350, set3DSpaceMode (null after setDepthBufferCheckOn/Off)
    grlib::CGLibDblUniformBlock* m_pMaskWork;  // 0x358, setViewPort's LayerResViewPortInfo block (cleared by the mask modes)
    grlib::CGLibRenderTarget* m_pRenderTarget;  // 0x360, getDefRenderTarget (the main one when null)
    grlib::CGLibTextureBuffer m_lut;  // 0x368, shaderRelease releases it
    unsigned char pad_3D8[0x118];
    LayerShdSelect m_select;   // 0x4F0, what the next draw asks for (setupShader selects by its shader type)
    // 0x4FE, what the select functions last set the shader up with (LayerShdSelect's values; plain members, not a
    // LayerShdSelect: the select functions read 0x500 and 0x508 as 32-bit loads, so those fields are 4-aligned)
    short m_curShaderType;   // 0x4FE
    short m_curGaugeType;    // 0x500
    short m_curWorldType;    // 0x502
    short m_curIconType;     // 0x504
    short m_curOption;       // 0x506
    short m_curMaskObjType;  // 0x508
    short m_curSecTexType;   // 0x50A
    LayerShdViewPort m_viewPort;  // 0x50C, the last viewport set (layout units)
    unsigned char pad_51C[0xC];
    bool m_viewPortSet;  // 0x528, a viewport other than the full screen is set (resetViewPort resets it)
    bool m_depthCheck;  // 0x529, whether the depth test is on (setDepthBufferCheckOn/Off)
    bool m_renderTargetSet;  // 0x52A, setViewPort bound a render target (the next viewport is set unconditionally)
    unsigned char pad_52B[0x5];
    float m_screenWidth;  // LayerAccManager::getScreenWidth
    float m_screenHeight;  // LayerAccManager::getScreenHeight
    float m_screenDivWidth;  // LayerManager::getScreenDivWidth
    unsigned char pad_53C[0x4];
    float m_screenCalcPosWidth;  // LayerManager::getScreenCalcPosWidth
    float m_screenCalcPosHeight;  // LayerManager::getScreenCalcPosHeight
    float m_screenCalcSclWidth;  // LayerManager::getScreenCalcSclWidth
    float m_screenCalcSclHeight;  // LayerManager::getScreenCalcSclHeight
    float m_baseWidth;   // 0x550, resetViewPort's width
    float m_baseHeight;  // 0x554, resetViewPort's height
    float m_viewPortScale;  // 0x558, layout units to pixels (setViewPort/setShaderMaskMode)
    float m_viewPortSclWidth;   // 0x55C, resetViewPort's width scale
    float m_viewPortSclHeight;  // 0x560
    // 0x564/0x568: LayerObjUtil::updatePosMatrixUniformBlock scales a position matrix's x/y rows by them before
    // moving it by -1/+1 (screen to clip space; the names are not the original's)
    float m_clipSclX;
    float m_clipSclY;
    unsigned char pad_56C[0x8];
    float m_viewPortDivY;  // 0x574, LayerObjUtil::calcLayerRenderView divides the y offset by it (the name is not the original's)
    float m_gamma;  // LayerAccManager::setGamma
    unsigned char pad_57C[0x4];
};
}  // namespace layer

#endif

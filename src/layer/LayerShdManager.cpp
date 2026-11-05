#include "grlib/GrlTypes.h"
#include "grlib/CGLibCtl.h"
#include "grlib/CGLibState.h"
#include "classes/grlib/CGLibShdListBase.h"
#include "classes/grlib/CGLibShdListData.h"
#include "classes/layer/LayerShdManager.h"
#include "classes/layer/LayerHandleAllocator.h"
#include "layer/LayerRceManager.h"
#include "layer/LayerVertexObj.h"
#include "grlib/CGLibDblUniformBlock.h"
#include "grlib/CGLibVtxInstans.h"
#include "grlib/CGLibVtxOneInstans.h"
#include "mtl/MemManager.h"
#include "classes/layer/LayerManager.h"
#include "classes/layer/LayerObjTopMaskObj.h"
#include "classes/ml/DevFileTh.h"
#include "grlib/CGLibRenderTarget.h"
#include "layer/LayerResSecTexture.h"
#include "layer/LayerResViewPortInfo.h"
#include "layer/LayerTextureMan.h"
#include "layer/LayerVertexMan.h"
#include "ml/DevFileParamTh.h"
#include "ml/EventFileTh.h"
#include "layer/LayerPolyVertex.h"
#include "grlib/CGLibTexture.h"
#include <string.h>

namespace layer {

LayerRceManager::~LayerRceManager() {}

LayerShdManager::~LayerShdManager() {
    if (m_vertexMan != nullptr) {
        delete m_vertexMan;
        m_vertexMan = nullptr;
    }
    if (m_textureMan != nullptr) {
        delete m_textureMan;
        m_textureMan = nullptr;
    }
    shaderRelease();
}

void LayerShdManager::shaderRelease() {
    m_shdList.release();
    m_lut.release();
    if (m_pShdData != nullptr) {
        mtl::MemManager::deallocate(m_pShdData, 0, false);
        m_pShdData = nullptr;
    }
    if (m_pLutData != nullptr) {
        mtl::MemManager::deallocate(m_pLutData, 0, false);
        m_pLutData = nullptr;
    }
    m_lutSize = 0;
    if (m_pDeclOfs != nullptr) {
        mtl::MemManager::deallocate(m_pDeclOfs, 0, false);
        m_pDeclOfs = nullptr;
    }
    if (m_hShdFile != nullptr) {
        ml::DevFileTh::cancel(m_hShdFile, false);
        m_hShdFile = nullptr;
    }
    if (m_hLutFile != nullptr) {
        ml::DevFileTh::cancel(m_hLutFile, false);
        m_hLutFile = nullptr;
    }
}

void LayerShdManager::readShader() {
    shaderRelease();
    ml::DevFileParamTh param;
    param.m_hMem = m_pManager->m_dataHandle;
    param.m_listener = this;
    param.m_align = 0x1000;
    param.pad_6d = false;
    param.m_path = "/monolib/shader/shd_layout.wishp";
    m_hShdFile = ml::DevFileTh::readFile(param);
    param.m_path = "/monolib/shader/layer_lut.witx";
    m_hLutFile = ml::DevFileTh::readFile(param);
}

namespace {

// a vertex of colour only (0xC bytes; the type's name is not the original's)
struct ColorVertex {
    float x;
    float y;
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
};

// createRenderWork's default vertex buffers (m_defVertices by LayerDefVertType); the names are not the original's
// a unit quad of white vertices (lbl_71009D513C)
const ColorVertex s_colorQuad[4] = {
    {0.0f, 1.0f, 0xFF, 0xFF, 0xFF, 0xFF},
    {1.0f, 1.0f, 0xFF, 0xFF, 0xFF, 0xFF},
    {1.0f, 0.0f, 0xFF, 0xFF, 0xFF, 0xFF},
    {0.0f, 0.0f, 0xFF, 0xFF, 0xFF, 0xFF},
};
// the same with texture coordinates (lbl_71009D516C)
const LayerPolyVertex s_colorTexQuad[4] = {
    {0.0f, 1.0f, 0xFF, 0xFF, 0xFF, 0xFF, 0.0f, 1.0f},
    {1.0f, 1.0f, 0xFF, 0xFF, 0xFF, 0xFF, 1.0f, 1.0f},
    {1.0f, 0.0f, 0xFF, 0xFF, 0xFF, 0xFF, 1.0f, 0.0f},
    {0.0f, 0.0f, 0xFF, 0xFF, 0xFF, 0xFF, 0.0f, 0.0f},
};
// x, y, u, v per vertex (lbl_71009D51BC)
const float s_texQuad[4][4] = {
    {0.0f, 1.0f, 0.0f, 1.0f},
    {1.0f, 1.0f, 1.0f, 1.0f},
    {1.0f, 0.0f, 1.0f, 0.0f},
    {0.0f, 0.0f, 0.0f, 0.0f},
};
// a full-screen quad (lbl_71009D51FC)
const float s_screenQuad[4][4] = {
    {-1.0f, -1.0f, 0.0f, 1.0f},
    {1.0f, -1.0f, 1.0f, 1.0f},
    {1.0f, 1.0f, 1.0f, 0.0f},
    {-1.0f, 1.0f, 0.0f, 0.0f},
};
// (lbl_71009D523C)
const float s_texQuad2[4][4] = {
    {0.0f, 1.0f, 0.0f, 1.0f},
    {1.0f, 1.0f, 1.0f, 1.0f},
    {1.0f, 0.0f, 1.0f, 0.0f},
    {0.0f, 0.0f, 0.0f, 0.0f},
};
// the quads' indices: a strip of 4, a closed outline of 5 (lbl_71009D527C)
const unsigned char s_quadIndices[6] = {0, 1, 2, 3, 0, 0};

}  // namespace

bool LayerShdManager::setupUpdate() {
    if (m_pShdData == nullptr || m_pLutData == nullptr) {
        return false;
    }
    if (m_pDeclOfs == nullptr) {
        m_shdList.createPacShader(m_pShdData, 1002, true);
        unsigned int size = m_shdList.m_num * sizeof(LayerShdDeclOfs);
        m_pDeclOfs = static_cast<LayerShdDeclOfs*>(
            mtl::MemManager::allocate(m_pManager->m_gxHandle, size, 16, false, "no name", 0));
        memset(m_pDeclOfs, 0xFF, size);
        int num = m_shdList.m_num;
        if (num > 0) {
            int i = 0;
            do {
                (this->*s_CallSetup[i])(i);
            } while (++i != num);
        }
    }
    if (!m_renderWorkCreated) {
        createRenderWork();
    }
    grlib::CGLibTexture::createTextureImagePtrs(m_lut, m_pLutData, m_lutSize, false, nullptr, true);
    return true;
}

void LayerShdManager::createRenderWork() {
    grlib::CGLibVtxAttr attrs[5];
    attrs[0].format = 0x16;
    attrs[0].location = 0;
    attrs[0].offset = 0;
    attrs[0].stream = 0;
    attrs[1].format = 0x25;
    attrs[1].location = 1;
    attrs[1].offset = 8;
    attrs[1].stream = 0;
    m_fetches[0].createFetchObj(attrs, 2);
    attrs[0].format = 0x16;
    attrs[0].location = 0;
    attrs[0].offset = 0;
    attrs[0].stream = 0;
    attrs[1].format = 0x25;
    attrs[1].location = 1;
    attrs[1].offset = 8;
    attrs[1].stream = 0;
    attrs[2].format = 0x16;
    attrs[2].location = 2;
    attrs[2].offset = 0xC;
    attrs[2].stream = 0;
    m_fetches[1].createFetchObj(attrs, 3);
    attrs[0].format = 0x16;
    attrs[0].location = 0;
    attrs[0].offset = 0;
    attrs[0].stream = 0;
    attrs[1].format = 0x16;
    attrs[1].location = 1;
    attrs[1].offset = 8;
    attrs[1].stream = 0;
    attrs[2].format = 0x2E;
    attrs[2].location = 2;
    attrs[2].offset = 0;
    attrs[2].stream = 1;
    attrs[3].format = 0x2E;
    attrs[3].location = 3;
    attrs[3].offset = 0x10;
    attrs[3].stream = 1;
    attrs[4].format = 0x25;
    attrs[4].location = 4;
    attrs[4].offset = 0x20;
    attrs[4].stream = 1;
    m_fetches[2].createFetchObj(attrs, 5);
    attrs[0].format = 0x22;
    attrs[0].location = 0;
    attrs[0].offset = 0;
    attrs[0].stream = 0;
    attrs[1].format = 0x25;
    attrs[1].location = 1;
    attrs[1].offset = 0xC;
    attrs[1].stream = 0;
    attrs[2].format = 0x16;
    attrs[2].location = 2;
    attrs[2].offset = 0x10;
    attrs[2].stream = 0;
    m_fetches[3].createFetchObj(attrs, 3);
    attrs[0].format = 0x16;
    attrs[0].location = 0;
    attrs[0].offset = 0;
    attrs[0].stream = 0;
    attrs[1].format = 0x16;
    attrs[1].location = 1;
    attrs[1].offset = 8;
    attrs[1].stream = 0;
    m_fetches[4].createFetchObj(attrs, 2);

    m_samplers[0].initSampler(GrlTexClamp(0), GrlTexMagFilterType(0));
    m_samplers[0].updateData();
    m_samplers[1].initSampler(GrlTexClamp(0), GrlTexMagFilterType(1));
    m_samplers[1].updateData();
    m_samplers[3].initSampler(GrlTexClamp(2), GrlTexMagFilterType(1));
    m_samplers[3].updateData();
    m_samplers[2].initSampler(GrlTexClamp(2), GrlTexMagFilterType(0));
    m_samplers[2].updateData();
    m_samplers[5].initSampler(GrlTexClamp(2), GrlTexMagFilterType(1));
    m_samplers[5].setFilter(GrlTexMagFilterType(1), GrlTexMinFilterType(5), GrlTexTexAnisoRatio(0));
    m_samplers[5].updateData();
    m_samplers[4].initSampler(GrlTexClamp(2), GrlTexMagFilterType(0));
    m_samplers[4].setFilter(GrlTexMagFilterType(0), GrlTexMinFilterType(2), GrlTexTexAnisoRatio(0));
    m_samplers[4].updateData();
    m_samplers[6].initSampler(GrlTexClamp(6), GrlTexMagFilterType(1));
    m_samplers[6].setBorderType(GrlTexBorderType(0));
    m_samplers[6].updateData();
    m_samplers[7].initSampler(GrlTexClamp(2), GrlTexMagFilterType(1));
    m_samplers[7].setClamp(GrlTexClamp(0), GrlTexClamp(2), GrlTexClamp(2));
    m_samplers[7].updateData();
    m_samplers[8].initSampler(GrlTexClamp(2), GrlTexMagFilterType(1));
    m_samplers[8].setClamp(GrlTexClamp(2), GrlTexClamp(0), GrlTexClamp(2));
    m_samplers[8].updateData();

    m_defVertices[0].createCopyVertexBuff(s_colorQuad, sizeof(s_colorQuad), sizeof(s_colorQuad[0]));
    m_defVertices[1].createCopyVertexBuff(s_colorTexQuad, sizeof(s_colorTexQuad), sizeof(s_colorTexQuad[0]));
    m_defVertices[2].createCopyVertexBuff(s_texQuad, sizeof(s_texQuad), sizeof(s_texQuad[0]));
    m_defVertices[3].createCopyVertexBuff(s_screenQuad, sizeof(s_screenQuad), sizeof(s_screenQuad[0]));
    m_defVertices[4].createCopyVertexBuff(s_texQuad2, sizeof(s_texQuad2), sizeof(s_texQuad2[0]));
    m_quadIndex.createCopyIndexBuff(s_quadIndices, 4, GrlPrimitiveType(7), GrlIndexFormat(0));
    m_quadIndex2.createCopyIndexBuff(s_quadIndices, 5, GrlPrimitiveType(3), GrlIndexFormat(0));
    m_renderWorkCreated = true;
}

void LayerShdManager::resetViewPort() {
    if (m_viewPortSet) {
        m_pRenderTarget = nullptr;
        m_viewPortSet = false;
        m_renderTargetSet = false;
        m_viewPort.m_x = 0.0f;
        m_viewPort.m_y = 0.0f;
        m_viewPort.m_width = m_baseWidth;
        m_viewPort.m_height = m_baseHeight;
        float width = m_baseWidth * m_viewPortSclWidth;
        float height = m_baseHeight * m_viewPortSclHeight;
        grlib::LibMainStateViewPort viewport;
        viewport.x = 0.0f;
        viewport.y = 0.0f;
        viewport.width = width;
        viewport.height = height;
        viewport.minDepth = 0.0f;
        viewport.maxDepth = 1.0f;
        grlib::CGLibState::setViewport(viewport);
    }
}

void LayerShdManager::endShader(const ml::IDrDrawWorkInfo*) {
    setupMainRenderTarget();
    resetViewPort();
}

void LayerShdManager::setupMainRenderTarget() {
    grlib::CGLibState::setMainFrameBuffer();
}

// sets the viewport of the rectangle unless it is the one set (inline in setViewPort and setShaderMaskMode)
inline void LayerShdManager::setViewPortRect(const LayerShdViewPort& viewPort) {
    if (m_renderTargetSet || m_viewPort.m_x != viewPort.m_x || m_viewPort.m_y != viewPort.m_y ||
        m_viewPort.m_width != viewPort.m_width || m_viewPort.m_height != viewPort.m_height) {
        m_viewPort = viewPort;
        m_viewPortSet = true;
        m_renderTargetSet = false;
        float scale = m_viewPortScale;
        float width = scale * viewPort.m_width;
        float height = scale * viewPort.m_height;
        float x = scale * viewPort.m_x;
        float y = scale * viewPort.m_y;
        grlib::LibMainStateViewPort state;
        state.x = x;
        state.y = y;
        state.width = width;
        state.height = height;
        state.minDepth = 0.0f;
        state.maxDepth = 1.0f;
        grlib::CGLibState::setViewport(state);
    }
}

void LayerShdManager::setViewPort(LayerResViewPortInfo* info) {
    if (info->m_pRenderTarget != nullptr) {
        if (m_pRenderTarget != info->m_pRenderTarget) {
            if (!(info->m_flags & 1)) {
                info->m_pRenderTarget->clearTexture(info->m_clearColor, GrlClaerMask(0xF));
                info->m_flags |= 1;
            }
            info->m_pRenderTarget->setRenderTarget();
            m_renderTargetSet = true;
            m_viewPortSet = true;
            m_pRenderTarget = info->m_pRenderTarget;
            m_viewPort.m_x = 0.0f;
            m_viewPort.m_y = 0.0f;
            m_viewPort.m_width = info->m_pRenderTarget->m_width / m_viewPortScale;
            m_viewPort.m_height = info->m_pRenderTarget->m_height / m_viewPortScale;
        }
    } else {
        m_pRenderTarget = nullptr;
        setViewPortRect(info->m_viewPort);
    }
    m_pMaskWork = info->m_pUniform;
    m_select.m_maskObjType = 3;
}

void LayerShdManager::setShaderMaskMode(const LayerObjTopMaskObj* maskObj) {
    m_pMaskObj = maskObj;
    m_pMaskWork = nullptr;
    m_select.m_maskObjType = 2;
    setViewPortRect(maskObj->m_viewPort);
}

void LayerShdManager::setSecTexture(LayerResSecTexture* texture) {
    if (texture != nullptr && texture->m_value > 0.0f) {
        m_pSecTexture = texture->getTexture();
        m_pSecUniform = &texture->m_uniform;
        m_select.m_secTexType = 2;
    } else {
        m_pSecTexture = nullptr;
        m_select.m_secTexType = 1;
    }
}

void LayerShdManager::setShaderMaskOff() {
    m_pMaskWork = nullptr;
    m_pMaskObj = nullptr;
    m_select.m_maskObjType = 1;
}

void LayerShdManager::setDepthBufferCheckOn() {
    if (!m_depthCheck) {
        grlib::CGLibDepthCtl::setDepthControl(1, 0, GrlCompare(3));
        m_depthCheck = true;
    }
    m_select.m_worldType = 1;
    m_p3DSpaceBlock = nullptr;
}

void LayerShdManager::setDepthBufferCheckOff() {
    if (m_depthCheck) {
        grlib::CGLibDepthCtl::setDepthControl(0, 0, GrlCompare(1));
        m_depthCheck = false;
    }
    m_select.m_worldType = 1;
    m_p3DSpaceBlock = nullptr;
}

void LayerShdManager::set3DSpaceMode(grlib::CGLibDblUniformBlock* block) {
    if (!m_depthCheck) {
        grlib::CGLibDepthCtl::setDepthControl(1, 0, GrlCompare(3));
        m_depthCheck = true;
    }
    m_select.m_worldType = 2;
    m_p3DSpaceBlock = block;
}

grlib::CGLibDecShader* LayerShdManager::setupShader(grlib::CGLibDblUniformBlock* block) {
    grlib::CGLibDecShader* shader = (this->*s_CallSelect[m_select.m_shaderType])();
    block->setUniformBlock(0);
    // the mask object is handed in const; its uniform block is bound all the same
    LayerObjTopMaskObj* maskObj = const_cast<LayerObjTopMaskObj*>(m_pMaskObj);
    if (maskObj != nullptr) {
        maskObj->m_uniform.setUniformBlock(2);
        grlib::CGLibCtlTexture::setTexture(maskObj->getTexture(), m_samplers[6], 3);
    } else if (m_pMaskWork != nullptr) {
        m_pMaskWork->setUniformBlock(2);
    }
    if (m_pSecTexture != nullptr) {
        m_pSecUniform->setUniformBlock(3);
        grlib::CGLibCtlTexture::setTexture(*m_pSecTexture, m_samplers[3], 2);
    }
    return shader;
}

void LayerShdManager::setupTexture(const grlib::CGLibTextureBuffer& texture, LayerSamplerType sampler,
                                   unsigned int location) {
    grlib::CGLibCtlTexture::setTexture(texture, m_samplers[sampler], location);
}

grlib::CGLibDecShader* LayerShdManager::setupShader() {
    return (this->*s_CallSelect[m_select.m_shaderType])();
}

grlib::CGLibRenderTarget* LayerShdManager::getDefRenderTarget() {
    if (m_pRenderTarget != nullptr) {
        return m_pRenderTarget;
    }
    return grlib::CGLibState::getMainRenderTarget();
}

bool LayerShdManager::OnFileEvent(ml::EventFileTh* event) {
    if (event->m_kind == 2) {
        if (m_hShdFile == event->m_handle) {
            m_pShdData = event->moveFileData();
            m_hShdFile = nullptr;
        }
        if (m_hLutFile == event->m_handle) {
            m_pLutData = event->moveFileData();
            m_lutSize = event->m_result;
            m_hLutFile = nullptr;
        }
    }
    return true;
}

void LayerShdManager::setupVertex(LayerVertexObj* obj, unsigned int index) {
    obj->setVertex(index);
}

void LayerShdManager::setupVertex(LayerDefVertType type) {
    grlib::CGLibCtlVertex::setVertex(m_defVertices[type]);
}

void LayerShdManager::setupInstaceVertex(grlib::CGLibVtxInstans& vertex, unsigned int first, unsigned int count) {
    grlib::CGLibCtlVertex::setInstanceVertex(vertex, first, count, 1, 1);
}

void LayerShdManager::setupInstaceVertex(grlib::CGLibVtxOneInstans& vertex, unsigned int first, unsigned int count) {
    grlib::CGLibCtlVertex::setInstanceVertex(vertex, first, count, 1, 1);
}

void LayerShdManager::renderQuadsIndex() {
    m_quadIndex.drawIndex();
}

void LayerShdManager::renderInstaceQuadsIndex(unsigned int instances) {
    m_quadIndex.drawInsIndex(instances);
}

void LayerShdManager::setupBlendDef() {
    grlib::CGLibColorCtl::setBlendControl(GrlBlendFunc(5), GrlBlendFunc(6), GrlBlendCombine(1), GrlBlendFunc(2), GrlBlendFunc(6), GrlBlendCombine(1), GrlLogicType(3));
}

void LayerShdManager::setupBlendSwf() {
    grlib::CGLibColorCtl::setBlendControl(GrlBlendFunc(2), GrlBlendFunc(6), GrlBlendCombine(1), GrlBlendFunc(2), GrlBlendFunc(6), GrlBlendCombine(1), GrlLogicType(3));
}

void LayerShdManager::setupBlendNo() {
    grlib::CGLibColorCtl::setBlendOffControl(GrlLogicType(3));
}

void LayerShdManager::setupBlendAdd() {
    grlib::CGLibColorCtl::setBlendControl(GrlBlendFunc(5), GrlBlendFunc(2), GrlBlendCombine(1), GrlBlendFunc(2), GrlBlendFunc(2), GrlBlendCombine(1), GrlLogicType(3));
}

void LayerShdManager::setupBlendAddSwf() {
    grlib::CGLibColorCtl::setBlendControl(GrlBlendFunc(2), GrlBlendFunc(2), GrlBlendCombine(1), GrlBlendFunc(2), GrlBlendFunc(2), GrlBlendCombine(1), GrlLogicType(3));
}

void LayerShdManager::setupBlendSub() {
    grlib::CGLibColorCtl::setBlendControl(GrlBlendFunc(5), GrlBlendFunc(2), GrlBlendCombine(2), GrlBlendFunc(2), GrlBlendFunc(2), GrlBlendCombine(2), GrlLogicType(3));
}

void LayerShdManager::setupBlendSubSwf() {
    grlib::CGLibColorCtl::setBlendControl(GrlBlendFunc(2), GrlBlendFunc(2), GrlBlendCombine(2), GrlBlendFunc(2), GrlBlendFunc(2), GrlBlendCombine(2), GrlLogicType(3));
}

void LayerShdManager::setupBlendMul() {
    grlib::CGLibColorCtl::setBlendControl(GrlBlendFunc(1), GrlBlendFunc(3), GrlBlendCombine(1), GrlBlendFunc(1), GrlBlendFunc(5), GrlBlendCombine(1), GrlLogicType(3));
}

void LayerShdManager::initColor(unsigned int idx) {
    LayerShdDeclOfs& ofs = m_pDeclOfs[idx];
    const grlib::CGLibDecShader& shader = m_shdList.m_pList[idx];
    ofs.m_gaugeType = shader.getDeclarationOfs("MENU_GAUGE_TYPE");
    ofs.m_worldType = shader.getDeclarationOfs("MENU_WORLD_TYPE");
    ofs.m_maskObjType = shader.getDeclarationOfs("MENU_MASKOBJ_TYPE");
    ofs.m_option = shader.getDeclarationOfs("MENU_FILBLEND_TYPE");
    ofs.m_secTexType = shader.getDeclarationOfs("MENU_SECTEX_TYPE");
}

void LayerShdManager::initTex(unsigned int idx) {
    LayerShdDeclOfs& ofs = m_pDeclOfs[idx];
    const grlib::CGLibDecShader& shader = m_shdList.m_pList[idx];
    ofs.m_gaugeType = shader.getDeclarationOfs("MENU_GAUGE_TYPE");
    ofs.m_worldType = shader.getDeclarationOfs("MENU_WORLD_TYPE");
    ofs.m_maskObjType = shader.getDeclarationOfs("MENU_MASKOBJ_TYPE");
    ofs.m_option = shader.getDeclarationOfs("MENU_FILBLEND_TYPE");
    ofs.m_secTexType = shader.getDeclarationOfs("MENU_SECTEX_TYPE");
}

void LayerShdManager::initFont(unsigned int idx) {
    LayerShdDeclOfs& ofs = m_pDeclOfs[idx];
    const grlib::CGLibDecShader& shader = m_shdList.m_pList[idx];
    ofs.m_worldType = shader.getDeclarationOfs("MENU_WORLD_TYPE");
    ofs.m_iconType = shader.getDeclarationOfs("MENU_ICON_TYPE");
    ofs.m_maskObjType = shader.getDeclarationOfs("MENU_MASKOBJ_TYPE");
}

void LayerShdManager::initWin(unsigned int idx) {
    LayerShdDeclOfs& ofs = m_pDeclOfs[idx];
    const grlib::CGLibDecShader& shader = m_shdList.m_pList[idx];
    ofs.m_gaugeType = shader.getDeclarationOfs("MENU_GAUGE_TYPE");
    ofs.m_worldType = shader.getDeclarationOfs("MENU_WORLD_TYPE");
    ofs.m_maskObjType = shader.getDeclarationOfs("MENU_MASKOBJ_TYPE");
    ofs.m_secTexType = shader.getDeclarationOfs("MENU_SECTEX_TYPE");
}

void LayerShdManager::initNumber(unsigned int idx) {
    LayerShdDeclOfs& ofs = m_pDeclOfs[idx];
    const grlib::CGLibDecShader& shader = m_shdList.m_pList[idx];
    ofs.m_worldType = shader.getDeclarationOfs("MENU_WORLD_TYPE");
    ofs.m_maskObjType = shader.getDeclarationOfs("MENU_MASKOBJ_TYPE");
    ofs.m_secTexType = shader.getDeclarationOfs("MENU_SECTEX_TYPE");
}

void LayerShdManager::initPoly(unsigned int idx) {
    LayerShdDeclOfs& ofs = m_pDeclOfs[idx];
    const grlib::CGLibDecShader& shader = m_shdList.m_pList[idx];
    ofs.m_worldType = shader.getDeclarationOfs("MENU_WORLD_TYPE");
    ofs.m_option = shader.getDeclarationOfs("MENU_USE_TEX");
    ofs.m_maskObjType = shader.getDeclarationOfs("MENU_MASKOBJ_TYPE");
    ofs.m_secTexType = shader.getDeclarationOfs("MENU_SECTEX_TYPE");
}

void LayerShdManager::initGsBlur(unsigned int idx) {
    LayerShdDeclOfs& ofs = m_pDeclOfs[idx];
    const grlib::CGLibDecShader& shader = m_shdList.m_pList[idx];
    ofs.m_option = shader.getDeclarationOfs("MENU_USE_TEX");
}

void LayerShdManager::initFlowMap(unsigned int) {}

void LayerShdManager::initMemWrite(unsigned int idx) {
    LayerShdDeclOfs& ofs = m_pDeclOfs[idx];
    const grlib::CGLibDecShader& shader = m_shdList.m_pList[idx];
    ofs.m_option = shader.getDeclarationOfs("MENU_DECODE_TYPE");
}

void LayerShdManager::initGamma(unsigned int) {}

void LayerShdManager::initDebug(unsigned int idx) {
    LayerShdDeclOfs& ofs = m_pDeclOfs[idx];
    const grlib::CGLibDecShader& shader = m_shdList.m_pList[idx];
    ofs.m_worldType = shader.getDeclarationOfs("MENU_WORLD_TYPE");
    ofs.m_option = shader.getDeclarationOfs("MENU_USE_TEX");
}

void LayerShdManager::initTest(unsigned int idx) {
    LayerShdDeclOfs& ofs = m_pDeclOfs[idx];
    const grlib::CGLibDecShader& shader = m_shdList.m_pList[idx];
    ofs.m_option = shader.getDeclarationOfs("MENU_USE_TEX");
}

grlib::CGLibDecShader* LayerShdManager::selectColor() {
    unsigned int type = m_select.m_shaderType;
    grlib::CGLibDecShader& shader = *(m_shdList.m_pList + type);
    const LayerShdDeclOfs& ofs = m_pDeclOfs[m_select.m_shaderType];
    if (m_select.m_shaderType != m_curShaderType ||
        m_curGaugeType != m_select.m_gaugeType ||
        m_select.m_worldType != m_curWorldType ||
        m_curMaskObjType != m_select.m_maskObjType ||
        m_curOption != m_select.m_option ||
        m_curSecTexType != m_select.m_secTexType) {
        shader.setDeclarationIdx(ofs.m_gaugeType, m_select.m_gaugeType);
        shader.setDeclarationIdx(ofs.m_worldType, m_select.m_worldType);
        shader.setDeclarationIdx(ofs.m_maskObjType, m_select.m_maskObjType);
        shader.setDeclarationIdx(ofs.m_option, m_select.m_option);
        shader.setDeclarationIdx(ofs.m_secTexType, m_select.m_secTexType);
        grlib::CGLibCtlShader::setShader(shader, m_fetches[s_eFetchTbl[m_select.m_shaderType]]);
        if (m_p3DSpaceBlock != nullptr) {
            m_p3DSpaceBlock->setUniformBlock(1);
        }
        m_curShaderType = m_select.m_shaderType;
        m_curGaugeType = m_select.m_gaugeType;
        m_curWorldType = m_select.m_worldType;
        m_curMaskObjType = m_select.m_maskObjType;
        m_curOption = m_select.m_option;
        m_curSecTexType = m_select.m_secTexType;
    }
    return &shader;
}

grlib::CGLibDecShader* LayerShdManager::selectTex() {
    unsigned int type = m_select.m_shaderType;
    grlib::CGLibDecShader& shader = *(m_shdList.m_pList + type);
    const LayerShdDeclOfs& ofs = m_pDeclOfs[m_select.m_shaderType];
    if (m_select.m_shaderType != m_curShaderType ||
        m_curGaugeType != m_select.m_gaugeType ||
        m_select.m_worldType != m_curWorldType ||
        m_curMaskObjType != m_select.m_maskObjType ||
        m_curOption != m_select.m_option ||
        m_curSecTexType != m_select.m_secTexType) {
        shader.setDeclarationIdx(ofs.m_gaugeType, m_select.m_gaugeType);
        shader.setDeclarationIdx(ofs.m_worldType, m_select.m_worldType);
        shader.setDeclarationIdx(ofs.m_maskObjType, m_select.m_maskObjType);
        shader.setDeclarationIdx(ofs.m_option, m_select.m_option);
        shader.setDeclarationIdx(ofs.m_secTexType, m_select.m_secTexType);
        grlib::CGLibCtlShader::setShader(shader, m_fetches[s_eFetchTbl[m_select.m_shaderType]]);
        if (m_p3DSpaceBlock != nullptr) {
            m_p3DSpaceBlock->setUniformBlock(1);
        }
        m_curShaderType = m_select.m_shaderType;
        m_curGaugeType = m_select.m_gaugeType;
        m_curWorldType = m_select.m_worldType;
        m_curMaskObjType = m_select.m_maskObjType;
        m_curOption = m_select.m_option;
        m_curSecTexType = m_select.m_secTexType;
    }
    return &shader;
}

grlib::CGLibDecShader* LayerShdManager::selectFont() {
    unsigned int type = m_select.m_shaderType;
    grlib::CGLibDecShader& shader = *(m_shdList.m_pList + type);
    const LayerShdDeclOfs& ofs = m_pDeclOfs[m_select.m_shaderType];
    if (m_select.m_shaderType != m_curShaderType ||
        m_curIconType != m_select.m_iconType ||
        m_select.m_worldType != m_curWorldType ||
        m_curMaskObjType != m_select.m_maskObjType) {
        shader.setDeclarationIdx(ofs.m_worldType, m_select.m_worldType);
        shader.setDeclarationIdx(ofs.m_iconType, m_select.m_iconType);
        shader.setDeclarationIdx(ofs.m_maskObjType, m_select.m_maskObjType);
        grlib::CGLibCtlShader::setShader(shader, m_fetches[s_eFetchTbl[m_select.m_shaderType]]);
        if (m_p3DSpaceBlock != nullptr) {
            m_p3DSpaceBlock->setUniformBlock(1);
        }
        m_curShaderType = m_select.m_shaderType;
        m_curWorldType = m_select.m_worldType;
        m_curIconType = m_select.m_iconType;
        m_curMaskObjType = m_select.m_maskObjType;
    }
    return &shader;
}

grlib::CGLibDecShader* LayerShdManager::selectWin() {
    unsigned int type = m_select.m_shaderType;
    grlib::CGLibDecShader& shader = *(m_shdList.m_pList + type);
    const LayerShdDeclOfs& ofs = m_pDeclOfs[m_select.m_shaderType];
    if (m_select.m_shaderType != m_curShaderType ||
        m_curGaugeType != m_select.m_gaugeType ||
        m_select.m_worldType != m_curWorldType ||
        m_curMaskObjType != m_select.m_maskObjType ||
        m_curSecTexType != m_select.m_secTexType) {
        shader.setDeclarationIdx(ofs.m_gaugeType, m_select.m_gaugeType);
        shader.setDeclarationIdx(ofs.m_worldType, m_select.m_worldType);
        shader.setDeclarationIdx(ofs.m_maskObjType, m_select.m_maskObjType);
        shader.setDeclarationIdx(ofs.m_secTexType, m_select.m_secTexType);
        grlib::CGLibCtlShader::setShader(shader, m_fetches[s_eFetchTbl[m_select.m_shaderType]]);
        if (m_p3DSpaceBlock != nullptr) {
            m_p3DSpaceBlock->setUniformBlock(1);
        }
        m_curShaderType = m_select.m_shaderType;
        m_curGaugeType = m_select.m_gaugeType;
        m_curWorldType = m_select.m_worldType;
        m_curMaskObjType = m_select.m_maskObjType;
        m_curSecTexType = m_select.m_secTexType;
    }
    return &shader;
}

grlib::CGLibDecShader* LayerShdManager::selectIcon() {
    unsigned int type = m_select.m_shaderType;
    grlib::CGLibDecShader& shader = *(m_shdList.m_pList + type);
    const LayerShdDeclOfs& ofs = m_pDeclOfs[m_select.m_shaderType];
    if (m_select.m_shaderType != m_curShaderType ||
        m_curGaugeType != m_select.m_gaugeType ||
        m_select.m_worldType != m_curWorldType ||
        m_curMaskObjType != m_select.m_maskObjType ||
        m_curSecTexType != m_select.m_secTexType) {
        shader.setDeclarationIdx(ofs.m_gaugeType, m_select.m_gaugeType);
        shader.setDeclarationIdx(ofs.m_worldType, m_select.m_worldType);
        shader.setDeclarationIdx(ofs.m_maskObjType, m_select.m_maskObjType);
        shader.setDeclarationIdx(ofs.m_secTexType, m_select.m_secTexType);
        grlib::CGLibCtlShader::setShader(shader, m_fetches[s_eFetchTbl[m_select.m_shaderType]]);
        if (m_p3DSpaceBlock != nullptr) {
            m_p3DSpaceBlock->setUniformBlock(1);
        }
        m_curShaderType = m_select.m_shaderType;
        m_curGaugeType = m_select.m_gaugeType;
        m_curWorldType = m_select.m_worldType;
        m_curMaskObjType = m_select.m_maskObjType;
        m_curSecTexType = m_select.m_secTexType;
    }
    return &shader;
}

grlib::CGLibDecShader* LayerShdManager::selectNumber() {
    unsigned int type = m_select.m_shaderType;
    grlib::CGLibDecShader& shader = *(m_shdList.m_pList + type);
    const LayerShdDeclOfs& ofs = m_pDeclOfs[m_select.m_shaderType];
    if (m_select.m_shaderType != m_curShaderType ||
        m_select.m_worldType != m_curWorldType ||
        m_curMaskObjType != m_select.m_maskObjType ||
        m_curSecTexType != m_select.m_secTexType) {
        shader.setDeclarationIdx(ofs.m_worldType, m_select.m_worldType);
        shader.setDeclarationIdx(ofs.m_maskObjType, m_select.m_maskObjType);
        shader.setDeclarationIdx(ofs.m_secTexType, m_select.m_secTexType);
        grlib::CGLibCtlShader::setShader(shader, m_fetches[s_eFetchTbl[m_select.m_shaderType]]);
        if (m_p3DSpaceBlock != nullptr) {
            m_p3DSpaceBlock->setUniformBlock(1);
        }
        m_curShaderType = m_select.m_shaderType;
        m_curWorldType = m_select.m_worldType;
        m_curMaskObjType = m_select.m_maskObjType;
        m_curSecTexType = m_select.m_secTexType;
    }
    return &shader;
}

grlib::CGLibDecShader* LayerShdManager::selectPoly() {
    unsigned int type = m_select.m_shaderType;
    grlib::CGLibDecShader& shader = *(m_shdList.m_pList + type);
    const LayerShdDeclOfs& ofs = m_pDeclOfs[m_select.m_shaderType];
    if (m_select.m_shaderType != m_curShaderType ||
        m_select.m_worldType != m_curWorldType ||
        m_curOption != m_select.m_option ||
        m_curMaskObjType != m_select.m_maskObjType ||
        m_curSecTexType != m_select.m_secTexType) {
        shader.setDeclarationIdx(ofs.m_worldType, m_select.m_worldType);
        shader.setDeclarationIdx(ofs.m_option, m_select.m_option);
        shader.setDeclarationIdx(ofs.m_maskObjType, m_select.m_maskObjType);
        shader.setDeclarationIdx(ofs.m_secTexType, m_select.m_secTexType);
        grlib::CGLibCtlShader::setShader(shader, m_fetches[s_eFetchTbl[m_select.m_shaderType]]);
        m_curShaderType = m_select.m_shaderType;
        m_curWorldType = m_select.m_worldType;
        m_curOption = m_select.m_option;
        m_curMaskObjType = m_select.m_maskObjType;
        m_curSecTexType = m_select.m_secTexType;
    }
    return &shader;
}

grlib::CGLibDecShader* LayerShdManager::selectGsBlur() {
    unsigned int type = m_select.m_shaderType;
    grlib::CGLibDecShader& shader = *(m_shdList.m_pList + type);
    const LayerShdDeclOfs& ofs = m_pDeclOfs[m_select.m_shaderType];
    if (m_select.m_shaderType != m_curShaderType ||
        m_select.m_option != m_curOption) {
        shader.setDeclarationIdx(ofs.m_option, m_select.m_option);
        grlib::CGLibCtlShader::setShader(shader, m_fetches[s_eFetchTbl[m_select.m_shaderType]]);
        m_curShaderType = m_select.m_shaderType;
        m_curOption = m_select.m_option;
    }
    return &shader;
}

grlib::CGLibDecShader* LayerShdManager::selectFlowMap() {
    unsigned int type = m_select.m_shaderType;
    grlib::CGLibDecShader& shader = *(m_shdList.m_pList + type);
    if (m_select.m_shaderType != m_curShaderType) {
        grlib::CGLibCtlShader::setShader(shader, m_fetches[s_eFetchTbl[m_select.m_shaderType]]);
        m_curShaderType = m_select.m_shaderType;
    }
    return &shader;
}

grlib::CGLibDecShader* LayerShdManager::selectMemWrite() {
    unsigned int type = m_select.m_shaderType;
    grlib::CGLibDecShader& shader = *(m_shdList.m_pList + type);
    if (m_select.m_shaderType != m_curShaderType ||
        m_curOption != m_select.m_option) {
        shader.setDeclarationIdx(m_pDeclOfs[m_select.m_shaderType].m_option, m_select.m_option);
        grlib::CGLibCtlShader::setShader(shader, m_fetches[s_eFetchTbl[m_select.m_shaderType]]);
        m_curShaderType = m_select.m_shaderType;
        m_curOption = m_select.m_option;
    }
    return &shader;
}

grlib::CGLibDecShader* LayerShdManager::selectGamma() {
    unsigned int type = m_select.m_shaderType;
    grlib::CGLibDecShader& shader = *(m_shdList.m_pList + type);
    if (m_select.m_shaderType != m_curShaderType) {
        grlib::CGLibCtlShader::setShader(shader, m_fetches[s_eFetchTbl[m_select.m_shaderType]]);
        m_curShaderType = m_select.m_shaderType;
    }
    return &shader;
}

grlib::CGLibDecShader* LayerShdManager::selectDebug() {
    unsigned int type = m_select.m_shaderType;
    grlib::CGLibDecShader& shader = *(m_shdList.m_pList + type);
    const LayerShdDeclOfs& ofs = m_pDeclOfs[m_select.m_shaderType];
    if (m_select.m_shaderType != m_curShaderType ||
        m_select.m_worldType != m_curWorldType ||
        m_curOption != m_select.m_option) {
        shader.setDeclarationIdx(ofs.m_worldType, m_select.m_worldType);
        shader.setDeclarationIdx(ofs.m_option, m_select.m_option);
        grlib::CGLibCtlShader::setShader(shader, m_fetches[s_eFetchTbl[m_select.m_shaderType]]);
        m_curShaderType = m_select.m_shaderType;
        m_curWorldType = m_select.m_worldType;
        m_curOption = m_select.m_option;
    }
    return &shader;
}

grlib::CGLibDecShader* LayerShdManager::selectTest() {
    unsigned int type = m_select.m_shaderType;
    grlib::CGLibDecShader& shader = *(m_shdList.m_pList + type);
    const LayerShdDeclOfs& ofs = m_pDeclOfs[m_select.m_shaderType];
    if (m_select.m_shaderType != m_curShaderType ||
        m_curOption != m_select.m_option) {
        shader.setDeclarationIdx(ofs.m_option, m_select.m_option);
        grlib::CGLibCtlShader::setShader(shader, m_fetches[s_eFetchTbl[m_select.m_shaderType]]);
        m_curShaderType = m_select.m_shaderType;
    }
    return &shader;
}

void (LayerShdManager::*LayerShdManager::s_CallSetup[13])(unsigned int) = {
    &LayerShdManager::initColor,  &LayerShdManager::initTex,      &LayerShdManager::initFont,
    &LayerShdManager::initWin,    &LayerShdManager::initTex,      &LayerShdManager::initNumber,
    &LayerShdManager::initPoly,   &LayerShdManager::initGsBlur,   &LayerShdManager::initFlowMap,
    &LayerShdManager::initMemWrite, &LayerShdManager::initGamma,  &LayerShdManager::initDebug,
    &LayerShdManager::initTest,
};
grlib::CGLibDecShader* (LayerShdManager::*LayerShdManager::s_CallSelect[13])() = {
    &LayerShdManager::selectColor,    &LayerShdManager::selectTex,      &LayerShdManager::selectFont,
    &LayerShdManager::selectWin,      &LayerShdManager::selectIcon,     &LayerShdManager::selectNumber,
    &LayerShdManager::selectPoly,     &LayerShdManager::selectGsBlur,   &LayerShdManager::selectFlowMap,
    &LayerShdManager::selectMemWrite, &LayerShdManager::selectGamma,    &LayerShdManager::selectDebug,
    &LayerShdManager::selectTest,
};
void (*LayerShdManager::s_CallBlend[8])() = {
    &LayerShdManager::setupBlendDef, &LayerShdManager::setupBlendSwf,    &LayerShdManager::setupBlendNo,
    &LayerShdManager::setupBlendAdd, &LayerShdManager::setupBlendAddSwf, &LayerShdManager::setupBlendSub,
    &LayerShdManager::setupBlendSubSwf, &LayerShdManager::setupBlendMul,
};

LayerHandleAllocator::LayerHandleAllocator() {}

void LayerHandleAllocator::setMemHandle(mtl::ALLOC_HANDLE handle) {
    m_memHandle = handle;
}

void* LayerHandleAllocator::allocate(unsigned long size, unsigned long alignment) {
    return mtl::MemManager::allocate(m_memHandle, size, alignment, false, "no name", 0);
}

void LayerHandleAllocator::deallocate(void* memory) {
    if (memory != nullptr) {
        mtl::MemManager::deallocate(memory, 0, false);
    }
}

}  // namespace layer

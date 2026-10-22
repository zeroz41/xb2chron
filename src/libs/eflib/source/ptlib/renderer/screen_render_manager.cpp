#include "grlib/GrlTypes.h"
#include "grlib/CGLibCtl.h"
#include "grlib/CGLibDecShader.h"
#include "grlib/CGLibEtcUniformBlock.h"
#include "grlib/CGLibRenderTarget.h"
#include "grlib/CGLibTextureBuffer.h"
#include "ptlib/DrDrawWorkInfoEF.h"
#include "ptlib/renderer/ShaderManager.h"
#include "ptlib/renderer/RendererObj.h"
#include "ptlib/renderer/ScreenRenderManager.h"
#include "classes/ptlib/material/MaterialTexture.h"
#include "ptlib/renderer/RendererManager.h"
#include "ptlib/ParticleSystem.h"
#include "ptlib/StackAllocater.h"
#include "mm/MMStdBase.h"
#include "mm/Mat44.h"
#include "mm/Col4.h"
#include "mm/Vec4.h"
#include "new"

namespace ptlib { namespace screen {

// the quad: x, y, z, u, v per corner (the names are not the original's)
static float s_vertices[] = {
    -1.0f, -1.0f, 0.5f, 0.0f, 1.0f,  //
    1.0f,  -1.0f, 0.5f, 1.0f, 1.0f,  //
    1.0f,  1.0f,  0.5f, 1.0f, 0.0f,  //
    -1.0f, 1.0f,  0.5f, 0.0f, 0.0f,
};
static const unsigned short s_indices[] = {0, 1, 2, 3};

static ScreenRenderManager* s_pIns;

// RenderScreen's uniform block (the names are not the original's)
struct ScreenParam {
    float scaleX;
    float scaleY;
    float offsetX;
    float offsetY;
    mm::Col4 color;
    mm::Vec4 param;
};

void ScreenRenderManager::init() {
#line 98
    MM_ASSERT(!getPtr());
#line 102
    StaticAllocObj* alloc = StaticAllocObj::create(0x2F0, __FILE__, __LINE__);
    getPtr() = static_cast<ScreenRenderManager*>(alloc->sysAlloc(sizeof(ScreenRenderManager), 16, nullptr, 0));
    new (getPtr()) ScreenRenderManager();
    if (getPtr() != nullptr) {
        getPtr()->InitSub(alloc);
    }
}

ScreenRenderManager*& ScreenRenderManager::getPtr() {
    return s_pIns;
}

void ScreenRenderManager::InitSub(StaticAllocObj* alloc) {
    m_pAlloc = alloc;
    m_vertex.createCopyVertexBuff(s_vertices, sizeof(s_vertices), 5 * sizeof(float));
    m_index.createCopyIndexBuff(s_indices, 4, GrlPrimitiveType(7), GrlIndexFormat(1));
    m_samplers[0].initSampler(GrlTexClamp(0), GrlTexMagFilterType(1));
    m_samplers[0].updateData();
    m_samplers[2].initSampler(GrlTexClamp(2), GrlTexMagFilterType(0));
    m_samplers[2].updateData();
    m_samplers[3].initSampler(GrlTexClamp(2), GrlTexMagFilterType(1));
    m_samplers[3].updateData();
    m_samplers[1].initSampler(GrlTexClamp(0), GrlTexMagFilterType(1));
    m_samplers[1].setClamp(GrlTexClamp(0), GrlTexClamp(0), GrlTexClamp(0));
    m_samplers[1].updateData();
    void* memory = m_pAlloc->sysAlloc(0x100, 16, nullptr, 0);
    grlib::CGLibVtxAttr attributes[2];
    attributes[0].format = 0x22;
    attributes[0].location = 0;
    attributes[0].offset = 0;
    attributes[0].stream = 0;
    attributes[1].format = 0x16;
    attributes[1].location = 1;
    attributes[1].offset = 0xC;
    attributes[1].stream = 0;
    m_fetch.createMemFetchObj(memory, attributes, 2);
    efAstMsg("m_uAllocSizeUse < m_uAllocSize", "memory empty");
}

void ScreenRenderManager::term() {
#line 114
    MM_ASSERT(getPtr());
    ScreenRenderManager* manager = getPtr();
    manager->m_fetch.release();
    manager->m_vertex.release();
    manager->m_index.release();
    getPtr()->~ScreenRenderManager();
    StaticAllocObj::destroy(getPtr()->m_pAlloc);
    getPtr() = nullptr;
}

bool ScreenRenderManager::isValid() {
    return getPtr() != nullptr;
}

void ScreenRenderManager::RenderScreen(const DrDrawWorkInfoEF* pDrInfo, const mm::Mat44& rect, const mm::Vec3&,
                                       const mm::Col4& color, const grlib::CGLibTextureBuffer* texture, bool blend,
                                       mm::Vec4 param) {
    grlib::CGLibDecShader* shader =
        renderer::RenderManager::getPtr()->getRenderGrObj()->m_shaderManager.getShaderByIndex(renderer::EffShdType(7));
    grlib::CGLibEtcUniformBlock block;
    unsigned int ofs = shader->getDeclarationOfs("BLEND_TYPE");
    if (blend) {
        shader->setDeclarationIdx(ofs, 2);
    } else {
        shader->setDeclarationIdx(ofs, 1);
    }
    grlib::CGLibCtlVertex::setVertex(m_vertex);
    grlib::CGLibCtlShader::setShader(*shader, m_fetch);
    float x = rect.m[0][0];
    float y = rect.m[0][1];
    float width = rect.m[0][2];
    float height = rect.m[0][3];
    block.setMoveMem(sizeof(ScreenParam));
    ScreenParam* buffer = static_cast<ScreenParam*>(block.getBuff());
    buffer->scaleX = width / pDrInfo->m_screenWidth;
    buffer->scaleY = height / pDrInfo->m_screenHeight;
    buffer->offsetX = -(1.0f - buffer->scaleX) + x / pDrInfo->m_screenWidth * 2.0f;
    buffer->offsetY = (1.0f - buffer->scaleY) - y / pDrInfo->m_screenHeight * 2.0f;
    buffer->color.r = color.r;
    buffer->color.g = color.g;
    buffer->color.b = color.b;
    buffer->color.a = color.a;
    buffer->param = param;
    block.updateData(sizeof(ScreenParam));
    block.setUniformBlock(0);
    unsigned int location = shader->getCurrentShader().getTextureLocation("s0");
    if (texture != nullptr) {
        grlib::CGLibCtlTexture::setTexture(*texture, m_samplers[0], location);
    }
    m_index.drawIndex();
}

void ScreenRenderManager::RenderCapScreen(const DrDrawWorkInfoEF*, const grlib::CGLibTextureBuffer* texture0,
                                          const grlib::CGLibTextureBuffer* texture1) {
    grlib::CGLibDecShader* shader =
        renderer::RenderManager::getPtr()->getRenderGrObj()->m_shaderManager.getShaderByIndex(renderer::EffShdType(7));
    grlib::CGLibEtcUniformBlock block;
    shader->setDeclarationIdx(shader->getDeclarationOfs("BLEND_TYPE"), 1);
    shader->setDeclarationIdx(shader->getDeclarationOfs("TEX_TYPE"), 2);
    grlib::CGLibCtlVertex::setVertex(m_vertex);
    grlib::CGLibCtlShader::setShader(*shader, m_fetch);
    float* buffer = static_cast<float*>(block.getBuff());
    buffer[0] = 1.0f;
    buffer[1] = 1.0f;
    buffer[2] = 0.0f;
    buffer[3] = 0.0f;
    buffer[4] = 1.0f;
    buffer[5] = 1.0f;
    buffer[6] = 1.0f;
    buffer[7] = 1.0f;
    buffer[8] = 0.0f;
    buffer[9] = 0.0f;
    buffer[10] = 1.0f;
    buffer[11] = 1.0f;
    block.updateData(sizeof(ScreenParam));
    block.setUniformBlock(shader->getCurrentShader().getUniformBlockOfs("CommonBuff"));
    grlib::CGLibCtlTexture::setTexture(*texture0, m_samplers[0], shader->getCurrentShader().getTextureLocation("s0"));
    grlib::CGLibCtlTexture::setTexture(*texture1, m_samplers[0], shader->getCurrentShader().getTextureLocation("s1"));
    m_index.drawIndex();
    shader->setDeclarationIdx(shader->getDeclarationOfs("TEX_TYPE"), 1);
}

void ScreenRenderManager::RenderScreenDebug(const DrDrawWorkInfoEF* pDrInfo, const mm::Mat44& rect, const mm::Vec3&,
                                            const mm::Col4&, material::MaterialTexture* texture, bool blend,
                                            mm::Vec4 param) {
    grlib::CGLibDecShader* shader =
        renderer::RenderManager::getPtr()->getRenderGrObj()->m_shaderManager.getShaderByIndex(renderer::EffShdType(7));
    unsigned int ofs = shader->getDeclarationOfs("BLEND_TYPE");
    if (blend) {
        shader->setDeclarationIdx(ofs, 2);
    } else {
        shader->setDeclarationIdx(ofs, 1);
    }
    grlib::CGLibCtlVertex::setVertex(m_vertex);
    grlib::CGLibCtlShader::setShader(*shader, m_fetch);
    float x = rect.m[0][0];
    float y = rect.m[0][1];
    float width = rect.m[0][2];
    float height = rect.m[0][3];
    grlib::CGLibEtcUniformBlock block;
    block.setMoveMem(sizeof(ScreenParam));
    ScreenParam* buffer = static_cast<ScreenParam*>(block.getBuff());
    buffer->scaleX = width / pDrInfo->m_screenWidth;
    buffer->scaleY = height / pDrInfo->m_screenHeight;
    buffer->offsetX = x / pDrInfo->m_screenWidth * 2.0f;
    buffer->offsetY = -y / pDrInfo->m_screenHeight * 2.0f;
    buffer->color.b = 1.0f;
    buffer->color.a = 1.0f;
    buffer->color.r = 1.0f;
    buffer->color.g = 1.0f;
    buffer->param = param;
    block.updateData(sizeof(ScreenParam));
    block.setUniformBlock(0);
    unsigned int location = shader->getCurrentShader().getTextureLocation("s0");
    if (texture != nullptr) {
        grlib::CGLibCtlTexture::setTexture(texture->m_texture, m_samplers[0], location);
    }
    m_index.drawIndex();
}

void ScreenRenderManager::RenderSeparate(const DrDrawWorkInfoEF* pDrInfo) {
    grlib::CGLibCtlShader::setMemoryBarrierBit(4);
    grlib::CGLibDecShader* shader =
        renderer::RenderManager::getPtr()->getRenderGrObj()->m_shaderManager.getShaderByIndex(renderer::EffShdType(15));
    grlib::CGLibColorCtl::setMrtBlend(7, GrlLogicType(3));
    grlib::CGLibColorCtl::setMrtBlendControl(grlib::GrlMrtType(0), GrlBlendFunc(2), GrlBlendFunc(5), GrlBlendCombine(1));
    grlib::CGLibColorCtl::setMrtBlendControl(grlib::GrlMrtType(1), GrlBlendFunc(5), GrlBlendFunc(2), GrlBlendCombine(1));
    grlib::CGLibColorCtl::setMrtBlendControl(grlib::GrlMrtType(2), GrlBlendFunc(5), GrlBlendFunc(2), GrlBlendCombine(1));
    unsigned int outType;
    if (pDrInfo->m_pDepthBloom != nullptr) {
        if (pDrInfo->m_pTarget2 != nullptr) {
            pDrInfo->m_pTarget->setRenderTarget(*pDrInfo->m_pTarget1, *pDrInfo->m_pTarget2);
            outType = 1;
        } else {
            pDrInfo->m_pTarget->setRenderTarget(*pDrInfo->m_pTarget1);
            outType = 2;
        }
    } else if (pDrInfo->m_pTarget2 != nullptr) {
        pDrInfo->m_pTarget->setRenderTarget(*pDrInfo->m_pTarget2);
        outType = 3;
    } else {
        pDrInfo->m_pTarget->setRenderTarget();
        outType = 4;
    }
    shader->setDeclarationIdx(shader->getDeclarationOfs("OUTTYPE"), outType);
    grlib::CGLibCtlShader::setShader(*shader, m_fetch);
    float width = pDrInfo->m_pDepthColor->m_width;
    float height = pDrInfo->m_pDepthColor->m_height;
    grlib::CGLibEtcUniformBlock block;
    float* buffer = static_cast<float*>(block.getBuff());
    buffer[0] = width;
    buffer[1] = height;
    buffer[4] = 0.0f;
    buffer[5] = 0.0f;
    buffer[6] = 0.0f;
    buffer[7] = 0.0f;
    buffer[2] = 1.0f / width;
    buffer[3] = 1.0f / height;
    block.updateData(0x20);
    block.setUniformBlock(shader->getCurrentShader().getUniformBlockOfs("U_POST"));
    unsigned int depColLocation = shader->getCurrentShader().getTextureLocation("depCol");
    unsigned int depBlmLocation = shader->getCurrentShader().getTextureLocation("depBlm");
    unsigned int dwnDepLocation = shader->getCurrentShader().getTextureLocation("dwnDep");
    unsigned int orgDepLocation = shader->getCurrentShader().getTextureLocation("orgDep");
    grlib::CGLibCtlTexture::setTexture(*pDrInfo->m_pDownDepth->m_pTexture, m_samplers[2], dwnDepLocation);
    grlib::CGLibCtlTexture::setTexture(*pDrInfo->m_pOrgDepth->m_pTexture, m_samplers[2], orgDepLocation);
    grlib::CGLibCtlTexture::setTexture(*pDrInfo->m_pDepthColor->m_pTexture, m_samplers[3], depColLocation);
    if (pDrInfo->m_pDepthBloom != nullptr) {
        grlib::CGLibCtlTexture::setTexture(*pDrInfo->m_pDepthBloom->m_pTexture, m_samplers[3], depBlmLocation);
    }
    grlib::CGLibCtlVertex::setVertex(m_vertex);
    m_index.drawIndex();
    grlib::CGLibColorCtl::setBlendOffControl(GrlLogicType(3));
}

}}  // namespace ptlib::screen

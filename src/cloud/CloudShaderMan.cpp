#include "grlib/CGLibDecShader.h"
#include "ml/DevFileParamTh.h"
#include "ml/EventFileTh.h"
#include "classes/grlib/CGLibShdListBase.h"
#include "classes/grlib/CGLibShdListData.h"
#include "classes/cloud/CloudDataMan.h"
#include "cloud/CloudShaderMan.h"
#include "cloud/CloudTextureMan.h"
#include "cloud/CloudVertexMan.h"
#include "classes/ml/DrMdlBase.h"
#include "classes/ml/DrMdoMat.h"
#include "classes/ml/DrMdoCtl.h"
#include "classes/ml/DrMdlObj.h"
#include "classes/ml/DrMdoCtlNom.h"
#include "classes/ml/DrMdoCtlPos.h"
#include "classes/ml/DrMdoCtlSeamAll.h"
#include "classes/ml/DrMdoGrpObj.h"
#include "classes/ml/DrMan.h"
#include "ml/DrMdoSmlShadowMan.h"
#include "classes/ml/DrMemHandleAllocator.h"
#include "classes/ml/IDrDrawCallback.h"
#include "ml/MdoWrkMatRes.h"
#include "cloud/CloudShaderMan.h"
#include "cloud/CloudTextureMan.h"
#include "cloud/CloudVertexMan.h"
#include "grlib/CGLibVtxVertex.h"
#include "grlib/CGLibVtxIndex.h"
#include "classes/cloud/CloudDataMan.h"
#include "classes/cloud/CloudMan.h"
#include "classes/ml/DevFileTh.h"
#include "ml/DevFileParamTh.h"
#include "ml/EventFileTh.h"
#include "grlib/CGLibTextureBuffer.h"

namespace cloud {

CloudDataMan::CloudDataMan() {
    for (int i = 0; i < 5; i++) {
        m_pData[i] = nullptr;
        m_size[i] = 0;
        m_hFile[i] = nullptr;
    }
    ml::DevFileParamTh param;
    param.m_hMem = CloudMan::sys()->m_hData;
    param.m_listener = this;
    param.m_align = 0x1000;
    param.pad_6d = false;
    param.m_path = "/monolib/shader/cloud/shd_cloud.wishp";
    m_hFile[0] = ml::DevFileTh::readFile(param);
    param.m_align = 0x1000;
    param.m_path = "/monolib/shader/cloud/volume.witex";
    m_hFile[1] = ml::DevFileTh::readFile(param);
    param.m_align = 0x1000;
    param.m_path = "/monolib/shader/cloud/volume2.witex";
    m_hFile[2] = ml::DevFileTh::readFile(param);
    param.m_align = 0x1000;
    param.m_path = "/monolib/shader/cloud/pnoise.witex";
    m_hFile[3] = ml::DevFileTh::readFile(param);
    param.m_align = 0x1000;
    param.m_path = "/monolib/shader/cloud/tg_smoke_01_n.witex";
    m_hFile[4] = ml::DevFileTh::readFile(param);
    param.m_align = 0x1000;
}

CloudDataMan::~CloudDataMan() {
    for (int i = 0; i < 5; i++) {
        if (m_hFile[i] != nullptr) {
            ml::DevFileTh::cancel(m_hFile[i], false);
        }
        if (m_pData[i] != nullptr) {
            mtl::MemManager::deallocate(m_pData[i], 0, false);
            m_pData[i] = nullptr;
        }
    }
}

bool CloudDataMan::isReadOk() const {
    for (int i = 0; i < 5; i++) {
        if (m_pData[i] == nullptr) {
            return false;
        }
    }
    return true;
}

bool CloudDataMan::OnFileEvent(ml::EventFileTh* event) {
    if (event->m_kind == 2) {
        for (int i = 0; i < 5; i++) {
            if (m_hFile[i] == event->m_handle) {
                m_pData[i] = event->moveFileData();
                m_size[i] = event->m_result;
                m_hFile[i] = nullptr;
            }
        }
    }
    return true;
}

CloudShaderMan::CloudShaderMan() {
    m_pShdWork = nullptr;
    m_isEnable = true;
}

CloudShaderMan::~CloudShaderMan() { releaseShader(); }

void CloudShaderMan::releaseShader() {
    m_shdList.release();
    if (m_pShdWork != nullptr) {
        mtl::MemManager::deallocate(m_pShdWork, 0, false);
        m_pShdWork = nullptr;
    }
}

void CloudShaderMan::update() {}

void CloudShaderMan::createShader() {
    releaseShader();
    m_shdList.createPacShader(CloudMan::sys()->m_pDataMan->m_pData[0], 1002, true);
    unsigned int size = m_shdList.m_num * sizeof(unsigned int);
    m_pShdWork = static_cast<unsigned int*>(
        mtl::MemManager::allocate(CloudMan::sys()->m_hWork, size, 0x10, false, "no name", 0));
    {
        grlib::CGLibVtxAttr attr[4];
        attr[0].format = 0x16;
        attr[0].location = 0;
        attr[0].offset = 0;
        attr[0].stream = 0;
        m_vtxFetch[0].createFetchObj(attr, 1);
        attr[0].format = 0x22;
        attr[0].location = 0;
        attr[0].offset = 0;
        attr[0].stream = 0;
        attr[1].format = 0x16;
        attr[1].location = 1;
        attr[1].offset = 0xC;
        attr[1].stream = 0;
        m_vtxFetch[1].createFetchObj(attr, 2);
        attr[0].format = 0x22;
        attr[0].location = 0;
        attr[0].offset = 0;
        attr[0].stream = 0;
        m_vtxFetch[2].createFetchObj(attr, 1);
        attr[0].format = 0x2E;
        attr[0].location = 0;
        attr[0].offset = 0;
        attr[0].stream = 0;
        m_vtxFetch[3].createFetchObj(attr, 1);
    }
    m_samplers[1].initSampler(GrlTexClamp(2), GrlTexMagFilterType(0));
    m_samplers[1].setClamp(GrlTexClamp(0), GrlTexClamp(0), GrlTexClamp(0));
    m_samplers[0].initSampler(GrlTexClamp(2), GrlTexMagFilterType(1));
    m_samplers[0].setClamp(GrlTexClamp(0), GrlTexClamp(0), GrlTexClamp(0));
    m_samplers[3].initSampler(GrlTexClamp(2), GrlTexMagFilterType(0));
    m_samplers[3].setClamp(GrlTexClamp(2), GrlTexClamp(2), GrlTexClamp(2));
    m_samplers[2].initSampler(GrlTexClamp(2), GrlTexMagFilterType(1));
    m_samplers[2].setClamp(GrlTexClamp(2), GrlTexClamp(2), GrlTexClamp(2));
    m_samplers[4].initSampler(GrlTexClamp(2), GrlTexMagFilterType(1));
    m_samplers[4].setClamp(GrlTexClamp(0), GrlTexClamp(0), GrlTexClamp(0));
    m_samplers[4].setFilter(GrlTexMagFilterType(1), GrlTexMinFilterType(5), GrlTexTexAnisoRatio(0));
    m_samplers[5].initSampler(GrlTexClamp(6), GrlTexMagFilterType(1));
    m_samplers[5].setDepthCompare(GrlTexCompare(3));
    m_samplers[5].setBorderType(GrlTexBorderType(2));
    m_samplers[6].initSampler(GrlTexClamp(6), GrlTexMagFilterType(1));
    m_samplers[6].setBorderColor(mm::Col4(1.0f, 1.0f, 1.0f, 1.0f));
    m_samplers[7].initSampler(GrlTexClamp(6), GrlTexMagFilterType(0));
    m_samplers[7].setBorderColor(mm::Col4(0.0f, 0.0f, 0.0f, 0.0f));
    for (int i = 0; i < 8; i++) {
        m_samplers[i].updateData();
    }
}

void CloudShaderMan::setTexture(unsigned int location, const grlib::CGLibTextureBuffer& texture,
                                CloudSamplerType type) {
    grlib::CGLibCtlTexture::setTexture(texture, m_samplers[type], location);
}

grlib::CGLibDecShader* CloudShaderMan::setShader(CloudShaderType type, unsigned int declIdx0, unsigned int declIdx1,
                                                 unsigned int declIdx2) {
    return (this->*s_CallSelect[type])(type, declIdx0, declIdx1, declIdx2);
}
using namespace grlib;

CGLibDecShader* CloudShaderMan::selectRenderPlane(CloudShaderType type, unsigned int a, unsigned int b, unsigned int c) {
    CGLibDecShader* shader = &m_shdList.m_pList[type];
    unsigned int ofs0 = shader->getDeclarationOfs("CLD_LV_NUM");
    unsigned int ofs1 = shader->getDeclarationOfs("HOLE_MODE");
    unsigned int ofs2 = shader->getDeclarationOfs("BLND_MODE");
    shader->setDeclarationIdx(ofs0, a);
    shader->setDeclarationIdx(ofs1, b);
    shader->setDeclarationIdx(ofs2, c);
    CGLibCtlShader::setShader(*shader, m_vtxFetch[s_reShdFtxTbl[type]]);
    return shader;
}

CGLibDecShader* CloudShaderMan::selectDebug(CloudShaderType type, unsigned int a, unsigned int, unsigned int) {
    CGLibDecShader* shader = &m_shdList.m_pList[type];
    unsigned int ofs0 = shader->getDeclarationOfs("DEBUG_MODE");
    shader->setDeclarationIdx(ofs0, a);
    CGLibCtlShader::setShader(*shader, m_vtxFetch[s_reShdFtxTbl[type]]);
    return shader;
}

CGLibDecShader* CloudShaderMan::selectColor(CloudShaderType type, unsigned int, unsigned int, unsigned int) {
    CGLibDecShader* shader = &m_shdList.m_pList[type];
    CGLibCtlShader::setShader(*shader, m_vtxFetch[s_reShdFtxTbl[type]]);
    return shader;
}

CGLibDecShader* CloudShaderMan::selectParticles(CloudShaderType type, unsigned int, unsigned int, unsigned int) {
    CGLibDecShader* shader = &m_shdList.m_pList[type];
    CGLibCtlShader::setComputeShader(*shader);
    return shader;
}

CGLibDecShader* CloudShaderMan::selectShadow(CloudShaderType type, unsigned int a, unsigned int, unsigned int) {
    CGLibDecShader* shader = &m_shdList.m_pList[type];
    unsigned int ofs0 = shader->getDeclarationOfs("CLD_SHADOW_ON");
    shader->setDeclarationIdx(ofs0, a);
    CGLibCtlShader::setShader(*shader, m_vtxFetch[s_reShdFtxTbl[type]]);
    return shader;
}

CGLibDecShader* CloudShaderMan::selectRenderSky(CloudShaderType type, unsigned int a, unsigned int, unsigned int) {
    CGLibDecShader* shader = &m_shdList.m_pList[type];
    unsigned int ofs0 = shader->getDeclarationOfs("CLD_LV_NUM");
    shader->setDeclarationIdx(ofs0, a);
    CGLibCtlShader::setShader(*shader, m_vtxFetch[s_reShdFtxTbl[type]]);
    return shader;
}

CGLibDecShader* CloudShaderMan::selectMdlSphere(CloudShaderType type, unsigned int, unsigned int, unsigned int) {
    CGLibDecShader* shader = &m_shdList.m_pList[type];
    CGLibCtlShader::setShader(*shader, m_vtxFetch[s_reShdFtxTbl[type]]);
    return shader;
}

CGLibDecShader* CloudShaderMan::selectDetailMap(CloudShaderType type, unsigned int, unsigned int, unsigned int) {
    CGLibDecShader* shader = &m_shdList.m_pList[type];
    CGLibCtlShader::setShader(*shader, m_vtxFetch[s_reShdFtxTbl[type]]);
    return shader;
}

CGLibDecShader* CloudShaderMan::selectGlbFog(CloudShaderType type, unsigned int, unsigned int, unsigned int) {
    CGLibDecShader* shader = &m_shdList.m_pList[type];
    CGLibCtlShader::setShader(*shader, m_vtxFetch[s_reShdFtxTbl[type]]);
    return shader;
}

CGLibDecShader* CloudShaderMan::selectOutput(CloudShaderType type, unsigned int outMode, unsigned int earlyZOn,
                                            unsigned int) {
    CGLibDecShader* shader = &m_shdList.m_pList[type];
    shader->setDeclarationIdx(shader->getDeclarationOfs("OUT_MODE"), outMode);
    shader->setDeclarationIdx(shader->getDeclarationOfs("EARLY_Z_ON"), earlyZOn);
    CGLibCtlShader::setShader(*shader, m_vtxFetch[outMode == 3 ? 1 : 2]);
    return shader;
}

CGLibDecShader* CloudShaderMan::selectDownDepth(CloudShaderType type, unsigned int sampleType, unsigned int,
                                               unsigned int) {
    CGLibDecShader* shader = &m_shdList.m_pList[type];
    unsigned int ofs0 = shader->getDeclarationOfs("DONW_SAMPLE_TYPE");
    shader->setDeclarationIdx(ofs0, sampleType);
    CGLibCtlShader::setShader(*shader, m_vtxFetch[s_reShdFtxTbl[type]]);
    return shader;
}

CGLibDecShader* CloudShaderMan::selectBlur(CloudShaderType type, unsigned int, unsigned int, unsigned int) {
    CGLibDecShader* shader = &m_shdList.m_pList[type];
    CGLibCtlShader::setShader(*shader, m_vtxFetch[s_reShdFtxTbl[type]]);
    return shader;
}

CGLibDecShader* CloudShaderMan::selectCounter(CloudShaderType type, unsigned int mdlCalc, unsigned int,
                                             unsigned int) {
    CGLibDecShader* shader = &m_shdList.m_pList[type];
    unsigned int ofs0 = shader->getDeclarationOfs("CLD_MDL_CALC");
    shader->setDeclarationIdx(ofs0, mdlCalc);
    int fetch;
    switch (mdlCalc) {
    case 1:
        fetch = 1;
        break;
    case 2:
        fetch = 2;
        break;
    case 3:
        fetch = 1;
        break;
    case 4:
        fetch = 1;
        break;
    default:
        fetch = 2;
        break;
    }
    CGLibCtlShader::setShader(*shader, m_vtxFetch[fetch]);
    return shader;
}

CGLibDecShader* CloudShaderMan::selectPlnDepth(CloudShaderType type, unsigned int, unsigned int, unsigned int) {
    CGLibDecShader* shader = &m_shdList.m_pList[type];
    CGLibCtlShader::setShader(*shader, m_vtxFetch[s_reShdFtxTbl[type]]);
    return shader;
}

CGLibDecShader* CloudShaderMan::selectUpScale(CloudShaderType type, unsigned int, unsigned int, unsigned int) {
    CGLibDecShader* shader = &m_shdList.m_pList[type];
    CGLibCtlShader::setShader(*shader, m_vtxFetch[s_reShdFtxTbl[type]]);
    return shader;
}

CloudTextureMan::CloudTextureMan() {
    for (int i = 0; i < 4; i++) {
        m_pTextures[i] = nullptr;
    }
}

CloudTextureMan::~CloudTextureMan() { releaseTexture(); }

void CloudTextureMan::releaseTexture() {
    for (int i = 0; i < 4; i++) {
        if (m_pTextures[i] != nullptr) {
            delete m_pTextures[i];
            m_pTextures[i] = nullptr;
        }
    }
}

CloudVertexMan::CloudVertexMan() : m_pVertex(), m_pIndex() { createVertexList(); }

CloudVertexMan::~CloudVertexMan() { releaseVertexList(); }

void CloudVertexMan::releaseVertexList() {
    for (int i = 0; i < 9; i++) {
        if (m_pVertex[i] != nullptr) {
            delete m_pVertex[i];
            m_pVertex[i] = nullptr;
        }
        if (m_pIndex[i] != nullptr) {
            delete m_pIndex[i];
            m_pIndex[i] = nullptr;
        }
    }
}

void CloudVertexMan::bindVertexList(CloudVertexType type) { grlib::CGLibCtlVertex::setVertex(*m_pVertex[type]); }

void CloudVertexMan::renderIndexList(CloudVertexType type) { m_pIndex[type]->drawIndex(); }

CloudShaderMan::SelectFunc CloudShaderMan::s_CallSelect[16] = {
    &CloudShaderMan::selectRenderPlane, &CloudShaderMan::selectDebug,     &CloudShaderMan::selectColor,
    &CloudShaderMan::selectParticles,   &CloudShaderMan::selectColor,     &CloudShaderMan::selectShadow,
    &CloudShaderMan::selectRenderSky,   &CloudShaderMan::selectMdlSphere, &CloudShaderMan::selectDetailMap,
    &CloudShaderMan::selectGlbFog,      &CloudShaderMan::selectOutput,    &CloudShaderMan::selectDownDepth,
    &CloudShaderMan::selectBlur,        &CloudShaderMan::selectCounter,   &CloudShaderMan::selectPlnDepth,
    &CloudShaderMan::selectUpScale,
};

unsigned int CloudShaderMan::s_reShdFtxTbl[16] = {2, 1, 1, 0, 0, 1, 1, 2, 1, 2, 2, 1, 1, 1, 2, 1};

}  // namespace cloud

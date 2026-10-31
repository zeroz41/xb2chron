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
#include "grlib/CGLibTexture.h"
#include "cloud/CloudMdlParts.h"
#include "cloud/CloudMdlListMan.h"
#include "cloud/CloudMdlDataObj.h"
#include "cloud/CloudObjMan.h"
#include "classes/cloud/CloudObjMdl.h"
#include "mtl/MemManager.h"
#include <math.h>
#include <new>

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

void CloudTextureMan::createTexture() {
    releaseTexture();
    for (int i = 0; i < 4; i++) {
        m_pTextures[i] = new (CloudMan::sys()->m_hWork, nullptr, 0, 4, false) grlib::CGLibTextureBuffer();
    }
    CloudDataMan* data = CloudMan::sys()->m_pDataMan;
    for (int i = 0; i < 4; i++) {
        grlib::CGLibTexture::createTextureImagePtrs(*m_pTextures[i], data->m_pData[i + 1], data->m_size[i + 1], false,
                                                    nullptr, true);
    }
}

CloudVertexMan::CloudVertexMan() : m_pVertex(), m_pIndex() { createVertexList(); }

void CloudVertexMan::createVertexList() {
    releaseVertexList();
    // lbl_71009D4230
    static const float s_planeVtx[] = {
        -1.f, 0.f, -1.f,
        1.f, 0.f, -1.f,
        1.f, 0.f, 1.f,
        -1.f, 0.f, 1.f,
    };
    // lbl_71009D4260
    static const unsigned char s_planeIdx[] = {
        3, 2, 1, 0,
    };
    // lbl_71009D4264
    static const float s_thinBoxVtx[] = {
        -1.f, 0.f, -1.f,
        1.f, 0.f, -1.f,
        1.f, 0.f, 1.f,
        -1.f, 0.f, 1.f,
        -1.f, 0.02f, -1.f,
        1.f, 0.02f, -1.f,
        1.f, 0.02f, 1.f,
        -1.f, 0.02f, 1.f,
    };
    // lbl_71009D42C4
    static const unsigned char s_thinBoxIdx[] = {
        3, 2, 1, 0, 0, 1, 5, 4, 2, 3, 7, 6, 4, 7, 3, 0, 1, 2, 6, 5,
    };
    // lbl_71009D42D8
    static const float s_boxVtx[] = {
        -1.f, -0.025f, -1.f,
        1.f, -0.025f, -1.f,
        1.f, -0.025f, 1.f,
        -1.f, -0.025f, 1.f,
        -1.f, 0.025f, -1.f,
        1.f, 0.025f, -1.f,
        1.f, 0.025f, 1.f,
        -1.f, 0.025f, 1.f,
    };
    // lbl_71009D4338
    static const unsigned char s_boxIdx[] = {
        0, 1, 5, 4, 2, 3, 7, 6, 4, 7, 3, 0, 1, 2, 6, 5,
    };
    // lbl_71009D4348
    static const float s_quadVtx[] = {
        -1.f, -1.f, 0.5f, 0.f, 1.f,
        1.f, -1.f, 0.5f, 1.f, 1.f,
        1.f, 1.f, 0.5f, 1.f, 0.f,
        -1.f, 1.f, 0.5f, 0.f, 0.f,
    };
    // lbl_71009D4398
    static const unsigned char s_quadIdx[] = {
        0, 1, 2, 3,
    };
    // lbl_71009D439C
    static const float s_lowerBoxVtx[] = {
        -1.f, -1.f, -1.f,
        1.f, -1.f, -1.f,
        1.f, -1.f, 1.f,
        -1.f, -1.f, 1.f,
        -1.f, 0.f, -1.f,
        1.f, 0.f, -1.f,
        1.f, 0.f, 1.f,
        -1.f, 0.f, 1.f,
    };
    // lbl_71009D43FC
    static const unsigned char s_lowerBoxIdx[] = {
        3, 2, 1, 0, 4, 5, 6, 7, 0, 1, 5, 4, 2, 3, 7, 6, 4, 7, 3, 0, 1, 2, 6, 5,
    };
    // lbl_71009D4414
    static const float s_upperBoxVtx[] = {
        -1.f, 0.f, -1.f,
        1.f, 0.f, -1.f,
        1.f, 0.f, 1.f,
        -1.f, 0.f, 1.f,
        -1.f, 1.f, -1.f,
        1.f, 1.f, -1.f,
        1.f, 1.f, 1.f,
        -1.f, 1.f, 1.f,
    };
    // lbl_71009D4474
    static const unsigned char s_upperBoxIdx[] = {
        4, 5, 6, 7, 0, 1, 5, 4, 2, 3, 7, 6, 4, 7, 3, 0, 1, 2, 6, 5,
    };
    m_pVertex[0] = new (CloudMan::sys()->m_hWork, nullptr, 0, 4, false) grlib::CGLibVtxVertex();
    m_pVertex[0]->createCopyVertexBuff(s_planeVtx, sizeof(s_planeVtx), 12);
    m_pIndex[0] = new (CloudMan::sys()->m_hWork, nullptr, 0, 4, false) grlib::CGLibVtxIndex();
    m_pIndex[0]->createCopyIndexBuff(s_planeIdx, sizeof(s_planeIdx), GrlPrimitiveType(7), GrlIndexFormat(0));
    m_pVertex[1] = new (CloudMan::sys()->m_hWork, nullptr, 0, 4, false) grlib::CGLibVtxVertex();
    m_pVertex[1]->createCopyVertexBuff(s_thinBoxVtx, sizeof(s_thinBoxVtx), 12);
    m_pIndex[1] = new (CloudMan::sys()->m_hWork, nullptr, 0, 4, false) grlib::CGLibVtxIndex();
    m_pIndex[1]->createCopyIndexBuff(s_thinBoxIdx, sizeof(s_thinBoxIdx), GrlPrimitiveType(7), GrlIndexFormat(0));
    m_pVertex[8] = new (CloudMan::sys()->m_hWork, nullptr, 0, 4, false) grlib::CGLibVtxVertex();
    m_pVertex[8]->createCopyVertexBuff(s_boxVtx, sizeof(s_boxVtx), 12);
    m_pIndex[8] = new (CloudMan::sys()->m_hWork, nullptr, 0, 4, false) grlib::CGLibVtxIndex();
    m_pIndex[8]->createCopyIndexBuff(s_boxIdx, sizeof(s_boxIdx), GrlPrimitiveType(7), GrlIndexFormat(0));
    m_pVertex[2] = new (CloudMan::sys()->m_hWork, nullptr, 0, 4, false) grlib::CGLibVtxVertex();
    m_pVertex[2]->createCopyVertexBuff(s_quadVtx, sizeof(s_quadVtx), 20);
    m_pIndex[2] = new (CloudMan::sys()->m_hWork, nullptr, 0, 4, false) grlib::CGLibVtxIndex();
    m_pIndex[2]->createCopyIndexBuff(s_quadIdx, sizeof(s_quadIdx), GrlPrimitiveType(7), GrlIndexFormat(0));
    m_pVertex[3] = new (CloudMan::sys()->m_hWork, nullptr, 0, 4, false) grlib::CGLibVtxVertex();
    m_pVertex[3]->createCopyVertexBuff(s_lowerBoxVtx, sizeof(s_lowerBoxVtx), 12);
    m_pIndex[3] = new (CloudMan::sys()->m_hWork, nullptr, 0, 4, false) grlib::CGLibVtxIndex();
    m_pIndex[3]->createCopyIndexBuff(s_lowerBoxIdx, sizeof(s_lowerBoxIdx), GrlPrimitiveType(7), GrlIndexFormat(0));
    m_pVertex[7] = new (CloudMan::sys()->m_hWork, nullptr, 0, 4, false) grlib::CGLibVtxVertex();
    m_pVertex[7]->createCopyVertexBuff(s_upperBoxVtx, sizeof(s_upperBoxVtx), 12);
    m_pIndex[7] = new (CloudMan::sys()->m_hWork, nullptr, 0, 4, false) grlib::CGLibVtxIndex();
    m_pIndex[7]->createCopyIndexBuff(s_upperBoxIdx, sizeof(s_upperBoxIdx), GrlPrimitiveType(7), GrlIndexFormat(0));
    createSphere();
    createCapsule();
    createHalfSphere();
}

void CloudVertexMan::createSphere() {
    m_pVertex[4] = new (CloudMan::sys()->m_hWork, nullptr, 0, 4, false) grlib::CGLibVtxVertex();
    m_pIndex[4] = new (CloudMan::sys()->m_hWork, nullptr, 0, 4, false) grlib::CGLibVtxIndex();
    // 18 rings of 18 vertices between the poles, the top and bottom pole
    m_pVertex[4]->createVertexBuff((16 * 18 + 2) * 12, 12);
    void* buffer;
    unsigned int size;
    m_pVertex[4]->lock(&buffer, &size);
    float* vtx = static_cast<float*>(buffer);
    vtx[0] = 0.0f;
    vtx[1] = 1.0f;
    vtx[2] = 0.0f;
    int n = 1;
    for (int i = 1; i < 17; i++) {
        float theta = (float)i / 18.0f * 3.1415927f;
        float c = cosf(theta);
        float s = sinf(theta);
        for (int j = 0; j < 18; j++) {
            float phi = (float)j / 18.0f * 6.2831855f;
            float sp = sinf(phi);
            float cp = cosf(phi);
            vtx[n * 3 + 0] = s * sp;
            vtx[n * 3 + 1] = c;
            vtx[n * 3 + 2] = s * cp;
            n++;
        }
    }
    vtx[(16 * 18 + 1) * 3 + 0] = 0.0f;
    vtx[(16 * 18 + 1) * 3 + 1] = -1.0f;
    vtx[(16 * 18 + 1) * 3 + 2] = 0.0f;
    m_pVertex[4]->unlock();
    m_pIndex[4]->createIndexBuff(16 * 18 * 6, GrlPrimitiveType(4), GrlIndexFormat(1));
    m_pIndex[4]->lock(&buffer, &size);
    unsigned short* idx = static_cast<unsigned short*>(buffer);
    n = 0;
    for (int j = 0; j < 18; j++) {
        int next = j + 1 == 18 ? 0 : j + 1;
        idx[n + 0] = 0;
        idx[n + 1] = next + 1;
        idx[n + 2] = j + 1;
        idx[n + 18 * 3 + 0] = 16 * 18 + 1;
        idx[n + 18 * 3 + 1] = 15 * 18 + 1 + j;
        idx[n + 18 * 3 + 2] = 15 * 18 + 1 + next;
        n += 3;
    }
    n += 18 * 3;
    for (int i = 1; i < 16; i++) {
        for (int j = 0; j < 18; j++) {
            int next = j + 1 == 18 ? 0 : j + 1;
            idx[n++] = (i - 1) * 18 + 1 + j;
            idx[n++] = (i - 1) * 18 + 1 + next;
            idx[n++] = i * 18 + 1 + j;
            idx[n++] = i * 18 + 1 + j;
            idx[n++] = (i - 1) * 18 + 1 + next;
            idx[n++] = i * 18 + 1 + next;
        }
    }
    m_pIndex[4]->unlock();
}

void CloudVertexMan::createCapsule() {
    void* buffer;
    unsigned int size;
    grlib::CGLibVtxVertex* vertex = new (CloudMan::sys()->m_hWork, nullptr, 0, 4, false) grlib::CGLibVtxVertex();
    grlib::CGLibVtxIndex* index = new (CloudMan::sys()->m_hWork, nullptr, 0, 4, false) grlib::CGLibVtxIndex();
    // the top pole, 11 rings of 12 vertices (rings 5 and 6 both on the equator, w 1 above and 0 below), the bottom pole
    vertex->createVertexBuff((11 * 12 + 2) * 16, 16);
    vertex->lock(&buffer, &size);
    float* vtx = static_cast<float*>(buffer);
    vtx[0] = 0.0f;
    vtx[1] = 1.0f;
    vtx[2] = 0.0f;
    vtx[3] = 1.0f;
    float* p = &vtx[4];
    for (unsigned int i = 1; i < 12; i++) {
        int ring = i > 5 ? i - 1 : i;
        float theta = (float)ring / 12.0f * 3.1415927f;
        float w = i > 5 ? 0.0f : 1.0f;
        float c = cosf(theta);
        float s = sinf(theta);
        for (unsigned int j = 0; j < 12; j++) {
            float phi = (float)j / 12.0f * 6.2831855f;
            float sp = sinf(phi);
            float cp = cosf(phi);
            p[0] = s * sp;
            p[1] = c;
            p[2] = s * cp;
            p[3] = w;
            p += 4;
        }
    }
    vtx[(11 * 12 + 1) * 4 + 0] = 0.0f;
    vtx[(11 * 12 + 1) * 4 + 1] = -1.0f;
    vtx[(11 * 12 + 1) * 4 + 2] = 0.0f;
    vtx[(11 * 12 + 1) * 4 + 3] = 0.0f;
    vertex->unlock();
    index->createIndexBuff(11 * 12 * 6, GrlPrimitiveType(4), GrlIndexFormat(1));
    index->lock(&buffer, &size);
    unsigned short* idx = static_cast<unsigned short*>(buffer);
    int n = 0;
    for (int j = 0; j < 12; j++) {
        int next = j + 1 == 12 ? 0 : j + 1;
        idx[n + 0] = 0;
        idx[n + 1] = next + 1;
        idx[n + 2] = j + 1;
        idx[n + 12 * 3 + 0] = 11 * 12 + 1;
        idx[n + 12 * 3 + 1] = 10 * 12 + 1 + j;
        idx[n + 12 * 3 + 2] = 10 * 12 + 1 + next;
        n += 3;
    }
    n += 12 * 3;
    for (int i = 1; i < 11; i++) {
        for (int j = 0; j < 12; j++) {
            int next = j + 1 == 12 ? 0 : j + 1;
            idx[n++] = (i - 1) * 12 + 1 + j;
            idx[n++] = (i - 1) * 12 + 1 + next;
            idx[n++] = i * 12 + 1 + j;
            idx[n++] = i * 12 + 1 + j;
            idx[n++] = (i - 1) * 12 + 1 + next;
            idx[n++] = i * 12 + 1 + next;
        }
    }
    index->unlock();
    m_pVertex[6] = vertex;
    m_pIndex[6] = index;
}

void CloudVertexMan::createHalfSphere() {
    m_pVertex[5] = new (CloudMan::sys()->m_hWork, nullptr, 0, 4, false) grlib::CGLibVtxVertex();
    m_pIndex[5] = new (CloudMan::sys()->m_hWork, nullptr, 0, 4, false) grlib::CGLibVtxIndex();
    // the top pole and 8 rings of 16 vertices
    m_pVertex[5]->createVertexBuff((8 * 16 + 1) * 12, 12);
    void* buffer;
    unsigned int size;
    m_pVertex[5]->lock(&buffer, &size);
    float* vtx = static_cast<float*>(buffer);
    vtx[0] = 0.0f;
    vtx[1] = 1.0f;
    vtx[2] = 0.0f;
    int n = 1;
    for (int i = 1; i < 9; i++) {
        float theta = (float)i / 16.0f * 3.1415927f;
        float c = cosf(theta);
        float s = sinf(theta);
        for (int j = 0; j < 16; j++) {
            float phi = (float)j / 16.0f * 6.2831855f;
            float sp = sinf(phi);
            float cp = cosf(phi);
            vtx[n * 3 + 0] = s * sp;
            vtx[n * 3 + 2] = s * cp;
            vtx[n * 3 + 1] = c;
            n++;
        }
    }
    m_pVertex[5]->unlock();
    m_pIndex[5]->createIndexBuff(15 * 16 * 3, GrlPrimitiveType(4), GrlIndexFormat(1));
    m_pIndex[5]->lock(&buffer, &size);
    unsigned short* idx = static_cast<unsigned short*>(buffer);
    n = 0;
    for (int j = 0; j < 16; j++) {
        int next = j + 1 == 16 ? 0 : j + 1;
        idx[n++] = 0;
        idx[n++] = next + 1;
        idx[n++] = j + 1;
    }
    for (int i = 1; i < 8; i++) {
        for (int j = 0; j < 16; j++) {
            int next = j + 1 == 16 ? 0 : j + 1;
            idx[n++] = (i - 1) * 16 + 1 + j;
            idx[n++] = (i - 1) * 16 + 1 + next;
            idx[n++] = i * 16 + 1 + j;
            idx[n++] = i * 16 + 1 + j;
            idx[n++] = (i - 1) * 16 + 1 + next;
            idx[n++] = i * 16 + 1 + next;
        }
    }
    m_pIndex[5]->unlock();
}


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

void CloudMdlParts::createUniform(const mm::Vec3& dir) {
    float speed = m_params0[1] * 0.05f;
    m_scroll.x += speed * (dir.x * m_params1[4]);
    m_scroll.y += speed * (dir.y * m_params1[5]);
    m_scroll.z += speed * (dir.z * m_params1[4]);
    m_detailScroll.x += speed * (dir.x * m_params1[4]) * 10.0f;
    m_detailScroll.y += speed * (dir.y * m_params1[5]) * 10.0f;
    m_detailScroll.z += speed * (dir.z * m_params1[4]) * 10.0f;
    if (m_scrollType == 2) {
        m_scroll.x = fmodf(m_scroll.x, 256.0f);
        m_scroll.y = fmodf(m_scroll.y, 256.0f);
        if (m_scroll.z >= 4352.0f) {
            m_scroll.z -= 4352.0f;
        } else if (m_scroll.z <= -4352.0f) {
            m_scroll.z += 4352.0f;
        }
    } else {
        m_scroll.x = fmodf(m_scroll.x, 1.0f);
        m_scroll.y = fmodf(m_scroll.y, 1.0f);
        m_scroll.z = fmodf(m_scroll.z, 1.0f);
    }
    m_detailScroll.x = fmodf(m_detailScroll.x, 256.0f);
    m_detailScroll.y = fmodf(m_detailScroll.y, 256.0f);
    if (m_detailScroll.z >= 4352.0f) {
        m_detailScroll.z -= 4352.0f;
    } else if (m_detailScroll.z <= -4352.0f) {
        m_detailScroll.z += 4352.0f;
    }
    m_uniform.createMdlPolyUniform(this, m_scroll, m_detailScroll, &m_pData->getObjData(m_index));
    m_uniform.updateData();
}

void CloudMdlParts::bindVertex() {
    CloudMdlDataObj* data = m_pData;
    const CloudMdlDataObj::MeshInfo* mesh = data->m_pMesh + (data->m_pObjData + m_index)->m_meshIdx;
    grlib::CGLibCtlVertex::setVertex((data->m_pVtxBuf + mesh->m_vtxIdx)->m_vertex);
}

void CloudMdlParts::render() {
    CloudMdlDataObj* data = m_pData;
    const CloudMdlDataObj::MeshInfo* mesh = data->m_pMesh + (data->m_pObjData + m_index)->m_meshIdx;
    grlib::CGLibVtxIndex& index = (data->m_pVtxBuf + mesh->m_vtxIdx)->m_index;
    index.drawIndex(mesh->m_count, mesh->m_start * 2);
}

int CloudMdlParts::isDisp() const {
    if (!(m_pData->m_flags & 1)) {
        return 0;
    }
    unsigned int bit = m_dispBit;
    if (bit != 0 && (CloudMan::sys()->m_pReserved[bit >> 5] & (1 << (bit & 0x1F)))) {
        return 0;
    }
    return 1;
}

CloudMdlListMan::CloudMdlListMan() : m_pTop(nullptr), m_pTail(nullptr) {}

CloudMdlListMan::~CloudMdlListMan() { releaseAll(); }

void CloudMdlListMan::releaseAll() {
    for (CloudMdlParts* parts = m_pTop; parts != nullptr;) {
        CloudMdlParts* next = parts->m_pNext;
        delete parts;
        parts = next;
    }
    m_pTop = nullptr;
    m_pTail = nullptr;
}

void CloudMdlListMan::update() {}

CloudMdlDataObj::CloudMdlDataObj() : m_pPrev(nullptr), m_pNext(nullptr), m_pList(nullptr) {
    m_pFile = nullptr;
    m_flags = 0;
    m_ppParts = nullptr;
    m_vtxNum = 0;
    m_partsNum = 0;
    m_pAlloc = nullptr;
    m_pVtxBuf = nullptr;
}

CloudMdlDataObj::~CloudMdlDataObj() { releaseData(); }

void CloudMdlDataObj::releaseData() {
    for (int i = 0; i < m_vtxNum; i++) {
        m_pVtxBuf[i].m_vertex.release();
        m_pVtxBuf[i].m_index.release();
    }
    CloudMdlListMan& list = CloudMan::sys()->m_pObjMan->m_pMdl->m_partsList;
    for (int i = 0; i < m_partsNum; i++) {
        CloudMdlParts*& parts = m_ppParts[i];
        CloudMdlParts* next = parts->m_pNext;
        CloudMdlParts* prev = parts->m_pPrev;
        if (prev == nullptr) {
            if (next == nullptr) {
                list.m_pTop = nullptr;
                list.m_pTail = nullptr;
            } else {
                list.m_pTop = next;
                next->m_pPrev = nullptr;
            }
        } else if (next == nullptr) {
            list.m_pTail = prev;
            prev->m_pNext = nullptr;
        } else {
            prev->m_pNext = next;
            parts->m_pNext->m_pPrev = parts->m_pPrev;
        }
        if (parts != nullptr) {
            delete parts;
            parts = nullptr;
        }
    }
    m_memPool.release();
    if (m_pAlloc != nullptr) {
        mtl::MemManager::deallocate(m_pAlloc, 0, false);
        m_pAlloc = nullptr;
    }
    m_pFile = nullptr;
    m_ppParts = nullptr;
    m_vtxNum = 0;
    m_partsNum = 0;
    m_pVtxBuf = nullptr;
}

void CloudMdlDataObj::create(const void* data) {
    m_pFile = data;
    const Header* header = static_cast<const Header*>(data);
    const CMLObjData* objData =
        reinterpret_cast<const CMLObjData*>(static_cast<const char*>(data) + header->m_objDataOfs);
    m_partsNum = header->m_objDataNum;
    const VtxHeader* vtxHeader =
        reinterpret_cast<const VtxHeader*>(static_cast<const char*>(data) + header->m_vtxOfs);
    unsigned int infoOfs = vtxHeader->m_infoOfs;
    m_vtxNum = vtxHeader->m_num;
    unsigned int vtxSize = m_vtxNum * 0x50;
    unsigned int partsSize = m_partsNum * 8;
    void* buffer = mtl::MemManager::allocate(CloudMan::sys()->m_hWork, partsSize + vtxSize, 0x10, false, "no name", 0);
    m_pAlloc = buffer;
    m_ppParts = static_cast<CloudMdlParts**>(buffer);
    m_pVtxBuf = reinterpret_cast<VtxBuf*>(static_cast<char*>(buffer) + partsSize);
    m_pObjData = objData;
    m_pMesh = reinterpret_cast<const MeshInfo*>(static_cast<const char*>(m_pFile) + header->m_meshOfs);
    m_memPool.setupBuffer(const_cast<char*>(static_cast<const char*>(m_pFile)) + vtxHeader->m_bufOfs,
                          vtxHeader->m_bufSize);
    const VtxInfo* info = reinterpret_cast<const VtxInfo*>(static_cast<const char*>(data) + infoOfs);
    for (int i = 0; i < m_vtxNum; i++, info++) {
        new (&m_pVtxBuf[i].m_vertex) grlib::CGLibVtxVertex();
        new (&m_pVtxBuf[i].m_index) grlib::CGLibVtxIndex();
        m_pVtxBuf[i].m_vertex.createMemVertexBuff(&m_memPool, info->m_vtxOfs, info->m_vtxSize, 12);
        m_pVtxBuf[i].m_index.createMemIndexBuff(&m_memPool, info->m_idxOfs, info->m_idxSize >> 1, GrlPrimitiveType(4),
                                                GrlIndexFormat(1));
    }
    CloudMdlListMan& list = CloudMan::sys()->m_pObjMan->m_pMdl->m_partsList;
    for (int i = 0; i < m_partsNum; i++) {
        m_ppParts[i] = list.createParts();
        CloudMdlParts* parts = m_ppParts[i];
        parts->m_pData = this;
        parts->m_index = i;
        const CMLObjData* obj = &m_pObjData[parts->m_index];
        parts->m_pos = mm::Vec3(obj->m_pos[0], obj->m_pos[1], obj->m_pos[2]);
        parts->m_param = obj->m_param;
        for (int j = 0; j < 7; j++) {
            parts->m_params0[j] = obj->m_params0[j];
        }
        for (int j = 0; j < 7; j++) {
            parts->m_params1[j] = obj->m_params1[j];
        }
        parts->m_type = obj->m_type;
        parts->m_dispBit = obj->m_dispBit;
        parts->m_scrollType = (obj->m_flags & 1) + 1;
    }
}

void CloudMdlDataObj::release() { m_flags |= 0x40 << CloudMan::s_nDblStIdx; }

bool CloudMdlDataObj::update() {
    if (m_flags & 0x100) {
        return false;
    }
    if (m_flags & (0x40 << CloudMan::s_nDblDfIdx)) {
        m_flags &= ~1u;
        m_flags |= 0x100;
    } else {
        if (m_flags & 2) {
            m_flags |= 1;
        } else {
            m_flags &= ~1u;
        }
        m_flags &= ~2u;
    }
    return true;
}

void CloudMdlDataObj::setCallDisp(bool disp) {
    if (disp) {
        m_flags |= 2;
    } else {
        m_flags &= ~3u;
    }
}

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

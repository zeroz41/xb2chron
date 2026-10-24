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

namespace cloud {
using namespace grlib;

CGLibDecShader* CloudShaderMan::selectRenderPlane(CloudShaderType type, unsigned int a, unsigned int b, unsigned int c) {
    CGLibDecShader* shader = &m_pShaders[type];
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
    CGLibDecShader* shader = &m_pShaders[type];
    unsigned int ofs0 = shader->getDeclarationOfs("DEBUG_MODE");
    shader->setDeclarationIdx(ofs0, a);
    CGLibCtlShader::setShader(*shader, m_vtxFetch[s_reShdFtxTbl[type]]);
    return shader;
}

CGLibDecShader* CloudShaderMan::selectColor(CloudShaderType type, unsigned int, unsigned int, unsigned int) {
    CGLibDecShader* shader = &m_pShaders[type];
    CGLibCtlShader::setShader(*shader, m_vtxFetch[s_reShdFtxTbl[type]]);
    return shader;
}

CGLibDecShader* CloudShaderMan::selectShadow(CloudShaderType type, unsigned int a, unsigned int, unsigned int) {
    CGLibDecShader* shader = &m_pShaders[type];
    unsigned int ofs0 = shader->getDeclarationOfs("CLD_SHADOW_ON");
    shader->setDeclarationIdx(ofs0, a);
    CGLibCtlShader::setShader(*shader, m_vtxFetch[s_reShdFtxTbl[type]]);
    return shader;
}

CGLibDecShader* CloudShaderMan::selectRenderSky(CloudShaderType type, unsigned int a, unsigned int, unsigned int) {
    CGLibDecShader* shader = &m_pShaders[type];
    unsigned int ofs0 = shader->getDeclarationOfs("CLD_LV_NUM");
    shader->setDeclarationIdx(ofs0, a);
    CGLibCtlShader::setShader(*shader, m_vtxFetch[s_reShdFtxTbl[type]]);
    return shader;
}

CGLibDecShader* CloudShaderMan::selectMdlSphere(CloudShaderType type, unsigned int, unsigned int, unsigned int) {
    CGLibDecShader* shader = &m_pShaders[type];
    CGLibCtlShader::setShader(*shader, m_vtxFetch[s_reShdFtxTbl[type]]);
    return shader;
}

CGLibDecShader* CloudShaderMan::selectDetailMap(CloudShaderType type, unsigned int, unsigned int, unsigned int) {
    CGLibDecShader* shader = &m_pShaders[type];
    CGLibCtlShader::setShader(*shader, m_vtxFetch[s_reShdFtxTbl[type]]);
    return shader;
}

CGLibDecShader* CloudShaderMan::selectGlbFog(CloudShaderType type, unsigned int, unsigned int, unsigned int) {
    CGLibDecShader* shader = &m_pShaders[type];
    CGLibCtlShader::setShader(*shader, m_vtxFetch[s_reShdFtxTbl[type]]);
    return shader;
}

CGLibDecShader* CloudShaderMan::selectOutput(CloudShaderType type, unsigned int outMode, unsigned int earlyZOn,
                                            unsigned int) {
    CGLibDecShader* shader = &m_pShaders[type];
    shader->setDeclarationIdx(shader->getDeclarationOfs("OUT_MODE"), outMode);
    shader->setDeclarationIdx(shader->getDeclarationOfs("EARLY_Z_ON"), earlyZOn);
    CGLibCtlShader::setShader(*shader, m_vtxFetch[outMode == 3 ? 1 : 2]);
    return shader;
}

CGLibDecShader* CloudShaderMan::selectBlur(CloudShaderType type, unsigned int, unsigned int, unsigned int) {
    CGLibDecShader* shader = &m_pShaders[type];
    CGLibCtlShader::setShader(*shader, m_vtxFetch[s_reShdFtxTbl[type]]);
    return shader;
}

CGLibDecShader* CloudShaderMan::selectPlnDepth(CloudShaderType type, unsigned int, unsigned int, unsigned int) {
    CGLibDecShader* shader = &m_pShaders[type];
    CGLibCtlShader::setShader(*shader, m_vtxFetch[s_reShdFtxTbl[type]]);
    return shader;
}

CGLibDecShader* CloudShaderMan::selectUpScale(CloudShaderType type, unsigned int, unsigned int, unsigned int) {
    CGLibDecShader* shader = &m_pShaders[type];
    CGLibCtlShader::setShader(*shader, m_vtxFetch[s_reShdFtxTbl[type]]);
    return shader;
}

}  // namespace cloud

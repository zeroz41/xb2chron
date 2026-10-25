#include "classes/ml/DrResMdoInstPartsAnm.h"
#include "classes/ml/DrResMdoInstPartsGlbID.h"
#include "classes/ml/DrResMdoSeamColi.h"
#include "classes/ml/DrResMdoSortMpf.h"
#include "classes/ml/DrResMdoSortPos.h"
#include "classes/ml/DrResMdoSortSeamAll.h"
#include "classes/ml/DrResMdoSortNom.h"
#include "classes/ml/DrResMdoSortNomLastApha.h"
#include "classes/ml/DrResMdoSortNomFastApha.h"
#include "classes/ml/DrResMdoSortNomCldBackApha.h"
#include "classes/ml/DrResMdoSortGrp.h"
#include "classes/ml/DrResMdoSortSeamEnvMap.h"
#include "classes/ml/DrResMdoSortCloud.h"
#include "classes/ml/DrShdLgtClustered.h"
#include "classes/navi/NvmshAcObjBaseGbl.h"
#include "ml/DrResEtcParams.h"
#include "ml/DrResMdoMat.h"
#include "ml/DrResQueryObj.h"
#include "ml/DrPixlOccQuery.h"
#include "ml/DrResOccUniformObj.h"
#include "mtl/MemManager.h"
#include "ml/DrResFetch.h"
#include "ml/DrResMdoLight.h"
#include "ml/DrResMdoPosInstAnm.h"
#include "ml/DrResMdoUniformBlock.h"
#include "ml/DrResEtcPamObj.h"
#include "ml/DrResMdoLodObj.h"
#include "ml/DrResMdoMeshObj.h"
#include "ml/DrResMdoMorpObj.h"
#include "classes/ml/DrMan.h"
#include "classes/ml/DrResMdoInstPartsObj.h"
#include "ml/DrResShdPrePass.h"
#include "ml/DrResShdShw.h"
#include "ml/DrResShdStreamOut.h"
#include "ml/DrResShdObjMot.h"
#include "ml/DrResShdMpf.h"
#include "ml/DrShdDataObj.h"

namespace ml {

DrResMdoInstPartsAnm::~DrResMdoInstPartsAnm() {}

DrResMdoInstPartsGlbID::~DrResMdoInstPartsGlbID() {}

DrResMdoSeamColi::~DrResMdoSeamColi() {}

void DrResMdoLodObj::release(DrResMdoLodObj*& obj) {
    if (obj != nullptr) {
        obj = nullptr;
    }
}

void DrResEtcPamObj::release(DrResEtcPamObj*& obj) {
    if (obj != nullptr) {
        obj = nullptr;
    }
}

void DrResMdoMeshObj::release(DrResMdoMeshObj*& obj) {
    if (obj != nullptr) {
        obj = nullptr;
    }
}

void DrResMdoMorpObj::release(DrResMdoMorpObj*& obj) {
    if (obj != nullptr) {
        obj = nullptr;
    }
}

DrResMdoSortNom::DrResMdoSortNom(DrMdoCtlNom* owner) : DrMdoZSortObj(owner) {}

void DrResMdoSortNom::SetupRender() {
    static_cast<DrMdoCtlNom*>(m_owner)->callNomSetupRender();
}

void DrResMdoSortNom::ZPrepassRender() {
    static_cast<DrMdoCtlNom*>(m_owner)->callZSortNomZpreePassRender();
}

void DrResMdoSortNom::ThicknessRenderFirst() {
    static_cast<DrMdoCtlNom*>(m_owner)->callZSortThicknessRenderFirst();
}

void DrResMdoSortNom::ThicknessRenderSecond() {
    static_cast<DrMdoCtlNom*>(m_owner)->callZSortThicknessRenderSecond();
}

void DrResMdoSortNom::render() {
    static_cast<DrMdoCtlNom*>(m_owner)->callZSortNomRender();
}

void DrResMdoSortNom::GBuffRender() {
    static_cast<DrMdoCtlNom*>(m_owner)->callZSortGBuffRender();
}

void DrResMdoSortNom::lightPrePassRender() {
    static_cast<DrMdoCtlNom*>(m_owner)->callZSortLightPrePassRender();
}

void DrResMdoSortNom::alphaRender() {
    static_cast<DrMdoCtlNom*>(m_owner)->callZSortNomAlphaRender();
}

void DrResMdoSortNom::spAlphaRender() {
    static_cast<DrMdoCtlNom*>(m_owner)->callZSortNomSpAlphaRender();
}

void DrResMdoSortNom::refractionRender() {
    static_cast<DrMdoCtlNom*>(m_owner)->callZSortNomRefractionRender();
}

DrResMdoSortNomLastApha::DrResMdoSortNomLastApha(DrMdoCtlNom* owner) : DrMdoZSortObj(owner) {}

void DrResMdoSortNomLastApha::alphaRender() {
    static_cast<DrMdoCtlNom*>(m_owner)->callLastAlphaNomRender();
}

DrResMdoSortNomFastApha::DrResMdoSortNomFastApha(DrMdoCtlNom* owner) : DrMdoZSortObj(owner) {}

void DrResMdoSortNomFastApha::alphaRender() {
    static_cast<DrMdoCtlNom*>(m_owner)->callFastAlphaNomRender();
}

DrResMdoSortNomCldBackApha::DrResMdoSortNomCldBackApha(DrMdoCtlNom* owner) : DrMdoZSortObj(owner) {}

void DrResMdoSortNomCldBackApha::alphaRender() {
    static_cast<DrMdoCtlNom*>(m_owner)->callCldBackAlphaNomRender();
}

DrResMdoSortPos::DrResMdoSortPos(DrMdoCtlPos* owner) : DrMdoZSortObj(owner) {}

DrResMdoSortPos::~DrResMdoSortPos() {}

void DrResMdoSortPos::ZPrepassRender() {
    static_cast<DrMdoCtlPos*>(m_owner)->callZpreePassRenderPosAll();
}

void DrResMdoSortPos::ThicknessRenderFirst() {
    static_cast<DrMdoCtlPos*>(m_owner)->callThicknessRenderFirstPosAll();
}

void DrResMdoSortPos::ThicknessRenderSecond() {
    static_cast<DrMdoCtlPos*>(m_owner)->callThicknessRenderSecondPosAll();
}

void DrResMdoSortPos::render() {
    static_cast<DrMdoCtlPos*>(m_owner)->callRenderPosAll();
}

void DrResMdoSortPos::GBuffRender() {
    static_cast<DrMdoCtlPos*>(m_owner)->callGBuffRenderPosAll();
}

void DrResMdoSortPos::alphaRender() {
    static_cast<DrMdoCtlPos*>(m_owner)->callAlphaRenderPosAll();
}

void DrResMdoSortPos::spAlphaRender() {
    static_cast<DrMdoCtlPos*>(m_owner)->callSpAlphaRenderPosAll();
}

void DrResMdoSortPos::lightPrePassRender() {
    static_cast<DrMdoCtlPos*>(m_owner)->callLightPrePassRenderPosAll();
}

void DrResMdoSortPos::refractionRender() {
    static_cast<DrMdoCtlPos*>(m_owner)->callRefractionRenderPosAll();
}

DrResMdoSortMpf::DrResMdoSortMpf(DrMdoCtlMpf* owner) : DrMdoZSortObj(owner) {}

DrResMdoSortMpf::~DrResMdoSortMpf() {}

void DrResMdoSortMpf::ZPrepassRender() {
    static_cast<DrMdoCtlMpf*>(m_owner)->callZPrepassRender();
}

void DrResMdoSortMpf::render() {
    static_cast<DrMdoCtlMpf*>(m_owner)->callRenderMpf();
}

DrResMdoSortGrp::DrResMdoSortGrp(DrMdoGrpObj* owner) : DrMdoZSortObj(owner) {}

void DrResMdoSortGrp::SetupRender() {
    static_cast<DrMdoGrpObj*>(m_owner)->callNomSetupRender();
}

void DrResMdoSortGrp::ZPrepassRender() {
    static_cast<DrMdoGrpObj*>(m_owner)->callZSortNomZpreePassRender();
}

void DrResMdoSortGrp::ThicknessRenderFirst() {
    static_cast<DrMdoGrpObj*>(m_owner)->callZSortThicknessRenderFirst();
}

void DrResMdoSortGrp::ThicknessRenderSecond() {
    static_cast<DrMdoGrpObj*>(m_owner)->callZSortThicknessRenderSecond();
}

void DrResMdoSortGrp::render() {
    static_cast<DrMdoGrpObj*>(m_owner)->callZSortNomRender();
}

void DrResMdoSortGrp::GBuffRender() {
    static_cast<DrMdoGrpObj*>(m_owner)->callZSortGBuffRender();
}

void DrResMdoSortGrp::lightPrePassRender() {
    static_cast<DrMdoGrpObj*>(m_owner)->callZSortLightPrePassRender();
}

void DrResMdoSortGrp::alphaRender() {
    static_cast<DrMdoGrpObj*>(m_owner)->callZSortNomAlphaRender();
}

void DrResMdoSortGrp::spAlphaRender() {
    static_cast<DrMdoGrpObj*>(m_owner)->callZSortNomSpAlphaRender();
}

void DrResMdoSortGrp::refractionRender() {
    static_cast<DrMdoGrpObj*>(m_owner)->callZSortNomRefractionRender();
}

DrResMdoSortSeamAll::DrResMdoSortSeamAll(void* owner) : DrMdoZSortObj(owner) {}

DrResMdoSortSeamAll::~DrResMdoSortSeamAll() {}

void DrResMdoSortSeamAll::ZPrepassRender() {
    static_cast<DrMdoCtlSeamAll*>(m_owner)->callZPrePassSeamAll();
}

void DrResMdoSortSeamAll::ThicknessRenderFirst() {
    static_cast<DrMdoCtlSeamAll*>(m_owner)->callThicknessFirstSeamAll();
}

void DrResMdoSortSeamAll::ThicknessRenderSecond() {
    static_cast<DrMdoCtlSeamAll*>(m_owner)->callThicknessSecondSeamAll();
}

void DrResMdoSortSeamAll::render() {
    static_cast<DrMdoCtlSeamAll*>(m_owner)->callRenderSeamAll();
}

void DrResMdoSortSeamAll::GBuffRender() {
    static_cast<DrMdoCtlSeamAll*>(m_owner)->callGBuffRenderSeamAll();
}

void DrResMdoSortSeamAll::lightPrePassRender() {
    static_cast<DrMdoCtlSeamAll*>(m_owner)->callLightPrePassRenderSeamAll();
}

void DrResMdoSortSeamAll::alphaRender() {
    static_cast<DrMdoCtlSeamAll*>(m_owner)->callAlphaRenderSeamAll();
}

void DrResMdoSortSeamAll::spAlphaRender() {
    static_cast<DrMdoCtlSeamAll*>(m_owner)->callSpAlphaRenderSeamAll();
}

void DrResMdoSortSeamAll::refractionRender() {
    static_cast<DrMdoCtlSeamAll*>(m_owner)->callRefractionRenderSeamAll();
}

DrResMdoSortSeamEnvMap::DrResMdoSortSeamEnvMap(void* owner) : DrMdoZSortObj(owner) {}

DrResMdoSortSeamEnvMap::~DrResMdoSortSeamEnvMap() {}

void DrResMdoSortSeamEnvMap::render() {
    static_cast<DrMdoCtlSeamAll*>(m_owner)->callRenderSeamEnvMap();
}

void DrResMdoSortSeamEnvMap::GBuffRender() {
    static_cast<DrMdoCtlSeamAll*>(m_owner)->callGBuffRenderSeamEnvMap();
}

void DrResMdoSortSeamEnvMap::lightPrePassRender() {
    static_cast<DrMdoCtlSeamAll*>(m_owner)->callLightPrePassRenderSeamEnvMap();
}

void DrResMdoSortSeamEnvMap::alphaRender() {
    static_cast<DrMdoCtlSeamAll*>(m_owner)->callAlphaRenderSeamEnvMap();
}

void DrResMdoSortSeamEnvMap::spAlphaRender() {
    static_cast<DrMdoCtlSeamAll*>(m_owner)->callSpAlphaRenderSeamEnvMap();
}

void DrResMdoSortSeamEnvMap::refractionRender() {
    static_cast<DrMdoCtlSeamAll*>(m_owner)->callRefractionRenderSeamEnvMap();
}

DrResMdoSortCloud::DrResMdoSortCloud(void* owner) : DrMdoZSortObj(owner) {}

DrResMdoSortCloud::~DrResMdoSortCloud() {}

float DrResEtcParams::getParams() const {
    return m_params;
}

void DrResMdoLight::lgtCall_col_r(float* value, DrResEtcParams* params) {
    value[0] = params->getParams();
}

void DrResMdoLight::lgtCall_col_g(float* value, DrResEtcParams* params) {
    value[1] = params->getParams();
}

void DrResMdoLight::lgtCall_col_b(float* value, DrResEtcParams* params) {
    value[2] = params->getParams();
}

void DrResMdoLight::lgtCall_col_inv(float* value, DrResEtcParams* params) {
    value[3] = params->getParams();
}

DrResMdoLight::LgtValFunc DrResMdoLight::s_pCallLgtVal[4] = {
    &DrResMdoLight::lgtCall_col_r,
    &DrResMdoLight::lgtCall_col_g,
    &DrResMdoLight::lgtCall_col_b,
    &DrResMdoLight::lgtCall_col_inv,
};

void DrResMdoPosInstAnm::anmInsPosParm_TranX(mm::Vec3* pos, float value) {
    pos[0].x = value;
}

void DrResMdoPosInstAnm::anmInsPosParm_TranY(mm::Vec3* pos, float value) {
    pos[0].y = value;
}

void DrResMdoPosInstAnm::anmInsPosParm_TranZ(mm::Vec3* pos, float value) {
    pos[0].z = value;
}

void DrResMdoPosInstAnm::anmInsPosParm_RotX(mm::Vec3* pos, float value) {
    pos[1].x = value;
}

void DrResMdoPosInstAnm::anmInsPosParm_RotY(mm::Vec3* pos, float value) {
    pos[1].y = value;
}

void DrResMdoPosInstAnm::anmInsPosParm_RotZ(mm::Vec3* pos, float value) {
    pos[1].z = value;
}

void DrResMdoPosInstAnm::anmInsPosParm_SclX(mm::Vec3* pos, float value) {
    pos[2].x = value;
}

void DrResMdoPosInstAnm::anmInsPosParm_SclY(mm::Vec3* pos, float value) {
    pos[2].y = value;
}

void DrResMdoPosInstAnm::anmInsPosParm_SclZ(mm::Vec3* pos, float value) {
    pos[2].z = value;
}

DrResMdoPosInstAnm::AnmInsPosFunc DrResMdoPosInstAnm::s_pCallAnmInsPos[9] = {
    &DrResMdoPosInstAnm::anmInsPosParm_TranX,
    &DrResMdoPosInstAnm::anmInsPosParm_TranY,
    &DrResMdoPosInstAnm::anmInsPosParm_TranZ,
    &DrResMdoPosInstAnm::anmInsPosParm_RotX,
    &DrResMdoPosInstAnm::anmInsPosParm_RotY,
    &DrResMdoPosInstAnm::anmInsPosParm_RotZ,
    &DrResMdoPosInstAnm::anmInsPosParm_SclX,
    &DrResMdoPosInstAnm::anmInsPosParm_SclY,
    &DrResMdoPosInstAnm::anmInsPosParm_SclZ,
};

int DrResMdoUniformBlock::getStaticUniformBlockSize() {
    return 0x290;
}

int DrResMdoUniformBlock::getMdlUniformBlockSize() {
    return 0xF0;
}

int DrResMdoUniformBlock::getAVACharUniformBlockSize() {
    return 0xE0;
}

int DrResMdoUniformBlock::getToonUniformBlockSize() {
    return 0x70;
}

int DrResMdoUniformBlock::getToon2UniformBlockSize() {
    return 0x40;
}

int DrResMdoUniformBlock::getLightUniformBlockSize() {
    return 0x130;
}

int DrResMdoUniformBlock::getVolTexCalcUniformBlockSize() {
    return 0xA0;
}

int DrResMdoUniformBlock::getRimBloomCalcUniformBlockSize() {
    return 0x20;
}

int DrResMdoUniformBlock::getMpfMaterialUniformBlockSize() {
    return 0x30;
}

void DrResFetch::vert_set_VEC3(int offset, unsigned int location, grlib::CGLibVtxAttr& attr) {
    attr.format = 34;
    attr.location = location;
    attr.offset = offset;
    attr.stream = 0;
}

void DrResFetch::vert_set_BYTE(int offset, unsigned int location, grlib::CGLibVtxAttr& attr) {
    attr.format = 39;
    attr.location = location;
    attr.offset = offset;
    attr.stream = 0;
}

void DrResFetch::vert_set_USHORT2(int offset, unsigned int location, grlib::CGLibVtxAttr& attr) {
    attr.format = 20;
    attr.location = location;
    attr.offset = offset;
    attr.stream = 0;
}

void DrResFetch::vert_set_VEC2(int offset, unsigned int location, grlib::CGLibVtxAttr& attr) {
    attr.format = 22;
    attr.location = location;
    attr.offset = offset;
    attr.stream = 0;
}

void DrResFetch::vert_set_U32(int offset, unsigned int location, grlib::CGLibVtxAttr& attr) {
    attr.format = 37;
    attr.location = location;
    attr.offset = offset;
    attr.stream = 0;
}

void DrResFetch::vert_set_SHORT4(int offset, unsigned int location, grlib::CGLibVtxAttr& attr) {
    attr.format = 43;
    attr.location = location;
    attr.offset = offset;
    attr.stream = 0;
}

void DrResFetch::vert_set_GmPos4(int offset, unsigned int location, grlib::CGLibVtxAttr& attr) {
    attr.format = 34;
    attr.location = location;
    attr.offset = offset;
    attr.stream = 1;
}

void DrResFetch::vert_set_GmScl2(int offset, unsigned int location, grlib::CGLibVtxAttr& attr) {
    attr.format = 22;
    attr.location = location;
    attr.offset = offset;
    attr.stream = 1;
}

void DrResFetch::vert_set_GmCol4(int offset, unsigned int location, grlib::CGLibVtxAttr& attr) {
    attr.format = 37;
    attr.location = location;
    attr.offset = offset;
    attr.stream = 1;
}

void DrResFetch::vert_set_GmCal1(int offset, unsigned int location, grlib::CGLibVtxAttr& attr) {
    attr.format = 46;
    attr.location = location;
    attr.offset = offset;
    attr.stream = 1;
}

void DrResFetch::vert_set_GmCal2(int offset, unsigned int location, grlib::CGLibVtxAttr& attr) {
    attr.format = 46;
    attr.location = location;
    attr.offset = offset;
    attr.stream = 1;
}

void DrResFetch::vert_set_GmCal3(int offset, unsigned int location, grlib::CGLibVtxAttr& attr) {
    attr.format = 46;
    attr.location = location;
    attr.offset = offset;
    attr.stream = 1;
}

void DrResFetch::vert_set_GmInt(int offset, unsigned int location, grlib::CGLibVtxAttr& attr) {
    attr.format = 11;
    attr.location = location;
    attr.offset = offset;
    attr.stream = 1;
}

void DrResFetch::vert_set_S32(int offset, unsigned int location, grlib::CGLibVtxAttr& attr) {
    attr.format = 38;
    attr.location = location;
    attr.offset = offset;
    attr.stream = 0;
}

void DrResFetch::vert_set_GmFloat(int offset, unsigned int location, grlib::CGLibVtxAttr& attr) {
    attr.format = 10;
    attr.location = location;
    attr.offset = offset;
    attr.stream = 1;
}

void DrResFetch::vert_set_OutLineNom(int offset, unsigned int location, grlib::CGLibVtxAttr& attr) {
    attr.format = 38;
    attr.location = location;
    attr.offset = offset;
    attr.stream = 1;
}

void DrResFetch::vert_set_OutLineCol(int offset, unsigned int location, grlib::CGLibVtxAttr& attr) {
    attr.format = 37;
    attr.location = location;
    attr.offset = offset;
    attr.stream = 1;
}

void DrResFetch::vert_set_MofPos(int offset, unsigned int location, grlib::CGLibVtxAttr& attr) {
    attr.format = 34;
    attr.location = location;
    attr.offset = offset;
    attr.stream = 2;
}

void DrResFetch::vert_set_MofNom(int offset, unsigned int location, grlib::CGLibVtxAttr& attr) {
    attr.format = 37;
    attr.location = location;
    attr.offset = offset;
    attr.stream = 2;
}

void DrResFetch::vert_set_MofTan(int offset, unsigned int location, grlib::CGLibVtxAttr& attr) {
    attr.format = 46;
    attr.location = location;
    attr.offset = offset;
    attr.stream = 2;
}

void DrResFetch::vert_set_MofNewTan(int offset, unsigned int location, grlib::CGLibVtxAttr& attr) {
    attr.format = 37;
    attr.location = location;
    attr.offset = offset;
    attr.stream = 2;
}

void DrResFetch::vert_set_SHORT2(int offset, unsigned int location, grlib::CGLibVtxAttr& attr) {
    attr.format = 19;
    attr.location = location;
    attr.offset = offset;
    attr.stream = 0;
}

DrResFetch::SetVertFunc DrResFetch::s_callSetVert[52] = {
    &DrResFetch::vert_set_VEC3,
    &DrResFetch::vert_set_VEC3,
    &DrResFetch::vert_set_BYTE,
    &DrResFetch::vert_set_USHORT2,
    &DrResFetch::vert_set_USHORT2,
    &DrResFetch::vert_set_VEC2,
    &DrResFetch::vert_set_VEC2,
    &DrResFetch::vert_set_VEC2,
    &DrResFetch::vert_set_VEC2,
    &DrResFetch::vert_set_VEC2,
    &DrResFetch::vert_set_VEC2,
    &DrResFetch::vert_set_VEC2,
    &DrResFetch::vert_set_VEC2,
    &DrResFetch::vert_set_VEC2,
    &DrResFetch::vert_set_U32,
    &DrResFetch::vert_set_VEC3,
    &DrResFetch::vert_set_SHORT4,
    &DrResFetch::vert_set_U32,
    &DrResFetch::vert_set_VEC3,
    &DrResFetch::vert_set_SHORT4,
    &DrResFetch::vert_set_SHORT4,
    &DrResFetch::vert_set_GmPos4,
    &DrResFetch::vert_set_GmScl2,
    &DrResFetch::vert_set_GmCol4,
    &DrResFetch::vert_set_GmCal1,
    &DrResFetch::vert_set_GmCal2,
    &DrResFetch::vert_set_GmCal3,
    &DrResFetch::vert_set_GmInt,
    &DrResFetch::vert_set_S32,
    &DrResFetch::vert_set_S32,
    &DrResFetch::vert_set_GmFloat,
    &DrResFetch::vert_set_BYTE,
    &DrResFetch::vert_set_S32,
    &DrResFetch::vert_set_S32,
    &DrResFetch::vert_set_OutLineNom,
    &DrResFetch::vert_set_OutLineCol,
    &DrResFetch::vert_set_MofPos,
    &DrResFetch::vert_set_MofNom,
    &DrResFetch::vert_set_MofTan,
    &DrResFetch::vert_set_MofPos,
    &DrResFetch::vert_set_MofNewTan,
    &DrResFetch::vert_set_SHORT2,
    &DrResFetch::vert_set_SHORT2,
    &DrResFetch::vert_set_SHORT2,
    &DrResFetch::vert_set_SHORT2,
    &DrResFetch::vert_set_SHORT2,
    &DrResFetch::vert_set_SHORT2,
    &DrResFetch::vert_set_SHORT2,
    &DrResFetch::vert_set_SHORT2,
    &DrResFetch::vert_set_SHORT2,
    nullptr,
    nullptr,
};

void DrResMdoInstPartsObj::getMatrix(mm::Mat44& m) const {
    if (m_info->flags & 0x20) {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                m.m[i][j] = m_matrix->m[i][j];
            }
        }
    }
}

void DrResMdoInstPartsAnm::setNodeFrame(float frame) {
    m_nodeFrameStock[DrMan::s_nDblStockIdx] = frame;
    m_stockFlags |= 1 << DrMan::s_nDblStockIdx;
}

float DrResMdoInstPartsAnm::getNodeFrame() const {
    if (m_stockFlags & (1 << DrMan::s_nDblStockIdx)) {
        return m_nodeFrameStock[DrMan::s_nDblStockIdx];
    }
    if (m_stockFlags & (1 << DrMan::s_nDblMemIdx)) {
        return m_nodeFrameStock[DrMan::s_nDblMemIdx];
    }
    return m_nodeFrame;
}

void DrResMdoInstPartsAnm::setSwitchID(unsigned char id) {
    if ((m_info->flags & 0x80) && m_switchID != id) {
        m_switchID = id;
        updateSwitch();
    }
}

unsigned char DrResMdoInstPartsAnm::getSwitchIndex(unsigned int idx) const {
    if (idx < m_switchMax) {
        return m_switches[idx].index;
    }
    return 0;
}

void DrResShdStreamOut::setupStreamShader(unsigned int idx) {
    m_data->setupShader(idx);
}

void (DrResShdShw::*DrResShdShw::s_callShwSet[5])() = {
    &DrResShdShw::shwShdset_DefObj, &DrResShdShw::shwShdset_Inst, &DrResShdShw::shwShdset_Mot,
    &DrResShdShw::shwShdset_InstMot, &DrResShdShw::shwShdset_Fw,
};

void (DrResShdStreamOut::*DrResShdStreamOut::s_callStmOuSet[9])() = {
    &DrResShdStreamOut::stmShdset_Weight, &DrResShdStreamOut::stmShdset_Weight,
    &DrResShdStreamOut::stmShdset_Weight, &DrResShdStreamOut::stmShdset_Weight,
    &DrResShdStreamOut::stmShdset_WetVtx, &DrResShdStreamOut::stmShdset_MofSet,
    &DrResShdStreamOut::stmShdset_MofSet, &DrResShdStreamOut::stmShdset_MeshVtxSet,
    &DrResShdStreamOut::stmShdset_MofSet,
};

DrResShdShw::DrResShdShw(DrShdDataObj* data, int type) {
    m_data = data;
    for (int i = 0; i < 7; i++) {
        m_shaderSel[i] = -1;
    }
    m_flags = 1;
    m_type = type;
    m_texTypeOfs = data->getDeclarationOfs("TEX_TYPE");
    m_sptTypeOfs = m_data->getDeclarationOfs("SPT_TYPE");
    (this->*s_callShwSet[m_type])();
    m_flags &= ~1;
}

void DrResShdShw::setupShader(DrResFetch* fetch) {
    m_data->setupShader(fetch);
}

void DrResShdShw::setDecAType(unsigned int idx) {
    m_data->setDeclarationIdx(m_texTypeOfs, idx);
}

void DrResShdShw::setDecBType(unsigned int idx) {
    m_data->setDeclarationIdx(m_sptTypeOfs, idx);
}

void DrResShdStreamOut::setDecNum(unsigned int idx) {
    m_data->setDeclarationIdx(m_wetNumOfs, idx);
}

void DrResShdStreamOut::stmShdset_Weight() {
    m_shaderSel[0] = 1;
    m_shaderSel[1] = 0;
}

void DrResShdStreamOut::stmShdset_MofSet() {
    m_shaderSel[0] = 0;
    m_shaderSel[1] = 0;
}

void DrResShdStreamOut::stmShdset_MeshVtxSet() {
    m_shaderSel[0] = 0;
    m_shaderSel[1] = 1;
}


DrResFetch::DrResFetch() {}

DrResFetch::~DrResFetch() {
    release();
}

void DrResFetch::clearWork() {
    release();
}

void DrResFetch::setDefVertexParam(int type) {
    (this->*s_callDefVertex[type])();
}

DrResShdPrePass::DrResShdPrePass(DrShdDataObj* data, int type) {
    m_data = data;
    for (int i = 0; i < 11; i++) {
        m_shaderSel[i] = -1;
    }
    m_flags = 1;
    m_type = type;
    m_passTypeOfs = data->getDeclarationOfs("DECL_PASS_TYPE");
    (this->*s_callShdSet[m_type])();
    m_flags &= ~1;
}

void DrResShdPrePass::setupShader(unsigned int fetch, unsigned int passType) {
    m_data->setDeclarationIdx(m_passTypeOfs, passType);
    m_data->setupShader(fetch);
}

void DrResShdPrePass::preshdset_Obj() {
    m_shaderSel[5] = 2;
}

void DrResShdPrePass::preshdset_ObjT() {
    m_shaderSel[5] = 2;
    m_shaderSel[8] = 1;
    m_shaderSel[0] = 0;
}

void DrResShdPrePass::preshdset_ObjT_Al() {
    m_shaderSel[5] = 2;
    m_shaderSel[6] = 0;
    m_shaderSel[9] = 4;
    m_shaderSel[8] = 1;
    m_shaderSel[0] = 0;
    m_shaderSel[1] = 1;
}

void DrResShdPrePass::preshdset_Mot() {
    m_shaderSel[6] = 0;
}

void DrResShdPrePass::preshdset_MotT() {
    m_shaderSel[6] = 0;
    m_shaderSel[8] = 1;
    m_shaderSel[0] = 0;
}

void DrResShdPrePass::preshdset_MotT_Al() {
    m_shaderSel[5] = 2;
    m_shaderSel[6] = 0;
    m_shaderSel[9] = 4;
    m_shaderSel[8] = 1;
    m_shaderSel[0] = 0;
    m_shaderSel[1] = 1;
}

void DrResShdPrePass::preshdset_Inst() {
    m_shaderSel[6] = 0;
}

void DrResShdPrePass::preshdset_InstT() {
    m_shaderSel[6] = 0;
    m_shaderSel[8] = 1;
    m_shaderSel[0] = 0;
}

void DrResShdPrePass::preshdset_Obj_Al() {
    m_shaderSel[5] = 2;
    m_shaderSel[6] = 0;
    m_shaderSel[9] = 4;
    m_shaderSel[8] = 1;
    m_shaderSel[1] = 1;
}

void DrResShdPrePass::preshdset_Mot_Al() {
    m_shaderSel[5] = 2;
    m_shaderSel[6] = 0;
    m_shaderSel[9] = 4;
    m_shaderSel[8] = 1;
    m_shaderSel[1] = 1;
}

void DrResShdPrePass::preshdset_Inst_Al() {
    m_shaderSel[6] = 0;
    m_shaderSel[9] = 4;
    m_shaderSel[8] = 1;
    m_shaderSel[1] = 1;
}

void DrResShdPrePass::preshdset_InstT_Al() {
    m_shaderSel[6] = 0;
    m_shaderSel[9] = 4;
    m_shaderSel[8] = 1;
    m_shaderSel[0] = 0;
    m_shaderSel[1] = 1;
}

void DrResShdPrePass::preshdset_Inst_Bill_Al() {
    m_shaderSel[5] = 3;
    m_shaderSel[6] = 0;
    m_shaderSel[9] = 4;
    m_shaderSel[8] = 1;
    m_shaderSel[1] = 1;
}

void DrResShdPrePass::preshdset_InstT_Bill_Al() {
    m_shaderSel[5] = 3;
    m_shaderSel[6] = 0;
    m_shaderSel[9] = 4;
    m_shaderSel[8] = 1;
    m_shaderSel[0] = 0;
    m_shaderSel[1] = 1;
}

void DrResShdPrePass::preshdset_Fw() {
    m_shaderSel[5] = 2;
    m_shaderSel[3] = 3;
    m_shaderSel[10] = 3;
    m_shaderSel[4] = 4;
}

void DrResShdPrePass::preshdset_FwT() {
    m_shaderSel[5] = 2;
    m_shaderSel[8] = 1;
    m_shaderSel[3] = 3;
    m_shaderSel[0] = 0;
    m_shaderSel[10] = 3;
    m_shaderSel[4] = 4;
}

void DrResShdPrePass::preshdset_Fw_Al() {
    m_shaderSel[5] = 2;
    m_shaderSel[6] = 0;
    m_shaderSel[9] = 4;
    m_shaderSel[8] = 1;
    m_shaderSel[3] = 3;
    m_shaderSel[1] = 1;
    m_shaderSel[10] = 3;
    m_shaderSel[4] = 4;
}

void (DrResShdPrePass::*DrResShdPrePass::s_callShdSet[42])() = {
    &DrResShdPrePass::preshdset_Obj,
    &DrResShdPrePass::preshdset_ObjT,
    &DrResShdPrePass::preshdset_ObjT,
    &DrResShdPrePass::preshdset_ObjT_Al,
    &DrResShdPrePass::preshdset_ObjT_Al,
    &DrResShdPrePass::preshdset_Mot,
    &DrResShdPrePass::preshdset_MotT,
    &DrResShdPrePass::preshdset_MotT,
    &DrResShdPrePass::preshdset_MotT_Al,
    &DrResShdPrePass::preshdset_MotT_Al,
    &DrResShdPrePass::preshdset_Inst,
    &DrResShdPrePass::preshdset_InstT,
    &DrResShdPrePass::preshdset_InstT,
    &DrResShdPrePass::preshdset_Obj_Al,
    &DrResShdPrePass::preshdset_ObjT_Al,
    &DrResShdPrePass::preshdset_ObjT_Al,
    &DrResShdPrePass::preshdset_ObjT_Al_Fs,
    &DrResShdPrePass::preshdset_ObjT_Al_Fs,
    &DrResShdPrePass::preshdset_Mot_Al,
    &DrResShdPrePass::preshdset_MotT_Al,
    &DrResShdPrePass::preshdset_MotT_Al,
    &DrResShdPrePass::preshdset_MotT_Al_Fs,
    &DrResShdPrePass::preshdset_MotT_Al_Fs,
    &DrResShdPrePass::preshdset_Inst_Al,
    &DrResShdPrePass::preshdset_InstT_Al,
    &DrResShdPrePass::preshdset_InstT_Al,
    &DrResShdPrePass::preshdset_Inst_Bill_Al,
    &DrResShdPrePass::preshdset_InstT_Bill_Al,
    &DrResShdPrePass::preshdset_InstT_Bill_Al,
    &DrResShdPrePass::preshdset_Inst_Bill_Al,
    &DrResShdPrePass::preshdset_InstT_Bill_Al,
    &DrResShdPrePass::preshdset_InstT_Bill_Al,
    &DrResShdPrePass::preshdset_Fw,
    &DrResShdPrePass::preshdset_FwT,
    &DrResShdPrePass::preshdset_FwT,
    &DrResShdPrePass::preshdset_FwT_Al,
    &DrResShdPrePass::preshdset_FwT_Al,
    &DrResShdPrePass::preshdset_Fw_Al,
    &DrResShdPrePass::preshdset_FwT_Al,
    &DrResShdPrePass::preshdset_FwT_Al,
    &DrResShdPrePass::preshdset_FwT_Al_Fs,
    &DrResShdPrePass::preshdset_FwT_Al_Fs,
};

void DrResFetch::setupTexture2D() {
    grlib::CGLibVtxAttr attrs[2];
    attrs[0].format = 34;
    attrs[0].location = 0;
    attrs[0].offset = 0;
    attrs[0].stream = 0;
    attrs[1].format = 22;
    attrs[1].location = 1;
    attrs[1].offset = 12;
    attrs[1].stream = 0;
    createFetchObj(attrs, 2);
}

void DrResFetch::setupPositionOnly() {
    grlib::CGLibVtxAttr attrs[1];
    attrs[0].format = 34;
    attrs[0].location = 0;
    attrs[0].offset = 0;
    attrs[0].stream = 0;
    createFetchObj(attrs, 1);
}

void DrResFetch::setupSkinWeightCalc() {
    grlib::CGLibVtxAttr attrs[2];
    attrs[0].format = 34;
    attrs[0].location = 0;
    attrs[0].offset = 0;
    attrs[0].stream = 0;
    attrs[1].format = 39;
    attrs[1].location = 1;
    attrs[1].offset = 12;
    attrs[1].stream = 0;
    createFetchObj(attrs, 2);
}

void DrResFetch::setupZBuffObj() {
    grlib::CGLibVtxAttr attrs[1];
    attrs[0].format = 34;
    attrs[0].location = 0;
    attrs[0].offset = 0;
    attrs[0].stream = 0;
    createFetchObj(attrs, 1);
}

void DrResFetch::setupZBuffObjTex() {
    grlib::CGLibVtxAttr attrs[2];
    attrs[0].format = 34;
    attrs[0].location = 0;
    attrs[0].offset = 0;
    attrs[0].stream = 0;
    attrs[1].format = 22;
    attrs[1].location = 1;
    attrs[1].offset = 12;
    attrs[1].stream = 0;
    createFetchObj(attrs, 2);
}

void DrResFetch::setupZBuffMot() {
    grlib::CGLibVtxAttr attrs[2];
    attrs[0].format = 34;
    attrs[0].location = 0;
    attrs[0].offset = 0;
    attrs[0].stream = 0;
    attrs[1].format = 20;
    attrs[1].location = 1;
    attrs[1].offset = 12;
    attrs[1].stream = 0;
    createFetchObj(attrs, 2);
}

void DrResFetch::setupZBuffMotTex() {
    grlib::CGLibVtxAttr attrs[3];
    attrs[0].format = 34;
    attrs[0].location = 0;
    attrs[0].offset = 0;
    attrs[0].stream = 0;
    attrs[1].format = 20;
    attrs[1].location = 1;
    attrs[1].offset = 12;
    attrs[1].stream = 0;
    attrs[2].format = 22;
    attrs[2].location = 2;
    attrs[2].offset = 16;
    attrs[2].stream = 0;
    createFetchObj(attrs, 3);
}

void DrResFetch::setupZBuffInst() {
    grlib::CGLibVtxAttr attrs[4];
    attrs[0].format = 34;
    attrs[0].location = 0;
    attrs[0].offset = 0;
    attrs[0].stream = 0;
    attrs[1].format = 46;
    attrs[1].location = 1;
    attrs[1].offset = 0;
    attrs[1].stream = 1;
    attrs[2].format = 46;
    attrs[2].location = 2;
    attrs[2].offset = 16;
    attrs[2].stream = 1;
    attrs[3].format = 46;
    attrs[3].location = 3;
    attrs[3].offset = 32;
    attrs[3].stream = 1;
    createFetchObj(attrs, 4);
}

void DrResFetch::setupZBuffInstTex() {
    grlib::CGLibVtxAttr attrs[5];
    attrs[0].format = 34;
    attrs[0].location = 0;
    attrs[0].offset = 0;
    attrs[0].stream = 0;
    attrs[1].format = 22;
    attrs[1].location = 1;
    attrs[1].offset = 12;
    attrs[1].stream = 0;
    attrs[2].format = 46;
    attrs[2].location = 2;
    attrs[2].offset = 0;
    attrs[2].stream = 1;
    attrs[3].format = 46;
    attrs[3].location = 3;
    attrs[3].offset = 16;
    attrs[3].stream = 1;
    attrs[4].format = 46;
    attrs[4].location = 4;
    attrs[4].offset = 32;
    attrs[4].stream = 1;
    createFetchObj(attrs, 5);
}

void DrResFetch::setupZBuffObjAL() {
    grlib::CGLibVtxAttr attrs[2];
    attrs[0].format = 34;
    attrs[0].location = 0;
    attrs[0].offset = 0;
    attrs[0].stream = 0;
    attrs[1].format = 10;
    attrs[1].location = 1;
    attrs[1].offset = 0;
    attrs[1].stream = 1;
    createFetchObj(attrs, 2);
}

void DrResFetch::setupZBuffObjTexAL() {
    grlib::CGLibVtxAttr attrs[3];
    attrs[0].format = 34;
    attrs[0].location = 0;
    attrs[0].offset = 0;
    attrs[0].stream = 0;
    attrs[1].format = 22;
    attrs[1].location = 1;
    attrs[1].offset = 12;
    attrs[1].stream = 0;
    attrs[2].format = 10;
    attrs[2].location = 2;
    attrs[2].offset = 0;
    attrs[2].stream = 1;
    createFetchObj(attrs, 3);
}

void DrResFetch::setupZBuffMotAL() {
    grlib::CGLibVtxAttr attrs[3];
    attrs[0].format = 34;
    attrs[0].location = 0;
    attrs[0].offset = 0;
    attrs[0].stream = 0;
    attrs[1].format = 20;
    attrs[1].location = 1;
    attrs[1].offset = 12;
    attrs[1].stream = 0;
    attrs[2].format = 10;
    attrs[2].location = 2;
    attrs[2].offset = 0;
    attrs[2].stream = 1;
    createFetchObj(attrs, 3);
}

void DrResFetch::setupZBuffMotTexAL() {
    grlib::CGLibVtxAttr attrs[4];
    attrs[0].format = 34;
    attrs[0].location = 0;
    attrs[0].offset = 0;
    attrs[0].stream = 0;
    attrs[1].format = 20;
    attrs[1].location = 1;
    attrs[1].offset = 12;
    attrs[1].stream = 0;
    attrs[2].format = 22;
    attrs[2].location = 2;
    attrs[2].offset = 16;
    attrs[2].stream = 0;
    attrs[3].format = 10;
    attrs[3].location = 3;
    attrs[3].offset = 0;
    attrs[3].stream = 1;
    createFetchObj(attrs, 4);
}

void DrResFetch::setupShadowObj() {
    grlib::CGLibVtxAttr attrs[1];
    attrs[0].format = 34;
    attrs[0].location = 0;
    attrs[0].offset = 0;
    attrs[0].stream = 0;
    createFetchObj(attrs, 1);
}

void DrResFetch::setupShadowObjTex() {
    grlib::CGLibVtxAttr attrs[2];
    attrs[0].format = 34;
    attrs[0].location = 0;
    attrs[0].offset = 0;
    attrs[0].stream = 0;
    attrs[1].format = 22;
    attrs[1].location = 1;
    attrs[1].offset = 12;
    attrs[1].stream = 0;
    createFetchObj(attrs, 2);
}

void DrResFetch::setupShadowMot() {
    grlib::CGLibVtxAttr attrs[2];
    attrs[0].format = 34;
    attrs[0].location = 0;
    attrs[0].offset = 0;
    attrs[0].stream = 0;
    attrs[1].format = 20;
    attrs[1].location = 1;
    attrs[1].offset = 12;
    attrs[1].stream = 0;
    createFetchObj(attrs, 2);
}

void DrResFetch::setupShadowMotTex() {
    grlib::CGLibVtxAttr attrs[3];
    attrs[0].format = 34;
    attrs[0].location = 0;
    attrs[0].offset = 0;
    attrs[0].stream = 0;
    attrs[1].format = 20;
    attrs[1].location = 1;
    attrs[1].offset = 12;
    attrs[1].stream = 0;
    attrs[2].format = 22;
    attrs[2].location = 2;
    attrs[2].offset = 16;
    attrs[2].stream = 0;
    createFetchObj(attrs, 3);
}

void DrResFetch::setupShadowMotInst() {
    grlib::CGLibVtxAttr attrs[5];
    attrs[0].format = 34;
    attrs[0].location = 0;
    attrs[0].offset = 0;
    attrs[0].stream = 0;
    attrs[1].format = 20;
    attrs[1].location = 1;
    attrs[1].offset = 12;
    attrs[1].stream = 0;
    attrs[2].format = 46;
    attrs[2].location = 2;
    attrs[2].offset = 0;
    attrs[2].stream = 1;
    attrs[3].format = 46;
    attrs[3].location = 3;
    attrs[3].offset = 16;
    attrs[3].stream = 1;
    attrs[4].format = 46;
    attrs[4].location = 4;
    attrs[4].offset = 32;
    attrs[4].stream = 1;
    createFetchObj(attrs, 5);
}

void DrResFetch::setupShadowMotInstTex() {
    grlib::CGLibVtxAttr attrs[6];
    attrs[0].format = 34;
    attrs[0].location = 0;
    attrs[0].offset = 0;
    attrs[0].stream = 0;
    attrs[1].format = 20;
    attrs[1].location = 1;
    attrs[1].offset = 12;
    attrs[1].stream = 0;
    attrs[2].format = 22;
    attrs[2].location = 2;
    attrs[2].offset = 16;
    attrs[2].stream = 0;
    attrs[3].format = 46;
    attrs[3].location = 3;
    attrs[3].offset = 0;
    attrs[3].stream = 1;
    attrs[4].format = 46;
    attrs[4].location = 4;
    attrs[4].offset = 16;
    attrs[4].stream = 1;
    attrs[5].format = 46;
    attrs[5].location = 5;
    attrs[5].offset = 32;
    attrs[5].stream = 1;
    createFetchObj(attrs, 6);
}

void DrResFetch::setupMpf_Stm_Bill() {
    grlib::CGLibVtxAttr attrs[2];
    attrs[0].format = 34;
    attrs[0].location = 0;
    attrs[0].offset = 0;
    attrs[0].stream = 0;
    attrs[1].format = 22;
    attrs[1].location = 1;
    attrs[1].offset = 0;
    attrs[1].stream = 1;
    createFetchObj(attrs, 2);
}

void DrResFetch::setupMpf_Stm_Bill_Wind() {
    grlib::CGLibVtxAttr attrs[4];
    attrs[0].format = 34;
    attrs[0].location = 0;
    attrs[0].offset = 0;
    attrs[0].stream = 0;
    attrs[1].format = 34;
    attrs[1].location = 1;
    attrs[1].offset = 20;
    attrs[1].stream = 0;
    attrs[2].format = 22;
    attrs[2].location = 2;
    attrs[2].offset = 0;
    attrs[2].stream = 1;
    attrs[3].format = 11;
    attrs[3].location = 3;
    attrs[3].offset = 8;
    attrs[3].stream = 1;
    createFetchObj(attrs, 4);
}

void DrResFetch::setupMpf_Stm_Mdl_Wind() {
    grlib::CGLibVtxAttr attrs[3];
    attrs[0].format = 34;
    attrs[0].location = 0;
    attrs[0].offset = 0;
    attrs[0].stream = 0;
    attrs[1].format = 34;
    attrs[1].location = 1;
    attrs[1].offset = 36;
    attrs[1].stream = 0;
    attrs[2].format = 11;
    attrs[2].location = 2;
    attrs[2].offset = 0;
    attrs[2].stream = 1;
    createFetchObj(attrs, 3);
}

void DrResFetch::setupMpf_Stm_Mdl_Wind_NoNom() {
    grlib::CGLibVtxAttr attrs[3];
    attrs[0].format = 34;
    attrs[0].location = 0;
    attrs[0].offset = 0;
    attrs[0].stream = 0;
    attrs[1].format = 34;
    attrs[1].location = 1;
    attrs[1].offset = 24;
    attrs[1].stream = 0;
    attrs[2].format = 11;
    attrs[2].location = 2;
    attrs[2].offset = 0;
    attrs[2].stream = 1;
    createFetchObj(attrs, 3);
}

void DrResFetch::setupMpf_Stm_Mdl_NormalMap_Wind() {
    grlib::CGLibVtxAttr attrs[3];
    attrs[0].format = 34;
    attrs[0].location = 0;
    attrs[0].offset = 0;
    attrs[0].stream = 0;
    attrs[1].format = 34;
    attrs[1].location = 1;
    attrs[1].offset = 44;
    attrs[1].stream = 0;
    attrs[2].format = 11;
    attrs[2].location = 2;
    attrs[2].offset = 0;
    attrs[2].stream = 1;
    createFetchObj(attrs, 3);
}

void DrResFetch::setupMpf_Stm_Mdl_NormalMap_Wind_VNom() {
    grlib::CGLibVtxAttr attrs[5];
    attrs[0].format = 34;
    attrs[0].location = 0;
    attrs[0].offset = 0;
    attrs[0].stream = 0;
    attrs[1].format = 34;
    attrs[1].location = 1;
    attrs[1].offset = 20;
    attrs[1].stream = 0;
    attrs[2].format = 43;
    attrs[2].location = 2;
    attrs[2].offset = 32;
    attrs[2].stream = 0;
    attrs[3].format = 34;
    attrs[3].location = 3;
    attrs[3].offset = 44;
    attrs[3].stream = 0;
    attrs[4].format = 11;
    attrs[4].location = 4;
    attrs[4].offset = 0;
    attrs[4].stream = 1;
    createFetchObj(attrs, 5);
}

void DrResFetch::setupMpf_Pre_Bill() {
    grlib::CGLibVtxAttr attrs[2];
    attrs[0].format = 34;
    attrs[0].location = 0;
    attrs[0].offset = 0;
    attrs[0].stream = 1;
    attrs[1].format = 34;
    attrs[1].location = 1;
    attrs[1].offset = 0;
    attrs[1].stream = 2;
    createFetchObj(attrs, 2);
}

void DrResFetch::setupMpf_Pre_Bill_Nuki() {
    grlib::CGLibVtxAttr attrs[3];
    attrs[0].format = 22;
    attrs[0].location = 0;
    attrs[0].offset = 12;
    attrs[0].stream = 0;
    attrs[1].format = 34;
    attrs[1].location = 1;
    attrs[1].offset = 0;
    attrs[1].stream = 1;
    attrs[2].format = 34;
    attrs[2].location = 2;
    attrs[2].offset = 0;
    attrs[2].stream = 2;
    createFetchObj(attrs, 3);
}

void DrResFetch::setupMpf_Pre_Bill_Nuki_Layer() {
    grlib::CGLibVtxAttr attrs[4];
    attrs[0].format = 22;
    attrs[0].location = 0;
    attrs[0].offset = 12;
    attrs[0].stream = 0;
    attrs[1].format = 34;
    attrs[1].location = 1;
    attrs[1].offset = 0;
    attrs[1].stream = 1;
    attrs[2].format = 34;
    attrs[2].location = 2;
    attrs[2].offset = 0;
    attrs[2].stream = 2;
    attrs[3].format = 17;
    attrs[3].location = 3;
    attrs[3].offset = 16;
    attrs[3].stream = 2;
    createFetchObj(attrs, 4);
}

void DrResFetch::setupMpf_Pre_Mdl() {
    grlib::CGLibVtxAttr attrs[4];
    attrs[0].format = 34;
    attrs[0].location = 0;
    attrs[0].offset = 0;
    attrs[0].stream = 1;
    attrs[1].format = 46;
    attrs[1].location = 1;
    attrs[1].offset = 0;
    attrs[1].stream = 2;
    attrs[2].format = 46;
    attrs[2].location = 2;
    attrs[2].offset = 16;
    attrs[2].stream = 2;
    attrs[3].format = 46;
    attrs[3].location = 3;
    attrs[3].offset = 32;
    attrs[3].stream = 2;
    createFetchObj(attrs, 4);
}

void DrResFetch::setupMpf_Pre_Mdl_Nuki() {
    grlib::CGLibVtxAttr attrs[5];
    attrs[0].format = 22;
    attrs[0].location = 0;
    attrs[0].offset = 12;
    attrs[0].stream = 0;
    attrs[1].format = 34;
    attrs[1].location = 1;
    attrs[1].offset = 0;
    attrs[1].stream = 1;
    attrs[2].format = 46;
    attrs[2].location = 2;
    attrs[2].offset = 0;
    attrs[2].stream = 2;
    attrs[3].format = 46;
    attrs[3].location = 3;
    attrs[3].offset = 16;
    attrs[3].stream = 2;
    attrs[4].format = 46;
    attrs[4].location = 4;
    attrs[4].offset = 32;
    attrs[4].stream = 2;
    createFetchObj(attrs, 5);
}

void DrResFetch::setupMpf_Pre_Mdl_Nuki_Layer() {
    grlib::CGLibVtxAttr attrs[6];
    attrs[0].format = 22;
    attrs[0].location = 0;
    attrs[0].offset = 12;
    attrs[0].stream = 0;
    attrs[1].format = 34;
    attrs[1].location = 1;
    attrs[1].offset = 0;
    attrs[1].stream = 1;
    attrs[2].format = 46;
    attrs[2].location = 2;
    attrs[2].offset = 0;
    attrs[2].stream = 2;
    attrs[3].format = 46;
    attrs[3].location = 3;
    attrs[3].offset = 16;
    attrs[3].stream = 2;
    attrs[4].format = 46;
    attrs[4].location = 4;
    attrs[4].offset = 32;
    attrs[4].stream = 2;
    attrs[5].format = 17;
    attrs[5].location = 5;
    attrs[5].offset = 52;
    attrs[5].stream = 2;
    createFetchObj(attrs, 6);
}

void DrResFetch::setupMpf_Pre_Mdl_Def() {
    grlib::CGLibVtxAttr attrs[4];
    attrs[0].format = 34;
    attrs[0].location = 0;
    attrs[0].offset = 0;
    attrs[0].stream = 0;
    attrs[1].format = 46;
    attrs[1].location = 1;
    attrs[1].offset = 0;
    attrs[1].stream = 1;
    attrs[2].format = 46;
    attrs[2].location = 2;
    attrs[2].offset = 16;
    attrs[2].stream = 1;
    attrs[3].format = 46;
    attrs[3].location = 3;
    attrs[3].offset = 32;
    attrs[3].stream = 1;
    createFetchObj(attrs, 4);
}

void DrResFetch::setupMpf_Pre_Mdl_Def_Nuki() {
    grlib::CGLibVtxAttr attrs[5];
    attrs[0].format = 34;
    attrs[0].location = 0;
    attrs[0].offset = 0;
    attrs[0].stream = 0;
    attrs[1].format = 22;
    attrs[1].location = 1;
    attrs[1].offset = 12;
    attrs[1].stream = 0;
    attrs[2].format = 46;
    attrs[2].location = 2;
    attrs[2].offset = 0;
    attrs[2].stream = 1;
    attrs[3].format = 46;
    attrs[3].location = 3;
    attrs[3].offset = 16;
    attrs[3].stream = 1;
    attrs[4].format = 46;
    attrs[4].location = 4;
    attrs[4].offset = 32;
    attrs[4].stream = 1;
    createFetchObj(attrs, 5);
}

void DrResFetch::setupMpf_Pre_Mdl_Def_Nuki_Layer() {
    grlib::CGLibVtxAttr attrs[6];
    attrs[0].format = 22;
    attrs[0].location = 0;
    attrs[0].offset = 12;
    attrs[0].stream = 0;
    attrs[1].format = 34;
    attrs[1].location = 1;
    attrs[1].offset = 0;
    attrs[1].stream = 0;
    attrs[2].format = 46;
    attrs[2].location = 2;
    attrs[2].offset = 0;
    attrs[2].stream = 1;
    attrs[3].format = 46;
    attrs[3].location = 3;
    attrs[3].offset = 16;
    attrs[3].stream = 1;
    attrs[4].format = 46;
    attrs[4].location = 4;
    attrs[4].offset = 32;
    attrs[4].stream = 1;
    attrs[5].format = 17;
    attrs[5].location = 5;
    attrs[5].offset = 52;
    attrs[5].stream = 1;
    createFetchObj(attrs, 6);
}

void DrResFetch::setupMpf_Pre_Dithe_Bill() {
    grlib::CGLibVtxAttr attrs[3];
    attrs[0].format = 34;
    attrs[0].location = 0;
    attrs[0].offset = 0;
    attrs[0].stream = 1;
    attrs[1].format = 34;
    attrs[1].location = 1;
    attrs[1].offset = 0;
    attrs[1].stream = 2;
    attrs[2].format = 37;
    attrs[2].location = 2;
    attrs[2].offset = 12;
    attrs[2].stream = 2;
    createFetchObj(attrs, 3);
}

void DrResFetch::setupMpf_Pre_Dithe_Bill_Nuki() {
    grlib::CGLibVtxAttr attrs[4];
    attrs[0].format = 22;
    attrs[0].location = 0;
    attrs[0].offset = 12;
    attrs[0].stream = 0;
    attrs[1].format = 34;
    attrs[1].location = 1;
    attrs[1].offset = 0;
    attrs[1].stream = 1;
    attrs[2].format = 34;
    attrs[2].location = 2;
    attrs[2].offset = 0;
    attrs[2].stream = 2;
    attrs[3].format = 37;
    attrs[3].location = 3;
    attrs[3].offset = 12;
    attrs[3].stream = 2;
    createFetchObj(attrs, 4);
}

void DrResFetch::setupMpf_Pre_Dithe_Bill_Nuki_Layer() {
    grlib::CGLibVtxAttr attrs[5];
    attrs[0].format = 22;
    attrs[0].location = 0;
    attrs[0].offset = 12;
    attrs[0].stream = 0;
    attrs[1].format = 34;
    attrs[1].location = 1;
    attrs[1].offset = 0;
    attrs[1].stream = 1;
    attrs[2].format = 34;
    attrs[2].location = 2;
    attrs[2].offset = 0;
    attrs[2].stream = 2;
    attrs[3].format = 17;
    attrs[3].location = 3;
    attrs[3].offset = 16;
    attrs[3].stream = 2;
    attrs[4].format = 37;
    attrs[4].location = 4;
    attrs[4].offset = 12;
    attrs[4].stream = 2;
    createFetchObj(attrs, 5);
}

void DrResFetch::setupMpf_Pre_Dithe_Mdl() {
    grlib::CGLibVtxAttr attrs[5];
    attrs[0].format = 34;
    attrs[0].location = 0;
    attrs[0].offset = 0;
    attrs[0].stream = 1;
    attrs[1].format = 46;
    attrs[1].location = 1;
    attrs[1].offset = 0;
    attrs[1].stream = 2;
    attrs[2].format = 46;
    attrs[2].location = 2;
    attrs[2].offset = 16;
    attrs[2].stream = 2;
    attrs[3].format = 46;
    attrs[3].location = 3;
    attrs[3].offset = 32;
    attrs[3].stream = 2;
    attrs[4].format = 37;
    attrs[4].location = 4;
    attrs[4].offset = 48;
    attrs[4].stream = 2;
    createFetchObj(attrs, 5);
}

void DrResFetch::setupMpf_Pre_Dithe_Mdl_Nuki() {
    grlib::CGLibVtxAttr attrs[6];
    attrs[0].format = 22;
    attrs[0].location = 0;
    attrs[0].offset = 12;
    attrs[0].stream = 0;
    attrs[1].format = 34;
    attrs[1].location = 1;
    attrs[1].offset = 0;
    attrs[1].stream = 1;
    attrs[2].format = 46;
    attrs[2].location = 2;
    attrs[2].offset = 0;
    attrs[2].stream = 2;
    attrs[3].format = 46;
    attrs[3].location = 3;
    attrs[3].offset = 16;
    attrs[3].stream = 2;
    attrs[4].format = 46;
    attrs[4].location = 4;
    attrs[4].offset = 32;
    attrs[4].stream = 2;
    attrs[5].format = 37;
    attrs[5].location = 5;
    attrs[5].offset = 48;
    attrs[5].stream = 2;
    createFetchObj(attrs, 6);
}

void DrResFetch::setupMpf_Pre_Dithe_Mdl_Nuki_Layer() {
    grlib::CGLibVtxAttr attrs[7];
    attrs[0].format = 22;
    attrs[0].location = 0;
    attrs[0].offset = 12;
    attrs[0].stream = 0;
    attrs[1].format = 34;
    attrs[1].location = 1;
    attrs[1].offset = 0;
    attrs[1].stream = 1;
    attrs[2].format = 46;
    attrs[2].location = 2;
    attrs[2].offset = 0;
    attrs[2].stream = 2;
    attrs[3].format = 46;
    attrs[3].location = 3;
    attrs[3].offset = 16;
    attrs[3].stream = 2;
    attrs[4].format = 46;
    attrs[4].location = 4;
    attrs[4].offset = 32;
    attrs[4].stream = 2;
    attrs[5].format = 17;
    attrs[5].location = 5;
    attrs[5].offset = 52;
    attrs[5].stream = 2;
    attrs[6].format = 37;
    attrs[6].location = 6;
    attrs[6].offset = 48;
    attrs[6].stream = 2;
    createFetchObj(attrs, 7);
}

void DrResFetch::setupMpf_Pre_Dithe_Mdl_Def() {
    grlib::CGLibVtxAttr attrs[5];
    attrs[0].format = 34;
    attrs[0].location = 0;
    attrs[0].offset = 0;
    attrs[0].stream = 0;
    attrs[1].format = 46;
    attrs[1].location = 1;
    attrs[1].offset = 0;
    attrs[1].stream = 1;
    attrs[2].format = 46;
    attrs[2].location = 2;
    attrs[2].offset = 16;
    attrs[2].stream = 1;
    attrs[3].format = 46;
    attrs[3].location = 3;
    attrs[3].offset = 32;
    attrs[3].stream = 1;
    attrs[4].format = 37;
    attrs[4].location = 4;
    attrs[4].offset = 48;
    attrs[4].stream = 1;
    createFetchObj(attrs, 5);
}

void DrResFetch::setupMpf_Pre_Dithe_Mdl_Def_Nuki() {
    grlib::CGLibVtxAttr attrs[6];
    attrs[0].format = 34;
    attrs[0].location = 0;
    attrs[0].offset = 0;
    attrs[0].stream = 0;
    attrs[1].format = 22;
    attrs[1].location = 1;
    attrs[1].offset = 12;
    attrs[1].stream = 0;
    attrs[2].format = 46;
    attrs[2].location = 2;
    attrs[2].offset = 0;
    attrs[2].stream = 1;
    attrs[3].format = 46;
    attrs[3].location = 3;
    attrs[3].offset = 16;
    attrs[3].stream = 1;
    attrs[4].format = 46;
    attrs[4].location = 4;
    attrs[4].offset = 32;
    attrs[4].stream = 1;
    attrs[5].format = 37;
    attrs[5].location = 5;
    attrs[5].offset = 48;
    attrs[5].stream = 1;
    createFetchObj(attrs, 6);
}

void DrResFetch::setupMpf_Pre_Dithe_Mdl_Def_Nuki_Layer() {
    grlib::CGLibVtxAttr attrs[7];
    attrs[0].format = 22;
    attrs[0].location = 0;
    attrs[0].offset = 12;
    attrs[0].stream = 0;
    attrs[1].format = 34;
    attrs[1].location = 1;
    attrs[1].offset = 0;
    attrs[1].stream = 0;
    attrs[2].format = 46;
    attrs[2].location = 2;
    attrs[2].offset = 0;
    attrs[2].stream = 1;
    attrs[3].format = 46;
    attrs[3].location = 3;
    attrs[3].offset = 16;
    attrs[3].stream = 1;
    attrs[4].format = 46;
    attrs[4].location = 4;
    attrs[4].offset = 32;
    attrs[4].stream = 1;
    attrs[5].format = 17;
    attrs[5].location = 5;
    attrs[5].offset = 52;
    attrs[5].stream = 1;
    attrs[6].format = 37;
    attrs[6].location = 6;
    attrs[6].offset = 48;
    attrs[6].stream = 1;
    createFetchObj(attrs, 7);
}

void DrResFetch::setupMpf_Drw_Bill() {
    grlib::CGLibVtxAttr attrs[5];
    attrs[0].format = 22;
    attrs[0].location = 0;
    attrs[0].offset = 12;
    attrs[0].stream = 0;
    attrs[1].format = 34;
    attrs[1].location = 1;
    attrs[1].offset = 0;
    attrs[1].stream = 1;
    attrs[2].format = 34;
    attrs[2].location = 2;
    attrs[2].offset = 12;
    attrs[2].stream = 1;
    attrs[3].format = 34;
    attrs[3].location = 3;
    attrs[3].offset = 0;
    attrs[3].stream = 2;
    attrs[4].format = 37;
    attrs[4].location = 4;
    attrs[4].offset = 12;
    attrs[4].stream = 2;
    createFetchObj(attrs, 5);
}

void DrResFetch::setupMpf_Drw_Bill_Layer() {
    grlib::CGLibVtxAttr attrs[7];
    attrs[0].format = 22;
    attrs[0].location = 0;
    attrs[0].offset = 12;
    attrs[0].stream = 0;
    attrs[1].format = 34;
    attrs[1].location = 1;
    attrs[1].offset = 0;
    attrs[1].stream = 1;
    attrs[2].format = 34;
    attrs[2].location = 2;
    attrs[2].offset = 12;
    attrs[2].stream = 1;
    attrs[3].format = 34;
    attrs[3].location = 3;
    attrs[3].offset = 0;
    attrs[3].stream = 2;
    attrs[4].format = 37;
    attrs[4].location = 4;
    attrs[4].offset = 12;
    attrs[4].stream = 2;
    attrs[5].format = 17;
    attrs[5].location = 5;
    attrs[5].offset = 16;
    attrs[5].stream = 2;
    attrs[6].format = 38;
    attrs[6].location = 6;
    attrs[6].offset = 20;
    attrs[6].stream = 2;
    createFetchObj(attrs, 7);
}

void DrResFetch::setupMpf_Drw_Mdl() {
    grlib::CGLibVtxAttr attrs[9];
    attrs[0].format = 22;
    attrs[0].location = 0;
    attrs[0].offset = 12;
    attrs[0].stream = 0;
    attrs[1].format = 34;
    attrs[1].location = 1;
    attrs[1].offset = 20;
    attrs[1].stream = 0;
    attrs[2].format = 37;
    attrs[2].location = 2;
    attrs[2].offset = 32;
    attrs[2].stream = 0;
    attrs[3].format = 34;
    attrs[3].location = 3;
    attrs[3].offset = 0;
    attrs[3].stream = 1;
    attrs[4].format = 34;
    attrs[4].location = 4;
    attrs[4].offset = 12;
    attrs[4].stream = 1;
    attrs[5].format = 46;
    attrs[5].location = 5;
    attrs[5].offset = 0;
    attrs[5].stream = 2;
    attrs[6].format = 46;
    attrs[6].location = 6;
    attrs[6].offset = 16;
    attrs[6].stream = 2;
    attrs[7].format = 46;
    attrs[7].location = 7;
    attrs[7].offset = 32;
    attrs[7].stream = 2;
    attrs[8].format = 37;
    attrs[8].location = 8;
    attrs[8].offset = 48;
    attrs[8].stream = 2;
    createFetchObj(attrs, 9);
}

void DrResFetch::setupMpf_Drw_Mdl_Layer() {
    grlib::CGLibVtxAttr attrs[10];
    attrs[0].format = 22;
    attrs[0].location = 0;
    attrs[0].offset = 12;
    attrs[0].stream = 0;
    attrs[1].format = 34;
    attrs[1].location = 1;
    attrs[1].offset = 20;
    attrs[1].stream = 0;
    attrs[2].format = 37;
    attrs[2].location = 2;
    attrs[2].offset = 32;
    attrs[2].stream = 0;
    attrs[3].format = 34;
    attrs[3].location = 3;
    attrs[3].offset = 0;
    attrs[3].stream = 1;
    attrs[4].format = 34;
    attrs[4].location = 4;
    attrs[4].offset = 12;
    attrs[4].stream = 1;
    attrs[5].format = 46;
    attrs[5].location = 5;
    attrs[5].offset = 0;
    attrs[5].stream = 2;
    attrs[6].format = 46;
    attrs[6].location = 6;
    attrs[6].offset = 16;
    attrs[6].stream = 2;
    attrs[7].format = 46;
    attrs[7].location = 7;
    attrs[7].offset = 32;
    attrs[7].stream = 2;
    attrs[8].format = 37;
    attrs[8].location = 8;
    attrs[8].offset = 48;
    attrs[8].stream = 2;
    attrs[9].format = 17;
    attrs[9].location = 9;
    attrs[9].offset = 52;
    attrs[9].stream = 2;
    createFetchObj(attrs, 10);
}

void DrResFetch::setupMpf_Drw_Mdl_NoNom() {
    grlib::CGLibVtxAttr attrs[8];
    attrs[0].format = 22;
    attrs[0].location = 0;
    attrs[0].offset = 12;
    attrs[0].stream = 0;
    attrs[1].format = 37;
    attrs[1].location = 1;
    attrs[1].offset = 20;
    attrs[1].stream = 0;
    attrs[2].format = 34;
    attrs[2].location = 2;
    attrs[2].offset = 0;
    attrs[2].stream = 1;
    attrs[3].format = 34;
    attrs[3].location = 3;
    attrs[3].offset = 12;
    attrs[3].stream = 1;
    attrs[4].format = 46;
    attrs[4].location = 4;
    attrs[4].offset = 0;
    attrs[4].stream = 2;
    attrs[5].format = 46;
    attrs[5].location = 5;
    attrs[5].offset = 16;
    attrs[5].stream = 2;
    attrs[6].format = 46;
    attrs[6].location = 6;
    attrs[6].offset = 32;
    attrs[6].stream = 2;
    attrs[7].format = 37;
    attrs[7].location = 7;
    attrs[7].offset = 48;
    attrs[7].stream = 2;
    createFetchObj(attrs, 8);
}

void DrResFetch::setupMpf_Drw_Mdl_NoNom_Layer() {
    grlib::CGLibVtxAttr attrs[9];
    attrs[0].format = 22;
    attrs[0].location = 0;
    attrs[0].offset = 12;
    attrs[0].stream = 0;
    attrs[1].format = 37;
    attrs[1].location = 1;
    attrs[1].offset = 20;
    attrs[1].stream = 0;
    attrs[2].format = 34;
    attrs[2].location = 2;
    attrs[2].offset = 0;
    attrs[2].stream = 1;
    attrs[3].format = 34;
    attrs[3].location = 3;
    attrs[3].offset = 12;
    attrs[3].stream = 1;
    attrs[4].format = 46;
    attrs[4].location = 4;
    attrs[4].offset = 0;
    attrs[4].stream = 2;
    attrs[5].format = 46;
    attrs[5].location = 5;
    attrs[5].offset = 16;
    attrs[5].stream = 2;
    attrs[6].format = 46;
    attrs[6].location = 6;
    attrs[6].offset = 32;
    attrs[6].stream = 2;
    attrs[7].format = 37;
    attrs[7].location = 7;
    attrs[7].offset = 48;
    attrs[7].stream = 2;
    attrs[8].format = 17;
    attrs[8].location = 8;
    attrs[8].offset = 52;
    attrs[8].stream = 2;
    createFetchObj(attrs, 9);
}

void DrResFetch::setupMpf_Drw_Mdl_Def() {
    grlib::CGLibVtxAttr attrs[8];
    attrs[0].format = 34;
    attrs[0].location = 0;
    attrs[0].offset = 0;
    attrs[0].stream = 0;
    attrs[1].format = 22;
    attrs[1].location = 1;
    attrs[1].offset = 12;
    attrs[1].stream = 0;
    attrs[2].format = 34;
    attrs[2].location = 2;
    attrs[2].offset = 20;
    attrs[2].stream = 0;
    attrs[3].format = 37;
    attrs[3].location = 3;
    attrs[3].offset = 32;
    attrs[3].stream = 0;
    attrs[4].format = 46;
    attrs[4].location = 4;
    attrs[4].offset = 0;
    attrs[4].stream = 1;
    attrs[5].format = 46;
    attrs[5].location = 5;
    attrs[5].offset = 16;
    attrs[5].stream = 1;
    attrs[6].format = 46;
    attrs[6].location = 6;
    attrs[6].offset = 32;
    attrs[6].stream = 1;
    attrs[7].format = 37;
    attrs[7].location = 7;
    attrs[7].offset = 48;
    attrs[7].stream = 1;
    createFetchObj(attrs, 8);
}

void DrResFetch::setupMpf_Drw_Mdl_Def_Layer() {
    grlib::CGLibVtxAttr attrs[9];
    attrs[0].format = 34;
    attrs[0].location = 0;
    attrs[0].offset = 0;
    attrs[0].stream = 0;
    attrs[1].format = 22;
    attrs[1].location = 1;
    attrs[1].offset = 12;
    attrs[1].stream = 0;
    attrs[2].format = 34;
    attrs[2].location = 2;
    attrs[2].offset = 20;
    attrs[2].stream = 0;
    attrs[3].format = 37;
    attrs[3].location = 3;
    attrs[3].offset = 32;
    attrs[3].stream = 0;
    attrs[4].format = 46;
    attrs[4].location = 4;
    attrs[4].offset = 0;
    attrs[4].stream = 1;
    attrs[5].format = 46;
    attrs[5].location = 5;
    attrs[5].offset = 16;
    attrs[5].stream = 1;
    attrs[6].format = 46;
    attrs[6].location = 6;
    attrs[6].offset = 32;
    attrs[6].stream = 1;
    attrs[7].format = 37;
    attrs[7].location = 7;
    attrs[7].offset = 48;
    attrs[7].stream = 1;
    attrs[8].format = 17;
    attrs[8].location = 8;
    attrs[8].offset = 52;
    attrs[8].stream = 1;
    createFetchObj(attrs, 9);
}

void DrResFetch::setupMpf_Drw_Mdl_Def_NoNom() {
    grlib::CGLibVtxAttr attrs[7];
    attrs[0].format = 34;
    attrs[0].location = 0;
    attrs[0].offset = 0;
    attrs[0].stream = 0;
    attrs[1].format = 22;
    attrs[1].location = 1;
    attrs[1].offset = 12;
    attrs[1].stream = 0;
    attrs[2].format = 37;
    attrs[2].location = 2;
    attrs[2].offset = 20;
    attrs[2].stream = 0;
    attrs[3].format = 46;
    attrs[3].location = 3;
    attrs[3].offset = 0;
    attrs[3].stream = 1;
    attrs[4].format = 46;
    attrs[4].location = 4;
    attrs[4].offset = 16;
    attrs[4].stream = 1;
    attrs[5].format = 46;
    attrs[5].location = 5;
    attrs[5].offset = 32;
    attrs[5].stream = 1;
    attrs[6].format = 37;
    attrs[6].location = 6;
    attrs[6].offset = 48;
    attrs[6].stream = 1;
    createFetchObj(attrs, 7);
}

void DrResFetch::setupMpf_Drw_Mdl_Def_NoNom_Layer() {
    grlib::CGLibVtxAttr attrs[8];
    attrs[0].format = 34;
    attrs[0].location = 0;
    attrs[0].offset = 0;
    attrs[0].stream = 0;
    attrs[1].format = 22;
    attrs[1].location = 1;
    attrs[1].offset = 12;
    attrs[1].stream = 0;
    attrs[2].format = 37;
    attrs[2].location = 2;
    attrs[2].offset = 20;
    attrs[2].stream = 0;
    attrs[3].format = 46;
    attrs[3].location = 3;
    attrs[3].offset = 0;
    attrs[3].stream = 1;
    attrs[4].format = 46;
    attrs[4].location = 4;
    attrs[4].offset = 16;
    attrs[4].stream = 1;
    attrs[5].format = 46;
    attrs[5].location = 5;
    attrs[5].offset = 32;
    attrs[5].stream = 1;
    attrs[6].format = 37;
    attrs[6].location = 6;
    attrs[6].offset = 48;
    attrs[6].stream = 1;
    attrs[7].format = 17;
    attrs[7].location = 7;
    attrs[7].offset = 52;
    attrs[7].stream = 1;
    createFetchObj(attrs, 8);
}

void DrResFetch::setupMpf_Drw_Mdl_NormalMap() {
    grlib::CGLibVtxAttr attrs[9];
    attrs[0].format = 34;
    attrs[0].location = 0;
    attrs[0].offset = 0;
    attrs[0].stream = 0;
    attrs[1].format = 22;
    attrs[1].location = 1;
    attrs[1].offset = 12;
    attrs[1].stream = 0;
    attrs[2].format = 34;
    attrs[2].location = 2;
    attrs[2].offset = 20;
    attrs[2].stream = 0;
    attrs[3].format = 43;
    attrs[3].location = 3;
    attrs[3].offset = 32;
    attrs[3].stream = 0;
    attrs[4].format = 37;
    attrs[4].location = 4;
    attrs[4].offset = 40;
    attrs[4].stream = 0;
    attrs[5].format = 46;
    attrs[5].location = 5;
    attrs[5].offset = 0;
    attrs[5].stream = 1;
    attrs[6].format = 46;
    attrs[6].location = 6;
    attrs[6].offset = 16;
    attrs[6].stream = 1;
    attrs[7].format = 46;
    attrs[7].location = 7;
    attrs[7].offset = 32;
    attrs[7].stream = 1;
    attrs[8].format = 37;
    attrs[8].location = 8;
    attrs[8].offset = 48;
    attrs[8].stream = 1;
    createFetchObj(attrs, 9);
}

void DrResFetch::setupMpf_Drw_Mdl_NormalMap_Wind() {
    grlib::CGLibVtxAttr attrs[10];
    attrs[0].format = 22;
    attrs[0].location = 0;
    attrs[0].offset = 12;
    attrs[0].stream = 0;
    attrs[1].format = 34;
    attrs[1].location = 1;
    attrs[1].offset = 20;
    attrs[1].stream = 0;
    attrs[2].format = 43;
    attrs[2].location = 2;
    attrs[2].offset = 32;
    attrs[2].stream = 0;
    attrs[3].format = 37;
    attrs[3].location = 3;
    attrs[3].offset = 40;
    attrs[3].stream = 0;
    attrs[4].format = 34;
    attrs[4].location = 4;
    attrs[4].offset = 0;
    attrs[4].stream = 1;
    attrs[5].format = 34;
    attrs[5].location = 5;
    attrs[5].offset = 12;
    attrs[5].stream = 1;
    attrs[6].format = 46;
    attrs[6].location = 6;
    attrs[6].offset = 0;
    attrs[6].stream = 2;
    attrs[7].format = 46;
    attrs[7].location = 7;
    attrs[7].offset = 16;
    attrs[7].stream = 2;
    attrs[8].format = 46;
    attrs[8].location = 8;
    attrs[8].offset = 32;
    attrs[8].stream = 2;
    attrs[9].format = 37;
    attrs[9].location = 9;
    attrs[9].offset = 48;
    attrs[9].stream = 2;
    createFetchObj(attrs, 10);
}

void DrResFetch::setupMpf_Drw_Mdl_NormalMap_Wind_Layer() {
    grlib::CGLibVtxAttr attrs[11];
    attrs[0].format = 22;
    attrs[0].location = 0;
    attrs[0].offset = 12;
    attrs[0].stream = 0;
    attrs[1].format = 34;
    attrs[1].location = 1;
    attrs[1].offset = 20;
    attrs[1].stream = 0;
    attrs[2].format = 43;
    attrs[2].location = 2;
    attrs[2].offset = 32;
    attrs[2].stream = 0;
    attrs[3].format = 37;
    attrs[3].location = 3;
    attrs[3].offset = 40;
    attrs[3].stream = 0;
    attrs[4].format = 34;
    attrs[4].location = 4;
    attrs[4].offset = 0;
    attrs[4].stream = 1;
    attrs[5].format = 34;
    attrs[5].location = 5;
    attrs[5].offset = 12;
    attrs[5].stream = 1;
    attrs[6].format = 46;
    attrs[6].location = 6;
    attrs[6].offset = 0;
    attrs[6].stream = 2;
    attrs[7].format = 46;
    attrs[7].location = 7;
    attrs[7].offset = 16;
    attrs[7].stream = 2;
    attrs[8].format = 46;
    attrs[8].location = 8;
    attrs[8].offset = 32;
    attrs[8].stream = 2;
    attrs[9].format = 37;
    attrs[9].location = 9;
    attrs[9].offset = 48;
    attrs[9].stream = 2;
    attrs[10].format = 17;
    attrs[10].location = 10;
    attrs[10].offset = 52;
    attrs[10].stream = 2;
    createFetchObj(attrs, 11);
}

void DrResFetch::setupMpf_Drw_Mdl_NormalMap_Wind_VNom() {
    grlib::CGLibVtxAttr attrs[10];
    attrs[0].format = 22;
    attrs[0].location = 0;
    attrs[0].offset = 12;
    attrs[0].stream = 0;
    attrs[1].format = 34;
    attrs[1].location = 1;
    attrs[1].offset = 24;
    attrs[1].stream = 1;
    attrs[2].format = 46;
    attrs[2].location = 2;
    attrs[2].offset = 36;
    attrs[2].stream = 1;
    attrs[3].format = 37;
    attrs[3].location = 3;
    attrs[3].offset = 40;
    attrs[3].stream = 0;
    attrs[4].format = 34;
    attrs[4].location = 4;
    attrs[4].offset = 0;
    attrs[4].stream = 1;
    attrs[5].format = 34;
    attrs[5].location = 5;
    attrs[5].offset = 12;
    attrs[5].stream = 1;
    attrs[6].format = 46;
    attrs[6].location = 6;
    attrs[6].offset = 0;
    attrs[6].stream = 2;
    attrs[7].format = 46;
    attrs[7].location = 7;
    attrs[7].offset = 16;
    attrs[7].stream = 2;
    attrs[8].format = 46;
    attrs[8].location = 8;
    attrs[8].offset = 32;
    attrs[8].stream = 2;
    attrs[9].format = 37;
    attrs[9].location = 9;
    attrs[9].offset = 48;
    attrs[9].stream = 2;
    createFetchObj(attrs, 10);
}

void DrResFetch::setupMpf_Drw_Mdl_NormalMap_Layer() {
    grlib::CGLibVtxAttr attrs[10];
    attrs[0].format = 22;
    attrs[0].location = 0;
    attrs[0].offset = 12;
    attrs[0].stream = 0;
    attrs[1].format = 34;
    attrs[1].location = 1;
    attrs[1].offset = 20;
    attrs[1].stream = 0;
    attrs[2].format = 43;
    attrs[2].location = 2;
    attrs[2].offset = 32;
    attrs[2].stream = 0;
    attrs[3].format = 37;
    attrs[3].location = 3;
    attrs[3].offset = 40;
    attrs[3].stream = 0;
    attrs[4].format = 34;
    attrs[4].location = 4;
    attrs[4].offset = 0;
    attrs[4].stream = 0;
    attrs[5].format = 46;
    attrs[5].location = 5;
    attrs[5].offset = 0;
    attrs[5].stream = 1;
    attrs[6].format = 46;
    attrs[6].location = 6;
    attrs[6].offset = 16;
    attrs[6].stream = 1;
    attrs[7].format = 46;
    attrs[7].location = 7;
    attrs[7].offset = 32;
    attrs[7].stream = 1;
    attrs[8].format = 37;
    attrs[8].location = 8;
    attrs[8].offset = 48;
    attrs[8].stream = 1;
    attrs[9].format = 17;
    attrs[9].location = 9;
    attrs[9].offset = 52;
    attrs[9].stream = 1;
    createFetchObj(attrs, 10);
}

void DrResFetch::setupZBuffInstDith() {
    grlib::CGLibVtxAttr attrs[5];
    attrs[0].format = 34;
    attrs[0].location = 0;
    attrs[0].offset = 0;
    attrs[0].stream = 0;
    attrs[1].format = 46;
    attrs[1].location = 1;
    attrs[1].offset = 0;
    attrs[1].stream = 1;
    attrs[2].format = 46;
    attrs[2].location = 2;
    attrs[2].offset = 16;
    attrs[2].stream = 1;
    attrs[3].format = 46;
    attrs[3].location = 3;
    attrs[3].offset = 32;
    attrs[3].stream = 1;
    attrs[4].format = 10;
    attrs[4].location = 4;
    attrs[4].offset = 48;
    attrs[4].stream = 1;
    createFetchObj(attrs, 5);
}

void DrResFetch::setupZBuffInstDithTex() {
    grlib::CGLibVtxAttr attrs[6];
    attrs[0].format = 34;
    attrs[0].location = 0;
    attrs[0].offset = 0;
    attrs[0].stream = 0;
    attrs[1].format = 22;
    attrs[1].location = 1;
    attrs[1].offset = 12;
    attrs[1].stream = 0;
    attrs[2].format = 46;
    attrs[2].location = 2;
    attrs[2].offset = 0;
    attrs[2].stream = 1;
    attrs[3].format = 46;
    attrs[3].location = 3;
    attrs[3].offset = 16;
    attrs[3].stream = 1;
    attrs[4].format = 46;
    attrs[4].location = 4;
    attrs[4].offset = 32;
    attrs[4].stream = 1;
    attrs[5].format = 10;
    attrs[5].location = 5;
    attrs[5].offset = 48;
    attrs[5].stream = 1;
    createFetchObj(attrs, 6);
}

void DrResFetch::setupZBuffInstBillDith() {
    grlib::CGLibVtxAttr attrs[6];
    attrs[0].format = 34;
    attrs[0].location = 0;
    attrs[0].offset = 0;
    attrs[0].stream = 0;
    attrs[1].format = 20;
    attrs[1].location = 1;
    attrs[1].offset = 12;
    attrs[1].stream = 0;
    attrs[2].format = 46;
    attrs[2].location = 2;
    attrs[2].offset = 0;
    attrs[2].stream = 1;
    attrs[3].format = 46;
    attrs[3].location = 3;
    attrs[3].offset = 16;
    attrs[3].stream = 1;
    attrs[4].format = 46;
    attrs[4].location = 4;
    attrs[4].offset = 32;
    attrs[4].stream = 1;
    attrs[5].format = 10;
    attrs[5].location = 5;
    attrs[5].offset = 48;
    attrs[5].stream = 1;
    createFetchObj(attrs, 6);
}

void DrResFetch::setupZBuffInstBillDithTex() {
    grlib::CGLibVtxAttr attrs[7];
    attrs[0].format = 34;
    attrs[0].location = 0;
    attrs[0].offset = 0;
    attrs[0].stream = 0;
    attrs[1].format = 20;
    attrs[1].location = 1;
    attrs[1].offset = 12;
    attrs[1].stream = 0;
    attrs[2].format = 22;
    attrs[2].location = 2;
    attrs[2].offset = 16;
    attrs[2].stream = 0;
    attrs[3].format = 46;
    attrs[3].location = 3;
    attrs[3].offset = 0;
    attrs[3].stream = 1;
    attrs[4].format = 46;
    attrs[4].location = 4;
    attrs[4].offset = 16;
    attrs[4].stream = 1;
    attrs[5].format = 46;
    attrs[5].location = 5;
    attrs[5].offset = 32;
    attrs[5].stream = 1;
    attrs[6].format = 10;
    attrs[6].location = 6;
    attrs[6].offset = 52;
    attrs[6].stream = 1;
    createFetchObj(attrs, 7);
}

void DrResFetch::setupDebugPosColor() {
    grlib::CGLibVtxAttr attrs[2];
    attrs[0].format = 34;
    attrs[0].location = 0;
    attrs[0].offset = 0;
    attrs[0].stream = 0;
    attrs[1].format = 37;
    attrs[1].location = 1;
    attrs[1].offset = 12;
    attrs[1].stream = 0;
    createFetchObj(attrs, 2);
}

void DrResFetch::setupXYZW() {
    grlib::CGLibVtxAttr attrs[1];
    attrs[0].format = 46;
    attrs[0].location = 0;
    attrs[0].offset = 0;
    attrs[0].stream = 0;
    createFetchObj(attrs, 1);
}

void DrResFetch::setupOutLineObj() {
    grlib::CGLibVtxAttr attrs[3];
    attrs[0].format = 34;
    attrs[0].location = 0;
    attrs[0].offset = 0;
    attrs[0].stream = 0;
    attrs[1].format = 38;
    attrs[1].location = 1;
    attrs[1].offset = 0;
    attrs[1].stream = 1;
    attrs[2].format = 37;
    attrs[2].location = 2;
    attrs[2].offset = 4;
    attrs[2].stream = 1;
    createFetchObj(attrs, 3);
}

void DrResFetch::setupGlassBrObj() {
    grlib::CGLibVtxAttr attrs[2];
    attrs[0].format = 45;
    attrs[0].location = 0;
    attrs[0].offset = 0;
    attrs[0].stream = 0;
    attrs[1].format = 38;
    attrs[1].location = 1;
    attrs[1].offset = 8;
    attrs[1].stream = 0;
    createFetchObj(attrs, 2);
}

void DrResFetch::setupMofSetObj() {
    grlib::CGLibVtxAttr attrs[2];
    attrs[0].format = 46;
    attrs[0].location = 0;
    attrs[0].offset = 0;
    attrs[0].stream = 0;
    attrs[1].format = 47;
    attrs[1].location = 1;
    attrs[1].offset = 16;
    attrs[1].stream = 0;
    createFetchObj(attrs, 2);
}

void DrResFetch::setupMeshVtxObj() {
    grlib::CGLibVtxAttr attrs[2];
    attrs[0].format = 45;
    attrs[0].location = 0;
    attrs[0].offset = 0;
    attrs[0].stream = 0;
    attrs[1].format = 38;
    attrs[1].location = 1;
    attrs[1].offset = 8;
    attrs[1].stream = 0;
    createFetchObj(attrs, 2);
}

void DrResFetch::setupOutMeshVtx() {
    grlib::CGLibVtxAttr attrs[4];
    attrs[0].format = 22;
    attrs[0].location = 0;
    attrs[0].offset = 0;
    attrs[0].stream = 0;
    attrs[1].format = 37;
    attrs[1].location = 1;
    attrs[1].offset = 8;
    attrs[1].stream = 0;
    attrs[2].format = 34;
    attrs[2].location = 2;
    attrs[2].offset = 0;
    attrs[2].stream = 1;
    attrs[3].format = 37;
    attrs[3].location = 3;
    attrs[3].offset = 12;
    attrs[3].stream = 1;
    createFetchObj(attrs, 4);
}

void DrResFetch::setupMpf_Cull_Fade_Mdl() {
    grlib::CGLibVtxAttr attrs[4];
    attrs[0].format = 46;
    attrs[0].location = 0;
    attrs[0].offset = 0;
    attrs[0].stream = 0;
    attrs[1].format = 46;
    attrs[1].location = 1;
    attrs[1].offset = 16;
    attrs[1].stream = 0;
    attrs[2].format = 46;
    attrs[2].location = 2;
    attrs[2].offset = 32;
    attrs[2].stream = 0;
    attrs[3].format = 47;
    attrs[3].location = 3;
    attrs[3].offset = 48;
    attrs[3].stream = 0;
    createFetchObj(attrs, 4);
}

void DrResFetch::setupMpf_Pre_Mdl_Layer() {
    grlib::CGLibVtxAttr attrs[5];
    attrs[0].format = 34;
    attrs[0].location = 0;
    attrs[0].offset = 0;
    attrs[0].stream = 1;
    attrs[1].format = 46;
    attrs[1].location = 1;
    attrs[1].offset = 0;
    attrs[1].stream = 2;
    attrs[2].format = 46;
    attrs[2].location = 2;
    attrs[2].offset = 16;
    attrs[2].stream = 2;
    attrs[3].format = 46;
    attrs[3].location = 3;
    attrs[3].offset = 32;
    attrs[3].stream = 2;
    attrs[4].format = 17;
    attrs[4].location = 4;
    attrs[4].offset = 52;
    attrs[4].stream = 2;
    createFetchObj(attrs, 5);
}

void DrResFetch::setupMpf_Pre_Dithe_Mdl_Layer() {
    grlib::CGLibVtxAttr attrs[6];
    attrs[0].format = 34;
    attrs[0].location = 0;
    attrs[0].offset = 0;
    attrs[0].stream = 1;
    attrs[1].format = 46;
    attrs[1].location = 1;
    attrs[1].offset = 0;
    attrs[1].stream = 2;
    attrs[2].format = 46;
    attrs[2].location = 2;
    attrs[2].offset = 16;
    attrs[2].stream = 2;
    attrs[3].format = 46;
    attrs[3].location = 3;
    attrs[3].offset = 32;
    attrs[3].stream = 2;
    attrs[4].format = 17;
    attrs[4].location = 4;
    attrs[4].offset = 52;
    attrs[4].stream = 2;
    attrs[5].format = 37;
    attrs[5].location = 5;
    attrs[5].offset = 48;
    attrs[5].stream = 2;
    createFetchObj(attrs, 6);
}

void DrResFetch::setupWeightVtx() {
    grlib::CGLibVtxAttr attrs[2];
    attrs[0].format = 42;
    attrs[0].location = 0;
    attrs[0].offset = 0;
    attrs[0].stream = 0;
    attrs[1].format = 39;
    attrs[1].location = 1;
    attrs[1].offset = 8;
    attrs[1].stream = 0;
    createFetchObj(attrs, 2);
}

void DrResFetch::setupShadowFw() {
    grlib::CGLibVtxAttr attrs[4];
    attrs[0].format = 34;
    attrs[0].location = 0;
    attrs[0].offset = 0;
    attrs[0].stream = 0;
    attrs[1].format = 22;
    attrs[1].location = 1;
    attrs[1].offset = 12;
    attrs[1].stream = 0;
    attrs[2].format = 37;
    attrs[2].location = 2;
    attrs[2].offset = 20;
    attrs[2].stream = 0;
    attrs[3].format = 38;
    attrs[3].location = 3;
    attrs[3].offset = 24;
    attrs[3].stream = 0;
    createFetchObj(attrs, 4);
}

void DrResFetch::setupDepthCheck() {
    grlib::CGLibVtxAttr attrs[2];
    attrs[0].format = 34;
    attrs[0].location = 0;
    attrs[0].offset = 0;
    attrs[0].stream = 0;
    attrs[1].format = 46;
    attrs[1].location = 1;
    attrs[1].offset = 0;
    attrs[1].stream = 1;
    createFetchObj(attrs, 2);
}

void DrResFetch::setupDebTexStm() {
    grlib::CGLibVtxAttr attrs[3];
    attrs[0].format = 22;
    attrs[0].location = 0;
    attrs[0].offset = 0;
    attrs[0].stream = 0;
    attrs[1].format = 46;
    attrs[1].location = 1;
    attrs[1].offset = 0;
    attrs[1].stream = 1;
    attrs[2].format = 37;
    attrs[2].location = 2;
    attrs[2].offset = 16;
    attrs[2].stream = 1;
    createFetchObj(attrs, 3);
}

void DrResFetch::setupZBuffFw() {
    grlib::CGLibVtxAttr attrs[4];
    attrs[0].format = 34;
    attrs[0].location = 0;
    attrs[0].offset = 0;
    attrs[0].stream = 0;
    attrs[1].format = 22;
    attrs[1].location = 1;
    attrs[1].offset = 12;
    attrs[1].stream = 0;
    attrs[2].format = 37;
    attrs[2].location = 2;
    attrs[2].offset = 20;
    attrs[2].stream = 0;
    attrs[3].format = 38;
    attrs[3].location = 3;
    attrs[3].offset = 24;
    attrs[3].stream = 0;
    createFetchObj(attrs, 4);
}

void DrResFetch::setupZBuffFwAL() {
    grlib::CGLibVtxAttr attrs[5];
    attrs[0].format = 34;
    attrs[0].location = 0;
    attrs[0].offset = 0;
    attrs[0].stream = 0;
    attrs[1].format = 22;
    attrs[1].location = 1;
    attrs[1].offset = 12;
    attrs[1].stream = 0;
    attrs[2].format = 37;
    attrs[2].location = 2;
    attrs[2].offset = 20;
    attrs[2].stream = 0;
    attrs[3].format = 38;
    attrs[3].location = 3;
    attrs[3].offset = 24;
    attrs[3].stream = 0;
    attrs[4].format = 10;
    attrs[4].location = 4;
    attrs[4].offset = 0;
    attrs[4].stream = 1;
    createFetchObj(attrs, 5);
}

void DrResFetch::setupMofZBuffObj() {
    grlib::CGLibVtxAttr attrs[1];
    attrs[0].format = 34;
    attrs[0].location = 0;
    attrs[0].offset = 0;
    attrs[0].stream = 2;
    createFetchObj(attrs, 1);
}

void DrResFetch::setupMofZBuffObjTex() {
    grlib::CGLibVtxAttr attrs[2];
    attrs[0].format = 34;
    attrs[0].location = 0;
    attrs[0].offset = 0;
    attrs[0].stream = 2;
    attrs[1].format = 22;
    attrs[1].location = 1;
    attrs[1].offset = 0;
    attrs[1].stream = 0;
    createFetchObj(attrs, 2);
}

void DrResFetch::setupMofZBuffMot() {
    grlib::CGLibVtxAttr attrs[2];
    attrs[0].format = 34;
    attrs[0].location = 0;
    attrs[0].offset = 0;
    attrs[0].stream = 2;
    attrs[1].format = 20;
    attrs[1].location = 1;
    attrs[1].offset = 0;
    attrs[1].stream = 0;
    createFetchObj(attrs, 2);
}

void DrResFetch::setupMofZBuffMotTex() {
    grlib::CGLibVtxAttr attrs[3];
    attrs[0].format = 34;
    attrs[0].location = 0;
    attrs[0].offset = 0;
    attrs[0].stream = 2;
    attrs[1].format = 20;
    attrs[1].location = 1;
    attrs[1].offset = 0;
    attrs[1].stream = 0;
    attrs[2].format = 22;
    attrs[2].location = 2;
    attrs[2].offset = 4;
    attrs[2].stream = 0;
    createFetchObj(attrs, 3);
}

void DrResFetch::setupMofZBuffObjAL() {
    grlib::CGLibVtxAttr attrs[2];
    attrs[0].format = 34;
    attrs[0].location = 0;
    attrs[0].offset = 0;
    attrs[0].stream = 2;
    attrs[1].format = 10;
    attrs[1].location = 1;
    attrs[1].offset = 0;
    attrs[1].stream = 1;
    createFetchObj(attrs, 2);
}

void DrResFetch::setupMofZBuffObjTexAL() {
    grlib::CGLibVtxAttr attrs[3];
    attrs[0].format = 34;
    attrs[0].location = 0;
    attrs[0].offset = 0;
    attrs[0].stream = 2;
    attrs[1].format = 22;
    attrs[1].location = 1;
    attrs[1].offset = 0;
    attrs[1].stream = 0;
    attrs[2].format = 10;
    attrs[2].location = 2;
    attrs[2].offset = 0;
    attrs[2].stream = 1;
    createFetchObj(attrs, 3);
}

void DrResFetch::setupMofZBuffMotAL() {
    grlib::CGLibVtxAttr attrs[3];
    attrs[0].format = 34;
    attrs[0].location = 0;
    attrs[0].offset = 0;
    attrs[0].stream = 2;
    attrs[1].format = 20;
    attrs[1].location = 1;
    attrs[1].offset = 0;
    attrs[1].stream = 0;
    attrs[2].format = 10;
    attrs[2].location = 2;
    attrs[2].offset = 0;
    attrs[2].stream = 1;
    createFetchObj(attrs, 3);
}

void DrResFetch::setupMofZBuffMotTexAL() {
    grlib::CGLibVtxAttr attrs[4];
    attrs[0].format = 34;
    attrs[0].location = 0;
    attrs[0].offset = 0;
    attrs[0].stream = 2;
    attrs[1].format = 20;
    attrs[1].location = 1;
    attrs[1].offset = 0;
    attrs[1].stream = 0;
    attrs[2].format = 22;
    attrs[2].location = 2;
    attrs[2].offset = 4;
    attrs[2].stream = 0;
    attrs[3].format = 10;
    attrs[3].location = 3;
    attrs[3].offset = 0;
    attrs[3].stream = 1;
    createFetchObj(attrs, 4);
}

void DrResFetch::setupMofShadowObj() {
    grlib::CGLibVtxAttr attrs[1];
    attrs[0].format = 34;
    attrs[0].location = 0;
    attrs[0].offset = 0;
    attrs[0].stream = 2;
    createFetchObj(attrs, 1);
}

void DrResFetch::setupMofShadowObjTex() {
    grlib::CGLibVtxAttr attrs[2];
    attrs[0].format = 34;
    attrs[0].location = 0;
    attrs[0].offset = 0;
    attrs[0].stream = 2;
    attrs[1].format = 22;
    attrs[1].location = 1;
    attrs[1].offset = 0;
    attrs[1].stream = 0;
    createFetchObj(attrs, 2);
}

void DrResFetch::setupMofShadowMot() {
    grlib::CGLibVtxAttr attrs[2];
    attrs[0].format = 34;
    attrs[0].location = 0;
    attrs[0].offset = 0;
    attrs[0].stream = 2;
    attrs[1].format = 20;
    attrs[1].location = 1;
    attrs[1].offset = 0;
    attrs[1].stream = 0;
    createFetchObj(attrs, 2);
}

void DrResFetch::setupMofShadowMotTex() {
    grlib::CGLibVtxAttr attrs[3];
    attrs[0].format = 34;
    attrs[0].location = 0;
    attrs[0].offset = 0;
    attrs[0].stream = 2;
    attrs[1].format = 20;
    attrs[1].location = 1;
    attrs[1].offset = 0;
    attrs[1].stream = 0;
    attrs[2].format = 22;
    attrs[2].location = 2;
    attrs[2].offset = 4;
    attrs[2].stream = 0;
    createFetchObj(attrs, 3);
}

void DrResFetch::setupMeshVtxAdd() {
    grlib::CGLibVtxAttr attrs[3];
    attrs[0].format = 34;
    attrs[0].location = 0;
    attrs[0].offset = 0;
    attrs[0].stream = 0;
    attrs[1].format = 37;
    attrs[1].location = 1;
    attrs[1].offset = 12;
    attrs[1].stream = 0;
    attrs[2].format = 46;
    attrs[2].location = 2;
    attrs[2].offset = 16;
    attrs[2].stream = 0;
    createFetchObj(attrs, 3);
}

void DrResFetch::setLgtVertexParam() {
    grlib::CGLibVtxAttr attrs[2];
    attrs[0].format = 34;
    attrs[0].location = 0;
    attrs[0].offset = 0;
    attrs[0].stream = 0;
    attrs[1].format = 22;
    attrs[1].location = 1;
    attrs[1].offset = 12;
    attrs[1].stream = 0;
    createFetchObj(attrs, 2);
}

DrResFetch::DefVertexFunc DrResFetch::s_callDefVertex[91] = {
    &DrResFetch::setupTexture2D,
    &DrResFetch::setupPositionOnly,
    &DrResFetch::setupSkinWeightCalc,
    &DrResFetch::setupZBuffObj,
    &DrResFetch::setupZBuffObjTex,
    &DrResFetch::setupZBuffMot,
    &DrResFetch::setupZBuffMotTex,
    &DrResFetch::setupZBuffInst,
    &DrResFetch::setupZBuffInstTex,
    &DrResFetch::setupZBuffObjAL,
    &DrResFetch::setupZBuffObjTexAL,
    &DrResFetch::setupZBuffMotAL,
    &DrResFetch::setupZBuffMotTexAL,
    &DrResFetch::setupShadowObj,
    &DrResFetch::setupShadowObjTex,
    &DrResFetch::setupShadowMot,
    &DrResFetch::setupShadowMotTex,
    &DrResFetch::setupShadowMotInst,
    &DrResFetch::setupShadowMotInstTex,
    &DrResFetch::setupMpf_Stm_Bill,
    &DrResFetch::setupMpf_Stm_Bill_Wind,
    &DrResFetch::setupMpf_Stm_Mdl_Wind,
    &DrResFetch::setupMpf_Stm_Mdl_Wind_NoNom,
    &DrResFetch::setupMpf_Stm_Mdl_NormalMap_Wind,
    &DrResFetch::setupMpf_Stm_Mdl_NormalMap_Wind_VNom,
    &DrResFetch::setupMpf_Pre_Bill,
    &DrResFetch::setupMpf_Pre_Bill_Nuki,
    &DrResFetch::setupMpf_Pre_Bill_Nuki_Layer,
    &DrResFetch::setupMpf_Pre_Mdl,
    &DrResFetch::setupMpf_Pre_Mdl_Nuki,
    &DrResFetch::setupMpf_Pre_Mdl_Nuki_Layer,
    &DrResFetch::setupMpf_Pre_Mdl_Def,
    &DrResFetch::setupMpf_Pre_Mdl_Def_Nuki,
    &DrResFetch::setupMpf_Pre_Mdl_Def_Nuki_Layer,
    &DrResFetch::setupMpf_Pre_Dithe_Bill,
    &DrResFetch::setupMpf_Pre_Dithe_Bill_Nuki,
    &DrResFetch::setupMpf_Pre_Dithe_Bill_Nuki_Layer,
    &DrResFetch::setupMpf_Pre_Dithe_Mdl,
    &DrResFetch::setupMpf_Pre_Dithe_Mdl_Nuki,
    &DrResFetch::setupMpf_Pre_Dithe_Mdl_Nuki_Layer,
    &DrResFetch::setupMpf_Pre_Dithe_Mdl_Def,
    &DrResFetch::setupMpf_Pre_Dithe_Mdl_Def_Nuki,
    &DrResFetch::setupMpf_Pre_Dithe_Mdl_Def_Nuki_Layer,
    &DrResFetch::setupMpf_Drw_Bill,
    &DrResFetch::setupMpf_Drw_Bill_Layer,
    &DrResFetch::setupMpf_Drw_Mdl,
    &DrResFetch::setupMpf_Drw_Mdl_Layer,
    &DrResFetch::setupMpf_Drw_Mdl_NoNom,
    &DrResFetch::setupMpf_Drw_Mdl_NoNom_Layer,
    &DrResFetch::setupMpf_Drw_Mdl_Def,
    &DrResFetch::setupMpf_Drw_Mdl_Def_Layer,
    &DrResFetch::setupMpf_Drw_Mdl_Def_NoNom,
    &DrResFetch::setupMpf_Drw_Mdl_Def_NoNom_Layer,
    &DrResFetch::setupMpf_Drw_Mdl_NormalMap,
    &DrResFetch::setupMpf_Drw_Mdl_NormalMap_Wind,
    &DrResFetch::setupMpf_Drw_Mdl_NormalMap_Wind_Layer,
    &DrResFetch::setupMpf_Drw_Mdl_NormalMap_Wind_VNom,
    &DrResFetch::setupMpf_Drw_Mdl_NormalMap_Layer,
    &DrResFetch::setupZBuffInstDith,
    &DrResFetch::setupZBuffInstDithTex,
    &DrResFetch::setupZBuffInstBillDith,
    &DrResFetch::setupZBuffInstBillDithTex,
    &DrResFetch::setupDebugPosColor,
    &DrResFetch::setupXYZW,
    &DrResFetch::setupOutLineObj,
    &DrResFetch::setupGlassBrObj,
    &DrResFetch::setupMofSetObj,
    &DrResFetch::setupMeshVtxObj,
    &DrResFetch::setupOutMeshVtx,
    &DrResFetch::setupMpf_Cull_Fade_Mdl,
    &DrResFetch::setupMpf_Pre_Mdl_Layer,
    &DrResFetch::setupMpf_Pre_Dithe_Mdl_Layer,
    &DrResFetch::setupWeightVtx,
    &DrResFetch::setupShadowFw,
    &DrResFetch::setupDepthCheck,
    &DrResFetch::setupDebTexStm,
    &DrResFetch::setupZBuffFw,
    &DrResFetch::setupZBuffFwAL,
    &DrResFetch::setupMofZBuffObj,
    &DrResFetch::setupMofZBuffObjTex,
    &DrResFetch::setupMofZBuffMot,
    &DrResFetch::setupMofZBuffMotTex,
    &DrResFetch::setupMofZBuffObjAL,
    &DrResFetch::setupMofZBuffObjTexAL,
    &DrResFetch::setupMofZBuffMotAL,
    &DrResFetch::setupMofZBuffMotTexAL,
    &DrResFetch::setupMofShadowObj,
    &DrResFetch::setupMofShadowObjTex,
    &DrResFetch::setupMofShadowMot,
    &DrResFetch::setupMofShadowMotTex,
    &DrResFetch::setupMeshVtxAdd,
};


namespace _drrsm {
const char* c_DeclOfsNames[2] = {"MODE_UMATE_ON", "DECL_DITHER"};
}  // namespace _drrsm

DrResShdMpf::DrResShdMpf(DrShdDataObj* data, int type) {
    m_data = data;
    for (int i = 0; i < 8; i++) {
        m_shaderSel[i] = -1;
    }
    m_flags = 1;
    m_type = type;
    for (int i = 0; i < 2; i++) {
        m_declOfs[i] = m_data->getDeclarationOfs(_drrsm::c_DeclOfsNames[i]);
    }
    m_shaderSel[2] = 1;
    m_shaderSel[0] = 0;
    m_shaderSel[1] = 1;
    m_shaderSel[3] = m_data->getCurrentShader().getUniformBlockOfs("U_MpfWet");
    m_shaderSel[4] = m_data->getCurrentShader().getUniformBlockOfs("U_MpfOld");
    m_shaderSel[5] = 1;
    m_shaderSel[6] = 0;
    m_shaderSel[7] = 2;
    m_flags &= ~1;
}

void DrResShdMpf::setupShader(unsigned int idx) {
    m_data->setDeclarationIdx(m_declOfs[0], 2 - (idx & 1));
    m_data->setDeclarationIdx(m_declOfs[1], 2 - ((idx >> 1) & 1));
    m_data->setupShader((idx >> 1) & 1);
}

void DrResShdShw::shwShdset_DefObj() {
    m_shaderSel[2] = 1;
    m_shaderSel[3] = 2;
    m_shaderSel[1] = 0;
    m_shaderSel[0] = 0;
}

void DrResShdShw::shwShdset_Inst() {
    m_shaderSel[2] = 1;
    m_shaderSel[3] = 2;
    m_shaderSel[1] = 0;
    m_shaderSel[0] = 0;
}

void DrResShdShw::shwShdset_Mot() {
    m_shaderSel[2] = 1;
    m_shaderSel[3] = 2;
    m_shaderSel[1] = 0;
    m_shaderSel[0] = 0;
}

void DrResShdShw::shwShdset_InstMot() {
    m_shaderSel[2] = 1;
    m_shaderSel[3] = 2;
    m_shaderSel[1] = 0;
    m_shaderSel[0] = 0;
}

void DrResShdShw::shwShdset_Fw() {
    m_shaderSel[2] = 1;
    m_shaderSel[3] = 2;
    m_shaderSel[1] = 0;
    m_shaderSel[0] = 0;
    m_shaderSel[4] = 3;
    m_shaderSel[5] = 1;
    m_shaderSel[6] = 2;
}

DrResShdStreamOut::DrResShdStreamOut(DrShdDataObj* data, int type) {
    m_data = data;
    m_shaderSel[0] = -1;
    m_shaderSel[1] = -1;
    m_shaderSel[2] = -1;
    m_type = type;
    m_wetNumOfs = 0;
    (this->*s_callStmOuSet[m_type])();
}


void (DrResShdObjMot::*DrResShdObjMot::s_callMotObjSet[6])() = {
    &DrResShdObjMot::motblur_motObj, &DrResShdObjMot::motblur_motObjTex, &DrResShdObjMot::motblur_motObjTex,
    &DrResShdObjMot::motblur_notObj, &DrResShdObjMot::motblur_notObjTex, &DrResShdObjMot::motblur_notObjTex,
};

DrResShdObjMot::DrResShdObjMot(DrShdDataObj* data, int type) {
    m_data = data;
    for (int i = 0; i < 5; i++) {
        m_shaderSel[i] = -1;
    }
    m_flags = 1;
    m_type = type;
    (this->*s_callMotObjSet[m_type])();
    m_flags &= ~1;
}

void DrResShdObjMot::motblur_motObj() {
    m_shaderSel[0] = 0;
    m_shaderSel[1] = 1;
    m_shaderSel[2] = m_data->getCurrentShader().getUniformBlockOfs("U_VPam");
    m_shaderSel[3] = m_data->getCurrentShader().getUniformBlockOfs("U_VPam");
}

void DrResShdObjMot::motblur_motObjTex() {
    m_shaderSel[0] = 0;
    m_shaderSel[1] = 1;
    m_shaderSel[2] = m_data->getCurrentShader().getUniformBlockOfs("U_VPam");
    m_shaderSel[3] = m_data->getCurrentShader().getUniformBlockOfs("U_VPam");
    m_shaderSel[4] = m_data->getCurrentShader().getTextureLocation("tex");
}

void DrResShdObjMot::motblur_notObj() {
    m_shaderSel[0] = m_data->getCurrentShader().getUniformBlockOfs("U_MDL1");
    m_shaderSel[1] = m_data->getCurrentShader().getUniformBlockOfs("U_MDL2");
    m_shaderSel[2] = m_data->getCurrentShader().getUniformBlockOfs("U_VPam");
    m_shaderSel[3] = m_data->getCurrentShader().getUniformBlockOfs("U_VPam");
}

void DrResShdObjMot::motblur_notObjTex() {
    m_shaderSel[0] = m_data->getCurrentShader().getUniformBlockOfs("U_MDL1");
    m_shaderSel[1] = m_data->getCurrentShader().getUniformBlockOfs("U_MDL2");
    m_shaderSel[2] = m_data->getCurrentShader().getUniformBlockOfs("U_VPam");
    m_shaderSel[3] = m_data->getCurrentShader().getUniformBlockOfs("U_VPam");
    m_shaderSel[4] = m_data->getCurrentShader().getTextureLocation("tex");
}

void DrResEtcParams::setParams(float value) {
    m_flags |= 1 << DrMan::s_nDblStockIdx;
    m_value[DrMan::s_nDblStockIdx] = value;
}

void DrResEtcParams::setPreParams(float value) {
    m_flags |= 4 << DrMan::s_nDblStockIdx;
    m_preValue[DrMan::s_nDblStockIdx] = value;
}

void DrResEtcParams::setInitParams(float value) {
    m_preValue[1] = value;
    m_preValue[0] = value;
    m_value[1] = value;
    m_value[0] = value;
    m_params = value;
}

void DrResMdoMat::setColor(float r, float g, float b, float a) {
    m_color[0] = r;
    m_color[1] = g;
    m_color[2] = b;
    m_alpha = a;
}

void DrResMdoMat::setAlpha(float alpha) {
    m_alpha = alpha;
}

void DrResMdoMat::setName(const char* name) {
    m_name = name;
}

DrResQueryAcc::DrResQueryAcc() : m_query(nullptr) {}

void DrResQueryAcc::releaseQuery() {
    if (m_query != nullptr) {
        m_query->m_user = nullptr;
        m_query = nullptr;
    }
}

int DrResQueryObj::getOccZPassCount() {
    if (m_flags & (4 << DrMan::s_nDblNowIdx)) {
        return m_query.getQueryPixel();
    }
    return 0;
}

DrResQueryObj::DrResQueryObj() : m_work(), m_user(nullptr), m_userWork(nullptr), m_flags(0) {}

DrResQueryObj::~DrResQueryObj() {
    m_query.release();
}

bool DrResQueryObj::update() {
    if (m_user != nullptr) {
        if (m_flags & 2) {
            if (m_flags & 1) {
                m_flags &= ~1;
                return false;
            }
            m_user->m_query = nullptr;
        } else {
            if (m_flags & 1) {
                m_flags &= ~1;
                return false;
            }
            m_flags = 2;
            return false;
        }
    } else if (m_flags & 1) {
        m_flags &= ~3;
        return false;
    }
    m_flags = 0;
    m_user = nullptr;
    m_userWork = nullptr;
    return true;
}

void DrResQueryObj::begin() {
    m_query.beginQuery();
    m_flags |= 4 << DrMan::s_nDblNowIdx;
}

void DrResQueryObj::end() {
    m_query.endQuery();
}

DrResUseQueryObj::DrResUseQueryObj() : m_query(nullptr), m_pixel(0) {}

DrResUseQueryObj::~DrResUseQueryObj() {
    if (m_query != nullptr) {
        m_query->m_user = nullptr;
        m_query = nullptr;
    }
}

void DrResUseQueryObj::update() {
    if (m_query != nullptr) {
        m_pixel = m_query->getOccZPassCount();
    } else {
        m_pixel = 0;
    }
}

void DrResUseQueryObj::end() {
    if (m_query != nullptr) {
        m_query->end();
    }
}

void DrResUseQueryObj::begin(DrPixlOccQuery* occ) {
    DrResQueryObj* query = m_query;
    if (query == nullptr) {
        query = occ->createObj();
        if (query == nullptr) {
            return;
        }
        m_query = query;
        query->m_user = this;
    }
    query->m_flags |= 1;
    query->begin();
}

DrResOccUniformObj::~DrResOccUniformObj() {
    if (m_buf != nullptr) {
        mtl::MemManager::deallocate(m_buf, 0, false);
        m_buf = nullptr;
    }
}

void DrResOccUniformObj::begin() {
    m_cnt = 0;
}

void DrResOccUniformObj::end() {}

mm::Mat44* DrResOccUniformObj::getMatTbl() {
    if (m_max <= m_cnt) {
        return nullptr;
    }
    return &m_matTbl[m_cnt++];
}

mm::Mat44* DrResOccUniformObj::getMatTbl(int idx) {
    return m_matTbl + idx;
}

}  // namespace ml


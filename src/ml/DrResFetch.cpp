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
#include "ml/DrResShdShw.h"
#include "ml/DrResShdStreamOut.h"
#include "ml/DrShdDataObj.h"

namespace ml {

DrResMdoInstPartsAnm::~DrResMdoInstPartsAnm() {}

DrResMdoInstPartsGlbID::~DrResMdoInstPartsGlbID() {}

DrResMdoSeamColi::~DrResMdoSeamColi() {}

void DrShdLgtClustered::update() {}

void DrShdLgtClustered::delViewInfo(int) {}

void DrShdLgtClustered::debugRender() {}

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

void DrShdLgtClustered::setPntLightUniformBlock(unsigned int idx, unsigned int location) {
    m_viewWork[idx].pntLight.setUniformBlock(location);
}

void DrShdLgtClustered::setSptLightUniformBlock(unsigned int idx, unsigned int location) {
    m_viewWork[idx].sptLight.setUniformBlock(location);
}

void DrShdLgtClustered::setPointerListUniformBlock(unsigned int idx, unsigned int location) {
    m_viewWork[idx].pointerList.setUniformBlock(location);
}

void DrShdLgtClustered::setLightListUniformBlock(unsigned int, unsigned int) {}

void DrShdLgtClustered::setParamUniformBlock(unsigned int idx, unsigned int location) {
    m_viewWork[idx].param.setUniformBlock(location);
}

void DrShdLgtClustered::setPntLightStorageBuffer(unsigned int idx, unsigned int location) {
    m_viewWork[idx].pntLight.setStorageBuffer(location);
}

void DrShdLgtClustered::setSptLightStorageBuffer(unsigned int idx, unsigned int location) {
    m_viewWork[idx].sptLight.setStorageBuffer(location);
}

void DrShdLgtClustered::setPointerListStorageBuffer(unsigned int idx, unsigned int location) {
    m_viewWork[idx].pointerList.setStorageBuffer(location);
}

void DrShdLgtClustered::setLightListStorageBuffer(unsigned int idx, unsigned int location) {
    m_viewWork[idx].lightList.setStorageBuffer(location);
}

void DrShdLgtClustered::setParamStorageBuffer(unsigned int idx, unsigned int location) {
    m_viewWork[idx].param.setStorageBuffer(location);
}

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

}  // namespace ml

namespace navi {

NvmshAcObjBaseGbl::~NvmshAcObjBaseGbl() {}

}  // namespace navi


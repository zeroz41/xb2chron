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
#include "classes/ml/DrMdlBase.h"
#include "classes/cloud/CloudMan.h"
#include "classes/ml/DrShdLgtClustered.h"
#include "classes/navi/NvmshAcObjBaseGbl.h"
#include "ml/DrResEtcParams.h"
#include "ml/DrResMdoMat.h"
#include "ml/DrResQueryObj.h"
#include "ml/DrPixlOccQuery.h"
#include "ml/DrResOccUniformObj.h"
#include "ml/DrResEtcUniformObj.h"
#include "ml/DrResClip.h"
#include "ml/DrResMpfSampler.h"
#include "ml/DrResEtcTexList.h"
#include "classes/ml/DrGpuCheckObj.h"
#include "ml/DrGpuCheckRender.h"
#include "ml/DrMdlMan.h"
#include "ml/DrMdoVertexMan.h"
#include "ml/ScnObjAccGpuCheck.h"
#include "ml/DrShdDataList.h"
#include "ml/DrShdDataObj.h"
#include "grlib/CGLibCtl.h"
#include "grlib/CGLibUniformArray.h"
#include "grlib/CGLibVtxInstans.h"
#include "ml/DrPixlMan.h"
#include "ml/DrCalcMan.h"
#include "ml/DrCalcClipMan.h"
#include "ml/DrLightMan.h"
#include "classes/ml/DrLightObjPnt.h"
#include "classes/ml/DrLightObjSpt.h"
#include <new>
#include "classes/ml/DrStmReadCheck.h"
#include "ml/DrResMdoVertex.h"
#include "grlib/CGLibVtxVertex.h"
#include "grlib/CGLibVtxIndex.h"
#include "classes/ml/DrResMdoSeamRead.h"
#include "classes/ml/DevFileTh.h"
#include "ml/DevFileParamTh.h"
#include "ml/EventFileTh.h"
#include "classes/ml/DrResMdoSeamTexture.h"
#include "classes/ml/DrResMdoSeamVertex.h"
#include "classes/ml/DrResMdoSeamTexList.h"
#include "classes/ml/DrResMdoSeamMemObj.h"
#include "grlib/CGLibTexture.h"
#include "grlib/CGLibTextureBuffer.h"
#include "classes/ml/DrResMdoSeamWrkLight.h"
#include "classes/ml/DrEnvironmentObj.h"
#include "ml/DrEnvironmentMan.h"
#include "classes/ml/DrMan.h"
#include "ml/DrResMdoSeamMemMan.h"
#include "classes/ml/DrResMdoSeamWrkLow.h"
#include "classes/ml/DrResMdoSeamWrkInst.h"
#include "classes/ml/DrResMdoSeamWrkBase.h"
#include "ml/DrResMdoSeamWrkPosInst.h"
#include "ml/DrMdoCtlSeamInstMap.h"
#include "ml/DrPixlShadowCacheMan.h"
#include "classes/ml/DrCalcStmListObj.h"
#include "classes/ml/DrCalcTexStreamMan.h"
#include "ml/MdoWrkVanishEffect.h"
#include "ml/MdsMatVertexInfo.h"
#include "ml/MdsMpfMatInfoHeader.h"
#include "ml/DrCalcViewWork.h"
#include "mm/Math.h"
#include "mtl/MemManager.h"
#include "ml/DrResFetch.h"
#include "ml/DrResMdoLight.h"
#include "ml/DrResMdoPosInstAnm.h"
#include "ml/DrResMdoUniformBlock.h"
#include "ml/DrResEtcPamObj.h"
#include "ml/DrResMdoLodObj.h"
#include "ml/DrResMdoAlpTbl.h"
#include "ml/DrResMdoSeamWrkPosMpf.h"
#include "ml/DrResMdoMeshObj.h"
#include "ml/DrResMdoShdObj.h"
#include "ml/DrResMdoMorpObj.h"
#include "classes/ml/DrMan.h"
#include "classes/ml/DrResMdoInstPartsObj.h"
#include "ml/DrResShdPrePass.h"
#include "ml/DrResShdShw.h"
#include "ml/DrResShdStreamOut.h"
#include "ml/DrResShdObjMot.h"
#include "ml/DrResShdMpf.h"
#include "ml/DrShdDataObj.h"
#include "ml/DrResMdoPos.h"
#include "ml/DrResMdoSeamParmRead.h"
#include "classes/ml/DrResMdoSeamWrkEnv.h"
#include "ml/MdoWrkMatRes.h"
#include <string.h>
#include "ml/DrResMdoInstAnmObj.h"
#include "ml/DrPixlToonGrad.h"
#include "ml/DrPixlRenderTarget.h"
#include "ml/DrResWrkClipList.h"
#include "ml/DrResMdoSampler.h"
#include "grlib/CGLibSampler.h"
#include "ml/DrResFilterData.h"
#include "ml/DrResMdoTexSimple.h"
#include "classes/ml/DrResMdoSeamWrkMpf.h"
#include "ml/DrMdoCtlMpfAuto.h"
#include "ml/DrMdoCtlSeamMpfMap.h"
#include "ml/DrMdoCtlMpfWork.h"
#include "ml/DrMdoCtlMpfInst.h"
#include "ml/DrResMdoInstMdlInfo.h"
#include "ml/DrResMdoVtxMeshObj.h"
#include "ml/DrResMdoTexList.h"
#include "ml/DrResMdoPntAlphaMan.h"
#include "ml/DrMdoMorphing.h"
#include "ml/DrShdMan.h"
#include "classes/ml/DrAPCache.h"

namespace ml {

DrResMdoInstPartsAnm::~DrResMdoInstPartsAnm() {}

DrResMdoInstPartsGlbID::~DrResMdoInstPartsGlbID() {}

DrResMdoSeamColi::~DrResMdoSeamColi() {}

unsigned int DrResMdoLodObj::calcWorkSize(const unsigned char* data) {
    const MdoHeader* header = reinterpret_cast<const MdoHeader*>(data);
    const MdoLod* lod = (header->m_flags & MdoHeader::FLAG_LOD) ? reinterpret_cast<const MdoLod*>(data + header->m_lodOfs) : nullptr;
    int grpNum = 1;
    int partsNum = 1;
    if (lod != nullptr) {
        grpNum = lod->m_grpNum + 1;
        partsNum = lod->m_partsNum + 1;
    }
    return sizeof(DrResMdoLodObj) + grpNum * 0x20 + partsNum * 0x20;
}

unsigned int DrResMdoAlpTbl::calcWorkSize(const unsigned char* data) {
    const MdoHeader* header = reinterpret_cast<const MdoHeader*>(data);
    if (!(header->m_flags & MdoHeader::FLAG_ALPTBL)) {
        return 0;
    }
    const AlpHeader* alp = reinterpret_cast<const AlpHeader*>(data + header->m_alpOfs);
    int num = alp->m_num;
    int pad = (4 - num % 4) % 4;
    int bitNum = num / 32 + (num % 32 != 0 ? 1 : 0);
    return sizeof(DrResMdoAlpTbl) + (num + bitNum + pad) * 4;
}

unsigned int DrResMdoAlpTbl::create(unsigned char* work, const unsigned char* data) {
    DrResMdoAlpTbl* obj = new (work) DrResMdoAlpTbl;
    const MdoHeader* header = reinterpret_cast<const MdoHeader*>(data);
    if (!(header->m_flags & MdoHeader::FLAG_ALPTBL)) {
        return 0;
    }
    float* alpha = reinterpret_cast<float*>(work + sizeof(DrResMdoAlpTbl));
    obj->m_alpha = alpha;
    const AlpHeader* alp = reinterpret_cast<const AlpHeader*>(data + header->m_alpOfs);
    obj->m_data = reinterpret_cast<const unsigned char*>(alp) + alp->m_dataOfs;
    obj->m_num = alp->m_num;
    int num = alp->m_num;
    unsigned int alphaNum = (4 - num % 4) % 4 + num;
    obj->m_inst.createInstansBuffer(alphaNum * 8);
    for (unsigned int i = 0; i < obj->m_num; i++) {
        obj->m_alpha[i] = 1.0f;
    }
    unsigned int bitNum = obj->m_num / 32 + ((obj->m_num & 0x1F) != 0 ? 1 : 0);
    obj->m_bits = reinterpret_cast<unsigned int*>(alpha + alphaNum);
    memset(obj->m_bits, 0, bitNum * sizeof(unsigned int));
    return alphaNum * sizeof(float) + bitNum * sizeof(unsigned int) + sizeof(DrResMdoAlpTbl);
}

void DrResMdoAlpTbl::release(DrResMdoAlpTbl*& obj) {
    DrResMdoAlpTbl* p = obj;
    if (p != nullptr) {
        p->m_inst.release();
        p->~DrResMdoAlpTbl();
        obj = nullptr;
    }
}

unsigned int DrResMdoLodObj::create(unsigned char* work, const unsigned char* data) {
    return reinterpret_cast<DrResMdoLodObj*>(work)->setup(data, work + sizeof(DrResMdoLodObj));
}

void DrResMdoLodObj::release(DrResMdoLodObj*& obj) {
    if (obj != nullptr) {
        obj = nullptr;
    }
}

void DrResEtcPamObj::mdonode_etcpam_etcmesh_disp(const MdsEtcParamsCallBack* cb, DrResEtcParams* params, wrkCallbackArg& arg) {
    float value = params->getParams();
    DrResMdoMeshParts* parts = arg.m_mesh->m_parts + cb->m_meshNo;
    float alpha = !(value <= 0.5f) ? 1.0f : 0.0f;
    parts->m_alpha[0] = parts->m_alpha[1] = parts->m_alpha[2] = alpha;
    parts->m_flags &= ~6;
}

void DrResEtcPamObj::mdonode_etcpam_volfadeanm(const MdsEtcParamsCallBack* cb, DrResEtcParams* params, wrkCallbackArg& arg) {
    if (m_flags & 1) {
        unsigned int idx = arg.m_mesh->m_parts[cb->m_meshNo].m_vanishNo * 3 + 2;
        float value = params->getParams();
        if (value <= 0.01f) {
            arg.m_vanishEffect[idx].m_alpha = arg.m_vanishEffect[idx].m_baseAlpha;
        } else if (value > 1.0f) {
            arg.m_vanishEffect[idx].m_alpha = arg.m_vanishEffect[idx].m_baseAlpha + 1.0f;
        } else {
            arg.m_vanishEffect[idx].m_alpha = value + arg.m_vanishEffect[idx].m_baseAlpha;
        }
        float& alpha = arg.m_vanishEffect[idx].m_alpha;
        if (alpha > 1.0f) {
            alpha = 1.0f;
        } else if (alpha < 0.0f) {
            alpha = 0.0f;
        }
    }
}

DrResEtcPamObj::NodeFunc DrResEtcPamObj::s_pMdoNodeEtcParm[2] = {
    &DrResEtcPamObj::mdonode_etcpam_etcmesh_disp,
    &DrResEtcPamObj::mdonode_etcpam_volfadeanm,
};

void DrResEtcPamObj::update() {
    for (unsigned int i = 0; i < m_paramNum; i++) {
        DrResEtcParams& params = m_params[i];
        if (params.m_flags & (1 << DrMan::s_nDblMemIdx)) {
            params.m_flags &= ~(1 << DrMan::s_nDblMemIdx);
            params.m_params = params.m_value[DrMan::s_nDblMemIdx];
        }
        if ((4 << DrMan::s_nDblMemIdx) & params.m_flags) {
            params.m_flags &= ~(4 << DrMan::s_nDblMemIdx);
            params.m_params = params.m_preValue[DrMan::s_nDblMemIdx];
        }
    }
}

unsigned int DrResEtcPamObj::calcWorkSize(const unsigned char* mdo) {
    const MdoHeader* header = reinterpret_cast<const MdoHeader*>(mdo);
    const MdoEtcPams* pams = reinterpret_cast<const MdoEtcPams*>(mdo + header->m_etcPamOfs);
    return pams->m_num * 0x18 + 0x20;
}

void DrResEtcPamObj::release(DrResEtcPamObj*& obj) {
    if (obj != nullptr) {
        obj = nullptr;
    }
}

void DrResMdoMeshParts::setDefAlpha(float alpha) {
    m_alpha[DrMan::s_nDblStockIdx] = alpha;
    m_flags |= 2 << DrMan::s_nDblStockIdx;
    m_alpha[DrMan::s_nDblIdx] = alpha;
}

int DrResMdoMeshObj::getIdx(const char* name) const {
    for (unsigned int i = 0; i < m_num; i++) {
        if (strcmp(m_parts[i].m_name, name) == 0) {
            return i;
        }
    }
    return -1;
}

DrResMdoMeshObj& DrResMdoMeshObj::operator=(const DrResMdoMeshObj& other) {
    for (unsigned int i = 0; i < m_num; i++) {
        DrResMdoMeshParts* dst = m_parts;
        const DrResMdoMeshParts* src = other.m_parts;
        if (dst[i].m_flags & DrResMdoMeshParts::FLAG_WORK) {
            memcpy(dst[i].m_work, src[i].m_work, 0x40);
        }
        dst[i].m_alpha[0] = src[i].m_alpha[0];
        dst[i].m_alpha[1] = src[i].m_alpha[1];
        dst[i].m_alpha[2] = src[i].m_alpha[2];
        dst[i].m_flags = src[i].m_flags;
        dst[i].m_vanishNo = src[i].m_vanishNo;
    }
    return *this;
}

void DrResMdoMeshObj::release(DrResMdoMeshObj*& obj) {
    if (obj != nullptr) {
        obj = nullptr;
    }
}

int DrResMdoShdObj::getDecShdIdx(const char* name) const {
    for (unsigned int i = 0; i < m_num; i++) {
        if (strcmp(reinterpret_cast<const char*>(m_header) + m_entries[i].m_data->m_nameOfs, name) == 0) {
            return i;
        }
    }
    return -1;
}

void DrResMdoShdObj::setDecShdParm(unsigned int idx, unsigned int parm) {
    if (idx < m_num) {
        m_entries[idx].m_decShdParm = parm;
    }
}

unsigned int DrResMdoShdObj::calcWorkSize(const unsigned char* mdo) {
    const ShdHeader* header =
        reinterpret_cast<const ShdHeader*>(mdo + reinterpret_cast<const MdoHeader*>(mdo)->m_shdOfs);
    const ShdData* data =
        reinterpret_cast<const ShdData*>(reinterpret_cast<const unsigned char*>(header) + header->m_dataOfs);
    unsigned int size = 0;
    for (int i = 0; i < header->m_num; i++, data++) {
        size += data->m_workNum;
    }
    size += -size & 3;
    return size + header->m_num * sizeof(Entry) + sizeof(DrResMdoShdObj);
}

void DrResMdoMorpObj::update(MdoWrkMatRes* wrkMatRes, DrResEtcPamObj* pamObj) {
    DrMdoMorphing morphing(wrkMatRes, this, pamObj);
    morphing.updateParms();
    int blend = morphing.isBlendCheck();
    if (blend != 0) {
        morphing.resetDefVertex();
        if (blend != 1) {
            morphing.blendVertex();
        }
        m_blended = true;
        morphing.parmsUpdate();
    } else if (m_blended) {
        if (m_oldPos) {
            morphing.oldPosVertex();
        }
        m_blended = false;
    }
}

unsigned int DrResMdoMorpObj::calcWorkSize(const unsigned char* mdo) {
    const MdoHeader* header = reinterpret_cast<const MdoHeader*>(mdo);
    const MdoMorphs* morphs = reinterpret_cast<const MdoMorphs*>(mdo + header->m_morphOfs);
    return morphs->m_num * sizeof(Target) + sizeof(DrResMdoMorpObj);
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

void DrResMdoSortCloud::alphaRender() {
    cloud::CloudMan* cloudMan = static_cast<cloud::CloudMan*>(m_owner);
    DrMan* man = DrMan::getIns();
    cloudMan->alphaRender(&man->m_drawWorkInfo[man->m_postParmIdx]);
}

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


DrResMdoSeamWrkMpf::DrResMdoSeamWrkMpf()
    : m_memObj(nullptr), m_dataIdx(0), m_dispNum(0), m_readCnt(0),
      m_poliNum(0), m_cacheFlags(0), m_renderNum(), m_matRes(nullptr), m_workBuf(nullptr), m_mpfWork(nullptr),
      m_mpfAuto(nullptr), m_mpfInst(nullptr), m_etcWork(nullptr), m_readSize(0) {}

DrResMdoSeamWrkMpf::~DrResMdoSeamWrkMpf() {
    if (m_matRes != nullptr) {
        m_mpfAuto->autoMpfRelease();
        m_mpfAuto->~DrMdoCtlMpfAuto();
        m_mpfAuto = nullptr;
        m_mpfInst = nullptr;
        m_mpfWork = nullptr;
        if (m_matRes != nullptr) {
            mtl::MemManager::deallocate(m_matRes, 0, false);
            m_matRes = nullptr;
        }
        if (m_workBuf != nullptr) {
            mtl::MemManager::deallocate(m_workBuf, 0, false);
            m_workBuf = nullptr;
        }
    }
    m_memObj = nullptr;
    m_dispNum = 0;
}

void DrResMdoSeamWrkMpf::releaseCache(DrMdoCtlSeamMpfMap* ctl) {
    for (int i = 0; i < m_etcNum; i++) {
        if ((m_etcBits[i >> 5] & (1 << (i & 0x1F))) && m_etcWork[i].m_work != nullptr) {
            ctl->releaseFreeSeamMemObj(static_cast<DrResMdoSeamMemObj*>(m_etcWork[i].m_work));
            m_etcWork[i].m_work = nullptr;
        }
    }
    for (int i = 0; i < m_poliNum; i++) {
        ctl->releaseFreeSeamMemObj(m_poliMemTbl[i]);
    }
    m_poliNum = 0;
    if (m_matRes != nullptr) {
        m_mpfAuto->autoMpfRelease();
        m_mpfAuto->~DrMdoCtlMpfAuto();
        m_mpfAuto = nullptr;
        m_mpfInst = nullptr;
        m_mpfWork = nullptr;
        if (m_matRes != nullptr) {
            mtl::MemManager::deallocate(m_matRes, 0, false);
            m_matRes = nullptr;
        }
        if (m_workBuf != nullptr) {
            mtl::MemManager::deallocate(m_workBuf, 0, false);
            m_workBuf = nullptr;
        }
    }
    m_memObj = nullptr;
    m_dispNum = 0;
}

void DrResMdoSeamWrkMpf::setEtcMpfCache(int id, DrResMdoSeamMemObj* mem) {
    const EtcEntry* entry = m_etcEntry;
    for (int i = 0; i < m_etcNum; i++, entry++) {
        if (entry->m_id == id) {
            m_etcBits[i >> 5] |= 1 << (i & 0x1F);
            DrResMdoSeamWrkPosMpf* work = &m_etcWork[i];
            work->m_work = mem;
            work->m_workNum = i;
            const unsigned char* data = mem->m_pData;
            const EtcData* head = reinterpret_cast<const EtcData*>(data);
            work->m_data = data;
            work->m_pos = data + head->m_posOfs;
            work->m_info = data + head->m_infoOfs;
            work->m_posNum = head->m_posNum;
            m_etcWorkTbl[m_dispNum] = &m_etcWork[i];
            m_dispNum++;
            return;
        }
    }
}

void DrResMdoSeamWrkMpf::setMpfPoliCache(int id, DrResMdoSeamMemObj* mem) {
    const unsigned char* data = reinterpret_cast<const unsigned char*>(m_mpfAuto->m_pHeader);
    const PoliHead* head = reinterpret_cast<const PoliHead*>(data + m_mpfAuto->m_pHeader->m_poliOfs);
    const PoliEntry* entry = reinterpret_cast<const PoliEntry*>(reinterpret_cast<const unsigned char*>(head) + head->m_entryOfs);
    for (int i = 0; i < head->m_entryNum; i++, entry++) {
        if (entry->m_id == id) {
            m_poliBits[i >> 5] |= 1 << (i & 0x1F);
            m_poliMemTbl[m_poliNum] = mem;
            m_poliIdx[m_poliNum] = i;
            setupMpfPoliWork(m_poliNum);
            m_poliNum++;
            return;
        }
    }
}

void DrResMdoSeamWrkMpf::setupMpfPoliWork(int idx) {
    _wkMpfAutoBuff* buff = m_buffTbl[idx];
    const unsigned char* data = m_poliMemTbl[idx]->m_pData;
    const PoliData* head = reinterpret_cast<const PoliData*>(data);
    buff->m_max[0] = head->m_max[0];
    buff->m_min[0] = head->m_min[0];
    buff->m_max[1] = head->m_max[1];
    buff->m_min[1] = head->m_min[1];
    buff->m_pPoli = reinterpret_cast<const MdsMpfAutoPoli*>(data + head->m_poliOfs);
    buff->m_pTbl[0] = data + head->m_tblOfs[0];
    buff->m_pTbl[1] = data + head->m_tblOfs[1];
    buff->m_pTbl[2] = data + head->m_tblOfs[2];
    buff->m_pTbl[3] = data + head->m_tblOfs[3];
    if (head->m_treeOfs != 0) {
        buff->m_pTree = reinterpret_cast<const MdsMpfAutoTree*>(data + head->m_treeOfs);
    } else {
        buff->m_pTree = nullptr;
    }
    buff->m_pPoliList = reinterpret_cast<const unsigned int*>(data + head->m_poliListOfs);
    buff->m_pCell = reinterpret_cast<const unsigned int*>(data + head->m_cellOfs);
    buff->m_pGrid = reinterpret_cast<const float(*)[2]>(data + head->m_gridOfs);
    if (head->m_instOfs != 0) {
        buff->m_pInstData = reinterpret_cast<const _wkMpfAutoBuff::Inst*>(data + head->m_instOfs);
        buff->m_pPosTree = reinterpret_cast<const MdsMpfAutoPosTree*>(data + head->m_posTreeOfs);
        buff->m_pIdxTbl = reinterpret_cast<const unsigned int*>(data + head->m_idxTblOfs);
    } else {
        buff->m_pInstData = nullptr;
    }
}

inline void DrResMdoTexList::releaseTexInfo() {
    if (m_texNum != 0) {
        for (int i = 0; i < m_texNum; i++) {
            m_texBuf[i].~CGLibTextureBuffer();
        }
        m_texBuf = nullptr;
        m_texNum = 0;
    }
    if (m_texAlloc != nullptr) {
        mtl::MemManager::deallocate(m_texAlloc, 0, false);
        m_texAlloc = nullptr;
    }
}

int DrResWrkClipList::calcWorkSize(const unsigned char* data, unsigned int ofs) {
    const ListHead* head = reinterpret_cast<const ListHead*>(data + ofs);
    int size = (head->m_num / 32) * 4 + 4;
    return size + (0x20 - size % 0x20) % 0x20;
}

int DrResWrkClipList::setupWork(unsigned char* work, const unsigned char* data, unsigned int ofs) {
    const ListHead* head = reinterpret_cast<const ListHead*>(data + ofs);
    m_data = data;
    m_num = head->m_num;
    m_list = data + head->m_ofs;
    m_work = reinterpret_cast<unsigned int*>(work);
    int size = (m_num / 32) * 4 + 4;
    m_workSize = size + (0x20 - size % 0x20) % 0x20;
    return m_workSize;
}

void DrResWrkClipList::changeMemCall(const unsigned char* data, unsigned int ofs) {
    m_data = data;
    m_list = data + reinterpret_cast<const ListHead*>(data + ofs)->m_ofs;
}

void DrResMdoSeamWrkPosMpf::setupMpfBasePos(const unsigned char* data) {
    const MpfHeader* header = reinterpret_cast<const MpfHeader*>(data);
    m_data = data;
    m_work = nullptr;
    m_workNum = 0;
    m_pos = data + header->m_posOfs;
    m_info = data + header->m_infoOfs;
    m_posNum = header->m_posNum;
}

DrResMdoTexList::DrResMdoTexList(const unsigned char* data)
    : m_pPrev(nullptr), m_pNext(nullptr), m_res(data), m_refCount(1), m_texBuf(nullptr), m_stmList(nullptr),
      m_texAlloc(nullptr), m_texNum(0), m_flags(0), m_stmState(0), m_data(data), m_mem(data), pad_90(nullptr),
      pad_98(nullptr) {
    createTexInfoList();
    createTexList(m_data, m_mem);
}

void DrResMdoTexList::createTexInfoList() {
    releaseTexInfo();
    m_pool.release();
    m_flags = 0;
    m_stmState = 0;
    m_texNum = calcTextureMax(m_data);
    unsigned int size = calcTextureMax(m_data) * 0x70;
    m_texAlloc = mtl::MemManager::allocate(DrMan::get()->m_allocHandle, size, 0x10, false, "no name", 0);
    m_texBuf = static_cast<grlib::CGLibTextureBuffer*>(m_texAlloc);
    for (int i = 0; i < m_texNum; i++) {
        new (&m_texBuf[i]) grlib::CGLibTextureBuffer();
    }
}

void DrResMdoTexList::createTexList(const unsigned char* data, const unsigned char* mem) {
    m_flags |= FLAG_CREATED;
    const MdsTexInfo* info = reinterpret_cast<const MdsTexInfo*>(data + reinterpret_cast<const MdsTexHeader*>(data)->m_infoOfs);
    if (!(m_flags & FLAG_MEM)) {
        m_flags |= FLAG_MEM;
        const MdsTexInfo* last = (info + m_texNum) - 1;
        int size = last->m_ofs - info[0].m_ofs + last->m_size;
        size += -size & 0xFFF;
        m_pool.setupBuffer(const_cast<unsigned char*>(mem) + info[0].m_ofs, size);
    }
    int base = info[0].m_ofs;
    for (int i = 0; i < m_texNum; i++) {
        grlib::CGLibTexture::createTextureImagePtrs(m_texBuf[i], info[i].m_size, m_pool, info[i].m_ofs - base, false,
                                                    nullptr, true);
    }
}

DrResMdoTexList::DrResMdoTexList(const unsigned char* data, DrCalcStmListObj* stm, const unsigned char* mem,
                                 const MdsTexHeader* stmTex)
    : m_pPrev(nullptr), m_pNext(nullptr), m_res(data), m_refCount(1), m_texBuf(nullptr), m_stmList(stm),
      m_texAlloc(nullptr), m_texNum(0), m_flags(0), m_stmState(0), m_data(data), m_mem(mem), pad_90(nullptr),
      pad_98(nullptr) {
    createStmTexInfoList(stm, reinterpret_cast<const unsigned char*>(stmTex), true);
    createTexList(m_data, m_mem);
}

void DrResMdoTexList::createStmTexInfoList(DrCalcStmListObj* stm, const unsigned char* stmTex, bool byName) {
    releaseTexInfo();
    m_pool.release();
    m_flags = 0;
    m_stmState = 0;
    unsigned int num = calcTextureMax(m_data);
    m_texNum = num;
    unsigned long texSize = calcTextureMax(m_data) * 0x70;
    unsigned int size = texSize + num * 2;
    if (num & 1) {
        size += 2;
    }
    m_texAlloc = mtl::MemManager::allocate(DrMan::get()->m_allocHandle, size, 0x10, false, "no name", 0);
    m_texBuf = static_cast<grlib::CGLibTextureBuffer*>(m_texAlloc);
    for (int i = 0; i < m_texNum; i++) {
        new (&m_texBuf[i]) grlib::CGLibTextureBuffer();
    }
    m_flags |= FLAG_STM;
    m_stmIdx = reinterpret_cast<unsigned short*>(static_cast<unsigned char*>(m_texAlloc) + texSize);
    m_stmList = stm;
    if (byName) {
        const MdsTexHeader* header = reinterpret_cast<const MdsTexHeader*>(stmTex);
        const MdsTexInfo* stmInfo = reinterpret_cast<const MdsTexInfo*>(stmTex + header->m_infoOfs);
        const MdsTexHeader* texHeader = getHeader();
        for (int i = 0; i < m_texNum; i++) {
            const MdsTexInfo* info = reinterpret_cast<const MdsTexInfo*>(m_data + texHeader->m_infoOfs);
            const char* name = reinterpret_cast<const char*>(m_data + info[i].m_nameOfs);
            m_stmIdx[i] = 0;
            for (int j = 0; j < header->m_num; j++) {
                if (strcmp(name, reinterpret_cast<const char*>(stmTex + stmInfo[j].m_nameOfs)) == 0) {
                    m_stmIdx[i] = j + 1;
                    break;
                }
            }
        }
    } else {
        for (int i = 0; i < m_texNum; i++) {
            m_stmIdx[i] = 0;
        }
        const unsigned short* idx = reinterpret_cast<const unsigned short*>(stmTex);
        for (int j = 0; j < m_stmList->m_texNum; j++) {
            m_stmIdx[idx[j]] = j + 1;
        }
    }
}

DrResMdoTexList::DrResMdoTexList(const unsigned char* data, DrCalcStmListObj* stm, const unsigned char* mem,
                                 const unsigned short* stmIdx)
    : m_pPrev(nullptr), m_pNext(nullptr), m_res(data), m_refCount(1), m_texBuf(nullptr), m_stmList(stm),
      m_texAlloc(nullptr), m_texNum(0), m_flags(0), m_stmState(0), m_data(data), m_mem(mem), pad_90(nullptr),
      pad_98(nullptr) {
    createStmTexInfoList(stm, reinterpret_cast<const unsigned char*>(stmIdx), false);
    createTexList(m_data, m_mem);
}

DrResMdoTexList::~DrResMdoTexList() {
    releaseTexInfo();
    m_pool.release();
    m_flags = 0;
}

void DrResMdoTexList::update() {
    texStmUpdate();
    m_flags &= ~(FLAG_STM_READ | FLAG_STM_READ_ALL);
}

void DrResMdoTexList::callStmRead(int mode) {
    if (mode != 0) {
        m_flags |= FLAG_STM_READ;
        if (mode == 2) {
            m_flags |= FLAG_STM_READ_ALL;
        }
    }
}

grlib::CGLibTextureBuffer* DrResMdoTexList::getTexObj(unsigned int idx) {
    return &m_texBuf[idx];
}

grlib::CGLibTextureBuffer* DrResMdoTexList::getStmTexObj(unsigned int idx) {
    if (m_stmIdx[idx] != 0) {
        return m_stmList->getTexObj(m_stmIdx[idx] - 1);
    }
    return getTexObj(idx);
}

void DrResMdoTexList::changeMemTexList(const unsigned char* mem) {
    m_data = mem;
    m_mem = mem;
    const MdsTexInfo* info = getInfo();
    int base = info[0].m_ofs;
    m_flags |= FLAG_MEM;
    const MdsTexInfo* last = (info + m_texNum) - 1;
    int size = last->m_ofs - info[0].m_ofs + last->m_size;
    size += -size & 0xFFF;
    m_pool.setupBuffer(const_cast<unsigned char*>(m_mem) + info[0].m_ofs, size);
    for (int i = 0; i < m_texNum; i++) {
        grlib::CGLibTexture::changeTextureImagePtrs(m_texBuf[i], info[i].m_size, m_pool, info[i].m_ofs - base);
    }
}

unsigned int DrResMdoTexList::calcTextureMax(const unsigned char* data) {
    return *reinterpret_cast<const unsigned int*>(data);
}

DrResMdoTexSimple::~DrResMdoTexSimple() {
    m_tex.release();
    m_flags &= ~FLAG_CLEAR_MASK;
}

void DrResMdoTexSimple::createTex() {
    grlib::CGLibTexture::createTextureImagePtrs(m_tex, m_image, m_imageSize, false, nullptr, false);
    m_flags |= FLAG_CREATED;
}

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

int DrResMdoUniformBlock::getValWork(int type, int num) {
    int size = s_nVarSizeTbl[type];
    if (num == 0) {
        num = 1;
    }
    return size * num * 4;
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

int DrResMdoPntAlphaMan::getWrkSize(int num) { return num * 0x18 + 0x18; }

void DrResMdoPntAlphaMan::update(float delta) {
    int num = 0;
    for (int i = 0; i < m_activeNum; i++) {
        m_active[num] = m_active[i];
        Entry* entry = m_active[i];
        if (entry->m_touched) {
            entry->m_flags &= ~FLAG_TOUCHED;
            if (entry->m_flags & FLAG_FADEIN) {
                entry->m_alpha += delta * 0.1f;
                if (entry->m_alpha > 1.0f) {
                    entry->m_alpha = 1.0f;
                }
            } else {
                entry->m_alpha -= delta * 0.1f;
                if (entry->m_alpha < 0.0f) {
                    entry->m_alpha = 0.0f;
                }
            }
            num++;
        } else {
            entry->m_flags = 0;
            entry->m_alpha = 1.0f;
        }
    }
    m_activeNum = num;
}

float DrResMdoPntAlphaMan::getAlphaObj(const void* obj, bool fadeIn) {
    for (int i = 0; i < m_activeNum; i++) {
        Entry* entry = m_active[i];
        if (entry->m_obj == obj) {
            entry->m_flags |= FLAG_TOUCHED;
            if (fadeIn) {
                entry->m_flags |= FLAG_FADEIN;
            } else {
                entry->m_flags &= ~FLAG_FADEIN;
            }
            return entry->m_alpha;
        }
    }
    for (int i = 0; i < m_entryNum; i++) {
        if (!m_entry[i].m_used) {
            m_active[m_activeNum] = &m_entry[i];
            Entry* claimed = m_active[m_activeNum];
            claimed->m_obj = obj;
            claimed->m_flags = FLAG_USED;
            Entry* entry = m_active[m_activeNum++];
            entry->m_flags |= FLAG_TOUCHED;
            if (fadeIn) {
                entry->m_flags |= FLAG_FADEIN;
            } else {
                entry->m_flags &= ~FLAG_FADEIN;
            }
            return entry->m_alpha;
        }
    }
    return 1.0f;
}

void DrResMdoPntAlphaMan::setAlphaReset(const void* obj, bool fadeIn) {
    for (int i = 0; i < m_activeNum; i++) {
        Entry* entry = m_active[i];
        if (entry->m_obj == obj) {
            entry->m_flags |= FLAG_TOUCHED;
            if (fadeIn) {
                entry->m_flags |= FLAG_FADEIN;
            } else {
                entry->m_flags &= ~FLAG_FADEIN;
            }
            entry->m_alpha = fadeIn ? 1.0f : 0.0f;
            return;
        }
    }
    for (int i = 0; i < m_entryNum; i++) {
        if (!m_entry[i].m_used) {
            m_active[m_activeNum] = &m_entry[i];
            Entry* claimed = m_active[m_activeNum];
            claimed->m_obj = obj;
            claimed->m_flags = FLAG_USED;
            Entry* entry = m_active[m_activeNum++];
            entry->m_flags |= FLAG_TOUCHED;
            if (fadeIn) {
                entry->m_flags |= FLAG_FADEIN;
            } else {
                entry->m_flags &= ~FLAG_FADEIN;
            }
            entry->m_alpha = fadeIn ? 1.0f : 0.0f;
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

void DrResMdoInstPartsAnm::updateSwitch() {
    int switchMax = m_switchMax;
    int no = -1;
    for (int i = 0; i < switchMax; i++) {
        if (m_switches[i].index == m_switchID) {
            no = i;
            break;
        }
    }
    const Switch& sw = m_switches[no == -1 ? 0 : no];
    if (sw.flags & 0x2) {
        m_stockFlags |= 0x4;
    } else {
        m_stockFlags &= ~0x4;
    }
    if (!(sw.flags & 0x1)) {
        return;
    }
    unsigned short start = sw.startFrame;
    unsigned short num = sw.endFrame - sw.startFrame;
    if (m_info->flags & 0x8) {
        m_nodeFrameBase = start;
        m_nodeFrameMax = num;
        bool stocked = m_stockFlags & (1 << DrMan::s_nDblStockIdx);
        float maxFrame = getNodeMaxFrame();
        if (stocked) {
            if (maxFrame < m_nodeFrameStock[DrMan::s_nDblStockIdx]) {
                m_nodeFrameStock[DrMan::s_nDblStockIdx] = getNodeMaxFrame();
            }
            if (m_nodeFrameStock[DrMan::s_nDblStockIdx] < 0.0f) {
                m_nodeFrameStock[DrMan::s_nDblStockIdx] = 0.0f;
            }
            m_oldNodeFrame = m_nodeFrameStock[DrMan::s_nDblStockIdx];
        } else {
            if (maxFrame < m_nodeFrame) {
                m_nodeFrame = getNodeMaxFrame();
            }
            if (m_nodeFrame < 0.0f) {
                m_nodeFrame = 0.0f;
            }
            m_oldNodeFrame = m_nodeFrame;
        }
    }
    if (m_info->flags & 0x10) {
        DrResMdoPosInstAnm* anm = m_posAnm;
        anm->m_frameStart = start;
        anm->m_frameMax = num;
    }
}

unsigned char DrResMdoInstPartsAnm::getSwitchIndex(unsigned int idx) const {
    if (idx < m_switchMax) {
        return m_switches[idx].index;
    }
    return 0;
}

void DrResMdoInstPartsAnm::getMatrix(mm::Mat44& mtx) const {
    if (m_info->flags & 0x10) {
        DrResMdoPosInstAnm* anm = m_posAnm;
        if (anm->m_setMatrixFlags & (1 << DrMan::s_nDblStockIdx)) {
            mtx = anm->m_setMatrix[DrMan::s_nDblStockIdx];
        } else if (anm->m_setMatrixFlags & (1 << DrMan::s_nDblMemIdx)) {
            mtx = anm->m_setMatrix[DrMan::s_nDblMemIdx];
        } else {
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                    mtx.m[i][j] = anm->m_data.matrix.m[i][j];
                }
            }
        }
    } else if (m_info->flags & 0x20) {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                mtx.m[i][j] = m_matrix->m[i][j];
            }
        }
    }
}

void DrResMdoInstPartsAnm::getAnmMatrix(mm::Mat44& mtx) const {
    if (m_info->flags & 0x10) {
        m_posAnm->getAnmMatrix(&mtx, m_posFrame * m_nodeFrameRate);
    } else if (m_info->flags & 0x20) {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                mtx.m[i][j] = m_matrix->m[i][j];
            }
        }
    }
}

void DrResMdoInstPartsAnm::setMatrix(const mm::Mat44& mtx) {
    if (m_info->flags & 0x10) {
        DrResMdoPosInstAnm* anm = m_posAnm;
        int idx = DrMan::s_nDblStockIdx;
        anm->m_setMatrix[idx] = mtx;
        anm->m_setMatrixFlags |= 1 << idx;
    }
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

void DrResFetch::setMdlVertexParam(int num, const MdsMatVertexInfo* info) {
    grlib::CGLibVtxAttr attr[52];
    for (int i = 0; i < num; i++, info++) {
        s_callSetVert[info->m_attr](info->m_size, i, attr[i]);
    }
    createFetchObj(attr, num);
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

void DrResShdPrePass::preshdset_ObjT_Al_Fs() {
    m_shaderSel[5] = 2;
    m_shaderSel[6] = 0;
    m_shaderSel[9] = 4;
    m_shaderSel[8] = 1;
    // The original stores entries 0 and 1 as one 64-bit write: it copies them from a two-entry table (form
    // inferred from the code; the table's name is not the original's).
    const int texAlphaSel[2] = {0, 1};
    for (int i = 0; i < 2; i++) {
        m_shaderSel[i] = texAlphaSel[i];
    }
    m_shaderSel[2] = 5;
}

void DrResShdPrePass::preshdset_Mot_Al() {
    m_shaderSel[5] = 2;
    m_shaderSel[6] = 0;
    m_shaderSel[9] = 4;
    m_shaderSel[8] = 1;
    m_shaderSel[1] = 1;
}

void DrResShdPrePass::preshdset_MotT_Al_Fs() {
    m_shaderSel[5] = 2;
    m_shaderSel[6] = 0;
    m_shaderSel[9] = 4;
    m_shaderSel[8] = 1;
    // The original stores entries 0 and 1 as one 64-bit write: it copies them from a two-entry table (form
    // inferred from the code; the table's name is not the original's).
    const int texAlphaSel[2] = {0, 1};
    for (int i = 0; i < 2; i++) {
        m_shaderSel[i] = texAlphaSel[i];
    }
    m_shaderSel[2] = 5;
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

void DrResShdPrePass::preshdset_FwT_Al() {
    m_shaderSel[5] = 2;
    m_shaderSel[6] = 0;
    m_shaderSel[9] = 4;
    m_shaderSel[8] = 1;
    m_shaderSel[10] = 3;
    // The original stores entries 0 and 1 as one 64-bit write: it copies them from a two-entry table (form
    // inferred from the code; the table's name is not the original's).
    const int texAlphaSel[2] = {0, 1};
    for (int i = 0; i < 2; i++) {
        m_shaderSel[i] = texAlphaSel[i];
    }
    m_shaderSel[3] = 3;
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

void DrResShdPrePass::preshdset_FwT_Al_Fs() {
    m_shaderSel[5] = 2;
    m_shaderSel[6] = 0;
    m_shaderSel[9] = 4;
    m_shaderSel[8] = 1;
    m_shaderSel[10] = 3;
    // The original stores entries 0 and 1 as one 64-bit write: it copies them from a two-entry table (form
    // inferred from the code; the table's name is not the original's).
    const int texAlphaSel[2] = {0, 1};
    for (int i = 0; i < 2; i++) {
        m_shaderSel[i] = texAlphaSel[i];
    }
    m_shaderSel[2] = 5;
    m_shaderSel[3] = 3;
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

DrResMdoMat& DrResMdoMat::operator=(const DrResMdoMat& other) {
    m_color = other.m_color;
    m_alphaParam = other.m_alphaParam;
    pad_1C = other.pad_1C;
    return *this;
}

void DrResMdoMat::setColor(float r, float g, float b, float a) {
    m_color.r = r;
    m_color.g = g;
    m_color.b = b;
    m_color.a = a;
}

void DrResMdoMat::setAlpha(float alpha) {
    m_color.a = alpha;
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

DrResQueryObj::DrResQueryObj() : m_next(nullptr), m_prev(nullptr), m_user(nullptr), m_userWork(nullptr), m_flags(0) {}

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

DrResMdoSampler::DrResMdoSampler(const unsigned char* data)
    : m_pPrev(nullptr), m_pNext(nullptr), m_data(data), pad_18(1), m_samplerBuf(nullptr), m_samplerNum(0) {
    setupSampler(data);
}

DrResMdoSampler::~DrResMdoSampler() {
    if (m_samplerBuf != nullptr) {
        for (int i = 0; i < m_samplerNum; i++) {
            m_samplers[i].~CGLibSampler();
        }
        if (m_samplerBuf != nullptr) {
            mtl::MemManager::deallocate(m_samplerBuf, 0, false);
            m_samplerBuf = nullptr;
        }
    }
}

DrResOccUniformObj::DrResOccUniformObj(DrMan* man, int max) : m_max(max), m_cnt(0), m_buf(nullptr) {
    int size = m_max * 0x40;
    m_buf = m_matTbl = static_cast<mm::Mat44*>(mtl::MemManager::allocate(man->m_allocHandle, size, 0x10, false, "no name", 0));
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

DrResMdoSeamWrkInst::MdlInfo* DrResMdoSeamWrkInst::getMdlInfo() {
    if (m_mdlCnt < m_mdlNum) {
        return &m_mdlInfo[m_mdlCnt++];
    }
    return nullptr;
}

void DrResMdoSeamWrkInst::callShadowCacheInstUpdate(unsigned long mask) {
    for (unsigned long i = 0; i < 36; i++) {
        if ((1UL << i) & mask) {
            for (int j = 0; j < m_posInstNum; j++) {
                DrResMdoSeamWrkPosInst* pos = m_posInstList[j];
                if (pos->m_shadowCacheBufSize != 0) {
                    memset(pos->m_shadowCacheBuf[i], 0, pos->m_shadowCacheBufSize);
                }
            }
        }
    }
    m_shadowCacheDone &= ~mask;
}

mm::Mat44* DrResOccUniformObj::getMatTbl(int idx) {
    return m_matTbl + idx;
}


DrResEtcUniformObj::DrResEtcUniformObj(DrMan* man, int entryMax, int size, int matMax)
    : m_entryMax(entryMax), m_entryCnt(0), m_used(0), m_matMax(matMax), m_buf(nullptr) {
    int allocSize = m_entryMax * 8 + m_matMax * 0x40;
    void* buf = mtl::MemManager::allocate(man->m_allocHandle, allocSize, 0x10, false, "no name", 0);
    m_buf = buf;
    m_matTbl = reinterpret_cast<mm::Mat44*>(static_cast<unsigned char*>(buf) + (m_entryMax << 3));
    m_entry = static_cast<Entry*>(buf);
    m_size = size;
    m_block.setup(size);
}

DrResEtcUniformObj::~DrResEtcUniformObj() {
    m_block.release();
    if (m_buf != nullptr) {
        mtl::MemManager::deallocate(m_buf, 0, false);
        m_buf = nullptr;
    }
}

void DrResEtcUniformObj::begin() {
    m_entryCnt = 0;
    m_used = 0;
}

void DrResEtcUniformObj::end() {
    if (m_used != 0) {
        m_block.updateData(0, m_used);
    }
}

void DrResEtcUniformObj::setUniformBlock(short idx, unsigned int location) {
    m_block.setUniformBlock(location, m_entry[idx].ofs, m_entry[idx].size);
}

void DrResEtcUniformObj::setStorageBuffer(short idx, unsigned int location, unsigned int ofs) {
    m_block.setStorageBuffer(location, m_entry[idx].ofs + ofs, m_entry[idx].size - ofs);
}

unsigned char* DrResEtcUniformObj::createUniformBuff(int size) {
    int alignedSize = size + (0x100 - size % 0x100) % 0x100;
    unsigned char* buf = m_block.getBuff() + m_used;
    m_entry[m_entryCnt].ofs = m_used;
    m_entry[m_entryCnt].size = size;
    m_used += alignedSize;
    m_entryCnt++;
    return buf;
}

// the pixel count m_pixel is forced to while the camera is inside the box (the name is not the original's)
static const unsigned int c_fullPixel = 800000;

DrResClip::DrResClip() : m_query(nullptr), m_flags(FLAG_INIT0 | FLAG_INIT1), m_holdCnt(0), m_pixel(0) {}

DrResClip::~DrResClip() {
    if (m_query != nullptr) {
        m_query->m_user = nullptr;
        m_query = nullptr;
    }
}

bool DrResClip::clipChk(DrCalcViewWork* view, const mm::Vec3& pos, const mm::Vec3& size, float radius, bool noOcc) {
    m_flags &= ~(FLAG_IN_FRUSTUM | FLAG_OUT_FRUSTUM);
    mm::Vec3 d(view->m_viewPos.x - pos.x, view->m_viewPos.y - pos.y, view->m_viewPos.z - pos.z);
    float margin = view->m_near + 0.2f;
    if (size.x + margin >= mm::fabs(d.x) && margin + size.y >= mm::fabs(d.y) && margin + size.z >= mm::fabs(d.z)) {
        m_flags = (m_flags & ~(FLAG_INIT0 | FLAG_INIT1)) | FLAG_SKIP0 | FLAG_SKIP1 | FLAG_SKIP2 | FLAG_VISIBLE |
                  FLAG_FULL_PIXEL;
        m_pixel = c_fullPixel;
        m_holdCnt = 4;
        return false;
    }
    if (!view->m_clipPlane.clipTest(&pos.x, &size.x)) {
        m_pixel = 0;
        m_flags = (m_flags & ~(FLAG_VISIBLE | FLAG_INIT0 | FLAG_INIT1 | FLAG_FULL_PIXEL)) | FLAG_SKIP0 | FLAG_SKIP1 |
                  FLAG_SKIP2 | FLAG_OUT_FRUSTUM;
        return true;
    }
    m_flags |= FLAG_IN_FRUSTUM;
    if (noOcc) {
        if (m_flags & FLAG_FULL_PIXEL) {
            m_pixel = c_fullPixel;
        }
        m_flags = (m_flags & ~(FLAG_INIT0 | FLAG_INIT1)) | FLAG_SKIP0 | FLAG_SKIP1 | FLAG_SKIP2 | FLAG_VISIBLE;
        m_holdCnt = 3;
        return false;
    }
    if (m_flags & (FLAG_SKIP0 | FLAG_SKIP1 | FLAG_SKIP2)) {
        if (m_flags & FLAG_FULL_PIXEL) {
            m_pixel = c_fullPixel;
        }
        if (m_flags & FLAG_SKIP0) {
            m_flags &= ~FLAG_SKIP0;
        } else if (m_flags & FLAG_SKIP1) {
            m_flags &= ~FLAG_SKIP1;
        } else if (m_flags & FLAG_SKIP2) {
            m_flags &= ~(FLAG_SKIP2 | FLAG_FULL_PIXEL);
        }
        return false;
    }
    if (m_flags & (FLAG_INIT0 | FLAG_INIT1)) {
        if (m_flags & FLAG_INIT0) {
            m_flags &= ~FLAG_INIT0;
        } else {
            m_flags &= ~FLAG_INIT1;
        }
        m_flags &= ~(FLAG_VISIBLE | FLAG_FULL_PIXEL);
        m_pixel = 0;
        return false;
    }
    if (m_query != nullptr && (m_query->m_flags & (4 << DrMan::s_nDblNowIdx))) {
        m_pixel = m_query->m_query.getQueryPixel();
    } else {
        m_pixel = 0;
    }
    if (m_pixel == 0) {
        if (!(m_flags & FLAG_VISIBLE)) {
            return true;
        }
        if (m_holdCnt-- < 0) {
            m_flags &= ~FLAG_VISIBLE;
            m_holdCnt = 0;
            return true;
        }
        return false;
    }
    m_flags |= FLAG_VISIBLE;
    m_holdCnt = 5;
    return false;
}

bool DrResClip::clipChkOccOff(DrCalcViewWork* view, const mm::Vec3& pos, float radius) {
    m_flags &= ~(FLAG_IN_FRUSTUM | FLAG_INIT0 | FLAG_INIT1 | FLAG_OUT_FRUSTUM);
    m_pixel = 0;
    float dx = view->m_viewPos.x - pos.x;
    float dy = view->m_viewPos.y - pos.y;
    float dz = view->m_viewPos.z - pos.z;
    if (dx * dx + dy * dy + dz * dz <= radius * radius) {
        m_flags = (m_flags & ~FLAG_VISIBLE) | FLAG_SKIP0 | FLAG_SKIP1 | FLAG_SKIP2;
        return false;
    }
    if (view->m_clipPlane.clipTest(pos, radius)) {
        return false;
    }
    m_flags = 0;
    return true;
}

DrResMpfSampler::DrResMpfSampler(const MdsMpfMatInfoHeader* header) : m_sampler() {
    setupSampler(header);
}

DrResMpfSampler::~DrResMpfSampler() {
    for (int i = 0; i < 3; i++) {
        if (m_sampler[i] != nullptr) {
            delete m_sampler[i];
            m_sampler[i] = nullptr;
        }
    }
}

void DrResMpfSampler::setupSampler(const MdsMpfMatInfoHeader* header) {
    for (int i = 0; i < 3; i++) {
        if (m_sampler[i] != nullptr) {
            delete m_sampler[i];
            m_sampler[i] = nullptr;
        }
    }
    for (int i = 0; i < 3; i++) {
        m_sampler[i] = new (DrMan::getIns()->m_resHandle, nullptr, 0, 4, false) grlib::CGLibSampler;
        unsigned short flags;
        switch (i) {
        case 0:
            flags = header->m_samplerFlags0;
            break;
        case 1:
            flags = header->m_samplerFlags1;
            break;
        case 2:
            flags = header->m_samplerFlags2;
            break;
        default:
            flags = 0;
            break;
        }
        m_sampler[i]->initSampler(static_cast<GrlTexClamp>(2), static_cast<GrlTexMagFilterType>(1));
        // bit 0/1: s/t clamp 0, else 2 (1 with bit 2/3)
        GrlTexClamp clampS = static_cast<GrlTexClamp>((flags & 1) ? 0 : 2 - ((flags >> 2) & 1));
        GrlTexClamp clampT = static_cast<GrlTexClamp>((flags & 2) ? 0 : 2 - ((flags >> 3) & 1));
        m_sampler[i]->setClamp(clampS, clampT, static_cast<GrlTexClamp>(2));
        if (flags & 0x10) {
            m_sampler[i]->setFilter(static_cast<GrlTexMagFilterType>(0), static_cast<GrlTexMinFilterType>(2),
                                    static_cast<GrlTexTexAnisoRatio>(0));
        } else {
            m_sampler[i]->setFilter(static_cast<GrlTexMagFilterType>(1), static_cast<GrlTexMinFilterType>(5),
                                    static_cast<GrlTexTexAnisoRatio>(0));
        }
        m_sampler[i]->updateData();
    }
}

DrPixlToonGrad::DrPixlToonGrad(DrMan* drMan) {
    m_update = true;
    m_drMan = drMan;
    for (int i = 0; i < 2; i++) {
        m_gradTarget[i] = new (m_drMan->m_workHandle, nullptr, 0, 4, false) DrPixlRenderTarget(m_drMan);
        m_gradTarget[i]->setTextureInfo(512.0f, 256.0f, static_cast<GrlSurfaceFormat>(0x25), false, 0);
        m_darkGradTarget[i] = new (m_drMan->m_workHandle, nullptr, 0, 4, false) DrPixlRenderTarget(m_drMan);
        m_darkGradTarget[i]->setTextureInfo(512.0f, 256.0f, static_cast<GrlSurfaceFormat>(0x25), false, 0);
    }
}

DrPixlToonGrad::~DrPixlToonGrad() {
    for (int i = 0; i < 2; i++) {
        if (m_gradTarget[i] != nullptr) {
            delete m_gradTarget[i];
            m_gradTarget[i] = nullptr;
        }
        if (m_darkGradTarget[i] != nullptr) {
            delete m_darkGradTarget[i];
            m_darkGradTarget[i] = nullptr;
        }
    }
}

grlib::CGLibTextureBuffer& DrPixlToonGrad::getGradTex() const {
    return *m_gradTarget[DrMan::s_nDblIdx]->m_pTexture;
}

grlib::CGLibTextureBuffer& DrPixlToonGrad::getDarkGradTex() const {
    return *m_darkGradTarget[DrMan::s_nDblIdx]->m_pTexture;
}

DrResEtcTexList::~DrResEtcTexList() {
    releaseTexture();
}

// 1.0.0 has it out of line (0x7100868D70); 3.0.1 keeps only the copy inlined into the destructor
void DrResEtcTexList::releaseTexture() {
    if (m_buf != nullptr) {
        for (int i = 0; i < m_num; i++) {
            m_texture[i].~CGLibTextureBuffer();
        }
        if (m_buf != nullptr) {
            mtl::MemManager::deallocate(m_buf, 0, false);
            m_buf = nullptr;
        }
        m_texture = nullptr;
        m_num = 0;
    }
}

void DrResEtcTexList::release() {
    m_flags |= 1;
}

grlib::CGLibTextureBuffer* DrResEtcTexList::getTextureID(unsigned int id) {
    if (m_flags & 1) {
        return nullptr;
    }
    const Entry* entry =
        reinterpret_cast<const Entry*>(reinterpret_cast<const unsigned char*>(m_header) + m_header->m_entryOfs);
    for (int i = 0; i < m_num; i++, entry++) {
        if (entry->m_id == id) {
            return &m_texture[i];
        }
    }
    return nullptr;
}

DrGpuCheckObj::~DrGpuCheckObj() {
    m_query.release();
}

void DrGpuCheckObj::setPause(bool pause) {
    if (pause) {
        m_flags |= FLAG_PAUSE;
    } else {
        m_flags &= ~FLAG_PAUSE;
    }
}

void DrGpuCheckObj::release() {
    m_flags |= FLAG_RELEASE << DrMan::s_nDblStockIdx;
}

unsigned int DrGpuCheckObj::isDeleteCall() const {
    return m_flags & (FLAG_RELEASE << DrMan::s_nDblIdx);
}

void DrGpuCheckObj::render() {
    if (m_flags & FLAG_QUERY) {
        DrGpuCheckRender* check = DrMan::get()->m_mdlMan->m_gpuCheckRender;
        m_query.beginQuery();
        if (m_flags & FLAG_CREATE) {
            check->render(m_instansOfs, 2);
        } else {
            check->render(m_instansOfs, 1);
        }
        m_query.endQuery();
        m_flags |= FLAG_QUERIED << DrMan::s_nDblIdx;
    }
}

bool DrGpuCheckObj::isRender() const {
    return (m_flags & FLAG_RENDER) != 0;
}



DrResFilterData::~DrResFilterData() {
    if (m_texNum != 0) {
        for (int i = 0; i < m_texNum; i++) {
            m_texture[i].~CGLibTextureBuffer();
        }
        if (m_texture != nullptr) {
            mtl::MemManager::deallocate(m_texture, 0, false);
            m_texture = nullptr;
        }
        m_texNum = 0;
    }
}

grlib::CGLibTextureBuffer* DrResFilterData::findFilterTexture(unsigned int id) const {
    for (int i = 0; i < m_texNum; i++) {
        if (m_entries[i].m_id == id) {
            return &m_texture[i];
        }
    }
    return m_texture;
}

DrGpuCheckBase* DrGpuCheckBase::createEffGpuCheckObj(int type) {
    return DrMan::get()->m_mdlMan->createEffGpuCheckObj(type);
}

DrGpuCheckRender::DrGpuCheckRender() {
    m_uniform.setup(0x80);
}

DrGpuCheckRender::~DrGpuCheckRender() {}

void DrGpuCheckRender::beginUpdate() {
    m_viewWork = DrMan::get()->m_calcMan->m_pViewWork;
    m_instans = DrMan::get()->m_mdlMan->m_vertexMan->m_instans;
    m_instansBuff = static_cast<mm::Vec4*>(m_instans->getNextInstansBuff());
    m_instansOfs = m_instansStart = m_instans->m_offset;
    m_mode = 1;
}

void DrGpuCheckRender::endUpdate() {
    if (m_instansOfs != m_instansStart) {
        m_instans->m_offset += m_instansOfs - m_instansStart;
    }
}

void DrGpuCheckRender::endRender() {
    DrMan::get()->m_pixlMan->depCheckEnd();
}

void DrGpuCheckRender::render(unsigned int ofs, int mode) {
    if (m_mode != mode) {
        DrShdDataObj* shd = m_shdList->getSelectShdObj(8);
        shd->setDeclarationIdx(m_declOfs, mode);
        shd->setupShader(0u);
        if (mode == 1) {
            m_shdList->bindShdDepthCheck();
        } else {
            m_shdList->bindShdBoxVertex();
        }
        m_mode = mode;
    }
    grlib::CGLibCtlVertex::setInstanceVertex(*m_instans, 0x10, ofs, 1, 1);
    if (mode == 1) {
        m_shdList->renderQuads();
    } else {
        m_shdList->renderBox();
    }
}

DrGpuCheckObj::DrGpuCheckObj(int type, bool eff)
    : m_prev(nullptr), m_next(nullptr), m_type(type), m_query(), m_instansOfs(0), m_flags(0),
      m_pos{mm::Vec4(0.0f, 0.0f, 0.0f, 1.0f), mm::Vec4(0.0f, 0.0f, 0.0f, 1.0f)}, m_worldPos(0.0f, 0.0f, 0.0f, 1.0f),
      m_holdCnt(3), m_waitCnt(0) {
    if (eff) {
        m_flags = FLAG_CREATE;
    }
}

void DrGpuCheckObj::setPos(const mm::Vec3& pos, float radius) {
    int idx = DrMan::s_nDblStockIdx;
    m_flags |= FLAG_POS << idx;
    mm::Vec3 p(pos);
    m_pos[idx].x = p.x;
    m_pos[idx].y = p.y;
    m_pos[idx].z = p.z;
    m_pos[idx].w = radius;
}

void DrGpuCheckObj::setWorldPos(const mm::Vec3& pos, float radius) {
    mm::Vec3 p(pos);
    m_worldPos.x = p.x;
    m_worldPos.y = p.y;
    m_worldPos.z = p.z;
    m_worldPos.w = radius;
    if (DrMan::get()->m_mdlMan->m_gpuCheckRender->m_viewWork->m_gpuCheckAllVisible) {
        m_holdCnt = 3;
        m_flags |= FLAG_RENDER;
    }
}



DrStmReadCheck::DrStmReadCheck(const char* name) : m_flags(0) {
    m_list = DrMan::get()->m_texStreamMan->createTexStmListObj(name);
}

DrStmReadCheck::~DrStmReadCheck() {
    if (m_list != nullptr) {
        m_list->release();
        m_list = nullptr;
    }
}

void DrStmReadCheck::release() {
    m_flags |= FLAG_RELEASE << DrMan::s_nDblStockIdx;
}

void* DrStmReadCheck::getAdder() {
    if ((m_flags & FLAG_READY) && m_list != nullptr) {
        m_list->getAdder();
    }
    return nullptr;
}

bool DrStmReadCheck::update() {
    if (m_flags & (FLAG_RELEASE << DrMan::s_nDblIdx)) {
        return true;
    }
    if (!(m_flags & FLAG_READY)) {
        if (m_mode == 2) {
            m_list->setUseMode(static_cast<DrCalcStmListObj::DrTexUseMode>(2));
        } else if (m_mode == 1) {
            m_list->setUseMode(static_cast<DrCalcStmListObj::DrTexUseMode>(1));
        } else {
            m_list->setUseMode(static_cast<DrCalcStmListObj::DrTexUseMode>(0));
        }
    }
    return false;
}


void DrResMdoLight::lgtCreate() {
    if (m_flags & FLAG_CREATED) {
        return;
    }
    DrLightMan* man = DrMan::getIns()->m_lightMan;
    if (man == nullptr) {
        return;
    }
    const EtcLights* res = m_etcLights;
    m_flags |= FLAG_CREATED;
    unsigned long lgtOfs = res->m_lightOfs;
    unsigned long matOfs = res->m_matOfs;
    m_num = res->m_num;
    for (int i = 0; i < res->m_num; i++, lgtOfs += sizeof(EtcLight), matOfs += sizeof(mm::Mat44)) {
        const EtcLight* lgt = reinterpret_cast<const EtcLight*>(reinterpret_cast<const unsigned char*>(res) + lgtOfs);
        DrLightObj* light;
        if (lgt->m_type == 0) {
            DrLightObjPnt* pnt = man->createInstantPntLight();
            mm::Vec3 col(lgt->m_color[0], lgt->m_color[1], lgt->m_color[2]);
            col = col * lgt->m_intensity;
            pnt->m_color[0] = col.x;
            pnt->m_color[1] = col.y;
            pnt->m_color[2] = col.z;
            pnt->m_lightParam = lgt->m_param == 0.0f ? 1.0f : lgt->m_param;
            if (lgt->m_flags & 2) {
                pnt->setSubtractOn(true);
            }
            if (lgt->m_size != 0.0f) {
                pnt->m_size = lgt->m_size;
            }
            pnt->m_lightParam2 = lgt->m_param2;
            pnt->m_lightRate = lgt->m_rate;
            pnt->setMat(*reinterpret_cast<const mm::Mat44*>(reinterpret_cast<const unsigned char*>(res) + matOfs));
            light = pnt;
        } else {
            DrLightObjSpt* spt = man->createInstantSptLight();
            mm::Vec3 col(lgt->m_color[0], lgt->m_color[1], lgt->m_color[2]);
            col = col * lgt->m_intensity;
            spt->m_color[0] = col.x;
            spt->m_color[1] = col.y;
            spt->m_color[2] = col.z;
            spt->m_lightParam = lgt->m_param == 0.0f ? 1.0f : lgt->m_param;
            if (lgt->m_size != 0.0f) {
                spt->m_size = lgt->m_size;
            }
            if (lgt->m_flags & 2) {
                spt->setSubtractOn(true);
            }
            spt->m_lightParam2 = lgt->m_param2;
            spt->m_spotParam = lgt->m_rate;
            spt->pad_e0 = lgt->m_spotPadE0;
            spt->m_angle = lgt->m_angle;
            spt->setMat(*reinterpret_cast<const mm::Mat44*>(reinterpret_cast<const unsigned char*>(res) + matOfs));
            light = spt;
        }
        m_lights[i] = light;
    }
}

void DrResMdoLight::setDisp(bool disp) {
    if (disp) {
        m_flags |= FLAG_DISP;
    } else {
        m_flags &= ~FLAG_DISP;
    }
}

unsigned int DrResMdoLight::calcWorkSize(const unsigned char* mdo) {
    const MdoHeader* header = reinterpret_cast<const MdoHeader*>(mdo);
    const MdoLights* lights = reinterpret_cast<const MdoLights*>(mdo + header->m_lightOfs);
    return lights->m_num * sizeof(DrLightObj*) + sizeof(DrResMdoLight);
}

void DrResMdoLight::release(DrResMdoLight*& obj) {
    DrResMdoLight* light = obj;
    if (light == nullptr) {
        return;
    }
    if (light->m_lights != nullptr) {
        DrLightMan* man = DrMan::getIns()->m_lightMan;
        for (int i = 0; i < light->m_num; i++) {
            if (light->m_lights[i] != nullptr) {
                if (light->m_lights[i]->isPnt()) {
                    man->releasePntLight(static_cast<DrLightObjPnt*>(light->m_lights[i]));
                } else {
                    man->releaseSptLight(static_cast<DrLightObjSpt*>(light->m_lights[i]));
                }
            }
        }
        light->m_num = 0;
        light->m_lights = nullptr;
    }
    obj = nullptr;
}


DrResMdoPos::DrResMdoPos(const MdsPosKeepData* data) : m_owner(0), m_data(data), m_frame(0), m_alphaCnt(0), m_alphaMax(0xFF) {}

DrResMdoPos::~DrResMdoPos() { release(); }

void DrResMdoPos::copy(DrResMdoPos* src) {
    m_frame = 0;
    m_id = src->m_id;
    m_data = src->m_data;
    m_alphaCnt = src->m_alphaCnt;
    m_alphaMax = src->m_alphaMax;
}

bool DrResMdoPos::clipTest(DrCalcViewWork* view, const mm::Vec3& pos, float radius) {
    float dx = view->m_viewPos.x - pos.x;
    float dy = view->m_viewPos.y - pos.y;
    float dz = view->m_viewPos.z - pos.z;
    if (dx * dx + dy * dy + dz * dz > radius * radius && !view->m_clipPlane.clipTest(pos, radius)) {
        return false;
    }
    return true;
}

void DrResMdoPos::setAddAlphaCnt(int cnt) {
    int alpha = m_alphaCnt + cnt;
    if (alpha > 0xFF) {
        m_alphaCnt = 0xFF;
        return;
    }
    m_alphaCnt = alpha;
}

bool DrResMdoPos::setSubAlphaCnt(int cnt) {
    int alpha = m_alphaCnt - cnt;
    if (alpha < 0) {
        m_alphaCnt = 0;
        return false;
    }
    m_alphaCnt = alpha;
    return true;
}

int DrResMdoPosAddList::createBuffSize() { return ADD_MAX * sizeof(DrResMdoPos); }

int DrResMdoPosAddList::setupBuff(unsigned char* buff) {
    m_buff = reinterpret_cast<DrResMdoPos*>(buff);
    m_cnt = 0;
    for (int i = 0; i < ADD_MAX; i++) {
        new (&m_buff[i]) DrResMdoPos();
    }
    return createBuffSize();
}

void DrResMdoPosAddList::release() {
    for (int i = 0; i < ADD_MAX; i++) {
        m_buff[i].release();
    }
}

void DrResMdoPosAddList::begin() { m_cnt = 0; }

DrResMdoPos* DrResMdoPosAddList::createAdd() {
    if (m_cnt >= ADD_MAX) {
        return 0;
    }
    return &m_buff[m_cnt++];
}

DrResMdoInstAnmObj::DrResMdoInstAnmObj() : m_header(0), m_parts(0), pad_10() {}

void DrResMdoInstAnmObj::release() {
    m_header = nullptr;
    m_parts = nullptr;
    memset(pad_10, 0, sizeof(pad_10));
}

void DrResMdoInstAnmObj::setupLink(DrResMdoPos* pos) const {
    if (m_header) {
        for (int i = 0, idx = m_header->linkTopA; i < m_header->linkNumA; i++, idx++) {
            pos[m_parts[idx]->m_info->posNo].m_id = idx;
        }
        for (int i = 0, idx = m_header->linkTopB; i < m_header->linkNumB; i++, idx++) {
            pos[m_parts[idx]->m_info->posNo].m_id = idx;
        }
    }
}

DrResMdoSeamParmRead::DrResMdoSeamParmRead() : m_flags(0), m_readPos(0.0f, 0.0f, 0.0f), pad_62C() { m_posCnt = 0; }

DrResMdoSeamParmRead::~DrResMdoSeamParmRead() {}

void DrResMdoSeamParmRead::setStockBaseMap(int no) {
    if (m_stockBaseMapCnt < STOCK_BASE_MAP_MAX) {
        m_stockBaseMap[m_stockBaseMapCnt++] = no;
    }
}

void DrResMdoSeamParmRead::setStockInstMap(int no, DrResMdoSeamWrkInst* wrk) {
    if (m_stockInstMapCnt < STOCK_INST_MAP_MAX) {
        StockInst& stock = m_stockInstMap[m_stockInstMapCnt++];
        stock.wrk = wrk;
        stock.no = no;
        stock.type = STOCK_TYPE_INST;
    }
}

void DrResMdoSeamParmRead::setStockMpfMdl(int no) {
    if (m_stockMpfMdlCnt < STOCK_MPF_MDL_MAX) {
        m_stockMpfMdl[m_stockMpfMdlCnt++] = no;
    }
}

void DrResMdoSeamParmRead::setStockEnvMdl(int no) { m_stockEnvMdl = no; }

void DrResMdoSeamParmRead::setStockLowMdl(int no) {
    if (m_stockLowMdlCnt < STOCK_LOW_MDL_MAX) {
        m_stockLowMdl[m_stockLowMdlCnt++] = no;
    }
}

void DrResMdoSeamParmRead::setStockLight(int no) {
    if (m_stockLightCnt < STOCK_LIGHT_MAX) {
        m_stockLight[m_stockLightCnt++] = no;
    }
}

void DrResMdoSeamParmRead::resetHeightLvTexture() { m_heightLvTexCnt = 0; }

void DrResMdoSeamParmRead::addPos(const mm::Vec3& pos) {
    m_flags |= FLAG_POS;
    m_pos[m_posCnt] = pos;
    m_posCnt++;
}

DrResMdoSeamWrkEnv::DrResMdoSeamWrkEnv()
    : m_matBits(nullptr), m_work0(nullptr), m_work1(nullptr), m_work2(nullptr), m_matRes(nullptr), m_memObj(nullptr),
      m_flags(0), m_dispNum(0) {}

void DrResMdoSeamWrkEnv::release() {
    if (m_matRes) {
        mtl::MemManager::deallocate(m_matRes, 0, false);
        m_matRes = 0;
    }
    if (m_work0) {
        mtl::MemManager::deallocate(m_work0, 0, false);
        m_work0 = 0;
    }
    if (m_work1) {
        mtl::MemManager::deallocate(m_work1, 0, false);
        m_work1 = 0;
    }
    if (m_matBits) {
        mtl::MemManager::deallocate(m_matBits, 0, false);
        m_matBits = 0;
    }
    m_work2 = 0;
    m_flags = 0;
    m_memObj = 0;
}

void DrResMdoSeamWrkEnv::setupWork(MdoWrkMatRes* matRes, grlib::CGLibTriUniformArray* triArray, mtl::ALLOC_HANDLE handle,
                                   const MdsSeamEnvMapHead* head, const MdsSeamEnvMapData* data) {
    m_matRes = matRes;
    m_head = head;
    m_data = data;
    m_flags = 0;
    m_dispNum = data->dispNum;
    m_work0 = 0;
    m_work1 = 0;
    m_work2 = 0;
    matRes->m_pTriUniformArray = triArray;
    // one bit per material, rounded up to 0x20 bytes
    unsigned int size = (matRes->m_matNum / 32) * 4 + 4;
    size = size + ((0x20 - (size & 0x1F)) & 0x1F);
    m_matBits = m_matBitsTop = mtl::MemManager::allocate(handle, size, 0x20, false, "no name", 0);
    memset(m_matBits, 0, size);
}

void DrResMdoSeamWrkEnv::changeMemCall(const MdsSeamEnvMapHead* head) {
    m_head = head;
    m_flags &= ~FLAG_MEM_MASK;
}

void DrResMdoSeamWrkEnv::setInfo(const mm::Vec3& pos0, const mm::Vec3& pos1, bool flag, unsigned int type) {
    m_type = type;
    m_infoFlag = flag;
    m_pos0 = pos0;
    m_pos1 = pos1;
}

unsigned int DrResMdoSeamWrkEnv::chkDispState() { return m_flags & (1 << DrMan::s_nDblNowIdx); }

void DrResMdoSeamWrkEnv::setDispState() { m_flags |= 1 << DrMan::s_nDblNowIdx; }



unsigned int DrResMdoInstMdlInfo::calcWorkSize(const unsigned char* data) {
    return reinterpret_cast<const Data*>(data)->m_num * 0x10 + sizeof(DrResMdoInstMdlInfo);
}

unsigned int DrResMdoInstMdlInfo::create(unsigned char* work, DrResMdoInstMdlInfo*& out, const unsigned char* data,
                                         const char* name) {
    DrResMdoInstMdlInfo* info = reinterpret_cast<DrResMdoInstMdlInfo*>(work);
    out = info;
    info->m_name[0] = '\0';
    info->pad_110 = 0;
    info->m_deleteFlags = 0;
    info->m_num = 0;
    info->m_list = nullptr;
    return out->setup(work + sizeof(DrResMdoInstMdlInfo), data, name);
}

void DrResMdoInstMdlInfo::releaseCall() {
    for (int i = 0; i < m_num; i++) {
        DrMdlBase* mdl = m_list[i].m_mdl;
        if (mdl != nullptr) {
            mdl->setDeleteCall(DrMan::s_nDblStockIdx);
        }
    }
    m_num = 0;
    m_deleteFlags |= 2 << DrMan::s_nDblStockIdx;
}

void DrResMdoInstMdlInfo::release(DrResMdoInstMdlInfo*& info) {
    DrResMdoInstMdlInfo* obj = info;
    for (int i = 0; i < obj->m_num; i++) {
        Entry& entry = obj->m_list[i];
        if (entry.m_mdl != nullptr) {
            entry.m_mdl->setDeleteCall(DrMan::s_nDblStockIdx);
            entry.m_mdl = nullptr;
        }
    }
    obj->m_num = 0;
    info = nullptr;
}

DrResMdoSeamMemMan::DrResMdoSeamMemMan() {
    m_memList.m_head = nullptr;
    m_memList.m_tail = nullptr;
    m_spareList.m_head = nullptr;
    m_spareList.m_tail = nullptr;
    pad_24 = 0;
    pad_28 = 0;
    m_flags = 0;
    m_objNum = 0;
    m_objs = nullptr;
}

DrResMdoSeamMemMan::~DrResMdoSeamMemMan() { releaseMem(); }

void DrResMdoSeamMemMan::releaseMem() {
    for (unsigned int i = 0; i < m_objNum; i++) {
        m_objs[i].~DrResMdoSeamMemObj();
    }
    m_objNum = 0;
    if (m_objs != nullptr) {
        mtl::MemManager::deallocate(m_objs, 0, false);
        m_objs = nullptr;
    }
    m_flags = 0;
    m_spareList.m_head = nullptr;
    m_spareList.m_tail = nullptr;
    m_memList.m_head = nullptr;
    m_memList.m_tail = nullptr;
}

DrResMdoSeamMemObj* DrResMdoSeamMemMan::createFreeObj(unsigned int size) {
    for (DrResMdoSeamMemObj* obj = m_memList.m_head; obj != nullptr; obj = obj->m_next) {
        if (!(obj->m_flags & 1) && size <= obj->m_size) {
            unsigned int rest = obj->m_size - size;
            if (rest == 0) {
                obj->m_flags = 0;
            } else {
                DrResMdoSeamMemObj* spare = m_spareList.m_head;
                if (spare == nullptr) return nullptr;
                obj->m_size = size;
                spare->m_pData = obj->m_pData + size;
                spare->m_size = rest;
                m_spareList.remove(spare);
                spare->m_flags = 0;
                m_memList.insertNext(obj, spare);
            }
            obj->m_flags |= 1;
            return obj;
        }
    }
    return nullptr;
}

DrResMdoSeamMemObj* DrResMdoSeamMemMan::createBackFreeObj(unsigned int size) {
    DrResMdoSeamMemObj* ret = nullptr;
    for (DrResMdoSeamMemObj* obj = m_memList.m_tail; obj != nullptr; obj = obj->m_prev) {
        if (!(obj->m_flags & 1) && size <= obj->m_size) {
            unsigned int rest = obj->m_size - size;
            if (rest != 0) {
                ret = m_spareList.m_head;
                if (ret == nullptr) break;
                obj->m_size = rest;
                ret->m_size = size;
                ret->m_pData = obj->m_pData + rest;
                m_spareList.remove(ret);
                ret->m_flags = 0;
                m_memList.insertNext(obj, ret);
            } else {
                ret = obj;
                obj->m_flags = 0;
            }
            ret->m_flags |= 1;
            break;
        }
    }
    return ret;
}

DrResMdoSeamMemObj* DrResMdoSeamMemMan::createParentFreeObj(DrResMdoSeamMemObj* parent, unsigned int size) {
    if (parent->m_size < size) return nullptr;
    DrResMdoSeamMemObj* obj = m_spareList.m_head;
    if (obj != nullptr) {
        m_spareList.remove(obj);
        unsigned int rest = parent->m_size - size;
        parent->m_size = size;
        obj->m_size = rest;
        obj->m_pData = parent->m_pData + size;
        obj->m_flags = 1;
        DrResMdoSeamMemObj* next = parent->m_next;
        parent->m_next = obj;
        obj->m_prev = parent;
        if (next != nullptr) {
            obj->m_next = next;
            next->m_prev = obj;
        } else {
            obj->m_next = nullptr;
            m_memList.m_tail = obj;
        }
    }
    return obj;
}

void DrResMdoSeamMemMan::releaseFreeObj(DrResMdoSeamMemObj* obj) {
    clearMemObj(obj, m_memList);
    if (m_flags & 2) {
        for (int i = 0; i < m_cacheNum; i++) {
            if (m_cache[i] == obj) m_cache[i] = nullptr;
        }
    }
}

// Zeroes 0x8-0x58 as one block, then sets the flags.
DrResMdoSeamRead::DrResMdoSeamRead() : m_handles(), m_readWaitBits(0), m_readDoneBits(0), m_flags(0), m_path(nullptr) {
    m_flags = FLAG_READ_ASYNC;
}

DrResMdoSeamRead::~DrResMdoSeamRead() { release(); }

void DrResMdoSeamRead::release() {
    m_readWaitBits = 0;
    m_readDoneBits = 0;
    if (m_flags & FLAG_OPEN) {
        for (int i = 0; i < 8; i++) {
            if (m_handles[i] != nullptr) {
                DevFileTh::rfClose(m_handles[i]);
                m_handles[i] = nullptr;
            }
        }
        m_flags &= ~FLAG_OPEN;
    }
    if (m_flags & FLAG_READ_FILE) {
        for (int i = 0; i < 8; i++) {
            if (m_handles[i] != nullptr) {
                DevFileTh::cancel(m_handles[i], false);
                m_handles[i] = nullptr;
            }
        }
        m_flags &= ~FLAG_READ_FILE;
    }
}

void DrResMdoSeamRead::setup(bool async) {
    m_flags = (m_flags & ~(FLAG_READ_ASYNC | FLAG_READ_SYNC)) | (async ? FLAG_READ_ASYNC : FLAG_READ_SYNC);
}

void DrResMdoSeamRead::setOpenInit() {
    release();
    if (!(m_flags & FLAG_READ_ASYNC)) return;
    DevFileParamTh param;
    param.m_listener = this;
    param.m_path = m_path;
    for (int i = 0; i < 8; i++) {
        if (m_handles[i] == nullptr) {
            m_handles[i] = DevFileTh::rfOpen(param);
            if (m_handles[i] == nullptr) {
                m_flags |= FLAG_OPEN_ERR;
                return;
            }
        }
    }
    m_flags |= FLAG_OPEN;
}

void DrResMdoSeamRead::update(const char* path, bool async) {
    m_path = path;
    m_flags &= ~FLAG_OPEN_ERR;
    if (async) {
        if (m_flags & FLAG_READ_SYNC) m_flags |= FLAG_WANT_ASYNC;
    } else {
        if (m_flags & FLAG_READ_ASYNC) m_flags |= FLAG_WANT_SYNC;
    }
    if ((m_flags & (FLAG_WANT_ASYNC | FLAG_READ_SYNC)) == (FLAG_WANT_ASYNC | FLAG_READ_SYNC)) m_flags |= FLAG_MODE_CHANGE;
    if ((m_flags & (FLAG_WANT_SYNC | FLAG_READ_ASYNC)) == (FLAG_WANT_SYNC | FLAG_READ_ASYNC)) m_flags |= FLAG_MODE_CHANGE;
    if (m_flags & FLAG_MODE_CHANGE) {
        if (!isRead()) {
            if (m_flags & FLAG_MODE_WAIT) {
                release();
                m_flags = (m_flags & ~0xFF) | ((m_flags & FLAG_WANT_ASYNC) ? FLAG_READ_ASYNC : FLAG_READ_SYNC);
            } else {
                m_flags |= FLAG_MODE_WAIT;
            }
        }
    }
    if ((m_flags & (FLAG_OPEN | FLAG_READ_ASYNC)) == FLAG_READ_ASYNC) setOpenInit();
    if ((m_flags & (FLAG_READ_FILE | FLAG_READ_SYNC)) == FLAG_READ_SYNC) {
        release();
        if (m_flags & FLAG_READ_SYNC) m_flags |= FLAG_READ_FILE;
    }
}

bool DrResMdoSeamRead::isRead() {
    if (m_flags & FLAG_READ_ASYNC) {
        for (int i = 0; i < 8; i++) {
            if (DevFileTh::rfIsBusy(m_handles[i])) return true;
        }
        return false;
    }
    if (m_flags & FLAG_READ_SYNC) {
        for (int i = 0; i < 8; i++) {
            if (m_handles[i] != nullptr) return true;
        }
    }
    return false;
}

void DrResMdoSeamRead::readCancel() {}

bool DrResMdoSeamRead::read(int& idx, unsigned int ofs, unsigned int size, DrResMdoSeamMemObj* obj) {
    int no = getFileHandleNum();
    if (no == -1) return false;
    unsigned short bit = 1 << no;
    m_readDoneBits &= ~bit;
    m_readWaitBits |= bit;
    int readSize = (int)size + ((int)size % 0x40 != 0 ? 0x40 - (int)size % 0x40 : 0);
    DevFileParamTh param;
    param.pad_4c = ofs;
    param.pad_50 = readSize;
    param.m_buffer = obj->m_pData;
    param.m_size = obj->m_size;
    param.m_prio = DrMan::get()->m_seamReadPrio;
    if (!(m_flags & FLAG_READ_ASYNC)) {
        param.m_path = m_path;
        param.m_listener = this;
        m_handles[no] = DevFileTh::readFile(param);
    } else {
        DevFileTh::rfRead(m_handles[no], param);
    }
    idx = no;
    return true;
}

int DrResMdoSeamRead::getFileHandleNum() {
    if (m_flags & FLAG_READ_SYNC) {
        for (int i = 0; i < 8; i++) {
            if (!(m_readWaitBits & (1 << i)) && m_handles[i] == nullptr) return i;
        }
    } else if (m_flags & FLAG_READ_ASYNC) {
        for (int i = 0; i < 8; i++) {
            if (!(m_readWaitBits & (1 << i)) && !DevFileTh::rfIsBusy(m_handles[i])) return i;
        }
    }
    return -1;
}

bool DrResMdoSeamRead::OnFileEvent(EventFileTh* event) {
    for (int i = 0; i < 8; i++) {
        if (m_handles[i] == event->m_handle && event->m_kind == 2) {
            m_readDoneBits |= 1 << i;
            if (m_flags & FLAG_READ_SYNC) m_handles[i] = nullptr;
            return true;
        }
    }
    return false;
}

int DrResMdoSeamRead::getReadMax() {
    int num = 0;
    if (m_flags & FLAG_READ_SYNC) {
        for (int i = 0; i < 8; i++) {
            if (!(m_readWaitBits & (1 << i)) && m_handles[i] == nullptr) num++;
        }
    } else if (m_flags & FLAG_READ_ASYNC) {
        for (int i = 0; i < 8; i++) {
            if (!(m_readWaitBits & (1 << i)) && !DevFileTh::rfIsBusy(m_handles[i])) num++;
        }
    }
    return num;
}

int DrResMdoSeamTexList::SEAMRES_TEXLIST_CNTMAX = 0x3C;

DrResMdoSeamTexList::DrResMdoSeamTexList(int no)
    : m_prev(nullptr), m_next(nullptr), m_memObj(nullptr), m_texture(nullptr), pad_28(nullptr), m_buf(nullptr),
      m_no(no), m_cnt(0), pad_3B(0), m_dataIdx(0), m_num(0) {}

DrResMdoSeamTexList::~DrResMdoSeamTexList() {
    release();
    m_memObj = nullptr;
}

void DrResMdoSeamTexList::release() {
    if (m_buf != nullptr) {
        for (int i = 0; i < m_num; i++) {
            m_texture[i].release();
        }
        if (m_buf != nullptr) {
            mtl::MemManager::deallocate(m_buf, 0, false);
            m_buf = nullptr;
        }
    }
    pad_28 = nullptr;
    m_num = 0;
}

void DrResMdoSeamTexList::setListCnt(int cnt) { SEAMRES_TEXLIST_CNTMAX = cnt; }

int DrResMdoSeamTexture::SEAMRES_NOM_CNTMAX = 0x78;
int DrResMdoSeamTexture::SEAMRES_HEIGHT_CNTMAX = 0x3C;

DrResMdoSeamTexture::DrResMdoSeamTexture(int no)
    : m_prev(nullptr), m_next(nullptr), m_memObj(nullptr), m_heightMemObj(nullptr), m_heightOffset(0), m_no(no),
      m_dataIdx(0), m_cnt(0), m_readIn(0), m_heightCnt(0), m_heightReady(0) {}

DrResMdoSeamTexture::~DrResMdoSeamTexture() {
    release();
    m_memObj = nullptr;
}

void DrResMdoSeamTexture::release() {
    m_texture.release();
    m_heightMemObj = nullptr;
    m_heightReady = 0;
}

bool DrResMdoSeamTexture::update() {
    m_readIn = 0;
    if (++m_cnt >= SEAMRES_NOM_CNTMAX) return true;
    if (m_memObj->m_flags & 2) m_readIn = 1;
    return false;
}

bool DrResMdoSeamTexture::updateHeight() { return ++m_heightCnt >= SEAMRES_HEIGHT_CNTMAX; }

void DrResMdoSeamTexture::createTexture(int size) {
    m_heightMemObj = nullptr;
    grlib::CGLibTexture::createTextureImagePtrs(m_texture, m_memObj->m_pData, size, false, nullptr, false);
    m_cnt = 0;
    m_heightCnt = 0;
    m_heightReady = 0;
}

void DrResMdoSeamTexture::createHeightMoveTexture(int offset, unsigned int size) {
    grlib::CGLibTexture::changeTextureImagePtrs(m_texture, m_heightMemObj->m_pData + offset, size);
    m_cnt = 0;
    m_heightCnt = 0;
    m_heightOffset = offset;
}

void DrResMdoSeamTexture::createHeightTexture(int size, int size2) {
    grlib::CGLibTexture::createMixTextureImagePtrs(m_texture, m_memObj->m_pData, size, size2, false, nullptr, false);
}

void DrResMdoSeamTexture::resetTexture(int size) {
    m_heightReady = 0;
    m_heightMemObj = nullptr;
    grlib::CGLibTexture::createTextureImagePtrs(m_texture, m_memObj->m_pData, size, false, nullptr, false);
}

void DrResMdoSeamTexture::changeMemTexture(int size) {
    grlib::CGLibTexture::changeTextureImagePtrs(m_texture, m_memObj->m_pData, size);
}

void DrResMdoSeamTexture::changeMemTexture(int size, int size2) {
    grlib::CGLibTexture::changeMixTextureImagePtrs(m_texture, m_memObj->m_pData, size, size2);
}

DrResMdoSeamVertex::DrResMdoSeamVertex(int no)
    : m_prev(nullptr), m_next(nullptr), m_memObj(nullptr), m_vertex(nullptr), m_no(no), m_cnt(0), m_dataIdx(0),
      m_readIn(0) {}

DrResMdoSeamVertex::~DrResMdoSeamVertex() { release(); }

void DrResMdoSeamVertex::release() {
    if (m_vertex != nullptr) {
        delete m_vertex;
        m_vertex = nullptr;
    }
}

bool DrResMdoSeamVertex::update() {
    m_readIn = 0;
    if (++m_cnt >= SEAMRES_CNTMAX) return true;
    if (m_memObj->m_flags & 2) m_readIn = 1;
    return false;
}

void DrResMdoSeamVertex::createVertex() {
    release();
    m_vertex = new (DrMan::getIns()->m_resHandle, nullptr, 0, 4, false) DrResMdoVertex(m_memObj->m_pData);
    m_cnt = 0;
    m_readIn = 0;
}

void DrResMdoSeamVertex::changeMemVertex() {
    if (m_vertex != nullptr) m_vertex->changeMemVertex(m_memObj->m_pData);
}

int DrResMdoSeamVertex::SEAMRES_CNTMAX = 0x3C;

DrResMdoSeamWrkBase::DrResMdoSeamWrkBase()
    : m_matRes(nullptr), m_matWork(nullptr), m_vertexList(nullptr), m_shadowCacheDone(0), m_cacheFlags(0),
      m_bufNum(0), m_readSize(0), m_nodeBits(nullptr), m_nodeWork(nullptr), m_memObj(nullptr), m_instans(nullptr),
      m_outFrame(0), m_fadeAlpha(0), m_vertexNum(0) {}

DrResMdoSeamWrkBase::~DrResMdoSeamWrkBase() { release(); }

void DrResMdoSeamWrkBase::release() {
    if (m_vertexList != nullptr) {
        for (int i = 0; i < m_vertexNum; i++) {
            VertexEntry& entry = m_vertexList[i];
            if (entry.vertex != nullptr) {
                delete entry.vertex;
                entry.vertex = nullptr;
            }
            entry.memObj = nullptr;
        }
    }
    DrResMdoAlpTbl* instans = m_instans;
    if (instans != nullptr) {
        instans->m_inst.release();
        instans->m_inst.~CGLibVtxInstans();
        m_instans = nullptr;
    }
    m_vertexList = nullptr;
    m_vertexNum = 0;
    m_nodeBits = nullptr;
    m_nodeWork = nullptr;
    for (int i = 0; i < m_bufNum; i++) {
        if (m_bufList[i] != nullptr) {
            mtl::MemManager::deallocate(m_bufList[i], 0, false);
            m_bufList[i] = nullptr;
        }
    }
    m_bufNum = 0;
    if (m_matRes != nullptr) {
        mtl::MemManager::deallocate(m_matRes, 0, false);
        m_matRes = nullptr;
    }
    if (m_matWork != nullptr) {
        mtl::MemManager::deallocate(m_matWork, 0, false);
        m_matWork = nullptr;
    }
    m_memObj = nullptr;
}

void DrResMdoSeamWrkBase::releaseCache(DrMdoCtlSeamBaseMap* ctl) {
    if (m_vertexList != nullptr) {
        for (int i = 0; i < m_vertexNum; i++) {
            VertexEntry& entry = m_vertexList[i];
            DrResMdoSeamMemObj* memObj = entry.memObj;
            if (entry.vertex != nullptr) {
                delete entry.vertex;
                entry.vertex = nullptr;
            }
            entry.memObj = nullptr;
            if (memObj != nullptr) {
                ctl->releaseFreeSeamMemObj(memObj);
            }
        }
    }
    m_vertexList = nullptr;
    m_nodeBits = nullptr;
    m_nodeWork = nullptr;
    m_vertexNum = 0;
    release();
}

void DrResMdoSeamWrkBase::calcCacheInfo() {
    for (int i = 0; i < m_vertexNum; i++) {
        if (isVertexReady(i)) {
            VertexEntry& entry = m_vertexList[i];
            if (entry.memObj->m_flags & 2) {
                const unsigned char* data = entry.memObj->m_pData;
                entry.vertex->changeMemVertex(data);
            }
        }
    }
    if (!(m_cacheFlags & 0x200)) {
        for (int i = 0; i < m_vertexNum; i++) {
            if (isVertexReady(i)) {
                m_nodeWork[i >> 5] |= 1 << (i & 31);
            } else {
                m_nodeWork[i >> 5] &= ~(1 << (i & 31));
            }
        }
    } else {
        const MdlCount* count = m_mdlCount;
        for (int i = 0; i < count->m_num; i++) {
            if (isVertexReady(i) || isVertexReady(i + count->m_num)) {
                m_nodeWork[i >> 5] |= 1 << (i & 31);
            } else {
                m_nodeWork[i >> 5] &= ~(1 << (i & 31));
            }
        }
    }
}

bool DrResMdoSeamWrkEnv::update(const mm::Vec3&, bool force) {
    m_flags &= ~FLAG_READ;
    if (m_matRes == nullptr) {
        return false;
    }
    if (force) {
        return true;
    }
    if (m_memObj->m_flags & 2) {
        m_flags |= FLAG_READ;
    }
    return false;
}

DrResMdoSeamWrkInst::~DrResMdoSeamWrkInst() { release(); }

void DrResMdoSeamWrkInst::release() {
    if (m_posInsts != nullptr) {
        int num = m_header->m_etcNum;
        for (int i = 0; i <= num; i++) {
            DrResMdoSeamWrkPosInst& pos = m_posInsts[i];
            if (pos.m_entryNum != 0) {
                for (int j = 0; j < pos.m_entryNum; j++) {
                    DrResMdoSeamWrkPosInst::Entry& entry = pos.m_entries[j];
                    if (entry.m_user != nullptr) {
                        entry.m_user->m_entry = nullptr;
                        entry.m_user = nullptr;
                    }
                }
                pos.m_entryNum = 0;
            }
            pos.m_memObj = nullptr;
            if (pos.m_buf != nullptr) {
                mtl::MemManager::deallocate(pos.m_buf, 0, false);
                pos.m_buf = nullptr;
            }
        }
        m_posInsts = nullptr;
        m_posInstNum = 0;
    }
    if (m_pPair != nullptr) {
        m_pPair->m_pPair = nullptr;
    }
    m_pPair = nullptr;
    for (int i = 0; i < m_bufNum; i++) {
        if (m_bufList[i] != nullptr) {
            mtl::MemManager::deallocate(m_bufList[i], 0, false);
            m_bufList[i] = nullptr;
        }
    }
    m_bufNum = 0;
    if (m_pWrkMatRes != nullptr) {
        mtl::MemManager::deallocate(m_pWrkMatRes, 0, false);
        m_pWrkMatRes = nullptr;
    }
    if (pad_58 != nullptr) {
        mtl::MemManager::deallocate(pad_58, 0, false);
        pad_58 = nullptr;
    }
    if (m_vertex != nullptr) {
        delete m_vertex;
        m_vertex = nullptr;
    }
    m_memObj = nullptr;
    m_shadowCacheDone = 0;
}

void DrResMdoSeamWrkInst::releaseCache(DrMdoCtlSeamInstMap* ctl) {
    int num = m_header->m_etcNum;
    for (int i = 0; i < num; i++) {
        if (m_etcBits[i >> 5] & (1 << (i & 0x1F))) {
            DrResMdoSeamMemObj* memObj = m_posInsts[i + 1].m_memObj;
            if (memObj != nullptr) {
                ctl->releaseFreeSeamMemObj(memObj);
            }
            DrResMdoSeamWrkPosInst& pos = m_posInsts[i + 1];
            if (pos.m_entryNum != 0) {
                for (int j = 0; j < pos.m_entryNum; j++) {
                    DrResMdoSeamWrkPosInst::Entry& entry = pos.m_entries[j];
                    if (entry.m_user != nullptr) {
                        entry.m_user->m_entry = nullptr;
                        entry.m_user = nullptr;
                    }
                }
                pos.m_entryNum = 0;
            }
            pos.m_memObj = nullptr;
            if (pos.m_buf != nullptr) {
                mtl::MemManager::deallocate(pos.m_buf, 0, false);
                pos.m_buf = nullptr;
            }
        }
    }
    release();
}

void DrResMdoSeamWrkInst::changeMemCall() {
    const MdsSeamInstMapHead* header = reinterpret_cast<const MdsSeamInstMapHead*>(m_memObj->m_pData);
    m_header = header;
    const unsigned char* top = reinterpret_cast<const unsigned char*>(header);
    m_baseData = reinterpret_cast<const DrResMdoSeamWrkPosInst::BaseData*>(top + header->m_baseOfs);
    const unsigned char* base = reinterpret_cast<const unsigned char*>(m_baseData);
    pad_30 = base + *reinterpret_cast<const unsigned int*>(base + 0x8);
    pad_38 = base + *reinterpret_cast<const unsigned int*>(base + 0x10);
    if (header->m_vertexOfs != 0 && m_vertex != nullptr) {
        m_vertex->changeMemVertex(top + header->m_vertexOfs);
    }
    DrResMdoSeamWrkPosInst* pos = m_posInsts;
    const DrResMdoSeamWrkPosInst::BaseData* data = m_baseData;
    const unsigned char* p = reinterpret_cast<const unsigned char*>(data);
    pos->m_data = p;
    pos->m_posTbl = reinterpret_cast<const DrResMdoSeamWrkPosInst::PosRecord*>(p + data->m_posOfs);
    pos->m_tbl18 = p + data->m_ofs28;
    pos->m_tbl10 = p + data->m_ofs20;
    if (data->m_subOfs != 0) {
        const DrResMdoSeamWrkPosInst::SubTbl* sub = reinterpret_cast<const DrResMdoSeamWrkPosInst::SubTbl*>(p + data->m_subOfs);
        pos->m_sub = sub;
        pos->m_subTbl10 = p + sub->m_ofs10;
        pos->m_subTbl0 = p + sub->m_ofs0;
        pos->m_subTbl8 = p + sub->m_ofs8;
    }
    [](DrResMdoSeamWrkPosInst* p) {
        for (int j = 0; j < p->m_entryNum; j++) {
            p->m_entries[j].m_pos = &p->m_posTbl[j];
        }
    }(pos);
    unsigned int headOfs = data->m_headOfs;
    if (headOfs != 0) {
        DrResMdoSeamWrkPosInst::HeadBlock* head = pos->m_head;
        const unsigned char* posData = pos->m_data;
        head->m_data = posData;
        head->m_body = posData + *reinterpret_cast<const unsigned int*>(posData + headOfs);
    }
}

void DrResMdoSeamWrkInst::calcCacheInfo() {
    for (int i = 1; i < m_posInstNum; i++) {
        DrResMdoSeamWrkPosInst* pos = m_posInstList[i];
        if (pos->m_memObj->m_flags & 2) {
            const unsigned char* p = pos->m_memObj->m_pData;
            const DrResMdoSeamWrkPosInst::EtcData* data = reinterpret_cast<const DrResMdoSeamWrkPosInst::EtcData*>(p);
            pos->m_data = p;
            pos->m_posTbl = reinterpret_cast<const DrResMdoSeamWrkPosInst::PosRecord*>(p + data->m_posOfs);
            pos->m_tbl18 = p + data->m_ofs14;
            pos->m_tbl10 = p + data->m_ofsC;
            if (data->m_subOfs != 0) {
                const DrResMdoSeamWrkPosInst::SubTbl* sub = reinterpret_cast<const DrResMdoSeamWrkPosInst::SubTbl*>(p + data->m_subOfs);
                pos->m_sub = sub;
                pos->m_subTbl10 = p + sub->m_ofs10;
                pos->m_subTbl0 = p + sub->m_ofs0;
                pos->m_subTbl8 = p + sub->m_ofs8;
            }
            [](DrResMdoSeamWrkPosInst* p) {
                for (int j = 0; j < p->m_entryNum; j++) {
                    p->m_entries[j].m_pos = &p->m_posTbl[j];
                }
            }(pos);
            unsigned int headOfs = data->m_headOfs;
            if (headOfs != 0) {
                DrResMdoSeamWrkPosInst::HeadBlock* head = pos->m_head;
                const unsigned char* top = pos->m_data;
                head->m_data = top;
                head->m_body = top + *reinterpret_cast<const unsigned int*>(top + headOfs);
            }
        }
    }
}

bool DrResMdoSeamWrkInst::setEtcPosCache(mtl::ALLOC_HANDLE handle, int cacheIdx, DrResMdoSeamMemObj* memObj,
                                         const DrResMdoInstAnmObj* anm) {
    if (m_cacheFlags & 5) {
        return false;
    }
    const MdsSeamInstMapHead* header = m_header;
    const EtcInfo* info = reinterpret_cast<const EtcInfo*>(reinterpret_cast<const unsigned char*>(header) + header->m_etcOfs);
    for (int i = 0; i < header->m_etcNum; i++, info++) {
        if (info->m_cacheIdx == cacheIdx) {
            m_etcBits[i >> 5] |= 1 << (i & 0x1F);
            m_posInsts[i + 1].setupEtcInstPos(i, memObj, handle, anm);
            m_posInstList[m_posInstNum] = &m_posInsts[i + 1];
            m_posInstNum++;
            m_shadowCacheDone = 0;
            return true;
        }
    }
    return false;
}

DrResMdoSeamWrkLight::DrResMdoSeamWrkLight()
    : m_prev(nullptr), m_next(nullptr), m_envObj(nullptr), m_memObj(nullptr), m_dataIdx(0), m_id(0), pad_38(0),
      pad_3A(0) {}

DrResMdoSeamWrkLight::~DrResMdoSeamWrkLight() { release(); }

void DrResMdoSeamWrkInst::beginMdl() { m_mdlCnt = 0; }

void DrResMdoSeamWrkLight::release() {
    if (m_envObj != nullptr) {
        m_envObj->release();
        m_envObj = nullptr;
    }
    m_memObj = nullptr;
    pad_3A = 0;
}

void DrResMdoSeamWrkLight::setupWork(const MdsSeamLgtMapData* data) {
    m_envObj = DrMan::getIns()->m_curEnvMan->createObj(m_memObj->m_pData);
    m_data = data;
    pad_38 = 0;
    pad_3A = 0;
    m_id = data->id;
}

DrResMdoSeamWrkLow::~DrResMdoSeamWrkLow() { release(); }

void DrResMdoSeamWrkLow::release() {
    grlib::CGLibVtxInstans* instans = m_instans;
    if (instans != nullptr) {
        instans->release();
        instans->~CGLibVtxInstans();
        m_instans = nullptr;
    }
    if (m_matRes != nullptr) {
        mtl::MemManager::deallocate(m_matRes, 0, false);
        m_matRes = nullptr;
    }
    if (m_buf2 != nullptr) {
        mtl::MemManager::deallocate(m_buf2, 0, false);
        m_buf2 = nullptr;
    }
    m_num = 0;
    m_memObj = nullptr;
}


void DrResMdoVtxMeshObj::setActive(bool active, unsigned int count) {
    if (active) {
        if (!m_active) {
            m_flags |= 0x10000 << DrMan::s_nDblStockIdx;
            m_flags &= ~(0x40000 << DrMan::s_nDblIdx);
            m_countMax = count;
        }
    } else {
        m_flags |= 0x40000 << DrMan::s_nDblStockIdx;
        m_flags &= ~(0x10000 << DrMan::s_nDblIdx);
    }
}

void DrResMdoVtxMeshObj::resourceInit(DrResMdoVertex* vertex) {
    DrResMdoVertex::EtcBlock* etc = vertex->m_etc;
    unsigned int num = 0;
    if (etc != nullptr) {
        m_vertex = etc->vertex;
        m_uniform = etc->uniform;
        num = m_vertex->m_num;
    }
    m_vtxNum = num;
}

void DrResMdoVtxMeshObj::update(const mm::Mat44& mtx, float a, float step, float scale) {
    updateInit(mtx, scale);
    if ((m_flags & 1) && m_vtxNum != 0) {
        updateCount(step);
        updateUniform(mtx, a, step, scale);
        m_mtx = mtx;
    }
}

void DrResMdoVtxMeshObj::updateInit(const mm::Mat44& mtx, float scale) {
    if (m_flags & (0x10000 << DrMan::s_nDblIdx)) {
        m_flags &= ~(0x10000 << DrMan::s_nDblIdx);
        m_active = true;
    }
    if (m_flags & (0x40000 << DrMan::s_nDblIdx)) {
        m_flags &= ~(0x40000 << DrMan::s_nDblIdx);
        m_active = false;
    }
    if (m_vtxNum == 0) {
        m_active = false;
    }
    if (m_vtxNum != 0 && m_active && m_val130 * scale > 0.01f) {
        m_flags = (m_flags & ~0xD) | 1;
    } else if (m_flags & 1) {
        m_flags |= 8;
        if (m_flags & 4) {
            m_flags &= ~1;
        }
    }
    if (m_flags & 1) {
        if (!(m_flags & 2)) {
            m_oneBlock.setup(m_countMax * 0x20);
            m_oneBlock.updateData();
            m_dblBlock.setup(0x130);
            m_buf = static_cast<float*>(
                mtl::MemManager::allocate(DrMan::get()->m_allocHandle, m_countMax * 8UL, 4, false, "no name", 0));
            m_flags |= 2;
            m_mtx = mtx;
        }
    } else {
        if (m_flags & 2) {
            m_oneBlock.release();
            m_dblBlock.release();
            if (m_buf != nullptr) {
                mtl::MemManager::deallocate(m_buf, 0, false);
                m_buf = nullptr;
            }
        }
        m_flags &= ~0xF;
    }
}

void DrResMdoVtxMeshObj::stmRender(bool hasNode) {
    if (!(m_flags & 1) || (m_count1 == 0 && m_count3 == 0)) {
        return;
    }
    DrShdDataList* list = DrMan::getIns()->m_shdMan->m_dataList;
    DrResShdStreamOut* stm = list->getStmOutObj(7);
    grlib::CGLibPolygon::setRasterizer(1);
    unsigned int num = m_vtxNum < m_val110 ? m_vtxNum : m_val110;
    if (m_count3 != 0) {
        m_count3 = 0;
        DrShdDataObj* data = stm->m_data;
        unsigned int mode = hasNode ? 2 : 1;
        data->setDeclarationIdx(data->getDeclarationOfs("CALC_MODE"), mode);
        stm->m_data->setupShader(0u);
        if (hasNode) {
            list->m_boneStmOut.setStorageBuffer(1);
            list->m_oldBoneStmOut.setStorageBuffer(2);
        }
        m_uniform->setUniformBlock(stm->m_shaderSel[1]);
        m_dblBlock.setUniformBlock(stm->m_shaderSel[0]);
        if (m_count2 + num > m_vtxNum) {
            unsigned int count = m_vtxNum - m_count2;
            m_oneBlock.setStorageBuffer(0);
            grlib::CGLibCtlVertex::setVertex(*m_vertex, m_vertex->m_stride * m_count2);
            grlib::CGLibCtlVertex::renderVertex(static_cast<GrlPrimitiveType>(0), count);
            count = m_count2 + num - m_vtxNum;
            m_oneBlock.setStorageBuffer(0);
            grlib::CGLibCtlVertex::setVertex(*m_vertex);
            grlib::CGLibCtlVertex::renderVertex(static_cast<GrlPrimitiveType>(0), count);
        } else {
            m_oneBlock.setStorageBuffer(0);
            grlib::CGLibCtlVertex::setVertex(*m_vertex, m_vertex->m_stride * m_count2);
            grlib::CGLibCtlVertex::renderVertex(static_cast<GrlPrimitiveType>(0), num);
        }
        m_count2 = (m_count2 + num) % m_vtxNum;
        grlib::CGLibCtlShader::setMemoryBarrierBit(1);
    }
    if (m_count1 != 0) {
        DrShdDataObj* data = stm->m_data;
        data->setDeclarationIdx(data->getDeclarationOfs("CALC_MODE"), 3);
        stm->m_data->setupShader(1u);
        m_dblBlock.setUniformBlock(stm->m_shaderSel[0]);
        if (m_count0 + m_count1 > m_countMax) {
            unsigned int count = m_countMax - m_count0;
            m_oneBlock.setStorageBuffer(0, m_count0 * 0x20, count * 0x20);
            grlib::CGLibCtlVertex::setUniformVertex(m_oneBlock, 0x20, m_count0 * 0x20, 0, 0);
            grlib::CGLibCtlVertex::renderVertex(static_cast<GrlPrimitiveType>(0), count);
            count = m_count0 + m_count1 - m_countMax;
            m_oneBlock.setStorageBuffer(0);
            grlib::CGLibCtlVertex::setUniformVertex(m_oneBlock, 0x20, 0, 0, 0);
            grlib::CGLibCtlVertex::renderVertex(static_cast<GrlPrimitiveType>(0), count);
        } else {
            m_oneBlock.setStorageBuffer(0, m_count0 * 0x20, m_count1 * 0x20);
            grlib::CGLibCtlVertex::setUniformVertex(m_oneBlock, 0x20, m_count0 * 0x20, 0, 0);
            grlib::CGLibCtlVertex::renderVertex(static_cast<GrlPrimitiveType>(0), m_count1);
        }
        grlib::CGLibCtlShader::setMemoryBarrierBit(1);
    }
    grlib::CGLibPolygon::setRasterizer(0);
}

bool DrResMdoVtxMeshObj::isRender() const {
    if (!(m_flags & 1)) {
        return false;
    }
    if (m_count1 == 0 && m_count3 == 0) {
        return false;
    }
    return true;
}

void DrResMdoVtxMeshObj::alpRender() {
    if (!(m_flags & 1) || m_count1 == 0) {
        return;
    }
    DrAPCache* cache = DrMan::get()->m_apCache;
    DrShdDataList* list = DrMan::get()->m_shdMan->m_dataList;
    DrShdDataObj* shader = list->getPostShdObj(0x3F);
    cache->setupCulling(static_cast<DrApCullType>(2));
    cache->setupDepthStencil(0, 0, 0, 2);
    cache->setupAlphaBlend(2);
    DrMan::get()->m_pixlMan->selectGBuffRenderTarget(0xC0);
    list->bindShdEffVtx();
    shader->setupShader(0u);
    DrCalcViewWork* view = DrMan::get()->m_calcMan->m_pViewWork;
    unsigned int ofs = shader->getCurrentShader().getUniformBlockOfs("U_Static");
    view->m_staticBlock.setUniformBlock(ofs);
    ofs = shader->getCurrentShader().getUniformBlockOfs("U_Pam");
    m_dblBlock.setUniformBlock(ofs);
    unsigned int max = m_countMax;
    if (m_count0 + m_count1 > max) {
        unsigned int num = max - m_count0;
        grlib::CGLibCtlVertex::setUniformVertex(m_oneBlock, 0x20, m_count0 * 0x20, 1, 1);
        list->renderEffVtx(num);
        num = m_count0 + m_count1 - m_countMax;
        grlib::CGLibCtlVertex::setUniformVertex(m_oneBlock, 0x20, 0, 1, 1);
        list->renderEffVtx(num);
    } else {
        grlib::CGLibCtlVertex::setUniformVertex(m_oneBlock, 0x20, m_count0 * 0x20, 1, 1);
        list->renderEffVtx(m_count1);
    }
}

void DrResMdoVtxMeshObj::release(DrResMdoVtxMeshObj*& obj) {
    DrResMdoVtxMeshObj* p = obj;
    if (p != nullptr) {
        p->m_oneBlock.release();
        p->m_dblBlock.release();
        if (p->m_buf != nullptr) {
            mtl::MemManager::deallocate(p->m_buf, 0, false);
            p->m_buf = nullptr;
        }
        p->~DrResMdoVtxMeshObj();
        obj = nullptr;
    }
}

unsigned int DrResMdoVtxMeshObj::calcWorkSize(const unsigned char*) { return 0x140; }

void DrResMdoSeamWrkBase::beginRender() {
    m_selectVertex = -1;
    m_matRes->m_pVertex = nullptr;
}

void DrResMdoSeamWrkBase::endRender() { m_matRes->m_pVertex = nullptr; }

void DrResMdoSeamWrkBase::selectVertex(int index) {
    if (m_selectVertex != index) {
        m_matRes->m_pVertex = m_vertexList[index].vertex;
        m_matRes->m_pVertex->beginVertexSetup();
        m_selectVertex = index;
    }
}

void DrResMdoSeamWrkBase::callShadowCacheBaseUpdate(unsigned long mask) {
    for (unsigned long i = 0; i < 36; i++) {
        if ((1UL << i) & mask) {
            memset(m_shadowCacheBuf[i], 0, m_shadowCacheBufSize);
        }
    }
    m_shadowCacheDone &= ~mask;
}

bool DrResMdoSeamWrkBase::seachShadowBaseMapRender(DrPixlShadowCacheObj& cache, DrMdoCtlSeamBaseMap* ctl) {
    if (m_shadowCacheDone & cache.m_cacheBit) {
        return false;
    }
    if (!(m_header->m_flags & 4)) {
        unsigned int idx = cache.m_cacheIdx;
        m_curShadowCacheBuf = m_shadowCacheBuf[idx];
        beginRender();
        bool hit = seachShadowBaseMapRenderChild(cache, ctl, m_baseMapTree);
        endRender();
        if (hit) {
            return true;
        }
    }
    m_shadowCacheDone |= cache.m_cacheBit;
    return false;
}

void DrResMdoSeamWrkBase::seachDefShadowBaseMapRender(DrPixlShadowObj* shadow, DrMdoCtlSeamBaseMap* ctl) {
    if (!(m_header->m_flags & 4)) {
        beginRender();
        seachDefShadowBaseMapRenderChild(shadow, ctl, m_baseMapTree);
        endRender();
    }
}

void DrResMdoVertex::beginVertexSetup() { m_bindVertex = -1; }

DrResMdoVertex::DrResMdoVertex(const unsigned char* data)
    : m_pPrev(nullptr), m_pNext(nullptr), m_resData(data), m_state(1), m_work(nullptr), m_stream(nullptr) {
    setupVertex(data);
}

DrResMdoVertex::~DrResMdoVertex() { vertexRelease(); }

void DrResMdoVertex::update() {
    if (m_stream != nullptr) {
        DrCalcStmListObj::ResTexObj* res = m_stream->getResVertexObj();
        if (res->m_flags & 1) {
            changeMemVertex(res->m_pData);
        }
    }
}

int DrResMdoVertex::getVertexMax(int index) const { return m_vertex[index].m_num; }

void DrResMdoVertex::render(int index) { m_index[index].drawIndex(); }

void DrResMdoVertex::renderIns(int index, int instances) { m_index[index].drawInsIndex(instances); }

grlib::CGLibVtxVertex* DrResMdoVertex::getWeightVertex() { return &m_vertex[m_weight->vertexNo]; }

int DrResMdoVertex::setWeightVertexBind(int index) {
    const VertexHead* head = reinterpret_cast<const VertexHead*>(m_vtxData);
    if (head->weightVertexNo[index] == 0) {
        return 0;
    }
    grlib::CGLibCtlVertex::setVertex(m_vertex[head->weightVertexNo[index]]);
    m_bindVertex = head->weightVertexNo[index];
    return m_vertex[head->weightVertexNo[index]].m_num;
}

const DrResMdoVertex::WeightInfo* DrResMdoVertex::getWeightVertexInfo(int no, int lv) {
    const unsigned short* table = reinterpret_cast<const unsigned short*>(m_vtxData + m_weight->tableOffset);
    unsigned int info = table[lv * 9 + no];
    if (info == 0) return nullptr;
    return reinterpret_cast<const WeightInfo*>(m_vtxData + m_weight->infoOffset + (info - 1) * sizeof(WeightInfo));
}

void DrResMdoVertex::setEtcVertexBind(int index, int slot) {
    m_bindVertex = -1;
    grlib::CGLibCtlVertex::setAddVertex(m_etcVertex[m_bindTbl[index].vertexNo], 0, slot, 0);
}

void DrResMdoVertex::setMofBlendVertexBind(grlib::CGLibOneUniformArray* array, int index, int slot) {
    m_bindVertex = -1;
    unsigned int no = m_bindTbl[index].uniformNo;
    grlib::CGLibCtlVertex::setUniformVertex(array->m_pArray[no], m_etcData[no].stride, 0, slot, 0);
}

void DrResMdoVertex::setVertexBind(int index) {
    if (m_bindVertex != index) {
        grlib::CGLibCtlVertex::setVertex(m_vertex[index]);
        m_bindVertex = index;
    }
}

}  // namespace ml


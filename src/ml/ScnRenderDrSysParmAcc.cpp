#include "classes/ml/DrMdoMat.h"
#include "classes/ml/ScnRender.h"
#include "classes/ml/ScnRenderDrSys.h"
#include "classes/ml/DrMan.h"
#include "classes/cloud/CloudMan.h"
#include "ml/DrIniSys.h"
#include "ml/DrPixlPostParm.h"
#include "ml/ScnRenderDrSysParmAcc.h"
#include "ml/ScnRenderDrViewCtrl.h"
#include "classes/ml/ScnObjModelDrSys.h"
#include "ml/MdoWrkMatRes.h"
#include "classes/ml/DrMdlObj.h"
#include "classes/ml/DrMdoCtlNom.h"
#include "ml/DrResEtcParams.h"
#include "ml/DrResMdoMeshObj.h"
#include "ml/DrResMdoVtxMeshObj.h"
#include "ml/DrCreator.h"
#include "ml/DrEnvColiMan.h"
#include "ml/DrEnvironmentMan.h"
#include "ml/ScnObjAccResMdlInfo.h"
#include "ml/ScnObjAccResNode.h"
#include "ml/ScnObjAccEtcParams.h"
#include "ml/ScnObjAccResSubMesh.h"
#include "ml/ScnObjAccVolumeFade.h"
#include "ml/ScnObjAccMdlParticle.h"
#include "ml/ScnObjAccGpuCheck.h"
#include "ml/ScnObjAccStmReadObj.h"
#include "ml/ScnRenderDrEnvColi.h"
#include "ml/ScnObjAccRimBloom.h"
#include "ml/DrStmReadObj.h"
#include "classes/ml/ScnObjModelDrSysStandard.h"
#include "classes/ml/ScnObjLightDrSys.h"
#include "classes/ml/ScnObjClipDySys.h"
#include "classes/ml/ScnObjIBLDr.h"
#include "classes/ml/ScnObjEnvColiDr.h"
#include "ml/ScnObjAccSeamPos.h"
#include "ml/ScnObjAccSeamEtcPos.h"
#include "classes/ml/DrMdoCtlPos.h"
#include "nn/os.h"
#include "classes/grlib/CGLibManager.h"
#include "classes/grlib/context/CGLibSystemContext.h"
#include "grlib/CGLibMemHandle.h"
#include "grlib/CGLibVtxInstans.h"
#include "grlib/CGLibVtxOneInstans.h"
#include "grlib/CGLibVtxVertex.h"
#include "grlib/CGLibVtlMemPool.h"
#include "grlib/CGLibVtxStmOut.h"
#include <string.h>

namespace grlib {

CGLibVtxInstans::CGLibVtxInstans() { m_base = 0; }

CGLibVtxInstans::~CGLibVtxInstans() { CGLibMemHandle::free(m_mem); }

void CGLibVtxInstans::release() { CGLibMemHandle::free(m_mem); }

void CGLibVtxInstans::createInstansBuffer(int size) {
    CGLibMemHandle::free(m_mem);
    m_size = size;
    m_frameSize = m_size / 2;
    CGLibMemHandle::allocVertex(m_mem, size);
    context::CGLibSystemContext::sys()->getVertexGpuAddress(m_gpuAddress, m_mem);
}

void CGLibVtxInstans::beginInstansBuff() {
    m_base = CGLibManager::s_nDblNowIdx * m_frameSize;
    m_offset = 0;
    m_flushed = 0;
}

void CGLibVtxInstans::updateInstansBuff() {
    unsigned int size = m_offset - m_flushed;
    if (size != 0) {
        nn::os::FlushDataCache(static_cast<unsigned char*>(m_mem.m_pMem) + (m_base + m_flushed), size);
        m_flushed = m_offset;
    }
}

void* CGLibVtxInstans::getNextInstansBuff() { return static_cast<unsigned char*>(m_mem.m_pMem) + (m_offset + m_base); }

CGLibVtxOneInstans::CGLibVtxOneInstans() {}

CGLibVtxOneInstans::~CGLibVtxOneInstans() { CGLibMemHandle::free(m_mem); }

void CGLibVtxOneInstans::createInstansBuffer(int size) {
    CGLibMemHandle::free(m_mem);
    m_size = size;
    CGLibMemHandle::allocVertex(m_mem, size);
    context::CGLibSystemContext::sys()->getVertexGpuAddress(m_gpuAddress, m_mem);
}

void CGLibVtxOneInstans::beginInstansBuff() {
    m_offset = 0;
    m_flushed = 0;
}

void CGLibVtxOneInstans::updateInstansBuff() {
    if (m_offset != m_flushed) {
        nn::os::FlushDataCache(static_cast<unsigned char*>(m_mem.m_pMem) + m_flushed, m_offset - m_flushed);
        m_flushed = m_offset;
    }
}

void* CGLibVtxOneInstans::getBuff() { return m_mem.m_pMem; }

CGLibVtxStmOut::CGLibVtxStmOut() {}

CGLibVtxStmOut::~CGLibVtxStmOut() { CGLibMemHandle::free(m_mem); }

void CGLibVtxStmOut::release() { CGLibMemHandle::free(m_mem); }

unsigned int CGLibVtxStmOut::getSize() { return m_size; }

CGLibVtxVertex::CGLibVtxVertex() : m_size(0), m_stride(0), m_num(0) {}

CGLibVtxVertex::~CGLibVtxVertex() { CGLibMemHandle::free(m_mem); }

void CGLibVtxVertex::release() { CGLibMemHandle::free(m_mem); }

void CGLibVtxVertex::delayRelease() { context::CGLibSystemContext::sys()->releaseDelayVertex(m_mem); }

void CGLibVtxVertex::createVertexBuff(unsigned int size, unsigned int stride) {
    CGLibMemHandle::free(m_mem);
    m_size = size;
    m_stride = stride;
    m_num = size / stride;
    CGLibMemHandle::allocVertex(m_mem, size + (-size & 3));
    context::CGLibSystemContext::sys()->getVertexGpuAddress(m_gpuAddress, m_mem);
}

void CGLibVtxVertex::createMemVertexBuff(CGLibVtlMemPool* pool, unsigned int offset, unsigned int size,
                                         unsigned int stride) {
    CGLibMemHandle::free(m_mem);
    m_size = size;
    m_stride = stride;
    m_num = size / stride;
    CGLibMemHandle::setMemBuff(m_mem, pool->m_pMem + offset);
    m_gpuAddress = pool->m_gpuAddress + offset;
}

void CGLibVtxVertex::createCopyVertexBuff(const void* vertices, unsigned int size, unsigned int stride) {
    CGLibMemHandle::free(m_mem);
    m_num = size / m_stride;
    m_size = size;
    m_stride = stride;
    CGLibMemHandle::allocVertex(m_mem, size + (-size & 3));
    memcpy(m_mem.m_pMem, vertices, size);
    nn::os::FlushDataCache(m_mem.m_pMem, size);
    context::CGLibSystemContext::sys()->getVertexGpuAddress(m_gpuAddress, m_mem);
}

void CGLibVtxVertex::resetVertexBuff(CGLibVtlMemPool* pool, unsigned int offset) {
    CGLibMemHandle::setMemBuff(m_mem, pool->m_pMem + offset);
    m_gpuAddress = pool->m_gpuAddress + offset;
}

void CGLibVtxVertex::lock(void** ppBuffer, unsigned int* pSize) {
    *ppBuffer = m_mem.m_pMem;
    *pSize = m_size;
}

void CGLibVtxVertex::unlock() { nn::os::FlushDataCache(m_mem.m_pMem, m_size); }

void CGLibVtxVertex::unlock(unsigned int offset, unsigned int size) {
    nn::os::FlushDataCache(static_cast<unsigned char*>(m_mem.m_pMem) + offset, size);
}

}  // namespace grlib


namespace ml {
ScnObjAccResMdlInfo::ScnObjAccResMdlInfo(ScnObjModel* model) {
    m_drMdl = nullptr;
    m_drMdl = static_cast<ScnObjModelDrSys*>(model)->m_pMdlObj;
}

int ScnObjAccResMdlInfo::isGpuRender() const { return m_drMdl->isGpuRender(); }

void ScnObjAccResMdlInfo::setAlwaysMiddleTexStm(bool on) { m_drMdl->setAlwaysMiddleTexStm(on); }

void ScnObjAccResMdlInfo::setGpuClip(bool on) { m_drMdl->setGpuClip(on); }

void ScnObjAccResMdlInfo::setAlwaysTexStm(bool on) { m_drMdl->setAlwaysTexStm(on); }

void ScnObjAccResMdlInfo::setDblBuffAlpha(bool on) { m_drMdl->setDblBuffAlpha(on); }

void ScnObjAccResMdlInfo::setSpAlphaMode(bool on) { m_drMdl->setSpAlphaMode(on); }

void ScnObjAccResMdlInfo::setCamCheckMode(bool on) { m_drMdl->setCamCheckMode(on); }

bool ScnObjAccResMdlInfo::isCamCheckResl() const { return m_drMdl->isCamCheckResl(); }

void ScnObjAccResMdlInfo::createAfterImage(const DrMdlAfterImageParams& params) {
    if (m_drMdl->m_mdlType != 0) {
        return;
    }
    static_cast<DrMdoCtlNom*>(m_drMdl)->createAfterImage(
        params.m_params0[0], params.m_params0[1], params.m_params0[2], params.m_color0, params.m_params1[0],
        params.m_params1[1], params.m_params1[2], params.m_color1, params.m_params2[0], params.m_params2[1],
        params.m_params2[2]);
}

void ScnObjAccResMdlInfo::releaseAfterImage() {
    if (m_drMdl->m_mdlType != 0) {
        return;
    }
    static_cast<DrMdoCtlNom*>(m_drMdl)->releaseAfterImage();
}

ScnObjAccResNode::ScnObjAccResNode() : m_drMdl(nullptr) {}

ScnObjAccResNode::ScnObjAccResNode(ScnObjModel* model) : m_drMdl(static_cast<ScnObjModelDrSys*>(model)->m_pMdlObj) {}

void ScnObjAccResNode::setDrMdl(DrMdlObj* mdl) { m_drMdl = mdl; }

int ScnObjAccResNode::getBoneMax() const { return m_drMdl->getNodeMax(); }

int ScnObjAccResNode::getBoneIndex(const char* name) const { return m_drMdl->getNodeIdx(name); }

const char* ScnObjAccResNode::getBoneName(int index) const {
    if (index < 0) {
        return nullptr;
    }
    return m_drMdl->getNodeName(index);
}

void ScnObjAccResNode::setBoneMat(int index, const mm::Mat44& mat) { m_drMdl->setResBoneMat(index, mat); }

mm::Mat44* ScnObjAccResNode::getBoneMatPtr(int index) { return m_drMdl->getResBoneMatPtr(index); }

ScnObjAccEtcParams::ScnObjAccEtcParams(ScnObjModel* model) {
    DrMdlObj* mdl = static_cast<ScnObjModelDrSys*>(model)->m_pMdlObj;
    if (mdl->m_mdlType != 0) {
        m_table = nullptr;
    } else {
        m_table = static_cast<DrMdoCtlNom*>(mdl)->m_etcParams;
    }
}

unsigned int ScnObjAccEtcParams::getMax() const {
    if (m_table == nullptr) {
        return 0;
    }
    return m_table->m_num;
}

const char* ScnObjAccEtcParams::getName(unsigned int index) const {
    if (m_table == nullptr) {
        return nullptr;
    }
    if (index >= m_table->m_num) {
        return nullptr;
    }
    return m_table->m_strBase + m_table->m_names[index].m_nameOfs;
}

int ScnObjAccEtcParams::getIndex(const char* name) const {
    if (m_table != nullptr) {
        for (unsigned long i = 0; i < m_table->m_num; i++) {
            if (strcmp(name, m_table->m_strBase + m_table->m_names[i].m_nameOfs) == 0) {
                return i;
            }
        }
    }
    return -1;
}

void ScnObjAccEtcParams::setParams(unsigned int index, float value) {
    if (m_table != nullptr && index < m_table->m_num) {
        m_table->m_params[index].setParams(value);
    }
}

void ScnObjAccEtcParams::setPreParams(unsigned int index, float value) {
    if (m_table != nullptr && index < m_table->m_num) {
        m_table->m_params[index].setPreParams(value);
    }
}

void ScnObjAccEtcParams::setInitParams(unsigned int index, float value) {
    if (m_table != nullptr && index < m_table->m_num) {
        m_table->m_params[index].setInitParams(value);
    }
}

void ScnObjAccEtcParams::setRimBloom(bool on) {
    if (m_table != nullptr) {
        m_table->m_flags = !on ? (m_table->m_flags & ~1) : (m_table->m_flags | 1);
    }
}

ScnObjAccResSubMesh::ScnObjAccResSubMesh(ScnObjModel* model) {
    m_mesh = nullptr;
    DrMdlObj* mdl = static_cast<ScnObjModelDrSys*>(model)->m_pMdlObj;
    if (mdl->m_mdlType == 0 && mdl->m_pWrkMatRes != nullptr) {
        MdoWrkMatRes* res = mdl->m_pWrkMatRes;
        m_mesh = static_cast<DrMdoCtlNom*>(mdl)->m_mesh;
        const MdoMdlData* data = res->m_pMdlData;
        m_subMesh = reinterpret_cast<const char*>(data) + data->m_subMeshOfs;
    }
}

int ScnObjAccResSubMesh::getExtMax() const {
    if (m_mesh == nullptr) {
        return 0;
    }
    return m_mesh->m_num;
}

int ScnObjAccResSubMesh::getExtIdx(const char* name) const {
    if (m_mesh == nullptr) {
        return -1;
    }
    return m_mesh->getIdx(name);
}

const char* ScnObjAccResSubMesh::getExtName(int index) const {
    DrResMdoMeshParts* parts = m_mesh->m_parts;
    return parts[static_cast<unsigned int>(index)].m_name;
}

void ScnObjAccResSubMesh::setExtAlpha(int index, float alpha) {
    DrResMdoMeshParts* parts = m_mesh->m_parts;
    parts[static_cast<unsigned int>(index)].setDefAlpha(alpha);
}

ScnObjAccVolumeFade::ScnObjAccVolumeFade(ScnObjModel* model) : m_material(static_cast<ScnObjModelDrSys*>(model)->m_pMdlObj) {}

ScnObjAccVolumeFade::~ScnObjAccVolumeFade() {}

int ScnObjAccVolumeFade::getMax() const {
    if (m_material == nullptr) {
        return 0;
    }
    return m_material->getVanishEffectMax();
}

void ScnObjAccVolumeFade::setRatio(float ratio, int index) {
    if (m_material == nullptr) {
        return;
    }
    if (index >= 0) {
        MdoVanishEffectWrk* wrk = m_material->getVanishEffectWrk(index, DrMan::s_nDblIdx);
        if (wrk != nullptr) {
            wrk->m_ratio = ratio;
            wrk->m_flags |= 0x100;
        }
    } else {
        for (unsigned int i = 0; i < m_material->getVanishEffectMax(); i++) {
            MdoVanishEffectWrk* wrk = m_material->getVanishEffectWrk(i, DrMan::s_nDblIdx);
            wrk->m_ratio = ratio;
            wrk->m_flags |= 0x100;
        }
    }
}

float ScnObjAccVolumeFade::getRatio(unsigned int index) const {
    float ratio = 0.0f;
    if (m_material != nullptr) {
        MdoVanishEffectWrk* base = m_material->getVanishEffectWrk(index, 2);
        if (base != nullptr) {
            MdoVanishEffectWrk* wrk = m_material->getVanishEffectWrk(index, DrMan::s_nDblIdx);
            if (!(wrk->m_flags & 0x100)) {
                wrk = m_material->getVanishEffectWrk(index, DrMan::s_nDblStockIdx);
                if (!(wrk->m_flags & 0x100)) {
                    return base->m_ratio;
                }
            }
            ratio = wrk->m_ratio;
        }
    }
    return ratio;
}

ScnObjAccRimBloom::ScnObjAccRimBloom(ScnObjModel* model) : m_drMdl(static_cast<ScnObjModelDrSys*>(model)->m_pMdlObj) {}

ScnObjAccRimBloom::~ScnObjAccRimBloom() {}

void ScnObjAccRimBloom::setRimColor(const mm::Col3& color) {
    if (m_drMdl != nullptr) {
        MdoRimBloomWrk* wrk = m_drMdl->getRimBloomWrk(DrMan::s_nDblIdx);
        if (wrk != nullptr) {
            wrk->m_color = color;
            wrk->m_flags |= 1;
        }
    }
}

void ScnObjAccRimBloom::setRimEmissive(float emissive) {
    if (m_drMdl != nullptr) {
        MdoRimBloomWrk* wrk = m_drMdl->getRimBloomWrk(DrMan::s_nDblIdx);
        if (wrk != nullptr) {
            wrk->m_emissive = emissive;
            wrk->m_flags |= 8;
        }
    }
}

void ScnObjAccRimBloom::setRimPower(float power) {
    if (m_drMdl != nullptr) {
        MdoRimBloomWrk* wrk = m_drMdl->getRimBloomWrk(DrMan::s_nDblIdx);
        if (wrk != nullptr) {
            wrk->m_power = power;
            wrk->m_flags |= 2;
        }
    }
}

void ScnObjAccRimBloom::setBlackRatio(float ratio) {
    if (m_drMdl != nullptr) {
        MdoRimBloomWrk* wrk = m_drMdl->getRimBloomWrk(DrMan::s_nDblIdx);
        if (wrk != nullptr) {
            wrk->m_blackRatio = ratio;
            wrk->m_flags |= 4;
        }
    }
}

ScnObjAccMdlParticle::ScnObjAccMdlParticle(ScnObjModel* model) {
    DrMdlObj* mdl = static_cast<ScnObjModelDrSys*>(model)->m_pMdlObj;
    if (mdl->m_mdlType != 0) {
        m_vtxMesh = nullptr;
    } else {
        m_vtxMesh = static_cast<DrMdoCtlNom*>(mdl)->m_vtxMesh;
    }
}

void ScnObjAccMdlParticle::setActive(bool active, unsigned int index) {
    if (m_vtxMesh != nullptr) {
        m_vtxMesh->setActive(active, index);
    }
}
ScnObjAccSeamPos::ScnObjAccSeamPos(ScnObjModel* model) : m_anm(nullptr) {
    DrMdlObj* mdl = static_cast<ScnObjModelDrSys*>(model)->m_pMdlObj;
    if (mdl->m_mdlType == 3) {
        m_anm = &static_cast<DrMdoCtlSeam*>(mdl)->m_instAnm;
    } else if (mdl->m_mdlType == 1) {
        m_anm = &static_cast<DrMdoCtlPos*>(mdl)->m_instAnm;
    } else {
        m_anm = nullptr;
    }
}

unsigned int ScnObjAccSeamPos::getMax() const {
    if (m_anm == nullptr) {
        return 0;
    }
    if (m_anm->m_header == nullptr) {
        return 0;
    }
    return m_anm->m_header->partsMax;
}

ScnObjAccPartsPos ScnObjAccSeamPos::getObj(unsigned int index) {
    if (m_anm == nullptr) {
        return ScnObjAccPartsPos(nullptr);
    }
    DrResMdoInstPartsObj* obj;
    if (m_anm->m_header == nullptr) {
        obj = nullptr;
    } else {
        obj = m_anm->m_parts[index];
    }
    return ScnObjAccPartsPos(obj);
}

void ScnObjAccPartsPos::setMatrix(const mm::Mat44& mat) { m_obj->setMatrix(mat); }
void ScnObjAccPartsPos::getMatrix(mm::Mat44& mat) { m_obj->getMatrix(mat); }
const char* ScnObjAccPartsPos::getName() const { return m_obj->m_names + m_obj->m_info->nameOfs; }
unsigned int ScnObjAccPartsPos::getID() const { return m_obj->m_info->id; }
bool ScnObjAccPartsPos::isPosAnm() const { return (m_obj->m_info->flags >> 4) & 1; }
bool ScnObjAccPartsPos::isNodeAnm() const { return (m_obj->m_info->flags >> 3) & 1; }
bool ScnObjAccPartsPos::isPosMatrix() const { return (m_obj->m_info->flags & 0x30) != 0; }
bool ScnObjAccPartsPos::isRandomStart() const { return (m_obj->m_info->flags >> 1) & 1; }
bool ScnObjAccPartsPos::isSwitch() const { return (m_obj->m_info->flags >> 7) & 1; }
bool ScnObjAccPartsPos::isColiOff() const { return (m_obj->m_flags >> 3) & 1; }
bool ScnObjAccPartsPos::isColiSkipData() const { return (m_obj->m_flags >> 4) & 1; }
void ScnObjAccPartsPos::setAlpha(float alpha) { m_obj->m_alpha = alpha; }
bool ScnObjAccPartsPos::isLoop() const { return (m_obj->m_flags >> 2) & 1; }
void ScnObjAccPartsPos::setPosFrame(float frame) { m_obj->setPosFrame(frame); }
float ScnObjAccPartsPos::getPosFrame() const { return m_obj->getPosFrame(); }
float ScnObjAccPartsPos::getPosMaxFrame() const { return m_obj->getPosMaxFrame(); }
float ScnObjAccPartsPos::getPosStartFrame() const { return m_obj->getPosStartFrame(); }
void ScnObjAccPartsPos::setNodeFrame(float frame) { m_obj->setNodeFrame(frame); }
float ScnObjAccPartsPos::getNodeFrame() const { return m_obj->getNodeFrame(); }
float ScnObjAccPartsPos::getNodeMaxFrame() const { return m_obj->getNodeMaxFrame(); }
float ScnObjAccPartsPos::getNodeStartFrame() const { return m_obj->getNodeStartFrame(); }
void ScnObjAccPartsPos::getAnmMatrix(mm::Mat44* mat) const { m_obj->getAnmMatrix(*mat); }
unsigned char ScnObjAccPartsPos::getSwitchID() const { return m_obj->getSwitchID(); }
void ScnObjAccPartsPos::setSwitchID(unsigned int id) { m_obj->setSwitchID(id); }

ScnObjAccSeamEtcPos::ScnObjAccSeamEtcPos(ScnObjModel* model) : m_list(nullptr) {
    DrMdlObj* mdl = static_cast<ScnObjModelDrSys*>(model)->m_pMdlObj;
    if (mdl->m_mdlType != 3) {
        m_list = nullptr;
    } else {
        m_list = &static_cast<DrMdoCtlSeam*>(mdl)->m_etcPos;
    }
}

unsigned int ScnObjAccSeamEtcPos::getObjMax() const {
    if (m_list == nullptr) {
        return 0;
    }
    return m_list->m_max;
}

ScnObjAccPartsEtcPos ScnObjAccSeamEtcPos::getObj(unsigned int index) {
    return ScnObjAccPartsEtcPos(&m_list->m_entries[index]);
}

const char* ScnObjAccPartsEtcPos::getObjName() const {
    const DrMdoCtlSeam::EtcPos::Data* data = m_entry->m_data;
    return reinterpret_cast<const char*>(data) + data->objNameOfs;
}
const char* ScnObjAccPartsEtcPos::getEffName() const {
    const DrMdoCtlSeam::EtcPos::Data* data = m_entry->m_data;
    return reinterpret_cast<const char*>(data) + data->effNameOfs;
}
float ScnObjAccPartsEtcPos::getRange() const { return m_entry->m_data->range; }
float ScnObjAccPartsEtcPos::getNearClip(unsigned int index) const { return m_entry->m_data->nearClip[index]; }
float ScnObjAccPartsEtcPos::getFarClip(unsigned int index) const { return m_entry->m_data->farClip[index]; }
unsigned int ScnObjAccPartsEtcPos::getMatrixMax() const { return m_entry->m_data->matrixMax; }
const mm::Mat44& ScnObjAccPartsEtcPos::getMatrix(unsigned int index) const {
    const DrMdoCtlSeam::EtcPos::Data* data = m_entry->m_data;
    const mm::Mat44* mats = reinterpret_cast<const mm::Mat44*>(reinterpret_cast<const char*>(data) + data->matrixOfs);
    return mats[index];
}
bool ScnObjAccPartsEtcPos::isDisp(unsigned int index) const {
    if (m_entry->m_dispOn) {
        return true;
    }
    const DrMdoCtlSeam::EtcPos::Data* data = m_entry->m_data;
    unsigned short dispIdx =
        reinterpret_cast<const unsigned short*>(reinterpret_cast<const char*>(data) + data->dispIdxOfs)[index];
    if (dispIdx != 0 && (DrMan::getIns()->m_dispOffBits[dispIdx >> 5] & (1 << (dispIdx & 0x1F))) != 0) {
        return false;
    }
    return true;
}

ScnObjAccGpuCheck::ScnObjAccGpuCheck(DrGpuCheckBase* check) : m_check(check) {}

void ScnObjAccGpuCheck::setPos(const mm::Vec3& pos, float radius) { m_check->setPos(pos, radius); }

bool ScnObjAccGpuCheck::isRender() const { return m_check->isRender(); }

DrGpuCheckBase* ScnObjAccGpuCheck::create(unsigned int arg) {
    DrCreator creator;
    return creator.createGpuCheckObj(arg);
}

ScnObjAccStmReadObj::ScnObjAccStmReadObj(DrStmReadObj* obj) : m_obj(obj) {}

void ScnObjAccStmReadObj::readType(ReadType type) {
    switch (type) {
    case READ_TYPE_0:
        m_obj->m_readType = 0;
        break;
    case READ_TYPE_1:
        m_obj->m_readType = 1;
        break;
    case READ_TYPE_2:
        m_obj->m_readType = 2;
        break;
    }
}

DrStmReadCheck* ScnObjAccStmReadObj::create(const char* name) {
    DrCreator creator;
    return creator.createStmLoadObj(name);
}


void ScnRenderDrSys::setDefaultEvn() {}

void ScnRenderDrSys::applyCamera(ml::ScnObjCam*) {}

void ScnRenderDrSys::update() {}

void ScnRenderDrSys::setup(const ml::ScnSetup*) {}

ScnRenderDrSys::~ScnRenderDrSys() {
    if (m_drMan != nullptr) {
        delete m_drMan;
        m_drMan = nullptr;
    }
}

void ScnRenderDrSys::applyBegin() { m_drMan->begin(); }

void ScnRenderDrSys::applyEnd() { m_drMan->end(); }

void ScnRenderDrSys::applyLoopCnt() { m_drMan->loopCnt(); }

void ScnRenderDrSys::applyUpdate(int arg) { m_drMan->apply(arg); }

void ScnRenderDrSys::applyRender(int arg) { m_drMan->render(arg); }

void ScnRenderDrSys::tail() { m_drMan->tail(); }

void ScnRenderDrSys::setMdlDblPause(bool pause) { m_drMan->m_mdlDblPause = pause; }

void ScnRenderDrSys::setGlbSpd(float speed) { m_drMan->m_glbSpd = speed; }

void ScnRenderDrSys::setCallBack(IDrDrawCallback* callback) { m_drMan->setCallBack(callback); }

void ScnRenderDrSys::releaseCallBack(IDrDrawCallback* callback) { m_drMan->releaseCallBack(callback); }

void ScnRenderDrSys::openPixelDebugWindow(WinProc* proc) { m_drMan->openPixelDebugWindow(proc); }

void ScnRenderDrSys::openHisgtramDebugWindow(WinProc* proc) { m_drMan->openHistgramDebugWindow(proc); }

ScnObjModel* ScnRenderDrSys::createMdl(Scn* scn, const void* res, const char* name, int view) {
    if (res == nullptr) {
        return nullptr;
    }
    return ScnObjModelDrSysStandard::create(scn, res, name, view);
}

ScnObj* ScnRenderDrSys::createLgt(Scn* scn, const void* res, int view) { return ScnObjLightDrSys::create(scn, res, view); }

void ScnRenderDrSys::createClip(Scn* scn, const void* res, int view) { ScnObjClipDySys::create(scn, res, view); }

ScnObjIBL* ScnRenderDrSys::createIBL(Scn* scn, const void* res, int view) { return ScnObjIBLDr::create(scn, res, view); }

void ScnRenderDrSys::createEnvColi(Scn* scn, const void* res, int view) { ScnObjEnvColiDr::create(scn, res, view); }

ScnRenderDrEnvColi::ScnRenderDrEnvColi(int view) { m_envColi = DrMan::getIns()->m_envMan[view]->m_envColiMan; }

ScnRenderDrEnvColi::~ScnRenderDrEnvColi() {}

bool ScnRenderDrEnvColi::testEnvColi(const mm::Vec3& pos, float range) {
    return m_envColi->testEnvColi(nullptr, pos, range);
}

int ScnRenderDrEnvColi::getWindId() const { return m_envColi->m_windId; }

bool ScnRenderDrEnvColi::isRoom() const { return (m_envColi->m_flags >> 2) & 1; }

ScnRenderDrSysParmAcc::ScnRenderDrSysParmAcc() : m_drMan(nullptr), m_postParm(nullptr), m_view(0) {
    m_drMan = DrMan::get();
    m_postParm = m_drMan->m_postParm[m_view];
}

ScnRenderDrSysParmAcc::ScnRenderDrSysParmAcc(ScnRenderDrSys* render, int view)
    : m_drMan(nullptr), m_postParm(nullptr) {
    m_drMan = render->m_drMan;
    m_postParm = m_drMan->m_postParm[view];
    m_view = view;
}

void ScnRenderDrSysParmAcc::setDOFOverride(bool enable) { m_postParm->setOverrideDOF(enable); }

void ScnRenderDrSysParmAcc::setToneMap(bool enable) { m_postParm->m_toneMap = enable; }

void ScnRenderDrSysParmAcc::setOverrideToneMap(float value) { m_postParm->setOverrideToneMap(value); }

void ScnRenderDrSysParmAcc::setMotBlurOverride(bool enable) { m_postParm->setOverrideMotBlur(enable); }

void ScnRenderDrSysParmAcc::setMotBlur(bool enable) { m_postParm->m_motBlur = enable; }

void ScnRenderDrSysParmAcc::setMotBlurDefault(bool enable) { m_drMan->m_iniSys->m_motBlurDefault = enable; }

void ScnRenderDrSysParmAcc::setDOF(bool enable) { m_postParm->setDOF(enable); }

bool ScnRenderDrSysParmAcc::isDOF() const { return m_postParm->m_dofOverride || m_postParm->m_dof; }

void ScnRenderDrSysParmAcc::setDoFPixlRatio(float ratio) { m_postParm->setDoFPixlRatio(ratio); }

void ScnRenderDrSysParmAcc::setDoFDistance(float distance) { m_postParm->setDoFDistance(distance); }

void ScnRenderDrSysParmAcc::setDoFRange(float range) { m_postParm->setDoFRange(range); }

void ScnRenderDrSysParmAcc::setDoFStrength(float strength) { m_postParm->setDoFStrength(strength); }

void ScnRenderDrSysParmAcc::setDoFLens(float lens) { m_postParm->setDoFLens(lens); }

void ScnRenderDrSysParmAcc::setDoFBlend(float blend) { m_postParm->setDoFBlend(blend); }

void ScnRenderDrSysParmAcc::setDofHLvMode(bool enable) { m_postParm->setDOFHlv(enable); }

void ScnRenderDrSysParmAcc::setDofPixlLv(int level) {
    DrPixlPostParm* postParm = m_postParm;
    if (level < 0 || level >= 3) {
        postParm->setDoFPixlLv(0);
        return;
    }
    postParm->setDoFPixlLv(level);
}

void ScnRenderDrSysParmAcc::setDOFAutoFocus(bool enable) { m_postParm->setDOFAutoFocus(enable); }

void ScnRenderDrSysParmAcc::setDOFFocusNum(int num) {
    if (num > 11U) {
        num = 0;
    }
    m_postParm->setDoFocusNum(num);
}

void ScnRenderDrSysParmAcc::setDOFFocusMin(float min) { m_postParm->setDofFocusMin(min); }

float ScnRenderDrSysParmAcc::getDoFPixlRatio() const { return m_postParm->m_dofPixlRatio; }

float ScnRenderDrSysParmAcc::getDoFDistance() const { return m_postParm->m_dofDistance; }

float ScnRenderDrSysParmAcc::getDoFRange() const { return m_postParm->m_dofRange; }

float ScnRenderDrSysParmAcc::getDoFStrength() const { return m_postParm->m_dofStrength; }

float ScnRenderDrSysParmAcc::getDoFLens() const { return m_postParm->m_dofLens; }

float ScnRenderDrSysParmAcc::getDoFBlend() const { return m_postParm->m_dofBlend; }

bool ScnRenderDrSysParmAcc::isDofHLvMode() const { return m_postParm->m_dofHLvMode; }

int ScnRenderDrSysParmAcc::getDofPixlLv() const { return m_postParm->m_dofPixlLv; }

bool ScnRenderDrSysParmAcc::isDOFAutoFocus() const { return m_postParm->m_dofAutoFocus; }

int ScnRenderDrSysParmAcc::getDOFFocusNum() const { return m_postParm->m_dofFocusNum; }

float ScnRenderDrSysParmAcc::getDOFFocusMin() const { return m_postParm->m_dofFocusMin; }

void ScnRenderDrSysParmAcc::setPlaneCloudNum(unsigned int num) {
    cloud::CloudMan* cloudMan = DrMan::getIns()->m_cloudMan;
    if (cloudMan != nullptr) {
        cloudMan->setCldNum(num);
    }
}

void ScnRenderDrSysParmAcc::setGlobalWind(const mm::Vec3& power) { m_drMan->setGlobalWind(power); }

void ScnRenderDrSysParmAcc::setAutoReduction(bool enable) { m_drMan->setAutoReduction(enable); }

void ScnRenderDrSysParmAcc::setColorFilterOverride(bool enable) { m_postParm->setOverrideColorFilter(enable); }

void ScnRenderDrSysParmAcc::setColorFilterNum(int num) { m_postParm->setColorFilterNum(num); }

void ScnRenderDrSysParmAcc::setColorFilterFarNum(int num) { m_postParm->setColorFilterFarNum(num); }

void ScnRenderDrSysParmAcc::setColorFilterFrm(float frame) { m_postParm->setColorFilterFrm(frame); }

void ScnRenderDrSysParmAcc::setRainDrop(bool enable) { m_postParm->m_rainDrop = enable; }

void ScnRenderDrSysParmAcc::setTimeVal(float time) { m_drMan->setTimeVal(time); }

void ScnRenderDrSysParmAcc::setWeather(int weather) { m_postParm->m_weather = weather; }

void ScnRenderDrSysParmAcc::setWeatherFrame(float frame) { m_postParm->setWeatherFrame(frame); }

void ScnRenderDrSysParmAcc::getWeatherFrame() const { m_drMan->fn_710071E620(); }

void ScnRenderDrSysParmAcc::setSeamMapAddPosMode(bool enable) { m_drMan->m_seamMapAddPosMode = enable; }

void ScnRenderDrSysParmAcc::setSeamMapReadPos(const mm::Vec3& pos) {
    m_drMan->m_seamMapReadPos = pos;
}

void ScnRenderDrSysParmAcc::setSelectIdDisp(int index, bool off) {
    if (off) {
        m_drMan->offGblIdx(index);
    } else {
        m_drMan->setGblIdx(index);
    }
}

bool ScnRenderDrSysParmAcc::isMdlAllMiddleTexStm() const { return m_drMan->isAllMiddelTexStmChk(); }

bool ScnRenderDrSysParmAcc::isSeamMapRead() const { return m_drMan->isSeamMapStmOk(); }

bool ScnRenderDrSysParmAcc::fn_710070A0DC() { return m_drMan->fn_710071E77C(); }

void ScnRenderDrSysParmAcc::setToonDirLightScale(bool enable) { m_drMan->m_toonDirLightScale = enable; }

void ScnRenderDrSysParmAcc::setToonAmbient(bool enable) {
    if (enable) {
        m_drMan->m_toonAmbient = 3;
    } else {
        m_drMan->m_toonAmbient = 0;
    }
}

void ScnRenderDrSysParmAcc::setPlayerPos(const mm::Vec3& pos) {}

void ScnRenderDrSysParmAcc::setCameraLight(bool enable) { m_drMan->m_cameraLight = enable; }

void ScnRenderDrSysParmAcc::deleteAddRenderView(ScnRenderDrViewCtrl* view) {
    m_drMan->deleteAddRenderSystem(view->m_viewIndex + 1);
}

void ScnRenderDrSysParmAcc::setModelTexture(const ScnRenderDrMdlTexture& texture) {
    DR_MODEL_TEXTURE modelTexture;
    modelTexture.m_texture = texture.m_texture;
    modelTexture.m_enable = texture.m_enable;
    m_drMan->setModelTexture(&modelTexture, texture.m_slot);
}

void ScnRenderDrSysParmAcc::resetModelTexture(unsigned int slot) { m_drMan->resetModelTexture(slot); }

void ScnRenderDrSysParmAcc::setGlassBr(bool enable, unsigned int arg) { m_postParm->setGlassBrk(enable, arg); }

bool ScnRenderDrSysParmAcc::isGlassBr() { return m_postParm->m_glassBr; }

void ScnRenderDrSysParmAcc::setViewRenderSkip(unsigned int view, bool skip) {
    DrMan* drMan = DrMan::get();
    if (skip) {
        drMan->m_viewRenderSkip |= 1 << view;
    } else {
        drMan->m_viewRenderSkip &= ~(1 << view);
    }
}

void ScnRenderDrSysParmAcc::resetScene() { m_postParm->resetScene(); }

void ScnRenderDrSysParmAcc::setAutoResetScene(bool enable) { DrMan::get()->m_autoResetScene = enable; }

void ScnRenderDrSysParmAcc::setGamma(float gamma) { DrMan::get()->m_gamma = gamma; }

void ScnRenderDrSysParmAcc::setCaptureMode(bool enable) {
    DrMan* drMan = DrMan::get();
    if (enable) {
        drMan->m_captureMode[DrMan::s_nDblStockIdx] = 1;
    } else {
        drMan->m_captureMode[DrMan::s_nDblStockIdx] = 2;
    }
}

}  // namespace ml

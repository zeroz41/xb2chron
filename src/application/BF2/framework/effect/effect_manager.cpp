#include "classes/effect/SystemManager.h"
#include "classes/fw/EffectManager.h"
#include "effect/SendParam.h"
#include "classes/fw/EffectCasterSend.h"
#include "classes/effect/SystemManager.h"
#include "classes/fw/EffectManager.h"
#include "classes/fw/EffectCasterBase.h"
#include "classes/fw/EffectPoint.h"
#include "classes/ml/DrMdoMat.h"
#include "classes/ml/DrMdlObj.h"
#include "classes/ml/ScnObjModelDrSys.h"
#include "classes/ml/DrMdoGrpObj.h"
#include "classes/ml/DrMan.h"
#include "ml/DrCreator.h"
#include "classes/fw/Framework.h"
#include "classes/fw/EffectPack.h"
#include "mtl/MemManager.h"
#include "ml/DrLightMan.h"
#include "classes/ml/DrLightObjPnt.h"
#include "classes/ml/DrLightObjSpt.h"
#include "ml/ScnObjAccVolumeFade.h"
#include "classes/fw/AssetManager.h"
#include "classes/fw/EffectData.h"
#include "classes/mm/mtl/IAllocator.h"
#include "ptlib/ParticleSystem.h"
#include "ml/DevFileParamTh.h"
#include "classes/ml/DevFileTh.h"
#include <string.h>

namespace fw {

// the original's new names effect_caster_impl.h: the EffectCasterSend members come from that header
EffectCasterSend* EffectCasterSend::create(EffectCasterBase* caster, mm::mtl::IAllocator* allocator,
                                           unsigned int count) {
#line 196 "D:/Monolithsoft/BF2/prog/application/BF2\\framework/effect/effect_caster_impl.h"
    EffectCasterSend* send = new (allocator, 16, __FILE__, __LINE__) EffectCasterSend(allocator);
#line 32 "D:/Monolithsoft/BF2/prog/application/BF2/framework/effect/effect_manager.cpp"
    if (send) {
        send->m_caster = caster;
        send->m_mtxAndNames[0].reserve(count);
        send->m_mtxAndNames[1].reserve(count);
        MtxAndName entry;
        for (unsigned int i = count; i != 0; i--) {
            send->m_mtxAndNames[0].push_back(entry);
            send->m_mtxAndNames[1].push_back(entry);
        }
    }
    return send;
}

EffectCasterSend::~EffectCasterSend() {}

void EffectCasterSend::tailCopy() {
    int src = effect::SystemManager::getPtr()->m_secondBuffer != 0;
    int dst = effect::SystemManager::getPtr()->m_secondBuffer == 0;
    m_scl[dst] = m_scl[src];
    m_frame[dst] = m_frame[src];
    m_stateName[dst] = m_stateName[src];
}

void EffectCasterSend::sendData(mm::Mat44& mtx, const char* name, int index) {
    if (m_caster != nullptr && effect::SystemManager::getPtr() != nullptr) {
        // the half effect::SystemManager does not read
        MtxAndName* entries;
        if (effect::SystemManager::getPtr()->m_secondBuffer) {
            entries = &m_mtxAndNames[0][0];
        } else {
            entries = &m_mtxAndNames[1][0];
        }
        entries[index].m_mtx = mtx;
        if (name != nullptr) {
            strcpy(entries[index].m_name, name);
        } else {
            strcpy(entries[index].m_name, "root");
        }
        entries[index].m_hash = AssetManager::getHash(entries[index].m_name);
    }
}

void EffectCasterSend::sendDataStateName(const char* name) {
    if (m_caster != nullptr && effect::SystemManager::getPtr() != nullptr) {
        m_stateName[effect::SystemManager::getPtr()->m_secondBuffer ? 1 : 0] = name;
    }
}

const char* EffectCasterSend::getStateName() {
    return m_stateName[!effect::SystemManager::getPtr()->m_secondBuffer].m_str;
}

void* EffectCasterSend::getBindData(unsigned int& size) {
    if (m_caster == nullptr) {
        return nullptr;
    }
    void* data = m_caster->pad_20;
    size = m_caster->pad_28;
    return data;
}

float EffectCasterSend::getMdlFrame() {
    return m_frame[!effect::SystemManager::getPtr()->m_secondBuffer];
}

float EffectCasterSend::getMdlScl() {
    return m_scl[!effect::SystemManager::getPtr()->m_secondBuffer];
}

bool EffectCasterSend::getMdlMat(mm::Mat44& mtx) {
    if (effect::SystemManager::getPtr() == nullptr) {
        return true;
    }
    bool second = effect::SystemManager::getPtr()->m_secondBuffer;
    unsigned int hash = AssetManager::getHash("root");
    if (second) {
        for (unsigned int i = 0; i < m_mtxAndNames[0].size(); i++) {
            if (hash == m_mtxAndNames[0][i].m_hash && strcmp(m_mtxAndNames[0][i].m_name, "root") == 0) {
                mtx = m_mtxAndNames[0][i].m_mtx;
                return true;
            }
        }
    } else {
        for (unsigned int i = 0; i < m_mtxAndNames[1].size(); i++) {
            if (hash == m_mtxAndNames[1][i].m_hash && strcmp(m_mtxAndNames[1][i].m_name, "root") == 0) {
                mtx = m_mtxAndNames[1][i].m_mtx;
                return true;
            }
        }
    }
    return false;
}

bool EffectCasterSend::getEfpMat(mm::Mat44& mtx, const char* name) {
    if (effect::SystemManager::getPtr() != nullptr && name != nullptr) {
        bool second = effect::SystemManager::getPtr()->m_secondBuffer;
        unsigned int hash = AssetManager::getHash(name);
        if (second) {
            for (unsigned int i = 0; i < m_mtxAndNames[0].size(); i++) {
                if (hash == m_mtxAndNames[0][i].m_hash && strcmp(m_mtxAndNames[0][i].m_name, name) == 0) {
                    mtx = m_mtxAndNames[0][i].m_mtx;
                    return true;
                }
            }
        } else {
            for (unsigned int i = 0; i < m_mtxAndNames[1].size(); i++) {
                if (hash == m_mtxAndNames[1][i].m_hash && strcmp(m_mtxAndNames[1][i].m_name, name) == 0) {
                    mtx = m_mtxAndNames[1][i].m_mtx;
                    return true;
                }
            }
        }
        getMdlMat(mtx);
    } else {
        getMdlMat(mtx);
        if (name == nullptr) {
            ptlib::efWng("error EFP null");
        } else {
            ptlib::efWng("error EFP %s", name);
        }
    }
    return false;
}

void* EffectCasterSend::getMdl() {
    m_mdl = static_cast<ml::ScnObjModelDrSys*>(m_caster->m_pModel)->m_pMdlObj;
    return m_mdl;
}

bool EffectManager::initialize() {
    return true;
}

bool EffectManager::isCommonLoaded() {
    return commonLoaded();
}

void EffectManager::addPack(EffectPack* pack) {
    (*m_packMap)[std::string(pack->m_name.m_str)] = pack;
}

void EffectManager::removePack(EffectPack* pack) {
    PackMap::iterator it = m_packMap->find(std::string(pack->m_name.m_str));
    if (it != m_packMap->end()) {
        m_packMap->erase(it);
    }
}

EffectPack* EffectManager::findPack(const char* name) {
    PackMap::iterator it = m_packMap->find(std::string(name));
    if (it != m_packMap->end()) {
        return it.__node_->__value_.__cc.second;
    }
    return nullptr;
}

void EffectManager::addData(EffectData* data) {
    (*m_dataMap)[std::string(data->getName())] = data;
}

void EffectManager::removeData(EffectData* data) {
    DataMap::iterator it = m_dataMap->find(std::string(data->getName()));
    if (it != m_dataMap->end()) {
        m_dataMap->erase(it);
    }
}

void EffectManager::setMasterPause(bool pause) {
    if (m_masterPause != pause && effect::SystemManager::getPtr() != nullptr) {
        m_masterPause = pause;
        effect::SystemManager::getPtr()->es_pause(m_masterPause);
    }
}

void EffectManager::sendCaster(EffectCasterBase* caster, mm::Mat44& mtx, const char* name, int index) {
    for (unsigned long i = 0; i < 32; ++i) {
        for (CasterGroup::iterator it = m_casterGroups[i].begin(); it != m_casterGroups[i].end(); ++it) {
            if (it->m_caster == caster) {
                it->sendData(mtx, name, index);
                return;
            }
        }
    }
}

void EffectManager::sendCaster(EffectCasterBase* caster, float scl) {
    for (unsigned long i = 0; i < 32; ++i) {
        for (CasterGroup::iterator it = m_casterGroups[i].begin(); it != m_casterGroups[i].end(); ++it) {
            if (it->m_caster == caster) {
                if (caster != nullptr && effect::SystemManager::getPtr() != nullptr) {
                    it->m_scl[effect::SystemManager::getPtr()->m_secondBuffer ? 1 : 0] = scl;
                }
                return;
            }
        }
    }
}

void EffectManager::sendCasterFrame(EffectCasterBase* caster, float frame) {
    for (unsigned long i = 0; i < 32; ++i) {
        for (CasterGroup::iterator it = m_casterGroups[i].begin(); it != m_casterGroups[i].end(); ++it) {
            if (it->m_caster == caster) {
                if (caster != nullptr && effect::SystemManager::getPtr() != nullptr) {
                    it->m_frame[effect::SystemManager::getPtr()->m_secondBuffer ? 1 : 0] = frame;
                }
                return;
            }
        }
    }
}

void EffectManager::sendCasterStateName(EffectCasterBase* caster, const char* name) {
    for (unsigned long i = 0; i < 32; ++i) {
        for (CasterGroup::iterator it = m_casterGroups[i].begin(); it != m_casterGroups[i].end(); ++it) {
            if (it->m_caster == caster) {
                it->sendDataStateName(name);
                return;
            }
        }
    }
}

void EffectManager::kill(unsigned int handle) {
    if (handle != 0) {
        effect::SystemManager::getPtr()->es_fade_core(nullptr, handle, 1);
    }
}

void EffectManager::remove(unsigned int handle) {
    if (handle != 0) {
        effect::SystemManager::getPtr()->es_fade_core(nullptr, handle, -1);
    }
}

void EffectManager::dead(unsigned int handle) {
    effect::SystemManager::getPtr()->es_fade_core(nullptr, handle, 0);
}

void EffectManager::fadeOutDead(unsigned int handle) {
    if (handle != 0) {
        effect::SystemManager::getPtr()->es_fade_core(nullptr, handle, 1);
    }
}

void EffectManager::fadeOutDead(unsigned int handle, unsigned int frames) {
    if (handle != 0) {
        effect::SystemManager::getPtr()->es_fade_core(nullptr, handle, frames);
    }
}

void EffectManager::setDisp(unsigned int handle, bool disp) {
    if (handle != 0) {
        effect::SystemManager::getPtr()->es_set_disp(handle, disp);
    }
}

void EffectManager::setAlpha(unsigned int handle, float alpha) {
    if (handle != 0) {
        effect::SystemManager::getPtr()->es_set_alpha(handle, alpha);
    }
}

void EffectManager::setSpeed(unsigned int handle, float speed) {
    if (handle != 0) {
        effect::SystemManager::getPtr()->es_set_speed(handle, speed);
    }
}

void EffectManager::setCategory(unsigned int handle, EF_CATEGORY category) {
    if (handle != 0) {
        effect::SystemManager::getPtr()->es_set_category(handle, category);
    }
}

void EffectManager::setViewnum(unsigned int handle, unsigned int viewnum) {
    if (handle != 0) {
        effect::SystemManager::getPtr()->es_set_viewnum(handle, viewnum);
    }
}

// no handle test here (es_set_param gets every handle). The colour is set again after the scale: the original stores
// it after the matrix copy, where the default constructor's stores would sit before it.
void EffectManager::setParam(unsigned int handle, const mm::Mat44& mtx, const mm::Vec3& scale, unsigned char value) {
    effect::SendParam param;
    param.m_mtx = mtx;
    param.m_scale = scale;
    param.m_color[0] = 1.0f;
    param.m_color[1] = 1.0f;
    param.m_color[2] = 1.0f;
    param.m_color[3] = 1.0f;
    param.m_flagF = value;
    effect::SystemManager::getPtr()->es_set_param(handle, &param);
}

void EffectManager::setParam(unsigned int handle, const mm::Vec3& pos, const mm::Vec3& rot, const mm::Vec3& scale) {
    effect::SendParam param;
    // rot read one angle at a time (x first, then y, then z), the rows as Mat44::setRotXYZ writes them
    float ax = rot.x;
    float sx = ::sinf(ax);
    float cx = ::cosf(ax);
    float ay = rot.y;
    float sy = ::sinf(ay);
    float cy = ::cosf(ay);
    float az = rot.z;
    float sz = ::sinf(az);
    float cz = ::cosf(az);
    mm::Mat44& mtx = param.m_mtx;
    mtx.m[0][0] = cy * cz;
    mtx.m[0][1] = cy * sz;
    mtx.m[0][2] = -sy;
    mtx.m[0][3] = 0.0f;
    mtx.m[1][0] = sx * sy * cz - cx * sz;
    mtx.m[1][1] = sx * sy * sz + cx * cz;
    mtx.m[1][2] = sx * cy;
    mtx.m[1][3] = 0.0f;
    mtx.m[2][0] = cx * sy * cz + sx * sz;
    mtx.m[2][1] = cx * sy * sz - sx * cz;
    mtx.m[2][2] = cx * cy;
    mtx.m[2][3] = 0.0f;
    mtx.m[3][0] = pos.x;
    mtx.m[3][1] = pos.y;
    mtx.m[3][2] = pos.z;
    mtx.m[3][3] = 1.0f;
    param.m_scale = scale;
    param.m_color[0] = 1.0f;
    param.m_color[1] = 1.0f;
    param.m_color[2] = 1.0f;
    param.m_color[3] = 1.0f;
    effect::SystemManager::getPtr()->es_set_param(handle, &param);
}


// as above: the colour set again after the scale
void EffectManager::setParam(unsigned int handle, const mm::Vec3& pos, const mm::Vec3& scale) {
    effect::SendParam param;
    param.m_mtx.setTrans(pos);
    param.m_scale = scale;
    param.m_color[0] = 1.0f;
    param.m_color[1] = 1.0f;
    param.m_color[2] = 1.0f;
    param.m_color[3] = 1.0f;
    effect::SystemManager::getPtr()->es_set_param(handle, &param);
}

// hands the caster's send (the effect system's callback for its model) to the effect; a null caster gets its own
// call (the original's separate argument block for it)
void EffectManager::setParam(unsigned int handle, EffectCasterBase* caster, float rate) {
    if (handle != 0) {
        effect::SystemManager* mgr = effect::SystemManager::getPtr();
        if (caster != nullptr) {
            EffectCasterSend* send = nullptr;
            for (unsigned long i = 0; i < 32; ++i) {
                for (CasterGroup::iterator it = m_casterGroups[i].begin(); it != m_casterGroups[i].end(); ++it) {
                    if (it->m_caster == caster) {
                        send = &*it;
                        goto found;
                    }
                }
            }
        found:
            mgr->es_set_param_cas(handle, send, "", 2, rate, 0);
        } else {
            mgr->es_set_param_cas(handle, nullptr, "", 2, rate, 0);
        }
    }
}

void EffectManager::setMatrix(unsigned int handle, const mm::Mat44& mtx) {
    if (handle != 0) {
        effect::SendParam param;
        param.m_mtx = mtx;
        effect::SystemManager::getPtr()->es_set_param_pos_only(handle, &param);
    }
}

void EffectManager::setParamPosOnly(unsigned int handle, const effect::SendParam* param) {
    if (handle != 0) {
        effect::SystemManager::getPtr()->es_set_param_pos_only(handle, param);
    }
}

void EffectManager::setParamPosOnly2(unsigned int handle, const effect::SendParam* param) {
    if (handle != 0) {
        effect::SystemManager::getPtr()->es_set_param_pos_only2(handle, param);
    }
}

void EffectManager::setParam(unsigned int handle, const effect::SendParam* param) {
    if (handle != 0) {
        effect::SystemManager::getPtr()->es_set_param(handle, param);
    }
}

bool EffectManager::isExist(unsigned int handle) {
    return effect::SystemManager::getPtr()->es_isalive(handle) > 0;
}

int EffectManager::getDeadFlag(unsigned int handle) {
    return effect::SystemManager::getPtr()->es_getDeadFlag(handle);
}

bool EffectManager::isLoop(void* data) const {
    return effect::SystemManager::getPtr()->es_is_loop(data);
}

bool EffectManager::containsCamAxis(void* data) const {
    return effect::SystemManager::getPtr()->es_contais_cam_axis(data);
}

void EffectManager::efSystemStart(const ml::IDrDrawWorkInfo* info) {
    if (pad_2fda != 0 || effect::SystemManager::getPtr() != nullptr) {
        return;
    }
    effect::SystemManager::setUserAllocFunc(effectAllocSys, effectFreeSys, effectAllocRes, effectFreeRes,
                                            effectSysHandle, effectResHandle);
    effect::SystemManager::setUserFileFunc(debugReadFile, debugReadFileEnd);
    effect::SystemManager::setUserOutputString(debugOutputString, warnOutputString);
    effect::SystemManager::setUserDrFunc(createMdl, deleteMdl, createLgt, deleteLgt, setMdlPos, setMdlMatrix,
                                         setMdlColor, setMdlAlpha, setMdlSpeed, setLgtPos, setLgtMatrix, setLgtParam,
                                         debugRenderer, createGroup, destroyGroup);
    effect::SystemManager::create(reinterpret_cast<const ptlib::DrDrawWorkInfoEF*>(info));
}

void* EffectManager::effectAllocSys(void* user, unsigned int size, unsigned int alignment, const char* name,
                                     unsigned int line) {
    return mtl::MemManager::allocate(get()->m_sysHandle, size, alignment, false, "no name", 0);
}

void EffectManager::effectFreeSys(void* user, void* p) {
    mtl::MemManager::deallocate(p, 0, false);
}

void* EffectManager::effectAllocRes(void* user, unsigned int size, unsigned int alignment, const char* name,
                                     unsigned int line) {
    return mtl::MemManager::allocate(get()->m_resHandle, size, alignment, false, "no name", 0);
}

void EffectManager::effectFreeRes(void* user, void* p) {
    mtl::MemManager::deallocate(p, 0, false);
}

mtl::ALLOC_HANDLE EffectManager::effectSysHandle() {
    return get()->m_sysHandle;
}

mtl::ALLOC_HANDLE EffectManager::effectResHandle() {
    return get()->m_resHandle;
}

void EffectManager::remove(EffectCasterBase* caster) {
    effect::SystemManager* mgr = effect::SystemManager::getPtr();
    EffectCasterSend* send = nullptr;
    for (unsigned long i = 0; i < 32; ++i) {
        for (CasterGroup::iterator it = m_casterGroups[i].begin(); it != m_casterGroups[i].end(); ++it) {
            if (it->m_caster == caster) {
                send = &*it;
                goto found;
            }
        }
    }
found:
    mgr->es_remove_cas(send);
}

unsigned int EffectManager::create(const char* name, EffectPack* pack, bool flag) {
    void* efb = search(name, pack);
    if (efb == nullptr) {
        return 0;
    }
    return create(efb, flag);
}

unsigned int EffectManager::create(void* efb, bool flag) {
    if (effect::SystemManager::getPtr() == nullptr) {
        return 0;
    }
    return effect::SystemManager::getPtr()->es_create(efb, flag);
}

unsigned int EffectManager::create(const char* name, EffectPack* pack, const effect::SendParam* param, bool flag) {
    void* efb = search(name, pack);
    if (efb == nullptr) {
        return 0;
    }
    return effect::SystemManager::getPtr()->es_create(efb, param, flag);
}

void* EffectManager::debugReadFile(const char* path, int& size) {
    ml::DevFileParamTh param;
    param.m_hMem = get()->m_resHandle;
    param.m_align = 0x1000;
    param.m_path = path;
    return ml::DevFileTh::readFileBlock(param, &size, nullptr);
}

void EffectManager::debugReadFileEnd(void* data) {
    if (data != nullptr) {
        mtl::MemManager::deallocate(data, 0, false);
    }
}

void EffectManager::debugOutputString(const char* text) {}

void EffectManager::warnOutputString(const char* text) {}

void EffectManager::setMdlPos(void* mdl, void* pos) {
    if (mdl != nullptr && pos != nullptr) {
        static_cast<ml::DrMdlObj*>(mdl)->setOffsetPos(*static_cast<const mm::Vec3*>(pos));
    }
}

void EffectManager::setMdlMatrix(void* mdl, void* matrix) {
    if (mdl != nullptr && matrix != nullptr) {
        static_cast<ml::DrMdlObj*>(mdl)->setMatrix(*static_cast<const mm::Mat44*>(matrix));
    }
}

void EffectManager::setMdlAlpha(void* mdl, float alpha) {
    if (mdl != nullptr) {
        static_cast<ml::DrMdlObj*>(mdl)->setAlpha(alpha);
    }
}

void* EffectManager::search(const char* name, EffectPack* pack) {
    if (pack != nullptr) {
        if (void* efb = pack->searchEfb(name)) {
            return efb;
        }
    }
    for (CommonPack& entry : m_commonPacks) {
        if (EffectPack* common = entry.m_pack.get()) {
            if (void* efb = common->searchEfb(name)) {
                return efb;
            }
        }
    }
    return nullptr;
}

unsigned int EffectManager::createHateRing() {
    void* efb = nullptr;
    for (CommonPack& entry : m_commonPacks) {
        EffectPack* common = entry.m_pack.get();
        if (common != nullptr && (efb = common->searchEfb("cmn_000_000")) != nullptr) {
            break;
        }
    }
    if (efb == nullptr || effect::SystemManager::getPtr() == nullptr) {
        return 0;
    }
    return effect::SystemManager::getPtr()->es_create(efb, true);
}


unsigned int EffectManager::createHateRingVec() {
    void* efb = nullptr;
    for (CommonPack& entry : m_commonPacks) {
        EffectPack* common = entry.m_pack.get();
        if (common != nullptr && (efb = common->searchEfb("cmn_000_001")) != nullptr) {
            break;
        }
    }
    if (efb == nullptr || effect::SystemManager::getPtr() == nullptr) {
        return 0;
    }
    return effect::SystemManager::getPtr()->es_create(efb, true);
}

bool EffectManager::updateHateRingVec(unsigned int handle, const mm::Vec3& pos, const float& angle, const float& scale,
                                      const mm::Col4& color) {
    effect::SendParam param;
    memcpy(param.m_color, &color, sizeof(param.m_color));
    param.m_scale.x = scale;
    mm::Mat44 rot;
    rot.setRotY(angle);
    param.m_mtx = param.m_mtx * rot;
    param.m_mtx.setTransRow(pos);
    param.m_id = 4;
    setParam(handle, &param);
    return true;
}

unsigned int EffectManager::createHateArrow() {
    void* efb = nullptr;
    for (CommonPack& entry : m_commonPacks) {
        EffectPack* common = entry.m_pack.get();
        if (common != nullptr && (efb = common->searchEfb("cmn_000_002")) != nullptr) {
            break;
        }
    }
    if (efb == nullptr || effect::SystemManager::getPtr() == nullptr) {
        return 0;
    }
    return effect::SystemManager::getPtr()->es_create(efb, true);
}

bool EffectManager::updateHateArrow(unsigned int handle, const mm::Vec3& pos, const float& angle, const float& scale,
                                    const mm::Col4& color) {
    effect::SendParam param;
    memcpy(param.m_color, &color, sizeof(param.m_color));
    param.m_scale.x = scale;
    mm::Mat44 rot;
    rot.setRotY(angle);
    param.m_mtx = param.m_mtx * rot;
    param.m_mtx.setTransRow(pos);
    setParam(handle, &param);
    return true;
}

unsigned int EffectManager::createComboBall(unsigned int type) {
    if (type == 0) {
        return 0;
    }
    mm::mtl::FixStr<32> name;
    name.format("cmn_010_%03d", type - 1);
    void* efb = nullptr;
    for (CommonPack& entry : m_commonPacks) {
        EffectPack* common = entry.m_pack.get();
        if (common != nullptr && (efb = common->searchEfb(name.m_str)) != nullptr) {
            break;
        }
    }
    if (efb == nullptr || effect::SystemManager::getPtr() == nullptr) {
        return 0;
    }
    return effect::SystemManager::getPtr()->es_create(efb, true);
}

bool EffectManager::updateComboBall(unsigned int handle, const mm::Vec3& pos, const float& scale) {
    effect::SendParam param;
    param.m_scale.x = scale;
    param.m_mtx.setTrans(pos);
    setParam(handle, &param);
    return true;
}


void EffectManager::KizunaWork::term() {
    if (m_model != nullptr) {
        m_model->setDisp(false);
        m_model->setDeleteCall(ml::DrMan::s_nDblStockIdx);
        m_model = nullptr;
    }
    for (int i = 0; i < 8; ++i) {
        unsigned int handle = m_effects[i];
        if (handle != 0) {
            effect::SystemManager::getPtr()->es_fade_core(nullptr, handle, -1);
            m_effects[i] = 0;
        }
    }
}

unsigned int EffectManager::createKizunaLine() {
    for (unsigned int i = 1; i < 8; ++i) {
        if (!m_kizunaWorks[i].m_inUse) {
            m_kizunaWorks[i].m_inUse = true;
            m_kizunaWorks[i].init();
            return i;
        }
    }
    return 0;
}

void EffectManager::destroyKizunaLine(unsigned int handle) {
    if (handle - 1 < 7) {
        KizunaWork& work = m_kizunaWorks[handle];
        work.m_inUse = false;
        work.m_start = mm::Vec3::zero;
        work.m_end = mm::Vec3::zero;
        if (work.m_model != nullptr) {
            work.m_model->setDisp(false);
        }
        for (int i = 0; i < 8; ++i) {
            unsigned int effect = work.m_effects[i];
            if (effect != 0) {
                effect::SystemManager::getPtr()->es_fade_core(nullptr, effect, -1);
                work.m_effects[i] = 0;
            }
        }
    }
}

void EffectManager::updateKizunaLine(unsigned int handle, const mm::Vec3& start, const mm::Vec3& end,
                                     unsigned int count) {
    if (handle - 1 < 7) {
        KizunaWork& work = m_kizunaWorks[handle];
        work.m_start = start;
        unsigned int n = count == 0 ? 1 : count;
        work.m_end = end;
        work.m_count = n < 7 ? n : 6;
    }
}

void EffectManager::destroyHateRing(unsigned int handle) {
    if (handle != 0) {
        effect::SystemManager::getPtr()->es_fade_core(nullptr, handle, -1);
    }
}

void EffectManager::destroyHateRingVec(unsigned int handle) {
    if (handle != 0) {
        effect::SystemManager::getPtr()->es_fade_core(nullptr, handle, -1);
    }
}

void EffectManager::destroyHateArrow(unsigned int handle) {
    if (handle != 0) {
        effect::SystemManager::getPtr()->es_fade_core(nullptr, handle, -1);
    }
}

void EffectManager::destroyComboBall(unsigned int handle) {
    if (handle != 0) {
        effect::SystemManager::getPtr()->es_fade_core(nullptr, handle, 1);
    }
}

void EffectManager::setMdlColor(void* mdl, void* param) {
    if (mdl == nullptr || param == nullptr) {
        return;
    }
    ml::DrMdlObj* obj = static_cast<ml::DrMdlObj*>(mdl);
    const MdlColorParam* prm = static_cast<const MdlColorParam*>(param);
    mm::Col3 color(prm->m_color.r, prm->m_color.g, prm->m_color.b);
    obj->setAceColor(0, color);
    obj->setAceVal(1, prm->m_aceVal[1]);
    obj->setAceVal(2, prm->m_aceVal[2]);
    obj->m_viewNum = prm->m_viewNum;
    if (prm->m_dispThreshold > 0.01f) {
        obj->setDisp(false);
    } else {
        obj->setDisp(true);
    }
    obj->setAceVal(0, prm->m_aceVal[0]);
}

void EffectManager::setMdlSpeed(void* mdl, void* speed) {
    if (mdl != nullptr && speed != nullptr) {
        static_cast<ml::DrMdlObj*>(mdl)->m_speed = *static_cast<const float*>(speed);
    }
}

void* EffectManager::createGroup(int arg, int viewNum) {
    if (mm::mtl::PtrSingleton<Framework>::sys() == nullptr) {
        return nullptr;
    }
    return ml::DrCreator().createInstantGrp(arg, viewNum);
}

void EffectManager::destroyGroup(void* grp) {
    if (grp != nullptr && mm::mtl::PtrSingleton<Framework>::sys() != nullptr) {
        static_cast<ml::DrMdoGrpObj*>(grp)->setDeleteCall(ml::DrMan::s_nDblStockIdx);
    }
}

void* EffectManager::createMdl(const void* res, const char* name, int index, const void* grp, int option) {
    ml::DrMdlObj* mdl = nullptr;
    if (grp != nullptr && mm::mtl::PtrSingleton<Framework>::sys() != nullptr) {
        mdl = const_cast<ml::DrMdoGrpObj*>(static_cast<const ml::DrMdoGrpObj*>(grp))->createInstantMdl(res, name, option);
        mdl->setMatrix(mm::Mat44::identity);
        mdl->setDisp(true);
        mdl->setOcclusionQuery(false);
    }
    return mdl;
}

void EffectManager::deleteMdl(void* mdl) {
    if (mdl != nullptr && mm::mtl::PtrSingleton<Framework>::sys() != nullptr) {
        static_cast<ml::DrMdlObj*>(mdl)->setDisp(false);
        static_cast<ml::DrMdlObj*>(mdl)->setDeleteCall(ml::DrMan::s_nDblStockIdx);
    }
}

// the original reads the view's light manager before it tests DrMan for null (the order its code keeps)
void* EffectManager::createLgt(unsigned int type, int viewNum) {
    if (mm::mtl::PtrSingleton<Framework>::sys() == nullptr) {
        return nullptr;
    }
    ml::DrMan* dr = ml::DrMan::getIns();
    ml::DrLightMan* lightMan = dr->m_viewLightMan[viewNum];
    if (dr == nullptr || lightMan == nullptr) {
        return nullptr;
    }
    switch (type) {
    case 1:
        return lightMan->createInstantPntLight();
    case 2:
        return lightMan->createInstantSptLight();
    }
    return nullptr;
}

void EffectManager::deleteLgt(unsigned int type, void* lgt) {
    if (lgt == nullptr || mm::mtl::PtrSingleton<Framework>::sys() == nullptr) {
        return;
    }
    ml::DrMan* dr = ml::DrMan::getIns();
    if (dr == nullptr || dr->m_lightMan == nullptr) {
        return;
    }
    switch (type) {
    case 1:
        dr->m_lightMan->releaseInstantPntLight(static_cast<ml::DrLightObjPnt*>(lgt));
        break;
    case 2:
        dr->m_lightMan->releaseInstantSptLight(static_cast<ml::DrLightObjSpt*>(lgt));
        break;
    }
}

// whether a light can be changed: deleteLgt's first test, shared by the setters (the helper and its name are
// inferred: the original tests the value pointer before the light, which only a separate test of the light gives)
static inline bool isLgtUsable(void* lgt) {
    return lgt != nullptr && mm::mtl::PtrSingleton<Framework>::sys() != nullptr;
}

void EffectManager::setLgtPos(unsigned int type, void* lgt, void* pos) {
    if (pos == nullptr || !isLgtUsable(lgt)) {
        return;
    }
    ml::DrMan* dr = ml::DrMan::getIns();
    if (dr == nullptr || dr->m_lightMan == nullptr) {
        return;
    }
    switch (type) {
    case 1:
        static_cast<ml::DrLightObjPnt*>(lgt)->setPos(*static_cast<const mm::Vec3*>(pos));
        break;
    case 2:
        static_cast<ml::DrLightObjSpt*>(lgt)->setPos(*static_cast<const mm::Vec3*>(pos));
        break;
    }
}

void EffectManager::setLgtMatrix(unsigned int type, void* lgt, void* matrix) {
    if (matrix == nullptr || !isLgtUsable(lgt)) {
        return;
    }
    ml::DrMan* dr = ml::DrMan::getIns();
    if (dr == nullptr || dr->m_lightMan == nullptr) {
        return;
    }
    switch (type) {
    case 1:
        static_cast<ml::DrLightObjPnt*>(lgt)->setMat(*static_cast<const mm::Mat44*>(matrix));
        break;
    case 2:
        static_cast<ml::DrLightObjSpt*>(lgt)->setMat(*static_cast<const mm::Mat44*>(matrix));
        break;
    }
}

void EffectManager::setLgtParam(unsigned int type, void* lgt, void* param) {
    if (param == nullptr || !isLgtUsable(lgt)) {
        return;
    }
    ml::DrMan* dr = ml::DrMan::getIns();
    if (dr == nullptr || dr->m_lightMan == nullptr) {
        return;
    }
    const LgtParam* src = static_cast<const LgtParam*>(param);
    switch (type) {
    case 1: {
        ml::DrLightObjPnt* pnt = static_cast<ml::DrLightObjPnt*>(lgt);
        if (src->m_lightParam > -1.0f) {
            pnt->m_lightParam = src->m_lightParam;
        }
        const mm::Col3 color = src->m_color;
        pnt->m_color[0] = color.r;
        pnt->m_color[1] = color.g;
        pnt->m_color[2] = color.b;
        if (src->m_size > -1.0f) {
            pnt->m_size = src->m_size;
        }
        pnt->m_lightParam2 = src->m_lightParam2;
        break;
    }
    case 2: {
        ml::DrLightObjSpt* spt = static_cast<ml::DrLightObjSpt*>(lgt);
        if (src->m_lightParam > -1.0f) {
            spt->m_lightParam = src->m_lightParam;
        }
        const mm::Col3 color = src->m_color;
        spt->m_color[0] = color.r;
        spt->m_color[1] = color.g;
        spt->m_color[2] = color.b;
        if (src->m_size > -1.0f) {
            spt->m_size = src->m_size;
        }
        spt->m_angle = src->m_angle;
        spt->m_lightParam2 = src->m_lightParam2;
        spt->pad_e0 = src->m_param18;
        break;
    }
    default:
        return;
    }
    if (src->m_subtract > 0.0f) {
        static_cast<ml::DrLightObj*>(lgt)->setSubtractOn(true);
    } else {
        static_cast<ml::DrLightObj*>(lgt)->setSubtractOn(false);
    }
}

void EffectManager::addCaster(EffectCasterBase* caster) {
    for (unsigned long i = 0; i < 32; ++i) {
        for (CasterGroup::iterator it = m_casterGroups[i].begin(); it != m_casterGroups[i].end(); ++it) {
            if (it->m_caster == caster) {
                return;
            }
        }
    }
    EffectCasterSend* send = EffectCasterSend::create(caster, caster->m_pAllocator, caster->m_pointCount);
    if (send != nullptr) {
        send->m_point = caster->m_pPoint;
        m_casterGroups[caster->m_layer].push_back(send);
    }
}

void EffectManager::removeCaster(EffectCasterBase* caster) {
    CasterGroup& group = m_casterGroups[caster->m_layer];
    for (CasterGroup::iterator it = group.begin(); it != group.end(); ++it) {
        if (it->m_caster == caster) {
            remove(caster);
            EffectCasterSend* send = it.operator->();  // unchecked (operator* asserts m_node: the original does not)
            group.erase(it);
            delete send;
            return;
        }
    }
}

void EffectManager::changeLayerCaster(EffectCasterBase* caster, unsigned int index, unsigned int layer) {
    CasterGroup& group = m_casterGroups[index];
    for (CasterGroup::iterator it = group.begin(); it != group.end(); ++it) {
        if (it->m_caster == caster) {
            EffectCasterSend* send = it.operator->();  // unchecked, as in removeCaster
            group.erase(it);
            m_casterGroups[layer].push_back(send);
            return;
        }
    }
}

bool EffectManager::getVolumeFadeParam(unsigned int type, ml::VolumeFadeParams& params) {
    if (type < 32) {
        const VolumeFadeParams* src = m_volumeFadeParams[type];
        if (src != nullptr) {
            for (int i = 0; i < 5; ++i) {
                params.m_colors[i] = src->m_colors[i];
                params.m_values0[i] = src->m_values0[i];
                params.m_values1[i] = src->m_values1[i];
                params.m_values2[i] = src->m_values2[i];
            }
            params.m_color0 = mm::Vec3(src->m_color0.r, src->m_color0.g, src->m_color0.b);
            params.m_color1 = mm::Vec3(src->m_color1.r, src->m_color1.g, src->m_color1.b);
            params.m_value0 = src->m_value0;
            params.m_value1 = src->m_value1;
            params.m_value2 = src->m_value2;
            return true;
        }
    }
    return false;
}

void EffectManager::fn_7100179D30(bool flag) {
    effect::SystemManager::getPtr()->fn_710083FF24(flag);
}

void EffectManager::fn_710017658C() {
    pad_2fdb = 1;
    pad_2fd7 = 1;
    pad_2fda = 0;
}

bool EffectManager::fn_71001765AC() {
    return pad_2fdb == 0;
}

void EffectManager::fn_71001765C0() {
    pad_2fdc = 1;
}

bool EffectManager::fn_71001765D0() {
    return pad_2fdc == 0;
}

bool EffectManager::finalize() {
    return fn_71001765E8();
}

// Proposed name, not the original's: the symbols leave it unnamed (lbl_7100B415B0). fn_7100177028's folder.
const char* s_commonEffectDir = "effect/common";

bool EffectManager::fn_7100177028(mm::mtl::FixStr<32>& path) {
    path = s_commonEffectDir;
    if (m_gfManagerFlag) {
        path += "_dlc";
    }
    path += "/";
    return true;
}

void RimBloomCalc::calcEndFrame() {
    if (m_endFrame < m_curves[0].m_keys.back().m_frame) {
        m_endFrame = m_curves[0].m_keys.back().m_frame;
    }
    if (m_endFrame < m_curves[1].m_keys.back().m_frame) {
        m_endFrame = m_curves[1].m_keys.back().m_frame;
    }
    if (m_endFrame < m_curves[2].m_keys.back().m_frame) {
        m_endFrame = m_curves[2].m_keys.back().m_frame;
    }
}

void EffectManager::updateLayer(const UpdateInfo& info, unsigned int layers) {
    for (unsigned long i = 0; i < 32; ++i) {
        if (layers & (1 << i)) {
            for (CasterGroup::iterator it = m_casterGroups[i].begin(); it != m_casterGroups[i].end(); ++it) {
                if (it->m_caster != nullptr && !it->m_caster->m_isDead) {
                    if (it->m_point != nullptr) {
                        it->m_point->update(info);
                    }
                    if (it->m_caster != nullptr) {
                        it->m_caster->update(info);
                    }
                    if (it->m_point != nullptr) {
                        for (int j = 0; j < it->m_point->getPointCount(); ++j) {
                            it->m_point->setDirty(j, true);
                        }
                    }
                }
            }
        }
    }
}

void EffectManager::updateLayerPost(const UpdateInfo& info, unsigned int layers) {
    for (unsigned long i = 0; i < 32; ++i) {
        if (layers & (1 << i)) {
            for (CasterGroup::iterator it = m_casterGroups[i].begin(); it != m_casterGroups[i].end(); ++it) {
                if (it->m_caster != nullptr && !it->m_caster->m_isDead) {
                    it->m_caster->postUpdate(info);
                }
            }
        }
    }
}

void EffectManager::tail(const UpdateInfo& info, bool flag) {
    if (pad_2fda && effect::SystemManager::getPtr() != nullptr) {
        effect::SystemManager::destroy();
        effect::SystemManager::setUserFuncClear();
    }
    for (unsigned long i = 0; i < 32; ++i) {
        for (CasterGroup::iterator it = m_casterGroups[i].begin(); it != m_casterGroups[i].end(); ++it) {
            it->tailCopy();
        }
    }
    m_tailFlip = (m_tailFlip + 1) % 2;
    EffectCasterBase::tail();
    if (effect::SystemManager::getPtr() != nullptr) {
        effect::SystemManager::getPtr()->tail(flag);
    }
}

void EffectManager::fn_710017CB08(bool flag) {
    m_gfManagerFlag = flag;
}

void EffectManager::begin() {
    if (!isFinalized() && effect::SystemManager::getPtr() != nullptr) {
        effect::SystemManager::getPtr()->begin();
    }
}

void EffectManager::end() {
    if (!isFinalized() && effect::SystemManager::getPtr() != nullptr) {
        effect::SystemManager::getPtr()->end();
    }
}

#define FW_EFFECT_RENDER(NAME)                                                                                       \
    void EffectManager::NAME(ml::IDrDrawWorkInfo const* info) {                                                      \
        if (!isFinalized() && !m_inactive && effect::SystemManager::getPtr() != nullptr) {                           \
            effect::SystemManager::getPtr()->NAME(reinterpret_cast<const ptlib::DrDrawWorkInfoEF*>(info));           \
        }                                                                                                            \
    }
FW_EFFECT_RENDER(opacityRender)
FW_EFFECT_RENDER(alphaRender)
FW_EFFECT_RENDER(lastRender)
FW_EFFECT_RENDER(blurRender)
FW_EFFECT_RENDER(finalRender)

}  // namespace fw

#include "classes/effect/SystemManager.h"
#include "classes/fw/EffectManager.h"
#include "classes/fw/EffectCasterSend.h"
#include "classes/effect/SystemManager.h"
#include "classes/fw/EffectManager.h"
#include "classes/fw/EffectCasterBase.h"
#include "classes/ml/DrMdoMat.h"
#include "classes/ml/DrMdlObj.h"
#include "classes/ml/DrMdoGrpObj.h"
#include "classes/ml/DrMan.h"
#include "ml/DrCreator.h"
#include "classes/fw/Framework.h"
#include "classes/fw/EffectPack.h"
#include "mtl/MemManager.h"

namespace fw {

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

bool EffectManager::initialize() {
    return true;
}

bool EffectManager::isCommonLoaded() {
    return commonLoaded();
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

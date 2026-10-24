#include "classes/fw/EffectCasterSend.h"
#include "classes/effect/SystemManager.h"
#include "classes/fw/EffectManager.h"
#include "classes/effect/SystemManager.h"
#include "classes/fw/EffectManager.h"
#include "classes/ml/DrMdlObj.h"
#include "mtl/MemManager.h"

namespace fw {

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

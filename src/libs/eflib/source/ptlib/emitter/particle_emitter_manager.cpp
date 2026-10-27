#define MM_LIB_FROM_EFLIB
#include "ptlib/IntrusiveList.h"
#include "ptlib/emitter/EmitterManager.h"
#include "ptlib/emitter/EmitterObj.h"
#include "classes/ptlib/emitter/ComputeManager.h"
#include "classes/ptlib/emitter/EmitterSetNode.h"
#include "ptlib/ParticleSystem.h"
#include "ptlib/renderer/RendererStream.h"
#include "mm/MMStdBase.h"
#include <new>

namespace ptlib { namespace emitter {

// the instance EmitterManager::init makes (proposed name, not the original's: the symbols leave it unnamed,
// lbl_71015E9D30)
static EmitterManager* s_pEmitterManager;
// the instance ComputeManager::init makes (proposed name, not the original's: the symbols leave it unnamed,
// lbl_71015E9D38)
static ComputeManager* s_pComputeManager;

float EmitterObj::calc_fade() {
    if (m_fadeFrames == 0) {
        return 1.0f;
    }
    return static_cast<float>(m_fadeCount) / static_cast<float>(m_fadeFrames);
}

float EmitterObj::getCateSpd() {
    float* speeds = EmitterManager::getPtr()->m_categorySpeed;
    return speeds[m_category];
}

float EmitterObj::getEmitterScale() {
    float scale = m_pCas != nullptr ? m_pCas->getScale() : 1.0f;
    return scale * m_casScale;
}

void EmitterObj::remove_particle_free_tbl(ParticleObj* pParticle) {
    m_particleList.unlinkCount(pParticle);
    pParticle->particle_clear_union();
    EmitterManager::get()->m_particleFreeList.push_front(pParticle);
}

EmitterManager* EmitterManager::get() {
#line 21 "D:/Monolithsoft/BF2/prog/libs/eflib/proj/windows/../../../eflib/source\\ptlib/emitter/particle_emitter_manager.cpp"
    MM_ASSERT(getPtr());
    return getPtr();
}

EmitterManager*& EmitterManager::getPtr() {
    return s_pEmitterManager;
}

void* EmitterObj::lockStream(const DrDrawWorkInfoEF* pDrInfo) {
    return m_pStream->lockStream(pDrInfo);
}

void EmitterObj::unlockStream(const DrDrawWorkInfoEF* pDrInfo, unsigned int count) {
    m_pStream->unlockStream(pDrInfo, count);
}

void EmitterObj::renderStreamNum(renderer::RenderSet& set, const DrDrawWorkInfoEF* pDrInfo) {
    if (m_pStream != nullptr) {
        m_pStream->renderStreamNum(set, pDrInfo);
    }
}

void ComputeManager::init() {
#line 40 "D:/Monolithsoft/BF2/prog/libs/eflib/proj/windows/../../../eflib/source\\ptlib/emitter/compute/particle_emitter_compute_impl.h"
    MM_ASSERT(!getPtr());
#line 41 "D:/Monolithsoft/BF2/prog/libs/eflib/proj/windows/../../../eflib/source\\ptlib/emitter/compute/particle_emitter_compute_impl.h"
    getPtr() = static_cast<ComputeManager*>(ParticleManager::sysAlloc(sizeof(ComputeManager), 32, __FILE__, __LINE__));
    if (getPtr() != nullptr) {
        new (getPtr()) ComputeManager();
        getPtr()->initSub();
    }
}

void ComputeManager::term() {
#line 51 "D:/Monolithsoft/BF2/prog/libs/eflib/proj/windows/../../../eflib/source\\ptlib/emitter/compute/particle_emitter_compute_impl.h"
    MM_ASSERT(getPtr());
    if (getPtr() != nullptr) {
        getPtr()->termSub();
        getPtr()->~ComputeManager();
        if (getPtr() != nullptr) {
            ParticleManager::sysFree(getPtr());
            getPtr() = nullptr;
        }
    }
    getPtr() = nullptr;
}

EmitterObj* EmitterManager::getEmitterFree() {
    if (m_emitterFreeList.m_size == 0) {
        return nullptr;
    }
    IntrusiveList<EmitterObj>::iterator it = m_emitterFreeList.begin();
    EmitterObj* pEmitter = it.get();
    m_emitterFreeList.erase(it);
    return pEmitter;
}

void EmitterManager::emitter_set_param_pos_only(unsigned int handle, EmitterParam* pParam) {
    for (IntrusiveList<EmitterObj>::iterator it = m_emitterActiveList.begin(); it != m_emitterActiveList.end(); ++it) {
        if (it->m_handle == handle) {
            if (it->m_pAttach == nullptr) {
                it->m_mtx = pParam->m_mtx;
            }
            ParticleManager::get()->update_model_spd(&*it, 1.0f);
        }
    }
}

void EmitterManager::emitter_set_param(unsigned int handle, EmitterParam* pParam) {
    for (IntrusiveList<EmitterObj>::iterator it = m_emitterActiveList.begin(); it != m_emitterActiveList.end(); ++it) {
        if (it->m_handle == handle) {
            it->emitter_set_param_sub(pParam);
        }
    }
    if (pParam->m_preFrames >= 1.0f) {
        int count = static_cast<int>(pParam->m_preFrames * 0.5f);
        float frames = 2.0f;
        if (count < 1) {
            count = 1;
            frames = pParam->m_preFrames;
        }
        for (int i = 0; i < count; i++) {
            emitter_update(handle, frames, false);
        }
    }
}

void EmitterManager::emitter_set_param(FxHeader* pHeader, EmitterParam* pParam) {
    for (IntrusiveList<EmitterObj>::iterator it = m_emitterActiveList.begin(); it != m_emitterActiveList.end(); ++it) {
        if (it->m_pHeader == pHeader) {
            it->emitter_set_param_sub(pParam);
        }
    }
}

void EmitterManager::emitter_set_casparam(unsigned int handle, const void* pModel, EmitterParam* pParam) {
    for (IntrusiveList<EmitterObj>::iterator it = m_emitterActiveList.begin(); it != m_emitterActiveList.end(); ++it) {
        if (it->m_handle == handle && it->m_pAttach == nullptr) {
            it->m_pCas->m_pModel = pModel;
            it->m_pCas->m_name[0] = '\0';
            it->emitter_set_param_sub(pParam);
        }
    }
}

void EmitterManager::emitter_set_disp(unsigned int handle, int disp) {
    for (IntrusiveList<EmitterObj>::iterator it = m_emitterActiveList.begin(); it != m_emitterActiveList.end(); ++it) {
        if (it->m_handle == handle) {
            it->m_disp = disp;
        }
    }
}

void EmitterManager::emitter_set_alpha(unsigned int handle, float alpha) {
    for (IntrusiveList<EmitterObj>::iterator it = m_emitterActiveList.begin(); it != m_emitterActiveList.end(); ++it) {
        if (it->m_handle == handle) {
            it->m_alpha = alpha;
        }
    }
}

void EmitterManager::emitter_set_speed(unsigned int handle, float speed) {
    for (IntrusiveList<EmitterObj>::iterator it = m_emitterActiveList.begin(); it != m_emitterActiveList.end(); ++it) {
        if (handle == 0 || it->m_handle == handle) {
            it->m_speed = speed;
        }
    }
}

void EmitterManager::emitter_set_category(unsigned int handle, unsigned int category) {
    for (IntrusiveList<EmitterObj>::iterator it = m_emitterActiveList.begin(); it != m_emitterActiveList.end(); ++it) {
        if (it->m_handle == handle) {
            it->m_category = category;
        }
    }
}

void EmitterManager::emitter_set_viewnum(unsigned int handle, int view) {
    for (IntrusiveList<EmitterObj>::iterator it = m_emitterActiveList.begin(); it != m_emitterActiveList.end(); ++it) {
        if (it->m_handle == handle) {
            it->m_viewNum = view;
            it->m_pGrp = ParticleManager::getGrp(it->m_viewNum);
        }
    }
}

void EmitterManager::emitter_set_nowait(unsigned int handle, int nowait) {
    for (IntrusiveList<EmitterObj>::iterator it = m_emitterActiveList.begin(); it != m_emitterActiveList.end(); ++it) {
        if (it->m_handle == handle) {
            it->m_nowait = nowait;
        }
    }
}

void EmitterManager::moveAfter() {}

IntrusiveList<EmitterObj>* EmitterManager::getEmitterActiveList() {
    return &m_emitterActiveList;
}

void EmitterManager::removeEmitterActive(EmitterObj* pEmitter) {
    if (pEmitter->m_pStream != nullptr) {
        pEmitter->m_pStream->release();
    }
    pEmitter->releaseParticleAll();
    m_emitterActiveList.remove(pEmitter);
}

bool EmitterManager::emitter_set_check(FxHeader* pHeader) {
    for (IntrusiveList<EmitterSetNode>::iterator it = m_emitterSetList.begin(); it != m_emitterSetList.end(); ++it) {
        if (pHeader != nullptr) {
            return true;
        }
    }
    return false;
}

ComputeManager*& ComputeManager::getPtr() {
    return s_pComputeManager;
}

ComputeManager::~ComputeManager() {}

void ComputeManager::resetUpdate() {
    m_isUpdated = false;
}

void ComputeManager::update(unsigned int view) {
    m_viewIndex = view != 0;
    m_type3Uniform[m_viewIndex].createParticlesUniform();
    m_type2Uniform[m_viewIndex].createParticlesUniform();
    m_type4Uniform[m_viewIndex].createParticlesUniform();
    if (!m_isUpdated) {
        m_type1Uniform.createParticlesUniform();
        m_isUpdated = true;
    }
    m_type0Uniform.createParticlesUniform();
    calculateParticle();
}

}}  // namespace ptlib::emitter

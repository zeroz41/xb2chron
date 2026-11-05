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

void ParticleObj::particle_clear_union() {
    if (m_hasMdl) {
        if (m_pWork->m_pMdl != nullptr) {
            ParticleManager::deleteMdl(m_pWork->m_pMdl);
            m_pWork->m_pMdl = nullptr;
        }
        m_hasMdl = false;
    }
    if (m_hasLgt) {
        if (m_pWork->m_pLgt != nullptr) {
            ParticleManager::deleteLgt(m_pWork->m_lgtId, m_pWork->m_pLgt);
            m_pWork->m_pLgt = nullptr;
        }
        m_hasLgt = false;
    }
    m_pWork->m_pEmParent = nullptr;
    m_pWork->m_pLgt = nullptr;
    m_pWork->m_pMdl = nullptr;
    m_pWork->pad_118 = nullptr;
    m_pWork->pad_120 = nullptr;
    if (m_pWork != nullptr) {
        if (m_hasMdl) {
            ParticleManager::get()->deleteMdl(m_pWork->m_pMdl);
            m_pWork->m_pMdl = nullptr;
            m_hasMdl = false;
        }
        if (m_hasLgt) {
            ParticleManager::get()->deleteLgt(m_pWork->m_lgtId, m_pWork->m_pLgt);
            m_pWork->m_lgtId = 0;
            m_pWork->m_pLgt = nullptr;
            m_hasLgt = false;
        }
    }
}

EmitterManager* EmitterManager::get() {
#line 21 "D:/Monolithsoft/BF2/prog/libs/eflib/proj/windows/../../../eflib/source\\ptlib/emitter/particle_emitter_manager.cpp"
    MM_ASSERT(getPtr());
    return getPtr();
}

EmitterManager*& EmitterManager::getPtr() {
    return s_pEmitterManager;
}

int EmitterObj::move_func(float frame, int flag) {
#line 1958 "D:/Monolithsoft/BF2/prog/libs/eflib/proj/windows/../../../eflib/source\\ptlib/emitter/particle_emitter.cpp"
    MM_ASSERT(m_move_type < MOVE_TYPE_MAX);
    switch (m_move_type) {
    case 1:
        return move01_type0(frame, flag);
    case 2:
        return move01_type1(frame, flag);
    case 3:
        move01_type9(frame, flag);
        break;
    case 4:
        return move01_type_model(frame, flag);
    case 5:
        return move01_type5(frame, flag);
    case 6:
        return move01_type12(frame, flag);
    }
    return 0;
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

void EmitterObj::releaseParticleAll() {
    while (m_particleList.begin() != m_particleList.end()) {
        IntrusiveList<ParticleObj>::iterator it = m_particleList.begin();
        ParticleObj* pParticle = it.get();
        m_particleList.erase(it);
        EmitterManager::get()->m_particleFreeList.push_front(*pParticle);
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

void EmitterManager::emitter_set_link(FxHeader* pHeader) {
    if (!(m_emitterSetFreeList.m_size > 0)) {
#line 908 "D:/Monolithsoft/BF2/prog/libs/eflib/proj/windows/../../../eflib/source\\ptlib/emitter/particle_emitter_manager.cpp"
        MM_ASSERT(0);
    } else {
        IntrusiveList<EmitterSetNode>::iterator it = m_emitterSetFreeList.begin();
        EmitterSetNode* pNode = it.get();
        m_emitterSetFreeList.erase(it);
        pNode->m_pHeader = pHeader;
        m_emitterSetList.push_back(*pNode);
    }
}

void EmitterManager::emitter_set_unlink(FxHeader* pHeader) {
    for (IntrusiveList<EmitterSetNode>::iterator it = m_emitterSetList.begin(); it != m_emitterSetList.end();) {
        if (it->m_pHeader == pHeader) {
            EmitterSetNode& node = *it;
            it = m_emitterSetList.erase(it);
            m_emitterSetFreeList.push_back(node);
        } else {
            ++it;
        }
    }
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

void EmitterManager::emitter_set_param_pos_only2(unsigned int handle, EmitterParam* pParam) {
    for (IntrusiveList<EmitterObj>::iterator it = m_emitterActiveList.begin(); it != m_emitterActiveList.end(); ++it) {
        if (it->m_handle == handle) {
            if (it->m_pAttach == nullptr) {
                it->m_mtx.setTransRow(pParam->m_mtx.getTrans());
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

void EmitterManager::emitter_pack_free(unsigned long pack) {
    int count = 0;
    for (IntrusiveList<EmitterSetNode>::iterator it = m_emitterSetList.begin(); it != m_emitterSetList.end(); ++it) {
        if (it->m_pHeader->m_userParam == pack) {
            count++;
        }
    }
    if (count > 0) {
        do {
            for (IntrusiveList<EmitterSetNode>::iterator it = m_emitterSetList.begin(); it != m_emitterSetList.end();
                 ++it) {
                if (it->m_pHeader->m_userParam == pack) {
                    emitter_set_free(it->m_pHeader, 1);
                    count--;
                    break;
                }
            }
        } while (count > 0);
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

ParticleObj* EmitterManager::createCommon(EmitterObj* pEmitter) {
    ParticleObj* pParticle;
    if (pEmitter->m_allocMode == 1) {
        pParticle = particleAlloc(pEmitter, false);
    } else {
        pParticle = particleAlloc(pEmitter, true);
    }
    if (pParticle != nullptr) {
        mm::Vec3 goal;
        EmitterObj::calc_start2goal01(pEmitter, &pParticle->m_pos, &goal);
        pParticle->m_goal = goal;
        pParticle->pad_c2 = 0;
        pParticle->m_prevPos = pParticle->m_pos;
        pParticle->pad_40 = mm::Vec3::zero;
        pParticle->pad_50 = mm::Vec3::zero;
        pParticle->getExtParam().m_pLgt = nullptr;
        pParticle->getExtParam().m_pMdl = nullptr;
        pParticle->getExtParam().pad_118 = nullptr;
        pParticle->getExtParam().pad_120 = nullptr;
        pParticle->getExtParam().m_pMdl = nullptr;
    }
    return pParticle;
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

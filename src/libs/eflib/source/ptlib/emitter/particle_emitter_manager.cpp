#define MM_LIB_FROM_EFLIB
#include "ptlib/IntrusiveList.h"
#include "ptlib/emitter/EmitterManager.h"
#include "ptlib/emitter/EmitterObj.h"
#include "classes/ptlib/emitter/ComputeManager.h"
#include "classes/ptlib/emitter/EmitterSetNode.h"
#include "ptlib/ParticleSystem.h"
#include "ptlib/renderer/RendererStream.h"
#include "mm/MMStdBase.h"
#include "mm/Math.h"
#include "ptlib/Utility.h"
#include "ptlib/StackAllocater.h"
#include "ml/ScnObjAccGpuCheck.h"
#include "ptlib/forcefield/TurbulenceN.h"
#include "ptlib/material/MaterialManager.h"
#include <new>
#include <string.h>

namespace ptlib { namespace emitter {

// the instance EmitterManager::init makes (proposed name, not the original's: the symbols leave it unnamed,
// lbl_71015E9D30)
static EmitterManager* s_pEmitterManager;
// the instance ComputeManager::init makes (proposed name, not the original's: the symbols leave it unnamed,
// lbl_71015E9D38)
static ComputeManager* s_pComputeManager;

float EmitterObj::check_ground(const mm::Vec3& pos, float height, float* pAngle) {
    mm::Vec3 normal;
    mm::Vec3 outPos;
    outPos.y = -80.0f;
    mm::Vec3 end(pos.x, pos.y - height, pos.z);
    bool hit = ParticleManager::getPtr()->testLineGround(normal, outPos, pos, end);
    float ground = outPos.y;
    if (hit) {
        if (pAngle != nullptr) {
            mm::Vec3 n = normal;
            pAngle[0] = ::atan2f(::sqrtf(n.x * n.x + n.z * n.z), n.y);
            pAngle[1] = ::atan2f(n.x, n.z);
        }
#line 729 "D:/Monolithsoft/BF2/prog/libs/eflib/proj/windows/../../../eflib/source\\ptlib/emitter/particle_emitter.cpp"
        MM_ASSERT(!outPos.isError());
    } else if (!mm::Vec3::isValid(ground)) {
        ground = -80.0f;
    }
    return ground;
}

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

void ParticleObj::move01_common_keyframe(EmitterObj* pEmitter, float rate, int flag) {
    math::KeyFrameIP kf;
    float frame = m_frame * m_frameSpeed;
    if (m_life == 0x7FFF) {
        if (pEmitter->m_fadeFrames != 0 && pEmitter->m_fadeState != 0) {
            frame = 0x10000 + pEmitter->m_fadeFrames - pEmitter->m_fadeCount;
        }
        if (m_frame > 32768.0f) {
            m_frame -= 16384.0f;
        }
    }
    float emitterFrame = pEmitter->m_frame;
    calcSpeedKeyframe(pEmitter, kf, frame, emitterFrame);
    calcParSize(flag, pEmitter, kf, frame, emitterFrame, true);
    calcParRot(kf, frame, pEmitter, true, rate);
    if (pEmitter->m_pData->m_vecKfCount != 0) {
        pEmitter->m_pData->get_kf(&kf, pEmitter->m_pData->m_vecKfCount, 6, frame, m_pWork->m_vecKeyIndex,
                                  &m_pWork->m_vecKey, &m_pVecKf, pEmitter->m_pKfTable);
        kf.keyrand_get_ip3(&m_keyVec, &m_pWork->m_vecKey, pEmitter->m_seed);
    }
    move_common_keyframe_uv1_full(pEmitter, frame, rate);
    calcMatColor(frame, kf, pEmitter, emitterFrame, true);
}

bool EmitterObj::isRenderCheck() const {
    if (m_pGpuCheck == nullptr || m_pGpuCheck->isRender()) {
        return true;
    }
    return m_frame < 60.0f;
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

void ParticleObj::emitter_create_local_common_grav_wind(EmitterObj* pEmitter) {
    const GravityParam* pGravity = pEmitter->m_pGravity;
    if (pGravity != nullptr) {
        m_pWork->m_gravity = pGravity->m_speed + pGravity->m_speedRange * math::randf2(pEmitter->m_seed);
        m_pWork->m_gravityVec = mm::Vec3::zero;
    }
    const WindParam* pWind = pEmitter->m_pWind;
    if (pWind != nullptr) {
        mm::Vec3 dir(pWind->m_dir.x, pWind->m_dir.y, pWind->m_dir.z);
        float strength = pWind->m_strength;
        if (pWind->m_type != 0 && pWind->m_type != 8 && pWind->m_type != 10 && pWind->m_type != 11) {
            const mm::Mat44& mtx = pEmitter->m_pCas->m_mtx;
            dir = mm::Vec3(dir.x * mtx.m[0][0] + dir.y * mtx.m[1][0] + dir.z * mtx.m[2][0],
                           dir.x * mtx.m[0][1] + dir.y * mtx.m[1][1] + dir.z * mtx.m[2][1],
                           dir.x * mtx.m[0][2] + dir.y * mtx.m[1][2] + dir.z * mtx.m[2][2]);
        }
        m_pWork->m_wind = mm::Vec3(strength * dir.x, strength * dir.y, strength * dir.z);
    }
    if (pEmitter->m_pNoise != nullptr) {
        m_pWork->m_noise = mm::Vec3::zero;
    }
}

void EmitterManager::init() {
#line 44 "D:/Monolithsoft/BF2/prog/libs/eflib/proj/windows/../../../eflib/source\\ptlib/emitter/particle_emitter_manager.cpp"
    MM_ASSERT(!getPtr());
#line 59 "D:/Monolithsoft/BF2/prog/libs/eflib/proj/windows/../../../eflib/source\\ptlib/emitter/particle_emitter_manager.cpp"
    StaticAllocObj* alloc = StaticAllocObj::create(0xC9CA50, __FILE__, __LINE__);
    getPtr() = static_cast<EmitterManager*>(alloc->sysAlloc(sizeof(EmitterManager), 16, nullptr, 0));
    if (getPtr() != nullptr) {
        new (getPtr()) EmitterManager();
        getPtr()->init_sub(alloc);
    }
    forcefield::FfManager::init();
    ComputeManager::init();
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

void EmitterManager::clear() {
    if (pad_1788 != nullptr) {
        pad_1788 = nullptr;
    }
    m_flip = 0;
    pad_1748 = 0;
    for (IntrusiveList<EmitterObj>::iterator it = m_emitterActiveList.begin(); it != m_emitterActiveList.end();) {
        it = m_emitterActiveList.erase(it);
    }
    for (IntrusiveList<EmitterObj>::iterator it = m_emitterFreeList.begin(); it != m_emitterFreeList.end();) {
        it = m_emitterFreeList.erase(it);
    }
    m_emitterSetList.clear();
    m_emitterSetFreeList.clear();
    pad_1798 = 0;
    for (int i = 4; i >= 0; i--) {
        m_pDrawTop[i] = nullptr;
    }
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

void EmitterManager::emitter_set_casname(unsigned int handle, const void* pModel, const char* name, int, float scale,
                                         int mode) {
    if (name != nullptr && strlen(name) >= 0x10) {
        efAstMsg("0", "emitter_set_casname:too long name[%s]", name);
    }
    for (IntrusiveList<EmitterObj>::iterator it = m_emitterActiveList.begin(); it != m_emitterActiveList.end(); ++it) {
        if (it->m_handle == handle && it->m_pAttach == nullptr) {
            if (pModel != nullptr) {
                it->m_pCas->m_pModel = pModel;
                it->m_casScale = scale;
                it->m_casMode = mode;
                if (name != nullptr) {
                    strcpy(it->m_pCas->m_name, name);
                }
            } else {
                it->m_pCas->m_pModel = nullptr;
                it->m_pCas->m_name[0] = '\0';
            }
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

void EmitterManager::emitter_set_free_all_sub(bool flag) {
    while (!m_emitterActiveList.empty()) {
        emitter_free_core(&*m_emitterActiveList.begin());
    }
    for (;;) {
        IntrusiveList<EmitterSetNode>::iterator it = m_emitterSetList.begin();
        if (m_emitterSetList.end() == it) {
            break;
        }
        FxHeader* pHeader = it->m_pHeader;
        if (pHeader->m_userParam == 0) {
            emitter_set_free(pHeader, 1);
        } else {
            emitter_pack_free(pHeader->m_userParam);
        }
    }
    IntrusiveList<EmitterObj> list;
    for (IntrusiveList<EmitterObj>::iterator it = m_emitterFreeList.begin(); it != m_emitterFreeList.end(); ++it) {
        if (it->m_pStream != nullptr) {
            it->m_pStream->release();
        }
        it->releaseParticleAll();
    }
    material::MaterialManager::get()->allClear(flag);
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

void EmitterManager::move() {
    EmitterObj* pTail0 = nullptr;
    EmitterObj* pTail2 = nullptr;
    EmitterObj* pTail1 = nullptr;
    for (IntrusiveList<EmitterObj>::iterator it = m_emitterActiveList.begin(); it != m_emitterActiveList.end(); ++it) {
        EmitterObj* pEmitter = &*it;
        EmitterArg* pArg = pEmitter->m_pData;
        bool seen = pEmitter->isRenderCheck();
        if (pArg == nullptr || !seen) {
            continue;
        }
        if ((pArg->m_type & 0xFE) != 4 && (pEmitter->m_disp == 0 || !(pEmitter->m_alpha > 0.0f))) {
            continue;
        }
        switch (pArg->m_type) {
        case 0:
        case 1:
        case 9:
            if (pTail0 != nullptr) {
                pTail0->m_pDrawNext = pEmitter;
            } else {
                m_pDrawTop[0] = pEmitter;
            }
            pTail0 = pEmitter;
            break;
        case 2:
            if (pTail2 != nullptr) {
                pTail2->m_pDrawNext = pEmitter;
            } else {
                m_pDrawTop[2] = pEmitter;
            }
            pTail2 = pEmitter;
            break;
        case 4:
        case 5:
            if (pTail1 != nullptr) {
                pTail1->m_pDrawNext = pEmitter;
            } else {
                m_pDrawTop[1] = pEmitter;
            }
            pTail1 = pEmitter;
            break;
        case 12:
            if (pTail0 != nullptr) {
                pTail0->m_pDrawNext = pEmitter;
            } else {
                m_pDrawTop[0] = pEmitter;
            }
            pTail0 = pEmitter;
            break;
        }
        if (pTail0 != nullptr) {
            pTail0->m_pDrawNext = nullptr;
        } else {
            m_pDrawTop[0] = nullptr;
        }
        if (pTail2 != nullptr) {
            pTail2->m_pDrawNext = nullptr;
        } else {
            m_pDrawTop[2] = nullptr;
        }
        if (pTail1 != nullptr) {
            pTail1->m_pDrawNext = nullptr;
        } else {
            m_pDrawTop[1] = nullptr;
        }
        m_pDrawTop[3] = nullptr;
    }
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
        pParticle->m_rotSign = 0;
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

void EmitterManager::createSpd(EmitterObj* pEmitter, EmitterArg* pArg, math::KeyFrameIP& kf, float frame,
                               ParticleObj* pParticle, bool key) {
    const SpeedParam* pSpeed = pEmitter->m_pSpeed;
    if (pSpeed == nullptr) {
        pParticle->m_speed = 0.0f;
        pParticle->m_baseSpeed = 0.0f;
        return;
    }
    float speed = pSpeed->m_speed + pSpeed->m_speedRange * math::randf2(pEmitter->m_seed);
    if (key && (pSpeed->m_kfCount != 0 || pSpeed->m_kfCount2 != 0)) {
        pArg->get_kf(&kf, pSpeed->m_kfCount != 0 ? pSpeed->m_kfCount : pSpeed->m_kfCount2, 2, frame,
                     pEmitter->m_spdKeyIndex, &pEmitter->m_spdKey, &pParticle->m_pSpdKf, pEmitter->m_pSpdKfTable);
        float value = kf.keyrand_get_ip1(&pEmitter->m_spdKey, pEmitter->m_seed);
        if (pSpeed->m_kfCount != 0) {
            pParticle->m_speedKey = value;
        }
        speed *= value;
    }
    pParticle->m_baseSpeed = speed;
    pParticle->m_speed = speed * pEmitter->getEmitterScale();
}

ParticleObj* EmitterObj::move_type1_sort(ParticleObj** pTable, EmitterObj* pEmitter) {
    if (pTable != nullptr) {
        memset(pTable, 0, sizeof(ParticleObj*) * 100);
    }
    ParticleObj* pLast = nullptr;
    for (IntrusiveList<ParticleObj>::iterator it = pEmitter->m_particleList.begin();
         it != pEmitter->m_particleList.end(); ++it) {
        ParticleObj* pParticle = it.get();
        short life = pParticle->m_life;
        if (life < 0 || life > 100) {
            pLast = pParticle;
            if (pTable == nullptr) {
                break;
            }
        } else if (pTable != nullptr) {
            pTable[life - 1] = pParticle;
        }
    }
    return pLast;
}

void EmitterObj::move_common_cas_update(EmitterArg* pArg) {
    // never set: calc_start2goal_axis gets whatever the register holds (the original passes it uninitialized)
    unsigned int seed;
    calc_start2goal_axis(m_pCas->m_mtx, m_pCas->m_scale, this, pArg->m_axisType, seed, false);
    EmitterCas* pCas = m_pCas;
    const mm::Mat44& mtx = pCas->m_mtx;
    mm::Quat& rot = pCas->m_rot;
    float trace[4];
    trace[0] = mtx.m[0][0] - mtx.m[1][1] - mtx.m[2][2] + 1.0f;
    trace[1] = -mtx.m[0][0] + mtx.m[1][1] - mtx.m[2][2] + 1.0f;
    trace[2] = -mtx.m[0][0] - mtx.m[1][1] + mtx.m[2][2] + 1.0f;
    trace[3] = mtx.m[0][0] + mtx.m[1][1] + mtx.m[2][2] + 1.0f;
    unsigned int index = trace[1] > trace[0] ? 1 : 0;
    if (trace[2] > trace[index]) {
        index = 2;
    }
    if (trace[3] > trace[index]) {
        index = 3;
    }
    if (trace[index] < 0.0f) {
        rot = mm::Quat::identity;
        return;
    }
    float* q[4] = {&rot.x, &rot.y, &rot.z, &rot.w};
    float s = ::sqrtf(trace[index]) * 0.5f;
    *q[index] = s;
    s = 0.25f / s;
    switch (index) {
    case 0:
        rot.y = s * (mtx.m[0][1] + mtx.m[1][0]);
        rot.z = s * (mtx.m[2][0] + mtx.m[0][2]);
        rot.w = s * (mtx.m[1][2] - mtx.m[2][1]);
        break;
    case 1:
        rot.x = s * (mtx.m[0][1] + mtx.m[1][0]);
        rot.z = s * (mtx.m[1][2] + mtx.m[2][1]);
        rot.w = s * (mtx.m[2][0] - mtx.m[0][2]);
        break;
    case 2:
        rot.x = s * (mtx.m[2][0] + mtx.m[0][2]);
        rot.y = s * (mtx.m[1][2] + mtx.m[2][1]);
        rot.w = s * (mtx.m[0][1] - mtx.m[1][0]);
        break;
    case 3:
        rot.x = s * (mtx.m[1][2] - mtx.m[2][1]);
        rot.y = s * (mtx.m[2][0] - mtx.m[0][2]);
        rot.z = s * (mtx.m[0][1] - mtx.m[1][0]);
        break;
    }
}

// mm::Vec3::isValid read through the float's memory (calcParSize's check loads each component once, as an integer;
// the name is not the original's)
static inline bool isValidBits(const float& f) {
    unsigned int bits = *reinterpret_cast<const unsigned int*>(&f);
    return bits != 0xCCCCCCCC && (bits & 0x7F800000) != 0x7F800000;
}

void ParticleObj::calcParSize(int flag, EmitterObj* pEmitter, math::KeyFrameIP& kf, float frame, float emitterFrame,
                              bool key) {
    if (flag != 0) {
        return;
    }
    EmitterArg* pArg = pEmitter->m_pData;
    float scale = pEmitter->getEmitterScale() * m_sizeRate;
    mm::Vec3NA size = {scale, scale, scale};
    if (pArg->m_sizeKfCount != 0) {
        pArg->get_kf(&kf, pArg->m_sizeKfCount, 6, frame, m_pWork->m_sizeKeyIndex, &m_pWork->m_sizeKey, &m_pSizeKf,
                     pEmitter->m_pSizeKfTable);
        kf.keyrand_mul_ip3(&size, &m_pWork->m_sizeKey, pEmitter->m_seed);
    } else {
        size.x = scale * m_baseSize.x;
        size.y = scale * m_baseSize.y;
        size.z = scale * m_baseSize.z;
    }
    if (key) {
        if (pArg->m_sizeScaleCount != 0) {
            size.x = size.x * m_sizeScale.x;
            size.y = size.y * m_sizeScale.y;
            size.z = size.z * m_sizeScale.z;
        } else if (pArg->m_emSizeKfCount != 0) {
            pArg->get_kf(&kf, pArg->m_emSizeKfCount, 6, emitterFrame, pEmitter->m_sizeKeyIndex, &pEmitter->m_sizeKey,
                         &m_pSizeKf, pEmitter->m_pSizeKfTable);
            kf.keyrand_mul_ip3(&size, &pEmitter->m_sizeKey, pEmitter->m_seed);
        }
    }
    if (isValidBits(m_sizeMul.x) && isValidBits(m_sizeMul.y) && isValidBits(m_sizeMul.z)) {
        size.x = size.x * m_sizeMul.x;
        size.y = size.y * m_sizeMul.y;
        size.z = size.z * m_sizeMul.z;
    }
    m_size.x = size.x;
    m_size.y = size.y;
    m_size.z = size.z;
}

void ParticleObj::calcParRot(math::KeyFrameIP& kf, float frame, EmitterObj* pEmitter, bool key, float rate) {
    EmitterArg* pArg = pEmitter->m_pData;
    if (pArg->m_rotKfCount == 0) {
        return;
    }
    pArg->get_kf(&kf, pArg->m_rotKfCount, 6, frame, m_pWork->m_rotKeyIndex, &m_pWork->m_rotKey, &m_pRotKf,
                 pEmitter->m_pRotKfTable);
    if (pArg->m_rotMode == 0 && key) {
        kf.keyrand_get_ip3(&m_rot, &m_pWork->m_rotKey, pEmitter->m_seed);
        return;
    }
    mm::Vec3 add;
    kf.keyrand_get_ip3(&add, &m_pWork->m_rotKey, pEmitter->m_seed);
    add.x *= rate;
    add.y *= rate;
    add.z *= rate;
    switch (pArg->m_rotMode) {
    case 2:
        if (m_rotSign & 1) {
            add.x = -add.x;
        }
        if (m_rotSign & 2) {
            add.y = -add.y;
        }
        if (m_rotSign & 4) {
            add.z = -add.z;
        }
    case 1: {
        float rot = add.x + m_rot.x;
        if (rot > 3.14159274f) {
            rot -= 6.28318548f;
        } else if (rot < -3.14159274f) {
            rot += 6.28318548f;
        }
        m_rot.x = rot;
        rot = add.y + m_rot.y;
        if (rot > 3.14159274f) {
            rot -= 6.28318548f;
        } else if (rot < -3.14159274f) {
            rot += 6.28318548f;
        }
        m_rot.y = rot;
        rot = add.z + m_rot.z;
        if (rot > 3.14159274f) {
            rot -= 6.28318548f;
        } else if (rot < -3.14159274f) {
            rot += 6.28318548f;
        }
        m_rot.z = rot;
        break;
    }
    }
}

void ParticleObj::calcNoise(EmitterObj* pEmitter, mm::Vec3& speed) {
    const NoiseParam* pNoise = pEmitter->m_pNoise;
    if (pNoise == nullptr) {
        return;
    }
    float rate = move_common_check_begin_end_fin_fout(pEmitter, pNoise->m_begin, pNoise->m_end, pNoise->m_fadeIn,
                                                      pNoise->m_fadeOut, pNoise->m_frameType) *
                 pEmitter->getEmitterScale();
    if (rate > 0.0f) {
        mm::Vec3 noise;
        TurbulenceN::turb3d(noise, m_pos, pNoise->m_frequency, pNoise->m_amplitude, pNoise->m_octaves);
        m_pWork->m_noise += noise;
        speed.x += rate * m_pWork->m_noise.x;
        speed.y += rate * m_pWork->m_noise.y;
        speed.z += rate * m_pWork->m_noise.z;
    }
}

void ParticleObj::calcNewton(EmitterObj* pEmitter, mm::Vec3& speed) {
    const NewtonParam* pNewton = pEmitter->m_pNewton;
    if (pNewton == nullptr) {
        return;
    }
    unsigned short begin = pNewton->m_begin;
    unsigned short end = pNewton->m_end;
    float frame = pNewton->m_frameType <= 1 ? pEmitter->m_frame : m_frame * m_frameSpeed;
    unsigned int now = static_cast<int>(frame);
    if (now < begin) {
        return;
    }
    if (end != 0 && now > end) {
        return;
    }
    mm::Vec3 dir = m_pos - pEmitter->m_newtonCenter;
    float dist = dir.length();
    if (dist > pNewton->m_radius) {
        float power = pNewton->m_power * ::powf(dist, pNewton->m_exponent);
        float length = dir.length();
        mm::Vec3 pull = dir;
        if (length <= 1e-6f) {
            pull = mm::Vec3::zero;
        } else {
            float scale = 1.0f / length;
            pull.x = scale * pull.x;
            pull.y = scale * pull.y;
            pull.z = scale * pull.z;
        }
        mm::Vec3 force = pull * power;
        m_pWork->m_newton -= force;
    }
    speed.x += m_pWork->m_newton.x;
    speed.y += m_pWork->m_newton.y;
    speed.z += m_pWork->m_newton.z;
}

void ParticleObj::calcIsFit(int isFit, EmitterObj* pEmitter, mm::Vec3& dir) {
    if (isFit == 0) {
        return;
    }
    EmitterArg* pData = pEmitter->m_pData;
    if (pData != nullptr && pData->m_type == 4) {
        return;
    }
    if (pData->m_fitType != 8 && pData->m_fitType != 9) {
        return;
    }
    ParticleObj* pParent;
    EmitterObj* pParentEmitter;
    if (pData->m_fitParent && (pParent = pEmitter->m_pAttach) != nullptr &&
        (pParentEmitter = pParent->m_pWork->m_pEmParent) != nullptr && pEmitter->m_attachId == pParent->m_id &&
        pParentEmitter->m_pData != nullptr && (pParentEmitter->m_pData->m_fitType & 8) != 0) {
        m_rot.x = pParent->m_rot.x;
        m_rot.y = pEmitter->m_pAttach->m_rot.y;
    } else {
        m_rot.x = -atan2f(dir.y, sqrtf(dir.x * dir.x + dir.z * dir.z));
        m_rot.y = atan2f(dir.x, dir.z);
    }
}

void ParticleObj::calcExternalColor(mm::Vec3& color, EmitterObj* pEmitter, float& alpha, int setColor,
                                    int setColor2) {
    if (pEmitter->m_pData->m_externalColor) {
        color.x = m_pWork->m_color.x * pEmitter->m_colorR;
        color.y = m_pWork->m_color.y * pEmitter->m_colorG;
        color.z = m_pWork->m_color.z * pEmitter->m_colorB;
        alpha = m_pWork->m_alpha * pEmitter->m_alpha;
        m_pWork->m_rgba = Utility::conv_rgba(&color, alpha);
    } else if (setColor != 0) {
        m_pWork->m_rgba = Utility::conv_rgba(&m_pWork->m_color, m_pWork->m_alpha);
    }
    if (setColor2 != 0) {
        mm::Vec3 color2;
        color2.x = m_pWork->m_color2.x * pEmitter->m_colorR;
        color2.y = m_pWork->m_color2.y * pEmitter->m_colorG;
        color2.z = m_pWork->m_color2.z * pEmitter->m_colorB;
        m_pWork->m_rgba2 = Utility::conv_rgba(&color2, m_pWork->m_alpha * pEmitter->m_alpha);
    }
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

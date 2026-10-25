#define MM_LIB_FROM_EFLIB
#include "classes/effect/SystemManager.h"
#include "ptlib/ParticleSystem.h"
#include "ptlib/DrDrawWorkInfoEF.h"
#include "classes/ptlib/emitter/ComputeManager.h"
#include "ptlib/emitter/EmitterManager.h"
#include "ptlib/forcefield/FfManager.h"
#include "classes/effect/SystemManager.h"
#include "ptlib/ParticleSystem.h"
#include "ptlib/DrDrawWorkInfoEF.h"
#include "classes/ptlib/emitter/ComputeManager.h"
#include "ptlib/renderer/RendererStream.h"
#include "ptlib/renderer/ScreenRenderManager.h"
#include "mm/MMStdBase.h"

namespace effect {

// the one manager: create sets it, destroy clears it (proposed name, not the original's: the symbols leave it
// unnamed, lbl_71015E9D28)
static SystemManager* s_pIns;

SystemManager* SystemManager::get() {
#line 64
    MM_ASSERT(getPtr());
    return getPtr();
}

SystemManager*& SystemManager::getPtr() {
    return s_pIns;
}

bool SystemManager::isValid() {
    if (getPtr() != nullptr && getPtr()->m_clearAllCount == 0) {
        return true;
    }
    return false;
}

SystemManager::~SystemManager() {
    m_commands[0].clear();
    m_commands[1].clear();
    m_addForces.clear();
}

SystemManager* SystemManager::create(const ptlib::DrDrawWorkInfoEF* info) {
#line 551
    getPtr() = static_cast<SystemManager*>(ptlib::ParticleManager::sysAlloc(sizeof(SystemManager), 16, __FILE__, __LINE__));
    new (getPtr()) SystemManager;
    if (getPtr() == nullptr) {
        ptlib::efAstMsg("0", "task create error!!");
        return nullptr;
    }
    ptlib::ParticleManager::init(info);
    return getPtr();
}

void SystemManager::destroy() {
    SystemManager* sys = getPtr();
    if (sys != nullptr) {
        ptlib::ParticleManager::get()->term();
        sys->m_destroyFlag = false;
        getPtr()->~SystemManager();
        if (getPtr() != nullptr) {
            ptlib::ParticleManager::sysFree(getPtr());
            getPtr() = nullptr;
        }
    }
    ptlib::screen::ScreenRenderManager::term();
}

void SystemManager::setUserFuncClear() {
    ptlib::ParticleManager::setUserAllocFunc(nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);
    ptlib::ParticleManager::setUserFileFunc(nullptr, nullptr);
    ptlib::ParticleManager::setUserOutputString(nullptr, nullptr);
    ptlib::ParticleManager::setUserDrFunc(nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
                                          nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);
}

void SystemManager::setUserAllocFunc(void* (*alloc)(void*, unsigned int, unsigned int, const char*, unsigned int),
                                     void (*free)(void*, void*),
                                     void* (*alloc2)(void*, unsigned int, unsigned int, const char*, unsigned int),
                                     void (*free2)(void*, void*), mtl::ALLOC_HANDLE (*handle)(),
                                     mtl::ALLOC_HANDLE (*handle2)()) {
    ptlib::ParticleManager::setUserAllocFunc(alloc, free, alloc2, free2, handle, handle2);
}

void SystemManager::setUserFileFunc(void* (*load)(const char*, int&), void (*release)(void*)) {
    ptlib::ParticleManager::setUserFileFunc(load, release);
}

void SystemManager::setUserOutputString(void (*print)(const char*), void (*warn)(const char*)) {
    ptlib::ParticleManager::setUserOutputString(print, warn);
}

void SystemManager::setUserDrFunc(void* (*a)(const void*, const char*, int, const void*, int), void (*b)(void*),
                                  void* (*c)(unsigned int, int), void (*d)(unsigned int, void*),
                                  void (*e)(void*, void*), void (*f)(void*, void*), void (*g)(void*, void*),
                                  void (*h)(void*, float), void (*i)(void*, void*),
                                  void (*j)(unsigned int, void*, void*), void (*k)(unsigned int, void*, void*),
                                  void (*l)(unsigned int, void*, void*), void (*m)(void*), void* (*n)(int, int),
                                  void (*o)(void*)) {
    ptlib::ParticleManager::setUserDrFunc(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o);
}

void SystemManager::es_free(void* handle) {
    if (handle != nullptr) {
        ptlib::ParticleManager::get()->emitter_set_free(static_cast<ptlib::FxHeader*>(handle), 0);
    }
}

int SystemManager::es_getDeadFlag(unsigned int handle) {
    if (ptlib::HashManager::getPtr() == nullptr) {
        return -1;
    }
    return ptlib::HashManager::getPtr()->searchDead(handle);
}

bool SystemManager::es_is_loop(void* data) const {
    return static_cast<ptlib::FxHeader*>(data)->m_loop != 0;
}

bool SystemManager::es_contais_cam_axis(void* data) {
    return static_cast<ptlib::FxHeader*>(data)->m_containsCamAxis != 0;
}

void SystemManager::es_clearall(bool flag) {
    if (m_clearAllCount == 0) {
        m_clearAllCount = 1;
    }
    m_clearAllFlag = flag;
}

void SystemManager::setGlobalSpeed(float speed) {
    m_globalSpeed[m_writeSide == 0] = speed;
}

void SystemManager::setCategorySpd(unsigned int category, float speed) {
    ptlib::emitter::EmitterManager::getPtr()->m_categorySpeed[category] = speed;
}

void SystemManager::begin() {
    ptlib::renderer::EffStateManager::get()->begin();
}

void SystemManager::end() {}

void SystemManager::apply(const ptlib::DrDrawWorkInfoEF* info) {
    if (m_enableUpdate) {
        MainLoop(info);
    }
}

void SystemManager::opacityRender(const ptlib::DrDrawWorkInfoEF* info) {}

void SystemManager::lastRender(const ptlib::DrDrawWorkInfoEF* info) {}

void SystemManager::finalRender(const ptlib::DrDrawWorkInfoEF* info) {
    testRender(info);
}

void SystemManager::moveMain() {
    // the original passes nothing it sets: the call goes out with whatever s0 holds
    float delta;
    testUpdate(delta);
}

}  // namespace effect

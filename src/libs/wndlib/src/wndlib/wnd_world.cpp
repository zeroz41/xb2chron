#include "mm/mtl/IntrusiveList.h"
#include "classes/wnd/WindObject.h"
#include "classes/wnd/AreaWind.h"
#include "classes/wnd/LocalWind.h"
#include "classes/wnd/GlobalWind.h"
#include "classes/wnd/BroadPhazeInterface.h"
#include "classes/wnd/WindWorld.h"

#include "wnd/UpdateInfo.h"
#include "mm/MMStdBase.h"

namespace wnd {

WindWorld::WindWorld(Dispatcher* pDispatcher, BroadPhazeInterface* pBroadPhaze,
                     const Array<const ResConpoundWind*>& resWind, mm::mtl::IAllocator* allocator)
    : m_time(0.0f), m_debugMode(false) {
    m_pBroadPhaze = pBroadPhaze;
    m_pBroadPhaze->addRef();
    m_pDispatcher = pDispatcher;
    m_pDispatcher->addRef();
    m_globalWindManager.setup(resWind, allocator);
}

// every area wind and probe out of the world, then everything that let go of released
WindWorld::~WindWorld() {
    while (!m_areaWinds.empty()) {
        removeAreaWind(*m_areaWinds.begin()->m_pOwner);
    }
    while (!m_probes.empty()) {
        removeProbe(*m_probes.begin());
    }
    delayErace();
    if (m_pDispatcher != nullptr) {
        m_pDispatcher->release();
        m_pDispatcher = nullptr;
    }
    if (m_pBroadPhaze != nullptr) {
        m_pBroadPhaze->release();
        m_pBroadPhaze = nullptr;
    }
}

void WindWorld::removeAreaWind(AreaWind& wind) {
#line 144
    MM_ASSERT(m_pBroadPhaze);
    m_pBroadPhaze->removeWindObject(wind);
    m_areaWinds.remove(&wind.m_worldNode);
    m_releaseList.push_back(&wind.m_releaseNode);
}

void WindWorld::removeProbe(WindProbe& probe) {
    probe.setAreaWind(nullptr);
    probe.unbindGlobalWind();
    m_pBroadPhaze->destroyProxy(probe);
    m_probes.remove(&probe);
    probe.m_hitCaches.clear();
    m_releaseList.push_back(&probe.m_releaseNode);
}

void WindWorld::delayErace() {
    while (!m_releaseList.empty()) {
        WindObject* object = m_releaseList.begin()->m_pOwner;
        m_releaseList.remove(&object->m_releaseNode);
        object->release();
    }
}

// the objects let go of released, the time stepped, the global wind and each probe's power from it
void WindWorld::update(float deltaTime) {
    delayErace();
    m_time += deltaTime;
    UpdateInfo info = {m_time, deltaTime, m_debugMode};
    m_globalWindManager.m_globalWind.update(info);
    if (!m_probes.empty()) {
        for (mm::mtl::IntrusiveList<WindProbe>::iterator it = m_probes.begin(); it != m_probes.end(); ++it) {
            it->calcGlobalWindPower(info);
        }
    }
}

bool WindWorld::addAreaWind(AreaWind& wind) {
#line 126
    MM_ASSERT(m_pBroadPhaze);
    bool added = m_pBroadPhaze->addWindObject(wind);
    if (added) {
        wind.addRef();
        m_areaWinds.push_back(&wind.m_worldNode);
    }
    return added;
}

bool WindWorld::addProbe(WindProbe& probe) {
    probe.addRef();
    m_probes.push_back(&probe);
    m_pBroadPhaze->createProxy(probe);
    probe.bindGlobalWind(m_globalWindManager.m_globalWind);
    return true;
}

}  // namespace wnd

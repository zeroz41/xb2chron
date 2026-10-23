#include "classes/fw/WindManager.h"
#include "classes/fw/FrameworkMemory.h"
#include "fw/ParamBuilder.h"
#include "arc/CArcData.h"

namespace fw {
WindManager::WindManager() : m_world(nullptr), m_resource(nullptr), pad_80{} {}

WindManager::~WindManager() {
    if (m_resource != nullptr) {
        m_resource->release();
        m_resource = nullptr;
    }
}

bool WindManager::setGlobalWind(int index) {
    return m_world != nullptr ? m_world->m_globalWindManager.setCurrentWind(index) : false;
}

void WindManager::destroyWorld() {
    if (m_defaultProbe.get() != nullptr) {
        m_defaultProbe = nullptr;
    }
    if (m_mainProbe.get() != nullptr) {
        m_mainProbe = nullptr;
    }
    if (m_world != nullptr) {
        m_world->release();
        m_world = nullptr;
    }
}

const mm::Vec3& WindManager::getGlobalWindPower() {
    WindManager* manager = get();
    if (manager == nullptr) {
        return mm::Vec3::zero;
    }
    if (manager->m_mainProbe.get() != nullptr) {
        wnd::WindProbe* probe = manager->m_mainProbe.get()->m_pProbe;
        return probe->m_blender.m_winds[probe->m_windIndex];
    }
    if (manager->m_defaultProbe.get() != nullptr) {
        return manager->m_defaultProbe.get()->m_pProbe->m_blender.m_winds[0];
    }
    return mm::Vec3::zero;
}

void WindManager::addProbe(WindProbe* probe) {
    m_probes.push_back(probe);
    if (m_world != nullptr) {
        m_world->addProbe(*probe->m_pProbe);
    }
    if (probe->m_isMain) {
        m_mainProbe = probe;
    }
}

void WindManager::removeProbe(WindProbe* probe) {
    if (m_mainProbe.get() == probe) {
        m_mainProbe = nullptr;
    }
    if (m_world != nullptr) {
        m_world->removeProbe(*probe->m_pProbe);
    }
    m_probes.remove(probe);
}

bool WindManager::initialize() {
    if (m_resource == nullptr) {
        m_resource = CommonResource::request(FrameworkMemory::getAllocator(5), "/param/wind.prm", 10, false);
        if (m_resource == nullptr) {
            return false;
        }
    }
    if (!m_resource->valid()) {
        return false;
    }
    arc::CArcData archive(m_resource->getAssetData());
    m_params = ParamBuilder::importBinary(archive.getFileAdr("wind.param"), nullptr);
    return true;
}

const char* WindManager::getName() const { return "WindManager"; }
}  // namespace fw

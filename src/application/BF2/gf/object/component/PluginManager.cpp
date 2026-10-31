#include "gf/PluginManager.h"

#include "classes/gf/Plugin.h"

namespace gf {

PluginManager::PluginManager(mm::mtl::IAllocator* allocator)
    : m_creators(allocator), m_plugins(allocator), m_enabled(allocator), m_behavior(nullptr), m_inSetup(false) {}

void PluginManager::beginSetup(GfComBehavior& behavior, unsigned int count) {
    m_creators.resize(count, nullptr);
    m_plugins.resize(count, nullptr);
    m_enabled.resize(count, false);
    m_behavior = &behavior;
    m_inSetup = true;
}

void PluginManager::endSetup() {
    for (unsigned int i = 0; i < m_creators.size(); i++) {
        if (m_creators[i] && m_enabled[i]) {
            m_plugins[i] = m_creators[i]();
        }
    }
    for (unsigned int i = 0; i < m_plugins.size(); i++) {
        if (m_plugins[i] && !m_plugins[i]->onSetup(*m_behavior)) {
            if (m_plugins[i]) {
                delete m_plugins[i];
                m_plugins[i] = nullptr;
            }
        }
    }
    m_inSetup = false;
}

void PluginManager::cleanup() {
    if (m_behavior) {
        for (unsigned int i = 0; i < m_plugins.size(); i++) {
            if (m_plugins[i]) {
                m_plugins[i]->onCleanup(*m_behavior);
                if (m_plugins[i]) {
                    delete m_plugins[i];
                    m_plugins[i] = nullptr;
                }
            }
        }
    }
}

void PluginManager::update(const fw::UpdateInfo& info) {
    for (unsigned int i = 0; i < m_plugins.size(); i++) {
        if (m_plugins[i] && m_plugins[i]->m_active) {
            m_plugins[i]->onUpdate(*m_behavior, info);
        }
    }
}

}  // namespace gf

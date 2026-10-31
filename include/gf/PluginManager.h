#ifndef GF_PLUGINMANAGER_H
#define GF_PLUGINMANAGER_H

#include "classes/gf/Plugin.h"
#include "mm/mtl/RTTI.h"
#include "mm/mtl/Vector.h"

namespace fw { class UpdateInfo; }
namespace mm { namespace mtl { class IAllocator; } }
namespace gf { class GfComBehavior; }

namespace gf {
// a behavior component's plugins (GfComBehavior holds one at 0x10): three vectors on one allocator
// (its destructor asserts mm_mtl/vector.h's `m_allocator` for each) and a flag at 0x80
class PluginManager {
public:
    typedef Plugin* (*Creator)();

    PluginManager(mm::mtl::IAllocator* allocator);
    // inline: its vectors go; GfComBehaviorEnemy's unit holds the weak copy the module kept
    ~PluginManager() {}
    // sizes the vectors for count plugins, none to make yet
    void beginSetup(GfComBehavior& behavior, unsigned int count);
    // makes the plugins whose creator is set and enabled; drops those whose setup fails
    void endSetup();
    void cleanup();
    void update(const fw::UpdateInfo& info);

    // the plugin with an id, none past the table (inline: the name is not the original's)
    Plugin* getPlugin(unsigned int id) const {
        if (id < m_plugins.size()) {
            return m_plugins[id];
        }
        return nullptr;
    }
    // T's plugin, by T's id: none when it is none or another kind (inline: the name is not the original's)
    template <typename T>
    T* getPlugin() const {
        Plugin* plugin = getPlugin(T::PLUGIN_ID);
        return plugin != nullptr && plugin->getRTTI()->isKindOf(&T::m_rtti) ? static_cast<T*>(plugin) : nullptr;
    }

    // between beginSetup and endSetup: the plugin endSetup makes at index, and whether it does (inline: the name
    // is not the original's)
    void setCreator(unsigned int index, Creator creator, bool enabled) {
        m_creators[index] = creator;
        m_enabled[index] = enabled;
    }
    // T's plugin made by its creator (when one is set) and set up on the behavior; GfComBehaviorPc makes the pad
    // plugins this way when a PC goes back under pad control (inline template: proven by its instances' code)
    template <typename T>
    void createPlugin() {
        if (m_creators[T::PLUGIN_ID]) {
            m_plugins[T::PLUGIN_ID] = m_creators[T::PLUGIN_ID]();
            if (m_plugins[T::PLUGIN_ID]) {
                m_plugins[T::PLUGIN_ID]->onSetup(*m_behavior);
            }
        }
    }
    // T's plugin (when there is one) cleaned up on the behavior and deleted (inline template)
    template <typename T>
    void destroyPlugin() {
        if (m_plugins[T::PLUGIN_ID]) {
            m_plugins[T::PLUGIN_ID]->onCleanup(*m_behavior);
            if (m_plugins[T::PLUGIN_ID]) {
                delete m_plugins[T::PLUGIN_ID];
                m_plugins[T::PLUGIN_ID] = nullptr;
            }
        }
    }
    mm::mtl::Vector<Creator> m_creators;  // endSetup calls each set one
    mm::mtl::Vector<Plugin*> m_plugins;   // endSetup stores what the creators made
    mm::mtl::Vector<bool> m_enabled;      // endSetup skips a creator whose flag is clear
    GfComBehavior* m_behavior;            // beginSetup's; endSetup sets the plugins up on it
    bool m_inSetup;                       // beginSetup sets it, endSetup clears it
};
}  // namespace gf

#endif

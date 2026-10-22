#ifndef GF_PLUGINMANAGER_H
#define GF_PLUGINMANAGER_H

#include "mm/mtl/Vector.h"
#include "mm/mtl/RTTI.h"
#include "classes/gf/Plugin.h"

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
    ~PluginManager();
    // sizes the vectors for count plugins, none to make yet
    void beginSetup(GfComBehavior& behavior, unsigned int count);
    // makes the plugins whose creator is set and enabled; drops those whose setup fails
    void endSetup();
    void cleanup();
    void update(const fw::UpdateInfo& info);

    // between beginSetup and endSetup: the plugin endSetup makes at index, and whether it does (inline: the name
    // is not the original's)
    void setCreator(unsigned int index, Creator creator, bool enabled) {
        m_creators[index] = creator;
        m_enabled[index] = enabled;
    }
    mm::mtl::Vector<Creator> m_creators;  // endSetup calls each set one
    mm::mtl::Vector<Plugin*> m_plugins;   // endSetup stores what the creators made
    mm::mtl::Vector<bool> m_enabled;      // endSetup skips a creator whose flag is clear
    GfComBehavior* m_behavior;            // beginSetup's; endSetup sets the plugins up on it
    bool m_inSetup;                       // beginSetup sets it, endSetup clears it
};
}  // namespace gf

#endif

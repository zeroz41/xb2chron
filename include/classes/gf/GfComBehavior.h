#ifndef CLASSES_GF_GFCOMBEHAVIOR_H
#define CLASSES_GF_GFCOMBEHAVIOR_H

#include "mm/mtl/RTTI.h"
#include "classes/gf/GfComponent.h"
#include "fw/Allocator.h"
#include "gf/PluginManager.h"

namespace fw { class UpdateInfo; }
namespace gf { class CallBackCache; }
namespace gf { class GfComAsm; }

namespace gf {
// table 0x7100B65EE0
class GfComBehavior : public ::gf::GfComponent {
public:
    GfComBehavior() : m_pluginManager(fw::Allocator::getProcAllocator()) {}
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~GfComBehavior() {}  // slot 1: inline (GfComBehaviorMapLodAnim's deleting one has its body)
    virtual void changeLayer(unsigned int, unsigned int);  // slot 3
    virtual void update(fw::UpdateInfo const&) = 0;  // slot 5
    virtual void procAnimCallback(gf::GfComAsm*, gf::CallBackCache const&);  // slot 6
    // what the asm component calls back with its animation events
    void callbackAnim(gf::GfComAsm* com, const gf::CallBackCache& cache);
    // the plugin at index as a T, none when there is none or it is another kind (inline: the name is not the
    // original's)
    template <typename T>
    T* getPlugin(unsigned int index) const {
        if (index < m_pluginManager.m_plugins.size()) {
            Plugin* plugin = m_pluginManager.m_plugins[index];
            if (plugin != nullptr) {
                return plugin->getRTTI()->isKindOf(&T::m_rtti) ? static_cast<T*>(plugin) : nullptr;
            }
        }
        return nullptr;
    }
    static mm::mtl::RTTI m_rtti;
    PluginManager m_pluginManager;  // destroyed by the destructor
};
}  // namespace gf

#endif

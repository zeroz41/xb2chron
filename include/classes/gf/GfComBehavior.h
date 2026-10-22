#ifndef CLASSES_GF_GFCOMBEHAVIOR_H
#define CLASSES_GF_GFCOMBEHAVIOR_H

#include "mm/mtl/RTTI.h"
#include "classes/gf/GfComponent.h"
#include "gf/PluginManager.h"

namespace fw { class UpdateInfo; }
namespace gf { class CallBackCache; }
namespace gf { class GfComAsm; }

namespace gf {
// table 0x7100B65EE0
class GfComBehavior : public ::gf::GfComponent {
public:
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~GfComBehavior() {}  // slot 1: inline (GfComBehaviorMapLodAnim's deleting one has its body)
    virtual void changeLayer(unsigned int, unsigned int);  // slot 3
    virtual void update(fw::UpdateInfo const&) = 0;  // slot 5
    virtual void procAnimCallback(gf::GfComAsm*, gf::CallBackCache const&);  // slot 6
    static mm::mtl::RTTI m_rtti;
    PluginManager m_pluginManager;  // destroyed by the destructor
};
}  // namespace gf

#endif

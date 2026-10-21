#ifndef CLASSES_GF_PLUGIN_H
#define CLASSES_GF_PLUGIN_H

#include "mm/mtl/RTTI.h"

namespace fw { class UpdateInfo; }
namespace gf { class GfComBehavior; }

namespace gf {
// table 0x7100B65938
class Plugin {
public:
    Plugin();
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~Plugin();  // slot 1
    virtual void onActivate() {}  // slot 3
    virtual void onDeactivate() {}  // slot 4
    virtual void onSetup(gf::GfComBehavior&) = 0;  // slot 5
    virtual void onCleanup(gf::GfComBehavior&) = 0;  // slot 6
    virtual void onUpdate(gf::GfComBehavior&, fw::UpdateInfo const&) = 0;  // slot 7
    void setActivate(bool active);

    static mm::mtl::RTTI m_rtti;

    bool m_active;  // set by setActivate, which calls onActivate or onDeactivate when it changes
};
}  // namespace gf

#endif

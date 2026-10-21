#ifndef CLASSES_GF_PC_LUREPLUGIN_H
#define CLASSES_GF_PC_LUREPLUGIN_H

#include "classes/gf/Plugin.h"

namespace fw { class UpdateInfo; }
namespace gf { class GF_OBJ_HANDLE; }
namespace gf { class GfComBehavior; }
namespace gf { class GfComBehaviorPc; }

namespace gf { namespace pc {
// table 0x7100B699C0
class LurePlugin : public ::gf::Plugin {
public:
    // its getRTTI, destructor and on* wrappers are inline in the original; the destructor releases the
    // parameter list at +0x18 (an mm::mtl::IntrusivePtr), which has no declaration yet
    virtual const mm::mtl::RTTI* getRTTI() const;  // slot 0
    virtual ~LurePlugin();  // slot 1
    virtual void onActivate();  // slot 3
    virtual void onDeactivate();  // slot 4
    virtual void onSetup(gf::GfComBehavior&);  // slot 5
    virtual void onCleanup(gf::GfComBehavior&);  // slot 6
    virtual void onUpdate(gf::GfComBehavior&, fw::UpdateInfo const&);  // slot 7
    virtual bool setup(gf::GfComBehaviorPc&);  // slot 8
    virtual void cleanup(gf::GfComBehaviorPc&);  // slot 9
    virtual void update(gf::GfComBehaviorPc&, fw::UpdateInfo const&);  // slot 10

    static mm::mtl::RTTI m_rtti;

    gf::GF_OBJ_HANDLE* m_target;  // the lure's target (StateUtilField::getLureTargetHandle's; -1: none)
};
}}  // namespace gf::pc

#endif

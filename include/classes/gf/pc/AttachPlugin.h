#ifndef CLASSES_GF_PC_ATTACHPLUGIN_H
#define CLASSES_GF_PC_ATTACHPLUGIN_H

#include "classes/gf/GfComBehaviorPc.h"
#include "classes/gf/Plugin.h"
#include "fw/Transform.h"

namespace fw { class UpdateInfo; }
namespace gf { class GF_OBJ_HANDLE; }

namespace gf { namespace pc {
// table 0x7100B695B8
class AttachPlugin : public ::gf::Plugin {
public:
    AttachPlugin();
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~AttachPlugin();  // slot 1
    virtual void onActivate();  // slot 3
    virtual void onDeactivate();  // slot 4
    virtual void onSetup(gf::GfComBehavior& behavior) {  // slot 5
        setup(static_cast<gf::GfComBehaviorPc&>(behavior));
    }
    virtual void onCleanup(gf::GfComBehavior& behavior) {  // slot 6
        cleanup(static_cast<gf::GfComBehaviorPc&>(behavior));
    }
    virtual void onUpdate(gf::GfComBehavior& behavior, fw::UpdateInfo const& info) {  // slot 7
        update(static_cast<gf::GfComBehaviorPc&>(behavior), info);
    }
    virtual bool setup(gf::GfComBehaviorPc&);  // slot 8
    virtual void cleanup(gf::GfComBehaviorPc&);  // slot 9
    virtual void update(gf::GfComBehaviorPc&, fw::UpdateInfo const&);  // slot 10
    // 1.0.0's: detaches the PC from what it is attached to and clears its dynamics' movement (inline in 3.0.1,
    // which has no copy of it)
    void dettachObj();
    void attachObj(gf::GF_OBJ_HANDLE* obj);
    void notifyMovement();
    void notifyExcludeMovementRider(const fw::Transform& transform);
    void changeWallMode(bool wall);

    // its slot in a PluginManager (getPlugin<AttachPlugin> reads slot 12)
    enum { PLUGIN_ID = 12 };

    enum {
        FLAG_ATTACH = 1 << 0,     // update sets it once attachObj has attached the PC, cleanup clears it
        FLAG_WALL_MODE = 1 << 1,  // changeWallMode's
    };

    static mm::mtl::RTTI m_rtti;

    unsigned int m_flags;
    gf::GF_OBJ_HANDLE* m_attachObj;   // what the PC is attached to (-1: nothing); onDeactivate detaches it
    gf::GfComBehaviorPc* m_behavior;  // the behavior setup was given, cleared by cleanup
    // the world transform of what the PC is attached to, as attachObj and notifyMovement last took it (the
    // constructor's: zero and identity; the name is not the original's)
    fw::Transform m_attachTransform;
};
}}  // namespace gf::pc

#endif

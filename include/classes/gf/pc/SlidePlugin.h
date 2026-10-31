#ifndef CLASSES_GF_PC_SLIDEPLUGIN_H
#define CLASSES_GF_PC_SLIDEPLUGIN_H

#include "classes/gf/GfComBehaviorPc.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/Plugin.h"

namespace fw { class UpdateInfo; }

namespace gf { namespace pc {
// table 0x7100B69A28
class SlidePlugin : public ::gf::Plugin {
public:
    SlidePlugin();
    // its index in GfComBehaviorPc's plugins (setup sets its creator there)
    enum { PLUGIN_ID = 10 };
    // what GfComBehaviorPc's plugin manager makes it with (inline: gf_com_behavior_pc's unit emits it, citing
    // this header)
    static Plugin* create() {
#line 26 "D:/Monolithsoft/BF2/prog/application/BF2\\gf/object/component/pc/plugin/gf_pc_slide_plugin.h"
        return new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) SlidePlugin;
    }
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~SlidePlugin() {}  // slot 1
    virtual void onActivate();  // slot 3
    virtual void onDeactivate();  // slot 4
    virtual bool onSetup(gf::GfComBehavior& behavior) {  // slot 5
        return setup(static_cast<gf::GfComBehaviorPc&>(behavior));
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

    static mm::mtl::RTTI m_rtti;
};
}}  // namespace gf::pc

#endif

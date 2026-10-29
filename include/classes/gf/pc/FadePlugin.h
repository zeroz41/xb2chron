#ifndef CLASSES_GF_PC_FADEPLUGIN_H
#define CLASSES_GF_PC_FADEPLUGIN_H

#include "classes/gf/GfComBehaviorPc.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/Plugin.h"
#include "fw/ParamAdapter.h"

namespace fw { class UpdateInfo; }

namespace gf { namespace pc {
// table 0x7100B696F0
class FadePlugin : public ::gf::Plugin {
public:
    // its parameter entry (the PC's field parameter list's 18); the name is not the original's
    struct Param {
        float m_fadeOutWait;  // update waits this long after the fade to black starts
        float m_blackWait;    // then this long before fading back in
        float m_fadeTime;     // each fade's length (create takes it at 30 frames a second); the fade in ends the plugin
    };

    FadePlugin();
    // its index in GfComBehaviorPc's plugins (setup sets its creator there)
    enum { PLUGIN_ID = 11 };
    // what GfComBehaviorPc's plugin manager makes it with (inline: gf_com_behavior_pc's unit emits it, citing
    // this header)
    static Plugin* create() {
#line 34 "D:/Monolithsoft/BF2/prog/application/BF2\\gf/object/component/pc/plugin/gf_pc_fade_plugin.h"
        return new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) FadePlugin;
    }
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~FadePlugin();  // slot 1
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

    static mm::mtl::RTTI m_rtti;

    int m_state;   // the fade's step: onActivate starts it at 3, update moves it on as m_time passes each step's time
    float m_time;  // the time spent in the current step
    unsigned char pad_14[0x4];
    fw::ParamAdapter m_param;  // setup finds it
};
}}  // namespace gf::pc

#endif

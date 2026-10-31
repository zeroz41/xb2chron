#ifndef CLASSES_GF_PC_COLVELCALCULATORPLUGIN_H
#define CLASSES_GF_PC_COLVELCALCULATORPLUGIN_H

#include "classes/gf/GfComBehaviorPc.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/Plugin.h"

namespace fw { class UpdateInfo; }

namespace gf { namespace pc {
// table 0x7100B69620
class ColVelCalculatorPlugin : public ::gf::Plugin {
public:
    // the PC's parameter entry update reads (the property's list's 1); the name is not the original's
    struct Param {
        unsigned char pad_0[0x10];
        float m_brake;     // how fast the carried movement dies down off the ground, per second
        float m_maxSpeed;  // the carried movement's top speed
    };

    ColVelCalculatorPlugin();
    // its index in GfComBehaviorPc's plugins (setup sets its creator there)
    enum { PLUGIN_ID = 13 };
    // what GfComBehaviorPc's plugin manager makes it with (inline: gf_com_behavior_pc's unit emits it, citing
    // this header)
    static Plugin* create() {
#line 27 "D:/Monolithsoft/BF2/prog/application/BF2\\gf/object/component/pc/plugin/gf_pc_col_velocity_plugin.h"
        return new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) ColVelCalculatorPlugin;
    }
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~ColVelCalculatorPlugin() {}  // slot 1
    virtual void onActivate();  // slot 3
    virtual bool onSetup(gf::GfComBehavior& behavior) {  // slot 5
        return setup(static_cast<gf::GfComBehaviorPc&>(behavior));
    }
    virtual void onCleanup(gf::GfComBehavior& behavior) {  // slot 6
        cleanup(static_cast<gf::GfComBehaviorPc&>(behavior));
    }
    virtual void onUpdate(gf::GfComBehavior& behavior, fw::UpdateInfo const& info) {  // slot 7
        update(static_cast<gf::GfComBehaviorPc&>(behavior), info);
    }
    virtual bool setup(gf::GfComBehaviorPc&) { return true; }  // slot 8
    virtual void cleanup(gf::GfComBehaviorPc&) {}  // slot 9
    virtual void update(gf::GfComBehaviorPc&, fw::UpdateInfo const&);  // slot 10

    static mm::mtl::RTTI m_rtti;

    bool m_onGround;  // update sets it each update the PC stands on ground and clears it otherwise
};
}}  // namespace gf::pc

#endif

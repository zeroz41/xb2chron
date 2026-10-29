#ifndef CLASSES_GF_PC_LOOKAXISPLUGIN_H
#define CLASSES_GF_PC_LOOKAXISPLUGIN_H

#include "classes/gf/GfComBehaviorPc.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/Plugin.h"
#include "fw/ParamAdapter.h"

namespace fw { class UpdateInfo; }

namespace gf { namespace pc {
// table 0x7100B69958
class LookAxisPlugin : public ::gf::Plugin {
public:
    // its parameter block: entry 4 of the param manager's list 5 (the names are not the original's)
    struct Param {
        unsigned char pad_0[0x14];
        float m_changeDuration;  // the time a changeAxisYaw change takes
    };

    LookAxisPlugin();
    // its index in GfComBehaviorPc's plugins (setup sets its creator there)
    enum { PLUGIN_ID = 20 };
    // what GfComBehaviorPc's plugin manager makes it with (inline: gf_com_behavior_pc's unit emits it, citing
    // this header)
    static Plugin* create() {
#line 27 "D:/Monolithsoft/BF2/prog/application/BF2\\gf/object/component/pc/plugin/gf_pc_look_axis_plugin.h"
        return new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) LookAxisPlugin;
    }
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~LookAxisPlugin() {}  // slot 1
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
    void setYaw(float yaw);
    void changeAxisYaw(float yaw);

    static mm::mtl::RTTI m_rtti;

    gf::GfComBehaviorPc* m_behavior;  // the behavior setup was given
    float m_yaw;                      // setYaw's
    float m_startYaw;                 // changeAxisYaw's: the yaw a change starts from
    float m_targetYaw;                // changeAxisYaw's: the yaw a change ends at
    float m_changeTime;               // the time a change has run; update blends the yaws by it
    bool m_changing;                  // changeAxisYaw sets it, update clears it when the change is over
    fw::ParamAdapter m_param;         // setup finds it in the param manager's list 5
};
}}  // namespace gf::pc

#endif

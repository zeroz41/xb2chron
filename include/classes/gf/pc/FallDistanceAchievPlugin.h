#ifndef CLASSES_GF_PC_FALLDISTANCEACHIEVPLUGIN_H
#define CLASSES_GF_PC_FALLDISTANCEACHIEVPLUGIN_H

#include "classes/gf/GfComBehaviorPc.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/Plugin.h"

namespace fw { class UpdateInfo; }
namespace gf { class GfComPropertyPc; }

namespace gf { namespace pc {
// table 0x7100B697C0
class FallDistanceAchievPlugin : public ::gf::Plugin {
public:
    FallDistanceAchievPlugin();
    // its index in GfComBehaviorPc's plugins (setup sets its creator there)
    enum { PLUGIN_ID = 21 };
    // what GfComBehaviorPc's plugin manager makes it with (inline: gf_com_behavior_pc's unit emits it, citing
    // this header)
    static Plugin* create() {
#line 26 "D:/Monolithsoft/BF2/prog/application/BF2\\gf/object/component/pc/plugin/gf_pc_fall_distance_achiev_plugin.h"
        return new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) FallDistanceAchievPlugin;
    }
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~FallDistanceAchievPlugin();  // slot 1
    virtual void onActivate();  // slot 3
    virtual void onDeactivate();  // slot 4
    virtual void onSetup(gf::GfComBehavior& behavior) {  // slot 5
        setup(static_cast<gf::GfComBehaviorPc&>(behavior));
    }
    virtual void onCleanup(gf::GfComBehavior& behavior) {  // slot 6
        cleanup(static_cast<gf::GfComBehaviorPc&>(behavior));
    }
    virtual void onUpdate(gf::GfComBehavior&, fw::UpdateInfo const&);  // slot 7 (inline in the original; its body reads the property)
    virtual bool setup(gf::GfComBehaviorPc&);  // slot 8
    virtual void cleanup(gf::GfComBehaviorPc&);  // slot 9

    static mm::mtl::RTTI m_rtti;

    gf::GfComPropertyPc* m_property;  // the PC's property component, found by setup
    float m_maxHeight;                // the highest the PC reaches while active; landing below it by 10 counts
};
}}  // namespace gf::pc

#endif

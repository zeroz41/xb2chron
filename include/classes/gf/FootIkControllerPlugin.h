#ifndef CLASSES_GF_FOOTIKCONTROLLERPLUGIN_H
#define CLASSES_GF_FOOTIKCONTROLLERPLUGIN_H

#include "classes/gf/Plugin.h"
#include "classes/gf/GfAllocator.h"

namespace fw { class UpdateInfo; }
namespace gf { class GfComBehavior; }

namespace gf {
// table 0x7100B656B0: drives the ground solvers of its object's IK component from the asm state's attributes
class FootIkControllerPlugin : public ::gf::Plugin {
public:
    // which ground solver it drives: setup picks it from the solvers the IK component has, switchMode changes it
    // (StateUtil::switchPlacementIK picks the slope for true); 1.0.0's type name, the value names are not the
    // original's
    enum Mode {
        MODE_NONE = 0,
        MODE_PLACEMENT = 1,  // fw::PlacementGroundSolver
        MODE_SLOPE = 2,      // fw::SlopeGroundSolver
        MODE_TWO_CHARA = 3,  // fw::TwoCharaGroundSolver
    };
    // its index in a behavior's plugins (GfComBehavior::callbackAnim reads it from index 3)
    enum { PLUGIN_ID = 3 };

    FootIkControllerPlugin();
    static Plugin* create() {
#line 24 "D:/Monolithsoft/BF2/prog/application/BF2\\gf/object/component/behavior/plugin/gf_foot_ik_controller_plugin.h"
        return new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) FootIkControllerPlugin;
    }
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~FootIkControllerPlugin() {}  // slot 1
    virtual void onActivate();  // slot 3
    virtual void onDeactivate();  // slot 4
    virtual void onSetup(gf::GfComBehavior& behavior) { setup(behavior); }  // slot 5
    virtual void onCleanup(gf::GfComBehavior& behavior) { cleanup(behavior); }  // slot 6
    virtual void onUpdate(gf::GfComBehavior& behavior, fw::UpdateInfo const& info) {  // slot 7
        update(behavior, info);
    }
    virtual bool setup(gf::GfComBehavior&);  // slot 8
    virtual void cleanup(gf::GfComBehavior&);  // slot 9
    virtual void update(gf::GfComBehavior&, fw::UpdateInfo const&);  // slot 10
    // the asm component's attribute bits (category 0, layer 0), none without one
    unsigned long getASMStateAttribute(gf::GfComBehavior& behavior) const;
    void setGroundPlacement(bool enable);
    void switchMode(Mode mode);

    static mm::mtl::RTTI m_rtti;

    gf::GfComBehavior* m_behavior;  // the behavior setup was given, cleared by cleanup
    Mode m_mode;                    // switchMode's
    // the names below are not the original's
    bool m_switcher;               // setup's: the IK has both a slope and a placement solver, so switchMode may
                                   // change the mode (StateUtil::setEnableHeadDetectForSwitcher tests it too)
    bool m_groundPlacement;        // setGroundPlacement's
    bool m_enableDownIK;           // StateUtil::setEnableDownIK and GfComBehaviorEvent::setFootIK set it,
                                   // switchMode clears it
    bool m_enableGroundPlacement;  // ground placement follows the attribute 0x1 only while set (from the start)
    bool m_syncDown;               // the "ikEvent" animation callbacks "syncDownOn" and "syncDownOff" set it
};
}  // namespace gf

#endif

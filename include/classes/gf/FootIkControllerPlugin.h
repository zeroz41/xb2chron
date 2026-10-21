#ifndef CLASSES_GF_FOOTIKCONTROLLERPLUGIN_H
#define CLASSES_GF_FOOTIKCONTROLLERPLUGIN_H

#include "classes/gf/Plugin.h"

namespace fw { class UpdateInfo; }
namespace gf { class GfComBehavior; }

namespace gf {
// table 0x7100B656B0
class FootIkControllerPlugin : public ::gf::Plugin {
public:
    enum Mode {};  // setup picks 1 to 3 from the ground solvers the IK has; values not named yet

    FootIkControllerPlugin();
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
    void setGroundPlacement(bool enable);
    void switchMode(Mode mode);

    static mm::mtl::RTTI m_rtti;

    gf::GfComBehavior* m_behavior;  // the behavior setup was given, cleared by cleanup
    Mode m_mode;                    // switchMode's
};
}  // namespace gf

#endif

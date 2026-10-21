#ifndef CLASSES_GF_PC_COLVELCALCULATORPLUGIN_H
#define CLASSES_GF_PC_COLVELCALCULATORPLUGIN_H

#include "classes/gf/GfComBehaviorPc.h"
#include "classes/gf/Plugin.h"

namespace fw { class UpdateInfo; }

namespace gf { namespace pc {
// table 0x7100B69620
class ColVelCalculatorPlugin : public ::gf::Plugin {
public:
    ColVelCalculatorPlugin();
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~ColVelCalculatorPlugin() {}  // slot 1
    virtual void onActivate();  // slot 3
    virtual void onSetup(gf::GfComBehavior& behavior) {  // slot 5
        setup(static_cast<gf::GfComBehaviorPc&>(behavior));
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

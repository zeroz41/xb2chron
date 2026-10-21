#ifndef CLASSES_GF_PC_WATERINPLUGIN_H
#define CLASSES_GF_PC_WATERINPLUGIN_H

#include "classes/gf/GfComBehaviorPc.h"
#include "classes/gf/Plugin.h"

namespace fw { class UpdateInfo; }

namespace gf { namespace pc {
// table 0x7100B69BC8
class WaterInPlugin : public ::gf::Plugin {
public:
    WaterInPlugin();
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~WaterInPlugin();  // slot 1
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
    void onEvent(gf::GfComBehaviorPc& behavior);

    static mm::mtl::RTTI m_rtti;

    gf::GfComBehaviorPc* m_behavior;  // the behavior setup was given, cleared by cleanup
    bool m_eventDone;                 // onEvent sets it; update and onDeactivate do nothing more once it is set
};
}}  // namespace gf::pc

#endif

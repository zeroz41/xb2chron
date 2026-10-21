#ifndef CLASSES_GF_PC_TIMERPLUGIN_H
#define CLASSES_GF_PC_TIMERPLUGIN_H

#include "classes/gf/GfComBehaviorPc.h"
#include "classes/gf/Plugin.h"

namespace fw { class UpdateInfo; }

namespace gf { namespace pc {
// table 0x7100B69B60
class TimerPlugin : public ::gf::Plugin {
public:
    enum TYPE {
        TYPE_NUM = 1  // its one value has no name yet
    };
    // a timer that counts while it is active, from zero each time it is activated
    struct Timer {
        bool m_activate;
        float m_time;
    };

    TimerPlugin();
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~TimerPlugin() {}  // slot 1
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
    void setActivateTimer(TYPE type, bool activate);

    static mm::mtl::RTTI m_rtti;

    Timer m_timers[TYPE_NUM];
};
}}  // namespace gf::pc

#endif

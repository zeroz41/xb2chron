#ifndef CLASSES_GF_EVTBGMTASKDELAYSTOP_H
#define CLASSES_GF_EVTBGMTASKDELAYSTOP_H

#include "classes/gf/EvtBgmTask.h"
#include "classes/gf/GfEvtBgm.h"

namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B53B38: stops the event BGM after its setup's m_stopTime (GfEvtBgm::playBgm and stopBgm queue it)
class EvtBgmTaskDelayStop : public ::gf::EvtBgmTask {
public:
    // out of line in 1.0.0; inline in 3.0.1
    EvtBgmTaskDelayStop(const EventBgmSetup& setup) : m_setup(setup), m_time(setup.m_stopTime), m_cancel(false) {}
    virtual void start(gf::GfEvtBgm*);  // slot 4
    virtual bool update(gf::GfEvtBgm*, fw::UpdateInfo const&);  // slot 5
    virtual void cancel(gf::GfEvtBgm*);  // slot 6
    static EvtBgmTaskDelayStop* create(const EventBgmSetup& setup);

    EventBgmSetup m_setup;  // what the event BGM's setup becomes when it stops
    float m_time;  // the time left before it stops; the name is not the original's
    bool m_cancel;  // cancel sets it: update then ends the task at once; the name is not the original's
};
}  // namespace gf

#endif

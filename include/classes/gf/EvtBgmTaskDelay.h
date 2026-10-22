#ifndef CLASSES_GF_EVTBGMTASKDELAY_H
#define CLASSES_GF_EVTBGMTASKDELAY_H

#include "classes/gf/EvtBgmTask.h"
#include "classes/gf/GfEvtBgm.h"

namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B53AF0: plays a BGM after its setup's delay (GfEvtBgm::playBgm queues it)
class EvtBgmTaskDelay : public ::gf::EvtBgmTask {
public:
    // out of line in 1.0.0; inline in 3.0.1
    EvtBgmTaskDelay(const EventBgmSetup& setup) : m_setup(setup), m_cancel(false) {}
    virtual bool isPlayTask() const { return true; }  // slot 3
    virtual void start(gf::GfEvtBgm*);  // slot 4
    virtual bool update(gf::GfEvtBgm*, fw::UpdateInfo const&);  // slot 5
    virtual void cancel(gf::GfEvtBgm*);  // slot 6
    static EvtBgmTaskDelay* create(const EventBgmSetup& setup);

    EventBgmSetup m_setup;  // the BGM to play; update counts its m_delay down
    bool m_cancel;  // cancel sets it: update then ends the task at once; the name is not the original's
};
}  // namespace gf

#endif

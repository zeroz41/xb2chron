#ifndef CLASSES_GF_EVTBGMTASKVOLUME_H
#define CLASSES_GF_EVTBGMTASKVOLUME_H

#include "classes/gf/EvtBgmTask.h"
#include "classes/gf/GfEvtBgm.h"

namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B53B80: moves the event BGM's volume to a setup's m_volume over its m_volumeTime
// (GfEvtBgm::changeBgmVolume queues it)
class EvtBgmTaskVolume : public ::gf::EvtBgmTask {
public:
    // out of line in 1.0.0; inline in 3.0.1
    EvtBgmTaskVolume(const EventBgmSetup& setup) : m_time(setup.m_volumeTime), m_volume(setup.m_volume), m_cancel(false) {}
    virtual bool isVolumeTask() const { return true; }  // slot 2
    virtual void start(gf::GfEvtBgm*);  // slot 4
    virtual bool update(gf::GfEvtBgm*, fw::UpdateInfo const&);  // slot 5
    virtual void cancel(gf::GfEvtBgm*);  // slot 6
    static EvtBgmTaskVolume* create(const EventBgmSetup& setup);

    float m_time;  // the time left to reach m_volume; the name is not the original's
    float m_volume;  // the volume to reach; the name is not the original's
    bool m_cancel;  // cancel sets it: update then ends the task at once; the name is not the original's
};
}  // namespace gf

#endif

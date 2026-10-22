#ifndef CLASSES_GF_EVTBGMTASK_H
#define CLASSES_GF_EVTBGMTASK_H

namespace fw { class UpdateInfo; }
namespace gf { class GfEvtBgm; }

namespace gf {
// table none (its derived classes'): a step GfEvtBgm queues and runs one at a time (GfEvtBgm::updateBgmTask starts
// the first, updates it until update returns true, then deletes it)
class EvtBgmTask {
public:
    virtual ~EvtBgmTask() {}  // slot 0
    virtual bool isVolumeTask() const { return false; }  // slot 2
    virtual bool isPlayTask() const { return false; }  // slot 3
    virtual void start(gf::GfEvtBgm*) = 0;  // slot 4
    virtual bool update(gf::GfEvtBgm*, fw::UpdateInfo const&) = 0;  // slot 5: true when the task is done
    virtual void cancel(gf::GfEvtBgm*) = 0;  // slot 6
};
}  // namespace gf

#endif

#ifndef CLASSES_GF_EVTBGMTASK_H
#define CLASSES_GF_EVTBGMTASK_H

namespace gf {
// table none (its derived classes')
class EvtBgmTask {
public:
    virtual ~EvtBgmTask();  // slot 0
    virtual bool isVolumeTask() const { return false; }  // slot 2
    virtual bool isPlayTask() const { return false; }  // slot 3
};
}  // namespace gf

#endif

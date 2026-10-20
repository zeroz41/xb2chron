#ifndef CLASSES_GF_EVTBGMTASK_H
#define CLASSES_GF_EVTBGMTASK_H

namespace gf {
// table none (its derived classes')
class EvtBgmTask {
public:
    virtual ~EvtBgmTask();  // slot 0
    virtual void isVolumeTask() const;  // slot 2
    virtual void isPlayTask() const;  // slot 3
};
}  // namespace gf

#endif

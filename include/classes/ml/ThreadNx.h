#ifndef CLASSES_ML_THREADNX_H
#define CLASSES_ML_THREADNX_H

namespace ml {
// table 0x7100B78528
class ThreadNx {
public:
    virtual ~ThreadNx();  // slot 0
    virtual void isSuspended() const;  // slot 2
    virtual void isTerminated();  // slot 3
    virtual void exitThread();  // slot 4
    virtual void getHandle() const;  // slot 5
    virtual void getID() const;  // slot 6
    virtual void getCPUID() const;  // slot 7
    virtual void getName() const;  // slot 8
    virtual void setSignalEvent(bool);  // slot 9
    virtual void waitSignalEvent();  // slot 10
    virtual void isWaitingEvent() const;  // slot 11
};
}  // namespace ml

#endif

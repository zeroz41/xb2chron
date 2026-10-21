#ifndef CLASSES_ML_THREAD_H
#define CLASSES_ML_THREAD_H

namespace ml {
// table 0x7100B784B8
class Thread {
public:
    virtual ~Thread();  // slot 0
    virtual bool isSuspended() const = 0;  // slot 2
    virtual bool isTerminated() = 0;  // slot 3
    virtual void exitThread() = 0;  // slot 4
    virtual void getHandle() const = 0;  // slot 5
    virtual void getID() const = 0;  // slot 6
    virtual void getCPUID() const = 0;  // slot 7
    virtual void getName() const = 0;  // slot 8
    virtual void setSignalEvent(bool) = 0;  // slot 9
    virtual void waitSignalEvent() = 0;  // slot 10
    virtual void isWaitingEvent() const = 0;  // slot 11
};
}  // namespace ml

#endif

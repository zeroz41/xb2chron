#ifndef CLASSES_MM_THREADING_THREADNX_H
#define CLASSES_MM_THREADING_THREADNX_H

#include "classes/mm/threading/Thread.h"

namespace mm { namespace threading {
// table 0x7100B82570
class ThreadNx : public ::mm::threading::Thread {
public:
    virtual ~ThreadNx();  // slot 0
    virtual bool isSuspended() const;  // slot 2
    virtual bool isTerminated();  // slot 3
    virtual void exitThread();  // slot 4
    virtual void getHandle() const;  // slot 5
    virtual void getID() const;  // slot 6
    virtual void getCPUID() const;  // slot 7
    virtual void getName() const;  // slot 8
    virtual void setSignalEvent(bool);  // slot 9
    virtual void waitSignalEvent();  // slot 10
    virtual void isWaitingEvent() const;  // slot 11
};
}}  // namespace mm::threading

#endif

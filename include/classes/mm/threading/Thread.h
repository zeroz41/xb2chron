#ifndef CLASSES_MM_THREADING_THREAD_H
#define CLASSES_MM_THREADING_THREAD_H

#include "classes/mm/threading/ReferenceObject.h"

namespace mm { namespace threading {
// table 0x7100B824E0
class Thread : public ::mm::threading::ReferenceObject {
public:
    virtual ~Thread();  // slot 0
    virtual void isSuspended() const = 0;  // slot 2
    virtual void isTerminated() = 0;  // slot 3
    virtual void exitThread() = 0;  // slot 4
    virtual void getHandle() const = 0;  // slot 5
    virtual void getID() const = 0;  // slot 6
    virtual void getCPUID() const = 0;  // slot 7
    virtual void getName() const = 0;  // slot 8
    virtual void setSignalEvent(bool) = 0;  // slot 9
    virtual void waitSignalEvent() = 0;  // slot 10
    virtual void isWaitingEvent() const = 0;  // slot 11
};
}}  // namespace mm::threading

#endif

#ifndef CLASSES_MM_THREADING_EVENTWAIT_H
#define CLASSES_MM_THREADING_EVENTWAIT_H

#include "mm/threading/CriticalSection.h"
#include "nn/os.h"

namespace mm { namespace threading {
// table 0x7100B75998
class EventWait {
public:
    EventWait(bool manualClear, bool signaled);
    virtual ~EventWait();  // slot 0
    void finalize();
    void setSignal(bool signal);
    bool waitSignal(unsigned int milliseconds);
    bool isSignal() const;

    nn::os::EventType m_event;         // 0x08
    CriticalSection m_section;         // 0x30 (setSignal(false) and the constructor hold it)
    bool m_initialized;                // 0x58 (set by the constructor, cleared by finalize; name inferred)
};
}}  // namespace mm::threading

#endif

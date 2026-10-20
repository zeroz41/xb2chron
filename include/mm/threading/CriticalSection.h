#ifndef MM_THREADING_CRITICALSECTION_H
#define MM_THREADING_CRITICALSECTION_H

#include "nn/os.h"

namespace mm { namespace threading {

// a recursive mutex
class CriticalSection {
public:
    CriticalSection();
    ~CriticalSection();
    mutable nn::os::MutexType m_mutex;
    bool m_enabled;  // set by the constructor; CS locks and unlocks only while it is
};

// locks a CriticalSection for its lifetime
class CS {
public:
    CS(const CriticalSection& section);
    ~CS();
    const CriticalSection* m_section;
};

}}  // namespace mm::threading

#endif

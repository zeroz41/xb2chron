#ifndef ML_CRITICALSECTION_H
#define ML_CRITICALSECTION_H

#include "nn/os.h"

namespace ml {

// monolib's recursive mutex (its constructor and destructor are out of line; the lock and unlock are inline:
// WorkRootState's functions test the flag and call nn::os::LockMutex themselves)
class CriticalSection {
public:
    CriticalSection();
    ~CriticalSection();
    void setCostIgnore(bool ignore);  // empty in the release build
    bool isLocked() const;
    void lock() const {
        if (m_enabled) {
            nn::os::LockMutex(&m_mutex);
        }
    }
    void unlock() const {
        if (m_enabled) {
            nn::os::UnlockMutex(&m_mutex);
        }
    }
    mutable nn::os::MutexType m_mutex;
    bool m_enabled;  // 0x20 (the name is not the original's)
};

// locks a CriticalSection for its lifetime (inline everywhere: no symbol)
class CS {
public:
    CS(const CriticalSection& section) : m_section(&section) { m_section->lock(); }
    ~CS() { m_section->unlock(); }
    const CriticalSection* m_section;
};

// the non-recursive one (its constructor and destructor are out of line, in Scn.cpp's range)
class CriticalSectionNC {
public:
    CriticalSectionNC();
    ~CriticalSectionNC();
    void setCostIgnore(bool ignore);  // empty in the release build
    void lock() const {
        if (m_enabled) {
            nn::os::LockMutex(&m_mutex);
        }
    }
    void unlock() const {
        if (m_enabled) {
            nn::os::UnlockMutex(&m_mutex);
        }
    }
    mutable nn::os::MutexType m_mutex;
    bool m_enabled;  // 0x20, set by the constructor as CriticalSection's (the name is not the original's)
};

// locks a CriticalSectionNC for its lifetime (out of line)
class CSNC {
public:
    CSNC(const CriticalSectionNC& section);
    ~CSNC();
    const CriticalSectionNC* m_section;
};

}  // namespace ml

#endif

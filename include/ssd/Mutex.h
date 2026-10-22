#ifndef SSD_MUTEX_H
#define SSD_MUTEX_H

#include "nn/os.h"

namespace ssd {

// the sound library's lock: an nn::os mutex, whether it has been initialized (1.0.0's InitDebug sets it after
// nn::os::InitializeMutex, QuitDebug finalizes only while it is set) and how deep it is locked
// (SystemCore::LockAudio counts up the one it holds after locking)
class Mutex {
public:
    Mutex() : m_initialized(false), m_lockCount(0) {}
    ~Mutex() {
        m_initialized = false;
        m_lockCount = 0;
    }

    // the names of these four are not the original's (1.0.0 and 3.0.1 keep no copy): MemoryManager::Init
    // initializes its lock so (a recursive mutex), Quit finalizes it only while it is initialized
    void Initialize() {
        nn::os::InitializeMutex(&m_mutex, true, 0);
        m_initialized = true;
        m_lockCount = 0;
    }
    void Finalize() {
        if (m_initialized) {
            m_initialized = false;
            m_lockCount = 0;
            nn::os::FinalizeMutex(&m_mutex);
        }
    }
    // locks and counts up (1.0.0's SystemCore::LockAudio), counts down and unlocks, then asks whether the
    // thread still holds it and ignores the answer (1.0.0's SystemCore::UnlockAudio, MemoryManager::FreeBlock)
    void Lock() {
        nn::os::LockMutex(&m_mutex);
        ++m_lockCount;
    }
    void Unlock() {
        --m_lockCount;
        nn::os::UnlockMutex(&m_mutex);
        nn::os::IsMutexLockedByCurrentThread(&m_mutex);
    }

    nn::os::MutexType m_mutex;
    bool m_initialized;
    unsigned char m_lockCount;
};

// holds a Mutex locked for its scope (the name is not the original's)
class ScopedLock {
public:
    ScopedLock(Mutex& mutex) : m_mutex(mutex) {
        m_mutex.Lock();
    }
    ~ScopedLock() {
        m_mutex.Unlock();
    }

    Mutex& m_mutex;
};

extern Mutex OutStreamLock;

}  // namespace ssd

#endif

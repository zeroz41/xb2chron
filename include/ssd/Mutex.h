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

    nn::os::MutexType m_mutex;
    bool m_initialized;
    unsigned char m_lockCount;
};

extern Mutex OutStreamLock;

}  // namespace ssd

#endif

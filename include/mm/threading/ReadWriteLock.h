#ifndef MM_THREADING_READWRITELOCK_H
#define MM_THREADING_READWRITELOCK_H

#include "nn/os.h"

namespace mm { namespace threading {

class ReadWriteLock {
public:
    ReadWriteLock();
    ~ReadWriteLock();
    mutable nn::os::ReaderWriterLockType m_lock;
};

// holds a ReadWriteLock's read lock for its lifetime
class ReadLockGuard {
public:
    ReadLockGuard(const ReadWriteLock& lock);
    ~ReadLockGuard();
    const ReadWriteLock* m_lock;
};

// holds a ReadWriteLock's write lock for its lifetime
class WriteLockGuard {
public:
    WriteLockGuard(const ReadWriteLock& lock);
    ~WriteLockGuard();
    const ReadWriteLock* m_lock;
};

}}  // namespace mm::threading

#endif

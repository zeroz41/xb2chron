#ifndef MM_THREADING_SPINLOCK_H
#define MM_THREADING_SPINLOCK_H

namespace mm { namespace threading {

// a lock taken by spinning on a word: 0 while free
class SpinLock {
public:
    SpinLock();
    // spins until the lock is taken (the argument's meaning is not known; anm::ThreadPool passes 0)
    void lock(float wait);
    void unlock() { __atomic_store_n(&m_lock, 0, __ATOMIC_RELEASE); }

    int m_lock;
};

}}  // namespace mm::threading

#endif

#include "mm/threading/ReadWriteLock.h"

namespace mm { namespace threading {

ReadLockGuard::ReadLockGuard(const ReadWriteLock& lock) : m_lock(&lock) {
    nn::os::AcquireReadLock(&lock.m_lock);
}

ReadLockGuard::~ReadLockGuard() {
    nn::os::ReleaseReadLock(&m_lock->m_lock);
}

WriteLockGuard::WriteLockGuard(const ReadWriteLock& lock) : m_lock(&lock) {
    nn::os::AcquireWriteLock(&lock.m_lock);
}

WriteLockGuard::~WriteLockGuard() {
    nn::os::ReleaseWriteLock(&m_lock->m_lock);
}

}}  // namespace mm::threading

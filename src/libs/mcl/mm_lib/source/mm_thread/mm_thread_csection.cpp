#include "mm/threading/CriticalSection.h"
#include "mm/threading/ReadWriteLock.h"

namespace mm { namespace threading {

ReadWriteLock::ReadWriteLock() {
    nn::os::InitializeReaderWriterLock(&m_lock);
}

ReadWriteLock::~ReadWriteLock() {
    nn::os::FinalizeReaderWriterLock(&m_lock);
}

CriticalSection::CriticalSection() {
    m_enabled = true;
    nn::os::InitializeMutex(&m_mutex, true, 31);
}

CriticalSection::~CriticalSection() {
    nn::os::FinalizeMutex(&m_mutex);
}

CS::CS(const CriticalSection& section) {
    if (section.m_enabled) {
        nn::os::LockMutex(&section.m_mutex);
    }
    m_section = &section;
}

CS::~CS() {
    if (m_section->m_enabled) {
        nn::os::UnlockMutex(&m_section->m_mutex);
    }
}

}}  // namespace mm::threading

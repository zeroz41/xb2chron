#ifndef NN_OS_H
#define NN_OS_H

// NintendoSDK 3.5.0's nn::os, as far as the module imports it. Sizes are the ones the game's own layouts show.
namespace nn { namespace os {

struct MutexType {
    unsigned char pad_0[0x20];  // mm::threading::CriticalSection's flag follows it at 0x20
};
struct ReaderWriterLockType {
    unsigned char pad_0[0x30];  // ml::DevFileNxTh's entries end 0x30 after the one they hold
};

void InitializeMutex(MutexType* mutex, bool recursive, int lockLevel);
void FinalizeMutex(MutexType* mutex);
void LockMutex(MutexType* mutex);
void UnlockMutex(MutexType* mutex);

void InitializeReaderWriterLock(ReaderWriterLockType* lock);
void FinalizeReaderWriterLock(ReaderWriterLockType* lock);
void AcquireReadLock(ReaderWriterLockType* lock);
void ReleaseReadLock(ReaderWriterLockType* lock);
void AcquireWriteLock(ReaderWriterLockType* lock);
void ReleaseWriteLock(ReaderWriterLockType* lock);

}}  // namespace nn::os

#endif

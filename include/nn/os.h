#ifndef NN_OS_H
#define NN_OS_H

#include "nn/result.h"

// NintendoSDK 3.5.0's nn::os, as far as the module imports it. Sizes are the ones the game's own layouts show.
namespace nn { namespace os {

struct MutexType {
    unsigned char pad_0[0x20];  // mm::threading::CriticalSection's flag follows it at 0x20
};
struct ReaderWriterLockType {
    unsigned char pad_0[0x30];  // ml::DevFileNxTh's entries end 0x30 after the one they hold
};
struct alignas(8) ThreadType {
    unsigned char pad_0[0x1C0];  // mm::threading::ThreadNx holds one at 0x30, its EventWait follows at 0x1F0
};

typedef void (*ThreadFunction)(void* argument);

const int HighestThreadPriority = 0;
const int DefaultThreadPriority = 16;
const int LowestThreadPriority = 31;

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

Result CreateThread(ThreadType* thread, ThreadFunction function, void* argument, void* stack, unsigned long stackSize,
                    int priority, int idealCore);
Result CreateThread(ThreadType* thread, ThreadFunction function, void* argument, void* stack, unsigned long stackSize,
                    int priority);
void DestroyThread(ThreadType* thread);
void StartThread(ThreadType* thread);
void SetThreadName(ThreadType* thread, const char* name);
const char* GetThreadNamePointer(const ThreadType* thread);

}}  // namespace nn::os

#endif

#ifndef NN_OS_H
#define NN_OS_H

#include "nn/result.h"

// NintendoSDK 3.5.0's nn::os, as far as the module imports it. Sizes are the ones the game's own layouts show.
namespace nn {

// a length of time in nanoseconds, passed by value in one register (nn::os::SleepThread)
class TimeSpan {
public:
    static TimeSpan FromMilliSeconds(long milliSeconds) {
        TimeSpan span;
        span.m_nanoSeconds = milliSeconds * 1000000;
        return span;
    }

    static TimeSpan FromSeconds(long seconds) {
        TimeSpan span;
        span.m_nanoSeconds = seconds * 1000000000;
        return span;
    }

    static TimeSpan FromMicroSeconds(long microSeconds) {
        TimeSpan span;
        span.m_nanoSeconds = microSeconds * 1000;
        return span;
    }
    long GetNanoSeconds() const {
        return m_nanoSeconds;
    }

private:
    long m_nanoSeconds;
};

}  // namespace nn

namespace nn { namespace os {

// 8-aligned (the SDK's holds the owner thread's pointer): ssd::Mutex, the type and two flags, is 0x28 bytes
// (OutStreamLock's .bss, MemoryManager's flag at 0x30 after its lock at 0x8)
struct alignas(8) MutexType {
    unsigned char pad_0[0x20];  // mm::threading::CriticalSection's flag follows it at 0x20
};
struct ReaderWriterLockType {
    unsigned char pad_0[0x30];  // ml::DevFileNxTh's entries end 0x30 after the one they hold
};
struct alignas(8) ThreadType {
    unsigned char pad_0[0x1C0];  // mm::threading::ThreadNx holds one at 0x30, its EventWait follows at 0x1F0
};

typedef void (*ThreadFunction)(void* argument);

// the system tick count, returned by value in one register
class Tick {
public:
    Tick() {}
    explicit Tick(long value) : m_value(value) {}
    long GetInt64Value() const {
        return m_value;
    }

private:
    long m_value;
};

Tick GetSystemTick();
// ticks per second
long GetSystemTickFrequency();
TimeSpan ConvertToTimeSpan(Tick tick);
Tick ConvertToTick(TimeSpan span);

// 0x28 bytes: ssd::Thread holds one at 0x20, its ThreadType follows at 0x48
struct alignas(8) EventType {
    unsigned char pad_0[0x28];
};
enum EventClearMode {
    EventClearMode_ManualClear,
    EventClearMode_AutoClear,
};
// writes the CPU cache lines of the range back to memory (the SDK's)
void FlushDataCache(const void* address, unsigned long size);

void InitializeEvent(EventType* event, bool initiallySignaled, EventClearMode clearMode);
void FinalizeEvent(EventType* event);
void SignalEvent(EventType* event);
void ClearEvent(EventType* event);
void WaitEvent(EventType* event);
bool TimedWaitEvent(EventType* event, TimeSpan timeout);

// the SDK's timer event (ml::pad_detail::g_TimerEvent drives the vibration node thread; its size is not known
// here: the .bss leaves it up to 0xAC0 bytes before the next global's 0x1000-aligned start; 0x60 is the SDK's)
struct alignas(8) TimerEventType {
    unsigned char pad_0[0x60];
};
void InitializeTimerEvent(TimerEventType* event, EventClearMode clearMode);
void FinalizeTimerEvent(TimerEventType* event);
void StartPeriodicTimerEvent(TimerEventType* event, TimeSpan first, TimeSpan interval);
void StopTimerEvent(TimerEventType* event);
void WaitTimerEvent(TimerEventType* event);

// 0x30 bytes; its state byte at 0x28 (0: not initialized) is what SystemEvent's destructor tests
// (ssd::SystemCorePlatform's destructor reads it at 0x160 of the event at 0x138)
struct alignas(8) SystemEventType {
    unsigned char pad_0[0x28];
    unsigned char _state;
    unsigned char pad_29[0x7];
};
void DestroySystemEvent(SystemEventType* event);
void WaitSystemEvent(SystemEventType* event);

class SystemEvent {
public:
    SystemEvent() {
        m_SystemEvent._state = 0;
    }
    ~SystemEvent() {
        if (m_SystemEvent._state == 0) {
            return;
        }
        DestroySystemEvent(&m_SystemEvent);
    }
    SystemEventType* GetBase() {
        return &m_SystemEvent;
    }

private:
    SystemEventType m_SystemEvent;
};

const int HighestThreadPriority = 0;
const int DefaultThreadPriority = 16;
const int LowestThreadPriority = 31;

void InitializeMutex(MutexType* mutex, bool recursive, int lockLevel);
void FinalizeMutex(MutexType* mutex);
void LockMutex(MutexType* mutex);
void UnlockMutex(MutexType* mutex);
bool IsMutexLockedByCurrentThread(const MutexType* mutex);

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
void WaitThread(ThreadType* thread);
void SetThreadCoreMask(ThreadType* thread, int idealCore, unsigned long affinityMask);
void StartThread(ThreadType* thread);
void SetThreadName(ThreadType* thread, const char* name);
const char* GetThreadNamePointer(const ThreadType* thread);
void SleepThread(TimeSpan time);
unsigned long GetThreadAvailableCoreMask();
ThreadType* GetCurrentThread();
int GetCurrentCoreNumber();

// 8-aligned (it holds pointers); 0x58 bytes: ml::MicroThreadNx keeps each fiber's stack right after one
struct alignas(8) FiberType {
    unsigned char pad_0[0x58];
};
typedef FiberType* (*FiberFunction)(void* argument);

void InitializeFiber(FiberType* fiber, FiberFunction function, void* argument, void* stack, unsigned long stackSize,
                     int option);
void FinalizeFiber(FiberType* fiber);
void SwitchToFiber(FiberType* fiber);
FiberType* GetCurrentFiber();

}}  // namespace nn::os

#endif

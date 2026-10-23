#ifndef SSD_THREAD_H
#define SSD_THREAD_H

#include "nn/os.h"
#include "ssd/Debug.h"
#include "ssd/MemoryBlock.h"

namespace ssd {
// a library thread (its code cites "D:/ssd/ssd51/ssd/sources/system/thread.nx.cpp"): its stack from
// SoundMemory::allocator_, an event it sleeps on, and the function it runs. The field names are not the
// original's.
class Thread {
public:
    // what CreateThreadImpl starts the thread with (the field names are not the original's)
    struct Param {
        Param();

        void* userData;          // the function's second argument
        int priority;            // 0 here; CreateThreadImpl creates the thread at priority 16
        int idealCore;           // -1: SetThreadCoreMask's ideal core
        unsigned long coreMask;  // GetThreadAvailableCoreMask(): SetThreadCoreMask's mask
        unsigned long pad_18;
        unsigned long stackSize;  // 0 asks for 0x8000 bytes
        float interval;           // kept as a double at 0x18
    };

    typedef void (*Function)(void* argument, void* userData);

    Thread();
    ~Thread();

    Result CreateThreadImpl(void* argument, Function function, const Param& param);
    static void ThreadEntryProc(void* thread);
    Result CloseThread();
    Result Sleep(float time);

    bool created_;   // set with running_ once the thread starts, cleared by CloseThread
    bool running_;   // set while ThreadEntryProc runs the function
    bool closing_;   // set by CloseThread before it waits for the thread
    bool sleeping_;  // set by Sleep
    MemoryBlock stack_;
    double interval_;
    nn::os::EventType event_;
    nn::os::ThreadType thread_;
    void* argument_;
    Function function_;
    void* userData_;
};
}  // namespace ssd

#endif

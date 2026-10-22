#ifndef CLASSES_ANM_THREADPOOL_H
#define CLASSES_ANM_THREADPOOL_H

#include "classes/mm/threading/EventWait.h"
#include "mm/threading/SpinLock.h"

namespace anm { class JobQueue; }
namespace mm { namespace mtl { class IAllocator; }}
namespace mm { namespace threading { class Thread; }}

namespace anm {
// how a ThreadPool is set up (the names are not the original's)
struct TreadPoolInfo {
    unsigned int m_threadMask;  // bit n starts worker thread n (WorkerThread0..2 on cores 1..3)
    int m_priority;             // the worker threads'
    unsigned int m_maxJobs;     // the most jobs a worker takes from the queue at a time
};

// table 0x7100B81018; up to three worker threads running a JobQueue's jobs
class ThreadPool {
public:
    // what a worker thread is started with
    struct ThreadArgument {
        ThreadPool* m_pPool;
        unsigned int m_index;
    };

    enum State {
        STATE_SETUP = 0,   // initialize has not finished
        STATE_RUN = 1,     // the workers run jobs
        STATE_FINISH = 2,  // finalize: the workers return
    };

    ThreadPool(const TreadPoolInfo& info, mm::mtl::IAllocator& allocator);
    virtual ~ThreadPool();  // slot 0
    // hands the queue to the workers and starts them
    virtual void processAllJob(anm::JobQueue& queue);  // slot 2
    // waits for the workers to finish the queue
    virtual void waitForCompletion();  // slot 3
    virtual void initialize(const TreadPoolInfo& info, mm::mtl::IAllocator& allocator);  // slot 4
    virtual void finalize();  // slot 5
    static unsigned int threadFunc(void* argument);

    mm::threading::Thread* m_threads[3];
    mm::threading::EventWait m_startEvents[3];  // per worker: set to start it on the queue (the names of the
                                                // fields are not the original's)
    mm::threading::SpinLock m_lock;  // held while a worker takes jobs from the queue
    State m_state;
    mm::threading::EventWait m_doneEvents[3];  // per worker: set when it is idle
    TreadPoolInfo m_info;
    JobQueue* m_pJobQueue;  // anm_thread_pool.cpp asserts `m_pJobQueue == nullptr` as a queue is handed over
};
}  // namespace anm

#endif

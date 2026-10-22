#include "classes/anm/ThreadPool.h"
#include "anm/JobQueue.h"
#include "classes/mm/threading/EventWait.h"
#include "classes/mm/threading/Thread.h"
#include "mm/threading/SpinLock.h"
#include "mm/MMStdBase.h"
#include "nn/os.h"

namespace anm {

ThreadPool::ThreadPool(const TreadPoolInfo& info, mm::mtl::IAllocator& allocator)
    : m_startEvents{{false, true}, {false, true}, {false, true}}, m_state(STATE_SETUP),
      m_doneEvents{{false, true}, {false, true}, {false, true}}, m_info(info), m_pJobQueue(nullptr) {
    for (int i = 0; i < 3; i++) {
        m_threads[i] = nullptr;
    }
    for (int i = 0; i < 3; i++) {
        m_doneEvents[i].setSignal(false);
    }
    for (int i = 0; i < 3; i++) {
        m_startEvents[i].setSignal(false);
    }
    initialize(info, allocator);
}

ThreadPool::~ThreadPool() {
    finalize();
}

void ThreadPool::initialize(const TreadPoolInfo& info, mm::mtl::IAllocator& allocator) {
    ThreadArgument arguments[3] = {{this, 0}, {this, 1}, {this, 2}};
    if (info.m_threadMask & 1) {
        m_threads[0] = mm::threading::Thread::create(&allocator, "WorkerThread0", threadFunc, &arguments[0], 0x40000,
                                                     mm::threading::CPUID(1), info.m_priority);
        m_threads[0]->resume();
    }
    if (info.m_threadMask & 2) {
        m_threads[1] = mm::threading::Thread::create(&allocator, "WorkerThread1", threadFunc, &arguments[1], 0x40000,
                                                     mm::threading::CPUID(2), info.m_priority);
        m_threads[1]->resume();
    }
    if (info.m_threadMask & 4) {
        m_threads[2] = mm::threading::Thread::create(&allocator, "WorkerThread2", threadFunc, &arguments[2], 0x40000,
                                                     mm::threading::CPUID(3), info.m_priority);
        m_threads[2]->resume();
    }
    for (int i = 0; i < 3; i++) {
        if (m_threads[i] != nullptr) {
            m_doneEvents[i].waitSignal(0);
        }
    }
    m_state = STATE_RUN;
}

unsigned int ThreadPool::threadFunc(void* argument) {
    ThreadArgument* threadArgument = static_cast<ThreadArgument*>(argument);
    ThreadPool* pool = threadArgument->m_pPool;
    unsigned int index = threadArgument->m_index;
    Job jobs[0x200];
    mm::threading::EventWait& doneEvent = pool->m_doneEvents[index];
    doneEvent.setSignal(true);
    while (pool->m_state == STATE_SETUP) {
        nn::os::SleepThread(nn::TimeSpan::FromMilliSeconds(1));
    }
    mm::threading::EventWait& startEvent = pool->m_startEvents[index];
    startEvent.waitSignal(0);
    while (pool->m_state != STATE_FINISH) {
        JobQueue* queue = pool->m_pJobQueue;
        if (queue != nullptr) {
            while (queue->getCount() != 0) {
                pool->m_lock.lock(0.0f);
                unsigned int count = queue->getCount() < pool->m_info.m_maxJobs ? queue->getCount()
                                                                                : pool->m_info.m_maxJobs;
                for (unsigned int i = 0; i < count; i++) {
                    if (!queue->m_jobs.empty()) {
                        jobs[i] = queue->m_jobs.front();
                        queue->m_jobs.pop();
                    }
                }
                pool->m_lock.unlock();
                for (unsigned int i = 0; i < count; i++) {
                    queue->execute(jobs[i]);
                }
            }
        }
        doneEvent.setSignal(true);
        startEvent.waitSignal(0);
    }
    return 0;
}

void ThreadPool::finalize() {
    m_state = STATE_FINISH;
    for (int i = 0; i < 3; i++) {
        m_startEvents[i].setSignal(true);
    }
    for (int i = 0; i < 3; i++) {
        if (m_threads[i] != nullptr) {
            while (!m_threads[i]->isTerminated()) {
                nn::os::SleepThread(nn::TimeSpan::FromMilliSeconds(1));
            }
            if (m_threads[i] != nullptr) {
                m_threads[i]->release();
                m_threads[i] = nullptr;
            }
        }
    }
}

void ThreadPool::processAllJob(JobQueue& queue) {
#line 199
    MM_ASSERT(m_pJobQueue == nullptr);
    m_pJobQueue = &queue;
    m_startEvents[1].setSignal(true);
    m_startEvents[2].setSignal(true);
    m_startEvents[0].setSignal(true);
}

void ThreadPool::waitForCompletion() {
    if (m_pJobQueue != nullptr) {
        for (int i = 0; i < 3; i++) {
            if (m_threads[i] != nullptr) {
                m_doneEvents[i].waitSignal(0);
            }
        }
        m_pJobQueue = nullptr;
    }
}

}  // namespace anm

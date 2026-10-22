#ifndef ANM_JOBQUEUE_H
#define ANM_JOBQUEUE_H

#include "mm/MMStdBase.h"
#include "string.h"
#include "mm/mtl/Queue.h"

// anmlib's anm_job_queue.h, as the including file's include path named it (see anm/Array.h)
#ifdef MM_LIB_FROM_LIBS
#define ANM_JOB_QUEUE_PATH "../../src\\anmlib/base/anm_job_queue.h"
#else
#define ANM_JOB_QUEUE_PATH \
    "D:/Monolithsoft/BF2/prog/application/BF2//../../libs/anmlib/src\\anmlib/base/anm_job_queue.h"
#endif

namespace anm {
// what a job starts with: its type's name, its size and the function JobQueue runs it with (m_funcIndex; anm_job_queue.h
// asserts `m_funcs[job.m_funcIndex]`). The names are not the original's.
struct Job {
    Job(const char* name, unsigned int size, unsigned int funcIndex)
        : m_name(name), m_size(size), m_funcIndex(funcIndex) {}

    const char* m_name;
    unsigned int m_size;
    unsigned int m_funcIndex;
};

// one entry of a JobQueue (0x100 bytes, named "JobEntry"): a job copied over it (JobQueue::push)
struct JobEntry : public Job {
    JobEntry() : Job("JobEntry", sizeof(JobEntry), 0) {}

    unsigned char m_data[0xF0];
};

// the jobs anm::ThreadPool's workers run, and the functions they run them with
class JobQueue {
public:
    typedef void (*JobFunc)(Job& job);

    // room for capacity jobs from the allocator, no functions (the names of the members below are not the
    // original's)
    JobQueue(mm::mtl::IAllocator* allocator, unsigned int capacity) : m_jobs(allocator) {
        m_jobs.reserve(capacity);
        memset(m_funcs, 0, sizeof(m_funcs));
    }
    // func runs the jobs whose m_funcIndex is index
    void registerFunc(unsigned int index, JobFunc func) {
#line 37 ANM_JOB_QUEUE_PATH
        MM_ASSERT(m_funcs[index] == nullptr);
        m_funcs[index] = func;
    }
    // job (a Job's derived class) copied into an entry at the end
    template <typename T>
    void push(const T& job) {
        JobEntry entry;
        memcpy(&entry, &job, job.m_size);
        m_jobs.push_back(entry);
    }
    unsigned int getCount() const { return m_jobs.size(); }
    // runs the job's function on it
    void execute(JobEntry& job) {
#line 44 ANM_JOB_QUEUE_PATH
        MM_ASSERT(m_funcs[job.m_funcIndex]);
        m_funcs[job.m_funcIndex](job);
    }

    mm::mtl::Queue<JobEntry> m_jobs;
    JobFunc m_funcs[32];  // indexed by a job's m_funcIndex
};
}  // namespace anm

#endif

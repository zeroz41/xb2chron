#ifndef ANM_JOBQUEUE_H
#define ANM_JOBQUEUE_H

#include "mm/MMStdBase.h"
#include "mm/mtl/Queue.h"

// anmlib's anm_job_queue.h, as the including file's include path named it (see anm/Array.h)
#ifdef MM_LIB_FROM_LIBS
#define ANM_JOB_QUEUE_PATH "../../src\\anmlib/base/anm_job_queue.h"
#else
#define ANM_JOB_QUEUE_PATH \
    "D:/Monolithsoft/BF2/prog/application/BF2//../../libs/anmlib/src\\anmlib/base/anm_job_queue.h"
#endif

namespace anm {
// one job of a JobQueue: 0x100 bytes, the function to run on it chosen by m_funcIndex (anm_job_queue.h asserts
// `m_funcs[job.m_funcIndex]`). The other names are not the original's.
struct Job {
    Job() : m_name("JobEntry"), m_size(sizeof(Job)), m_funcIndex(0) {}

    const char* m_name;
    unsigned int m_size;
    unsigned int m_funcIndex;
    unsigned char m_data[0xF0];
};

// the jobs anm::ThreadPool's workers run, and the functions they run them with
class JobQueue {
public:
    typedef void (*JobFunc)(Job* job);

    unsigned int getCount() const { return m_jobs.size(); }
    // runs the job's function on it
    void execute(Job& job) {
#line 44 ANM_JOB_QUEUE_PATH
        MM_ASSERT(m_funcs[job.m_funcIndex]);
        m_funcs[job.m_funcIndex](&job);
    }

    mm::mtl::Queue<Job> m_jobs;
    JobFunc m_funcs[1];  // indexed by a job's m_funcIndex (the count is not known)
};
}  // namespace anm

#endif

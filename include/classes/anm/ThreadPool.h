#ifndef CLASSES_ANM_THREADPOOL_H
#define CLASSES_ANM_THREADPOOL_H

namespace anm { class JobQueue; }
namespace anm { class TreadPoolInfo; }
namespace mm { namespace mtl { class IAllocator; }}

namespace anm {
// table 0x7100B81018
class ThreadPool {
public:
    virtual ~ThreadPool();  // slot 0
    virtual void processAllJob(anm::JobQueue&);  // slot 2
    virtual void waitForCompletion();  // slot 3
    virtual void initialize(anm::TreadPoolInfo const&, mm::mtl::IAllocator&);  // slot 4
    virtual void finalize();  // slot 5
};
}  // namespace anm

#endif

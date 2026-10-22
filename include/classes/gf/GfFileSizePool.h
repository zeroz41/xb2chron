#ifndef CLASSES_GF_GFFILESIZEPOOL_H
#define CLASSES_GF_GFFILESIZEPOOL_H

#include "classes/mm/mtl/PtrSingleton.h"
#include "classes/mm/threading/EventWait.h"
#include "mm/threading/CriticalSection.h"
#include "mm/mtl/FixedQueue.h"
#include "mm/mtl/FixedVector.h"
#include "mm/mtl/FixStr.h"

namespace gf { class GfFileSizePool; }
namespace gf { class GfSetupParam; }
namespace ml { class Thread; }

namespace gf {
// table 0x7100B45938; the sizes of files, asked for by path and read on a thread of its own (1.0.0's symbols name
// the members; the field and nested type names are not the original's)
class GfFileSizePool : public ::mm::mtl::PtrSingleton< ::gf::GfFileSizePool> {
public:
    // a file's entry: its handle (the path's hashes and the entry's index in the pool), its path, its size
    // (-2 until the thread has read it, -1 for none)
    struct FileSizeInfo {
        unsigned long m_handle;
        mm::mtl::FixStr<128>* m_name;
        int m_size;
        unsigned int m_index;
    };

    GfFileSizePool(const GfSetupParam& param);
    virtual ~GfFileSizePool();  // slot 0

    static void build(const GfSetupParam& param);
    static void destroy();
    void destroyThread();
    unsigned long requestFileSize(const char* path);
    void recalcFileSizeCache(unsigned long handle, const char* path);
    bool getFileSize(int& size, unsigned long handle) const;
    static unsigned int fnThread(void* argument);
    void update();
    void copyPoolFromRequest();
    void execFileSizeJob(unsigned int count);

    // inline here: 1.0.0 has them out of line, 3.0.1 only inlined
    void initialize(const GfSetupParam& param);
    void finalize();
    void wakeupThread();
    static unsigned long getHash(const char* path);
    static unsigned long getHashFromHandle(unsigned long handle);
    static unsigned short getPoolIndex(unsigned long handle);
    static unsigned long getHandleFromFileName(unsigned int index, const char* path);

    bool m_initialized;  // 0x8 initialize sets it, finalize clears it
    bool m_exitThread;   // 0x9 finalize sets it: fnThread returns
    unsigned char pad_A[6];
    mm::mtl::FixedVector<FileSizeInfo, 0x1000> m_pool;     // 0x10 every file asked for
    mm::mtl::FixedQueue<FileSizeInfo, 0x200> m_jobQueue;    // 0x18018 the entries the thread reads, under m_cs
    mm::mtl::FixedQueue<FileSizeInfo, 0x200> m_requestQueue;  // 0x1B028 new requests, moved to m_jobQueue by update
    unsigned int m_nextIndex;  // 0x1E038 where a full pool looks for an entry to reuse
    ml::Thread* m_thread;      // 0x1E040
    mm::threading::EventWait m_event;  // 0x1E048 set to wake the thread
    mm::threading::CriticalSection m_cs;  // 0x1E0A8
    unsigned char pad_1E0C9[7];
    bool m_busy;     // 0x1E0D0 set while the thread works
    float m_jobTime;  // 0x1E0D4 the seconds the thread has spent on jobs
};
}  // namespace gf

#endif

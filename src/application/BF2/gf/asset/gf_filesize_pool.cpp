#include "classes/ml/Thread.h"
#include "classes/ml/DevFileTh.h"
#include "classes/gf/GfFileSizePool.h"
#include "gf/GfUtil.h"
#include "ml/TimeCount.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfInfo.h"
#include "mm/mtl/Hash.h"

namespace gf {

inline void GfFileSizePool::initialize(const GfSetupParam& param) {
    m_thread = ml::Thread::create("FileSizeJob", false, fnThread, this, 0x10000, ml::CPUID(2), 0);
    if (m_thread != nullptr) {
        m_thread->resume();
    }
    m_initialized = true;
}

inline void GfFileSizePool::finalize() {
    m_exitThread = true;
    destroyThread();
    m_initialized = false;
}

inline void GfFileSizePool::wakeupThread() {
    m_event.setSignal(true);
}

inline unsigned long GfFileSizePool::getHash(const char* path) {
    if (*path == '\\' || *path == '/') {
        path++;
    }
    return static_cast<unsigned long>(mm::mtl::hashStrCrc(path)) << 32 |
           (mm::mtl::hashStrCrc(util::getFilePtrFromPath(path)) & 0xFFFF0000);
}

inline unsigned long GfFileSizePool::getHashFromHandle(unsigned long handle) {
    return handle & 0xFFFFFFFFFFFF0000;
}

inline unsigned short GfFileSizePool::getPoolIndex(unsigned long handle) {
    return handle;
}

inline unsigned long GfFileSizePool::getHandleFromFileName(unsigned int index, const char* path) {
    unsigned long hash = getHash(path);
    util::getFilePtrFromPath(path);
    return index | hash;
}

GfFileSizePool::GfFileSizePool(const GfSetupParam& param)
    : m_initialized(false), m_exitThread(false), m_nextIndex(0), m_thread(nullptr), m_event(false, true),
      m_busy(false), m_jobTime(0.0f) {
    initialize(param);
}

GfFileSizePool::~GfFileSizePool() {}

void GfFileSizePool::build(const GfSetupParam& param) {
#line 62
    new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) GfFileSizePool(param);
}

void GfFileSizePool::destroy() {
    GfFileSizePool* pool = get();
    pool->finalize();
    delete pool;
}

void GfFileSizePool::destroyThread() {
    if (m_thread != nullptr) {
        while (!m_thread->isTerminated()) {
            m_event.setSignal(true);
            GfSleep(1);
        }
        if (m_thread != nullptr) {
            m_thread->release();
            m_thread = nullptr;
        }
        for (FileSizeInfo *it = m_pool.begin(), *end = m_pool.end(); it != end; ++it) {
            if (it->m_name != nullptr) {
                delete it->m_name;
                it->m_name = nullptr;
            }
        }
        m_pool.clear();
        m_requestQueue.clear();
        m_jobQueue.clear();
    }
}

// requestFileSize (0x71001C508C) is not here yet: its candidate (wip/gf_filesize_pool_full.cpp) differs only in
// where the full pool's search wraps its index (the original wraps it on both edges after the name test).

void GfFileSizePool::recalcFileSizeCache(unsigned long handle, const char* path) {
    FileSizeInfo& info = m_pool[getPoolIndex(handle)];
    if (info.m_name != nullptr) {
        delete info.m_name;
        info.m_name = nullptr;
    }
    info.m_handle = handle;
#line 224
    info.m_name = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) mm::mtl::FixStr<128>;
    *info.m_name = path;
    info.m_size = -2;
    m_requestQueue.push_back(info);
}

bool GfFileSizePool::getFileSize(int& size, unsigned long handle) const {
    const FileSizeInfo& info = m_pool[getPoolIndex(handle)];
    if (info.m_size != -2) {
        size = info.m_size;
        return true;
    }
    return false;
}

unsigned int GfFileSizePool::fnThread(void* argument) {
    GfFileSizePool* pool = get();
    pool->m_busy = true;
    while (!pool->m_exitThread) {
        pool->execFileSizeJob(100);
        pool->m_busy = false;
        pool->m_event.waitSignal(0);
        pool->m_busy = true;
        pool = get();
    }
    return 0;
}

void GfFileSizePool::update() {
    if (!m_busy) {
        copyPoolFromRequest();
        wakeupThread();
    }
}

// copyPoolFromRequest (0x71001C566C) is not here yet: its candidate (wip/gf_filesize_pool_full.cpp) differs only
// in registers: the original addresses the job queue's slots from two separate bases (the iterator's and erase's).

void GfFileSizePool::execFileSizeJob(unsigned int count) {
    mm::threading::CS lock(m_cs);
    ml::TimeCount timer;
    timer.start();
    unsigned int done = 0;
    for (mm::mtl::FixedQueue<FileSizeInfo, 0x200>::iterator it = m_jobQueue.begin(), end = m_jobQueue.end();
         it != end; ++it) {
        FileSizeInfo& job = *it;
        if (job.m_size == -2) {
            int size = ml::DevFileTh::getFileSize(job.m_name->m_str, nullptr);
            if (size < 0) {
                size = -1;
            }
            job.m_size = size;
            if (++done >= count) {
                break;
            }
        }
    }
    m_jobTime += timer.getSecLap();
}

}  // namespace gf

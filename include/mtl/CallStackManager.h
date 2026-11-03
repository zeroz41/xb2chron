#ifndef MTL_CALLSTACKMANAGER_H
#define MTL_CALLSTACKMANAGER_H

#include "ml/CriticalSection.h"
#include "mm/mtl/IntrusiveList.h"
#include "mtl/CallStackInfo.h"
#include "classes/mm/mtl/HeapAllocator.h"

namespace mtl {

// the call stack records of one allocator (DlAllocator holds one at 0x48; 0x40 bytes). 1.0.0 names the class,
// regist, remove and m_allocator; the instance member names are not the original's
class CallStackManager {
public:
    // the record for the caller's stack (what it returns is inferred from DlAllocator's footer)
    CallStackInfo* regist(unsigned int, const char*, unsigned int);
    void remove(CallStackInfo* info);

    // the counters MemManager::initialize clears
    static unsigned int m_maxAllocate;
    static unsigned int m_nowAllocate;
    static unsigned int m_maxAllocateSize;
    static unsigned int m_nowAllocateSize;
    static int m_maxRefCount;  // regist compares the records' counts with it signed
    static mm::mtl::HeapAllocator m_allocator;  // where the records live (1.0.0: 0x19F8 bytes .bss)
    // m_allocator's memory: MAX_ALLOCATE_SIZE records of 0xA8 bytes from malloc (MemManager::initialize; terminate
    // frees it)
    static void* m_buffer;
    static unsigned long m_bufferSize;
    static unsigned int MAX_ALLOCATE_SIZE;  // 0x4000

    mm::mtl::IntrusiveList<CallStackInfo> m_list;
    ml::CriticalSection m_cs;  // +0x18
};

}  // namespace mtl

#endif

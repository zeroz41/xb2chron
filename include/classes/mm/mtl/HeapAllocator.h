#ifndef CLASSES_MM_MTL_HEAPALLOCATOR_H
#define CLASSES_MM_MTL_HEAPALLOCATOR_H

#include "classes/mm/mtl/IAllocator.h"
#include "mm/mtl/FixStr.h"

namespace mm { namespace mtl {
// table 0x7100B82498; an IAllocator over one TLSF heap (HeapAllocUtil) in a buffer it is given
class HeapAllocator : public ::mm::mtl::IAllocator {
public:
    HeapAllocator();
    virtual ~HeapAllocator();  // slot 0
    void destroy(bool removePool);
    void create(void* buffer, unsigned long bufferSize, const char* name);
    virtual void* allocate(unsigned long size, unsigned long alignment);  // slot 2
    virtual void deallocate(void* memory);  // slot 3
    virtual const char* getName() const;  // slot 4
    virtual unsigned int getNameHash() const {  // slot 5
        return m_nameHash;
    }
    virtual void* allocate(unsigned long size, unsigned long alignment, const char* file, int line);  // slot 6

    void* m_buffer;  // the heap's pool over the buffer create() was given
    unsigned long m_bufferSize;
    unsigned long m_allocated;  // allocations not yet given back
    void* m_control;  // the heap HeapAllocUtil built in m_controlBuffer
    FixStr<64> m_name;
    unsigned int m_nameHash;
    unsigned char m_controlBuffer[0x1988];  // HeapAllocUtil's control block (control_construct fills 0x1988 bytes)
};
}}  // namespace mm::mtl

#endif

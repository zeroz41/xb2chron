#ifndef CLASSES_PTLIB_HEAPALLOCATOR_H
#define CLASSES_PTLIB_HEAPALLOCATOR_H

#include "classes/mm/mtl/IAllocator.h"
#include "mm/mtl/FixStr.h"

namespace ptlib {
// table 0x7100B807F0; the effect library's copy of mm_lib's HeapAllocator: one TLSF heap (HeapAllocUtil) in a
// buffer it is given, counting its blocks
class HeapAllocator : public ::mm::mtl::IAllocator {
public:
    // as destroy leaves it (1.0.0 has it out of line; 3.0.1 only inlines it into HeapAllocaterManager::init)
    HeapAllocator() {
        m_buffer = nullptr;
        m_control = nullptr;
        m_allocated = 0;
        m_bufferSize = 0;
        m_nameHash = 0;
        m_name.clear();
    }
    virtual ~HeapAllocator();  // slot 0
    void create(void* buffer, unsigned long bufferSize, const char* name);
    virtual void* allocate(unsigned long size, unsigned long alignment);  // slot 2
    virtual void deallocate(void* memory);  // slot 3
    virtual const char* getName() const;  // slot 4
    virtual unsigned int getNameHash() const;  // slot 5
    virtual void* allocate(unsigned long size, unsigned long alignment, const char* file, int line);  // slot 6
    virtual unsigned long getBlockNum();  // slot 7
    // whether memory is in the heap's buffer, and the bytes of its block (1.0.0 has them out of line; 3.0.1 has no
    // copy, only getBlockSize's assertion string)
    bool insideArea(const void* memory) const;
    bool hasMemory(const void* memory) const;
    unsigned long getBlockSize(const void* memory) const;

    void* m_buffer;  // the heap's pool over the buffer create() was given
    unsigned long m_bufferSize;
    unsigned long m_allocated;  // allocations not yet given back
    void* m_control;  // the heap HeapAllocUtil built in m_controlBuffer
    ::mm::mtl::FixStr<64> m_name;
    unsigned int m_nameHash;
    unsigned char m_controlBuffer[0x1988];  // HeapAllocUtil's control block (as mm::mtl::HeapAllocator's)
};

// the effect library's heap: one HeapAllocator with its memory after it, from ParticleManager::sysAlloc
class HeapAllocaterManager {
public:
    enum {
        HEAP_SIZE = 0x80000,  // the heap's bytes
        HEAP_OFFSET = 0x1A00,  // where they start in the block (after the allocator)
    };

    static void init();
    static void term();

    static HeapAllocator* s_pIns;
};
}  // namespace ptlib

#endif

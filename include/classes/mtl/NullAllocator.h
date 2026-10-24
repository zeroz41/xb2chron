#ifndef CLASSES_MTL_NULLALLOCATOR_H
#define CLASSES_MTL_NULLALLOCATOR_H

#include "classes/mtl/IMemAllocator.h"

namespace mtl {

// table 0x7100B79420: an allocator that hands out nothing (MemManager::createAllocator's type 0; 0x30 bytes), only
// a name. Every member is inline (emitted after the unit's functions, its destructor slot the base's)
class NullAllocator : public IMemAllocator {
public:
    NullAllocator() {}
    virtual ~NullAllocator() {}  // slot 0
    virtual void create(void* p, unsigned long size, const char* pszName) { m_name = pszName; }  // slot 2
    virtual void destroy() {}  // slot 3
    virtual AllocatorType getType() const { return static_cast<AllocatorType>(0); }  // slot 4
    virtual void* allocate(unsigned long size, unsigned long alignment) { return nullptr; }  // slot 5
    virtual void* allocate(unsigned long size, unsigned long alignment, const char* file, int line) {  // slot 6
        return nullptr;
    }
    virtual void* allocate_tail(unsigned long size, unsigned long alignment, const char* file, int line) {  // slot 7
        return nullptr;
    }
    virtual void deallocate(void* p, unsigned long size) {}  // slot 8
    virtual void* reallocate(void* p, unsigned long size) { return nullptr; }  // slot 9
    virtual void log(MemoryInfo* info, bool flag) const {}  // slot 10
    virtual const char* getName() const { return m_name.m_str; }  // slot 13
    virtual bool hasMemory(const void* p) const { return false; }  // slot 14
    virtual unsigned long getAllocSize(const void* p) const { return 0; }  // slot 15
    virtual void memoryInfo(MemoryInfo* info) const {}  // slot 16
    virtual void getMemImage(MEMIMAGE_HEAD* head) const {}  // slot 17
    virtual int getMemInfo1(MemoryInfo1* info, unsigned int flags) const { return 0; }  // slot 18
    virtual bool empty() const { return m_name.m_str[0] == '\0'; }  // slot 19
    virtual bool valid() const { return m_name.m_str[0] != '\0'; }  // slot 20
    virtual bool dummy() const { return m_name.m_str[0] != '\0'; }  // slot 21
    virtual unsigned int getMemSize(const void* p) const { return 0; }  // slot 22

    mm::mtl::FixStr<32> m_name;  // create's name (FixStr's asserts cite line 219/221)
};

}  // namespace mtl

#endif

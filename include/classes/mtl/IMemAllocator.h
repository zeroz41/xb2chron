#ifndef CLASSES_MTL_IMEMALLOCATOR_H
#define CLASSES_MTL_IMEMALLOCATOR_H

#include "mm/mtl/FixStr.h"

namespace mtl {

// the kind of allocator MemManager::createAllocator makes: 0 NullAllocator, 1 DlAllocator, 2 AssetAllocator<1024>
// (their getType values)
enum AllocatorType : int;

struct MemoryInfo;
struct MemoryInfo1;
struct MEMIMAGE_HEAD;

// monolib's allocator interface (the table none: its derived classes' tables; MemManager::Region holds one). Its
// destructor is out of line (the module's copy is a bare return); allocate_tail, log_callSTack and checkLeakMemory
// are inline defaults (emitted after the unit's functions)
class IMemAllocator {
public:
    virtual ~IMemAllocator();  // slot 0
    virtual void create(void* p, unsigned long size, const char* pszName) = 0;  // slot 2
    virtual void destroy() = 0;  // slot 3
    virtual AllocatorType getType() const = 0;  // slot 4
    virtual void* allocate(unsigned long size, unsigned long alignment) = 0;  // slot 5
    virtual void* allocate(unsigned long size, unsigned long alignment, const char* file, int line) = 0;  // slot 6
    virtual void* allocate_tail(unsigned long size, unsigned long alignment, const char* file, int line) {  // slot 7
        return nullptr;
    }
    virtual void deallocate(void* p, unsigned long size) = 0;  // slot 8
    virtual void* reallocate(void* p, unsigned long size) = 0;  // slot 9
    virtual void log(MemoryInfo* info, bool flag) const = 0;  // slot 10
    virtual void log_callSTack(void* p) const {}  // slot 11
    virtual void checkLeakMemory() {}  // slot 12
    virtual const char* getName() const = 0;  // slot 13
    virtual bool hasMemory(const void* p) const = 0;  // slot 14
    virtual unsigned long getAllocSize(const void* p) const = 0;  // slot 15
    virtual void memoryInfo(MemoryInfo* info) const = 0;  // slot 16
    virtual void getMemImage(MEMIMAGE_HEAD* head) const = 0;  // slot 17
    virtual int getMemInfo1(MemoryInfo1* info, unsigned int flags) const = 0;  // slot 18
    virtual bool empty() const = 0;  // slot 19
    virtual bool valid() const = 0;  // slot 20
    virtual bool dummy() const = 0;  // slot 21
};

}  // namespace mtl

#endif

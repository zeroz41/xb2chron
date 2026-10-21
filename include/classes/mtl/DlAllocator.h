#ifndef CLASSES_MTL_DLALLOCATOR_H
#define CLASSES_MTL_DLALLOCATOR_H

#include "classes/mtl/IMemAllocator.h"

namespace mtl { class MEMIMAGE_HEAD; }
namespace mtl { class MemoryInfo1; }
namespace mtl { class MemoryInfo; }

namespace mtl {
// table 0x7100B79320
class DlAllocator : public ::mtl::IMemAllocator {
public:
    virtual ~DlAllocator();  // slot 0
    virtual void create(void*, unsigned long, char const*);  // slot 2
    virtual void destroy();  // slot 3
    virtual void getType() const;  // slot 4
    virtual void allocate(unsigned long, unsigned long);  // slot 5
    virtual void allocate(unsigned long, unsigned long, char const*, int);  // slot 6
    virtual void deallocate(void*, unsigned long);  // slot 8
    virtual void reallocate(void*, unsigned long);  // slot 9
    virtual void log(mtl::MemoryInfo*, bool) const;  // slot 10
    virtual void log_callSTack(void*) const;  // slot 11
    virtual void checkLeakMemory();  // slot 12
    virtual void getName() const;  // slot 13
    virtual bool hasMemory(void const*) const;  // slot 14
    virtual void getAllocSize(void const*) const;  // slot 15
    virtual void memoryInfo(mtl::MemoryInfo*) const;  // slot 16
    virtual void getMemImage(mtl::MEMIMAGE_HEAD*) const;  // slot 17
    virtual void getMemInfo1(mtl::MemoryInfo1*, unsigned int) const;  // slot 18
    virtual void empty() const;  // slot 19
    virtual void valid() const;  // slot 20
    virtual bool dummy() const;  // slot 21
};
}  // namespace mtl

#endif

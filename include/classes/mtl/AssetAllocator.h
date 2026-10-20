#ifndef CLASSES_MTL_ASSETALLOCATOR_H
#define CLASSES_MTL_ASSETALLOCATOR_H

#include "classes/mtl/IMemAllocator.h"

namespace mtl { class MEMIMAGE_HEAD; }
namespace mtl { class MemoryInfo1; }
namespace mtl { class MemoryInfo; }

namespace mtl {
// a template: 1 instances in the module
template <int T0>
class AssetAllocator : public ::mtl::IMemAllocator {
public:
    virtual ~AssetAllocator();  // slot 0
    virtual void create(void*, unsigned long, char const*);  // slot 2
    virtual void destroy();  // slot 3
    virtual void getType() const;  // slot 4
    virtual void allocate(unsigned long, unsigned long);  // slot 5
    virtual void allocate(unsigned long, unsigned long, char const*, int);  // slot 6
    virtual void allocate_tail(unsigned long, unsigned long, char const*, int);  // slot 7
    virtual void deallocate(void*, unsigned long);  // slot 8
    virtual void reallocate(void*, unsigned long);  // slot 9
    virtual void log(mtl::MemoryInfo*, bool) const;  // slot 10
    virtual void getName() const;  // slot 13
    virtual void hasMemory(void const*) const;  // slot 14
    virtual void getAllocSize(void const*) const;  // slot 15
    virtual void memoryInfo(mtl::MemoryInfo*) const;  // slot 16
    virtual void getMemImage(mtl::MEMIMAGE_HEAD*) const;  // slot 17
    virtual void getMemInfo1(mtl::MemoryInfo1*, unsigned int) const;  // slot 18
    virtual void empty() const;  // slot 19
    virtual void valid() const;  // slot 20
    virtual void dummy() const;  // slot 21
};
}  // namespace mtl

#endif

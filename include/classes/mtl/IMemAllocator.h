#ifndef CLASSES_MTL_IMEMALLOCATOR_H
#define CLASSES_MTL_IMEMALLOCATOR_H

namespace mtl { class MemoryInfo; }

namespace mtl {
// table none (its derived classes')
class IMemAllocator {
public:
    virtual ~IMemAllocator() {}  // slot 0
    virtual void create(void*, unsigned long, char const*) = 0;  // slot 2
    virtual void destroy() = 0;  // slot 3
    virtual void getType() const = 0;  // slot 4
    virtual void allocate(unsigned long, unsigned long) = 0;  // slot 5
    virtual void allocate(unsigned long, unsigned long, char const*, int) = 0;  // slot 6
    virtual void allocate_tail(unsigned long, unsigned long, char const*, int);  // slot 7
    virtual void deallocate(void*, unsigned long) = 0;  // slot 8
    virtual void reallocate(void*, unsigned long) = 0;  // slot 9
    virtual void log(mtl::MemoryInfo*, bool) const = 0;  // slot 10
    virtual void log_callSTack(void*) const;  // slot 11
    virtual void checkLeakMemory();  // slot 12
};
}  // namespace mtl

#endif

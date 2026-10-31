#ifndef CLASSES_ML_MEMORYAUTORELEASER_H
#define CLASSES_ML_MEMORYAUTORELEASER_H

namespace ml {
// frees the memory it holds when it goes away (the class name and its destructor are the symbols'; the unit's static
// initializer constructs one file static and registers this destructor). The field name is not the original's.
class MemoryAutoReleaser {
public:
    MemoryAutoReleaser() : m_ptr(nullptr) {}
    ~MemoryAutoReleaser();
    void* m_ptr;  // malloc'ed memory, free()d by the destructor
};
}  // namespace ml

#endif

#ifndef CLASSES_SSD_ALLOCATOR_H
#define CLASSES_SSD_ALLOCATOR_H

#include <new>

namespace ssd {
// table none (its derived classes': fw::SoundSsdDriver::SoundAllocator's slot 0 holds this class's inline
// destructor). The sound library's memory source: MemoryManager calls slot 2 for an instance block's memory.
class Allocator {
public:
    // a block MemoryManager hands out (AcquireBlock fills it; the names are not the original's except
    // allocAdrs_, which MemoryManager::AllocInstance's assertion cites as "block->allocAdrs_"): the
    // allocator it came from, the aligned address, the allocator's own pointer, the element size times the
    // count, that size rounded up to the alignment, the element size and the count
    struct Block {
        Allocator* allocator;
        void* data;
        void* allocAdrs_;
        unsigned int size;
        unsigned int alignedSize;
        unsigned int elementSize;
        unsigned int count;
    };

    virtual ~Allocator() {}  // slot 0
    virtual void* AllocInstance(unsigned long size) = 0;  // slot 2
    virtual void FreeInstance(void* address) = 0;  // slot 3
    virtual void* AllocBuffer(unsigned long size, unsigned long alignment) = 0;  // slot 4
    virtual void FreeBuffer(void* address) = 0;  // slot 5
    virtual void* AllocStream(unsigned long size, unsigned long alignment) = 0;  // slot 6
    virtual void FreeStream(void* address) = 0;  // slot 7

    Block* NewInstanceImpl(unsigned long size, unsigned long count, unsigned long alignment);
    void DeleteInstanceImpl(Block* block);
    Block* GetMemoryBlock(void* address);
    Block* NewBufferImpl(unsigned long count, unsigned long elementSize, unsigned long alignment);
    void DeleteBufferImpl(Block* block);
    Block* NewStreamImpl(unsigned long size, unsigned long alignment);
    void DeleteStreamImpl(Block* block);

    // count instances of T default-initialized in one instance block (Array<T*>::SetArraySize leaves the
    // pointers unset), or null
    template <typename T>
    T* NewInstance(unsigned long count = 1, unsigned long alignment = 0x10) {
        Block* block = NewInstanceImpl(sizeof(T), count, alignment);
        if (block == nullptr) {
            return nullptr;
        }
        T* instances = static_cast<T*>(block->data);
        for (unsigned long i = 0; i < count; i++) {
            new (&instances[i]) T;
        }
        return instances;
    }

    // destroys every instance of the block holding instances and frees it
    template <typename T>
    void DeleteInstance(T* instances) {
        Block* block = GetMemoryBlock(instances);
        if (block != nullptr) {
            for (unsigned long i = 0; i < block->count; i++) {
                instances[i].~T();
            }
            DeleteInstanceImpl(block);
        }
    }

    // a buffer of count Ts, or null
    template <typename T>
    T* NewBuffer(unsigned long count, unsigned long alignment = 0x10) {
        Block* block = NewBufferImpl(count, sizeof(T), alignment);
        if (block == nullptr) {
            return nullptr;
        }
        return static_cast<T*>(block->data);
    }

    void DeleteBuffer(void* address) {
        DeleteBufferImpl(GetMemoryBlock(address));
    }
};

namespace SoundMemory {
// the allocator the library allocates from (MemoryManager::Init stores the one it is given)
extern Allocator* allocator_;
}  // namespace SoundMemory

}  // namespace ssd

#endif

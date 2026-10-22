#ifndef CLASSES_SSD_MEMORYMANAGER_H
#define CLASSES_SSD_MEMORYMANAGER_H

#include "classes/ssd/Allocator.h"
#include "classes/ssd/List.h"
#include "ssd/Mutex.h"

namespace ssd {
// table 0x7100B818E0: the sound library's block bookkeeping (memory_manager.cpp). Its one instance,
// memoryManager_, keeps numBlock_ BlockNodes: the free ones in one list, the ones handed out (an Allocator's
// instance, buffer or stream memory) in the other.
class MemoryManager {
public:
    class BlockNode;

    // 1.0.0 has the constructor out of line; 3.0.1 keeps no copy (the static initializer inlines it)
    MemoryManager() : initialized_(false), blocks_(nullptr), numBlock_(0) {}
    // inline: the module places its base destructor where memoryManager_'s registration first names it,
    // ahead of every other function of memory_manager.cpp, which only an inline destructor's does
    virtual ~MemoryManager() {  // slot 0
        Quit();
    }

    // sets up the manager over blockCount blocks from allocator (SoundCore::NewInstance passes 0x800)
    static void Init(int blockCount, Allocator* allocator);
    static void Quit();

    // a block of count elements of size bytes from allocator's instance memory, aligned, or null
    Allocator::Block* AllocInstance(Allocator* allocator, unsigned long size, unsigned long count,
                                    unsigned long alignment);
    void FreeInstance(Allocator* allocator, Allocator::Block* block);
    Allocator::Block* AllocBuffer(Allocator* allocator, unsigned long size, unsigned long count,
                                  unsigned long alignment);
    void FreeBuffer(Allocator* allocator, Allocator::Block* block);
    Allocator::Block* AllocStream(Allocator* allocator, unsigned long size, unsigned long alignment);
    void FreeStream(Allocator* allocator, Allocator::Block* block);
    // the handed-out block whose aligned address is address
    Allocator::Block* GetAllocatorBlock(void* address);
    // takes a free block for allocator and fills its sizes, or null when none is left
    Allocator::Block* AcquireBlock(Allocator* allocator, unsigned long size, unsigned long count,
                                   unsigned long alignment);
    // gives a block back to the free list
    void FreeBlock(Allocator::Block* block);

    static MemoryManager memoryManager_;

    // the names of the fields are not the original's except numInstance_, numBuffer_ and numStream_ (Quit's
    // assertions cite "memoryManager_.numInstance_ == 0" and the two others): the lock, whether Init ran, the
    // handed-out and the free blocks, the array Init allocates and its length, how many instance, buffer and
    // stream blocks are out, and whether the last AcquireBlock found the free list empty
    Mutex mutex_;
    bool initialized_;
    List<BlockNode> useList_;
    List<BlockNode> freeList_;
    BlockNode* blocks_;
    int numBlock_;
    int numInstance_;
    int numBuffer_;
    int numStream_;
    bool exhausted_;
};
}  // namespace ssd

// the lists' inline destructors need BlockNode complete wherever this class is seen
#include "classes/ssd/MemoryManager/BlockNode.h"

#endif

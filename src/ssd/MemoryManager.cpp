#include "nn/os.h"
#include "ssd/Debug.h"
#include "ssd/Mutex.h"
#include "classes/ssd/Allocator.h"
#include "classes/ssd/List.h"
#include "classes/ssd/MemoryManager.h"
#include "classes/ssd/MemoryManager/BlockNode.h"

namespace ssd {

MemoryManager MemoryManager::memoryManager_;

inline void MemoryManager::FreeBlock(Allocator::Block* block) {
    ScopedLock lock(mutex_);
    BlockNode* node = static_cast<BlockNode*>(block);
    useList_.Remove(node);
    node->allocator = nullptr;
    node->data = nullptr;
    node->allocAdrs_ = nullptr;
    freeList_.PushBack(node);
}

inline void MemoryManager::FreeInstance(Allocator* allocator, Allocator::Block* block) {
    allocator->FreeInstance(block->allocAdrs_);
    FreeBlock(block);
    numInstance_--;
}

inline void MemoryManager::FreeBuffer(Allocator* allocator, Allocator::Block* block) {
    allocator->FreeBuffer(block->allocAdrs_);
    FreeBlock(block);
    numBuffer_--;
}

inline void MemoryManager::FreeStream(Allocator* allocator, Allocator::Block* block) {
    allocator->FreeStream(block->allocAdrs_);
    FreeBlock(block);
    numStream_--;
}


Allocator::Block* Allocator::NewInstanceImpl(unsigned long size, unsigned long count, unsigned long alignment) {
    return MemoryManager::memoryManager_.AllocInstance(this, size, count, alignment);
}

void Allocator::DeleteInstanceImpl(Block* block) {
    MemoryManager::memoryManager_.FreeInstance(this, block);
}

Allocator::Block* Allocator::NewBufferImpl(unsigned long size, unsigned long count, unsigned long alignment) {
    return MemoryManager::memoryManager_.AllocBuffer(this, size, count, alignment);
}

void Allocator::DeleteBufferImpl(Block* block) {
    if (block != nullptr) {
        MemoryManager::memoryManager_.FreeBuffer(this, block);
    }
}

Allocator::Block* Allocator::NewStreamImpl(unsigned long size, unsigned long alignment) {
    return MemoryManager::memoryManager_.AllocStream(this, size, alignment);
}

void Allocator::DeleteStreamImpl(Block* block) {
    if (block != nullptr) {
        MemoryManager::memoryManager_.FreeStream(this, block);
    }
}

Allocator::Block* Allocator::GetMemoryBlock(void* address) {
    return MemoryManager::memoryManager_.GetAllocatorBlock(address);
}

void MemoryManager::Init(int blockCount, Allocator* allocator) {
    memoryManager_.mutex_.Initialize();
    SoundMemory::allocator_ = allocator;
    memoryManager_.blocks_ = new BlockNode[blockCount];
    for (int i = 0; i < blockCount; i++) {
        memoryManager_.blocks_[i].allocator = nullptr;
        memoryManager_.blocks_[i].allocAdrs_ = nullptr;
        memoryManager_.blocks_[i].data = nullptr;
        memoryManager_.freeList_.PushBack(&memoryManager_.blocks_[i]);
    }
    memoryManager_.numBlock_ = blockCount;
    memoryManager_.numInstance_ = 0;
    memoryManager_.numBuffer_ = 0;
    memoryManager_.numStream_ = 0;
    memoryManager_.initialized_ = true;
}

void MemoryManager::Quit() {
    if (memoryManager_.initialized_) {
        memoryManager_.useList_.Clear();
        memoryManager_.freeList_.Clear();
        delete[] memoryManager_.blocks_;
        memoryManager_.blocks_ = nullptr;
        memoryManager_.numBlock_ = 0;
        if (memoryManager_.numInstance_ != 0 || memoryManager_.numBuffer_ != 0 || memoryManager_.numStream_ != 0) {
#line 125
            SSD_ASSERT_MSG(memoryManager_.numInstance_ == 0, u"インスタンスが残っている可能性があります。");
            SSD_ASSERT_MSG(memoryManager_.numBuffer_ == 0, u"汎用バッファが残っている可能性があります。");
            SSD_ASSERT_MSG(memoryManager_.numStream_ == 0, u"ストリームバッファが残っている可能性があります。");
        }
        memoryManager_.numInstance_ = 0;
        memoryManager_.numBuffer_ = 0;
        memoryManager_.numStream_ = 0;
        memoryManager_.mutex_.Finalize();
    }
}
}  // namespace ssd

template ssd::List<ssd::MemoryManager::BlockNode>::Node::~Node();

namespace ssd {

Allocator::Block* MemoryManager::AllocInstance(Allocator* allocator, unsigned long size, unsigned long count,
                                               unsigned long alignment) {
    Allocator::Block* block = AcquireBlock(allocator, size, count, alignment);
    if (block != nullptr) {
        block->allocAdrs_ = allocator->AllocInstance(block->alignedSize);
#line 148 "D:/ssd/ssd51/ssd/sources/memory/memory_manager.cpp"
        SSD_ASSERT_NOT_NULL(block->allocAdrs_);
        if (block->allocAdrs_ == nullptr) {
            FreeBlock(block);
            return nullptr;
        }
        block->data = reinterpret_cast<void*>((reinterpret_cast<unsigned long>(block->allocAdrs_) + alignment - 1) &
                                              ~(alignment - 1));
        numInstance_++;
    }
    return block;
}

Allocator::Block* MemoryManager::AllocBuffer(Allocator* allocator, unsigned long size, unsigned long count,
                                             unsigned long alignment) {
    Allocator::Block* block = AcquireBlock(allocator, size, count, alignment);
    if (block != nullptr) {
        block->allocAdrs_ = allocator->AllocBuffer(block->alignedSize, alignment);
#line 185
        SSD_ASSERT_NOT_NULL(block->allocAdrs_);
        if (block->allocAdrs_ == nullptr) {
            FreeBlock(block);
            return nullptr;
        }
        block->data = reinterpret_cast<void*>((reinterpret_cast<unsigned long>(block->allocAdrs_) + alignment - 1) &
                                              ~(alignment - 1));
        numBuffer_++;
    }
    return block;
}

Allocator::Block* MemoryManager::AllocStream(Allocator* allocator, unsigned long size, unsigned long alignment) {
    Allocator::Block* block = AcquireBlock(allocator, size, 1, alignment);
    if (block != nullptr) {
        block->allocAdrs_ = allocator->AllocStream(block->alignedSize, alignment);
#line 229
        SSD_ASSERT_NOT_NULL(block->allocAdrs_);
        if (block->allocAdrs_ == nullptr) {
            FreeBlock(block);
            return nullptr;
        }
        block->data = reinterpret_cast<void*>((reinterpret_cast<unsigned long>(block->allocAdrs_) + alignment - 1) &
                                              ~(alignment - 1));
        numStream_++;
    }
    return block;
}

Allocator::Block* MemoryManager::GetAllocatorBlock(void* address) {
    Allocator::Block* freeBlock = nullptr;
    mutex_.Lock();
    if (address != nullptr) {
        List<BlockNode>::Node* node = useList_.head_.next;
        while (node != &useList_.head_) {
            if (static_cast<BlockNode*>(node)->data == address) {
                freeBlock = static_cast<BlockNode*>(node);
                break;
            }
            node = node->next;
        }
    }
    mutex_.Unlock();
#line 323
    SSD_ASSERT_MSG(freeBlock != nullptr, u"検索したメモリアドレスは管理外でした。");
    return freeBlock;
}

// not identical yet (11 words, register choice and schedule of the tail): the original multiplies count*size in
// 32 bits and adds (size + alignment) - 1; reading the product back from the block and a 32-bit alignment
// helper give that arithmetic, but the arguments land in other registers. The plain version, for reference:
/*
Allocator::Block* MemoryManager::AcquireBlock(Allocator* allocator, unsigned long size, unsigned long count,
                                              unsigned long alignment) {
    if (memoryManager_.blocks_ != nullptr) {
        mutex_.Lock();
        exhausted_ = freeList_.count_ == 0;
        if (!exhausted_) {
            BlockNode* node = static_cast<BlockNode*>(freeList_.head_.next);
            freeList_.Remove(node);
            useList_.PushBack(node);
            mutex_.Unlock();
            node->allocator = allocator;
            node->elementSize = size;
            node->count = count;
            node->size = size * count;
            node->alignedSize = (size * count + alignment - 1) & ~(alignment - 1);
            return node;
        }
        mutex_.Unlock();
        log_message(u"管理領域が枯渇しました。", 0);
        abort();
    }
    return nullptr;
}
*/

}  // namespace ssd

// explicit instantiation: as a weak_odr function Delete is no candidate for the inliner's deferral, so
// DeleteInstanceImpl is inlined into it and Delete stays out of line in ~List, as in the original
template ssd::List<ssd::MemoryManager::BlockNode>& ssd::List<ssd::MemoryManager::BlockNode>::Delete();

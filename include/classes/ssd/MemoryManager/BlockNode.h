#ifndef CLASSES_SSD_MEMORYMANAGER_BLOCKNODE_H
#define CLASSES_SSD_MEMORYMANAGER_BLOCKNODE_H

#include "classes/ssd/Allocator.h"
#include "classes/ssd/List.h"
#include "classes/ssd/MemoryManager.h"

namespace ssd {
// table 0x7100B81920: a block MemoryManager keeps, linked in one of its lists (AcquireBlock converts it to its
// Block at 0x18, FreeBlock back)
class MemoryManager::BlockNode : public List<BlockNode>::Node, public Allocator::Block {
public:
    virtual ~BlockNode() {}  // slot 0
};
}  // namespace ssd

#endif

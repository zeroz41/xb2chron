#ifndef CLASSES_SSD_MEMORYMANAGER_BLOCKNODE_H
#define CLASSES_SSD_MEMORYMANAGER_BLOCKNODE_H

#include "classes/ssd/MemoryManager.h"

namespace ssd {
// table 0x7100B81920
class MemoryManager::BlockNode {
public:
    virtual ~BlockNode();  // slot 0
};
}  // namespace ssd

#endif

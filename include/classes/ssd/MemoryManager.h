#ifndef CLASSES_SSD_MEMORYMANAGER_H
#define CLASSES_SSD_MEMORYMANAGER_H

namespace ssd {
// table 0x7100B818E0
class MemoryManager {
public:
    class BlockNode;
    virtual ~MemoryManager();  // slot 0
};
}  // namespace ssd

#endif

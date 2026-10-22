#ifndef CLASSES_SSD_MEMORYMANAGER_H
#define CLASSES_SSD_MEMORYMANAGER_H

namespace ssd { class Allocator; }

namespace ssd {
// table 0x7100B818E0
class MemoryManager {
public:
    class BlockNode;
    virtual ~MemoryManager();  // slot 0

    // sets up the manager over blockCount blocks from allocator (SoundCore::NewInstance passes 0x800)
    static void Init(int blockCount, Allocator* allocator);
    static void Quit();
};
}  // namespace ssd

#endif

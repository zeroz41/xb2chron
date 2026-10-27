#ifndef CLASSES_SSD_MEMORYBUFFER_H
#define CLASSES_SSD_MEMORYBUFFER_H

namespace ssd { class Allocator; }

namespace ssd {
// table 0x7100B823A8: a buffer from an allocator (SoundMemory::allocator_ unless Alloc is given one). The field
// names are not the original's.
class MemoryBuffer {
public:
    MemoryBuffer() : data_(nullptr), size_(0) {}
    // inline: its table is emitted with StreamController's, whose unit holds both destructors
    virtual ~MemoryBuffer() {  // slot 0
        Free();
    }

    void Alloc(unsigned long size, unsigned long alignment, Allocator* allocator);
    void Free();

    void* data_;
    unsigned long size_;
    Allocator* allocator_;
};
}  // namespace ssd

#endif

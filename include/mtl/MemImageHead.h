#ifndef MTL_MEMIMAGEHEAD_H
#define MTL_MEMIMAGEHEAD_H

namespace mtl {

// the block list an allocator's getMemImage fills (the struct name is the original's, from the slot's signature;
// the field names are inferred): m_num holds the room for images on entry and the images written on return
struct MEMIMAGE_HEAD {
    // one allocation: its address and size
    struct Image {
        void* m_addr;
        unsigned long m_size;
    };

    unsigned long pad_0;  // DlAllocator::getMemImage zeroes it when it has no mspace
    unsigned long pad_8;  // likewise
    unsigned long m_num;  // +0x10
    Image m_images[1];  // +0x18: m_num of them (written past the declared extent)
};

}  // namespace mtl

#endif

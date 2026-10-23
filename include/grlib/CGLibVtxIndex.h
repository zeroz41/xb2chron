#ifndef GRLIB_CGLIBVTXINDEX_H
#define GRLIB_CGLIBVTXINDEX_H

#include "grlib/GrlTypes.h"

namespace grlib {

// an index buffer in GPU memory (0x28 bytes)
class CGLibVtxIndex {
public:
    CGLibVtxIndex();
    ~CGLibVtxIndex();
    // a copy of count indices of the format, drawn as the primitive type
    void createCopyIndexBuff(const void* indices, unsigned int count, GrlPrimitiveType type, GrlIndexFormat format);
    void release();
    void drawIndex();
    void drawInsIndex(int instances);

    unsigned char pad_0[0x28];
};

}  // namespace grlib

#endif

#ifndef GRLIB_CGLIBUNIFORMARRAY_H
#define GRLIB_CGLIBUNIFORMARRAY_H

#include "grlib/CGLibTriUniformBlock.h"

namespace grlib {
// An array of uniform blocks (grlib::CGLibUniformArray<T>::setupArray(unsigned int) releases the old blocks,
// allocates num blocks and constructs them). Field names are not the original's.
template <class T>
class CGLibUniformArray {
public:
    void setupArray(unsigned int num);

    T* m_pArray;          // 0x0
    unsigned int m_num;   // 0x8
    unsigned char pad_C[0xC];
};

// ml::DrResMdoSeamWrk*::setupWork take a CGLibTriUniformArray*: the array of triangle uniform blocks
class CGLibTriUniformArray : public CGLibUniformArray<CGLibTriUniformBlock> {};
}  // namespace grlib

#endif

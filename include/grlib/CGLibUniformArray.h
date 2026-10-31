#ifndef GRLIB_CGLIBUNIFORMARRAY_H
#define GRLIB_CGLIBUNIFORMARRAY_H

#include "grlib/CGLibTriUniformBlock.h"
#include "grlib/CGLibMemHandle.h"
#include "mtl/MemManager.h"

namespace grlib {
// An array of uniform blocks (grlib::CGLibUniformArray<T>::setupArray(unsigned int) releases the old blocks,
// allocates num blocks and constructs them). Field names are not the original's.
template <class T>
class CGLibUniformArray {
public:
    void setupArray(unsigned int num);
    // releases every block, frees the array and m_mem (setupArray starts with it; ~LayerObjTopDef inlines it; the
    // name is not the original's)
    void release() {
        for (unsigned int i = 0; i < m_num; i++) {
            m_pArray[i].release();
        }
        m_num = 0;
        if (m_pArray != nullptr) {
            mtl::MemManager::deallocate(m_pArray, 0, false);
            m_pArray = nullptr;
        }
        CGLibMemHandle::free(m_mem);
    }

    T* m_pArray;          // 0x0
    unsigned int m_num;   // 0x8
    unsigned char pad_C[0xC];
    CGLibMemType m_mem;   // 0x18
};

// ml::DrResMdoSeamWrk*::setupWork take a CGLibTriUniformArray*: the array of triangle uniform blocks
class CGLibTriUniformArray : public CGLibUniformArray<CGLibTriUniformBlock> {};
}  // namespace grlib

#endif

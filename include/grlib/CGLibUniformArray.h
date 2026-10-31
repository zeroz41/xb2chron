#ifndef GRLIB_CGLIBUNIFORMARRAY_H
#define GRLIB_CGLIBUNIFORMARRAY_H

#include "grlib/CGLibDblUniformBlock.h"
#include "grlib/CGLibOneUniformBlock.h"
#include "grlib/CGLibTriUniformBlock.h"
#include "grlib/CGLibMemHandle.h"
#include "mtl/MemManager.h"

namespace grlib {
// An array of uniform blocks (grlib::CGLibUniformArray<T>::setupArray(unsigned int) releases the old blocks,
// allocates num blocks and constructs them). Field names are not the original's.
template <class T>
class CGLibUniformArray {
public:
    // DrShdDataList's and DrShdLgtTileBasedDr's constructors zero these and set up m_mem
    CGLibUniformArray() : m_pArray(nullptr), m_num(0), m_ofs(0), m_memSize(0) {}
    // DrShdLgtTileBasedDr's and DrShdDataList's destructors inline release()
    ~CGLibUniformArray() { release(); }
    void setupArray(unsigned int num);
    // takes size bytes of uniform memory for the blocks (DrShdLgtTileBasedDr::createWork and
    // DrShdDataList::createAlphaTestBlock inline it; the name is not the original's)
    void allocMem(unsigned int size) {
        m_ofs = size;
        CGLibMemHandle::free(m_mem);
        if (m_ofs != 0) {
            CGLibMemHandle::allocUniform(m_mem, m_ofs);
            m_memSize = m_ofs;
            m_ofs = 0;
        }
    }
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
    // the names below are not the original's
    unsigned int m_ofs;      // 0xC, the bytes of m_mem the blocks' setupArray calls took so far
    unsigned int m_memSize;  // 0x10, the size allocMem allocated
    unsigned char pad_14[0x4];
    CGLibMemType m_mem;   // 0x18
};

// ml::DrResMdoSeamWrk*::setupWork take a CGLibTriUniformArray*: the array of triangle uniform blocks
class CGLibTriUniformArray : public CGLibUniformArray<CGLibTriUniformBlock> {};
// ml::DrShdUniformBlockMan's material, volume texture and rim bloom arrays: double-buffered blocks
class CGLibDblUniformArray : public CGLibUniformArray<CGLibDblUniformBlock> {};
// ml::DrShdUniformBlockMan's motion blend arrays: single blocks
class CGLibOneUniformArray : public CGLibUniformArray<CGLibOneUniformBlock> {};
}  // namespace grlib

#endif

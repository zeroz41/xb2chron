#ifndef MM_MTL_BITFLAG_H
#define MM_MTL_BITFLAG_H

#include "mm/MMStdBase.h"

// mm_lib's bitflag.h, as the including file's include path named it (see mm/mtl/FixStr.h)
#ifdef MM_LIB_FROM_LIBS
#define MM_MTL_BITFLAG_PATH "../../../mcl/mm_lib/source\\mm_mtl/bitflag.h"
#else
#define MM_MTL_BITFLAG_PATH "D:/Monolithsoft/BF2/prog/application/BF2//../../libs/mcl/mm_lib/source\\mm_mtl/bitflag.h"
#endif

namespace mm { namespace mtl {

// Size flags in words of 32 (mm_mtl/bitflag.h; its assertions name the parameter `Size` and the index `index`).
// The class's and its members' names are not the original's; setting a flag asserts at line 89 (see
// GfGameFlag::setLocal), which is not written yet.
template <unsigned int Size>
class Bitflag {
public:
    // set and test as GfMenuManager's Bitflag<32> code shows them (one 32-bit word: no word index, the mask
    // 1UL << index without & 31); the names are not the original's
    void set(unsigned int index, bool on) {
#line 104 MM_MTL_BITFLAG_PATH
        MM_ASSERT(index < Size);
        unsigned long mask = 1UL << index;
        if (on) {
            m_flags[0] |= mask;
        } else {
            m_flags[0] &= ~mask;
        }
    }

    bool test(unsigned int index) const {
#line 133 MM_MTL_BITFLAG_PATH
        MM_ASSERT(index < Size);
        unsigned int mask = 1UL << index;
        return (m_flags[0] & mask) != 0;
    }

    // clears every flag (gevBattleEnd's single store; the name is not the original's)
    void reset() {
        for (unsigned int i = 0; i < (Size + 31) / 32; i++) {
            m_flags[i] = 0;
        }
    }

    bool operator[](unsigned int index) const {
#line 119 MM_MTL_BITFLAG_PATH
        MM_ASSERT(index < Size);
        unsigned int word = index >> 5;
        unsigned int mask = 1UL << (index & 31UL);
        return (m_flags[word] & mask) != 0;
    }

    unsigned int m_flags[(Size + 31) / 32];  // a word for every 32 flags or part of 32 (GfGameScene's Bitflag<6>)
};

}}  // namespace mm::mtl

#endif

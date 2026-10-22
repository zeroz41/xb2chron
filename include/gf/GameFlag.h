#ifndef GF_GAMEFLAG_H
#define GF_GAMEFLAG_H

#include "mm/mtl/Bitflag.h"

namespace gf {
// the game's flags, by width: GfGameFlag::getLocal and setLocal pick the array by the width in bits (1, 2, 4, 8, 16
// or 32) and index it. The field names are not the original's.
class GameFlag {
public:
    mm::mtl::Bitflag<0x10000> m_flag1;
    unsigned int m_flag2[0x1000];  // 16 to a word
    unsigned int m_flag4[0x400];  // 8 to a word
    unsigned char m_flag8[0x2000];
    unsigned short m_flag16[0xC00];
    unsigned int m_flag32[0xD08];
};
}  // namespace gf

#endif

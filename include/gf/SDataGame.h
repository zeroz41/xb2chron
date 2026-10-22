#ifndef GF_SDATAGAME_H
#define GF_SDATAGAME_H

#include "gf/GameFlag.h"

namespace gf {
// the game's data, as GfDataManager::getDataGame hands it out (1.0.0's GfGameUtil::setupNewGameParam takes one;
// that getDataGame's is one is inferred)
class SDataGame {
public:
    unsigned char pad_0[0xFBBC4];
    GameFlag m_gameFlag;  // GfGameFlag's (the name is not the original's)
};
}  // namespace gf

#endif

#ifndef GF_MAPJUMPFORRETURNBATTLE_H
#define GF_MAPJUMPFORRETURNBATTLE_H

namespace gf {

// 2.0.0's symbols name it (its constructor; GfPlayFactory::createMapJumpForReturnBattle takes one); the field names
// are not the original's. What GfGameArena::procMsgGameBtlArena (message type 2) and
// GfArenaBattle::mapjumpForReturnField pass to createMapJumpForReturnBattle: it copies m_mapjumpId into the first
// word of the GfMapjumpInfo it builds
struct MapJumpForReturnBattle {
    // out of line (gf_game_arena): GfArenaBattle::mapjumpForReturnField calls it; procMsgGameBtlArena inlines it
    MapJumpForReturnBattle();
    unsigned int m_mapjumpId;  // 0xE1
    unsigned char pad_4[4];
};

}  // namespace gf

#endif

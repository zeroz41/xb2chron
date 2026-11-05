#ifndef GF_MAPJUMPFORBATTLESTART_H
#define GF_MAPJUMPFORBATTLESTART_H

namespace gf {

// 2.0.0's symbols name it (GfPlayFactory::createMapJumpForBattleStart takes one); the field names are not the
// original's. GfArenaBattle::mapjumpForBattleStart builds one on the stack (8 bytes): GfBdatBtl's
// getBTL_ChBtlMapJump for its challenge, then 1 and 0; createMapJumpForBattleStart copies the id into the first word
// of the GfMapjumpInfo it builds and the two bytes into its flags at 0x165 and 0x166
struct MapJumpForBattleStart {
    unsigned int m_mapjumpId;
    unsigned char pad_4;
    unsigned char pad_5;
};

}  // namespace gf

#endif

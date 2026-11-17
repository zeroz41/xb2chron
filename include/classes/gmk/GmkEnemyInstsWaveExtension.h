#ifndef CLASSES_GMK_GMKENEMYINSTSWAVEEXTENSION_H
#define CLASSES_GMK_GMKENEMYINSTSWAVEEXTENSION_H

namespace gf { class GF_OBJ_HANDLE; }
namespace mm { class Vec3; }

namespace gmk {
// 3.0.1's symbols name it and its members setBattleStateEnemy and createPopupEffect (both in GmkElevator.cpp's unit).
// GmkEnemyInsts holds one at 0x184: GmkEnemyInsts::PopInfo::validatePopPos calls both with the insts plus 0x184 as
// this, the popped object and its PopInfo's pop action type, in the battle arena and on Ira. 4 bytes: the
// constructor clears 0x184..0x188 with one 4-byte store (a class with no table).
class GmkEnemyInstsWaveExtension {
public:
    // with flag bit 0, the popped enemy goes into battle (after idling for a non-zero pop action type) unless its
    // gimmick has an invincible condition
    void setBattleStateEnemy(gf::GF_OBJ_HANDLE* handle, unsigned char popActType) const;
    // on Ira, an enemy gimmick object popped with flag bit 1 and no invincible condition shows its list's pop effect
    // at pos (not for pop action types 3 to 6)
    void createPopupEffect(gf::GF_OBJ_HANDLE* handle, unsigned char popActType, const mm::Vec3& pos) const;
    // flag bits the enemy wave gimmick (GmkEnemyWave) sets: 0x2 and 0x1 in its create, 0x4 set by GmkEnemy::onGobEvent
    // on event 3 on Ira and cleared by GmkEnemyWave's seqWaitToValidLinkGmkList (the name is not the original's)
    unsigned char m_flags = 0;
    unsigned char pad_1 = 0;
    unsigned char pad_2 = 0;
    unsigned char pad_3 = 0;
};
}  // namespace gmk

#endif

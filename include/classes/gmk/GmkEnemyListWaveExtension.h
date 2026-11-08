#ifndef CLASSES_GMK_GMKENEMYLISTWAVEEXTENSION_H
#define CLASSES_GMK_GMKENEMYLISTWAVEEXTENSION_H

#include "classes/gmk/GmkEnemyWaveList.h"
#include "classes/gmk/IGmkList.h"
#include "mm/Vec3.h"

namespace gmk {
// 2.0.0's symbols name it and its members create and createPopEffect. GmkEnemyList holds one at 0x470:
// GmkEnemyList::createGmk calls create with the list plus 0x470 as this; create runs the wave list at its start
// (TGmkList<GmkEnemyWave>::create on this) and keeps an effect at 0x460.
class GmkEnemyListWaveExtension {
public:
    GmkEnemyListWaveExtension() : m_waveList(-1), m_popEffect(nullptr) {}
    // in the battle arena or on Ira: creates the wave list from the gimmick set row's "enemyWave_bdat" table and,
    // on Ira, finds the pop effect "ma40a_01_130_dlc" in the field's effect pack
    void create(IGmkList::CreateInfo& info);
    // creates the pop effect (category 2) at pos, if create found one
    void createPopEffect(const mm::Vec3& pos) const;
    GmkEnemyWaveList m_waveList;  // 0x0 (the name is not the original's)
    void* m_popEffect;  // 0x460: fw::EffectManager::search's (the name is not the original's)
};
}  // namespace gmk

#endif

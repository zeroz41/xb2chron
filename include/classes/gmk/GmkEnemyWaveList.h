#ifndef CLASSES_GMK_TUNK_B6D480_H
#define CLASSES_GMK_TUNK_B6D480_H

#include "classes/gmk/TGmkList.h"
#include "classes/gmk/GmkEnemyWave.h"
#include "classes/gmk/GmkBattleChallenge.h"

namespace gmk {
// 2.0.0's symbols name it. The gimmicks of kind 0x3A from the resource's 'ENEW' section, and a second list of kind 0x3B
// ('BTCL') whose BDAT table createGmk takes from the gimmick set's "battleChallenge_bdat" column.
class GmkEnemyWaveList : public ::gmk::TGmkList< ::gmk::GmkEnemyWave, ::gmk::GmkEnemyWave::BdatInfo, 1464159813u, 2u, ::gmk::GmkEnemyWaveGob> {
public:
    // the list of kind 0x3B: table 0x7100B6F098 (the name is not the original's)
    typedef TGmkList< ::gmk::GmkBattleChallenge, ::gmk::GmkBattleChallenge::BdatInfo, 1279480898u, 2u, ::gmk::GmkBattleChallengeGob> SubList;
    // out of line (0x71005B5488): GmkEnemyList's constructor calls it
    explicit GmkEnemyWaveList(unsigned int updateGmkNumPerFrame);
    virtual ~GmkEnemyWaveList();  // slot 0 (0x7100582E1C; D0 0x71005BC41C)
    virtual void create(gmk::IGmkList::CreateInfo const& info);  // slot 9 (0x7100583064)
    virtual void dispose();  // slot 10 (0x7100583068)
    virtual void update(float dt);  // slot 11 (0x71005830B8)
    virtual bool updateImmediate();  // slot 12 (0x7100583144)
    virtual void debugUpdateMmf();  // slot 13 (0x7100583258)
    virtual void debugDraw() const;  // slot 14 (0x710058327C)
    virtual void createGmk(void* data);  // slot 16 (0x71005B5910)
    SubList m_subList;  // 0x230 (the name is not the original's)
};
}  // namespace gmk

#endif

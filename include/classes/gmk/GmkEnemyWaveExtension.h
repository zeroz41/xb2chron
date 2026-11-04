#ifndef CLASSES_GMK_GMKENEMYWAVEEXTENSION_H
#define CLASSES_GMK_GMKENEMYWAVEEXTENSION_H

namespace gmk {
class GmkEnemy;

// 2.0.0's symbols name it and its members (getWavePopInfo, getBindedGmkEnemyWave, createSealedEnergyEffect,
// backHome; all in GmkElevator.cpp's unit, each taking the enemy). GmkEnemy holds one at 0x1d0:
// GfQuestTarget::getIconTypeBattle calls getBindedGmkEnemyWave with the enemy plus 0x1d0 as this and the enemy as its
// argument. Callers in its own unit leave this undefined (the functions do not read it).
class GmkEnemyWaveExtension {
public:
    // the enemy's wave pop settings, read by getWavePopInfo from its row (field names from the BDAT columns:
    // "party_flag", "Wpop_Priority", "Wpop_PopNumCond", "battlelockname" minus 1, "Wpop_TimerCond")
    struct WavePopInfo {
        unsigned char m_partyFlag;
        unsigned char m_popPriority;
        unsigned char m_popNumCond;
        short m_battleLockName;
        unsigned short m_popTimerCond;
    };
    // neither GmkEnemy's constructor (construct_n<gmk::GmkEnemy>) nor its copy (Vector<gmk::GmkEnemy>::expand, which
    // copies up to 0x1d0) writes it
    GmkEnemyWaveExtension() {}
    GmkEnemyWaveExtension(const GmkEnemyWaveExtension&) {}
    // reads enemy's WavePopInfo from its row while isInstalledBattleArenaContents or isGameTypeIra holds; its caller
    // is GmkEnemyWave::create
    void getWavePopInfo(const GmkEnemy* enemy, WavePopInfo& info) const;
    void* pad_0;  // size 8: GmkEnemy's size 0x1d8 (TGmkList::getInst's stride)
};
}  // namespace gmk

#endif

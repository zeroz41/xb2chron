#ifndef CLASSES_GMK_TUNK_B6D528_H
#define CLASSES_GMK_TUNK_B6D528_H

#include "classes/gmk/AGmkBase.h"
#include "classes/gmk/GmkPhantom.h"
#include "classes/gmk/GmkEnemyWave.h"
#include "classes/gmk/QuestFlagCond.h"
#include "classes/gmk/ScenarioFlagCond.h"
#include "plugin/Bdat.h"

namespace gmk {
// 2.0.0's symbols name it and its gimmick object type GmkBattleChallengeGob (TGmkList's 5th argument, which has no
// table or symbol of its own): the gimmick of kind 0x3B (table 0x7100B6D528). Element (0x100 bytes) of the list
// TGmkList<GmkBattleChallenge, ..., 'BTCL', ...> (table 0x7100B6F098) at 0x230 of GmkEnemyList's member at 0x470.
class GmkBattleChallengeGob;

class alignas(16) GmkBattleChallenge : public ::gmk::AGmkBase {
public:
    // weak (tail of the unit): emitted with the table, whose key function is create
    virtual ~GmkBattleChallenge() { dispose(); }  // slot 0 (~GmkBattleChallenge, dispose inlined; D0 ~GmkBattleChallenge)
    virtual gmk::GmkType getGmkType() const { return TYPE; }  // slot 2 (getGmkType)
    virtual bool isValid() const { return m_list != nullptr && m_createInfo.m_data != nullptr; }  // slot 3 (isValid)
    virtual void create(gmk::AGmkBase::CreateInfo const&);  // slot 4 (create, 0x234)
    virtual void dispose();  // slot 5 (dispose, 0xD8)
    virtual void update(float);  // slot 6 (update, 0x70)
    virtual void debugDraw() const;  // slot 7 (debugDraw, empty)
    // its bdat row (0xA bytes: createGmk's stride; read by initGmkBdatInfo initGmkBdatInfo, which inlines create; the
    // column names are the original's, the field names not)
    class BdatInfo {
    public:
        void create(CBdatWrapper bdat, int row, const AGmkBase& gmk) {
            m_scenarioFlag = ScenarioFlagCond((unsigned short)Bdat::getValCheck(bdat.m_fp, "ScenarioFlagMin", row, 2), (unsigned short)Bdat::getValCheck(bdat.m_fp, "ScenarioFlagMax", row, 2));
            m_questFlag = QuestFlagCond((unsigned short)Bdat::getValCheck(bdat.m_fp, "QuestFlag", row, 2), (unsigned char)Bdat::getValCheck(bdat.m_fp, "QuestFlagMin", row, 1),
                                        (unsigned char)Bdat::getValCheck(bdat.m_fp, "QuestFlagMax", row, 1));
            m_condition = (unsigned short)Bdat::getValCheck(bdat.m_fp, "Condition", row, 2);
        }
        ScenarioFlagCond m_scenarioFlag;  // 0x0
        QuestFlagCond m_questFlag;  // 0x4
        unsigned short m_condition;  // 0x8: "Condition"
    };
    static const gmk::GmkType TYPE = gmk::GmkType(0x3b);
    // its data (m_createInfo.m_data): the range of waves (GmkEnemyWave, GmkEnemyList's m_waveList) it runs, by index
    // (the names are not the original's)
    struct Data {
        unsigned char pad_0[0x4];
        unsigned int m_waveBegin;  // 0x4
        unsigned int m_waveEnd;    // 0x8
    };
    // the challenge's progress the battle code reads (btl::ChallengeBattleManager loads 0x0/0x4 and the byte at 0x8); the
    // names are not the original's
    struct State {
        State() { clear(); }
        void clear() {
            m_result = 0;
            m_isEnd = false;
            m_waveNum = 0;
            m_waveIndex = 0;
        }
        unsigned int m_waveNum;    // 0x0: how many waves it has
        unsigned int m_waveIndex;  // 0x4: the wave it is at (from 1)
        bool m_isEnd;              // 0x8
        int m_result;              // 0xC: 1 or 2 when a wave ended (2 while time was left)
    };
    const Data* getData() const { return reinterpret_cast<const Data*>(m_createInfo.m_data); }
    // how many waves it runs: none while not valid (the name is not the original's)
    unsigned int getWaveNum() const { return isValid() ? getData()->m_waveEnd - getData()->m_waveBegin : 0; }
    // its index-th wave in the gimmick set's enemy list, none when the set has no enemy list or fewer waves (defined
    // in GmkElevator.cpp, which sees GmkEnemyList; the name is not the original's)
    GmkEnemyWave* getWave(unsigned int index) const;
    // 2.0.0's symbols name them.
    AGmkBase* getBattleLock();
    // seqCheckCondition, seqWaveStart: the steps create and the first step store in m_seq
    void seqCheckCondition(float dt);
    void seqWaveStart(float dt);
    // 2.0.0's symbols name them. suspendAll (members: its address sits among this class's functions; suspend calls it
    // on sm_activeInstance with a bool).
    void suspendAll(bool);
    // seqWaitNextWave (step, next to seqWaveStart's family): counts m_timer down by dt, below 0 goes back to seqWaveStart
    void seqWaitNextWave(float dt);
    // suspend (btl::ChallengeBattleManager::UpdateProc calls it): suspendAll on the running challenge, if any
    static void suspend(bool);
    // 2.0.0's symbols name it. Empty (new in 3.0.1); gf::GfArenaBattle::fn_710028C9CC calls it with sm_battleStatus's word at +4 plus 1.
    // A static member: its address sits between seqWaitNextWave and suspend
    static void debugChangeWave(unsigned int);
    // terminate: clears sm_activeInstance, sm_targetGmkBdatId and sm_battleStatus (GfAppendWire's execBattle calls it)
    static void terminate();
    // the running challenge, set by seqCheckCondition (lbl_7100EB7DB0). 2.0.0's symbols name the three statics (in this
    // order; 2.0.0's sm_battleStatus is 0x10 bytes, 3.0.1's 0x14)
    static GmkBattleChallenge* sm_activeInstance;
    // set by GfAppendWire's execBattle from its message (lbl_7100EB7DB8)
    static unsigned int sm_targetGmkBdatId;
    // lbl_7100EB7DBC
    static State sm_battleStatus;
    unsigned char pad_48[0x8];
    GmkPhantom m_phantom;  // 0x50 (the name is not the original's)
    void (GmkBattleChallenge::*m_seq)(float dt);  // 0xE0: create sets seqCheckCondition, dispose clears it (the name is not the original's)
    unsigned short m_waveCount;  // 0xF0: the waves done (the name is not the original's)
    unsigned char pad_f2[0x2];
    float m_timer;  // 0xF4: seqWaveStart sets it from the wave's data (the name is not the original's)
    bool m_isAccCounted;  // 0xF8: create clears it, seqCheckCondition sets it after counting the access (the name is not the original's)
    bool m_isPaused;  // 0xF9: update skips m_seq when set (the name is not the original's)
    unsigned char pad_fa[0x2];
    int m_result;  // 0xFC: copied to sm_battleStatus.m_result (the name is not the original's)
};
}  // namespace gmk

#endif

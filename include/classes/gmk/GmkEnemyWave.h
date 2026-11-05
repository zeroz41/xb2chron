#ifndef CLASSES_GMK_TUNK_B6D418_H
#define CLASSES_GMK_TUNK_B6D418_H

#include "classes/gmk/AGmkBase.h"
#include "plugin/Bdat.h"
#include "classes/gmk/GmkAcc.h"
#include "classes/gmk/GmkPhantom.h"
#include "classes/gmk/GmkBattleLock.h"
#include "mm/mtl/FixedVector.h"
#include "classes/gmk/GmkEnemyWaveExtension.h"
#include "classes/gmk/ScenarioFlagCond.h"
#include "classes/gmk/QuestFlagCond.h"
#include "classes/gmk/TimeCond.h"
#include "classes/gmk/WeatherCond.h"

namespace gmk {
// 2.0.0's symbols name it. Element (0x4A0 bytes) of the list TGmkList<GmkEnemyWave, ..., 'ENEW', ...> (table
// 0x7100B6F140) that GmkEnemyList's member at 0x470 derives from. Inferred: the enemy wave gimmick gf_field_locator
// finds by "EnemyWaveID" (isPopCondMatched's notes below).
class GmkEnemyWaveGob;
class GmkEnemy;
class GmkSealedStone;

class alignas(16) GmkEnemyWave : public ::gmk::AGmkBase {
public:
    // weak (tail of the unit): emitted with the table, whose key function is create
    virtual ~GmkEnemyWave() { dispose(); }  // slot 0 (~GmkEnemyWave; D0 ~GmkEnemyWave)
    virtual gmk::GmkType getGmkType() const { return TYPE; }  // slot 2 (getGmkType)
    virtual bool isValid() const { return m_list != nullptr && m_createInfo.m_data != nullptr; }  // slot 3 (isValid)
    virtual void create(gmk::AGmkBase::CreateInfo const&);  // slot 4 (create, 0x314)
    virtual void dispose();  // slot 5 (dispose, 0x128; the destructor calls it out of line)
    virtual void update(float);  // slot 6 (update, 0x254)
    virtual void debugDraw() const;  // slot 7 (debugDraw, empty)
    virtual void onPlayerAccessed(gf::GF_OBJ_HANDLE*);  // slot 9 (onPlayerAccessed, 0x188)
    // its row (0x40 bytes: TGmkList::createGmk's stride; the names are not the original's)
    class BdatInfo {
    public:
        // its row reader: out of line (create), called by initGmkBdatInfo (initGmkBdatInfo) where the template
        // calls T1::create (so the name is the template's; the CBdatWrapper parameter as GmkElevator::BdatInfo's)
        void create(CBdatWrapper bdat, int row, const AGmkBase& gmk);
        // no constructor of its own: Vector<BdatInfo>::resize zero-fills each element, then stores the defaults below
        ScenarioFlagCond m_scenarioFlag;  // 0x0: "ScenarioFlagMin", "ScenarioFlagMax"
        QuestFlagCond m_questFlag;        // 0x4: "QuestFlag", "QuestFlagMin", "QuestFlagMax"
        TimeCond m_popTime;               // 0x8: "POP_TIME"
        WeatherCond m_popWeather;         // 0x18: "popWeather"
        unsigned short m_condition = 0;   // 0x28: "Condition"
        unsigned short m_opCondition = 0;  // 0x2A: "OP_Condition" (Ira only)
        unsigned short m_mapGimmickId = 0;  // 0x2C: "gimmick": the map gimmick (GmkType 0x21) seqWaitToValidLinkGmkList reaches with m_secondAcc
        unsigned char m_instanceMax = 0;  // 0x2E: "instanceMax"
        unsigned char m_onlyOnce = 0;     // 0x2F: "onlyOnce"
        unsigned short m_waitTime = 0;    // 0x30: "waitTime" (GmkBattleChallenge::seqWaveStart's timer, 0: none)
        unsigned short m_nameRadius = 10;  // 0x32: "nameRadius"
        unsigned int pad_34 = 0;
        unsigned short m_missMsgId = 0;   // 0x38: "missMSG_ID" (Ira only)
        unsigned short pad_3a = 0;
        unsigned short m_sealedStoneIndex = 0;  // 0x3C: "sealedStonePopID" (Ira only): from 1, the gimmick set's GmkSealedStoneList element seqWaitToValidLinkGmkList takes
    };
    const BdatInfo* getBdatInfo() const { return static_cast<const BdatInfo*>(m_createInfo.m_bdatInfo); }
    static const gmk::GmkType TYPE = gmk::GmkType(0x3a);
    // its data (m_createInfo.m_data): the range of enemies (GmkEnemy, the gimmick set's enemy list) it holds, by
    // index (the names are not the original's)
    struct Data {
        // how the player starts it: 2 by entering its phantom (seqWaitPlayerIntoPhantom), 1 by accessing it
        // (seqWaitAccessing) (reset's test)
        unsigned int m_accessType;
        float m_popRange;  // 0x4: seqUpdate pops while the player is closer than this (the name is not the original's)
        unsigned char pad_8[0x4];
        unsigned int m_enemyBegin;  // 0xC
        unsigned int m_enemyEnd;    // 0x10
    };
    const Data* getData() const { return reinterpret_cast<const Data*>(m_createInfo.m_data); }
    // one entry of the array isPopCondMatched walks (0x18 bytes): one of its enemies; create sorts them by priority, then
    // index
    struct Entry {
        Entry() {}
        // the pop settings copied member by member (create's stores skip the WavePopInfo's padding byte)
        Entry(GmkEnemy* enemy, unsigned short index, const GmkEnemyWaveExtension::WavePopInfo& popInfo) : m_enemy(enemy), pad_8(0), m_index(index), pad_e(0) {
            m_popInfo.m_partyFlag = popInfo.m_partyFlag;
            m_popInfo.m_popPriority = popInfo.m_popPriority;
            m_popInfo.m_popNumCond = popInfo.m_popNumCond;
            m_popInfo.m_battleLockName = popInfo.m_battleLockName;
            m_popInfo.m_popTimerCond = popInfo.m_popTimerCond;
        }
        GmkEnemy* m_enemy;
        unsigned int pad_8;  // create and seqWaitToValidLinkGmkList clear it
        unsigned short m_index;  // 0xC: its index in the data's range (the name is not the original's)
        unsigned short pad_e;  // create and seqWaitToValidLinkGmkList clear it
        GmkEnemyWaveExtension::WavePopInfo m_popInfo;  // 0x10 (the name is not the original's)
    };
    // 2.0.0's symbols name the next three (defined in GmkElevator.cpp's unit).
    // What isPopCondMatched does: false unless every entry of m_entries holds a valid gimmick with data at 0x48/0x50, a
    // positive count at 0x58 and a set byte at 0xE2; then its flags at 0x142, or its BdatInfo's conditions
    // (GfGameManager event state, GfGameCond::isGameCond). gf_field_locator's LocatorGimmick, LocatorGimmickEnemyWave
    // and GfGmkLocator call it.
    bool isPopCondMatched() const;
    // What getBindedEnemyNum does: its data's m_enemyEnd minus m_enemyBegin: how many enemies getBindedEnemy can return
    unsigned int getBindedEnemyNum() const;
    // What getBindedEnemy does: the GmkEnemy (0x1D8-byte element) at its data's m_enemyBegin plus index in the enemy
    // list of its list's create info (0x1B8), none when that list is missing or shorter
    GmkEnemy* getBindedEnemy(unsigned int index);
    // 2.0.0's symbols name it.
    void seqWaitToValidLinkGmkList(float dt);
    // 2.0.0's symbols name them.
    void applyPopCondMatchedEnemies(bool);
    void reset();
    // 2.0.0's symbols name it.
    void seqWaitAccessing(float dt);
    // 2.0.0's symbols name the next ones (defined in GmkElevator.cpp's unit; the steps m_seq runs).
    void seqFinish(float dt);
    void seqWaitPlayerIntoPhantom(float dt);
    void seqUpdate(float dt);
    void seqAbort(float dt);
    void seqAbortWait(float dt);
    // 2.0.0's symbols name it (seqUpdate calls it with the status counts and the free instance slots).
    void requestPopWaveEnemy(unsigned short gobNum, unsigned short popingNum, unsigned short freeNum, float dt);
    // 2.0.0's symbols name it (and getWavePopStatus). What its enemies are doing, counted by getWavePopStatus over its
    // entries (the field names are not the original's)
    struct WavePopStatus {
        unsigned int m_gobNum;      // objects (one per enemy unless its party flag is set) of the entries not popping
        unsigned int m_popingNum;   // the same for the entries popping (state 1 or 2), counted by what they pop
        unsigned int m_waitNum;     // entries that have not popped (state 0)
        unsigned int m_popNum;      // what all entries pop (arena and Ira only)
        unsigned int m_defeatNum;   // what the finished entries (state 3) popped and no longer hold
        bool m_isFlagged;           // an enemy has its wave flag 0x4 set
    };
    void getWavePopStatus(WavePopStatus& status) const;
    // 2.0.0's symbols name it. What it does (Ira, with a sealed stone): sends the stone an energy effect from pos and
    // posts its progress (the finished share of what the wave pops) to the stone's list
    void updateProgress(const mm::Vec3& pos) const;
    // how many game objects its enemies hold (the sum of their getGobInstNum)
    unsigned int getEnemyGobInstNum() const;
    // the remaining wave count seqUpdate keeps (reset, seqFinish: -1; 2.0.0's symbols name the static; it is
    // initialized at run time, so a type with a constructor: the type and member names are not the original's)
    struct ProgressInfo {
        ProgressInfo() : m_restNum(-1) {}
        int m_restNum;
    };
    static ProgressInfo sm_progressInfo;
    // the access count of the battle lock m_acc reaches, taken once (seqUpdate) and given back (reset, seqFinish)
    // (an inferred helper; the name is not the original's)
    void releaseAccCount() {
        if (m_isAccCounted && m_acc.isValid()) {
            static_cast<GmkBattleLock*>(m_acc.m_gmk)->pad_c4--;
            m_isAccCounted = false;
        }
    }
    gf::GF_OBJ_HANDLE* m_gob;  // 0x48: dispose destroys it unless it is -1 (the name is not the original's)
    float m_accessDistSq;  // 0x50: create squares the "0x7B" table's row 0 column 0x1E (the name is not the original's)
    unsigned char pad_54[0xc];
    GmkPhantom m_phantom;  // 0x60 (the name is not the original's)
    GmkAcc m_acc;  // 0xF0 (the name is not the original's)
    void (GmkEnemyWave::*m_seq)(float dt);  // 0x130: dispose clears it (the name is not the original's)
    bool m_isAccCounted;  // 0x140: create clears it after creating m_acc (the name is not the original's)
    // 0x141..0x145: flags the battle challenge (GmkBattleChallenge) reads and sets (the names are not the original's)
    bool m_isCleared;     // 0x141: seqWaveUpdate counts the waves up to the last one set
    bool m_isChallenge;   // 0x142: GmkBattleChallenge::create sets it
    bool m_isStarted;     // 0x143: GmkBattleChallenge::seqWaveStart sets it
    // 0x144: seqWaitPlayerIntoPhantom sets it once it has marked its invincible enemies (Ira); reset clears it (the
    // name is not the original's)
    bool m_isInvincibleMarked;
    bool m_isPaused;      // 0x145: GmkBattleChallenge::suspendAll sets it
    unsigned char pad_146[0x2];
    mm::mtl::FixedVector<Entry, 32> m_entries;  // 0x148, size at 0x448 (the name is not the original's)
    // 0x450: the gimmick set's sealed stone its row names, taken by seqWaitToValidLinkGmkList (the name is not the original's)
    GmkSealedStone* m_sealedStone;
    GmkAcc m_secondAcc;  // 0x458 (the name is not the original's)
};
}  // namespace gmk

#endif

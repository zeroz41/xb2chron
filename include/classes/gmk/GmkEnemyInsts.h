#ifndef CLASSES_GMK_GMKENEMYINSTS_H
#define CLASSES_GMK_GMKENEMYINSTS_H

#include "classes/gmk/ScenarioFlagCond.h"
#include "classes/gmk/QuestFlagCond.h"
#include "classes/gmk/TimeCond.h"
#include "classes/gmk/WeatherCond.h"
#include "classes/gmk/CloudCond.h"

class CBdatWrapper;
#include "classes/mm/mtl/ReferenceObject.h"
#include "mm/mtl/Vector.h"
namespace gf { class GF_OBJ_HANDLE; }
namespace gmk { class AGmkBase; }

namespace gmk {
// what GmkEnemyInsts::reqForcePopGobInst is asked to pop (layout not proven yet)
struct ForcePopEnemyInfo;

// a class with no table: an enemy gimmick's objects (GmkEnemy's at 0x48, GmkRoutedEnemy's at 0x50) and how they
// pop (its PopInfo at 0x98)
class GmkEnemyInsts {
public:
    class PopInfo {
    public:
        // one of the gimmick's pop slots (0x28 bytes: the destructors walk PopInfo's four at 0x28 apart)
        class PopEnemyInfo {
        public:
            ~PopEnemyInfo() { dispose(); }
            void dispose();
            // how many objects the slot has: its two lists' sizes (PopInfo::getGobInstNum adds the four slots';
            // inline, the name is not the original's)
            unsigned char getGobInstNum() const {
                if (pad_10 == nullptr || pad_18 == nullptr) {
                    return 0;
                }
                return pad_10->size() + pad_18->size();
            }
            unsigned char pad_0[0x4];
            unsigned char pad_4;  // GmkEnemyInsts::isQuestDead: false unless it equals pad_21 in every slot
            unsigned char pad_5[0x7];
            // the pop finders snap the position on the ground only when it is set (with their isYSnap)
            bool pad_c;
            unsigned char pad_d[0x3];
            // the slot's object handles in two lists (dispose empties and deletes both; getGobInst indexes pad_18
            // first, then pad_10)
            mm::mtl::Vector<gf::GF_OBJ_HANDLE*>* pad_10;
            mm::mtl::Vector<gf::GF_OBJ_HANDLE*>* pad_18;
            unsigned char pad_20;
            // GmkEnemyInsts::isQuestDead compares it with pad_4 in each slot (meaning not known)
            unsigned char pad_21;
            unsigned char pad_22[0x6];
        };
        // ~GmkEnemyInsts inlines it: each slot's dispose, the byte at 0x2 cleared, then the slots' destructors in
        // reverse (the name of dispose is not the original's)
        ~PopInfo() { dispose(); }
        void dispose() {
            for (unsigned int i = 0; i < 4; i++) {
                m_enemyInfos[i].dispose();
            }
            pad_2 = 0;
        }
        unsigned int getGobInstNum() const;  // how many objects pop
        // LocatorBat_EnemySpeciesID::update skips a gimmick when it answers true for the species with true
        bool hasTypeGenus(unsigned char genus, bool) const;
        // seqUpdateRepopCounter calls it as the counter runs out
        void removeDefeatedNamedEnemyInfo();
        unsigned char pad_0[0x2];
        unsigned char pad_2;
        unsigned char pad_3[0x5];
        PopEnemyInfo m_enemyInfos[4];  // 0x8 (the name is not the original's)
    };
    // the gimmick's row as it pops (GmkEnemy's at 0x80)
    // a gimmick row's pop conditions (create reads them; 0x60 bytes)
    class BdatInfo {
    public:
        void create(CBdatWrapper bdat, int row, const AGmkBase& gmk);
        bool isPopCondMatched() const;
        bool isInvincibleCondMatched() const;
        // whether the row's pop conditions hold for a summon (GfSmnEnemyManager::execAbsSummon asks before popping)
        bool isPopCondMatchedOfSmn() const;
        // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it (1.0.0's create reads only "pop_smn",
        // inline). A static member because only create calls it, right after create in this class's unit, and it
        // takes create's table and row (no this). What it does: the row's summon groups as bits: "flag" bit
        // "pop_smn" -> 1, and "pop_smn2"/"pop_smn3"/"pop_smn4" -> 2/4/8 when the sheet has that column and the bit
        // is set.
        static unsigned char fn_710058356C(CBdatWrapper bdat, int row);
        // the field names are not the original's (the row's column names)
        unsigned short m_condition;  // 0x0: "Condition"
        bool m_enePriority;          // 0x2: "flag" bit "ene_priority"
        // the summon groups the gimmick answers, one bit each (execAbsSummon tests its info's bit; clearSmnEnemies
        // destroys a GmkEnemy's object when any is set)
        unsigned char m_smnGroups;          // 0x3
        unsigned short m_squadId;           // 0x4: "squadId"
        unsigned short m_squadScale;        // 0x6: "squadScale", 100 for 0
        unsigned char m_form;               // 0x8: "form"
        unsigned char m_formRange;          // 0x9: "form_range"
        unsigned short m_mutekiCondition;   // 0xA: "muteki_Condition"
        bool m_specialName;                 // 0xC: the row's "name" is ma20a_b05_23 or ma20a_b05_24
        unsigned char pad_d;
        ScenarioFlagCond m_scenarioFlag;    // 0xE
        QuestFlagCond m_questFlag;          // 0x12
        // 0x16..0x18: padding (GmkEnemy's copy copies 0x0..0x16 as one run)
        TimeCond m_popTime;                 // 0x18: "POP_TIME"
        WeatherCond m_popWeather;           // 0x28: "popWeather"
        CloudCond m_popCloud;               // 0x38: "flag" bit "popCloud"
        QuestFlagCond m_mutekiQuestFlag;    // 0x48: "muteki_QuestFlag"/Min/Max
        // 0x4c..0x50: tail padding (not copied); size 0x50: the holders' copies copy 0x88..0x188 of the insts as one
        // run, which a member with a non-trivial copy cannot share
    };
    // what update and the sequence steps are given (the seq steps read its first float as the frame time)
    class UpdateInfo {
    public:
        float m_dt;  // (the name is not the original's; fields after it unknown)
    };
    // GmkEnemy's and GmkRoutedEnemy's dispose inline it (the name is not the original's): the flags' low three bits,
    // the objects, the counted reference at 0x150 and the distances back to their defaults
    void dispose() {
        m_flags &= ~7UL;
        disposeGobInsts(false, false);
        if (pad_150 != nullptr) {
            pad_150->release();
            pad_150 = nullptr;
        }
        pad_0 = 0;
        pad_8 = 0;
        pad_10 = -1;
        pad_14 = 100.0f;
        pad_18 = 50.0f;
        m_popDist = 110.0f;
        m_depopDist = 55.0f;
        pad_24 = 0;
        pad_28 = 0;
        pad_2c = 0;
        pad_30 = 0;
        pad_34 = 0;
    }
    ~GmkEnemyInsts();
    void disposeGobInsts(bool, bool);
    gf::GF_OBJ_HANDLE* getGobInst(unsigned int index) const;  // the handle of one of them
    bool isQuestDead() const;
    // pops the gimmick's objects now (GfSmnEnemyManager::execAbsSummon)
    void reqForcePopGobInst(const ForcePopEnemyInfo& info) const;
    // asks a running repop counter to restart from 0 (true when the sequence is seqUpdateRepopCounter)
    bool reqClearRepopCounter() const;
    void seqUpdatePopDepop(const UpdateInfo& info);
    void seqUpdateRepopCounter(const UpdateInfo& info);
    // whether it holds what it pops by: its first two fields set and a positive count at 0x10 (inline in GmkEnemy's
    // and GmkRoutedEnemy's isValid; the name is not the original's)
    bool isValid() const { return pad_0 != 0 && pad_8 != 0 && pad_10 > 0; }
    unsigned long pad_0;
    unsigned long pad_8;
    // seqUpdateRepopCounter never counts down for the values 40012 and 40013 (a bdat id? not proven)
    int pad_10;
    float pad_14;  // 100 after dispose
    float pad_18;  // 50 after dispose
    // the distances its objects pop within and depop beyond (GfRelSmnEnemy::create squares them; the names are not
    // the original's)
    float m_popDist;
    float m_depopDist;
    unsigned int pad_24;
    unsigned int pad_28;
    unsigned int pad_2c;
    unsigned int pad_30;
    unsigned int pad_34;
    BdatInfo m_bdatInfo;  // 0x38 (the name is not the original's)
    unsigned char pad_88[0x10];  // the constructor clears it
    PopInfo m_popInfo;  // 0x98 (the name is not the original's)
    // fields (its destructor 0x71005D85E8 touches +0x150, +0x178); size 0x188: GmkRoutedEnemy's Vector follows it at
    // 0x1d8 (insts at 0x50; its copy copies the insts up to 0x188)
    unsigned char pad_140;
    bool pad_141;  // when set, seqUpdateRepopCounter ends the count at once
    unsigned char pad_142[0xe];
    // released by dispose (reference_object.h's `m_RefCount > 0`); what it holds is unknown
    mm::mtl::ReferenceObject* pad_150;
    unsigned char pad_158[0x2];
    // set by reqClearRepopCounter (a const member), cleared by seqUpdateRepopCounter as it zeroes m_popWait (the
    // name is not the original's)
    mutable bool m_clearRepopCounterReq;
    unsigned char pad_15b[0x5];
    // the sequence step (seqUpdateRepopCounter moves on to seqUpdatePopDepop; the name is not the original's)
    void (GmkEnemyInsts::*m_seq)(const UpdateInfo&);
    // LocatorBat_EnemySpeciesID::update shows a gimmick that has no object only while this is not above 0 (meaning
    // not known; the name is not the original's)
    float m_popWait;
    unsigned char pad_174[0x4];
    // flag bits (canDepopGobInst tests bits 0 and 2; dispose clears bits 0..2 with one 64-bit and; the name is not
    // the original's)
    unsigned long m_flags;
    unsigned char pad_180[0x8];
};
}  // namespace gmk

#endif

#ifndef CLASSES_GMK_GMKENEMYINSTS_H
#define CLASSES_GMK_GMKENEMYINSTS_H

#include "classes/gmk/ScenarioFlagCond.h"
#include "classes/gmk/QuestFlagCond.h"
#include "classes/gmk/TimeCond.h"
#include "classes/gmk/WeatherCond.h"
#include "classes/gmk/CloudCond.h"

class CBdatWrapper;
#include "classes/mm/mtl/ReferenceObject.h"
#include "classes/gmk/GmkSquad.h"
#include "mm/mtl/Vector.h"
namespace gf { class GF_OBJ_HANDLE; }
namespace gmk { class AGmkBase; }
namespace mm { class Vec3; }

namespace gmk {
// what GmkEnemyInsts::reqForcePopGobInst is asked to pop (12 bytes: GfSmnEnemyManager::execAbsSummon builds one on
// the stack with a byte at 0x0 and zeroes at 0x4 and 0x8; reqForcePopGobInst keeps it at the insts' 0x144; the
// field names are not the original's)
struct ForcePopEnemyInfo {
    unsigned char pad_0 = 0;
    unsigned int pad_4 = 0;
    unsigned char pad_8 = 0;
};

// a class with no table: an enemy gimmick's objects (GmkEnemy's at 0x48, GmkRoutedEnemy's at 0x50) and how they
// pop (its PopInfo at 0x98)
class GmkEnemyInsts {
public:
    class IPopXformFinder;
    class PopInfo {
    public:
        // what seqUpdatePopDepop gives create: the insts' 0x8, 0x10 and its m_forcePopInfo's byte at 0x0 (the field
        // names are not the original's)
        class CreateInfo {
        public:
            unsigned char* pad_0;
            int pad_8;
            unsigned char pad_c;
        };
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
            // the defaults: Vector<GmkEnemy>::resize's stores (gaps at 0xd and 0x22 not set), as PopInfo::create
            // 0x7100583BAC resets each slot before it reads the row. The names m_eneId..m_chestHeight are not the
            // original's: the columns create reads into them.
            unsigned short m_eneId = 0;  // 0x0: the slot's enemy column of the row
            unsigned char pad_2 = 0;     // 0x2: the slot's next column (read as type 4)
            unsigned char pad_3 = 0;     // 0x3: a percentage: create counts pad_4 up by rolls against it
            // how many objects the slot pops (create rolls it); GmkEnemyInsts::isQuestDead: false unless it equals
            // pad_21 in every slot
            unsigned char pad_4 = 0;
            unsigned char m_fldMoveType = 0;  // 0x5: the slot's column, else the enemy's "FldMoveType"
            unsigned char m_actType = 0;      // 0x6: the enemy's "ActType"
            unsigned char m_typeGenus = 0;    // 0x7: the enemy's "TypeGenus"
            float m_chestHeight = 0.0f;       // 0x8: the enemy's "ChestHeight" / 100
            // the pop finders snap the position on the ground only when it is set (with their isYSnap); create
            // sets it unless m_actType is 3
            bool pad_c = false;
            unsigned char pad_d[0x3];
            // the slot's object handles in two lists (dispose empties and deletes both; getGobInst indexes pad_18
            // first, then pad_10)
            mm::mtl::Vector<gf::GF_OBJ_HANDLE*>* pad_10 = nullptr;
            mm::mtl::Vector<gf::GF_OBJ_HANDLE*>* pad_18 = nullptr;
            unsigned char pad_20 = 0;
            // GmkEnemyInsts::isQuestDead compares it with pad_4 in each slot (meaning not known)
            unsigned char pad_21 = 0;
            unsigned char pad_22[0x2];
            unsigned int pad_24 = 0;
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
        // 2.0.0's symbols name it (0x7100585078); GmkEnemyWave::requestPopWaveEnemy asks it whether a popping entry is done
        bool isPopFinished() const;
        // LocatorBat_EnemySpeciesID::update skips a gimmick when it answers true for the species with true
        bool hasTypeGenus(unsigned char genus, bool) const;
        // GfGameUtil::clearEnemyRepopCounter asks it with the enemy id and true before clearing the counter
        bool hasEneID(unsigned short id, bool) const;
        void create(const CreateInfo& info);
        void update(const GmkEnemyInsts& insts, const IPopXformFinder& finder);
        void validatePopPos(float dt, const GmkEnemyInsts& insts, const IPopXformFinder& finder);
        // takes an object out of the slots (onEnemyDead passes true)
        void removeGobInst(gf::GF_OBJ_HANDLE* handle, bool);
        // seqUpdateRepopCounter calls it as the counter runs out
        void removeDefeatedNamedEnemyInfo();
        // create's "flag" bit "ene_priority" and "pop_act_type" (the names are not the original's)
        bool m_enePriority = false;
        unsigned char m_popActType = 0;
        unsigned char pad_2 = 0;  // create clears it first and sets it to 1 at the end
        unsigned char pad_3[0x5];
        PopEnemyInfo m_enemyInfos[4];  // 0x8 (the name is not the original's)
    };
    // what finds the objects' pop positions (GmkEnemy and GmkRoutedEnemy each derive a PopXformFinder from it: four
    // slots, no destructor; the slot names are 3.0.1's symbols of GmkEnemy::PopXformFinder)
    class IPopXformFinder {
    public:
        virtual bool findPosRot(mm::Vec3& pos, mm::Vec3& rot, gf::GF_OBJ_HANDLE* handle,
                                const PopInfo::PopEnemyInfo& info) const = 0;  // slot 0
        virtual bool isYSnap() const = 0;  // slot 1
        // true when the object has its place (GmkEnemy::PopXformFinder::onPopGob returns true)
        virtual bool onPopGob(gf::GF_OBJ_HANDLE* handle) const = 0;  // slot 2
        // seqUpdatePopDepop passes the four slots' pad_4 counts summed after PopInfo::create
        virtual void onCreateGobInsts(unsigned int num) const = 0;  // slot 3
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
        // the defaults: Vector<GmkEnemy>::resize's stores (pad_d not set)
        unsigned short m_condition = 0;  // 0x0: "Condition"
        bool m_enePriority = false;      // 0x2: "flag" bit "ene_priority"
        // the summon groups the gimmick answers, one bit each (execAbsSummon tests its info's bit; clearSmnEnemies
        // destroys a GmkEnemy's object when any is set)
        unsigned char m_smnGroups = 0;          // 0x3
        unsigned short m_squadId = 0;           // 0x4: "squadId"
        unsigned short m_squadScale = 100;      // 0x6: "squadScale", 100 for 0
        unsigned char m_form = 0;               // 0x8: "form"
        unsigned char m_formRange = 0;          // 0x9: "form_range"
        unsigned short m_mutekiCondition = 0;   // 0xA: "muteki_Condition"
        bool m_specialName = false;             // 0xC: the row's "name" is ma20a_b05_23 or ma20a_b05_24
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
        // the names are not the original's
        float m_dt;
        unsigned char pad_4[0x4];
        const mm::Vec3* m_pos;  // 0x8: updatePopDepopCond measures from it to getInterestPos
        const IPopXformFinder* m_finder;  // 0x10
    };
    // what create takes (GmkRoutedEnemy::create builds it on the stack: the gimmick, its list's BDAT table, its row,
    // then four distances from the row or the list's defaults and the repop time; 0x38 bytes; the names are not the
    // original's). The defaults are the insts' own (100, 50, 110, 55, then zeros).
    class CreateInfo {
    public:
        CreateInfo()
            : m_popRange(100.0f), m_popHeight(50.0f), m_depopRange(110.0f), m_depopHeight(55.0f), m_repopTime(0.0f),
              pad_28(0), pad_2c(0), pad_30(0), pad_34(0) {}
        const AGmkBase* m_gmk;    // 0x0
        unsigned char* m_bdatFp;  // 0x8: the list's getBindedBdatFp
        int m_bdatId;             // 0x10: the gimmick's row
        float m_popRange;         // 0x14: "ene_disp_r"
        float m_popHeight;        // 0x18: "ene_disp_h"
        float m_depopRange;       // 0x1c: "ene_disp_r" + "ene_release_r"
        float m_depopHeight;      // 0x20: "ene_disp_h" + "ene_release_h"
        float m_repopTime;        // 0x24: "e_repoptime" * 60
        unsigned int pad_28;
        unsigned int pad_2c;
        unsigned int pad_30;
        unsigned int pad_34;
    };
    void create(const CreateInfo& info);
    // GmkEnemy's and GmkRoutedEnemy's dispose inline it (the name is not the original's): the flags' low three bits,
    // the objects, the counted reference at 0x150 and the distances back to their defaults
    void dispose() {
        m_flags &= ~7UL;
        disposeGobInsts(false, false);
        if (m_squad != nullptr) {
            m_squad->release();
            m_squad = nullptr;
        }
        m_gmk = nullptr;
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
    // releases the squad, then with a squad id makes one from the gimmick set's row and the id less one, with num
    // members and scale (GmkSquad's pad_2c)
    void createSquad(unsigned short squadId, unsigned int num, float scale);
    gf::GF_OBJ_HANDLE* getGobInst(unsigned int index) const;  // the handle of one of them (-1 past the last)
    bool isQuestDead() const;
    // shows or hides one of its objects by pad_140 (display bit 8) when the object is bound to a gimmick
    void validateDisp(gf::GF_OBJ_HANDLE* handle) const;
    // every object's display by validateDisp(handle)
    void validateDisp() const;
    // pops the gimmick's objects now (GfSmnEnemyManager::execAbsSummon)
    // false while objects are out, or for a summon gimmick without flag bit 2; else keeps info and sets pad_141
    bool reqForcePopGobInst(const ForcePopEnemyInfo& info) const;
    // asks a running repop counter to restart from 0 (true when the sequence is seqUpdateRepopCounter)
    bool reqClearRepopCounter() const;
    void seqUpdatePopDepop(const UpdateInfo& info);
    // m_flags: bit 0 the pop conditions hold, bit 1 the interest position is within the pop range (pad_88/pad_8c),
    // bit 2 within the depop range (pad_90/pad_94)
    void updatePopDepopCond(const UpdateInfo& info);
    void seqUpdateRepopCounter(const UpdateInfo& info);
    // back to seqUpdatePopDepop once no object is left
    void seqWaitToFadeOutOfGobInst(const UpdateInfo& info);
    bool canDepopGobInst() const;
    // the object's user data cleared and the object taken out; with none left the repop counter starts (not for a
    // summon gimmick)
    void onEnemyDead(gf::GF_OBJ_HANDLE* handle);
    // whether it holds what it pops by: its first two fields set and a positive count at 0x10 (inline in GmkEnemy's
    // and GmkRoutedEnemy's isValid; the name is not the original's)
    bool isValid() const { return m_gmk != nullptr && pad_8 != 0 && pad_10 > 0; }
    // the defaults: Vector<GmkEnemy>::resize's stores, the same values dispose sets
    // 0x0: its gimmick (create copies CreateInfo::m_gmk; createSquad reaches the gimmick set through its list)
    const AGmkBase* m_gmk = nullptr;
    // the gimmick's BDAT table (create reads its rows' "ene1num".."ene4num" from it; PopInfo::create gets it)
    unsigned char* pad_8 = nullptr;
    // seqUpdateRepopCounter never counts down for the values 40012 and 40013 (a bdat id? not proven)
    int pad_10 = -1;
    float pad_14 = 100.0f;  // 100 after dispose
    float pad_18 = 50.0f;   // 50 after dispose
    // the distances its objects pop within and depop beyond (GfRelSmnEnemy::create squares them; the names are not
    // the original's)
    float m_popDist = 110.0f;
    float m_depopDist = 55.0f;
    // onEnemyDead starts the repop counter m_popWait from it
    float pad_24 = 0.0f;
    unsigned int pad_28 = 0;
    unsigned int pad_2c = 0;
    unsigned int pad_30 = 0;
    unsigned int pad_34 = 0;
    BdatInfo m_bdatInfo;  // 0x38 (the name is not the original's)
    // create squares the CreateInfo's four distances into these: pop range across and in height, depop range across
    // and in height (updatePopDepopCond); the constructor clears them with one paired store
    float pad_88 = 0.0f;
    float pad_8c = 0.0f;
    float pad_90 = 0.0f;
    float pad_94 = 0.0f;
    PopInfo m_popInfo;  // 0x98 (the name is not the original's)
    // fields (its destructor 0x71005D85E8 touches +0x150, +0x178); size 0x188: GmkRoutedEnemy's Vector follows it at
    // 0x1d8 (insts at 0x50; its copy copies the insts up to 0x188)
    // the defaults from here on: Vector<GmkEnemy>::resize's stores (the gaps are not set)
    unsigned char pad_140 = 1;
    // when set, seqUpdateRepopCounter ends the count at once (reqForcePopGobInst sets it)
    mutable bool pad_141 = false;
    unsigned char pad_142[0x2];
    // reqForcePopGobInst's info (the name is not the original's)
    mutable ForcePopEnemyInfo m_forcePopInfo;
    // its squad, counted (createSquad makes it; dispose releases it; the name is not the original's)
    GmkSquad* m_squad = nullptr;
    unsigned char pad_158 = 0;
    unsigned char pad_159 = 0;
    // set by reqClearRepopCounter (a const member), cleared by seqUpdateRepopCounter as it zeroes m_popWait (the
    // name is not the original's)
    mutable bool m_clearRepopCounterReq = false;
    unsigned char pad_15b[0x5];
    // the sequence step (seqUpdateRepopCounter moves on to seqUpdatePopDepop; the name is not the original's)
    void (GmkEnemyInsts::*m_seq)(const UpdateInfo&) = nullptr;
    // LocatorBat_EnemySpeciesID::update shows a gimmick that has no object only while this is not above 0 (meaning
    // not known; the name is not the original's)
    float m_popWait = -1.0f;
    unsigned char pad_174[0x4];
    // flag bits (canDepopGobInst tests bits 0 and 2; dispose clears bits 0..2 with one 64-bit and; the name is not
    // the original's)
    unsigned long m_flags = 0;
    unsigned char pad_180 = 0;  // canDepopGobInst: no depop while set (a byte)
    unsigned char pad_181 = 0;
    unsigned char pad_182[0x2];
    // 0x184: flag bits the enemy wave gimmick (GmkEnemyWave) sets: 0x2 and 0x1 in its create, 0x4 cleared by its
    // seqWaitToValidLinkGmkList (the name is not the original's)
    unsigned char m_waveFlags = 0;
    // the constructor clears 0x184..0x188 with one 4-byte store (the types are not known)
    unsigned char pad_185 = 0;
    unsigned char pad_186 = 0;
    unsigned char pad_187 = 0;
};
}  // namespace gmk

#endif

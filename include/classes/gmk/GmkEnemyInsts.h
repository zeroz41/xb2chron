#ifndef CLASSES_GMK_GMKENEMYINSTS_H
#define CLASSES_GMK_GMKENEMYINSTS_H

#include "classes/gmk/ScenarioFlagCond.h"
#include "classes/gmk/QuestFlagCond.h"
#include "classes/gmk/TimeCond.h"
#include "classes/gmk/WeatherCond.h"
#include "classes/gmk/CloudCond.h"

class CBdatWrapper;
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
        class PopEnemyInfo;
        unsigned int getGobInstNum() const;  // how many objects pop
        unsigned char pad_0[0x8];  // fields: size unknown
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
        unsigned char pad_16[0x2];
        TimeCond m_popTime;                 // 0x18: "POP_TIME"
        WeatherCond m_popWeather;           // 0x28: "popWeather"
        CloudCond m_popCloud;               // 0x38: "flag" bit "popCloud"
        QuestFlagCond m_mutekiQuestFlag;    // 0x48: "muteki_QuestFlag"/Min/Max
        unsigned char pad_4c[0x14];         // fields: size from PopInfo's offset
    };
    gf::GF_OBJ_HANDLE* getGobInst(unsigned int index) const;  // the handle of one of them
    // pops the gimmick's objects now (GfSmnEnemyManager::execAbsSummon)
    void reqForcePopGobInst(const ForcePopEnemyInfo& info) const;
    unsigned char pad_0[0x1c];
    // the distances its objects pop within and depop beyond (GfRelSmnEnemy::create squares them; the names are not
    // the original's)
    float m_popDist;
    float m_depopDist;
    unsigned char pad_24[0x14];
    BdatInfo m_bdatInfo;  // 0x38 (the name is not the original's)
    PopInfo m_popInfo;  // (the name is not the original's)
    // fields (its destructor 0x71005D85E8 touches +0x150, +0x178); size 0x190: GmkEnemy (insts at 0x48) and
    // GmkRoutedEnemy (insts at 0x50) getInst strides 0x1d8 and 0x200
    unsigned char pad_a0[0xf0];
};
}  // namespace gmk

#endif

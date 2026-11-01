#ifndef CLASSES_GF_GFGAMECOND_H
#define CLASSES_GF_GFGAMECOND_H

#include "classes/mm/mtl/PtrSingleton.h"
#include "mm/mtl/FixedArray.h"

namespace gf { class GfGameCond; class GfSetupParam; enum CLOUD_SEA : int; }

namespace gf {
// table 0x7100B54758
class GfGameCond : public ::mm::mtl::PtrSingleton< ::gf::GfGameCond> {
public:
    // what the isGameCond* entry points ask fn_71002A48D4 (0xA bytes on the stack). The type and field names are not
    // the original's.
    struct CondQuery {
        CondQuery(unsigned int condition)
            : m_condition(condition), m_blade(0), m_index(0xFFFF), m_map(0), m_withoutEnv(false) {}
        unsigned short m_condition;  // the FLD_ConditionList row (0: none)
        unsigned short m_blade;      // the blade the idea, achievement and field skill conditions test (0: all)
        unsigned short m_index;      // the only condition slot to test (0xFFFF: all eight)
        unsigned short m_map;        // the map the environment's cloud sea is read for
        bool m_withoutEnv;           // environment conditions hold without a test
    };

    // the constructor, initialize and finalize: 1.0.0 has them out of line; 3.0.1 has no copy left (build and
    // destroy inline them), so they are defined inline in the unit
    GfGameCond(const GfSetupParam& param);
    virtual ~GfGameCond();  // slot 0
    void initialize(const GfSetupParam& param);
    void finalize();
    static void build(const GfSetupParam& param);
    static void destroy();
    static bool isQuest(unsigned int condition);
    static bool isScenario(unsigned int condition);
    // 1.0.0's overload with the time range bits, weather bits and cloud sea; inline in the unit (3.0.1 has no copy)
    static bool isGameEnv(unsigned int condition, unsigned int timeBits, unsigned int weatherBits, CLOUD_SEA cloudSea);
    static bool isGameEnv(unsigned int condition, unsigned int map);
    // whether a flag condition (a ConditionFlag row) holds
    static bool isFlag(unsigned int condition, bool*, bool*);
    // 1.0.0's level and item tests; inline in the unit (3.0.1 has no copy)
    static bool isLevel(unsigned int condition);
    static bool isParty(unsigned int condition, ::mm::mtl::FixedArray<bool, 3>* result);
    static bool isItem(unsigned int condition);
    static bool isIdea(unsigned int condition, unsigned int blade, ::mm::mtl::FixedArray<bool, 5>* result);
    static bool isAchievement(unsigned int condition, unsigned int blade);
    static bool isFieldSkillLevel(unsigned int condition, unsigned int blade);
    // the same, for a map (GfQuestTask::isEnableTaskCondition passes 6 for quest 2020)
    static bool isGameCondWithoutEnv(unsigned int condition);
    // Placeholder name: 1.0.0 has the same function unnamed (fn_7100313CE0, the same five callers, one dropped). A
    // member because its callers are GfGameCond's isGameCond* functions and it calls GfGameCond's tests. What it
    // does: tests the FLD_ConditionList row's eight condition slots by type (scenario, quest, environment, flag,
    // item, party, idea, level, achievement, field skill, a FLD_MapGimmick flag, a named enemy), all of them or
    // (the row's premise set) any of them.
    static bool fn_71002A48D4(const CondQuery& query);
    // whether the game condition (an FLD_ConditionList row) holds
    static bool isGameCond(unsigned int condition);
    static bool isGameCondWithMap(unsigned int condition, unsigned int map);
    static bool isGameCondWithBlade(unsigned int condition, unsigned int blade);
    // whether one of the row's slots before its first empty one is an environment condition
    static bool applyCond(unsigned int condition, unsigned int);
};
}  // namespace gf

#endif

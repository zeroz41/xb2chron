#ifndef CLASSES_GF_GFGAMECOND_H
#define CLASSES_GF_GFGAMECOND_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace gf { class GfGameCond; }

namespace gf {
// table 0x7100B54758
class GfGameCond : public ::mm::mtl::PtrSingleton< ::gf::GfGameCond> {
public:
    virtual ~GfGameCond();  // slot 0
    // whether the game condition (an FLD_ConditionList row) holds
    static bool isGameCond(unsigned int condition);
    // the same, for a map (GfQuestTask::isEnableTaskCondition passes 6 for quest 2020)
    static bool isGameCondWithoutEnv(unsigned int condition);
    static bool isGameCondWithMap(unsigned int condition, unsigned int map);
};
}  // namespace gf

#endif

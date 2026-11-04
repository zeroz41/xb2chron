#ifndef GF_GFDATADRIVERSKILL_H
#define GF_GFDATADRIVERSKILL_H

namespace gf {

// a driver's skill tree (functions, by their symbols; getSkill and getValidSkillNum by 1.0.0's): a skill is found by
// the driver, its kizuna line (0 to 4) and level, and whether it is the new game plus round's
class GfDataDriverSkill {
public:
    static bool getName(unsigned char*& bdat, unsigned int& id, unsigned int skill);  // its name's message
    static bool getEnhanceCaption(unsigned char*& bdat, unsigned int& id, unsigned int skill);
    static unsigned int getSkillFromBdat(unsigned int driver, unsigned int line, unsigned int level, bool round);
    static int getSkillCategoryFromBdat(unsigned int driver, unsigned int line, unsigned int level, bool round);
    static int getSkillPointFromBdat(unsigned int driver, unsigned int line, unsigned int level, bool round);
    static unsigned int getEnhanceFromBdat(unsigned int driver, unsigned int line, unsigned int level, bool round);
    static unsigned int getValidSkillNum(unsigned int driver, bool round);  // how many skills it has learned
    static unsigned int getSkill(unsigned int driver, unsigned int line, unsigned int level, bool round);  // learned
    static bool isSkillLevelUnlock(unsigned int driver, unsigned int level, bool round);
    static unsigned int getSkillLevelUnlockNum(unsigned int driver, unsigned int level, bool round);
    static bool isSkillUnlock(unsigned int driver, unsigned int line, unsigned int level, bool round);
    // the skill point cost of the line's next level (symbols)
    static unsigned int getNextSkillPoint(unsigned int driver, unsigned int line, bool round);
    // 2.0.0's symbols name it. What it does: the 16-bit level of kizuna line `line` (+8 of the line's 10-byte record at
    // +0x30, or +0x62 for the new game plus round) of the driver's row (DLC rows 0x11-0x19 in
    // GfDataManager::getDataGameIra's table, others in getDataGame's); 0 for a DLC driver (row above 6) whose
    // GfBdatChrDr::getChrIrType is set. GfGameUtil::checkDriverSkillLevelUp and execDriverSkillLevelUp test it against
    // 2 and the requested level.
    static unsigned int getSkillLevel(unsigned int driver, unsigned int line, bool round);
    // 2.0.0's symbols name it. What it does: stores the level (low byte) as getSkillLevel's field and, for a level
    // above 0, refreshes the line's skill ids from the "SkillID" columns. Caller: GfGameUtil::execDriverSkillLevelUp
    // after paying the skill points.
    static void setSkillLevel(unsigned int driver, unsigned int line, unsigned int level, bool round);
};

}  // namespace gf

#endif

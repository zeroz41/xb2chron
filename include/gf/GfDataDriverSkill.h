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
    static unsigned short getEnhanceFromBdat(unsigned int driver, unsigned int line, unsigned int level, bool round);
    static unsigned int getValidSkillNum(unsigned int driver, bool round);  // how many skills it has learned
    static unsigned int getSkill(unsigned int driver, unsigned int line, unsigned int level, bool round);  // learned
    static bool isSkillLevelUnlock(unsigned int driver, unsigned int level, bool round);
    static unsigned int getSkillLevelUnlockNum(unsigned int driver, unsigned int level, bool round);
    static bool isSkillUnlock(unsigned int driver, unsigned int line, unsigned int level, bool round);
};

}  // namespace gf

#endif

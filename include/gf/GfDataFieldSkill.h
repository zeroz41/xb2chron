#ifndef GF_GFDATAFIELDSKILL_H
#define GF_GFDATAFIELDSKILL_H

namespace gf {
// the field skills' BDAT data (functions, by its symbols)
class GfDataFieldSkill {
public:
    // a field skill's name: the message table and the id in it; false for none
    static bool getName(unsigned char*& bdat, unsigned int& id, unsigned int skill);
    static bool getCaption(unsigned char*& bdat, unsigned int& id, unsigned int skill);  // (appended by chardata)
    static bool isFieldSkillSettingAccessed(unsigned int skill);  // local flag type 2 bit 1
    static void setFieldSkillSettingAccessed(unsigned int skill);
    static bool isFieldSkillSettingComplete(unsigned int skill);  // local flag type 2 bit 2
    static void setFieldSkillSettingComplete(unsigned int skill);
};
}  // namespace gf

#endif

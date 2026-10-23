#ifndef GF_GFDATABLADESKILL_H
#define GF_GFDATABLADESKILL_H

namespace gf {
class GfDataBladeSkill {
public:
    static bool getName(unsigned char*& bdat, unsigned int& id, unsigned int skill);
    static unsigned int getEnhance(unsigned int skill, unsigned int index);
};
}  // namespace gf

#endif

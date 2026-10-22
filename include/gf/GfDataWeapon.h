#ifndef GF_GFDATAWEAPON_H
#define GF_GFDATAWEAPON_H

namespace gf {

// the weapons' data (functions, by their symbols)
class GfDataWeapon {
public:
    static bool getName(unsigned char*& bdat, unsigned int& id, unsigned int weapon);  // its name's message
    // the weapon a core chip makes of a blade's weapon
    static unsigned int getNewWeapon(unsigned int weapon, unsigned int chip);
    static int getDamage(unsigned int weapon);
    static int getGuardRatio(unsigned int weapon);
    static int getCriticalRatio(unsigned int weapon);
    static int getStability(unsigned int weapon);
    static unsigned int getEnhance(unsigned int weapon);
    // its weapon type's name message; false when it has none
    static bool getWeaponTypeNameByItem(unsigned char*& bdat, unsigned int& id, unsigned int weapon);
};

}  // namespace gf

#endif

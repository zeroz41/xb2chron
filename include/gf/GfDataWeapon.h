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
    // 2.0.0's symbols name them. What they do: 0 unless the row is 0x11-0x13; then they follow the row's linked rows
    // (GfDataDriver::getIraFront) and interpolate two GfBdatItem columns of that row by the driver's level (min + (max
    // - min) * (level - 1) / 98): getDamageForIra the damage (PcWpnIr AtkLv1/AtkLv99), getGuardRatioForIra the guard
    // rate, getCriticalRatioForIra the critical rate, getStabilityForIra the stability (StbLv1/StbLv99) that
    // DataObjDriver::getWeaponDamage / getGuardRate / getCriticalRate / getWeaponStability add for a DLC driver.
    static unsigned int getDamageForIra(unsigned int driver);
    static unsigned int getGuardRatioForIra(unsigned int driver);
    static unsigned int getCriticalRatioForIra(unsigned int driver);
    static unsigned int getStabilityForIra(unsigned int driver);
    static unsigned int getEnhance(unsigned int weapon);
    // its weapon type's name message; false when it has none
    static bool getWeaponTypeNameByItem(unsigned char*& bdat, unsigned int& id, unsigned int weapon);
    // a weapon type's name message; false when it has none
    static bool getWeaponTypeName(unsigned char*& bdat, unsigned int& id, unsigned int wpnType);
    static const char* getModelName(unsigned int weapon);
    static unsigned int getAsmWeaponType(unsigned int weapon);
    static unsigned int getEffWeaponType(unsigned int type);  // 0 and 17 as they are, else GfBdatItem::getPcWpnTypeMotion
};

}  // namespace gf

#endif

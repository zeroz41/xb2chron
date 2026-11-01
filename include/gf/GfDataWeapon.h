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
    // Placeholder names: new in 3.0.1, nothing in 1.0.0's place names them. Static members because they sit in
    // GfDataBlade's unit among GfDataWeapon's functions (between getStability and getEnhance) and take a driver row
    // (no this). What they do: 0 unless the row is 0x11-0x13; then they follow the row's linked rows
    // (GfDataDriver::fn_71002417DC) and interpolate two GfBdatItem columns of that row by the driver's level
    // (min + (max - min) * (level - 1) / 98): fn_710024FB98 the guard rate, fn_710024FCA8 the critical rate
    // DataObjDriver::getGuardRate / getCriticalRate add for a DLC driver.
    static unsigned int fn_710024FB98(unsigned int driver);
    static unsigned int fn_710024FCA8(unsigned int driver);
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

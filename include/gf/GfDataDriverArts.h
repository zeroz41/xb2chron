#ifndef GF_GFDATADRIVERARTS_H
#define GF_GFDATADRIVERARTS_H

namespace gf {

// the drivers' arts' data (functions, by their symbols): GfBdatBtl's ArtsDr table, by an arts id and a level
class GfDataDriverArts {
public:
    static unsigned char* getNameFP();     // the table of the arts' names
    static unsigned char* getCaptionFP();  // the table of the arts' captions
    static unsigned int getNameID(unsigned int arts);
    static unsigned int getCaptionID(unsigned int arts);
    // getIconID and getDebugName tail-call GfBdatBtl::getArtsDrUI and getArtsDrDebugName (BTL_Arts_Dr TalentCap and
    // CondCap, 16-bit columns the callee masks), so they return the callee's unsigned int
    static unsigned int getIconID(unsigned int arts);
    static unsigned int getDebugName(unsigned int arts);
    static unsigned int getEnhance(unsigned int arts, unsigned int level);
    static int getArtsType(unsigned int arts);
    static unsigned int getLevelMax(unsigned int arts);
    // GfBdatBtl::getArtsDrReleaseLv
    static unsigned int getLevelCap(unsigned int arts, unsigned int index);
    static unsigned int getNeedLevelupWp(unsigned int driver, unsigned int arts);
    // 1.0.0's names: 1.0.0's GfMenuArtsAdapter::update_ArtsNumDamage and update_ArtsNumRecast call
    // getDamageMul(arts, level) and getRecast(arts, level) where 3.0.1's call fn_7100249CD4 and fn_7100249D00 (the
    // symbols' names)
    static unsigned int getDamageMul(unsigned int arts, unsigned int level);
    static unsigned int getRecast(unsigned int arts, unsigned int level);
    // (appended by wpntype) 1.0.0's name: the symbols call it fn_71002453B4 (1.0.0's
    // GfMenuWeaponTypeAdapter::update_Arts* call getArtsLevel(driver, arts) at the same sites with the same arguments)
    static unsigned int getArtsLevel(unsigned int driver, unsigned int arts);
    // (appended by wpntype) 1.0.0's name (getWp(unsigned int, unsigned int)): the symbols call it fn_7100249790
    // (1.0.0's update_WpnTypeWP calls getWp at the same site); 3.0.1 added the mode (0, 1 or 2: which weapon point
    // table it reads; update_WpnTypeWP passes 0)
    static int getWp(unsigned int driver, unsigned int wpnType, int mode);
    // 1.0.0's name: the symbols call it fn_71002498F8 (it follows getWp; 1.0.0's DataObjDriver::addWeaponPoint calls
    // addWp at the same site with the same arguments; 3.0.1 added the DLC drivers' records)
    static void addWp(unsigned int driver, unsigned int wpnType, int point);
    static unsigned int getWpnType(unsigned int arts);
    // the symbols' name (its code is in GfDataBlade_710029064C's range; 0 for arts 0 or one outside the table).
    // GfGameArena::fn_7100290D40 (message type 13) and StateArenaEvent test it against 0
    static unsigned int getRangeType(unsigned int arts);
};

}  // namespace gf

#endif

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
    static unsigned short getIconID(unsigned int arts);     // GfBdatBtl::getArtsDrUI
    static unsigned short getDebugName(unsigned int arts);  // GfBdatBtl::getArtsDrDebugName
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
    static unsigned int getWpnType(unsigned int arts);
};

}  // namespace gf

#endif

#ifndef GF_GFDATADRIVERARTS_H
#define GF_GFDATADRIVERARTS_H

#include "mm/mtl/FixedArray.h"

namespace gf {
enum PTPOS : unsigned int;

// the drivers' arts' data (functions, by their symbols): GfBdatBtl's ArtsDr table, by an arts id and a level
class GfDataDriverArts {
public:
    static unsigned char* getNameFP();     // the table of the arts' names
    static unsigned char* getCaptionFP();  // the table of the arts' captions
    static unsigned int getNameID(unsigned int arts);
    static unsigned int getCaptionID(unsigned int arts);
    // 2.0.0's symbols name them (carried as getIconID and getDebugName before). They tail-call
    // GfBdatBtl::getArtsDrTalentCap and getArtsDrCondCap (BTL_Arts_Dr TalentCap and CondCap, 16-bit columns the callee
    // masks), so they return the callee's unsigned int
    static unsigned int getTalentCaptionID(unsigned int arts);
    static unsigned int getCondTalentCaptionID(unsigned int arts);
    static unsigned int getEnhance(unsigned int arts, unsigned int level);
    static int getArtsType(unsigned int arts);
    static unsigned int getLevelMax(unsigned int arts);
    // GfBdatBtl::getArtsDrReleaseLv
    static unsigned int getLevelCap(unsigned int arts, unsigned int index);
    static unsigned int getNeedLevelupWp(unsigned int driver, unsigned int arts);
    // 1.0.0's names: 1.0.0's GfMenuArtsAdapter::update_ArtsNumDamage and update_ArtsNumRecast call
    // getDamageMul(arts, level) and getRecast(arts, level) where 3.0.1's call getDamageMul and getRecast (the
    // symbols' names)
    static unsigned int getDamageMul(unsigned int arts, unsigned int level);
    static unsigned int getRecast(unsigned int arts, unsigned int level);
    // (appended by wpntype) 1.0.0's name: the symbols call it fn_71002453B4 (1.0.0's
    // GfMenuWeaponTypeAdapter::update_Arts* call getArtsLevel(driver, arts) at the same sites with the same arguments)
    static unsigned int getArtsLevel(unsigned int driver, unsigned int arts);
    // (appended by wpntype) 2.0.0's symbols name it (1.0.0's getWp(unsigned int, unsigned int); 1.0.0's
    // update_WpnTypeWP calls getWp at the same site); 3.0.1 added the mode (gf::PTPOS 0, 1 or 2: which weapon point
    // table it reads; update_WpnTypeWP passes 0)
    static int getWp(unsigned int driver, unsigned int wpnType, PTPOS mode);
    // 1.0.0's name: the symbols call it fn_71002498F8 (it follows getWp; 1.0.0's DataObjDriver::addWeaponPoint calls
    // addWp at the same site with the same arguments; 3.0.1 added the DLC drivers' records)
    static void addWp(unsigned int driver, unsigned int wpnType, int point);
    // the symbols name them. getEnableArts: up to 4 ArtsDr rows of the driver and weapon type (not flagged normal;
    // for a DLC driver only those of the mode's IrType), true when any. getSlotArts/setSlotArts: the 3 arts of
    // the driver's weapon type record of the mode (GfDataDriver::getDriverWeaponType and its DLC variants)
    static bool getEnableArts(mm::mtl::FixedArray<unsigned int, 4>& list, unsigned int driver, unsigned int wpnType,
                              PTPOS mode);
    static void getSlotArts(mm::mtl::FixedArray<unsigned int, 3>& list, unsigned int driver, unsigned int wpnType,
                            PTPOS mode);
    static void setSlotArts(unsigned int driver, unsigned int wpnType, const mm::mtl::FixedArray<unsigned int, 3>& list,
                            PTPOS mode);
    static unsigned int getWpnType(unsigned int arts);
};

}  // namespace gf

#endif

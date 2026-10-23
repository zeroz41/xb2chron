#ifndef GF_GFDATAHANA_H
#define GF_GFDATAHANA_H

namespace gf {

// Hana's (the artificial blade's) data (functions, by their symbols)
class GfDataHana {
public:
    static bool isValid(unsigned int blade);  // the blade is Hana (one of her forms)
    static unsigned int getRole(unsigned int hana);  // her role's message (GfDataBdat 0x115), 0 for none
    static int getAttribute(unsigned int hana);
    static unsigned int getAutoHate(unsigned int hana);
    static unsigned int getArtsHate(unsigned int hana);
    static int getEther();
    static int getPartsPower(unsigned int parts);  // the energy a part uses (GfMenuItemAdapter::update_useEnergy)
    static int getPowerCapacity(unsigned int hana);
    static int getEquipPower(unsigned int hana);
    static unsigned int getCondenserNum(unsigned int hana);
    static unsigned int getNartsNum(unsigned int hana);
    static unsigned int getNeedRolePartsEther(unsigned int hana);
    static unsigned int getNeedAttributePartsEther(unsigned int hana);
    static unsigned int getNeedArtsPartsEther(unsigned int hana);
    static unsigned int getNeedNArtsPartsEther(unsigned int hana);
    static unsigned int getNeedCondenserPartsEther(unsigned int hana);
    static unsigned int getDefaultRoleParts(unsigned int hana);
    static unsigned int getDefaultAttributeParts(unsigned int hana);
    static unsigned int getDefaultNArtsParts(unsigned int hana, unsigned int index);
    static unsigned int getDefaultCondenserParts(unsigned int hana, unsigned int index);
    static unsigned int getOpenCircuitEther(unsigned int hana, unsigned int index);
    static void setEther(unsigned int value);
};

}  // namespace gf

#endif

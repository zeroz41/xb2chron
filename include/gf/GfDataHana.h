#ifndef GF_GFDATAHANA_H
#define GF_GFDATAHANA_H

namespace gf {

// Hana's (the artificial blade's) data (functions, by their symbols)
class GfDataHana {
public:
    static bool isValid(unsigned int blade);  // the blade is Hana (one of her forms)
    static unsigned int getRole(unsigned int hana);  // her role's message (GfDataBdat 0x115), 0 for none
    static int getAttribute(unsigned int hana);
    static int getEther();
    static int getPowerCapacity(unsigned int hana);
    static int getEquipPower(unsigned int hana);
};

}  // namespace gf

#endif

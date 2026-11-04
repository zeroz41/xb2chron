#ifndef GF_GFGAMEUTILFIELDENHANCE_H
#define GF_GFGAMEUTILFIELDENHANCE_H


namespace gf {

// the field enhance helpers (functions; 2.0.0's symbols name the class)
class GfGameUtilFieldEnhance {
public:
    // 2.0.0's symbols name it. What they do: the sum of GfBdatBtl::getBTL_EnhanceParam1 over the enhances whose
    // getBTL_EnhanceEnhanceEffect is effect, times 0.01 (0 for driver 0 or none): the driver's own enhances
    // (GfDataDriver::getEquipAcceEnahnce; GfGameUtilFieldEnhance::integrateAccessoriesEffect) or the orb enhances of
    // its blade in slot blade (GfDataDriver::getBlade, GfDataBlade::getEquipOrbEnance;
    // GfGameUtilFieldEnhance::integrateOrbEffect). StateUtil::applyDamage adds both for effect 0x108 to its damage cut.
    static float integrateAccessoriesEffect(unsigned int driver, unsigned short effect);
    static float integrateOrbEffect(unsigned int driver, int blade, unsigned short effect);
};

}  // namespace gf

#endif

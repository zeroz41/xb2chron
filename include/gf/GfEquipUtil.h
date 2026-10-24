#ifndef GF_GFEQUIPUTIL_H
#define GF_GFEQUIPUTIL_H

namespace gf { class SDataDriver; }

namespace gf {
// equipment helpers (functions, by its symbols)
class GfEquipUtil {
public:
    static unsigned int getEquipAcceResult(const SDataDriver& data, unsigned int slot, unsigned int accessory);
    static unsigned int getEquipAcceResult(unsigned int driver, unsigned int slot, unsigned int accessory);
    // equips a weapon chip from the box on a blade
    static void equipBladeChip(unsigned int blade, unsigned int chip);
    static unsigned int getEquipOrbMax(unsigned int blade);
    static unsigned int getEquipBladeOrb(unsigned int blade, unsigned int slot);
};
}  // namespace gf

#endif

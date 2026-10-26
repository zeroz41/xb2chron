#ifndef GF_GFEQUIPUTIL_H
#define GF_GFEQUIPUTIL_H

namespace gf { class SDataDriver; }
namespace gf { struct GfItemHandle; }

namespace gf {
// equipment helpers (functions, by its symbols)
class GfEquipUtil {
public:
    static unsigned int getEquipAcceResult(const SDataDriver& data, unsigned int slot, unsigned int accessory);
    static unsigned int getEquipAcceResult(unsigned int driver, unsigned int slot, unsigned int accessory);
    // equips a weapon chip from the box on a blade
    static void equipBladeChip(unsigned int blade, unsigned int chip);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because it sits between
    // equipBladeChip and getEquipDriverAcce in this unit and, like getEquipDriverAcce, only forwards to
    // GfDataDriver's accessory data. What it does: GfDataDriver::fn_7100247BF0(driver), bit 31 of the driver's
    // third accessory word. Callers: GfMenuObjDrEquip2::SlotListener::reciveEvent and gf_menu_obj_drequip2's
    // fn_71003F1CD8 / fn_71003F20EC.
    static bool fn_71002FC38C(unsigned int driver);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member for the same reason as
    // fn_71002FC38C. What it does: GfDataDriver::fn_7100247B40(driver, flag), setting or clearing that bit.
    // Caller: GfMenuObjDrEquip2::SlotListener::reciveEvent.
    static void fn_71002FC390(unsigned int driver, bool flag);
    // the accessory in a driver's slot
    static unsigned int getEquipDriverAcce(unsigned int driver, unsigned int slot);
    // equips an accessory in a driver's slot (GfGameUtil::execEquipDriverDefaultAcce: slot 0, an empty handle)
    static void equipDriverAcce(unsigned int driver, unsigned int slot, unsigned int accessory, GfItemHandle handle);
    static unsigned int getEquipOrbMax(unsigned int blade);
    static unsigned int getEquipBladeOrb(unsigned int blade, unsigned int slot);
};
}  // namespace gf

#endif

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
    // 2.0.0's symbols name it. What it does: GfDataDriver::isEnableExtendEquipAcce(driver), bit 31 of the driver's
    // third accessory word. Callers: GfMenuObjDrEquip2::SlotListener::reciveEvent and gf_menu_obj_drequip2's
    // refreshExpandOperation / fn_71003F20EC.
    static bool isEnableExtendDriverAcce(unsigned int driver);
    // 2.0.0's symbols name it. What it does: GfDataDriver::setEnableExtendEquipAcce(driver, flag), setting or clearing
    // that bit. Caller: GfMenuObjDrEquip2::SlotListener::reciveEvent.
    static void setEnableExtendDriverAcce(unsigned int driver, bool flag);
    // the accessory in a driver's slot
    static unsigned int getEquipDriverAcce(unsigned int driver, unsigned int slot);
    // equips an accessory in a driver's slot (GfGameUtil::execEquipDriverDefaultAcce: slot 0, an empty handle)
    static void equipDriverAcce(unsigned int driver, unsigned int slot, unsigned int accessory, GfItemHandle handle);
    static unsigned int getEquipOrbMax(unsigned int blade);
    // equips an orb on a blade (GfGameScene::gevBladeActivate empties every slot of blade 1008 so: item 0, each slot
    // index, an empty handle)
    static void equipBladeOrb(unsigned int blade, unsigned int, unsigned int, GfItemHandle);
    static unsigned int getEquipBladeOrb(unsigned int blade, unsigned int slot);
};
}  // namespace gf

#endif

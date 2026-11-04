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
    // refreshExpandOperation / GfMenuObjDrEquip2::updateEquipItemList.
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
    // 2.0.0's symbols name it. A member because it lies among GfItemUtil's
    // functions (its unit). What it does: forwards to getEquipWpnAcce, which for a DLC driver (0x11-0x19) gives the
    // 16-bit item id at +0x5A4 of its row of GfDataManager::getDataGameIra's driver table, else 0.
    // GfMenuItemAdapter::ReferenceDriverEquipConverter shows it as slot 0's accessory of such a driver on menu layer 3.
    static unsigned int getEquipIraWpnAcce(unsigned int driver);
    // 2.0.0's symbols name it. A member because it lies among GfItemUtil's
    // functions right after GfEquipUtil::getEquipIraWpnAcce and takes no object. What it does: puts the item on the driver's DLC
    // accessory slot (GfDataDriver::setEquipWpnAcce / setEquipWpnAcceHandle with the handle), returning the old accessory to
    // the item box (or selling it when the box is full); returns true. GfGameUtil::execEquipIraDefaultWpnAcce and
    // GfMenuObjDrEquip2's removeItem / ItemListListener::reciveEvent call it.
    static bool equipIraWpnAcce(unsigned int driver, unsigned int item, GfItemHandle handle);
};
}  // namespace gf

#endif

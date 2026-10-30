#ifndef CLASSES_GF_GFMENUITEMADAPTER_H
#define CLASSES_GF_GFMENUITEMADAPTER_H

#include "classes/gf/GfMenuAdapter.h"
#include "classes/gf/GfMenuItemList.h"
#include "mm/mtl/Delegate.h"
#include "mm/mtl/IntrusivePtr.h"

namespace fw { class UpdateInfo; }
namespace ui { class UIObjectPlugin; }
namespace gf { class GfMenuItemList; }
namespace gf { class IGfMenuReferenceItem; }

namespace gf {
// a base of gf::GfMenuItemAdapter no evidence names yet
class TUnk_B5CA50 {
public:
    virtual void changeItem(gf::MenuItemInfo const&) = 0;
};
// table 0x7100B5CA20; base at 0x0 GfMenuAdapter (create constructs it as one, then installs this table), base at
// 0x30 unknown (TUnk_B5CA50). An item's display.
class GfMenuItemAdapter : public ::gf::GfMenuAdapter, public TUnk_B5CA50 {
public:
    class IConverter;
    class ListConverter;
    class MissionConverter;  // 1.0.0's (3.0.1 has none; fromMission's type)
    class PouchConverter;    // 1.0.0's (3.0.1 has none; fromPouch's type)
    class PouchReferenceDriverConverter;
    class ReferenceBladeEquipConverter;
    class ReferenceDriverEquipConverter;
    class ReferenceItemConverter;
    // a display callback and the plugin create makes for it (the table at 0x7100B5CA68, in create's type order)
    struct TypeSetup {
        bool (GfMenuItemAdapter::*func)(const MenuItemInfo&);
        GfMenuAdapter::PluginSetup plugin;
    };
    GfMenuItemAdapter(ui::UIObjectPlugin* plugin, bool changed)
        : GfMenuAdapter(plugin, false, changed), m_item(), m_update(), m_converter(nullptr) {}
    virtual ~GfMenuItemAdapter();  // slot 0
    virtual void update(fw::UpdateInfo const&);  // slot 2
    virtual void changeItem(gf::MenuItemInfo const&);  // slot 3
    static GfMenuItemAdapter* create(unsigned int handle, unsigned int type, const MenuItemInfo& item, bool changed);
    // an adapter of the list's item at that index (-1: the selected one's) on the handle's object, kind picking
    // its plugin
    // an adapter that takes its item from the converter (owned) on each update; 3.0.1 inlines it into every caller
    static GfMenuItemAdapter* createFromCoverter(unsigned int handle, unsigned int type, IConverter* converter,
                                                 bool changed);
    static GfMenuItemAdapter* createFromList(unsigned int handle, unsigned int kind, GfMenuItemList* list, int index,
                                             bool changed);
    static GfMenuItemAdapter* createFromReference(unsigned int handle, unsigned int type,
                                                  mm::mtl::IntrusivePtr<IGfMenuReferenceItem> reference, bool changed);
    // the item in a pouch slot of the referenced driver
    static GfMenuItemAdapter* createFromPouchReferenceDriver(unsigned int handle, unsigned int type, unsigned int pouch,
                                                             unsigned int reference, bool changed);
    // the accessory the referenced driver has in a slot (fn_71003432DC in the symbols: 1.0.0's function of this name
    // has the same code, line aside, and builds the same converter)
    static GfMenuItemAdapter* createFromReferenceDriverEquip(unsigned int handle, unsigned int type,
                                                             unsigned int reference, unsigned int slot, bool changed);
    // the aux core (orb) the referenced blade has in a slot
    static GfMenuItemAdapter* createFromReferenceBladeEquip(unsigned int handle, unsigned int type,
                                                            unsigned int reference, unsigned int slot, bool changed);
    bool update_Name(const MenuItemInfo& item);
    bool update_Icon(const MenuItemInfo& item);
    bool update_IconAll(const MenuItemInfo& item);
    bool update_Count(const MenuItemInfo& item);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because it is entry 4 of this
    // class's TypeSetup table (a number plugin 0..999). What it does: shows GfItemUtil::getEnableStock of the
    // item, or 3 for item 0x62D9 on menu layer 3 (GfMenuObjUtil::fn_710048FD30(3)); 0 without an item.
    bool fn_710034220C(const MenuItemInfo& item);
    bool update_Price(const MenuItemInfo& item);
    bool update_SellPrice(const MenuItemInfo& item);
    bool update_RareIcon(const MenuItemInfo& item);
    bool update_EquipableColor(const MenuItemInfo& item);
    bool update_Caption(const MenuItemInfo& item);
    bool update_CategoryIcon(const MenuItemInfo& item);
    bool update_GetAreaText(const MenuItemInfo& item);
    bool update_SubCategoryText(const MenuItemInfo& item);
    bool update_EffectTime(const MenuItemInfo& item);
    bool update_EffectText(const MenuItemInfo& item);
    bool update_useEnergy(const MenuItemInfo& item);
    bool update_needEther(const MenuItemInfo& item);
    bool update_dustEther(const MenuItemInfo& item);
    bool update_PArmor(const MenuItemInfo& item);
    bool update_EArmor(const MenuItemInfo& item);
    bool update_revise(const MenuItemInfo& item);
    bool update_dispRevise(const MenuItemInfo& item);
    bool update_roleText(const MenuItemInfo& item);
    bool update_canStack(const MenuItemInfo& item);
    // Placeholder name: the symbols call 0x7100342FA8 createFromCoverter, but it is entry 24 of this class's
    // TypeSetup table (an image plugin) and reads the item like the callbacks before it, so the symbol is not its
    // name. What it does: on menu layer 3, for a type 2 item, the icon of GfBdatItem's fn_7100202C3C(item) + 0x9E.
    bool fn_7100342FA8(const MenuItemInfo& item);

    // the field names are not the original's: the item it shows (create's; update takes the converter's through
    // changeItem), the callback create picks and where update takes the item from (owned)
    MenuItemInfo m_item;
    mm::mtl::Delegate<bool(const MenuItemInfo&)> m_update;
    IConverter* m_converter;
    // which of several adapters of one kind it is (GfMenuObjItemList2::setupItemList numbers its two kind 0xB
    // and three kind 0xE adapters from 0; the name is not the original's)
    unsigned int m_subIndex;
    unsigned char pad_74[0x4];
};
}  // namespace gf

#endif

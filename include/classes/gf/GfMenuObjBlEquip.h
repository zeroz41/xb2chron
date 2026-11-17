#ifndef CLASSES_GF_GFMENUOBJBLEQUIP_H
#define CLASSES_GF_GFMENUOBJBLEQUIP_H

#include "classes/gf/GfMenuObject.h"
#include "gf/GfMenuObjUtil.h"
#include "classes/ui/UIManager.h"
#include "ui/EventData.h"
#include "classes/gf/GfMenuItemList.h"
#include "classes/gf/GfMenuReference.h"
#include "gf/GfEquipUtil.h"

namespace ui {
class UIObjectAcc;
class UISelectObjList;
class UICtrlCursorSelect;
}  // namespace ui

namespace mm { namespace mtl { class ReferenceObject; } }

namespace gf {
class GfMenuCallContext;
class GfMenuItemList;
// table 0x7100B60430; the blade aux core (orb) equipment menu ("LAY_eqpac_slot", "LAY_stockac_list"). Field names
// are not the original's.
class GfMenuObjBlEquip : public ::gf::GfMenuObject {
public:
    class ItemSelectListener;
    class MainListener;
    class SlotListener;
    GfMenuObjBlEquip(unsigned int handle);
    virtual ~GfMenuObjBlEquip();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4

    // 1.0.0's out-of-line helpers (0x7100412E6C, 0x7100412EA8, 0x7100412EEC); 3.0.1 inlines them all
    static int setFadeIn(unsigned int handle) {
        int ctrl = GfMenuObjUtil::setCommonFadeIn(handle, 1, 1);
        GfMenuObject::hookCtrlEvent(handle, ctrl);
        return ctrl;
    }
    static void sendEvent(unsigned int handle, unsigned int type, unsigned int param) {
        ui::EventData event;
        event.m_type = type;
        event.m_param0 = param;
        ui::UIManager::get()->requestObjectEvent(handle, event, 0.0f);
    }
    static int setFadeOut(unsigned int handle) {
        int ctrl = GfMenuObjUtil::setCommonFadeOut(handle, 2, 1);
        GfMenuObject::hookCtrlEvent(handle, ctrl);
        return ctrl;
    }
    // 1.0.0's out-of-line updateEquipItemList (0x7100414068, the same code); 3.0.1 inlines it: the reference
    // blade's equipped orbs, one entry per slot (an empty slot has count 0)
    static void updateEquipItemList(GfMenuItemList* items) {
        unsigned int blade = GfMenuReference::getReferenceBladeID(0);
        unsigned int max = GfEquipUtil::getEquipOrbMax(blade);
        items->clear();
        for (unsigned int i = 0; i < max; i++) {
            MenuItemInfo info;
            info.m_type = 3;
            info.m_id = GfEquipUtil::getEquipBladeOrb(blade, i);
            info.m_count = info.m_id != 0;
            items->addContents(info);
        }
    }
    // 1.0.0's out-of-line removeItem (0x7100413F84, no callers left); 3.0.1 inlines it: takes the orb out of the
    // reference blade's slot, empties the slot's entry and refreshes the item list (the context goes unused)
    static bool removeItem(ui::UIObjectAcc& acc, GfMenuItemList* items, GfMenuItemList* items2,
                           ui::UISelectObjList* select, unsigned int blade, unsigned int slot, GfMenuCallContext*) {
        GfEquipUtil::equipBladeOrb(blade, 0, slot, GfItemHandle());
        if (items != nullptr && slot < items->m_list.size()) {
            MenuItemInfo& info = items->m_list[slot];
            info.m_type = 3;
            info.m_id = 0;
            info.m_count = 0;
            info.m_entry = GfItemHandle();
        }
        refreshItemList(acc, items2, select, slot);
        return true;
    }
    static void setupSlot(ui::UIObjectAcc& acc, GfMenuItemList* items);
    static void refreshSlot(ui::UIObjectAcc& acc);
    static void refreshItemList(ui::UIObjectAcc& acc, GfMenuItemList* items, ui::UISelectObjList* select,
                                unsigned int index);
    static void setupItemList(ui::UIObjectAcc& acc, GfMenuItemList* items, ui::UISelectObjList* select);
    static void sortOrb(GfMenuItemList* items, unsigned short type);

    GfMenuItemList* m_items;  // 0x28: initialize creates it and sets it up for pages of 3 rows
    ui::UICtrlCursorSelect* m_cursor;  // 0x30: the slots' cursor (SlotListener's event 1 creates it); the destructor releases it
    GfMenuItemList* m_items2;  // 0x38: initialize creates it
    ui::UISelectObjList* m_selectList;  // 0x40: initialize creates it
    GfMenuCallContext* m_context2;  // 0x48: initialize creates it
    int pad_50;
    int pad_54;
    GfMenuCallContext* m_context;  // 0x58: the constructor creates it
    int pad_60;  // the constructor clears it
};
}  // namespace gf

#endif

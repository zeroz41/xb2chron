#ifndef CLASSES_GF_GFMENUOBJDREQUIP2_H
#define CLASSES_GF_GFMENUOBJDREQUIP2_H

#include "classes/gf/GfMenuObject.h"
#include "classes/gf/GfMenuReferenceItem.h"
#include "mm/mtl/IntrusivePtr.h"

namespace ui {
class UIObjectAcc;
class UISelectObjList;
}  // namespace ui

namespace gf {
class GfMenuCallContext;
class GfMenuDriverList;
class GfMenuItemAdapter;
class GfMenuItemList;
// table 0x7100B61A60; the driver equipment menu. Field names are not the original's.
class GfMenuObjDrEquip2 : public ::gf::GfMenuObject {
public:
    class EquipItemListener;
    class ItemListListener;
    class MainListener;
    class SlotListener;
    GfMenuObjDrEquip2(unsigned int handle);
    virtual ~GfMenuObjDrEquip2();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4

    // 2.0.0's symbols name it. What it does: enables action 10 of the operation guide on "LAY_equip_slot"
    // (GfMenuObjOperationInfo::setActionEnable) when the game is cleared, the reference driver m_driver's
    // GfEquipUtil::isEnableExtendDriverAcce does not hold and the party has item 0x636A.
    void refreshExpandOperation();
    // 1.0.0's setupEquipItem (0x71004569D8: same place after EquipItemListener::reciveEvent, the same arguments
    // and its first three createFromList calls); 2.0.0's symbols name it
    // (returns nothing: its no-element path leaves the search result in w0)
    static void setupEquipItem(ui::UIObjectAcc& acc, GfMenuItemList* items);
    // 2.0.0's symbols name it (not written yet): refills the list for a reference driver
    // (GfMenuReference::getReferenceDriverID; SlotListener::reciveEvent and setupSlot call it)
    static void updateEquipItemList(GfMenuItemList* items, unsigned int);
    // 2.0.0's symbols name these
    static void setupSlot(ui::UIObjectAcc& acc, GfMenuItemList* items, unsigned int);
    static void refreshEquipItemSlot(unsigned int, GfMenuItemList* items);
    static void refreshItemList(ui::UIObjectAcc& acc, GfMenuItemList* items, ui::UISelectObjList* selectList,
                                GfMenuDriverList* drivers, unsigned int, unsigned int);
    static bool removeItem(ui::UIObjectAcc& acc, GfMenuItemList* equipItems, GfMenuItemList* items,
                           ui::UISelectObjList* selectList, GfMenuDriverList* drivers, unsigned int, unsigned int,
                           unsigned int, GfMenuCallContext* context);
    static void setupItemList(ui::UIObjectAcc& acc, GfMenuItemList* items, ui::UISelectObjList* selectList);

    // 0x24: the reference driver index (GfMenuReference::getReferenceDriverID); the constructor and initialize
    // clear it
    unsigned int m_driver;
    bool pad_28;
    GfMenuItemList* m_items;  // 0x30: initialize creates it and sets it up for pages of 3 rows
    mm::mtl::ReferenceObject* m_object;  // 0x38: the destructor releases it (its type is not read yet)
    GfMenuItemList* m_items2;  // 0x40: initialize creates it
    ui::UISelectObjList* m_selectList;  // 0x48: initialize creates it
    mm::mtl::ReferenceObject* m_object2;  // 0x50: the destructor releases it (its type is not read yet)
    mm::mtl::IntrusivePtr<GfMenuReferenceItem> m_refItem;  // 0x58: initialize creates it
    GfMenuCallContext* m_context2;  // 0x60: initialize creates it
    GfMenuDriverList* m_drivers;  // 0x68: initialize creates it (setupFromParty, type 2)
    GfMenuCallContext* m_context;  // 0x70: the constructor creates it
    int pad_78;
    int pad_7C;  // the constructor clears it; ItemListListener stores it
    int pad_80;
    int pad_84;  // the constructor clears it
};
}  // namespace gf

#endif

#ifndef CLASSES_GF_GFMENUOBJBLWEAPON2_H
#define CLASSES_GF_GFMENUOBJBLWEAPON2_H

#include "classes/gf/GfMenuObject.h"
#include "classes/gf/GfMenuReferenceNumber.h"
#include "classes/gf/GfMenuWeaponAdapter.h"
#include "gf/GfMenuSequence.h"
#include "mm/mtl/IntrusivePtr.h"
#include "classes/ui/UIManager.h"
#include "ui/EventData.h"

namespace ui {
class UIObjectAcc;
class UISelectObjList;
}  // namespace ui

namespace gf {
class GfMenuBladeList;
class GfMenuCallContext;
class GfMenuItemList;
// table 0x7100B60608; the blade weapon (core chip) menu. Field names are not the original's.
class GfMenuObjBlWeapon2 : public ::gf::GfMenuObject {
public:
    class ChrChangeListener;
    class ItemSelectListener;
    class MainListener;
    class WeaponListener;
    GfMenuObjBlWeapon2(unsigned int handle);
    virtual ~GfMenuObjBlWeapon2();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4

    // binds the blade weapon menu to that call context; false while it cannot yet (GfMenuObjShop::
    // seqWaitLoadBlWeapon retries it each update after resetting the context)
    static bool attach(GfMenuCallContext* context);
    // opens the menu from a shop: its full-screen layer parameter carries the open type 1 and the shop
    static void openForShop(unsigned int shop);
    // 1.0.0's helper (0x710041CEF8), inlined into its callers in 3.0.1: an event of that type and first parameter
    // to the object of that handle
    static void sendEvent(unsigned int handle, unsigned int type, unsigned int param) {
        ui::EventData event;
        event.m_param0 = param;
        event.m_type = type;
        ui::UIManager::get()->requestObjectEvent(handle, event, 0.0f);
    }
    void setupItemList(ui::UIObjectAcc& acc, GfMenuItemList* items, ui::UISelectObjList* select, unsigned int,
                       unsigned int);
    void setupWeapon(ui::UIObjectAcc& acc, GfMenuItemList* items, GfMenuWeaponAdapter::ReferenceChip& chip);
    void openCharChange();
    void closeCharChange();
    bool seqStart();
    bool seqSrcLeave();
    bool seqEnd();
    bool seqSrcAppear();
    bool seqSrcEffect();
    bool seqDstResume();

    GfMenuItemList* m_items;                         // the chips listed (initialize creates it)
    ui::UISelectObjList* m_select;                   // the list's selection (initialize creates it)
    mm::mtl::IntrusivePtr<GfMenuReferenceNumber> m_chip;  // the chip shown (its value is the chip's item id)
    GfMenuCallContext* m_charContext;                // initialize creates it
    unsigned char pad_48[8];
    GfMenuCallContext* m_context;                    // the constructor creates it
    GfMenuSequence<GfMenuObjBlWeapon2, 8> m_seq;
    bool m_seqStep;                                  // the running seq* job has started its step
    unsigned int pad_2EC;
    unsigned int m_openType;                         // the full-screen layer parameter's low half: 1 from a shop
    unsigned int m_shop;                             // its high half: openForShop's shop
    GfMenuBladeList* m_blades;                       // initialize creates it
    bool pad_300;
    unsigned int pad_304;
};
}  // namespace gf

#endif

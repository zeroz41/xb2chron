#ifndef CLASSES_GF_GFMENUOBJDRARTSSET2_H
#define CLASSES_GF_GFMENUOBJDRARTSSET2_H

#include "classes/gf/GfMenuObject.h"
#include "classes/gf/GfMenuReferenceNumber.h"
#include "gf/GfMenuSequence.h"
#include "mm/mtl/FixedVector.h"
#include "mm/mtl/IntrusivePtr.h"
#include "classes/ui/UIManager.h"
#include "ui/EventData.h"

namespace ui {
class UIObjectAcc;
}  // namespace ui

namespace gf {
class GfMenuArtsList;
class GfMenuBladeList;
class GfMenuCallContext;
class GfMenuItemList;
// table 0x7100B61978; the driver arts menu. Field names are not the original's.
class GfMenuObjDrArtsSet2 : public ::gf::GfMenuObject {
public:
    class ArtsListListener;
    class LevelupListener;
    class MainListener;
    class WpnTypeListener;
    GfMenuObjDrArtsSet2(unsigned int handle);
    virtual ~GfMenuObjDrArtsSet2();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4

    // 1.0.0's helper (0x710044BBD4), inlined into its callers in 3.0.1: an event of that type and first parameter
    // to the object of that handle
    static void sendEvent(unsigned int handle, unsigned int type, unsigned int param) {
        ui::EventData event;
        event.m_param0 = param;
        event.m_type = type;
        ui::UIManager::get()->requestObjectEvent(handle, event, 0.0f);
    }

    void setupWpnType(ui::UIObjectAcc& acc, mm::mtl::IntrusivePtr<GfMenuReferenceNumber> number, GfMenuArtsList* arts,
                      GfMenuBladeList* blades);
    // 0 when the art can level up, 4 at its highest level (refreshParam, refreshLvUp read it)
    int checkArtsLvUp(unsigned int driver, unsigned int wpnType, GfMenuArtsList* arts, unsigned int index);
    // 1.0.0's checkArtsLvUp(unsigned int, unsigned int, unsigned int, unsigned int) (0x710044EAB4), inlined into its
    // callers in 3.0.1: 4 for no art or one at its highest level, 5 when the weapon type's points are short of the
    // level-up cost, 0 when it can level up
    static int checkArtsLvUp(unsigned int driver, unsigned int wpnType, unsigned int arts, unsigned int level);
    // 1.0.0's refreshLvUp (0x710044B7D0: the same calls, string and arguments); 2.0.0's symbols name it
    void refreshLvUp(ui::UIObjectAcc& acc, unsigned int driver, unsigned int wpnType, GfMenuArtsList* arts);
    void setupWpnTypeIcon(ui::UIObjectAcc& acc, mm::mtl::FixedVector<unsigned int, 50>& wpnTypes,
                          GfMenuBladeList* blades);
    void refreshLvUpWpn(ui::UIObjectAcc& acc, unsigned int driver, const mm::mtl::FixedVector<unsigned int, 50>& wpnTypes);
    void setupArtsList(ui::UIObjectAcc& acc, GfMenuArtsList* arts, mm::mtl::IntrusivePtr<GfMenuReferenceNumber> number,
                       mm::mtl::IntrusivePtr<GfMenuReferenceNumber> number2);
    void refreshArtsSelect(ui::UIObjectAcc& acc, int index, int prev);
    void refreshLvCap(ui::UIObjectAcc& acc, unsigned int driver, unsigned int wpnType, GfMenuArtsList* arts,
                      unsigned int index);
    void refreshArtsNeedWP(ui::UIObjectAcc& acc, GfMenuArtsList* arts, unsigned int driver, unsigned int wpnType);
    void refreshParam(ui::UIObjectAcc& acc, unsigned int driver, unsigned int wpnType, GfMenuArtsList* arts,
                      unsigned int index);
    // 2.0.0's symbols name it. What it does: when layer 3 is usable (GfMenuObjUtil::isValidExpansion(3)), sets
    // "LAY_arts"' operation info: actions 12 (index < 3 on the arts list), 9 (items to use), 10 and 11 enabled only
    // while pad_12C is -1, action 1 while pad_2BA is clear, text 2 swapped and "LAY_list_index_btn" half transparent
    // otherwise.
    void updateArtsInputIra();
    // 2.0.0's symbols name it. What it does: counts the enabled arts (GfMenuObjUtil::getEnableArts, at least 3) of the
    // driver of reference s_RefDriverIndex and the weapon type in m_number; without the flag sets "LAY_arts"' input
    // selection to the index over that count and opens the character change (GfMenuObjMainMenu2::openCharChange with
    // pad_2B8); with it closes the character change, first setting the selection over one fewer when pad_2B4 or pad_2B9
    // is set.
    void updateArtsSwapSelectIra(int index, bool close);
    bool seqSelectItem();
    bool seqConfirmItem();
    bool seqReturnWeaponSelect();
    // 2.0.0's symbols name it. What it does: sends event 0x101 to "LAY_arts"; returns true.
    bool seqReturnArtsSelect();

    // 2.0.0's symbols name them. The constructor clears the first and sets the second to isActiveBCHWpn's answer while
    // the game is cleared, layer 3 is not usable and layer 1 is.
    static unsigned int s_RefDriverIndex;
    static bool s_EnableWpn2;

    mm::mtl::FixedVector<unsigned int, 50> m_wpnTypes;  // 0x28
    mm::mtl::IntrusivePtr<GfMenuReferenceNumber> m_number;  // 0xF8: initialize creates it
    mm::mtl::IntrusivePtr<GfMenuReferenceNumber> m_number2;  // 0x100: initialize creates it
    unsigned char pad_108[8];
    mm::mtl::ReferenceObject* m_object;  // 0x110: the destructor releases it (its type is not read yet)
    GfMenuCallContext* m_context;  // 0x118: initialize creates it (seqSelectItem opens the item select with it)
    GfMenuCallContext* m_context2;  // 0x120: initialize creates it
    int pad_128;  // the constructor sets -1
    int pad_12C;  // the constructor sets -1
    GfMenuArtsList* m_arts;  // 0x130: initialize creates it
    bool pad_138;
    GfMenuBladeList* m_blades;  // 0x140: the constructor creates it
    GfMenuItemList* m_items;  // 0x148: the constructor creates it (initialize adds items 0x633D-0x633F)
    GfMenuSequence<GfMenuObjDrArtsSet2, 4> m_seq;  // 0x150
    bool m_seqStep;  // 0x2B0: the running seq* job has started its step
    // 0x2B4: updateArtsSwapSelectIra passes it as GfMenuObjUtil::getEnableArts' mode
    unsigned int pad_2B4;
    bool pad_2B8;  // updateArtsSwapSelectIra passes it to GfMenuObjMainMenu2::openCharChange as its kind (0 or 1)
    bool pad_2B9;  // updateArtsSwapSelectIra passes it as GfMenuObjUtil::getEnableArts' flag
    bool pad_2BA;  // updateArtsInputIra disables operation 1 while it is set
};

// 2.0.0's symbols name it, a free function (not written yet; its address lies between GfMenuObjDrArtsSet2's
// constructor and destructor). What it does: when layer 1 is usable (GfMenuObjUtil::isValidExpansion(1)), lists driver
// 1's equipped weapon types (GfDataDriver::getEquipWpnType), drops each type but 0x11 whose four enabled arts
// (GfMenuObjUtil::getEnableArts) are all at level 0 and type 0x11 when driver 1's blade (GfDataDriver::getBlade(1, -1))
// is valid, then answers whether type 0x21 is left.
bool isActiveBCHWpn();
}  // namespace gf

#endif

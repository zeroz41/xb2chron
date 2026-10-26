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

    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because the constructor calls it
    // and its address lies between the constructor and the destructor. What it does: when layer 1 is usable
    // (GfMenuObjUtil::fn_710048FD30(1)), lists driver 1's equipped weapon types (GfDataDriver::getEquipWpnType),
    // drops each type but 0x11 whose four enabled arts (GfMenuObjUtil::getEnableArts) are all at level 0 and type
    // 0x11 when driver 1's blade (GfDataDriver::getBlade(1, -1)) is valid, then answers whether type 0x21 is left.
    static bool fn_71003E91EC();
    void setupWpnType(ui::UIObjectAcc& acc, mm::mtl::IntrusivePtr<GfMenuReferenceNumber> number, GfMenuArtsList* arts,
                      GfMenuBladeList* blades);
    // 0 when the art can level up, 4 at its highest level (refreshParam, refreshLvUp read it)
    int checkArtsLvUp(unsigned int driver, unsigned int wpnType, GfMenuArtsList* arts, unsigned int index);
    // 1.0.0's refreshLvUp (0x710044B7D0: the same calls, string and arguments); the symbols spell fn_71003EBC3C
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
    bool seqSelectItem();
    bool seqConfirmItem();
    bool seqReturnWeaponSelect();
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because seqSelectItem queues it
    // as a job of m_seq (in place of seqReturnWeaponSelect while layer 3 is usable). What it does: sends event
    // 0x101 to "LAY_arts"; returns true.
    bool fn_71003F03D8();

    // Proposed names, not the original's: the symbols leave them unnamed (lbl_7100EAB060, lbl_7100EAB064). The
    // constructor clears the first and sets the second to fn_71003E91EC's answer while the game is cleared, layer
    // 3 is not usable and layer 1 is.
    static unsigned int s_wpnTypeIndex;
    static bool s_extraWpnType;

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
    unsigned int pad_2B4;
    unsigned short pad_2B8;
    bool pad_2BA;
};
}  // namespace gf

#endif

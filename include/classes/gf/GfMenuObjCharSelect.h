#ifndef CLASSES_GF_GFMENUOBJCHARSELECT_H
#define CLASSES_GF_GFMENUOBJCHARSELECT_H

#include "classes/gf/GfMenuObject.h"
#include "gf/GfMenuSequence.h"
#include "mm/mtl/FixedArray.h"
#include "mm/mtl/FixedVector.h"
#include "mm/Pnt.h"

namespace gf { class GfMenuCallContext; class GfMenuDriverList; class GfMenuBladeList; class GfMenuItemList; class GAME_VOICE_HANDLE; }
namespace ui { class UIListInfoBase; class UIObjectAcc; struct EventData; }

namespace gf {
// table 0x7100B60F20; the party screen's character select (its object 0x61)
class GfMenuObjCharSelect : public ::gf::GfMenuObject {
public:
    class MainListener;
    class CharBlMoveListener;
    class CharDrListener;
    class CharDrMoveListener;
    class CharDrSoloListener;
    class CharListener;
    class DetailListener;
    class StatusListener;
    class SubMenuListener;
    // a party member as setPartyData fills it: the driver and the blades in its three slots (getEquipBladeNum,
    // setCharOffset; the names are not the original's)
    struct DriverData {
        unsigned int m_driver;
        unsigned int m_blades[3];
    };
    // two indices the code copies as one doubleword (the names are not the original's)
    struct IndexPair {
        int m_first;
        int m_second;
    };

    GfMenuObjCharSelect(unsigned int handle);
    virtual ~GfMenuObjCharSelect();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
    static bool getCharBusy();
    static void returnSubMenu();
    static void execCharPosScale(unsigned int);
    // opens the blade customize menu for a blade over a layer group (GfMenuObjBladeRelease::seqSubMenuOpenCustomize)
    static void openBladeCustomize(unsigned int handle, unsigned int blade, unsigned short layerGroup);
    bool seqConfSpecialWaitError();
    // a special operation's confirmation (pad_748 0-3: Homura/Hikari swap, Nia blade/driver): its common window, then
    // the operation's job, a two-frame wait, seqSpUpdateParty and seqReturnChange (seqReturn when declined)
    bool seqConfSpecial();
    // selects the driver in the list (the first when absent) and shows its blades, status icon and layout
    void refreshCharSelect(unsigned int driver);
    // 1.0.0's names, called where 3.0.1 calls fn_71003D0F84 and fn_71003D0FF8 (GfMenuObjHanaSubmenu's listeners)
    static void dispOnChar(unsigned int);
    static void dispOffChar(unsigned int);
    static bool attach(GfMenuCallContext* context);
    void updateSpecialOperation();
    bool seqWaitSelect();
    bool seqStreamWaitSelect();
    bool seqStreamWaitSelectBefore();
    // the copied driver's (blade 0) or blade's (otherwise) move layout: fades it in or out with the common motion and
    // opens or closes the common status window with it
    static void dispOnCopyChar(ui::UIObjectAcc& acc, unsigned int blade);
    static void dispOffCopyChar(ui::UIObjectAcc& acc, unsigned int blade);
    // places a driver (kind 0, slot 0) or blade (kind 1, slots 1-3) model; solo when the driver has no blade
    // returns the character layout's handle (0 when the slot is out of range or the menu has no object)
    static unsigned int setCharPosScale(unsigned int kind, unsigned int id, unsigned int slot, bool solo);
    // shows the driver's layout with blades or the solo one and lays its status out to match; returns the driver's
    // blade count
    static unsigned int setDriverPos(ui::UIObjectAcc& acc, mm::mtl::FixedArray<DriverData, 5>& drivers, unsigned int driver);
    // moves the driver's (index 0) or a blade's (1-3) layout out for its sub menu: its move layout warps out, its layout
    // fades in, the control slot goes to slots[index]; with all, the others fade out too (the names are inferred)
    static void moveCharSubMenuOut(ui::UIObjectAcc& acc, unsigned int index, mm::mtl::FixedArray<int, 8> slots, bool all);
    static void setCharOffset(ui::UIObjectAcc& acc, const mm::mtl::FixedArray<DriverData, 5>& drivers, unsigned int driver);
    // how many blades the driver has equipped, from the party data setPartyData filled
    static unsigned int getEquipBladeNum(unsigned int driver, const mm::mtl::FixedArray<DriverData, 5>& drivers);
    bool seqStreamWaitStatDr();
    bool seqStreamWaitStatBl();
    bool seqStreamWaitStatDrBefore();
    bool seqStreamWaitStatBlBefore();
    bool seqReturn();
    bool seqReturnChange();
    bool seqSpHomuraToHikari();
    bool seqSpHikariToHomura();
    bool seqSpNiaChangeDr();
    bool seqSpNiaChangeBl();
    // refills the three blade lists with the driver's blades from the party data (none when the driver is not in it)
    static void adjustBladeList(mm::mtl::FixedArray<DriverData, 5>& drivers,
                                mm::mtl::FixedVector<unsigned short, 422>& blades,
                                mm::mtl::FixedArray<GfMenuBladeList*, 3>& lists, unsigned int driver);
    // a sequence job: with special operation 4 (pad_748), opens the item select once (pad_6C0) and waits for it; a
    // picked item selects it in m_itemList and adds seqConfirmItem, otherwise seqReturn
    bool seqConfSpecialSelect();
    bool seqConfirmItem();
    // fills the party data from the list's first five drivers: each valid driver's blades (getBladeFromDriver)
    static void setPartyData(mm::mtl::FixedArray<DriverData, 5>& drivers, GfMenuDriverList* list);
    // rebuilds the driver list (setupFromParty, type 2) keeping the selected driver, then the party data
    bool seqSpUpdateParty();
    // waits for the driver's layout and the three blade images to stream in, then fades LAY_main in (unless pad_768)
    bool seqStreamWait();
    // the sub menu icons: the driver's (five), blade (three) and special (four) menus' BDAT icons, the rest hidden
    // after a party change: refills the party data and blade lists, selects the driver in the list and shows its
    // blades' layouts and status; returns how many valid blades it has
    int refreshDriver(ui::UIObjectAcc acc, unsigned int driver);
    static void setupCharSubMenu(ui::UIObjectAcc& acc, mm::mtl::FixedVector<unsigned int, 5>& drMenus,
                                 mm::mtl::FixedVector<unsigned int, 3>& blMenus,
                                 mm::mtl::FixedVector<unsigned int, 4>& spMenus);

    unsigned char pad_24[4];
    GfMenuDriverList* m_driverList;                        // initialize creates them
    mm::mtl::FixedArray<GfMenuBladeList*, 3> m_bladeLists;
    ui::UIListInfoBase* m_unusedList;  // only the constructor and destructor touch it in 3.0.1 (name not the original's)
    mm::mtl::FixedVector<unsigned short, 422> m_blades;    // the names below are not the original's
    mm::mtl::FixedArray<DriverData, 5> m_drivers;
    int m_driverNum;
    int m_driverNum2;
    mm::mtl::FixedArray<int, 8> m_subMenuPos;
    unsigned char pad_420[8];
    unsigned short pad_428;
    unsigned char pad_42A[6];
    GfMenuSequence<GfMenuObjCharSelect, 8> m_seq;
    bool pad_6C0;
    unsigned char pad_6C1[0x13];
    // the status window's position: StatusListener saves it when the window opens (event 0x105) and puts the window
    // back there on 0x106 (the name is not the original's)
    mm::Pnt<short> m_statusPos;
    int pad_6D8;
    unsigned char pad_6DC[4];
    GfMenuCallContext* m_context;
    int pad_6E8;
    unsigned char pad_6EC[4];
    mm::mtl::FixedVector<unsigned int, 5> m_subMenuDr;
    mm::mtl::FixedVector<unsigned int, 3> m_subMenuBl;
    mm::mtl::FixedVector<unsigned int, 4> m_subMenuSp;
    bool pad_740;
    bool pad_741;
    unsigned short pad_742;
    unsigned int pad_744;
    unsigned int pad_748;
    unsigned char pad_74C[4];
    IndexPair pad_750;
    IndexPair pad_758;
    int pad_760;
    unsigned char pad_764[4];
    bool pad_768;
    GfMenuItemList* m_itemList;
    GfMenuCallContext* m_subContext;
    // the voice seqConfirmItem plays (it stops the last one first; the name is not the original's)
    GAME_VOICE_HANDLE* m_voice;
};
}  // namespace gf

#endif

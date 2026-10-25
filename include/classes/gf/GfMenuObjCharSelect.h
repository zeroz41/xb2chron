#ifndef CLASSES_GF_GFMENUOBJCHARSELECT_H
#define CLASSES_GF_GFMENUOBJCHARSELECT_H

#include "classes/gf/GfMenuObject.h"
#include "gf/GfMenuSequence.h"
#include "mm/mtl/FixedArray.h"
#include "mm/mtl/FixedVector.h"

namespace gf { class GfMenuCallContext; class GfMenuDriverList; class GfMenuBladeList; class GfMenuItemList; }
namespace ui { class UIListInfoBase; class UIObjectAcc; struct EventData; }

namespace gf {
// the flags the character select shares with the status windows (proposed name, not the original's: the symbols
// leave it unnamed, lbl_7100EAA1D8). The constructor clears the first two as one halfword; getCharBusy reads the
// first; 1.0.0's GfMenuObjCmnStatus open/close/swapDrStatus use the second and open/close/swapBlStatus the third
struct CharSelectFlags {
    bool m_charBusy;      // a character move runs (the move listeners clear it when it ends)
    bool m_drStatusOpen;  // the names are not the original's
    bool m_blStatusOpen;
    unsigned char pad_3;
};

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
    // a party member as setPartyData fills it (the layout is not known yet)
    struct DriverData {
        unsigned char pad_0[0x10];
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
    // 1.0.0's names, called where 3.0.1 calls fn_71003D0F84 and fn_71003D0FF8 (GfMenuObjHanaSubmenu's listeners)
    static void dispOnChar(unsigned int);
    static void dispOffChar(unsigned int);
    static bool attach(GfMenuCallContext* context);
    bool seqStreamWaitStatDr();
    bool seqStreamWaitStatBl();
    bool seqStreamWaitStatDrBefore();
    bool seqStreamWaitStatBlBefore();
    bool seqReturn();
    bool seqReturnChange();
    bool seqSpHomuraToHikari();
    bool seqSpHikariToHomura();
    bool seqSpNiaChangeDr();

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
    unsigned char pad_6C1[0x17];
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
    void* pad_780;
};
}  // namespace gf

#endif

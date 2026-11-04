#ifndef CLASSES_GF_TUNK_B61178_H
#define CLASSES_GF_TUNK_B61178_H

#include "classes/gf/GfMenuObject.h"
#include "classes/ui/UIObjectListener.h"
#include "gf/GfMenuSequence.h"
#include "mm/mtl/FixedVector.h"

namespace gf { class GfMenuDriverList; }
namespace ui { class UIListInfoBase; class UISelectObjList; struct EventData; }

namespace gf {
// table 0x7100B61178: the menu object of gf_menu_obj_char_select_ira.cpp (new in 3.0.1, the Torna character select;
// GfMenuObjCharSelect::dispOnChar/dispOffChar call its fn_71003D1670/fn_71003D16C8). Unnamed class
// (TUnk_<table low address>): the symbols leave it unnamed (no RTTI in 3.0.1, nothing in 1.0.0). Its six listeners
// are named the same way after their tables.
class GfMenuObjCharSelectIra : public ::gf::GfMenuObject {
public:
    GfMenuObjCharSelectIra(unsigned int handle);
    virtual ~GfMenuObjCharSelectIra();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4

    // Placeholder names below: new in 3.0.1, nothing in 1.0.0's place names them. Members: their code is in this
    // unit, among the class's own functions.
    // sends LAY_move of the attached object 0x61 its open event (0); caller GfMenuObjCharSelect::dispOnChar
    static void fn_71003D1670();
    // the same with the close event; caller GfMenuObjCharSelect::dispOffChar
    static void fn_71003D16C8();
    // registers full-screen layer 0x12D with a GfMenuTypes::Param whose open type is 1 and changes the handle's
    // full-screen sub layer to it (GfMenuObject::changeFSSubLayer); caller GfMenuObjPartyForm3::DriverSelectListener
    static void openFromBattleBefore(unsigned int handle, unsigned short);
    // returns s_state; caller GfMenuObjDrArtsSet2::MainListener::reciveEvent
    static int getSubMenuMode();
    // sets the driver and blade references for the driver: when GfDataDriver::isIraFront holds, driver 0 and 1
    // are the driver and blade 0 is 0; otherwise driver 0 is GfDataDriver::getIraFront's row and blade 0 the
    // driver's GfDataBlade::fn_7100237B70(driver, -1). Callers: update, updateDriverList, fn_71003D4A64 and others
    static void fn_71003D273C(unsigned int driver);
    // fills m_driverList for the driver (GfGameParty::getPartyId(3, driver), m_partyId when that is -1); keepIndex
    // keeps the list's index
    void updateDriverList(unsigned int driver, bool keepIndex);
    // refills m_ids by m_driverList's size: 3 -> 0, 1, 2 (0, 2, 1 unless GfDataDriver::isIraFront holds for the
    // first driver), 2 -> 0, 1, 1 -> 0; caller updateDriverList
    void updateDriverPosList();
    // scales and centres each LAY_char row's IMG_char_img@/IMG_char_glow@ pair on its slot's layout (sCharFrames, or
    // character_solo on the last row) by GfMenuObjUtil::getImageParam(0, driver, .., 0); caller fn_71003D311C
    void applyImageParam();
    // sets m_driver to the driver, or, when GfDataDriver::isActivateUnuse holds for it, to the first id of
    // getIraBack's list for it for which it does not; m_partyId to GfDataParty::getDriverPartyID of it
    // puts the driver alone in m_driverList2 and IMG_char_move_img into LAY_move's "character" layout, scaled and
    // moved by GfMenuObjUtil::getImageParam(0, driver, .., 4); caller TUnk_B612A0::reciveEvent
    // shows the sub menu's title and description (s_state 1: driver texts of BDAT 0x182, else blade texts of 0x184)
    // for m_list580's row at the index; caller TUnk_B61278::reciveEvent
    void refreshSubMenu(int index);
    // takes one of m_ids (seqChangeDriverList); not written yet (0x7C4 bytes: LAY_char rows and controls)
    void fn_71003D311C(unsigned int);
    void updateDispDriver(unsigned int driver);
    void updateTopDriver(unsigned int driver);
    // for the blade's driver (getIraDriver, GfDataDriver::fn_71002418CC): refills the list when m_driver changes,
    // then selects the blade's row in m_driverList
    void changeBlade(unsigned int blade);
    // stops the control on each m_selectList object and updates its layout size, then the size of each
    // LAY_char@%02d row of pad_578's count; caller TUnk_B61200::reciveEvent
    void resetObjControl();
    // hands the full-screen input over to LAY_char (GfMenuObjMainMenu2::openCharChange 3) and sets its operation
    // info; caller TUnk_B61200::reciveEvent
    void startCharSelect();
    // m_seq jobs (they return true when done)
    // done once no IMG_char_img@%02d%02d (rows but the last, three each) or IMG_char_img@%02d (last row) of LAY_main
    // is streaming
    bool seqWaitStreaming();
    // sends LAY_char its open event (0)
    bool seqOpenCharSelectByInit();
    // done once m_req is -1 or GfReqManager::isValid(m_req)
    bool seqWaitRequest();
    // when LAY_char runs no control: refills the list for m_driver keeping its index, sends LAY_char open event 2
    // selects the list's driver again (updateDriverList), releases m_ctrl and m_ctrl2's controls, then refreshes the
    // rows for the selected one of m_ids (fn_71003D311C)
    bool seqChangeDriverList();
    bool seqOpenCharSelectByFormChange();
    // the same without keeping the index, open event 1
    bool seqOpenCharSelect();
    // done once IMG_char_move_img is no longer streaming
    bool seqWaitStreamingDriver();
    // runs a fade-in control of half preset 6's time on LAY_move
    bool seqOpenDriver();

    // the screen's mode (0, 1, 2): the destructor clears it, a listener sets it. Proposed name, not the original's:
    // the symbols leave it unnamed (lbl_7100EAA1DC); this unit's code reaches it through the GOT, so it is not a
    // file static
    static int s_state;

    // the names below are not the original's
    unsigned char pad_24[4];
    GfMenuDriverList* m_driverList;             // the constructor creates it
    ui::UISelectObjList* m_selectList;           // the constructor creates it
    mm::mtl::FixedVector<unsigned int, 3> m_ids;  // updateDriverPosList fills it from m_driverList's size
    unsigned int m_driver;                       // updateDriverList's driver
    int m_partyId;                               // updateDriverList's party id when GfGameParty has none
    GfMenuSequence<GfMenuObjCharSelectIra, 8> m_seq;
    GfMenuSequence<GfMenuObjCharSelectIra, 8> m_seq2;
    int pad_578;  // how many LAY_char@%02d rows resetObjControl updates
    int pad_57C;
    mm::mtl::FixedVector<unsigned int, 8> m_list580;
    ui::UISelectObjList* m_selectList2;          // the constructor creates it
    ui::UIListInfoBase* m_unusedList;            // only the constructor and destructor touch it
    GfMenuDriverList* m_driverList2;              // the constructor creates and sets it up
    unsigned int m_shownDriver;  // the driver update last set the references for (s_state 1: driver 0, 2: blade 0's)
    int pad_5C4;
    mm::mtl::FixedVector<unsigned int, 16> m_unused5C8;  // only the constructor and destructor touch it (element type unknown)
    int m_ctrl;                                  // control slots seqChangeDriverList releases
    int m_ctrl2;
    int m_req;                                   // a GfReqManager request, -1 for none
    bool pad_61C;
};

// table 0x7100B611D8: a listener of GfMenuObjCharSelectIra (nothing names the class); its reciveEvent is fn_71003D4A64
class TUnk_B611D8 : public ::ui::UIObjectListener {
public:
    // its code zeroes 0xC-0x1B after storing its table: its own fields, as other menus' listeners use theirs
    TUnk_B611D8(GfMenuObjCharSelectIra* owner) : pad_0C(), m_owner(owner) {}
    virtual ~TUnk_B611D8() {}  // slot 0: its D1 slot is the base's destructor
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
    unsigned char pad_0C[0x10];
    GfMenuObjCharSelectIra* m_owner;  // what initialize makes it for
};

// table 0x7100B61200: a listener of GfMenuObjCharSelectIra (nothing names the class); its reciveEvent is fn_71003D4B70
class TUnk_B61200 : public ::ui::UIObjectListener {
public:
    // its code zeroes 0xC-0x1B after storing its table: its own fields, as other menus' listeners use theirs
    TUnk_B61200(GfMenuObjCharSelectIra* owner) : pad_0C(), m_owner(owner) {}
    virtual ~TUnk_B61200() {}  // slot 0: its D1 slot is the base's destructor
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
    unsigned char pad_0C[0x10];
    GfMenuObjCharSelectIra* m_owner;  // what initialize makes it for
};

// table 0x7100B61228: a listener of GfMenuObjCharSelectIra (nothing names the class); its reciveEvent is fn_71003D5CBC
class TUnk_B61228 : public ::ui::UIObjectListener {
public:
    // its code zeroes 0xC-0x1B after storing its table: its own fields, as other menus' listeners use theirs
    TUnk_B61228(GfMenuObjCharSelectIra* owner) : pad_0C(), m_owner(owner) {}
    virtual ~TUnk_B61228() {}  // slot 0: its D1 slot is the base's destructor
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
    unsigned char pad_0C[0x10];
    GfMenuObjCharSelectIra* m_owner;  // what initialize makes it for
};

// table 0x7100B61250: a listener of GfMenuObjCharSelectIra (nothing names the class); its reciveEvent is fn_71003D5D94
class TUnk_B61250 : public ::ui::UIObjectListener {
public:
    // its code zeroes 0xC-0x1B after storing its table: its own fields, as other menus' listeners use theirs
    TUnk_B61250(GfMenuObjCharSelectIra* owner) : pad_0C(), m_owner(owner) {}
    virtual ~TUnk_B61250() {}  // slot 0: its D1 slot is the base's destructor
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
    unsigned char pad_0C[0x10];
    GfMenuObjCharSelectIra* m_owner;  // what initialize makes it for
};

// table 0x7100B61278: a listener of GfMenuObjCharSelectIra (nothing names the class); its reciveEvent is fn_71003D6068
class TUnk_B61278 : public ::ui::UIObjectListener {
public:
    // its code zeroes 0xC-0x1B after storing its table: its own fields, as other menus' listeners use theirs
    TUnk_B61278(GfMenuObjCharSelectIra* owner) : pad_0C(), m_owner(owner) {}
    virtual ~TUnk_B61278() {}  // slot 0: its D1 slot is the base's destructor
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
    unsigned char pad_0C[0x10];
    GfMenuObjCharSelectIra* m_owner;  // what initialize makes it for
};

// table 0x7100B612A0: a listener of GfMenuObjCharSelectIra (nothing names the class); its reciveEvent is fn_71003D6A88
class TUnk_B612A0 : public ::ui::UIObjectListener {
public:
    // its code zeroes 0xC-0x1B after storing its table: its own fields, as other menus' listeners use theirs
    TUnk_B612A0(GfMenuObjCharSelectIra* owner) : pad_0C(), m_owner(owner) {}
    virtual ~TUnk_B612A0() {}  // slot 0: its D1 slot is the base's destructor
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
    unsigned char pad_0C[0x10];
    GfMenuObjCharSelectIra* m_owner;  // what initialize makes it for
};

}  // namespace gf

#endif

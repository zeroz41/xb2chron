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
// GfMenuObjCharSelect::dispOnChar/dispOffChar call its dispOnChar/dispOffChar). 2.0.0's symbols name it and its six
// listeners, nested classes.
class GfMenuObjCharSelectIra : public ::gf::GfMenuObject {
public:
    class MainListener;
    class CharListener;
    class StatusListener;
    class ParamListener;
    class SubMenuListener;
    class CharMoveListener;
    GfMenuObjCharSelectIra(unsigned int handle);
    virtual ~GfMenuObjCharSelectIra();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4

    // 2.0.0's symbols name the functions below. Members: their code is in this unit, among the class's own
    // functions.
    // sends LAY_move of the attached object 0x61 its open event (0); caller GfMenuObjCharSelect::dispOnChar
    static void dispOnChar(unsigned int);
    // the same with the close event; caller GfMenuObjCharSelect::dispOffChar
    static void dispOffChar(unsigned int);
    // registers full-screen layer 0x12D with a GfMenuTypes::Param whose open type is 1 and changes the handle's
    // full-screen sub layer to it (GfMenuObject::changeFSSubLayer); caller GfMenuObjPartyForm3::DriverSelectListener
    static void openFromBattleBefore(unsigned int handle, unsigned short);
    // returns s_SubMenuMode; caller GfMenuObjDrArtsSet2::MainListener::reciveEvent
    static int getSubMenuMode();
    // fills m_driverList for the driver (GfGameParty::getPartyId(3, driver), m_partyId when that is -1); keepIndex
    // keeps the list's index
    void updateDriverList(unsigned int driver, bool keepIndex);
    // refills m_ids by m_driverList's size: 3 -> 0, 1, 2 (0, 2, 1 unless GfDataDriver::isIraFront holds for the
    // first driver), 2 -> 0, 1, 1 -> 0; caller updateDriverList
    void updateDriverPosList();
    // scales and centres each LAY_char row's IMG_char_img@/IMG_char_glow@ pair on its slot's layout (sCharFrames, or
    // character_solo on the last row) by GfMenuObjUtil::getImageParam(0, driver, .., 0); caller refreshCharSelect
    void applyImageParam();
    // sets m_driver to the driver, or, when GfDataDriver::isActivateUnuse holds for it, to the first id of
    // getIraBack's list for it for which it does not; m_partyId to GfDataParty::getDriverPartyID of it
    // puts the driver alone in m_driverList2 and IMG_char_move_img into LAY_move's "character" layout, scaled and
    // moved by GfMenuObjUtil::getImageParam(0, driver, .., 4); caller CharMoveListener::reciveEvent
    // shows the sub menu's title and description (s_SubMenuMode 1: driver texts of BDAT 0x182, else blade texts of 0x184)
    // for m_list580's row at the index; caller SubMenuListener::reciveEvent
    void refreshSubMenu(int index);
    // takes one of m_ids (seqChangeDriverList); not written yet (0x7C4 bytes: LAY_char rows and controls)
    void refreshCharSelect(int);
    void updateDispDriver(unsigned int driver);
    void updateTopDriver(unsigned int driver);
    // for the blade's driver (getIraDriver, GfDataDriver::getIraFromPos): refills the list when m_driver changes,
    // then selects the blade's row in m_driverList
    void changeBlade(unsigned int blade);
    // the form's drivers (up to three, the rest 0) replace the current party's Ira row that holds m_driver; sends it
    // as a party change (m_req) and queues seqWaitRequest, a frame, seqChangeDriverList, seqOpenCharSelectByFormChange
    void applyDriverForm(const mm::mtl::FixedVector<unsigned short, 32>& form);
    // stops the control on each m_selectList object and updates its layout size, then the size of each
    // LAY_char@%02d row of pad_578's count; caller CharListener::reciveEvent
    void resetObjControl();
    // hands the full-screen input over to LAY_char (GfMenuObjMainMenu2::openCharChange 3) and sets its operation
    // info; caller CharListener::reciveEvent
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
    // rows for the selected one of m_ids (refreshCharSelect)
    bool seqChangeDriverList();
    bool seqOpenCharSelectByFormChange();
    // the same without keeping the index, open event 1
    bool seqOpenCharSelect();
    // done once IMG_char_move_img is no longer streaming
    bool seqWaitStreamingDriver();
    // runs a fade-in control of half preset 6's time on LAY_move
    bool seqOpenDriver();

    // the screen's mode (0, 1, 2): the destructor clears it, a listener sets it. 2.0.0's symbols name it
    // (lbl_7100EAA1DC); this unit's code reaches it through the GOT, so it is not a file static
    static int s_SubMenuMode;

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
    unsigned int m_shownDriver;  // the driver update last set the references for (s_SubMenuMode 1: driver 0, 2: blade 0's)
    int pad_5C4;
    mm::mtl::FixedVector<unsigned int, 16> m_unused5C8;  // only the constructor and destructor touch it (element type unknown)
    int m_ctrl;                                  // control slots seqChangeDriverList releases
    int m_ctrl2;
    int m_req;                                   // a GfReqManager request, -1 for none
    bool pad_61C;
};

// table 0x7100B611D8: a listener of GfMenuObjCharSelectIra (2.0.0's symbols name it)
class GfMenuObjCharSelectIra::MainListener : public ::ui::UIObjectListener {
public:
    // its code zeroes 0xC-0x1B after storing its table: its own fields, as other menus' listeners use theirs
    MainListener(GfMenuObjCharSelectIra* owner) : pad_0C(), m_owner(owner) {}
    virtual ~MainListener() {}  // slot 0: its D1 slot is the base's destructor
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
    unsigned char pad_0C[0x10];
    GfMenuObjCharSelectIra* m_owner;  // what initialize makes it for
};

// table 0x7100B61200: a listener of GfMenuObjCharSelectIra (2.0.0's symbols name it)
class GfMenuObjCharSelectIra::CharListener : public ::ui::UIObjectListener {
public:
    // its code zeroes 0xC-0x1B after storing its table: its own fields, as other menus' listeners use theirs
    CharListener(GfMenuObjCharSelectIra* owner) : pad_0C(), m_owner(owner) {}
    virtual ~CharListener() {}  // slot 0: its D1 slot is the base's destructor
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
    unsigned char pad_0C[0x10];
    GfMenuObjCharSelectIra* m_owner;  // what initialize makes it for
};

// table 0x7100B61228: a listener of GfMenuObjCharSelectIra (2.0.0's symbols name it)
class GfMenuObjCharSelectIra::StatusListener : public ::ui::UIObjectListener {
public:
    // its code zeroes 0xC-0x1B after storing its table: its own fields, as other menus' listeners use theirs
    StatusListener(GfMenuObjCharSelectIra* owner) : pad_0C(), m_owner(owner) {}
    virtual ~StatusListener() {}  // slot 0: its D1 slot is the base's destructor
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
    unsigned char pad_0C[0x10];
    GfMenuObjCharSelectIra* m_owner;  // what initialize makes it for
};

// table 0x7100B61250: a listener of GfMenuObjCharSelectIra (2.0.0's symbols name it)
class GfMenuObjCharSelectIra::ParamListener : public ::ui::UIObjectListener {
public:
    // its code zeroes 0xC-0x1B after storing its table: its own fields, as other menus' listeners use theirs
    ParamListener(GfMenuObjCharSelectIra* owner) : m_shown(), m_refresh(), pad_14(), m_owner(owner) {}
    virtual ~ParamListener() {}  // slot 0: its D1 slot is the base's destructor
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
    // the names below are not the original's
    int m_shown;    // 1 while the parameter panel is faded in (events 0x21/0x22)
    int m_refresh;  // 1 until the next fade-in rebuilds IMG_char_param_exp's adapter (event 1 sets it)
    unsigned char pad_14[0x8];
    GfMenuObjCharSelectIra* m_owner;  // what initialize makes it for
};

// table 0x7100B61278: a listener of GfMenuObjCharSelectIra (2.0.0's symbols name it)
class GfMenuObjCharSelectIra::SubMenuListener : public ::ui::UIObjectListener {
public:
    // its code zeroes 0xC-0x1B after storing its table: its own fields, as other menus' listeners use theirs
    SubMenuListener(GfMenuObjCharSelectIra* owner) : pad_0C(), m_owner(owner) {}
    virtual ~SubMenuListener() {}  // slot 0: its D1 slot is the base's destructor
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
    unsigned char pad_0C[0x10];
    GfMenuObjCharSelectIra* m_owner;  // what initialize makes it for
};

// table 0x7100B612A0: a listener of GfMenuObjCharSelectIra (2.0.0's symbols name it)
class GfMenuObjCharSelectIra::CharMoveListener : public ::ui::UIObjectListener {
public:
    // its code zeroes 0xC-0x1B after storing its table: its own fields, as other menus' listeners use theirs
    CharMoveListener(GfMenuObjCharSelectIra* owner) : m_shown(), pad_10(), m_owner(owner) {}
    virtual ~CharMoveListener() {}  // slot 0: its D1 slot is the base's destructor
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
    int m_shown;  // 1 while LAY_move is shown (events 0x21/0x22; the name is not the original's)
    unsigned char pad_10[0xC];
    GfMenuObjCharSelectIra* m_owner;  // what initialize makes it for
};

namespace mnu_chr_sel_ira {
// sets the driver and blade references for the driver: when GfDataDriver::isIraFront holds, driver 0 and 1 are the
// driver and blade 0 is 0; otherwise driver 0 is GfDataDriver::getIraFront's row and blade 0 the driver's
// GfDataDriver::getIraBlade(driver, -1). Callers: GfMenuObjCharSelectIra::update, updateDriverList and its
// listeners. 2.0.0's symbols name it, a free function of this namespace
void setReferenceChar(unsigned int driver);
}  // namespace mnu_chr_sel_ira

}  // namespace gf

#endif

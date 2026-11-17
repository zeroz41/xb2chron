#ifndef CLASSES_GF_GFMENUOBJTITLE_H
#define CLASSES_GF_GFMENUOBJTITLE_H

#include "classes/gf/GfMenuObject.h"
#include "classes/ui/UIObjectListener.h"
#include "gf/GfMenuSequence.h"
#include "mm/mtl/FixedVector.h"
#include "mm/mtl/IntrusivePtr.h"
#include "ui/UIStr.h"

namespace ui { class UISelectObjList; struct EventData; }

namespace gf {
class GfMenuCallContext;
class GfMenuIDList;
class GfMenuMsgList;
class GfMenuReferenceNumber;

// table 0x7100B64D38
class GfMenuObjTitle : public ::gf::GfMenuObject {
public:
    class ListListener;
    // table 0x7100B64DF8 (2.0.0's symbols name it); its reciveEvent (not written yet) queues seqConfirmAdvancedNewGame
    class InfoListener;
    class AnnounceListener;

    GfMenuObjTitle(unsigned int handle);
    // TitleMenu::setupTitle attaches the title menu object to its call context; true when the object is there
    static bool attach(GfMenuCallContext* context);
    virtual ~GfMenuObjTitle();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
    // the title menu's items (TXT_newgame, TXT_continue, TXT_option, TXT_theater, TXT_newgame_adv) show when these
    // answer true
    static bool isEnableNewGame();
    static bool isEnableContinue();
    static bool isEnableOption();
    static bool isEnableEventsTheater();
    static bool isEnableNewGameAdv();
    void moveCursor(unsigned int handle, int index);
    // 2.0.0's symbols name it. What it does: opens common window 0x11B once, then sends event 0x101 to LAY_main
    bool seqAocError();
    // 2.0.0's symbols name them. What they do: seqSelectDifficulity: a job the confirm jobs below queue on a 0 window
    // result (not written yet). seqConfirmNewGame: opens common window 0xE1 once, then on result 0 queues
    // seqSelectDifficulity, else sends event 0x101 to LAY_main; queued by ListListener::reciveEvent.
    // seqConfirmAdvancedNewGame: opens common window 0x116 once, then on result 0 sends LAY_ang_info's close event and
    // queues seqSelectDifficulity, else enables LAY_ang_info's input; queued by InfoListener::reciveEvent.
    // seqTipsDifficulity: opens common window 0x10A once, then hands m_index to LAY_main's call context as the result;
    // queued by seqSelectDifficulity.
    bool seqSelectDifficulity();
    bool seqConfirmNewGame();
    bool seqConfirmAdvancedNewGame();
    bool seqTipsDifficulity();
    // 2.0.0's symbols name them. What they do: updateInfoPage fills m_msgList with page's rows of the add-on info
    // list (bdat 0x16A, 0x16B with add-on 3; its first row is the title, copied to m_str); refreshInfo shows m_str
    // and m_msgList's rows in LAY_ang_info's panes (its parameter is unused); seqInfoFadeOut/seqInfoFadeIn are the
    // m_seq jobs that slide LAY_ang_info_list out (then switch to m_infoPage) and back in
    void updateInfoPage(unsigned int page);
    void refreshInfo(unsigned int page);
    bool seqInfoFadeOut();
    bool seqInfoFadeIn();

    static bool s_NoSaveData;  // initialize: the save data's version is not 0x3A15B

    mm::mtl::FixedVector<unsigned int, 5> m_items;  // 0x28: the shown items' indices into the item table
    int m_index;  // 0x48 (the name is not the original's)
    ui::UISelectObjList* m_list;  // 0x50 (the name is not the original's)
    GfMenuSequence<GfMenuObjTitle, 4> m_seq;  // 0x58
    bool m_confirmOpen;  // 0x1B8: the seq job opened its common window (the name is not the original's)
    GfMenuCallContext* m_callContext;  // 0x1C0
    GfMenuIDList* m_idList;  // 0x1C8 (the name is not the original's)
    ui::UIStr m_str;  // 0x1D0 (the name is not the original's)
    GfMenuMsgList* m_msgList;  // 0x1E8 (the name is not the original's)
    mm::mtl::IntrusivePtr<GfMenuReferenceNumber> m_number;  // 0x1F0 (the name is not the original's)
    mm::mtl::IntrusivePtr<GfMenuReferenceNumber> m_numberMax;  // 0x1F8 (the name is not the original's)
    unsigned int m_infoPage;  // 0x200: the add-on info page seqInfoFadeOut switches to (the name is not the original's)
    int m_infoDir;  // 0x204: 0: the info pages slide right out, left in (the name is not the original's)
    // 0x208: with save data and TitleMain::m_newGameAdv, add-on layer 3 and GfMenuManager::isOnlyIra (the name is not
    // the original's)
    bool m_onlyIra;
    // 0x209: the constructor sets it with add-on layer 3 when GfMenuManager::isOnlyIra answers false (the name is not
    // the original's)
    bool m_iraAddOn;
};
// table 0x7100B64DD0: initialize registers it on LAY_main
class GfMenuObjTitle::ListListener : public ::ui::UIObjectListener {
public:
    // its code zeroes 0xC-0x1B after storing its table, as other menus' listeners do
    ListListener(GfMenuObjTitle* owner) : pad_0C(), m_owner(owner) {}
    virtual ~ListListener() {}  // slot 0
    virtual void reciveEvent(const ui::EventData&, unsigned int);  // slot 2
    unsigned char pad_0C[0x10];
    GfMenuObjTitle* m_owner;  // 0x20: what initialize makes it for
};

// table 0x7100B64DF8: initialize registers it on LAY_ang_info
class GfMenuObjTitle::InfoListener : public ::ui::UIObjectListener {
public:
    InfoListener(GfMenuObjTitle* owner) : m_page(0), m_result(0), pad_14(), m_owner(owner) {}
    virtual ~InfoListener() {}  // slot 0
    virtual void reciveEvent(const ui::EventData&, unsigned int);  // slot 2
    // 0xC: the add-on info page shown (event 8 with 9 / 2 steps it on or back; the name is not the original's)
    int m_page;
    // 0x10: the 0x101 event's parameter it sends LAY_main on close (event 0x21 zeroes it with m_page; the name is
    // not the original's)
    int m_result;
    unsigned char pad_14[8];
    GfMenuObjTitle* m_owner;  // 0x20
};

// table 0x7100B64E20: initialize registers it on LAY_announce when m_onlyIra is set
class GfMenuObjTitle::AnnounceListener : public ::ui::UIObjectListener {
public:
    AnnounceListener(GfMenuObjTitle* owner) : pad_0C(), m_owner(owner) {}
    virtual ~AnnounceListener() {}  // slot 0
    virtual void reciveEvent(const ui::EventData&, unsigned int);  // slot 2
    unsigned char pad_0C[0x10];
    GfMenuObjTitle* m_owner;  // 0x20
};
}  // namespace gf

#endif

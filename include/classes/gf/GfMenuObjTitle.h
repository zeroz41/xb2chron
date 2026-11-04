#ifndef CLASSES_GF_GFMENUOBJTITLE_H
#define CLASSES_GF_GFMENUOBJTITLE_H

#include "classes/gf/GfMenuObject.h"
#include "gf/GfMenuSequence.h"
#include "mm/mtl/FixedVector.h"
#include "mm/mtl/IntrusivePtr.h"
#include "ui/UIStr.h"

namespace ui { class UISelectObjList; }

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
    unsigned char pad_200[0x8];
    // 0x208: with save data and TitleMain::m_newGameAdv, add-on layer 3 and GfMenuManager::isOnlyIra (the name is not
    // the original's)
    bool m_onlyIra;
    // 0x209: the constructor sets it with add-on layer 3 when GfMenuManager::isOnlyIra answers false (the name is not
    // the original's)
    bool m_iraAddOn;
};
}  // namespace gf

#endif

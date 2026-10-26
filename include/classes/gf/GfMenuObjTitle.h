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
    bool seqConfirmNewGame();
    // Placeholder names: new in 3.0.1, nothing in 1.0.0's place names them. Members because they are m_seq jobs of
    // this class (they read m_confirmOpen, m_handle, m_seq). What they do:
    // fn_710048AAD8: a job the confirm jobs below queue on a 0 window result (not written yet).
    // fn_710048AF50: opens common window 0xE1 once, then on result 0 queues fn_710048AAD8, else sends event 0x101
    // to LAY_main; queued by ListListener::reciveEvent.
    // fn_710048B878: opens common window 0x116 once, then on result 0 sends LAY_ang_info's close event and queues
    // fn_710048AAD8, else enables LAY_ang_info's input; queued by fn_710048B048.
    // fn_710048BF38: opens common window 0x10A once, then hands m_index to LAY_main's call context as the result;
    // queued by fn_710048AAD8.
    bool fn_710048AAD8();
    bool fn_710048AF50();
    bool fn_710048B878();
    bool fn_710048BF38();

    static bool s_NoSaveData;  // initialize: the save data's version is not 0x3A15B

    mm::mtl::FixedVector<unsigned int, 5> m_items;  // 0x28: the shown items' indices into the item table
    int m_index;  // 0x48 (the name is not the original's)
    ui::UISelectObjList* m_list;  // 0x50 (the name is not the original's)
    GfMenuSequence<GfMenuObjTitle, 4> m_seq;  // 0x58
    bool m_confirmOpen;  // 0x1B8: seqConfirmNewGame opened its window (the name is not the original's)
    GfMenuCallContext* m_callContext;  // 0x1C0
    GfMenuIDList* m_idList;  // 0x1C8 (the name is not the original's)
    ui::UIStr m_str;  // 0x1D0 (the name is not the original's)
    GfMenuMsgList* m_msgList;  // 0x1E8 (the name is not the original's)
    mm::mtl::IntrusivePtr<GfMenuReferenceNumber> m_number;  // 0x1F0 (the name is not the original's)
    mm::mtl::IntrusivePtr<GfMenuReferenceNumber> m_numberMax;  // 0x1F8 (the name is not the original's)
    unsigned char pad_200[0x8];
    // 0x208: with save data and TitleMain::m_newGameAdv, add-on layer 3 in Japan (the name is not the original's)
    bool m_iraJP;
    // 0x209: the constructor sets it with add-on layer 3 outside Japan (the name is not the original's)
    bool m_iraOverseas;
};
}  // namespace gf

#endif

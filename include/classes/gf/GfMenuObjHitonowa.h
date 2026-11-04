#ifndef CLASSES_GF_TUNK_B62AA0_H
#define CLASSES_GF_TUNK_B62AA0_H

#include "classes/gf/GfMenuObject.h"
#include "classes/ui/UIObjectListener.h"
#include "gf/GfMenuSequence.h"
#include "mm/mtl/FixedVector.h"
#include "mm/mtl/IntrusivePtr.h"

namespace gf { class GAME_VOICE_HANDLE; class GfMenuIDList; class GfMenuReferenceNumber; }
namespace mm { template <typename T> class Pnt; }
namespace ui { class UIObjectAcc; struct EventData; class UISelectObjList; }

namespace gf {
// table 0x7100B62AA0; the "Hitonowa" (circle of people) menu evt_ui openHitonowa opens (gf_menu_obj_hitonowa.cpp).
// Unnamed class (TUnk_<table low address>, counted as debt): the symbols leave it unnamed (no RTTI in 3.0.1, nothing in
// 1.0.0). Its five listeners are named the same way after their tables (registered on LAY_main, LAY_result, LAY_list,
// LAY_image, LAY_bg).
class GfMenuObjHitonowa : public ::gf::GfMenuObject {
public:
    // the listeners initialize registers on its layouts, named after the layout each is registered on (the names are
    // not the original's): TUnk_B62AE8 LAY_main (table 0x7100B62AE8), ConfirmListener LAY_result (0x7100B62B10),
    // TUnk_B62B38 LAY_list (0x7100B62B38), TUnk_B62B60 LAY_image (0x7100B62B60), BgListener LAY_bg (0x7100B62B88)
    class TUnk_B62AE8;
    class ConfirmListener;
    class TUnk_B62B38;
    class TUnk_B62B60;
    class BgListener;

    virtual ~GfMenuObjHitonowa();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4

    // 2.0.0's symbols name it. What it does: registers full-screen layer 0x12F with a GfMenuTypes::Param whose menu is
    // 1. Caller: fn_71004488A0 (gf_menu_obj_* code).
    static void setBootFromEvent();
    // 2.0.0's symbols name it. What it does: clears the stream-image bits of image (resetStreamImageEx), asks
    // fn_710041D2C8 about id, and sets setStreamImage2nd for 1 or setStreamImage3rd's bit for 2. Caller: fn_7100447D88.
    static void setFaceStream(ui::UIObjectAcc& image, unsigned int id);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member: in this unit, called only by
    // setFaceStream. What it does (from its caller): returns 0, 1 or 2 for id, writing an int through value.
    static int fn_710041D2C8(unsigned int id, int* value);
    // 2.0.0's symbols name it. What it does: keeps GfGameManager::getHitonowaLevel() in s_gameValue and passes 0 to
    // GfMenuLocation::startNpcNavigate. Caller: fn_71003597B0.
    static void setupGame();
    // what setupGame keeps of GfGameManager::getHitonowaLevel(). Proposed name, not the original's: the symbols leave
    // it unnamed (lbl_7100EAB87C); this unit's code reaches it through the GOT, so it is not a file static
    static unsigned int s_gameValue;

    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member: its code is in this unit, after
    // finalize. What it does: reads BDAT table 0xA8's row id: "AreaNumber3" when its "Condition2" is set and holds
    // (GfGameCond::isGameCond), else "AreaNumber2" when "Condition1" is set and holds, else "AreaNumber1". Callers:
    // initialize (fn_710041D568) and fn_7100426D60.
    static unsigned int fn_710041E870(unsigned int id);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member: its code is in this unit, after
    // refreshComplete. What it does: places list's objects on a grid of columns columns from origin, each cell
    // width - 14 wide and height - 14 high (setPosCenter).
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member: its code is in this unit and it
    // reads this's lists; called by initialize (fn_710041D568). What it does: unless the list of kind (below 4)
    // already holds an id of the same GfDataBlade::fn_710024DA88 group, adds id with fn_7100255848's (kind 0) or
    // fn_71002557C8's value, sorts the list ascending (sortFromWork) and stores its size in m_refNums[kind].
    void fn_710041E6F8(unsigned char kind, unsigned int id);
    static void fn_710041EE6C(ui::UISelectObjList* list, const mm::Pnt<short>& origin, int width, int height,
                              unsigned int columns);
    // 2.0.0's symbols name it. What it does: shows LAY_level and fades it in (preset 3), then shows TXT_level_num and
    // TXT_level_max, only the latter opaque when s_gameValue is 6.
    void dispLevel();
    // 2.0.0's symbols name refreshComplete; the fn_ names are placeholders. Their code is in this unit and seqNextLost
    // passes this. What they do (not written yet): fn_710041F0A8 sets the list up for an id (its second argument 0
    // there); refreshComplete refreshes the menu after it.
    void fn_710041F0A8(int kind, unsigned int id);
    void refreshComplete();
    // 2.0.0's symbols name it. Its code is in this unit and its callers (seqDispResult, the LAY_list listener's
    // fn_7100423BD0) pass this. What it does (not written yet): sets up the list object handle for id (an NPC's or
    // blade's name text, dock position, a control). Its return value is unused by seqDispResult.
    void dispResult(unsigned int handle, unsigned int id);

    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member: the jobs below store what it returns
    // in m_busyCtrl (with 3 and 2), and seqCtrlWait waits on that control. What it does: starts a control of kind
    // and returns its slot (GfMenuObjUtil::isBusyCtrl's argument).
    int fn_710041FBC8(int kind);

    // m_seq jobs. Placeholder names: new in 3.0.1, nothing in 1.0.0's place names them; members of this class, as
    // their code and their callers' addJob calls show (Delegate<bool()>::memberFuncInvoker of this class).
    // 2.0.0's symbols name it. What it does: for the lists of kinds 1, 2 and 3, hides each entry's TXT_icon_new when
    // GfDataBlade::fn_710024DF88 holds for its id (alpha 0, else 1).
    void refreshNew();
    // start control 0 (fn_7100423514) or 1 (fn_7100423700) into m_busyCtrl, then add to m_seq: wait for it, 30
    // frames, seqCloseTelop, wait again, then fn_7100424E00 (0) or seqMoveLost (1). Reached by address from the
    // LAY_main listener's reciveEvent (fn_7100421588).
    bool fn_7100423514();
    bool fn_7100423700();
    // adds seqMoveEntry to m_seq
    bool seqStartEntry();
    // sends LAY_main event 0x102
    bool seqDialogEnd();
    // waits for the m_busyCtrl control to end, then forgets it
    bool seqCtrlWait();
    // sends LAY_image event 0x101
    bool seqStartImage();
    // play voices "702870101", "703750201", "704670105" and "701580101" into m_voice
    bool seqImageVoiceA();
    bool seqImageVoiceB();
    bool seqImageVoiceC();
    bool seqImageVoiceD();
    // waits for m_voice's result to reach 3, then forgets it
    bool seqVoiceWait();
    // starts control 3 into m_busyCtrl
    bool seqStartLevelMax();
    // does nothing
    bool seqLevelMaxFadeIn();
    // waits for m_animObject's animation to end, then forgets it
    bool seqAnimWait();
    // clears m_resultDone and sends LAY_image's open event (1)
    bool seqOpenImage();
    // waits for m_resultDone
    bool seqWaitImage();
    // starts control 2 into m_busyCtrl
    bool seqStartLevelUp();
    // adds seqWaitStreaming2 and seqReturnMain to m_seq
    bool seqReturn();
    // unless IMG_image@01 is still streaming: fades LAY_image in (preset time 6) into m_busyCtrl
    bool seqWaitStreamingImg();
    // unless IMG_image@01 is still streaming: hides TXT_telop@04, plays IMG_telop_base's "end_max" and shows
    // LAY_image
    bool seqWaitStreamingImgFirst();
    // fades LAY_telop out (0.2) into m_busyCtrl
    bool seqCloseTelop();
    // m_seq's job fn_7100423514 adds last (not written yet)
    bool fn_7100424E00();
    // sets up the list object at m_cursor with m_ids[m_cursor] (dispResult), enables LAY_result's input and its
    // operation info, clears m_resultDone and calls fn_7100569228
    bool seqDispResult();
    // waits for m_resultDone; then, when m_resultFadeOut is set, slides LAY_result out ("cmn_fade_motion_lr"
    // "fade_out_l") and clears it
    bool seqConfirmGet();
    // moves m_cursor on: adds seqMoveEntry while it is inside m_list, else seqReturn
    bool seqNextEntry();
    // sets up m_ids[m_cursor] (fn_710041F0A8 with 0, refreshComplete), then moves m_cursor on: adds seqMoveLost
    // while it is inside m_list, else seqReturn
    bool seqNextLost();
    // m_seq's job seqNextLost adds (not written yet)
    bool seqMoveLost();
    // m_seq's job seqReturn adds first (not written yet)
    bool seqWaitStreaming2();
    // sends LAY_main event 0x100
    bool seqReturnMain();
    // m_seq's job seqStartEntry adds (not written yet)
    bool seqMoveEntry();

    unsigned char pad_24[0x4];
    // the id lists the ctor creates (GfMenuIDList::create) and the select lists showing them, by kind (0-3; the
    // ctor and destructor create and release four of each; the names are not the original's)
    GfMenuIDList* m_idLists[4];
    ui::UISelectObjList* m_selectLists[4];
    unsigned char pad_68[0x30];
    // the m_list entry the jobs work on, seqNextEntry moves it on (the name is not the original's)
    unsigned int m_cursor;
    // ConfirmListener sets it when LAY_result reports event 8 with 1; seqOpenImage clears it (the name is not the
    // original's)
    bool m_resultDone;
    unsigned char pad_9D[0x3];
    // the ids seqDispResult sets up m_list's entries with, by m_cursor (the name is not the original's)
    mm::mtl::FixedVector<unsigned int, 4> m_ids;
    // the list m_cursor walks (the name is not the original's)
    ui::UISelectObjList* m_list;
    GfMenuSequence<GfMenuObjHitonowa, 16> m_seq;
    GfMenuSequence<GfMenuObjHitonowa, 16> m_seq2;
    // the control fn_710041FBC8 started, -1 none (the name is not the original's)
    int m_busyCtrl;
    // the object whose animation seqAnimWait waits for, 0 none (the name is not the original's)
    unsigned int m_animObject;
    unsigned char pad_AA8[0x429];
    // seqConfirmGet slides LAY_result out when it is set, and clears it (the name is not the original's)
    bool m_resultFadeOut;
    unsigned char pad_ED2[0x6];
    // the counts shown for the id lists, by kind (fn_710041E6F8 stores each list's size; the name is not the
    // original's)
    mm::mtl::IntrusivePtr<GfMenuReferenceNumber> m_refNums[4];
    // the voice the voice jobs play (the name is not the original's)
    GAME_VOICE_HANDLE* m_voice;
};

class GfMenuObjHitonowa::ConfirmListener : public ::ui::UIObjectListener {
public:
    // its initialize zeroes 0xC-0x1B after storing its table, as other menus' listeners do
    ConfirmListener(GfMenuObjHitonowa* owner) : pad_0C(), m_owner(owner) {}
    virtual ~ConfirmListener() {}  // slot 0: weak in the original, and its D1 slot is the base's destructor
    virtual void reciveEvent(const ui::EventData& event, unsigned int handle);  // slot 2
    unsigned char pad_0C[0x10];
    GfMenuObjHitonowa* m_owner;
};

class GfMenuObjHitonowa::BgListener : public ::ui::UIObjectListener {
public:
    BgListener(GfMenuObjHitonowa* owner) : pad_0C(), m_owner(owner) {}
    virtual ~BgListener() {}  // slot 0: weak in the original, and its D1 slot is the base's destructor
    virtual void reciveEvent(const ui::EventData& event, unsigned int handle);  // slot 2
    unsigned char pad_0C[0x10];
    GfMenuObjHitonowa* m_owner;
};
}  // namespace gf

#endif

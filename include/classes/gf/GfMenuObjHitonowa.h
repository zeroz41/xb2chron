#ifndef CLASSES_GF_TUNK_B62AA0_H
#define CLASSES_GF_TUNK_B62AA0_H

#include "classes/gf/GfMenuObject.h"
#include "classes/ui/UIObjectListener.h"
#include "gf/GfMenuSequence.h"
#include "mm/mtl/FixedArray.h"
#include "mm/mtl/FixedVector.h"
#include "mm/mtl/IntrusivePtr.h"

namespace gf { class GAME_VOICE_HANDLE; class GfMenuIDList; class GfMenuQuestList; class GfMenuReferenceNumber; }
namespace mm { template <typename T> class Pnt; }
namespace ui { class UICtrlCursorSelect; class UICtrlRoll; class UIObjectAcc; struct EventData; class UISelectObjList; }

namespace gf {
// table 0x7100B62AA0; the "Hitonowa" (circle of people) menu evt_ui openHitonowa opens (gf_menu_obj_hitonowa.cpp).
// 2.0.0's symbols name it and its five listeners (registered on LAY_main, LAY_result, LAY_list, LAY_image, LAY_bg).
class GfMenuObjHitonowa : public ::gf::GfMenuObject {
public:
    GfMenuObjHitonowa(unsigned int handle);
    // the listeners initialize registers on its layouts (2.0.0's symbols name them): MainListener LAY_main (table
    // 0x7100B62AE8), ConfirmListener LAY_result (0x7100B62B10), ListListener LAY_list (0x7100B62B38), ImageListener
    // LAY_image (0x7100B62B60), BgListener LAY_bg (0x7100B62B88)
    class MainListener;
    class ConfirmListener;
    class ListListener;
    class ImageListener;
    class BgListener;

    virtual ~GfMenuObjHitonowa();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4

    // 2.0.0's symbols name it. What it does: registers full-screen layer 0x12F with a GfMenuTypes::Param whose menu is
    // 1. Caller: GfMenuObjNpcTelop::HitonowaListener::reciveEvent (gf_menu_obj_* code).
    static void setBootFromEvent();
    // 2.0.0's symbols name it. What it does: clears the stream-image bits of image (resetStreamImageEx), asks
    // getNpcChange about id, and sets setStreamImage2nd for 1 or setStreamImage3rd's bit for 2. Caller: GfMenuObjNpcTelop::MainListener::reciveEvent.
    static void setFaceStream(ui::UIObjectAcc& image, unsigned int id);
    // 2.0.0's symbols name it. A member: in this unit, called only by setFaceStream. What it does (from its caller):
    // returns 0, 1 or 2 for id, writing an unsigned int through value.
    static int getNpcChange(unsigned int id, unsigned int& value);
    // 2.0.0's symbols name it. What it does: keeps GfGameManager::getHitonowaLevel() in s_CurLevel and passes 0 to
    // GfMenuLocation::startNpcNavigate. Caller: GfMenuManager::setupGame.
    static void setupGame();
    // what setupGame keeps of GfGameManager::getHitonowaLevel(). 2.0.0's symbols name it (lbl_7100EAB87C); this unit's
    // code reaches it through the GOT, so it is not a file static
    static unsigned int s_CurLevel;

    // 2.0.0's symbols name it. A member: its code is in this unit and it reads this's lists; called by initialize.
    // What it does: unless the list of kind (below 4) already holds an id of the same GfDataNpc::getHitonowaFlag2Index
    // group, adds id with GfDataHitonowa::getEntryComplete's (kind 0) or GfDataHitonowa::getEntryOn's value, sorts the list ascending (sortFromWork)
    // and stores its size in m_refNums[kind].
    void addNpc(unsigned char kind, unsigned int id);
    // the order addNpc's std::sort gives a list: ascending GfDataHitonowa::getEntryOn (the name is the original's, from
    // the sort's template arguments; stateless)
    struct CompareEntry {
        bool operator()(const unsigned int& a, const unsigned int& b) const;
    };
    // 2.0.0's symbols name it. A member: its code is in this unit, after refreshComplete. What it does: places list's
    // objects on a grid of columns columns from origin, each cell width - 14 wide and height - 14 high
    // (setPosCenter).
    static void placeObjectHitonowa(ui::UISelectObjList* list, const mm::Pnt<short>& origin, unsigned int width,
                                    unsigned int height, unsigned int columns);
    // 2.0.0's symbols name it. What it does: shows LAY_level and fades it in (preset 3), then shows TXT_level_num and
    // TXT_level_max, only the latter opaque when s_CurLevel is 6.
    void dispLevel();
    // 2.0.0's symbols name them. Their code is in this unit and seqNextLost passes this. What they do (not written
    // yet): delNpc sets the list up for an id (its first argument 0 there); refreshComplete refreshes the menu after
    // it.
    void delNpc(unsigned char kind, unsigned int id);
    void refreshComplete();
    // 2.0.0's symbols name it. Its code is in this unit and its callers (seqDispResult, the LAY_list listener's
    // ListListener::reciveEvent) pass this. What it does (not written yet): sets up the list object handle for id (an
    // NPC's or blade's name text, dock position, a control). Its return value is unused by seqDispResult.
    void dispResult(unsigned int handle, unsigned int id);
    // 2.0.0's symbols name it. Its code is in this unit and seqInEntry passes this (the list object at m_cursor, the
    // id there and its getNpcGroup). Not written yet.
    void dispStatus(unsigned int handle, unsigned int id, unsigned int group);
    // 2.0.0's symbols name it. Its code is in this unit and MainListener::reciveEvent calls it. What it does: builds
    // m_list from the select lists' objects whose ids m_ids holds (kinds 1, 2, 3 then 0, by pad_94's mode 0-2),
    // setting their alpha and TXT_icon_new, hides LAY_main's LAY_location_num@NN and resets m_cursor.
    void setupEvent();
    // 2.0.0's symbols name it. Its code is in this unit, after setupEvent. What it does: shows every select list's
    // objects again (alpha 1), lays the lists of kinds 1-3 out on LAY_icon_list's icon_center/icon_range grid
    // (placeObjectHitonowa, 5 columns) unless pad_94 is 1 or 2, and fades LAY_main's LAY_location_num@NN back in.
    void returnEvent();

    // 2.0.0's symbols name it. A member: the jobs below store what it returns in m_busyCtrl (with 3 and 2), and
    // seqCtrlWait waits on that control. What it does: starts a control of kind and returns its slot
    // (GfMenuObjUtil::isBusyCtrl's argument).
    int openTelop(unsigned int kind);

    // m_seq jobs. 2.0.0's symbols name them; members of this class, as their code and their callers' addJob calls
    // show (Delegate<bool()>::memberFuncInvoker of this class).
    // 2.0.0's symbols name it. What it does: for the lists of kinds 1, 2 and 3, hides each entry's TXT_icon_new when
    // GfDataNpc::isHitonowaNewFlag holds for its id (alpha 0, else 1).
    void refreshNew();
    // start control 0 (seqStartGet) or 1 (seqStartLost) into m_busyCtrl, then add to m_seq: wait for it, 30 frames,
    // seqCloseTelop, wait again, then seqMoveGet (0) or seqMoveLost (1). Reached by address from the LAY_main
    // listener's reciveEvent (MainListener::reciveEvent).
    bool seqStartGet();
    bool seqStartLost();
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
    // m_seq's job seqStartGet adds last (not written yet)
    bool seqMoveGet();
    // sets up the list object at m_cursor with m_ids[m_cursor] (dispResult), enables LAY_result's input and its
    // operation info, clears m_resultDone and calls createHitonowaGet
    bool seqDispResult();
    // waits for m_resultDone; then, when m_resultFadeOut is set, slides LAY_result out ("cmn_fade_motion_lr"
    // "fade_out_l") and clears it
    bool seqConfirmGet();
    // moves m_cursor on: adds seqMoveEntry while it is inside m_list, else seqReturn
    bool seqNextEntry();
    // sets up m_ids[m_cursor] (delNpc with 0, refreshComplete), then moves m_cursor on: adds seqMoveLost
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
    // 2.0.0's symbols name them (callers: ListListener::reciveEvent). selectComplete moves the list object to the
    // centre of its parent's "char_region" and scales its LAY_icon_face up (returns the move's control);
    // unselectComplete returns it (control into m_busyCtrl) and scales LAY_icon_face back.
    int selectComplete(unsigned int handle);
    void unselectComplete(unsigned int handle);
    // m_seq jobs (2.0.0's symbols name them)
    bool seqWaitStreamingEvent();
    bool seqWaitStreaming();
    // after the common window closes with result 0: navigates to the selected NPC of m_kind's list, or stops
    // navigating when it is already the target
    bool seqWaitNavi();
    bool seqChangeGet();
    bool seqInGet();
    bool seqNextGet();
    // fades in each list-0 object whose alpha is 0 ("cmn_fade_emotion" "fade_in", 0.1 s apart)
    bool seqDispGet();
    // shows m_list's IMG_icon_frame at m_cursor, starts its control into m_busyCtrl, then seqChangeLost2
    bool seqChangeLost();
    bool seqChangeLost2();
    bool seqInLost();
    bool seqInEntry();
    bool seqMoveEntry2();

    unsigned char pad_24[0x4];
    // the id lists the ctor creates (GfMenuIDList::create) and the select lists showing them, by kind (0-3; the
    // ctor and destructor create and release four of each; the names are not the original's)
    GfMenuIDList* m_idLists[4];
    ui::UISelectObjList* m_selectLists[4];
    unsigned char pad_68[0x8];
    // the roll control seqMoveLost takes the list object off (UICtrlRoll::delObject; the name is not the original's)
    ui::UICtrlRoll* m_roll;
    unsigned char pad_78[0x8];
    // the numbers initialize shows in LAY_level's TXT_level_num and TXT_next_num (GfMenuReferenceAdapter; the names
    // are not the original's)
    mm::mtl::IntrusivePtr<GfMenuReferenceNumber> m_levelNum;
    mm::mtl::IntrusivePtr<GfMenuReferenceNumber> m_nextNum;
    // initialize sets it (a value == 1) and tests it
    bool pad_90;
    unsigned char pad_91[0x3];
    // initialize sets it and tests it for 0, 1 and 2
    int pad_94;
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
    // the control openTelop started, -1 none (the name is not the original's)
    int m_busyCtrl;
    // the object whose animation seqAnimWait waits for, 0 none (the name is not the original's)
    unsigned int m_animObject;
    // the quest list the ctor creates (GfMenuQuestList::create) and the destructor releases (the name is not the
    // original's)
    GfMenuQuestList* m_questList;
    // a fixed vector the destructor empties (its 0x400-byte buffer ends at 0xEB0; the element type is not known)
    mm::mtl::FixedVector<unsigned int, 256> pad_AB0;
    // the kind of the id list the main layout shows (seqWaitNavi; the name is not the original's)
    unsigned int m_kind;
    unsigned char pad_EBC[0x4];
    // the list initialize picks LAY_list_item@%02d into, and the cursor it creates on it (LAY_list_item_cursor);
    // the destructor releases both (the names are not the original's)
    ui::UISelectObjList* m_listItems;
    ui::UICtrlCursorSelect* m_listCursor;
    // seqMoveEntry2 slides LAY_status out when it is set, and clears it (the name is not the original's)
    bool m_statusFadeOut;
    // seqConfirmGet slides LAY_result out when it is set, and clears it (the name is not the original's)
    bool m_resultFadeOut;
    // the ctor zeroes 0xED0-0xED3 with one 32-bit store
    bool pad_ED2;
    bool pad_ED3;
    unsigned char pad_ED4[0x4];
    // the counts shown for the id lists, by kind (addNpc stores each list's size; the name is not the
    // original's)
    mm::mtl::FixedArray<mm::mtl::IntrusivePtr<GfMenuReferenceNumber>, 4> m_refNums;
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

// 2.0.0's symbols name it, a free function of gf; its code is in gf_menu_obj_hitonowa.cpp, after
// GfMenuObjHitonowa::finalize. What it does: reads BDAT table 0xA8's row id: "AreaNumber3" when its "Condition2" is
// set and holds (GfGameCond::isGameCond), else "AreaNumber2" when "Condition1" is set and holds, else
// "AreaNumber1". Callers: GfMenuObjHitonowa::initialize and seqInEntry.
unsigned int getNpcGroup(unsigned int id);
}  // namespace gf

#endif

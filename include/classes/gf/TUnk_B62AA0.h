#ifndef CLASSES_GF_TUNK_B62AA0_H
#define CLASSES_GF_TUNK_B62AA0_H

#include "classes/gf/GfMenuObject.h"
#include "classes/ui/UIObjectListener.h"
#include "gf/GfMenuSequence.h"

namespace gf { class GAME_VOICE_HANDLE; }
namespace ui { class UIObjectAcc; struct EventData; }

namespace gf {
// table 0x7100B62AA0; the "Hitonowa" (circle of people) menu evt_ui openHitonowa opens (gf_menu_obj_hitonowa.cpp).
// Unnamed class (TUnk_<table low address>, counted as debt): the symbols leave it unnamed (no RTTI in 3.0.1, nothing in
// 1.0.0). Its five listeners are named the same way after their tables (registered on LAY_main, LAY_result, LAY_list,
// LAY_image, LAY_bg).
class TUnk_B62AA0 : public ::gf::GfMenuObject {
public:
    // the listeners initialize registers on its layouts, named after the layout each is registered on (the names are
    // not the original's): TUnk_B62AE8 LAY_main (table 0x7100B62AE8), TUnk_B62B10 LAY_result (0x7100B62B10),
    // TUnk_B62B38 LAY_list (0x7100B62B38), TUnk_B62B60 LAY_image (0x7100B62B60), TUnk_B62B88 LAY_bg (0x7100B62B88)
    class TUnk_B62AE8;
    class TUnk_B62B10;
    class TUnk_B62B38;
    class TUnk_B62B60;
    class TUnk_B62B88;

    virtual ~TUnk_B62AA0();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4

    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member: its code is in this unit between
    // the destructor and initialize. What it does: registers full-screen layer 0x12F with a GfMenuTypes::Param whose
    // menu is 1. Caller: fn_71004488A0 (gf_menu_obj_* code).
    static void fn_710041D238();
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member: its code is in this unit and it
    // calls this unit's fn_710041D2C8. What it does: clears the stream-image bits of image (fn_710069201C), asks
    // fn_710041D2C8 about id, and sets setStreamImage2nd for 1 or fn_7100691FD0's bit for 2. Caller: fn_7100447D88.
    static void fn_710041D268(ui::UIObjectAcc& image, unsigned int id);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member: in this unit, called only by
    // fn_710041D268. What it does (from its caller): returns 0, 1 or 2 for id, writing an int through value.
    static int fn_710041D2C8(unsigned int id, int* value);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member: its code is in this unit. What it
    // does: keeps GfGameManager::fn_71002AC8E0() in s_gameValue and passes 0 to
    // GfMenuLocation::fn_7100356980. Caller: fn_71003597B0.
    static void fn_710041D544();
    // what fn_710041D544 keeps of GfGameManager::fn_71002AC8E0(). Proposed name, not the original's: the symbols leave
    // it unnamed (lbl_7100EAB87C); this unit's code reaches it through the GOT, so it is not a file static
    static unsigned int s_gameValue;

    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member: the jobs below store what it returns
    // in m_busyCtrl (with 3 and 2), and fn_7100424A40 waits on that control. What it does: starts a control of kind
    // and returns its slot (GfMenuObjUtil::isBusyCtrl's argument).
    int fn_710041FBC8(int kind);

    // m_seq jobs. Placeholder names: new in 3.0.1, nothing in 1.0.0's place names them; members of this class, as
    // their code and their callers' addJob calls show (Delegate<bool()>::memberFuncInvoker of this class).
    // adds fn_7100426B44 to m_seq
    bool fn_71004238EC();
    // sends LAY_main event 0x102
    bool fn_7100423AE0();
    // waits for the m_busyCtrl control to end, then forgets it
    bool fn_7100424A40();
    // sends LAY_image event 0x101
    bool fn_7100424A84();
    // play voices "702870101", "703750201", "704670105" and "701580101" into m_voice
    bool fn_7100424BB4();
    bool fn_7100424BE4();
    bool fn_7100424C14();
    bool fn_7100424C44();
    // waits for m_voice's result to reach 3, then forgets it
    bool fn_7100424C74();
    // starts control 3 into m_busyCtrl
    bool fn_7100425E60();
    // does nothing
    bool fn_7100425E8C();
    // waits for m_animObject's animation to end, then forgets it
    bool fn_7100425E94();
    // clears m_resultDone and sends LAY_image's open event (1)
    bool fn_7100425EF8();
    // waits for m_resultDone
    bool fn_7100425F44();
    // starts control 2 into m_busyCtrl
    bool fn_7100425F4C();
    // adds fn_710042603C and fn_710042621C to m_seq
    bool fn_7100425F78();
    // m_seq's job fn_7100425F78 adds first (not written yet)
    bool fn_710042603C();
    // sends LAY_main event 0x100
    bool fn_710042621C();
    // m_seq's job fn_71004238EC adds (not written yet)
    bool fn_7100426B44();

    unsigned char pad_24[0x78];
    // TUnk_B62B10 sets it when LAY_result reports event 8 with 1; fn_7100425EF8 clears it (the name is not the
    // original's)
    bool m_resultDone;
    unsigned char pad_9D[0x23];
    GfMenuSequence<TUnk_B62AA0, 16> m_seq;
    GfMenuSequence<TUnk_B62AA0, 16> m_seq2;
    // the control fn_710041FBC8 started, -1 none (the name is not the original's)
    int m_busyCtrl;
    // the object whose animation fn_7100425E94 waits for, 0 none (the name is not the original's)
    unsigned int m_animObject;
    unsigned char pad_AA8[0x450];
    // the voice the voice jobs play (the name is not the original's)
    GAME_VOICE_HANDLE* m_voice;
};

class TUnk_B62AA0::TUnk_B62B10 : public ::ui::UIObjectListener {
public:
    // its initialize zeroes 0xC-0x1B after storing its table, as other menus' listeners do
    TUnk_B62B10(TUnk_B62AA0* owner) : pad_0C(), m_owner(owner) {}
    virtual ~TUnk_B62B10() {}  // slot 0: weak in the original, and its D1 slot is the base's destructor
    virtual void reciveEvent(const ui::EventData& event, unsigned int handle);  // slot 2
    unsigned char pad_0C[0x10];
    TUnk_B62AA0* m_owner;
};

class TUnk_B62AA0::TUnk_B62B88 : public ::ui::UIObjectListener {
public:
    TUnk_B62B88(TUnk_B62AA0* owner) : pad_0C(), m_owner(owner) {}
    virtual ~TUnk_B62B88() {}  // slot 0: weak in the original, and its D1 slot is the base's destructor
    virtual void reciveEvent(const ui::EventData& event, unsigned int handle);  // slot 2
    unsigned char pad_0C[0x10];
    TUnk_B62AA0* m_owner;
};
}  // namespace gf

#endif

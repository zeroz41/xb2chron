#ifndef CLASSES_GF_TUNK_B60AA8_H
#define CLASSES_GF_TUNK_B60AA8_H

#include "classes/gf/GfMenuObject.h"
#include "classes/ui/UIObjectListener.h"
#include "gf/GfMenuSequence.h"
#include "gf/SoundHandle.h"

namespace gf { class GAME_VOICE_HANDLE; class GfMenuCallContext; class GfMenuDriverList; }
namespace mm { namespace mtl { class ReferenceObject; } }
namespace ui { class UICtrlCursorSelect; class UISelectObjList; struct EventData; }

namespace gf {
// table 0x7100B60AA8 (gf_menu_obj_camp_menu). The symbols leave the class unnamed and it has no RTTI.
class TUnk_B60AA8 : public ::gf::GfMenuObject {
public:
    // the listeners initialize registers (named by their tables' starts; nothing names them)
    class TUnk_B60AF8;
    class TUnk_B60B20;
    class TUnk_B60B48;
    class TUnk_B60B70;
    class TUnk_B60B98;

    TUnk_B60AA8(unsigned int handle);
    virtual ~TUnk_B60AA8();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4

    // the sequence's jobs (placeholder names: new in 3.0.1, nothing in 1.0.0 names them)
    bool fn_71003BCEAC();  // opens common window 0x11F; on result 0 closes LAY_menu and opens LAY_sleep, else LAY_menu event 0x100
    bool fn_71003BCFB8();  // opens common window 0x11E, then sends LAY_menu event 0x100 (1 when its result is 0)
    bool fn_71003BD924();  // starts fade 2 (30 frames, black), then waits for it
    bool fn_71003BE0FC();  // once m_context is terminated, closes LAY_main's LAY_shop
    bool fn_71003BE178();  // starts fade 1 (15 frames, black)
    bool fn_71003BE1A0();  // waits while GfMenuManager::isFading
    bool fn_71003BE1BC();  // GfFieldTime setTime(7, 0), then GfGameManager::fn_71002AC6A8
    bool fn_71003BE1EC();  // done at once
    bool fn_71003BE1F4();  // terminates m_fsLayer's UI layer
    // Placeholder name: new in 3.0.1, nothing in 1.0.0 names it. A static member: only this class's functions call it
    // (0x71003BD69C, 0x71003BDF70, 0x71003BE8C4). What it does: finds the row of BDAT table 0x10E whose driver_id is
    // driver, stores its shop_id and summary_msg in shop[0] and shop[1] and returns true; false when none.
    static bool fn_71003BE7EC(unsigned int driver, unsigned short* shop);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0 names it. Static: it takes no this (fn_71003BCCD4 passes the
    // driver). What it does: true when the driver's shop (fn_71003BE7EC) is a ShopType 1 shop of BDAT 0xED whose
    // TableID row of BDAT 0xF0 has a DefTaskSet<n> (or an AddTaskSet<n> whose AddCondition<n> holds) with an
    // IraCraftIndex (BDAT 0xF2) whose local flag 2 (0xEE04 + index) is clear.
    static bool fn_71003BE8C4(unsigned int driver);
    // Placeholder names: new in 3.0.1, nothing in 1.0.0 names them. Members: called on the owner by its listeners
    void fn_71003BCCD4();  // shows LAY_menu's entries by the game flags
    bool fn_71003BD058();  // queues fade 1, its wait, (with fn_71002EDA8C) the time jobs and fn_71003BE1F4
    void fn_71003BD69C();  // the cursor's driver: its shop becomes the reference shop, its summary TXT_craft_info
    bool fn_71003BD978();  // opens full screen 5 and queues its jobs
    unsigned int fn_71003BDF70();  // the cursor's driver: LAY_shop's header texts and reference; returns its shop
    void fn_71003BE490(unsigned int index);  // shows the driver list 1 entry at index (-1: none)
    bool fn_71003BEB30();  // waits while a full-screen menu is open
    bool fn_71003BEB4C();  // the same code as fn_71003BE1F4

    unsigned char pad_24[4];
    GfMenuSequence<TUnk_B60AA8, 8> m_seq;  // 0x28 (the name is not the original's)
    bool m_jobStarted;  // 0x2B8: a job's first step ran; the jobs clear it as they end (the name is not the original's)
    GfMenuDriverList* m_driverList0;  // 0x2C0 the constructor creates them, the destructor releases them
    GfMenuDriverList* m_driverList1;  // 0x2C8
    ui::UISelectObjList* m_selectList;  // 0x2D0
    ui::UICtrlCursorSelect* m_cursor;  // 0x2D8: initialize's UICtrlCursorSelect::create, the destructor releases it
    GfMenuCallContext* m_context;  // 0x2E0
    GAME_VOICE_HANDLE* m_voice;  // 0x2E8 update drops it once its result is 3 or more
    SoundHandle m_sound;  // 0x2F0 (the name is not the original's)
};

// the listeners' layout is ui::UIObjectListener's, then the owner (as in the other menu objects' listeners)
class TUnk_B60AA8::TUnk_B60AF8 : public ::ui::UIObjectListener {
public:
    TUnk_B60AF8(TUnk_B60AA8* owner) : pad_0C(), m_owner(owner) {}
    virtual ~TUnk_B60AF8() {}  // slot 0: weak, its D1 slot is the base's destructor
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2: LAY_menu's events
    unsigned char pad_0C[0x10];  // cleared by the constructor
    TUnk_B60AA8* m_owner;
};

class TUnk_B60AA8::TUnk_B60B20 : public ::ui::UIObjectListener {
public:
    TUnk_B60B20(TUnk_B60AA8* owner) : pad_0C(), m_owner(owner) {}
    virtual ~TUnk_B60B20() {}  // slot 0: weak, its D1 slot is the base's destructor
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2: the craft driver list's events
    unsigned char pad_0C[0x10];  // cleared by the constructor
    TUnk_B60AA8* m_owner;
};

class TUnk_B60AA8::TUnk_B60B48 : public ::ui::UIObjectListener {
public:
    TUnk_B60B48(TUnk_B60AA8* owner) : pad_0C(), m_owner(owner) {}
    virtual ~TUnk_B60B48() {}  // slot 0: weak, its D1 slot is the base's destructor
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
    unsigned char pad_0C[0x10];  // cleared by the constructor
    TUnk_B60AA8* m_owner;
};

class TUnk_B60AA8::TUnk_B60B70 : public ::ui::UIObjectListener {
public:
    TUnk_B60B70(TUnk_B60AA8* owner) : m_mode(), pad_10(), m_owner(owner) {}
    virtual ~TUnk_B60B70() {}  // slot 0: weak, its D1 slot is the base's destructor
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2: LAY_shop's events
    // 1 after event 0x101 (the shop's sleep path): event 3 then queues the time jobs; 0 after the open (0x21)
    // (the name is not the original's)
    int m_mode;
    unsigned char pad_10[0xC];  // cleared by the constructor
    TUnk_B60AA8* m_owner;
};

class TUnk_B60AA8::TUnk_B60B98 : public ::ui::UIObjectListener {
public:
    TUnk_B60B98(TUnk_B60AA8* owner) : pad_0C(), m_owner(owner) {}
    virtual ~TUnk_B60B98() {}  // slot 0: weak, its D1 slot is the base's destructor
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
    unsigned char pad_0C[0x10];  // cleared by the constructor
    TUnk_B60AA8* m_owner;
};
}  // namespace gf

#endif

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
class GfMenuObjCampMenu : public ::gf::GfMenuObject {
public:
    // the listeners initialize registers (named by their tables' starts; nothing names them)
    class TUnk_B60AF8;
    class CraftListener;
    class SleepListener;
    class ShopListener;
    class ChrChangeListener;

    GfMenuObjCampMenu(unsigned int handle);
    virtual ~GfMenuObjCampMenu();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4

    // the sequence's jobs (placeholder names: new in 3.0.1, nothing in 1.0.0 names them)
    bool seqConfirmSleep();  // opens common window 0x11F; on result 0 closes LAY_menu and opens LAY_sleep, else LAY_menu event 0x100
    bool seqConfirmExit();  // opens common window 0x11E, then sends LAY_menu event 0x100 (1 when its result is 0)
    bool seqWaitSleepFade();  // starts fade 2 (30 frames, black), then waits for it
    bool seqWaitShop();  // once m_context is terminated, closes LAY_main's LAY_shop
    bool seqCloseSpecialFadeOut();  // starts fade 1 (15 frames, black)
    bool seqCloseSpecialFadeWait();  // waits while GfMenuManager::isFading
    bool seqAutoSave();  // GfFieldTime setTime(7, 0), then GfGameManager::reqestEventAutoSave
    bool seqAutoSaveWait();  // done at once
    bool seqCloseSpecial();  // terminates m_fsLayer's UI layer
    // what getDriverShopInfo answers (2.0.0's symbols name the type; the field names follow the BDAT columns it
    // reads, they are not the original's)
    struct ShopInfo {
        unsigned short m_shopId;
        unsigned short m_summaryMsg;
    };
    // 2.0.0's symbols name it. What it does: finds the row of BDAT table 0x10E whose driver_id is driver, stores its
    // shop_id and summary_msg in shop and returns true; false when none. Only this class's functions call it
    // (0x71003BD69C, 0x71003BDF70, 0x71003BE8C4).
    static bool getDriverShopInfo(unsigned int driver, ShopInfo& shop);
    // 2.0.0's symbols name it. What it does: true when the driver's shop (getDriverShopInfo) is a ShopType 1 shop of
    // BDAT 0xED whose TableID row of BDAT 0xF0 has a DefTaskSet<n> (or an AddTaskSet<n> whose AddCondition<n> holds)
    // with an IraCraftIndex (BDAT 0xF2) whose local flag 2 (0xEE04 + index) is clear.
    static bool hasNewCraft(unsigned int driver);
    // 2.0.0's symbols name them (they were free functions in gf before). What they do:
    // getSelectResult returns s_SelectResult (GfMenuManager::isCampSelectTalk compares it with 1).
    static int getSelectResult();
    // returnFromEvent takes the attached object 0x8D (GfMenuObject::getAttachedObject), and when its ui::UIObjectAcc
    // is valid sends an open event (0, child "LAY_menu", 0.0f) and clears s_SelectResult. Caller:
    // GfMenuManager::openCampMenu when its layer-300 flag is already set.
    static void returnFromEvent();
    // closeShopToTalk: when the attached object 0x8D's ui::UIObjectAcc is valid, sends event 0x101 (parameters zero)
    // to its child "LAY_shop" and clears s_SelectResult. Caller: GfMenuObjShop::ExcTaskListListener::reciveEvent.
    static void closeShopToTalk();
    // 2.0.0's symbols name it (lbl_7100EAA1D0). Reached through the GOT; getSelectResult returns it, the camp
    // menu's listeners set it to 1 (and 0), returnFromEvent/closeShopToTalk clear it after sending their event.
    static int s_SelectResult;
    // enableCraftChrChange: when the attached object 0x8D's ui::UIObjectAcc is valid, GfMenuObject::enableInput on its
    // child "LAY_chr_change"; disableCraftChrChange the same with GfMenuObject::disableInput. Caller:
    // GfMenuObjShop::ExcTaskListListener::reciveEvent.
    static void enableCraftChrChange();
    static void disableCraftChrChange();
    // setCampTalkNew: GfMenuFlag::set1(0x54, 0); ScriptPlayText's ui setCampTalkNew calls it.
    static void setCampTalkNew();
    // 2.0.0's symbols name them. Called on the owner by its listeners
    void refreshNotice();  // shows LAY_menu's entries by the game flags
    bool seqClose();  // queues fade 1, its wait, (with GfGameUtilDiff::isEnableAutoSave) the time jobs and seqCloseSpecial
    void refreshCraftInfo();  // the cursor's driver: its shop becomes the reference shop, its summary TXT_craft_info
    bool seqStartLevelUp();  // opens full screen 5 and queues its jobs
    unsigned int refreshShopInfo();  // the cursor's driver: LAY_shop's header texts and reference; returns its shop
    void refreshChrChange(int index);  // shows the driver list 1 entry at index (-1: none)
    bool seqWaitFSClose();  // waits while a full-screen menu is open
    bool seqEndSleep();  // the same code as seqCloseSpecial

    unsigned char pad_24[4];
    GfMenuSequence<GfMenuObjCampMenu, 8> m_seq;  // 0x28 (the name is not the original's)
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
class GfMenuObjCampMenu::TUnk_B60AF8 : public ::ui::UIObjectListener {
public:
    TUnk_B60AF8(GfMenuObjCampMenu* owner) : pad_0C(), m_owner(owner) {}
    virtual ~TUnk_B60AF8() {}  // slot 0: weak, its D1 slot is the base's destructor
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2: LAY_menu's events
    unsigned char pad_0C[0x10];  // cleared by the constructor
    GfMenuObjCampMenu* m_owner;
};

class GfMenuObjCampMenu::CraftListener : public ::ui::UIObjectListener {
public:
    CraftListener(GfMenuObjCampMenu* owner) : pad_0C(), m_owner(owner) {}
    virtual ~CraftListener() {}  // slot 0: weak, its D1 slot is the base's destructor
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2: the craft driver list's events
    unsigned char pad_0C[0x10];  // cleared by the constructor
    GfMenuObjCampMenu* m_owner;
};

class GfMenuObjCampMenu::SleepListener : public ::ui::UIObjectListener {
public:
    SleepListener(GfMenuObjCampMenu* owner) : pad_0C(), m_owner(owner) {}
    virtual ~SleepListener() {}  // slot 0: weak, its D1 slot is the base's destructor
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
    unsigned char pad_0C[0x10];  // cleared by the constructor
    GfMenuObjCampMenu* m_owner;
};

class GfMenuObjCampMenu::ShopListener : public ::ui::UIObjectListener {
public:
    ShopListener(GfMenuObjCampMenu* owner) : m_mode(), pad_10(), m_owner(owner) {}
    virtual ~ShopListener() {}  // slot 0: weak, its D1 slot is the base's destructor
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2: LAY_shop's events
    // 1 after event 0x101 (the shop's sleep path): event 3 then queues the time jobs; 0 after the open (0x21)
    // (the name is not the original's)
    int m_mode;
    unsigned char pad_10[0xC];  // cleared by the constructor
    GfMenuObjCampMenu* m_owner;
};

class GfMenuObjCampMenu::ChrChangeListener : public ::ui::UIObjectListener {
public:
    ChrChangeListener(GfMenuObjCampMenu* owner) : pad_0C(), m_owner(owner) {}
    virtual ~ChrChangeListener() {}  // slot 0: weak, its D1 slot is the base's destructor
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
    unsigned char pad_0C[0x10];  // cleared by the constructor
    GfMenuObjCampMenu* m_owner;
};
}  // namespace gf

#endif

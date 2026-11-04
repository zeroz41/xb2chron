#ifndef CLASSES_GF_GFMENUOBJSHOP_H
#define CLASSES_GF_GFMENUOBJSHOP_H

#include "classes/gf/GfMenuObject.h"
#include "gf/GfMenuSequence.h"
#include "mm/mtl/FixedVector.h"
#include "mm/mtl/IntrusivePtr.h"
#include "classes/gf/GfMenuReferenceNumber.h"

namespace ui {
class UICtrlCursorSelect;
class UISelectObjList;
}  // namespace ui

namespace gf {
class GfMenuCallContext;
class GfMenuItemList;

// table 0x7100B64738
class GfMenuObjShop : public ::gf::GfMenuObject {
public:
    class CommonListener;
    class ExcTaskListListener;
    class InnActListener;
    class MainListener;
    class NumSelectListener;
    class OrbListListener;
    class OrbRecipeListener;
    class SellFilterListener;
    class SellListListener;
    class StoreActListener;
    class StoreListListener;
    class SubListener;
    // what open sends the shop's layer (event 0x21)
    struct OpenParam {
        unsigned int m_shopId;  // the event's first parameter (16 bits) (the name is not the original's)
        // the event's 16-bit parameter 2, sent only when GfMenuObjUtil::isValidExpansion(3) and
        // GfMenuManager::isOpenCampMenu() answer true (new in 3.0.1; the name is not the original's)
        bool m_option;
    };
    virtual ~GfMenuObjShop();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4

    // starts the shop's call context (object id 0x77): its layer opens (event 0x21), category 1 joins the adapters
    static void open(GfMenuCallContext* context, const OpenParam& param);
    // the shop's call context (object id 0x77) ends: its layer closes (event 0x22), category 1 leaves the adapters
    static void close(GfMenuCallContext* context);
    // the shop's layer (object 0x77) shows or hides its blade (event 0x46, parameter the flag)
    static void dispBlade(bool disp);
    // 2.0.0's symbols name it. What it does: when GfMenuObjUtil::isValidExpansion(3) answers true, sends event 0x47
    // with GfMenuReference::getReferenceShopID() to the shop layer's child "LAY_exc_task_list".
    static void changeCraft();

    // redraws the shop's item lists (1.0.0's update calls it at the same flag; 3.0.1 adds the exchange tasks)
    void refreshItemList();
    // 2.0.0's symbols name it. What it does: shows "LAY_stock_num" by the mode at 0x28 and
    // GfMenuReference::getReferenceItemType(), and moves it by the value at 0x580 (-0x27 more in mode 3).
    void refreshStock();
    // the "IMG_store_sell_filter_icon@NN" icons of "LAY_store_sell_filter": the current filter's gets "sys_select"
    void refreshFilterIcon();
    // the SHOP special-shop row (BDAT 0xF4) whose shop_id is that shop and whose scenario_flag is 0 or the current
    // scenario value (GfDataUtil::getScenarioFlag); 0 for none
    static int getSpecialShop(unsigned int shopId);
    // "TXT_common_guide" shows that row's name (BDAT 0x146's "name", text BDAT 0x118) and fades in from the left
    void setGuideText(unsigned int id);
    // the sell list: the current filter's item type from the item box (s_filterItemType), or every type for filter 0
    void setupSellItemList();
    // the exchange task (BDAT 0xF2 row) can be rewarded: no "Reward", or every item of its reward's items 8-11 fits
    // the item box (GfItemUtil::isEnableAddItemBox)
    bool canGetExcTaskReward(unsigned int task);
    // 2.0.0's symbols name it. What it does: the item ids (low 16 bits) of the exchange task's (BDAT 0xF2 row's
    // "Reward", GfQuestUtil::getReward) reward items 8-11 that are set go to the vector until it is full; true when it
    // holds any.
    bool getExcTaskRewardItem(unsigned int task, mm::mtl::FixedVector<unsigned short, 4>& items);
    // the exchange task's (BDAT 0xF2 row) "HideReward" flag, its "Reward" items in the list and its reward's first
    // value; true when either is there
    bool getExcTaskReward(unsigned int task, unsigned int& value, GfMenuItemList* list, bool& hide);

    // 1.0.0's helpers (3.0.1 inlines them all and drops the copies): the main layer's call context gets that result
    void addCallContextResult(unsigned int result, unsigned int param);
    // event 0x40 to that object, or to the main layer when it is 0
    void sendEnableEvent(unsigned int handle);
    // event 0x41 to that object, or to the main layer when it is 0
    void sendExitEvent(unsigned int handle);
    // event 0x22 to that object, or to the main layer when it is 0
    void sendCloseEvent(unsigned int handle);

    // sequence jobs (m_seq): each returns true when done
    // "TXT_store_sell_index" shows the current filter's name (BDAT 0x11D, list 0x14B's entry filter + 1)
    void setFilterIndex();

    bool seqWaitLoadBlWeapon();
    bool seqEnd();
    bool seqWaitEndBlWeapon();
    bool seqEndDialog();
    bool seqWaitSleepFade();
    bool seqIntervalSleep();
    bool seqWaitFSClose();
    bool seqStartLevelUp();
    bool seqStartSleepFade();
    bool seqItemGet();

    // the shop (GfBdatShop's shop list row): InnActListener pays the inn with it (GfGameUtilShop::execPayInn); the
    // name is not the original's
    unsigned int m_shopId;  // 0x24
    // the shop's mode: 3 moves "LAY_stock_num" up by 0x27, 0 shows it by the filter's item type (refreshStock;
    // the name is not the original's)
    int m_mode;  // 0x28
    unsigned char pad_2C[0x38 - 0x2C];
    // the guide text "TXT_common_guide" shows (setGuideText; the name is not the original's)
    unsigned int m_guideTextId;  // 0x38
    unsigned char pad_3C[0x40 - 0x3C];
    // the inn's action list (initialize's ui::UISelectObjList): InnActListener selects and runs its rows (the name
    // is not the original's)
    ui::UISelectObjList* m_selectList;  // 0x40
    // the items the sell list shows (initialize creates it, setupSellItemList fills it; the name is not the original's)
    GfMenuItemList* m_sellItemList;  // 0x48
    // the sell list's objects (initialize creates it; setupSellItemList's page rows; the name is not the original's)
    ui::UISelectObjList* m_sellObjList;  // 0x50
    // refreshStock: "LAY_stock_num" follows the current filter's item type (the name is not the original's)
    bool m_useFilterItemType;  // 0x58
    // 1.0.0's reqRefreshItemList sets it, update calls refreshItemList and clears it (the name is not the original's)
    bool m_refreshItemList;  // 0x59
    // update redraws "LAY_stock_num" (refreshStock) and clears it (the name is not the original's)
    bool m_stockNumDirty;  // 0x5A
    unsigned char pad_5B[0x60 - 0x5B];
    // the item filters and the current one (setFilterIndex, refreshStock; the names are not the original's)
    mm::mtl::FixedVector<unsigned int, 22> m_filters;  // 0x60
    unsigned int m_filterIndex;  // 0xC0
    unsigned char pad_C4[0xC8 - 0xC4];
    // the inn action list's cursor ("LAY_inn_action_cursor"): InnActListener creates it on event 0x40 and
    // releases it when an action ends (the name is not the original's)
    ui::UICtrlCursorSelect* m_cursor;  // 0xC8
    unsigned char pad_D0[0x148 - 0xD0];
    // the item seqItemGet shows as got in mode 3, then clears (the name is not the original's)
    unsigned int m_getItemId;  // 0x148
    unsigned char pad_14C[0x160 - 0x14C];
    // the items seqItemGet shows as got (the name is not the original's)
    GfMenuItemList* m_itemList;  // 0x160
    // initialize creates them, finalize releases them (the name is not the original's)
    mm::mtl::IntrusivePtr<GfMenuReferenceNumber> m_numbers[26];  // 0x168
    unsigned char pad_238[0x240 - 0x238];  // 0x238: initialize's IntrusivePtr<GfMenuReferenceItem>
    // seqStartLevelUp switches the inn's cloud sea (raised when it is 0) once and clears it (the name is not the
    // original's)
    bool m_switchInnCloudSea;  // 0x240
    unsigned char pad_241[0x248 - 0x241];
    GfMenuSequence<GfMenuObjShop, 8> m_seq;  // 0x248 (the constructor stores its owner at 0x4C0)
    // seqIntervalSleep's countdown: a zero count starts at 1 (the name is not the original's)
    int m_sleepInterval;  // 0x4D8
    // a sequence job's first step is done (seqWaitSleepFade's fade, seqItemGet's call context); the constructor
    // clears it (the name is not the original's)
    bool m_seqStarted;  // 0x4DC
    unsigned char pad_4DD[0x4E0 - 0x4DD];
    // seqEnd hands them to the main layer's call context when the result is set (the names are not the original's)
    unsigned int m_result;  // 0x4E0
    int m_resultParam;  // 0x4E4
    unsigned char pad_4E8[0x4F8 - 0x4E8];
    // a UI object seqEndDialog closes with event 0x42 when it is set (the name is not the original's)
    unsigned int m_dialog;  // 0x4F8
    unsigned char pad_4FC[0x500 - 0x4FC];
    // seqItemGet shows the got items only when it is 1 (the name is not the original's)
    int m_itemGetState;  // 0x500
    unsigned char pad_504[0x570 - 0x504];
    // the blade weapon menu's call context (seqWaitLoadBlWeapon, seqWaitEndBlWeapon; the name is not the original's)
    GfMenuCallContext* m_blWeaponContext;  // 0x570
    // the constructor creates it; seqItemGet opens the got-item text with it (the name is not the original's)
    GfMenuCallContext* m_callContext;  // 0x578
    // refreshStock adds it to "LAY_stock_num"'s y position (the name is not the original's)
    int m_stockNumOffsetY;  // 0x580
    // later fields (from the constructor): 0x4F0 pointer, 0x504 int -1, 0x508..0x540 eight pointers, 0x548
    // QuestTaskParam, 0x568 int, 0x570 pointer, 0x578 GfMenuCallContext*, 0x584 int, 0x588 short
};
}  // namespace gf

#endif

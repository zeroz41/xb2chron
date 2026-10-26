#ifndef CLASSES_GF_GFMENUOBJDRKIZUNARING_H
#define CLASSES_GF_GFMENUOBJDRKIZUNARING_H

#include "classes/gf/GfMenuObject.h"
#include "gf/GfMenuSequence.h"
#include "mm/mtl/FixStr.h"
#include "classes/gf/GfMenuSkillAdapter.h"
#include "classes/ui/UIObjectAcc.h"
#include "classes/ui/UIManager.h"
#include "classes/gf/GfMenuCharDataAdapter.h"
#include "classes/gf/GfMenuReference.h"
#include "gf/GfDataDriverSkill.h"
#include "gf/GfMenuObjUtil.h"
#include "ui/EventData.h"

namespace gf { class GAME_VOICE_HANDLE; class GfMenuCallContext; class GfMenuItemList; }
namespace ui { class UIObjectAcc; class UISelectObjList; class UICtrlFrame; }

namespace gf {
// table 0x7100B61B50
class GfMenuObjDrKizunaRing : public ::gf::GfMenuObject {
public:
    class DriverStockSPListener;
    class MainListener;
    class RingListener;
    class RingPadListener;
    class SkillDetailListener;
    GfMenuObjDrKizunaRing(unsigned int handle);
    virtual ~GfMenuObjDrKizunaRing();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
    // 1.0.0's helpers (out of line there), inlined into their callers in 3.0.1
    // the driver's SP number (1.0.0 made the adapter by hand; 3.0.1's code calls createFromReferenceDriver)
    static void setupMain(ui::UIObjectAcc& acc) {
        GfMenuCharDataAdapter::createFromReferenceDriver(acc.searchChild("TXT_drst_spnum_S24_L1H10"), 0x1A, 0, true);
    }
    static void setupCircle(ui::UIObjectAcc& acc, unsigned int level) {}  // empty in 1.0.0
    // how many of the driver's three skill levels are unlocked (stops at the first locked one)
    static unsigned int getSkillUnlockLevel(unsigned int driver) {
        bool round = GfMenuReference::getReferenceNumber(2) != 0;
        if (!GfDataDriverSkill::isSkillLevelUnlock(driver, 1, round)) {
            return 0;
        }
        if (!GfDataDriverSkill::isSkillLevelUnlock(driver, 2, round)) {
            return 1;
        }
        if (!GfDataDriverSkill::isSkillLevelUnlock(driver, 3, round)) {
            return 2;
        }
        return 3;
    }
    static int setFadeIn(unsigned int handle) {
        GfMenuObjUtil::PresetCtrlParam param;
        param.m_preset = 6;
        param.m_out = 0;
        param.m_eventId = 1;
        int ctrl = GfMenuObjUtil::startPresetCtrl(handle, param);
        GfMenuObject::hookCtrlEvent(handle, ctrl);
        return ctrl;
    }
    static int setFadeOut(unsigned int handle) {
        GfMenuObjUtil::PresetCtrlParam param;
        param.m_preset = 6;
        param.m_out = 1;
        param.m_eventId = 2;
        int ctrl = GfMenuObjUtil::startPresetCtrl(handle, param);
        GfMenuObject::hookCtrlEvent(handle, ctrl);
        return ctrl;
    }
    static void sendEvent(unsigned int handle, unsigned int type, unsigned int param) {
        ui::EventData event;
        event.m_type = type;
        event.m_param0 = param;
        ui::UIManager::get()->requestObjectEvent(handle, event, 0.0f);
    }
    static bool isLockPos(int pos) { return pos % 6 == 0; }
    static bool isScreenLR(unsigned int pos) { return pos < 3; }
    static void setupRing(ui::UIObjectAcc& acc);
    static void setupRingList(ui::UIObjectAcc& acc, ui::UISelectObjList* list);
    static void refreshRing(ui::UIObjectAcc& acc);
    static void movePointer(unsigned int handle, int index, ui::UISelectObjList* list);
    static void setupSkillDetail(ui::UIObjectAcc& acc);
    // 1.0.0's (out of line there), inlined into DriverStockSPListener::reciveEvent in 3.0.1: the driver's SP texts
    static void setupDriverSkillInfo(ui::UIObjectAcc& acc) {
        mm::mtl::FixStr<32> name;
        name.format("TXT_dr_spnum_S20_L1H2@%02d", 1);
        GfMenuSkillAdapter::createFromReferenceDriver(acc.searchChild(name.m_str), 8, 0, 0, 1, 2, true);
        name.format("TXT_dr_spnummax_S20_L1H2@%02d", 1);
        GfMenuSkillAdapter::createFromReferenceDriver(acc.searchChild(name.m_str), 9, 0, 0, 1, 2, false);
    }
    bool seqWait();
    bool seqSkillAnime();
    bool seqUnlockAnime();
    bool seqCircleAnime();
    bool seqOpenAnime();
    bool seqExecSkill();
    bool seqComplete();
    bool seqEndAnime();

    // the names below are not the original's
    ui::UISelectObjList* m_ringList;     // initialize's
    ui::UICtrlFrame* m_ringFrame;        // RingListener's frame over the ring list
    bool m_detailOpen;                   // SkillDetailListener toggles it
    int m_unlockLevel;                   // RingListener: the selected line's unlocked level (0: none)
    unsigned int m_selected;             // the ring list's selection (-1: none)
    GfMenuCallContext* m_subContext;     // initialize's; RingPadListener's call context
    GfMenuCallContext* m_context;        // initialize's
    unsigned char pad_58[8];
    int m_round;                         // GfMenuReference number 2 / isSkillLevelUnlock's round flag
    GfMenuSequence<GfMenuObjDrKizunaRing, 8> m_seq;
    int m_step;                          // the seq* functions' step
    GfMenuCallContext* m_callContext;    // initialize's; seqComplete's openGetItem
    GfMenuItemList* m_itemList;          // initialize's
    GAME_VOICE_HANDLE* m_voice;
    unsigned int pad_318;
};
}  // namespace gf

#endif

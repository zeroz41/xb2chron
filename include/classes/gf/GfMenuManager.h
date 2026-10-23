#ifndef CLASSES_GF_GFMENUMANAGER_H
#define CLASSES_GF_GFMENUMANAGER_H

#include "classes/gf/IQuestEvent.h"
#include "classes/mm/mtl/PtrSingleton.h"
#include "classes/ui/UIUpdateCallback.h"

namespace gf { class GfSetupParam; }
namespace fw { class UpdateInfo; }
namespace fw { class UpdateInfo; }
namespace gf { class GF_OBJ_HANDLE; }
namespace gf { class GfMenuManager; }
namespace gf { class QuestChangeParam; }
namespace gf { class QuestCompleteChildParam; }
namespace gf { class QuestCompleteParam; }
namespace gf { class QuestOrderParam; }
namespace gf { class QuestStateParam; }
namespace gf { class QuestTaskParam; }
namespace gf { enum GEV : int; }
namespace ui { class EventData; }

namespace gf {
// a base of gf::GfMenuManager no evidence names yet
class TUnk_B5EA58 {
public:
    virtual ~TUnk_B5EA58();
    virtual void vf2();
    virtual void vf3();
    virtual void vf4();
    virtual void vf5();
    virtual void vf6();
    virtual void vf7();
    virtual void vf8();
    virtual void vf9();
    virtual void vf10();
    virtual void vf11();
    virtual void vf12();
    virtual void vf13();
    virtual void vf14();
    virtual void vf15();
    virtual void vf16();
    virtual void vf17();
    virtual void vf18();
    virtual void vf19();
    virtual void vf20();
    virtual void vf21();
    virtual void vf22();
    virtual void vf23();
    virtual void vf24();
    virtual void vf25();
    virtual void vf26();
    virtual void vf27();
    virtual void vf28();
    virtual void vf29();
    virtual void vf30();
    virtual void vf31();
    virtual void vf32();
    virtual void vf33();
    virtual void vf34();
    virtual void vf35();
    virtual void gevPlayEvent(gf::GEV, unsigned int) = 0;
    virtual void vf37();
    virtual void vf38();
    virtual void gevCameraControl(unsigned int) = 0;
    virtual void gevChangeTarget(gf::GF_OBJ_HANDLE*) = 0;
    virtual void gevAccessTarget(gf::GF_OBJ_HANDLE*) = 0;
    virtual void vf42();
    virtual void gevBattleStart() = 0;
    virtual void vf44();
    virtual void vf45();
    virtual void vf46();
    virtual void gevSalvageStateChange(unsigned int) = 0;
    virtual void vf48();
    virtual void vf49();
    virtual void vf50();
    virtual void vf51();
    virtual void vf52();
    virtual void vf53();
    virtual void vf54();
    virtual void vf55();
    virtual void vf56();
    virtual void vf57();
    virtual void vf58();
    virtual void vf59();
    virtual void vf60();
    virtual void vf61();
    virtual void vf62();
};
// a base of gf::GfMenuManager no evidence names yet
class TUnk_B5ECD0 {
public:
    virtual void reciveEvent(ui::EventData const&, unsigned int) = 0;
};
// table 0x7100B5E990; base at 0x8 unknown (TUnk_B5EA58), base at 0x18 unknown (TUnk_B5ECD0)
class GfMenuManager : public ::mm::mtl::PtrSingleton< ::gf::GfMenuManager>, public TUnk_B5EA58, public ::gf::IQuestEvent, public TUnk_B5ECD0, public ::ui::UIUpdateCallback {
public:
    static void build(const GfSetupParam& param);
    static void destroy();
    static bool isInitialized();
    static void update(const fw::UpdateInfo& info);
    void postUpdate(const fw::UpdateInfo& info);
    enum OBJ : int;
    virtual ~GfMenuManager();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
    virtual void vf3();  // slot 3
    virtual void gevAccessTarget(gf::GF_OBJ_HANDLE*);  // slot 4
    virtual void gevChangeTarget(gf::GF_OBJ_HANDLE*);  // slot 5
    virtual void gevCameraControl(unsigned int);  // slot 6
    virtual void gevBattleStart();  // slot 7
    virtual void vf8();  // slot 8
    virtual void gevPlayEvent(gf::GEV, unsigned int);  // slot 9
    virtual void gevSalvageStateChange(unsigned int);  // slot 10
    virtual void vf11();  // slot 11
    virtual void vf12();  // slot 12
    virtual void vf13();  // slot 13
    virtual void vf14();  // slot 14
    virtual void qevOrderQuest(gf::QuestOrderParam const&);  // slot 15
    virtual void qevCompleteQuest(gf::QuestCompleteParam const&);  // slot 16
    virtual void qevChangeTaskState(gf::QuestTaskParam const&);  // slot 17
    virtual void qevLoadTaskState(unsigned int);  // slot 18
    virtual void qevCompleteChildQuest(gf::QuestCompleteChildParam const&);  // slot 19
    virtual void qevChangeQuestState(gf::QuestStateParam const&);  // slot 20
    virtual void qevChangeCurrentQuest(gf::QuestChangeParam const&);  // slot 21
    virtual void beginUpdate(fw::UpdateInfo const&);  // slot 22
    static bool isBattleState(unsigned int);
    // the object the menu targets, -1 without a manager or a target
    static GF_OBJ_HANDLE* getTargetObjHandle();
    static bool isOpenFullScreen();
    static bool isSwitchingFullScreen();  // the full screen is switching its layers
    // the object the player can access now, (GF_OBJ_HANDLE*)-1 for none
    static gf::GF_OBJ_HANDLE* getAccessObjHandle();
    static bool isFieldHudInputEnable();  // not while GfMenuObjTutorial waits
    // the battle model view (GfChainAttack's setup opens it and waits for it, destroy closes it)
    static void openBtlModelView();
    static void closeBtlModelView();
    static bool isOpenBtlModelView();
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because it reads the manager's
    // own singleton (GfMenuManager::get()) and lives in its unit. What it does: the byte at 0x4102 of the manager as
    // a bool, false without a manager; GfMenuObjOpeningTelop's open/close calls send nothing while it holds, and
    // GfMenuObjStaffroll::update tests it.
    static bool fn_710035A738();
};
}  // namespace gf

#endif

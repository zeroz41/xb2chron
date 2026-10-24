#ifndef CLASSES_GF_GFMENUMANAGER_H
#define CLASSES_GF_GFMENUMANAGER_H

#include "classes/gf/IQuestEvent.h"
#include "classes/mm/mtl/PtrSingleton.h"
#include "classes/ml/fixed_size_alloc_inside.h"
#include "classes/ui/UIUpdateCallback.h"

namespace mm { struct Col4; }
namespace gf { class GfSetupParam; }
namespace gf { class MenuCommonWindowParam; }
namespace fw { class UpdateInfo; }
namespace fw { class UpdateInfo; }
namespace gf { class GF_OBJ_HANDLE; }
namespace gf { class GfMenuManager; }
namespace gf { class GfMenuCallContext; class SDataOption; }
namespace gf { enum GEV : int; class MapjumpCallbackInfo; class QuestCompleteParam; class QuestCompleteChildParam; }
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
    GfMenuManager(const GfSetupParam& param);
    static void build(const GfSetupParam& param);
    static void destroy();
    void finalize();
    // the gamma of both the layer and the scene renderer: value * 2 + 1.2 (applyOptionData passes the option's
    // 0..255 setting / 255)
    static void applyGammaCorrectValue(float value);
    static bool isInitialized();
    static bool isFading();  // a fade of layer 0, 1 or 2 runs
    static bool isFading(unsigned int layer);  // the fade of that layer runs
    static void update(const fw::UpdateInfo& info);
    void postUpdate(const fw::UpdateInfo& info);
    // the elements of the manager's fixed_size_alloc_inside<OBJ, 512>: the constructor places 512 of 0x20 bytes
    // (0x4000) before the in-use bits
    struct OBJ {
        unsigned char pad_0[0x20];
    };
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
    static bool isEnableQuestOpen();
    static void openFullScreen(unsigned int screen, bool flag0, bool flag1);
    static void closeFullScreen(bool flag0, bool flag1);
    static void openMenu(unsigned int menu);
    static void openChapterTelop(unsigned char chapter);
    static void openChapterEndTelop(unsigned char chapter);
    static bool isOpenChapterTelop();  // the chapter end telop waits on it too
    static void openZoneTelop(unsigned short zone);
    static bool isOpenZoneTelop();
    static void openDummyTutorial(unsigned char tutorial);
    static bool isOpenDummyTutorial();
    static bool isOpenPreciousWindow();
    static void openPreciousWindow(unsigned short id);
    static void openSave();
    // the common (message) window: open by message id or from a full parameter set; its result once closed
    static void openCommonWindow(unsigned short id);
    static void openCommonWindow(const MenuCommonWindowParam& param);
    static bool isOpenCommonWindow();
    static void closeCommonWindow();
    static int getCommonWindowResult();
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
    static void getFadeColor(unsigned int layer, mm::Col4& color);
    static void initOptionData(SDataOption& option);
    static bool isRegionJP();  // the constructor sets it when menu_ira/font/bf2.wisty exists
    static unsigned int getRegion();
    static bool isRegionUS();  // getRegion() is 1
    static void setEnableQuestOpen(bool enable);
    static float getUpdateDT();
    static unsigned int getCurCameraType();  // the type gevCameraControl last passed
    static unsigned int getLatestCommonWinID();  // the id openCommonWindow last opened
    static void openNameSelect();
    static bool isOpenNameSelect();
    static void openOpeningTelop();
    static void closeOpeningTelop();
    static void openStaffroll();
    static void closeStaffroll();
    static void acceptAccess(GF_OBJ_HANDLE* handle);
    static void setDispAll(bool disp);
    // (field names follow the 1.0.0 accessors that read them; where marked, the name is not the original's)
    ::ml::fixed_size_alloc_inside<OBJ, 512> m_objs;  // 0x28 (the name is not the original's)
    bool m_initialized;     // 0x4090: every accessor tests it (the name is not the original's)
    bool m_locked;  // 0x4091: getFadeColor, setDispAll and isDispHud do nothing while it holds (the name is not the original's)
    unsigned char pad_4092[0x26];
    GF_OBJ_HANDLE* m_targetObjHandle;  // 0x40B8 getTargetObjHandle
    GF_OBJ_HANDLE* m_accessObjHandle;  // 0x40C0 getAccessObjHandle
    unsigned char pad_40C8[0x4];
    unsigned int m_curCameraType;  // 0x40CC getCurCameraType, gevCameraControl
    GfMenuCallContext* m_callContext;  // 0x40D0 the common window's and telops' (the name is not the original's)
    int m_commonWindowResult;  // 0x40D8 getCommonWindowResult
    unsigned char pad_40DC[0x1C];
    float m_updateDT;  // 0x40F8 getUpdateDT
    unsigned char pad_40FC[0x1];
    bool m_openBtlModelView;  // 0x40FD isOpenBtlModelView
    bool m_openNameSelect;  // 0x40FE isOpenNameSelect, openNameSelect sets it
    bool m_openOpeningTelop;  // 0x40FF openOpeningTelop sets it (the name is not the original's)
    bool m_hideAll;  // 0x4100 setDispAll stores !disp (the name is not the original's)
    bool m_enableQuestOpen;  // 0x4101 isEnableQuestOpen, setEnableQuestOpen
    unsigned char pad_4102[0xA];
    unsigned int m_region;  // 0x410C getRegion; the constructor sets 1 without bdat/jp.bin (the name is not the original's)
    unsigned char pad_4110[0x1];
    bool m_regionJP;  // 0x4111 isRegionJP
    unsigned char pad_4112[0x52];
    unsigned int m_latestCommonWinID;  // 0x4164 getLatestCommonWinID, openCommonWindow
    unsigned char pad_4168[0x258];
};
}  // namespace gf

#endif

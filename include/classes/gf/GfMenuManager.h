#ifndef CLASSES_GF_GFMENUMANAGER_H
#define CLASSES_GF_GFMENUMANAGER_H

#include "classes/gf/IGfEvent.h"
#include "classes/gf/IQuestEvent.h"
#include "mm/mtl/Bitflag.h"
#include "classes/mm/mtl/PtrSingleton.h"
#include "classes/ml/fixed_size_alloc_inside.h"
#include "classes/ui/UIUpdateCallback.h"
#include "classes/gf/GfGmkLocatorAtlas.h"
#include "mm/mtl/FixedVector.h"

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
// a base of gf::GfMenuManager no evidence names yet
class TUnk_B5ECD0 {
public:
    virtual void reciveEvent(ui::EventData const&, unsigned int) = 0;
};
// table 0x7100B5E990; base at 0x8 gf::IGfEvent, base at 0x18 unknown (TUnk_B5ECD0)
class GfMenuManager : public ::mm::mtl::PtrSingleton< ::gf::GfMenuManager>, public ::gf::IGfEvent, public ::gf::IQuestEvent, public TUnk_B5ECD0, public ::ui::UIUpdateCallback {
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
    virtual void gevMapjump(gf::GEV, gf::MapjumpCallbackInfo const&);  // slot 3 (1.0.0 slot 3)
    virtual void gevAccessTarget(gf::GF_OBJ_HANDLE*);  // slot 4
    virtual void gevChangeTarget(gf::GF_OBJ_HANDLE*);  // slot 5
    virtual void gevCameraControl(unsigned int);  // slot 6
    virtual void gevBattleStart();  // slot 7
    virtual void gevBattleEnd();  // slot 8 (1.0.0 slot 8)
    virtual void gevPlayEvent(gf::GEV, unsigned int);  // slot 9
    virtual void gevSalvageStateChange(unsigned int);  // slot 10
    virtual void gevPlayerControl(gf::GEV);  // slot 11 (IGfEvent slot 10)
    virtual void gevItemAdd(unsigned int, int);  // slot 12 (IGfEvent slot 20)
    virtual void gevChangeParty();  // slot 13 (IGfEvent slot 34)
    virtual void gevChangeScenarioFlag(unsigned int, unsigned int);  // slot 14 (IGfEvent slot 45)
    virtual void qevOrderQuest(gf::QuestOrderParam const&);  // slot 15
    virtual void qevCompleteQuest(gf::QuestCompleteParam const&);  // slot 16
    virtual void qevChangeTaskState(gf::QuestTaskParam const&);  // slot 17
    virtual void qevLoadTaskState(unsigned int);  // slot 18
    virtual void qevCompleteChildQuest(gf::QuestCompleteChildParam const&);  // slot 19
    virtual void qevChangeQuestState(gf::QuestStateParam const&);  // slot 20
    virtual void qevChangeCurrentQuest(gf::QuestChangeParam const&);  // slot 21
    virtual void beginUpdate(fw::UpdateInfo const&);  // slot 22
    // Placeholder names below: new in 3.0.1, nothing in 1.0.0's place names them. Static members: each reads or
    // writes the manager's own singleton (GfMenuManager::get()) and lives in its unit.
    static bool fn_71003596C0();  // m_optionFlag, false without a manager (GfMenuObjOption's listeners, GfGameUtilSaveData::flushOptionSaveData)
    static void fn_7100359EA0();  // clears m_latestCommonWinID while m_initialized
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because its address is in
    // gf_menu_manager's unit and it reads the manager singleton. What it does: when the manager exists,
    // GfMenuObjUtil::fn_710048FD30(3) answers true, its 256-entry ushort list at 0x41A8 (count 0x43A8) is not full,
    // fn_710024DAB0(id) is nonzero and GfDataBlade::fn_710024DE6C(id) answers true, appends the id to that list.
    // Caller: the fld plugin's setNpcMeet when the id's flag changed.
    static void fn_710035A764(unsigned int id);
    static int fn_710035A364();  // m_titleValue, 0 without a manager (one caller, fn_710066AA7C)
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because it sits among
    // GfMenuManager's functions in gf_menu_manager's unit and reads the manager singleton. What it does: false
    // without a manager; else opens the given menu id (TUnk_B64C98::fn_7100487A1C / fn_71004879F0 when
    // GfMenuObjUtil::fn_710048FD30(3) holds, else TUnk_B60848::fn_71003B2ABC / fn_71003B2A90, creating UI layers
    // 0x12E or 0x67/0x66 when m_titleCount is 0), stores the id in m_titleCount and returns true. Caller:
    // tl::TitleStateWarning::fn_71001565A0 (id 10).
    static bool fn_710035A388(unsigned int menuId);
    static bool fn_710035A524();  // m_titleCount != 0 (tl::TitleStateWarning::fn_71001565A8, fn_71003AF924)
    static bool fn_710035A634(int index);  // m_bladeBookFlag's bit for index 0, else false (GfMenuBladeList::setupFromBook)
    static bool fn_710035A6BC();  // returns true (GfMenuObjMainMenu2's setupMainMenu and listener)
    static bool fn_710035A6CC();  // m_battleStateEnable (GfGamePad::eventInGameOpenSkipTravelMenu)
    static bool fn_710035A6F8();  // GfMenuFlag::get1(31) == 0 (GfGamePad::eventInGameOpenSkipTravelMenu)
    static void fn_710035A718(bool flag);  // stores m_evTheaterFlag (GfMenuObjEvTheater::finalize)
    static bool fn_710035A800();  // calls GfMenuObjUtil::fn_710048FD30(3), then whether m_npcMeetIds has elements
    static bool fn_710035DE04();  // m_hideAll, false without a manager or while m_locked
    static bool fn_7100359570();  // m_baseGameFlag, false without a manager or when GfGameManager::fn_71002A9E68()
    static void fn_710035DB2C();  // with GfMenuObjUtil::fn_710048FD30(1): creates ui layer 101, sets m_layer101Open
    static bool fn_710035DB80();  // m_layer101Open, false without a manager
    static void fn_710035DBAC();  // with GfGameManager::fn_71002AC64C(): creates ui layer 72, sets m_layer72Open
    static bool fn_710035DBFC();  // m_layer72Open, false without a manager
    // Placeholder names: new in 3.0.1, nothing in 1.0.0's place names them. Members because their addresses lie in
    // this class's unit and they test the manager. What they do: with a manager and GfMenuObjUtil::fn_710048FD30(1),
    // fn_710035A460 creates ui layer 102; fn_710035CE3C terminates it (terminateLayer(102, true)) and calls
    // GfMenuObjPartyGauge::fn_71004569F8().
    static void fn_710035A460();
    static void fn_710035CE3C();
    // Placeholder name: new in 3.0.1. What it does: returns gf::fn_71002229C0(4) (gf_data_aoc); callers are menu
    // objects at 0x710040BF88..0x710040E1E0.
    static int fn_710035A6C4();
    // with GfMenuObjUtil::fn_710048FD30(3): when m_layer300Open already holds calls gf::fn_71003BBB48 (camp menu),
    // else creates ui layer 300 and sets m_layer300Open
    static void fn_710035DC28();
    static bool fn_710035DC94();  // m_layer300Open, false without a manager
    static bool fn_710035DCC0();  // gf::fn_71003BBB38() == 1 (camp menu)
    static void fn_710035DD3C();  // with GfMenuObjUtil::fn_710048FD30(3): GfMenuObjMainMenu2::registOpenParam({0})
    static void fn_710035DD6C();  // with GfMenuObjUtil::fn_710048FD30(3): GfMenuObjMainMenu2::registOpenParam({3})
    static void setMainmenuOpenMap();
    static void setMainmenuOpenSystem();
    static bool isBattleState(unsigned int);
    static void setBattleState(unsigned int state, bool on);
    static void applyOptionData(const SDataOption& option);
    static bool isClearCheck();  // tl::TitleMain's clear flag, false without a TitleMain
    static bool isDispHud(int hud);  // false while m_locked; garbage without a manager, as the original
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
    // Placeholder name: new in 3.0.1 (1.0.0's GfFieldGrave::create calls openCommonWindow(unsigned short) in its
    // place, with one argument). A static member: its unit is gf_menu_manager and it reads the singleton.
    // What it does: when the manager exists, its byte at 0x4090 is set and m_callContext is there, it resets the
    // call context, passes it id and arg (fn_71003E1F60) and keeps id at 0x4164. gf::GfFieldGrave::create passes
    // 51 and the grave row's GmkGrave::BdatInfo::m_windowArg.
    static void fn_7100359CD8(unsigned short id, unsigned short arg);
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
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it (1.0.0's GfMenuObjTitle::initialize shows
    // no version). A member because it reads the manager's own singleton and lives in its unit. What it does:
    // "2.0.1" when GfGameManager::fn_71002A9E68() answers true and the manager is missing or not m_regionJP, else
    // the application's display version (nn::oe::GetDisplayVersion into a file static). Caller:
    // GfMenuObjTitle::initialize.
    static const char* fn_710035A660();
    // Placeholder name: the symbols leave it unnamed. A member because it reads the manager's own singleton and
    // lives in its unit. What it does: when GfMenuObjUtil::fn_710048FD30(3) answers true and the manager's
    // m_optionFlag holds, sets the option's m_soundUi.m_byte1E to whether fw::LangUtil::getLangType() is 0, 6 or 11.
    // Caller: tl::TitleStateMainScreen::loadSaveDataForTitle, on the title's option buffer after
    // GfGameUtilSaveData::setupOptionSaveData.
    static void fn_710035964C(SDataOption& option);
    // Placeholder name: the symbols leave it unnamed. A member because it reads the manager's own singleton and
    // lives in its unit. What it does: with a manager and GfMenuObjUtil::fn_710048FD30(1) true, creates ui layer
    // 103, then runs fn_710035A460 (layer 102), sets m_titleCount to 1 and answers true; false otherwise.
    // Caller: fn_71003AF9CC.
    static bool fn_710035A4A0();
    // Placeholder name: the symbols leave it unnamed. A member because it writes the manager's own singleton and
    // lives in its unit. What it does: during a map jump (GfGameManager::isMapjump) copies the atlas setup into
    // m_mapjumpAtlasInfo. Caller: GfMenuMapInfo::postUpdate, in place of GfGmkLocatorAtlas::create.
    static void fn_710035A844(const GfGmkLocatorAtlas::CreateInfo& info);
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
    bool m_targetChanged;  // 0x40C8 gevChangeTarget sets it when the target changes (the name is not the original's)
    bool m_accessChanged;  // 0x40C9 gevAccessTarget sets it when the access object changes (the name is not the original's)
    // 0x40CA setBattleState and gevBattleStart change m_battleState only while it holds; gevPlayEvent(12) clears it
    // (the name is not the original's)
    bool m_battleStateEnable;
    unsigned char pad_40CB[0x1];
    unsigned int m_curCameraType;  // 0x40CC getCurCameraType, gevCameraControl
    GfMenuCallContext* m_callContext;  // 0x40D0 the common window's and telops' (the name is not the original's)
    int m_commonWindowResult;  // 0x40D8 getCommonWindowResult
    mm::mtl::Bitflag<32> m_battleState;  // 0x40DC isBattleState, setBattleState (the name is not the original's)
    unsigned char pad_40E0[0x4];
    mm::mtl::Bitflag<32> m_dispHud;  // 0x40E4 isDispHud (the name is not the original's)
    unsigned char pad_40E8[0x10];
    float m_updateDT;  // 0x40F8 getUpdateDT
    unsigned char pad_40FC[0x1];
    bool m_openBtlModelView;  // 0x40FD isOpenBtlModelView
    bool m_openNameSelect;  // 0x40FE isOpenNameSelect, openNameSelect sets it
    bool m_openOpeningTelop;  // 0x40FF openOpeningTelop sets it (the name is not the original's)
    bool m_hideAll;  // 0x4100 setDispAll stores !disp (the name is not the original's)
    bool m_enableQuestOpen;  // 0x4101 isEnableQuestOpen, setEnableQuestOpen
    // 0x4102 fn_710035A718 stores it (GfMenuObjEvTheater::finalize), fn_710035A738 reads it (the name is not the original's)
    bool m_evTheaterFlag;
    bool m_layer101Open;  // 0x4103 fn_710035DB2C sets it after creating ui layer 101 (the name is not the original's)
    bool m_layer72Open;  // 0x4104 fn_710035DBAC sets it after creating ui layer 72 (the name is not the original's)
    bool m_layer300Open;  // 0x4105 fn_710035DC28 sets it after creating ui layer 300 (the name is not the original's)
    unsigned char pad_4106[0x6];
    unsigned int m_region;  // 0x410C getRegion; the constructor sets 1 without bdat/jp.bin (the name is not the original's)
    bool m_optionFlag;  // 0x4110 fn_71003596C0 reads it (GfMenuObjOption, flushOptionSaveData) (the name is not the original's)
    bool m_regionJP;  // 0x4111 isRegionJP
    // 0x4112 fn_7100359570 returns it unless GfGameManager::fn_71002A9E68() answers true (the name is not the original's)
    bool m_baseGameFlag;
    unsigned char pad_4113[0x1];
    bool m_bladeBookFlag : 1;  // 0x4114 fn_710035A634 reads its low bit (GfMenuBladeList::setupFromBook) (the name is not the original's)
    unsigned char pad_4115[0x4F];
    unsigned int m_latestCommonWinID;  // 0x4164 getLatestCommonWinID, openCommonWindow
    unsigned char pad_4168[0x8];
    // 0x4170 fn_710035A844 copies GfMenuMapInfo::postUpdate's atlas setup here during a map jump (the name is not
    // the original's)
    GfGmkLocatorAtlas::CreateInfo m_mapjumpAtlasInfo;
    int m_titleValue;  // 0x41A0 fn_710035A364 returns it (the name is not the original's)
    int m_titleCount;  // 0x41A4 fn_710035A524 tests it against 0 (TitleStateWarning) (the name is not the original's)
    // 0x41A8 fn_710035A764 appends the ids the fld plugin's setNpcMeet reports (fixed_vector.h's push_back asserts);
    // fn_710035A800 tests it for elements, the destructor clears it (the name is not the original's)
    mm::mtl::FixedVector<unsigned short, 256> m_npcMeetIds;
    unsigned char pad_43B0[0x10];
};
}  // namespace gf

#endif

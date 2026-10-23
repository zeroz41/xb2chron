#ifndef CLASSES_GF_GFGAMEMANAGER_H
#define CLASSES_GF_GFGAMEMANAGER_H

#include "classes/gf/IQuestEvent.h"
#include "classes/mm/mtl/PtrSingleton.h"

namespace gf { class GfSetupParam; }
namespace fw { class UpdateInfo; }
namespace gf { enum GF_STATE : int; }
namespace gf { enum ActivateType : int; }
namespace gf { class GF_OBJ_HANDLE; }
namespace gf { class GfGameManager; }
namespace gf { struct OwnerBonus; }
namespace gf { class MapjumpCallbackInfo; }
namespace gf { class QuestCompleteChildParam; }
namespace gf { class QuestCompleteParam; }
namespace gf { class QuestOrderParam; }
namespace gf { enum GEV : int; }
namespace gf { enum GF_STATE : int; }
namespace gf { enum RELOAD_BDAT : int; }

namespace gf {
// a base of gf::GfGameManager no evidence names yet
class TUnk_B54A90 {
public:
    virtual ~TUnk_B54A90();
    virtual void vf2();
    virtual void vf3();
    virtual void vf4();
    virtual void vf5();
    virtual void vf6();
    virtual void vf7();
    virtual void gevGetArts(unsigned int, unsigned int, bool) = 0;
    virtual void gevSelectHikari(bool) = 0;
    virtual void vf10();
    virtual void vf11();
    virtual void vf12();
    virtual void gevControllFree(bool) = 0;
    virtual void gevGameState(gf::GF_STATE, gf::GF_STATE) = 0;
    virtual void vf15();
    virtual void vf16();
    virtual void vf17();
    virtual void gevPartyIDMemberOK(bool, unsigned int) = 0;
    virtual void gevPartyMemberOK(bool) = 0;
    virtual void gevItemAdd(unsigned int, int) = 0;
    virtual void vf21();
    virtual void vf22();
    virtual void vf23();
    virtual void gevMercenariesMissionFlag(unsigned int, unsigned int, unsigned int) = 0;
    virtual void vf25();
    virtual void gevDriverLevel(unsigned int, unsigned int, unsigned int) = 0;
    virtual void gevDriverActivate(unsigned int, gf::ActivateType, gf::ActivateType) = 0;
    virtual void gevBladeActivate(unsigned int, gf::ActivateType, gf::ActivateType) = 0;
    virtual void gevBladeUnselect(unsigned int, bool) = 0;
    virtual void gevBladeEnable(unsigned int) = 0;
    virtual void vf31();
    virtual void gevGameObjEnter(gf::GF_OBJ_HANDLE*) = 0;
    virtual void gevGameObjLeave(gf::GF_OBJ_HANDLE*) = 0;
    virtual void vf34();
    virtual void gevChangeBlade(gf::GF_OBJ_HANDLE*, int, int) = 0;
    virtual void gevPlayEvent(gf::GEV, unsigned int) = 0;
    virtual void gevPause(unsigned int, unsigned int) = 0;
    virtual void gevLayerPause(unsigned int, bool) = 0;
    virtual void vf39();
    virtual void vf40();
    virtual void vf41();
    virtual void gevMapjump(gf::GEV, gf::MapjumpCallbackInfo const&) = 0;
    virtual void vf43();
    virtual void vf44();
    virtual void vf45();
    virtual void vf46();
    virtual void gevSalvageStateChange(unsigned int) = 0;
    virtual void vf48();
    virtual void gevChangeWeather(unsigned int, unsigned int) = 0;
    virtual void gevChangeTimeRange(unsigned int) = 0;
    virtual void vf51();
    virtual void gevReloadBdat(gf::RELOAD_BDAT, unsigned int) = 0;
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
// table 0x7100B54938; base at 0x8 unknown (TUnk_B54A90)
class GfGameManager : public ::mm::mtl::PtrSingleton< ::gf::GfGameManager>, public TUnk_B54A90, public ::gf::IQuestEvent {
public:
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member: its code is in gf_game_manager's unit
    // and GfManager::fn_710032A958 calls it on GfGameManager's instance. What it does: when PtrSingleton<gf::GfGameScene>'s
    // instance exists, calls fn_71002CC060 on it (the update info passed on unused); the info is TitleApplet's per-frame one
    void fn_71002AC9C0(const fw::UpdateInfo& info);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member: its code is in gf_game_manager's unit
    // among GfGameManager's functions. What it does: when the instance at lbl_7100C23300 exists, passes it and its bool to
    // fn_71002A7430 (as GfGameManager::setupGame does); GfManager::fn_710032A1FC calls it
    static void fn_71002AC558(bool flag);
    static void build(const GfSetupParam& param);
    static void destroy();
    static void setState(GF_STATE state, bool flag);
    static void leaveGameForDebug();
    static void destroyBattleEnemy();
    static bool isField();
    static void enterBattle(bool flag);
    static bool isStopBattleSequence();
    void update(const fw::UpdateInfo& info);
    void postUpdate(const fw::UpdateInfo& info);
    void updateParam(const fw::UpdateInfo& info);
    virtual ~GfGameManager();  // slot 0
    static gf::GF_OBJ_HANDLE* getPartyLeader();
    static gf::GF_OBJ_HANDLE* getControlMover();  // the object the player controls
    static gf::GF_OBJ_HANDLE* getPartyLeaderDriver();
    // whether an event is playing; with sequential, a sequential play's inner event state counts too
    static bool isEvent(bool sequential);
    // whether the player is in a talk (a forced one, or the game state's talk flag)
    static bool isTalking();
    static int getMapID();
    // the map a jump goes to (GfGameEnv's int at 0x10; GfFieldZoneScript::execScript names its script from it)
    static unsigned int getMapJumpID();
    static int getScenarioId();  // the chapter GfMenuGameAdapter::update_Chapter shows
    static bool isPlaySequenceClear();
    static bool isPlayerCameraPause();
    // the owner bonuses the party's precious items add up to (GfGameScene's)
    static const gf::OwnerBonus* getOwnerBonus();
    // whether the PC may access objects on the field now
    static bool isEnableFieldAccess();
    static bool isRoom();
    static bool isFadeout();
    static bool isStartGame();
    static bool isLeaveGameForDebug();
    static bool isControlFree();
    static bool isScenarioGame();
    static bool isGmkTutorialOK();
    static bool isTalkOK();
    static bool isEnablePlayerDeadSequence();
    static void setGmkTutorialSequenceOK(bool ok);
    static bool isBattle();
    // the game's state (GfGameState::getState's: this only forwards to it; GfGameSalvage::startSalvage starts only in
    // state 11)
    static GF_STATE getState();
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because its address is in this
    // file among GfGameManager's functions (every named function of the unit is GfGameManager's or IQuestEvent's
    // inline virtuals). What it does: whether the game runs in the mode the title screen switches on: true when
    // gf_game_env.cpp's 3.0.1 singleton (lbl_7100C23300: 0x10 bytes, class tables lbl_7100B54858/lbl_7100B54878,
    // created by fn_71002A752C from initialize) exists and its int at 0x8 is 1. Only fn_71002AC558(flag & 1)
    // writes that int; it is reached from title_main.cpp's fn_7100156288 through fn_710014FDB8 and gf_manager.cpp's
    // fn_710032A1FC, which hands the same flag to fw::Framework (byte 0x459), fw::EffectManager (0x2FD8),
    // fw::SoundManager (0x44C8), the render DrSys parameters and GfDataGame (bit 0 of 0xFD6D0). GfMenuManager's
    // constructor tests it right after registering menu layer 3 for "menu_ira" (see GfMenuObjUtil::fn_710048FD30).
    // "Ira" in those paths suggests the Torna expansion's mode; that is inferred, not a name. 269 callers.
    static bool isClearGame();  // the game has been cleared once (the story's end reached)
    static bool fn_71002A9E68();
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it (1.0.0's
    // GfGamePlayerUniqueScheduler::update calls isBattle() where 3.0.1 calls this). A static of GfGameManager because
    // gf_game_manager.cpp's functions fill its unit. What it does: true while an event of type 2 or more plays
    // (GfGameEvent::getPlayEventId through GfDataEvent::getEventType), while the fade is not clear
    // (GfGameManager::isFadeClear), or while GfGameScene's battle bit (0x148 bit 1, GfGameScene::isBattle) is set;
    // false when there is no GfGameScene. Its only caller is GfGamePlayerUniqueScheduler::update, which skips the
    // scheduler while it is true.
    static bool fn_71002AC70C();
    static void clear();
    // takes fn_71002A9E68()'s answer in 3.0.1 (every caller passes it; the symbols still spell 1.0.0's setupGame())
    static void setupGame(bool flag);
    virtual void vf2();  // slot 2
    virtual void vf3();  // slot 3
    virtual void vf4();  // slot 4
    virtual void vf5();  // slot 5
    virtual void vf6();  // slot 6
    virtual void vf7();  // slot 7
    virtual void gevGetArts(unsigned int, unsigned int, bool);  // slot 8
    virtual void gevDriverLevel(unsigned int, unsigned int, unsigned int);  // slot 9
    virtual void gevSelectHikari(bool);  // slot 10
    virtual void vf11();  // slot 11
    virtual void vf12();  // slot 12
    virtual void gevPause(unsigned int, unsigned int);  // slot 13
    virtual void gevChangeBlade(gf::GF_OBJ_HANDLE*, int, int);  // slot 14
    virtual void gevMapjump(gf::GEV, gf::MapjumpCallbackInfo const&);  // slot 15
    virtual void gevGameObjEnter(gf::GF_OBJ_HANDLE*);  // slot 16
    virtual void gevGameObjLeave(gf::GF_OBJ_HANDLE*);  // slot 17
    virtual void gevDriverActivate(unsigned int, gf::ActivateType, gf::ActivateType);  // slot 18
    virtual void gevBladeActivate(unsigned int, gf::ActivateType, gf::ActivateType);  // slot 19
    virtual void gevBladeUnselect(unsigned int, bool);  // slot 20
    virtual void gevBladeEnable(unsigned int);  // slot 21
    virtual void gevPlayEvent(gf::GEV, unsigned int);  // slot 22
    virtual void gevPartyMemberOK(bool);  // slot 23
    virtual void gevPartyIDMemberOK(bool, unsigned int);  // slot 24
    virtual void gevItemAdd(unsigned int, int);  // slot 25
    virtual void gevLayerPause(unsigned int, bool);  // slot 26
    virtual void gevReloadBdat(gf::RELOAD_BDAT, unsigned int);  // slot 27
    virtual void gevSalvageStateChange(unsigned int);  // slot 28
    virtual void vf29();  // slot 29
    virtual void vf30();  // slot 30
    virtual void gevChangeWeather(unsigned int, unsigned int);  // slot 31
    virtual void gevChangeTimeRange(unsigned int);  // slot 32
    virtual void gevGameState(gf::GF_STATE, gf::GF_STATE);  // slot 33
    virtual void gevControllFree(bool);  // slot 34
    virtual void gevMercenariesMissionFlag(unsigned int, unsigned int, unsigned int);  // slot 35
    virtual void vf36();  // slot 36
    virtual void vf37();  // slot 37
    virtual void qevOrderQuest(gf::QuestOrderParam const&);  // slot 38
    virtual void qevCompleteQuest(gf::QuestCompleteParam const&);  // slot 39
    virtual void qevCompleteChildQuest(gf::QuestCompleteChildParam const&);  // slot 40
};
}  // namespace gf

#endif

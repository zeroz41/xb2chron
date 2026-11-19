#ifndef CLASSES_GF_GFGAMEMANAGER_H
#define CLASSES_GF_GFGAMEMANAGER_H

#include "classes/gf/IGfEvent.h"
#include "classes/gf/IQuestEvent.h"
#include "classes/mm/mtl/PtrSingleton.h"
#include "mm/mtl/FixedVector.h"
#include "gf/ArenaMenuInfo.h"

namespace gf { class GfSetupParam; }
namespace mm { class Vec3; }
namespace fw { class UpdateInfo; }
namespace gf { enum GF_STATE : int; }
namespace gf { enum GAME_TYPE : int; }
namespace gf { enum ActivateType : int; }
namespace gf { class GF_OBJ_HANDLE; }
namespace gf { class GfGameManager; }
namespace mm { namespace mtl { template <typename, unsigned long> class FixedArray; }}
namespace gf { struct OwnerBonus; }
namespace gf { class MapjumpCallbackInfo; }
namespace gf { class QuestCompleteChildParam; }
namespace gf { class QuestCompleteParam; }
namespace gf { class QuestOrderParam; }
namespace gf { enum GEV : int; }
namespace gf { enum GF_STATE : int; }
namespace gf { enum RELOAD_BDAT : int; }
namespace gf { enum GfPlayerDead : int; }
namespace gf { enum GFDIFF : int; }

namespace gf {
// table 0x7100B54938; IGfEvent at 0x8 (1.0.0's table names the overrides), IQuestEvent at 0x10
class GfGameManager : public ::mm::mtl::PtrSingleton< ::gf::GfGameManager>, public ::gf::IGfEvent, public ::gf::IQuestEvent {
public:
    GfGameManager() : m_initialized(false), m_leaveGameForDebug(false) {}
    static void setStartGame();
    static bool isEnableRoomForHikariLv4();
    static void setStopMainMenuOpenForGimmick(bool stop);
    static bool isValidCollisionVelocity();
    // whether a map jump may start (neither the state nor the reserved one is 8 or 9)
    static bool isMapjumpOK();
    static bool isElevatorMoveOK(unsigned short lodId);
    // GfGameScene has player stop flag 1, 3, 4 or 5 set (false without a GfGameScene)
    static bool isGmkTutorialSequenceOK();
    // not in battle, not in theater mode, and the control is free
    static bool isAutoTalkOK();
    // 2.0.0's symbols name it: BattleManager::CheckGameOver calls it in both builds (2.0.0's uncalled
    // isQuestCompleteUI has the same code). What it does: whether a GfPlayComQuestCompleteUI is alive.
    static bool isExecCompleteUI();
    static bool isEnableBattouWithHoodHomura(bool flag);
    // the leader may not draw its weapon (a blade reset plays, the first blade rebuilds, or isEnableBattouWithHoodHomura(true))
    static bool isDisableBattou();
    // whether the fade of that layer runs (or SCOM type 27 is queued); -1 asks layers 0, 1 and 2
    static bool isFading(unsigned int layer);
    // the pad's characters: the controlled mover first
    static void collectPadCharList(mm::mtl::FixedArray<gf::GF_OBJ_HANDLE*, 2>* list);
    static void setValidCollisionVelocity(bool valid);
    // SCOM_ACCESS_TARGET and SCOM_TARGET_UI pass their request's object
    static void setAccessTarget(gf::GF_OBJ_HANDLE* handle);
    static void setTargetUI(gf::GF_OBJ_HANDLE* handle);
    // 2.0.0's symbols name it. What it does: when PtrSingleton<gf::GfGameScene>'s instance exists, calls
    // updateAfterLayer on it (the update info passed on unused); the info is TitleApplet's per-frame one
    void updateAfterLayer(const fw::UpdateInfo& info);
    // 2.0.0's symbols name it. What it does: copies the Vec3 into the static Vec3 getControlMoverPosition falls back on
    // (guard 0x7100D6CC00, first set to mm::Vec3::zero); TitleStatePlayEvent::gevPlayEvent passes gf::GfInfo::m_camPos
    // (GEV 0xE) and mm::Vec3::zero (GEV 0xD).
    static void setControlMoverPositionForNoPlayer(const mm::Vec3& pos);
    // 2.0.0's symbols name it. What it does: when the instance the pointer at 0x7100B94428 holds exists, tail-calls
    // isActiveArena on it (that one reads local game flag type 1 index 0xDC0D); false otherwise. 23 callers
    // (GfGameUtil::incEnemySuppress skips counting while it holds, GfFieldWeather::updateWeather,
    // GfGameScene::setEnemyDead, GfMenuBattleAdapter).
    static bool isBattleArenaActive();
    // 2.0.0's symbols name it. What it does: tail-calls GfGameUtilDiff::getBtlDifficult, the byte 0x6F into the option data
    // (tl::TitleMain's getOptionBuffer in advertize/theater mode, else GfDataManager::getDataOption()). Callers:
    // btl::BattleGlobal::PreUpdateProc, gf::GfGameUtil::getClearNamedTime (picks a record column 0/1/2/4 with it),
    // SCOM_ENBOOK_BOSS_TIME::exec.
    static unsigned int getBtlDifficult();
    // 2.0.0's symbols name it. A static member: its code is in gf_game_manager's unit among GfGameManager's functions
    // and takes no instance. What it does: when the instance the pointer at 0x7100B94428 holds exists, has
    // GfGameArena::getMenuInfo fill the record for the id and difficulty it is given and returns true; false otherwise.
    // gf_menu_btlch_adapter's callbacks pass the difficulty GfMenuReference::getReferenceBtlchDifficulty answers.
    static bool getBattleArenaMenuInfo(ArenaMenuInfo& info, unsigned int id, GFDIFF diff);
    // 2.0.0's symbols name it. What it does: returns the address 0xD8 bytes into the instance the pointer at
    // 0x7100B94428 holds (the one isBattleArenaActive asks); 12 callers (GfMenuBattleAdapter, the battle challenge
    // manager, gf_menu_obj_btl_time, gf_menu_btlch_adapter).
    static ArenaMenuInfo* getBattleArenaMenuInfo();
    // 2.0.0's symbols name it. What it does: when PtrSingleton<GfGameAoc> exists, passes it and its bool to
    // GfGameAoc::setupGame (as GfGameManager::setupGame does); GfManager::resetGameType calls it
    static void resetGameType(bool flag);
    // 2.0.0's symbols name it. What it does: tail-calls GfDataHitonowa::getFlag4Level, which returns bits 16-19 of the u32 at 0x101D08
    // of GfDataManager::getDataGame(). Callers: updateCloud2ForIra and gf_menu_obj_hitonowa's GfMenuObjHitonowa::setupGame
    // (keeps it in a file static), initialize and seqNextGet.
    static unsigned int getHitonowaLevel();
    static void build(const GfSetupParam& param);
    void initialize(const GfSetupParam& param);
    static void destroy();
    static void setState(GF_STATE state, bool flag);
    static void leaveGameForDebug();
    // whether the player is paused (StateFieldPrepareBigJump waits while it is)
    static bool isPlayerPause();
    static void destroyBattleEnemy();
    static bool isField();
    static bool isInnerState(GF_STATE state);
    static void enterBattle(bool flag);
    static bool isStopBattleSequence();
    void update(const fw::UpdateInfo& info);
    void postUpdate(const fw::UpdateInfo& info);
    void finalize();
    static float getFieldSpeed(const fw::UpdateInfo& info);
    void updateParam(const fw::UpdateInfo& info);
    virtual ~GfGameManager();  // slot 0
    static bool isGameObjEmpty();
    static bool isBladeChange();
    static bool isFullScreenMenu();
    static void setMapID(unsigned int, unsigned int);
    static bool isMapjump();
    static bool isMapjumpWithSaveData();
    static bool isAdvertize();
    static bool isPlayerDeadSequence();
    static bool isDisableAutoRun();
    static bool isRexAwakening();
    static bool isGmkTutorialMoverOK();
    static void setGmkTutorialMoverOK(bool ok);
    static GfPlayerDead getDeadType();
    static bool isForceBossBattleBgm();
    static bool isForceEventBgm();
    static bool isDisableJumpForRide();
    static void setHomuriWeaponExtraMesh(bool, float);
    static bool isPlayEnemyVoice();
    static bool isPartyMemberPlayVoice();
    static bool isEventWait();
    static bool isFieldLockMsgOK();
    static unsigned int getMapZoneID();
    static bool isPartyCreateForMapjump();
    static bool isInMetJIJI();
    static bool isEnableGimmickPhantomDamage();
    static bool isEnableGetFieldPrecious();
    static bool isEnableCreateBattleLock();
    static bool isPartyMover(gf::GF_OBJ_HANDLE* handle);
    static bool isNight();
    static bool isEnableHoodHomuraScenes();
    static bool isAssetNumberInvalid();
    static bool isEnableOpenMainMenuSequence();
    static bool isEnableOpenMainMenu();
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
    static const gf::OwnerBonus& getOwnerBonus();
    // whether the PC may access objects on the field now
    static bool isEnableFieldAccess();
    static bool isRoom();
    static bool isFadeout();
    static bool isStartGame();
    // SCOM_POPUP::exec holds popup kind 7 back while this is true
    static bool isBusyBladeCreateEvent();
    static bool isLeaveGameForDebug();
    static bool isControlFree();
    // an event plays: GfGameScene::isPlayEvent() when there is a GfGameScene (2.0.0's symbols name it; 1.0.0's
    // isPlayEvent at 0x71003196DC has the same code, and SCOM_FIELD_VOICE's stop test calls it in both)
    static bool isPlayEvent();
    static bool isScenarioGame();
    static bool isGmkTutorialOK();
    static bool isPlayEventOK();
    // the leader may show the landmark UI: control free and its target state 0/2/3/5 with no fade-out, state 1 the
    // target's m_gmkTutorialOK
    static bool isLandmarkUiOK();
    static bool isEnemyChangeBattleOK();
    // 2.0.0's symbols name it. What it does: with PtrSingleton<GfGameAoc>'s instance in mode 1, whether
    // GfDataUtil::getScenarioFlag (local flag 1, width 16) is in [11115, 11130); otherwise whether it is at least 10034
    // and its value / 64 is below 157. Callers: GfGameScene::checkFieldBladeChange / checkFieldBladeChangeForRide,
    // GfPlayFactory::createPlayerDead, GfSelectIra::update.
    static bool isGameOver();
    static bool isTalkOK();
    static bool isEnablePlayerDeadSequence();
    static void setGmkTutorialSequenceOK(bool ok);
    static bool isBattle();
    // GfGameUtil::isCondBladeModel asks it for a blade id before the blade's model condition
    static bool isChangeNormalHomuraForce(unsigned int blade);
    // whether the field target may be a battle target (GfGameTarget asks it each update)
    static bool isEnableFieldBattleTarget();
    // the game's state (GfGameState::getState's: this only forwards to it; GfGameSalvage::startSalvage starts only in
    // state 11)
    static GF_STATE getState();
    static bool isClearGame();  // the game has been cleared once (the story's end reached)
    // 2.0.0's symbols name it. What it does: whether the game runs in the mode the title screen switches on: true when
    // gf_game_env.cpp's 3.0.1 singleton (GfGameAoc: 0x10 bytes, created by build from initialize) exists and
    // its int at 0x8 is 1. Only resetGameType(flag & 1) writes that int; it is reached from title_main.cpp's update
    // through resetGameType and gf_manager.cpp's resetGameType, which hands the same flag to fw::Framework (byte
    // 0x459), fw::EffectManager (0x2FD8), fw::SoundManager (0x44C8), the render DrSys parameters and GfDataGame (bit 0
    // of 0xFD6D0). GfMenuManager's constructor tests it right after registering menu layer 3 for "menu_ira" (see
    // GfMenuObjUtil::isValidExpansion). 269 callers.
    static bool isGameTypeIra();
    // 2.0.0's symbols name it. What it does: tail-calls GfDataUtil::isVersion150 and returns its bool. Callers: GfMenuManager's
    // layer-72 opener (openNamedList), GfMenuCharDataAdapter, GfMenuObjCommonText::openWithNamed.
    static bool isEnableNamedRecord();
    // 2.0.0's symbols name it. What it does: when GfGameUtilDiff::isEnableAutoSave answers true and PtrSingleton<GfGameScene> exists, sets
    // the scene's byte at 0x8B8 to 1. Callers: seqAutoSave and the sys plugin's autoSave (no arguments).
    static void reqestEventAutoSave();
    // 2.0.0's symbols name it. What it does: false when gf_game_env.cpp's 3.0.1 singleton (GfGameAoc) does not exist,
    // else tail-calls isExistGameAoc(singleton, 0x30101) (an add-on content check). GfMenuObjUtil::isValidExpansion
    // answers its add-on menu layer 1 with it; GfMenuManager's constructor and GfGameScene::setEnemyDead call it too.
    static bool isInstalledBattleArenaContents();
    // 2.0.0's symbols name it. What it does: true while an event of type 2 or more plays (GfGameEvent::getPlayEventId
    // through GfDataEvent::getEventType), while the fade is not clear (GfGameManager::isFadeClear), or while
    // GfGameScene's battle bit (0x148 bit 1, GfGameScene::isBattle) is set; false when there is no GfGameScene. Its
    // only caller is GfGamePlayerUniqueScheduler::update, which skips the scheduler while it is true.
    static bool isDisableUnieqIdle();
    // 2.0.0's symbols name it. What it does: tail-calls gf::GfGameUtilDiff::getBtlDifParam(value) (GfWeapon's unit: the option data's
    // SSoundUiOption at +0x4C gets value through GfDataBtlDif::getBtlDifParam).
    // returns its value (btl::BattleGlobal::SetupDifficultyData reads w0 after the call)
    static unsigned int getBtlDifParam(unsigned int value);
    // 2.0.0's symbols name it. What it does: the int at 0x100 of PtrSingleton<GfGameArena>'s instance (its record's
    // m_value28), 0 when there is none.
    static unsigned int getBattleArenaScore();
    // 2.0.0's symbols name it. What it does: the int at 0x104 of PtrSingleton<GfGameArena>'s instance (its record's
    // m_value2C), 0 when there is none.
    static unsigned int getBattleArenaEtherCube();
    // 2.0.0's symbols name it. What it does: sets the byte at 0x8C0 of PtrSingleton<GfGameScene>'s instance when there
    // is one.
    static void reqestCraftPopupForIra();
    // 2.0.0's symbols name it. What it does: GfGameScene::isSepiaFilter() when there is a GfGameScene, else false.
    static bool isSepiaFilter();
    // 2.0.0's symbols name it. A static member: its code is in gf_game_manager's unit among
    // GfGameManager's functions and takes no instance. What it does: when GfGameAoc's instance exists with mode 1,
    // whether any of the party's drivers 0..2 (GfGameParty::getHandleDriver(party, n)) is in battle; else whether
    // driver 0 or the party's blade (getHandleBlade(party, -1)) is in battle, false without a driver.
    static bool fn_71002AC77C(unsigned int party);
    // 2.0.0's symbols name it. What it does: false unless GfGameAoc's instance exists, its mode is not 1 and
    // isExistGameAoc(0x30101) holds; then gf::GfGameUtilDiff::isEnableSpecialBgm() (option byte 0x84 is 0).
    static bool isEnableSpecialBgm();
    // 2.0.0's symbols name it. A static member: its code is in gf_game_manager's unit among
    // GfGameManager's functions and takes no instance. What it does: whether id is 0 or one of 30255..30258.
    static bool isEventTutorial(unsigned int id);
    // 2.0.0's symbols name it. What it does: the byte at 0x21B of PtrSingleton<tl::TitleMain>'s instance is set (false
    // without one).
    static bool isCompleteBothGame();
    // 2.0.0's symbols name it. What it does: whether the arena (GfGameArena) is in state 5 and
    // btl::ChallengeBattleManager's instance exists and either its IsResult holds or its IsWaveFinished holds with
    // btl::Utility::AI_GetEnemyNum() == 0.
    static bool isDisableFieldDamage();
    // 2.0.0's symbols name it. What it does: tail-call gf::GfGameUtilDiff::isEnableAutoBattle / GfGameUtilDiff::isEnableAutoButtonChallenge / GfGameUtilDiff::isEnableEnemyAgg (GfWeapon's
    // unit: the option data's bytes 0x7F / 0x80 / 0x81 are set).
    static bool isEnableAutoBattle();
    static bool isEnableAutoButtonChallenge();
    static bool isEnableEnemyAgg();
    // 2.0.0's symbols name it. What it does: true while GfPlayComQuestCompleteUI::s_active is above 0 or
    // PtrSingleton<GfPlayComOpenNpcEntry>'s instance exists; else GfGameScene::isOpenPreciousMenu() when there is a
    // GfGameScene, false otherwise. Caller: GfGameScene::isBattleStop.
    static bool isInvalidBattleStop();
    // 2.0.0's symbols name it. What it does: whether the int at 0x630 of PtrSingleton<GfGameScene>'s instance is above
    // 0 (false without one). Caller: btl::BattleCharacter::IsProcAI.
    static bool isStopEnemyAttack();
    // 2.0.0's symbols name it. What it does: the handle of PtrSingleton<GfGamePlayerFormation>'s first player
    // (m_players[0].m_handle) when there is a formation and it is not -1, else getPartyLeader() unless it is -1, else
    // GfGameParty::getDummpMover(). Callers: gmk's getPlayerPos / isPlayerExist / getInterestPos and many gimmick
    // updates.
    static GF_OBJ_HANDLE* getControlMoverForGimmick();
    // 2.0.0's symbols name it. What it does: while there is a GfGameScene and it plays an event, whether the object is
    // not displayed (GfObjAcc::isDisp(0) false); false otherwise. Caller: GfComBehaviorPc::update.
    static bool isPlayEventHideChar(GF_OBJ_HANDLE* handle);
    static void clear();
    // 2.0.0's symbols name its parameter type; every caller passes isGameTypeIra()'s answer
    static void setupGame(GAME_TYPE type);
    virtual void gevHanaCondenser(unsigned int, bool, unsigned int);  // slot 2 (forwards its first two to GfGameScene)
    virtual void gevOrbParam(unsigned int, unsigned int);  // slot 3 (forwards the first 32-bit value to GfGameScene)
    virtual void gevAcceParam(unsigned int, unsigned int);  // slot 4 (forwards the first 32-bit value to GfGameScene)
    virtual void gevChangeGameDifficult();  // slot 5 (forwards to GfGameScene)
    virtual void gevExecBuy(unsigned int, unsigned int, unsigned int);  // slot 6
    virtual void gevChangeParty();  // slot 7
    virtual void gevGetArts(unsigned int, unsigned int, bool);  // slot 8
    virtual void gevDriverLevel(unsigned int, unsigned int, unsigned int);  // slot 9
    virtual void gevSelectHikari(bool);  // slot 10
    virtual void gevBattleStart();  // slot 11
    virtual void gevBattleEnd();  // slot 12
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
    virtual void gevChangeScenarioFlag(unsigned int, unsigned int);  // slot 29
    virtual void gevChangeAocFlag(unsigned int id);  // slot 30 (forwards the id to GfGameAoc::gevChangeAocFlag)
    virtual void gevChangeWeather(unsigned int, unsigned int);  // slot 31
    virtual void gevChangeTimeRange(unsigned int);  // slot 32
    virtual void gevGameState(gf::GF_STATE, gf::GF_STATE);  // slot 33
    virtual void gevControllFree(bool);  // slot 34
    virtual void gevMercenariesMissionFlag(unsigned int, unsigned int, unsigned int);  // slot 35
    virtual void gevOpenPortal();  // slot 36 (forwards to GfGameScene)
    virtual void gevOpenMainMenu();  // slot 37 (forwards to GfGameScene)
    virtual void qevOrderQuest(gf::QuestOrderParam const&);  // slot 38
    virtual void qevCompleteQuest(gf::QuestCompleteParam const&);  // slot 39
    virtual void qevCompleteChildQuest(gf::QuestCompleteChildParam const&);  // slot 40

    // set at the end of initialize, cleared by finalize (the name is not the original's)
    bool m_initialized;
    // set by leaveGameForDebug, read by isLeaveGameForDebug (the name is not the original's)
    bool m_leaveGameForDebug;
    unsigned char pad_1A[0x6];
    static bool isFadeClear();
    static bool isExistBossEnemy();
    static bool isExistBossEnemyWithHp();
    static bool isPlayerFinishBattleState();
    static bool isWaitGimmickPopForMapjump();
    static bool isBattleStop();
    static const mm::Vec3& getControlMoverPosition();
    // the controlled mover's world rotation as euler angles (x = asin of the -m[2][1] term, then y and z by atan2;
    // Vec3::zero without a valid transform). Callers: GfGameParty, GfMenuObjMinimap2
    static mm::Vec3 getControlMoverRotation();
    // 2.0.0's symbols name them. Statics of GfGameManager: their addresses lie in gf_game_manager's unit among
    // GfGameManager's functions and they use no instance. What they do: isDispPreciousMenu and isDispQuestCompleteMenu
    // (the same code) answer whether GfPlayComQuestCompleteUI::s_disp is above 0; btl::BattleGlobal::PreUpdateProc
    // calls both. 2.0.0's symbols name it. A static of GfGameManager (address
    // among its functions in gf_game_manager's unit). What it does: stores the flag into _gfgm::s_bDisablePlayerCamPause.
    static void setDisablePlayerCameraPauseForTitle(bool flag);
    // 1.0.0's isExecTutorial tail-called GfMenuObjTutorial::isWaiting from btl::BattleGlobal::PreUpdateProc;
    // 3.0.1's PreUpdateProc calls this one at the same place (2.0.0's symbols name it)
    static bool isExecTutorial();
    static bool isDispPreciousMenu();
    static bool isDispQuestCompleteMenu();
    // isEnableInGameSF / isEnableInGameElma: whether GfItemUtil::getItemBoxCount of item 25472 / 25541 is not 0;
    // GfMenuBladeList::setupFromTeam, removeFieldBlade and GfGameUtil::setupPoweredNewGameParam call both.
    static bool isEnableInGameSF();
    static bool isEnableInGameElma();
    // isVibrationDisable: GfGameScene::isPlayEvent() when there is a GfGameScene (the same code as isPlayEvent);
    // gf::pc::StateUtil::playVibration calls it.
    static bool isVibrationDisable();
};
}  // namespace gf

#endif

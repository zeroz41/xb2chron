#ifndef CLASSES_GF_GFGAMESCENE_H
#define CLASSES_GF_GFGAMESCENE_H

#include "classes/mm/mtl/PtrSingleton.h"
#include "gf/QuestID.h"
#include "gf/OwnerBonus.h"
namespace mm { class Vec3; }
#include "mm/mtl/Bitflag.h"
#include "mm/mtl/FixedQueue.h"
#include "mm/mtl/FixedList.h"
#include "mm/mtl/FixedVector.h"

namespace gf { class GfGameScene; class GfAppendWire; }
namespace gf { enum GEV : int; class MapjumpCallbackInfo; class QuestCompleteParam; class QuestCompleteChildParam; }
namespace gf { enum GfPlayerDead : int; }
namespace gf { enum ActivateType : int; }
namespace gf { struct OwnerBonus; }
namespace fw { class UpdateInfo; }
namespace gf { class GF_OBJ_HANDLE; class MsgObjectNotifyDamage; class GF_SE_CATEGORY_HANDLE; }
namespace gf { class GfSetupParam; }
namespace gf {
// which player stop a GfGameScene flag is (GfGameManager's gimmick tutorial uses 1 and 2; no names known)
enum PLSTOP : int {};
}

namespace gf {
namespace _gfgsc {
// whether the party member's mover is getting field damage: its PC property's damage id is valid while its flag is
// set, or the field gimmicks' damage phantoms hold it (GfGameScene::isMoverGetFieldDamage asks member 0)
bool isPartyMemberGetFieldDamage(unsigned int index);
}  // namespace _gfgsc

// table 0x7100B55EF0
class GfGameScene : public ::mm::mtl::PtrSingleton< ::gf::GfGameScene> {
public:
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because ScriptPlayText's ui
    // startTutorial calls it on PtrSingleton<GfGameScene>::sys() (when there is one). What it does: when the byte at
    // 0x8B9 is set, clears it and calls GfEvent::callPlayerControl(15).
    void fn_71002C4BE4();
    QuestID getQuestIdForTaskLog() const;  // 1.0.0 symbol
    void postUpdate(const fw::UpdateInfo& info);
    void setEnemyDead(GF_OBJ_HANDLE* handle);  // SCOM_CHAR_DEAD::exec passes the dead object
    void gevChangeWeather(unsigned int, unsigned int);
    void gevChangeTimeRange(unsigned int);
    void gevItemAdd(unsigned int, int);
    void gevGameObjEnter(GF_OBJ_HANDLE*);
    void gevGameObjLeave(GF_OBJ_HANDLE*);
    virtual ~GfGameScene();  // slot 0
    void gevDriverLevel(unsigned int, unsigned int, unsigned int);
    void gevSelectHikari(bool);
    void gevDriverActivate(unsigned int, ActivateType, ActivateType);
    void gevBladeActivate(unsigned int, ActivateType, ActivateType);
    void gevBladeUnselect(unsigned int, bool);
    void gevControllFree(bool);
    void gevChangeScenarioFlag(unsigned int, unsigned int);
    bool isPlayerPause() const;
    void enterBattle(bool);
    bool isBattle() const;
    bool isControlFree() const;
    const gf::OwnerBonus* getOwnerBonus() const;
    void setForceStopBattle(bool stop);
    bool isForceBossBattleBgm() const;
    bool isForceEventBgm() const;
    bool isDisableJumpForRide() const;
    void setHomuriWeaponExtraMesh(bool, float);
    void updateParam(const fw::UpdateInfo&);
    void updateRideRequest(const fw::UpdateInfo& info);
    // the field blade change time counts up while the leader driver and its blade are out of battle in a free field
    void updateBladeChangeInField(const fw::UpdateInfo& info);
    // m_questIdForTaskLog follows the current quest (at once while it is empty, else when the game allows it)
    void updateQuestTaskLog(const fw::UpdateInfo& info);
    void updatePlayerState();
    bool isEnableRideCondition(unsigned int id) const;
    bool isPlayerStopFlag(PLSTOP);
    void setPlayerStopFlag(PLSTOP, bool);
    bool isPlayerTalkForce();
    void setPlayerTalkForce(bool force);
    // GfPlayComSalvage's player pause: made when the command is, destroyed when it ends
    void setAutoBattle(bool flag);  // GfPlayComBattleStart sets it while it starts the battle
    unsigned int createPlayerPause();
    void destroyPlayerPause(unsigned int pause);
    // how the player died (0 alive; GfPlayFactory::createGameOver sets 1 unless one is set)
    GfPlayerDead getDeadType();
    void setDeadType(GfPlayerDead type);
    bool isEnableFieldBladeChange() const;
    void requestFieldBladeChange();
    void setForceEventBgm(float time);
    // whether the party member with that id rides (GfGameRide asks it for the leader driver's setup's m_partyId)
    bool isRideParty(unsigned int id) const;
    void setEventPlayerStop(bool stop);
    // named by 1.0.0: reference (1.0.0's GfPlayComResetBladePlayerStop::start calls setResetBladePlayerStop)
    void setResetBladePlayerStop(bool stop);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because it follows setResetBladePlayerStop in
    // gf_game_scene and GfFieldMapGimmick::update calls it on the GfGameScene singleton. What it does:
    // EvtPlayerStop::setPlayerStop(stop) on the EvtPlayerStop at +0x658; GfFieldMapGimmick::update passes true while
    // the gimmick's field skill runs (solve state 1) and false once it is solved (state 2).
    void fn_71002C345C(bool stop);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because
    // GfPlayComAfterEventScript::start calls it on the GfGameScene singleton. What it does: sets the bool at +0x8B9
    // when the script name contains "aoc_tut24", "aoc_tut04" or "aoc_tut10" (it never clears it).
    void fn_71002C4B80(const char* name);

    // GfGameManager reads and writes the next four through its own accessors (isStartGame/setStartGame,
    // isEnableRoomForHikariLv4, setStopMainMenuOpenForGimmick, is/setValidCollisionVelocity); the field names
    // follow those accessors and are not the original's
    // a player stop the scene holds for one caller: setPlayerStop(true) pushes its PLSTOP as stopped once,
    // setPlayerStop(false) pushes it as released if the flag is set (the constructor gives the three PLSTOPs 3, 4, 5)
    class EvtPlayerStop {
    public:
        void setPlayerStop(bool stop);
        GfGameScene* m_scene;  // the constructor's this
        int m_state;  // 1 while this one stops the player (the name is not the original's)
        PLSTOP m_type;  // the PLSTOP it pushes (the name is not the original's)
    };
    // an entry of setDamageCharacter's (the names are not the original's)
    struct DamageCharacter {
        GF_OBJ_HANDLE* m_handle;  // the constructor's -1
        int m_time;  // setDamageCharacter zeroes the handle's
    };
    GfGameScene(const GfSetupParam& param);
    static void build(const GfSetupParam& param);  // makes the scene (0x8D0 bytes, allocator 1)
    static void destroy();
    static bool isPlayerSwimOnCloud();  // the controlled mover's target property is in state 2
    static bool isPlayerWalkAndRun();  // the controlled mover's target property is in state 0
    bool isMaskMainMenu() const;
    bool isMoverGetFieldDamage() const;
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because its address is in
    // gf_game_scene's unit and GfGameManager::isEnableOpenMainMenu passes the scene. What it does: whether the int at
    // 0x690 is below 30; isEnableOpenMainMenu answers false while it holds.
    bool fn_71002C4A14();
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because its address is in
    // gf_game_scene's unit and GfWeapon's unit's fn_71002ED96C / fn_71002ED99C call it on PtrSingleton<GfGameScene>'s
    // instance. What it does: keeps (handle, target, kind) records (0x20 bytes each from 0x6A8, count at 0x8A8);
    // with flag clear it looks for the record with that handle and kind, and it reads both objects (GfObjAcc, the
    // target's append handles by GfMountManager::getAppendHandles). kind is 0 or 1 (the two callers).
    void fn_71002C4C0C(GF_OBJ_HANDLE* handle, GF_OBJ_HANDLE* target, bool flag, unsigned int kind);
// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because its address is in
    // gf_game_scene's unit and GfGameManager's statics pass the scene. What they do: fn_71002C4B38: whether the int
    // at 0x698 is below 2 (GfGameManager::fn_71002AC340); fn_71002C4BFC: whether the int at 0x68C is not 0
    // (GfGameManager::fn_71002AC764).
    bool fn_71002C4B38();
    bool fn_71002C4BFC();
// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because its address is in
    // gf_game_scene's unit and GfGameManager::fn_71002AC9C0 tail-calls it on the scene with its update info.
    void fn_71002CC060(const ::fw::UpdateInfo& info);
    void refreshGimmickFlag();
    bool isRide(unsigned int id) const;
    // GfGameParty::gevPartyIDMemberOK passes the party id it is told about (1.0.0's symbol)
    void setRideOn(unsigned int id);
    bool isRideObj(GF_OBJ_HANDLE* handle) const;
    bool isPlayerPauseForBattle() const;
    void setDamageCharacter(GF_OBJ_HANDLE* handle);
    void addDamage(GF_OBJ_HANDLE* handle, const MsgObjectNotifyDamage& msg);
    void saveBattleHpForEnemy(GF_OBJ_HANDLE* handle);
    void updateAppendModel(const fw::UpdateInfo& info);
    // the object's wire, null for none (GfGameUtil's startWire/startWireWithClose/endWire call GfAppendWire's
    // members on it; the return type is inferred from that)
    GfAppendWire* getAppendControl(GF_OBJ_HANDLE* handle);
    // the wire whose wire object or owner is handle deleted and taken off the list (gevGameObjLeave)
    void destroyDriverAppendModelControl(GF_OBJ_HANDLE* handle);
    // starts the wire of a driver's append model (gevGameObjEnter, for an object of type 13)
    void createDriverAppendModelControl(GF_OBJ_HANDLE* handle);
    // keeps Hana JS (bdat id 1005, not set up with create type 2, 3 or 11) in m_hanaJSObjs (gevGameObjEnter, for
    // types 4 and 6)
    void enterExtraControlForHanaJS(GF_OBJ_HANDLE* handle);
    const mm::Vec3& getEnableSavePos() const;
    bool isResetBladePlay() const;
    bool isNeedResetBladeForBattleEndForBattleEnd() const;
    bool isNeedResetBladeForBattleEndForMenuOpen() const;
    // gevMapjump's: before the jump, every driver's hit points restored (MsgObjectHealHp 0, type 1) and the save
    // positions cleared; after it, the zone script created for the new map and the sound categories reset
    void applyMapjumpForStart(const gf::MapjumpCallbackInfo& info);
    void applyMapjumpForEnd(const gf::MapjumpCallbackInfo& info);
    void gevExecBuy(unsigned int, unsigned int, unsigned int shop);
    void gevChangeParty();
    void gevBattleStart();
    void gevBattleEnd();
    // Placeholder names: new in 3.0.1, nothing in 1.0.0's place names them. Members: they lie in gf_game_scene's
    // unit and GfGameManager's IGfEvent overrides fn_710000FA68, fn_710000FA60, fn_710000FA64, fn_710000FA20,
    // fn_710000FA1C and fn_710000FA18 (IGfEvent's slots 23, 21, 22, 5, 4 and 3, in that order) forward to them on PtrSingleton<GfGameScene>'s instance, passing their arguments on. What they do: fn_71002C5200 and
    // fn_71002C56CC hand the value to the same file function fn_71002C5208 (which, when
    // GfGameManager::isFullScreenMenu answers true, builds "%s%s" ".wimdo" model paths); fn_71002C56D4 does the
    // same kind of work with its value; fn_71002C5994 calls fn_71002E0F28 on every object of
    // GfGameObj::getList(5); fn_71002C79B8 starts from the scene's byte at 0x6A0; fn_71002C7C44, unless
    // GfGameManager::fn_71002A9E68 answers true, sets local game flag 52962 (type 1) once
    // GfDataBlade::fn_7100231884 reaches 8003.
    void fn_71002C5200(unsigned int value, bool flag);
    void fn_71002C56CC(unsigned int value);
    void fn_71002C56D4(unsigned int value);
    void fn_71002C5994();
    void fn_71002C79B8();
    void fn_71002C7C44();
    void setCameraAvtivateOneTime();
    bool isPlayerCameraPause();
    void setPlayerCameraPause(bool pause);
    void setForceBattleTime(float time);
    void addMoneyLog();
    void setForceBossBattleBgm(bool force);

    // The field names below are not the original's: they follow the accessors that read and write them.
    bool m_alive;  // destroy clears it before deleting the scene (the name is not the original's)
    unsigned char pad_9[0xF];
    float m_fieldBladeChangeTime;  // isEnableFieldBladeChange allows a change from 0.5
    unsigned char pad_1C[0x4];
    DamageCharacter m_damageCharacters[3];
    // updateParam clears it and refreshes m_ownerBonus (GfGameUtil::getOwnerBonus) while it is set (the name is not
    // the original's)
    bool m_ownerBonusDirty;
    unsigned char pad_51[0x3];
    OwnerBonus m_ownerBonus;  // getOwnerBonus's
    // the drivers' wires (getAppendControl finds one by its wire object or owner; the name is not the original's)
    mm::mtl::FixedList<GfAppendWire*, 8> m_appendWires;  // 0x78
    float m_moneyLogTime;  // addMoneyLog sets 0.5
    QuestID m_questIdForTaskLog;  // getQuestIdForTaskLog's
    // the battle's achievement counts (1.0.0 symbol BattleAchievement::addDamage; the field names are not the
    // original's)
    struct BattleAchievement {
        void addDamage(GF_OBJ_HANDLE* handle, const MsgObjectNotifyDamage& msg);
        bool m_battleStarted;  // gevBattleStart sets it
        unsigned char pad_1[0x3];
        int m_damageCount;  // addDamage counts each damage of an object of type 3 or 5
    };
    BattleAchievement m_battleAchievement;
    float m_forceBattleTime;  // setForceBattleTime's
    bool m_forceStopBattle;  // setForceStopBattle's; gevMapjump clears it
    bool m_forceBossBattleBgm;  // setForceBossBattleBgm's; gevBattleStart clears it without a boss
    bool m_bossBattleBgm;  // gevBattleStart sets it when the forced boss battle BGM has a boss or a copied BGM
    unsigned char pad_137[0x1];
    float m_forceEventBgm;  // setForceEventBgm's; isForceEventBgm while above 0
    bool m_playerTalkForce[2];  // setPlayerTalkForce sets the first; isPlayerTalkForce tests either
    unsigned char pad_13E[0x2];
    GfPlayerDead m_deadType;  // setDeadType's
    unsigned int m_playerPause;  // createPlayerPause's bits, one per pause
    unsigned int m_cameraActivateOneTime : 1;  // setCameraAvtivateOneTime's; isPlayerCameraPause clears it
    unsigned int m_battle : 1;  // isBattle's
    unsigned int m_playerCameraPause : 1;  // setPlayerCameraPause's
    unsigned int : 29;
    unsigned char pad_14C[0x24];
    // a player state check the constructor pushes (a value, a state id, the static test it calls); the names are
    // not the original's
    struct PlayerStateCheck {
        unsigned int m_value;
        unsigned int m_state;
        bool (*m_test)();
    };
    // the constructor's two checks (isPlayerSwimOnCloud with 0x3E, isPlayerWalkAndRun with 0x3C; the name is not
    // the original's)
    mm::mtl::FixedVector<PlayerStateCheck, 4> m_playerStateChecks;  // 0x170
    bool m_autoBattle;  // setAutoBattle's
    bool m_completeQuest;  // qevCompleteQuest and a completed mercenary mission set it
    unsigned char pad_1BA[0xE];
    mm::mtl::Bitflag<6> m_playerStopFlag;  // isPlayerStopFlag's, by PLSTOP
    unsigned char pad_1CC[0xD];
    bool m_startGame;
    bool m_enableRoomForHikariLv4;
    // enterBattle sets it when a battle starts with blade 1003 (Homura) in party slot 3 (the name is not the
    // original's)
    bool m_homuraBattle;
    unsigned char pad_1DC[0x4];
    bool m_stopMainMenuOpenForGimmick;
    unsigned char pad_1E1[0x7];
    // setPlayerStopFlag's requests: a PLSTOP, with 0x80 when it stops
    mm::mtl::FixedQueue<unsigned char, 64> m_playerStopQueue;
    unsigned char pad_238[0x1C];
    // GfGameManager::isEnableOpenMainMenu opens the main menu only while it is 0 or 1 (the name is not the original's)
    int m_openMainMenuState;
    // isEnableRideCondition lets a riding driver ride from 3 on (the name is not the original's)
    int m_value258;
    unsigned char pad_25C[0x1];
    // GfGameManager::isEnableOpenMainMenu answers false while it is set (the name is not the original's)
    bool m_disableOpenMainMenu;
    unsigned char pad_25E[0x22];
    bool m_validCollisionVelocity;
    // 0x2D0: seven positions getEnableSavePos returns the first enabled of (an enable flag, then the position at
    // 0x10, 0x20 bytes each); not laid out yet, as an mm::Vec3 there would make the class 16-aligned and build
    // allocates it 8-aligned
    unsigned char pad_281[0xF];
    // the point GfFieldMapSe measures its map sounds' distances from (x, y, z; floats, not an mm::Vec3, see above;
    // the name is not the original's)
    float m_listenerPos[3];
    unsigned char pad_29C[0x24];
    // cleared with the save positions by applyMapjumpForStart (floats, see above; the name is not the original's)
    float m_pos2C0[3];
    unsigned char pad_2CC[0x4];
    // a position getEnableSavePos may return (the names are not the original's)
    struct SavePos {
        bool m_enable;
        unsigned char pad_1[0xF];
        float m_pos[3];  // floats, not an mm::Vec3 (see above)
        unsigned char pad_1C[0x4];
    };
    SavePos m_savePos[7];  // getEnableSavePos returns the first enabled one's position
    bool m_flag3B0;  // cleared by applyMapjumpForStart (the name is not the original's)
    unsigned char pad_3B1[0xF];
    // enterExtraControlForHanaJS pushes the object (bdat id 1005) here (the name is not the original's)
    mm::mtl::FixedVector<GF_OBJ_HANDLE*, 8> m_hanaJSObjs;  // 0x3C0
    unsigned char pad_408[0x18];
    bool m_maskMainMenu;  // isMaskMainMenu's
    bool m_playEvent;  // isPlayEvent's
    unsigned char pad_422[0x6];
    // setEraseQuestEnemyForEventStart pushes the quest's enemies here (the name is not the original's)
    mm::mtl::FixedVector<GF_OBJ_HANDLE*, 64> m_eraseQuestEnemies;  // 0x428
    // GfGameManager::fn_71002AC384 answers whether it is above 0 (btl::BattleCharacter::IsProcAI asks; the name is
    // not the original's)
    int m_value630;
    // SCOM_FIELD_VOICE::createLandmark and createUnexplored play nothing while it is below 60 (+0x624 in 1.0.0;
    // the name is not the original's)
    unsigned int m_value634;
    EvtPlayerStop m_eventPlayerStop;  // setEventPlayerStop's
    EvtPlayerStop m_resetBladePlayerStop;  // setResetBladePlayerStop's
    EvtPlayerStop m_gimmickPlayerStop;  // fn_71002C345C's (GfFieldMapGimmick::update calls it)
    // gf::_gffsn::bgmvolFadeBattleEvent fades its track out while it is set (+0x648 in 1.0.0; the name is not the
    // original's)
    bool m_battleEventBgm;
    unsigned char pad_669[0x7];
    GF_SE_CATEGORY_HANDLE* m_seCategoryHandles[3];  // destroy releases them (the name is not the original's)
    // isDisableJumpForRide answers it (unless the battle allows the jump; the name is not the original's)
    bool m_rideActive;
    // setRideOn clears it for Nia's Byakko outside battle and sets it when GfGameRide::testRideOn refuses;
    // updateRideRequest retries the ride while it is set (the name is not the original's)
    bool m_rideRequest;
    unsigned char pad_68A[0x2];
    int m_value68C;  // fn_71002C4BFC answers whether it is not 0 (the name is not the original's)
    // postUpdate counts it up to 999 each unpaused frame (0 while paused or an event fade runs); fn_71002C4A14
    // answers whether it is below 30 (the name is not the original's)
    int m_frameCount690;
    unsigned char pad_694[0x4];
    unsigned int m_value698;  // fn_71002C4B38 answers whether it is below 2 (the name is not the original's)
    unsigned char pad_69C[0x4];
    // applyMapjumpForEnd moves it on to m_flag6A1 (the names are not the original's)
    bool m_flag6A0;
    bool m_flag6A1;
    unsigned char pad_6A2[0x6];
    // fn_71002C4C0C's (handle, target, kind) records (the names are not the original's)
    struct AppendRecord {
        GF_OBJ_HANDLE* m_handle;
        GF_OBJ_HANDLE* m_target;
        unsigned int m_kind;
        bool m_flag;
        unsigned char pad_15[0x3];
        int m_value18;
        unsigned char pad_1C[0x4];
    };
    mm::mtl::FixedVector<AppendRecord, 16> m_appendRecords;  // 0x6A8
    unsigned char pad_8B0[0x8];
    // GfPlayComIraCampSave::start clears it and requests solo party 22 (GfReqCommand::reqSoloParty) while it is set;
    // the name is not the original's
    bool m_iraCampSolo;
    // fn_71002C4B80 sets it for the "aoc_tut24", "aoc_tut04" and "aoc_tut10" scripts; fn_71002C4BE4 clears it and
    // calls GfEvent::callPlayerControl(15) (the name is not the original's)
    bool m_tutorialPlayerControl;
    unsigned char pad_8BA[0x6];
    bool m_flag8C0;  // GfGameManager::fn_71002AC6F0 sets it (the name is not the original's)
    unsigned char pad_8C1[0xF];  // build allocates 0x8D0 bytes
    void qevCompleteQuest(const gf::QuestCompleteParam& param);
    void gevMapjump(gf::GEV gev, const gf::MapjumpCallbackInfo& info);
    void gevPlayEvent(gf::GEV gev, unsigned int id);
    // gevPlayEvent's handlers for its GEVs 12, 13 and 11
    void playEventSequenceStart(unsigned int id);
    void playEventSequenceEnd(unsigned int id);
    void playEventPlayEnd(unsigned int id);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because gevPlayEvent (its only
    // caller) passes the scene and the event id on for GEV 14. What it does: 0x620 bytes that, in a scenario game,
    // read the controlled mover's position (GfGameManager::getControlMoverPosition, fn_71002AB894), destroy party
    // objects (SCOM_DESTROY_PARTY_OBJ::create) and set the scene's sound category volumes.
    void fn_71002C6D48(unsigned int id);
    void gevMercenariesMissionFlag(unsigned int, unsigned int, unsigned int);
    void clear();
    bool isPlayEvent() const;
    bool isBattleStop();
    bool isNeedFieldBladeChange(unsigned int index) const;
};
}  // namespace gf

#endif

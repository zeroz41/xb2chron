#ifndef CLASSES_GF_GFGAMESCENE_H
#define CLASSES_GF_GFGAMESCENE_H

#include "classes/mm/mtl/PtrSingleton.h"
#include "gf/QuestID.h"
#include "gf/OwnerBonus.h"
namespace mm { class Vec3; }
#include "mm/mtl/Bitflag.h"
#include "mm/mtl/FixedQueue.h"

namespace gf { class GfGameScene; }
namespace gf { enum GEV : int; class MapjumpCallbackInfo; class QuestCompleteParam; class QuestCompleteChildParam; }
namespace gf { enum GfPlayerDead : int; }
namespace gf { enum ActivateType : int; }
namespace gf { struct OwnerBonus; }
namespace fw { class UpdateInfo; }
namespace gf { class GF_OBJ_HANDLE; }
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
    static bool isPlayerSwimOnCloud();  // the controlled mover's target property is in state 2
    static bool isPlayerWalkAndRun();  // the controlled mover's target property is in state 0
    bool isMaskMainMenu() const;
    bool isMoverGetFieldDamage() const;
    void refreshGimmickFlag();
    bool isRide(unsigned int id) const;
    bool isRideObj(GF_OBJ_HANDLE* handle) const;
    bool isPlayerPauseForBattle() const;
    void setDamageCharacter(GF_OBJ_HANDLE* handle);
    const mm::Vec3& getEnableSavePos() const;
    bool isResetBladePlay() const;
    void gevExecBuy(unsigned int, unsigned int, unsigned int shop);
    void gevChangeParty();
    void gevBattleStart();
    void setCameraAvtivateOneTime();
    bool isPlayerCameraPause();
    void setPlayerCameraPause(bool pause);
    void setForceBattleTime(float time);
    void addMoneyLog();
    void setForceBossBattleBgm(bool force);

    // The field names below are not the original's: they follow the accessors that read and write them.
    unsigned char pad_8[0x10];
    float m_fieldBladeChangeTime;  // isEnableFieldBladeChange allows a change from 0.5
    unsigned char pad_1C[0x4];
    DamageCharacter m_damageCharacters[3];
    unsigned char pad_50[0x4];
    OwnerBonus m_ownerBonus;  // getOwnerBonus's
    unsigned char pad_72[0xAE];
    float m_moneyLogTime;  // addMoneyLog sets 0.5
    QuestID m_questIdForTaskLog;  // getQuestIdForTaskLog's
    bool m_battleStarted;  // gevBattleStart sets it
    unsigned char pad_129[0x7];
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
    unsigned char pad_14C[0x6C];
    bool m_autoBattle;  // setAutoBattle's
    bool m_completeQuest;  // qevCompleteQuest and a completed mercenary mission set it
    unsigned char pad_1BA[0xE];
    mm::mtl::Bitflag<6> m_playerStopFlag;  // isPlayerStopFlag's, by PLSTOP
    unsigned char pad_1CC[0xD];
    bool m_startGame;
    bool m_enableRoomForHikariLv4;
    unsigned char pad_1DB[0x5];
    bool m_stopMainMenuOpenForGimmick;
    unsigned char pad_1E1[0x7];
    // setPlayerStopFlag's requests: a PLSTOP, with 0x80 when it stops
    mm::mtl::FixedQueue<unsigned char, 64> m_playerStopQueue;
    unsigned char pad_238[0x48];
    bool m_validCollisionVelocity;
    // 0x2D0: seven positions getEnableSavePos returns the first enabled of (an enable flag, then the position at
    // 0x10, 0x20 bytes each); not laid out yet, as an mm::Vec3 there would make the class 16-aligned and build
    // allocates it 8-aligned
    unsigned char pad_281[0x19F];
    bool m_maskMainMenu;  // isMaskMainMenu's
    bool m_playEvent;  // isPlayEvent's
    unsigned char pad_422[0x216];
    EvtPlayerStop m_eventPlayerStop;  // setEventPlayerStop's
    EvtPlayerStop m_resetBladePlayerStop;  // setResetBladePlayerStop's
    EvtPlayerStop m_gimmickPlayerStop;  // fn_71002C345C's (GfFieldMapGimmick::update calls it)
    // gf::_gffsn::bgmvolFadeBattleEvent fades its track out while it is set (+0x648 in 1.0.0; the name is not the
    // original's)
    bool m_battleEventBgm;
    unsigned char pad_669[0x267];  // build allocates 0x8D0 bytes
    void qevCompleteQuest(const gf::QuestCompleteParam& param);
    void gevMapjump(gf::GEV gev, const gf::MapjumpCallbackInfo& info);
    void gevMercenariesMissionFlag(unsigned int, unsigned int, unsigned int);
    void clear();
    bool isPlayEvent() const;
    bool isBattleStop();
    bool isNeedFieldBladeChange(unsigned int index) const;
};
}  // namespace gf

#endif

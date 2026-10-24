#ifndef CLASSES_GF_GFGAMESCENE_H
#define CLASSES_GF_GFGAMESCENE_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace gf { class GfGameScene; }
namespace gf { enum GfPlayerDead : int; }
namespace gf { enum ActivateType : int; }
namespace gf { struct OwnerBonus; }
namespace fw { class UpdateInfo; }
namespace gf { class GF_OBJ_HANDLE; }
namespace gf {
// which player stop a GfGameScene flag is (GfGameManager's gimmick tutorial uses 1 and 2; no names known)
enum PLSTOP : int {};
}

namespace gf {
// table 0x7100B55EF0
class GfGameScene : public ::mm::mtl::PtrSingleton< ::gf::GfGameScene> {
public:
    void postUpdate(const fw::UpdateInfo& info);
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
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because it sits right after
    // setEventPlayerStop and GfPlayComResetBladePlayerStop calls it on the GfGameScene singleton. What it does:
    // EvtPlayerStop::setPlayerStop(stop) on the EvtPlayerStop at +0x648 (setEventPlayerStop's is at +0x638).
    void fn_71002C3450(bool stop);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because
    // GfPlayComAfterEventScript::start calls it on the GfGameScene singleton. What it does: sets the bool at +0x8B9
    // when the script name contains "aoc_tut24", "aoc_tut04" or "aoc_tut10" (it never clears it).
    void fn_71002C4B80(const char* name);

    unsigned char pad_8[0x660];
    // gf::_gffsn::bgmvolFadeBattleEvent fades its track out while it is set (+0x648 in 1.0.0; the name is not the
    // original's)
    bool m_battleEventBgm;
};
}  // namespace gf

#endif

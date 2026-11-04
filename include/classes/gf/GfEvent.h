#ifndef CLASSES_GF_GFEVENT_H
#define CLASSES_GF_GFEVENT_H

#include "classes/mm/mtl/PtrSingleton.h"
#include "mm/mtl/FixedQueue.h"

namespace gf { enum GEV : int; }  // as IGfEvent.h declares it
namespace gf { class GF_OBJ_HANDLE; enum ActivateType : int; }
namespace gf { class GfAchievementRelease; }
namespace gf { class GfSetupParam; }
namespace gf { class GfEvent; }
namespace gf { class IGfEvent; }
namespace gf { enum EXEC_STATE : int; }
namespace gf { enum GF_STATE : int; }

namespace gf {
// table 0x7100B591E8
class GfEvent : public ::mm::mtl::PtrSingleton< ::gf::GfEvent> {
public:
    GfEvent() : m_initialized(true) {}
    // the event for a driver changing its engaged blade from one slot to another
    static void callBladeChange(GF_OBJ_HANDLE* handle, int from, int to);
    static void callHikariCurrent(bool hikari);
    static void callBladeActivate(unsigned int blade, ActivateType from, ActivateType to);  // GfGameUtil::changeHikariCurrent passes its flag
    static void build(const GfSetupParam& param);
    static void destroy();
    static void callTargetAccess(GF_OBJ_HANDLE*);
    // 2.0.0's symbols name it. What it does: calls slot 5 (+0x28) of every listener in the instance's 32-entry ring
    // (count at +0x108, start at +0x110), taking no argument; GfGameSave::execOptionSaveWithMicroThread calls it first.
    static void callChangeGameDifficult();
    static void callGameObjEnter(GF_OBJ_HANDLE* handle);  // GfGameObj::flushEvent: an object entered the game
    static void callGameObjLeave(GF_OBJ_HANDLE* handle);  // GfGameObj::flushEvent: an object left the game
    static void callItemAdd(unsigned int item, int count);  // count of the item gained (or lost)
    static void callTargetChange(GF_OBJ_HANDLE*);
    // a party driver's object entering (true) or leaving (false) the game, with its setup's party id
    // (GfGameParty::gevGameObjEnter and gevGameObjLeave; 1.0.0's symbol)
    static void callPartyDriver(GF_OBJ_HANDLE* handle, unsigned int partyId, bool enter);
    static void callPartyMemberOK(bool ok);
    // 2.0.0's symbols name it. What it does: calls virtual slot 3 (+0x18, IGfEvent::gevOpenMainMenu) of every entry of
    // the GfEvent's ring of up to 32 listeners (count at 0x108, start index at 0x110, "index < N"). Callers:
    // GfGamePad's eventInGameOpenMainMenu, eventInGameOpenSystemMenu and eventInGameOpenSkipTravelMenu, before they
    // open the menu (no arguments).
    static void callOpenMeinMenu();
    // 2.0.0's symbols name it. What it does: calls virtual slot 4 (+0x20) of every entry of the GfEvent's ring of up to
    // 32 listeners (count at 0x108, start index at 0x110, "index < N"). Caller: the gmk plugin's openPortal (no
    // arguments).
    static void callOpenPortal();  // GfGameParty::update: the party's objects are ready (or not any more)
    static void callChangeTimeRange(unsigned int range);  // GfFieldTime::update: the time of day's range changed
    static void callChangeLeader(GF_OBJ_HANDLE* leader);  // GfGameParty::update: the party leader changed
    static void callPartyIDMemberOK(bool ok, unsigned int partyId);
    // GfPlayComCallbackEventSequence::start passes 12 (begin) or 13 and its id
    static void callEventPlay(GEV gev, unsigned int id);
    virtual ~GfEvent();  // slot 0
    static void callCameraControl(int type);
    // a mercenary mission's flag changed (GfGameMercenaries::setMissionFlag passes the mission, new and old flag)
    static void callMercenariesMissionFlag(unsigned int mission, unsigned int flag, unsigned int old);
    // listener joins (leaves) the ones GfEvent's calls reach
    static void addEventCallback(IGfEvent* listener);
    static void removeEventCallback(IGfEvent* listener);
    // each listener's gevGameMapModel (GfMapManager::destroyMapData passes the map's object and false)
    static void callGameMapModel(GF_OBJ_HANDLE* handle, bool flag);
    static void callGameState(GF_STATE prev, GF_STATE next);  // each listener's gevGameState
    static void callExecState(EXEC_STATE state);  // each listener's gevExecState
    static void callLoadGameTime(float time);  // each listener's gevLoadGameTime
    static void callSwapFormation(unsigned int index0, unsigned int index1);  // each listener's gevSwapFormation
    // each listener told the salvage game's state (1.0.0's and 2.0.0's name)
    static void callSalvageStateChange(unsigned int state);
    // each listener's gevChangeScenarioFlag: the scenario flag now, then the one before (GfDataManager::clear)
    static void callChangeScenarioFlag(unsigned int flag, unsigned int prevFlag);
    static void callBladeUnselect(unsigned int blade, bool unselect);  // GfDataBlade::setUnselect
    // GfDataBlade::setTrustPoint passes 4, the blade, 0, 0
    static void callDebugChangeIdea(unsigned int, unsigned int, unsigned int, unsigned int);
    // 2.0.0's symbols name it. What it does: calls virtual slot 23 (+0xB8) of every entry of the GfEvent's ring of up
    // to 32 listeners (count at 0x108, start index at 0x110, "index < N") with its three arguments. Callers:
    // GfGameUtilHana::execEquipCondenserParts (false) and execEquipExtendCondenserParts (true), after Hana's equipment
    // is stored, with Hana's id and the slot.
    static void callHanaCondenser(unsigned int hana, bool extend, unsigned int slot);
    // 2.0.0's symbols name it. What it does: calls IGfEvent slot 46 (gevChangeAocFlag) of every listener with its
    // arguments. Caller: GfGameFlag::setLocal.
    static void callChangeAocFlag(unsigned int);
    static void callBattleStart();  // each listener's gevBattleStart
    static void callBattleEnd();  // each listener's gevBattleEnd
    static void callPartyChange();  // each listener's gevChangeParty
    static void callAchievmentRelease(const GfAchievementRelease&);  // each listener's gevReleaseAchievment
    static void callDriverActivate(unsigned int, ActivateType, ActivateType);  // each listener's gevDriverActivate
    static void callBladeEnable(unsigned int);  // each listener's gevBladeEnable
    static void callDriverLevel(unsigned int, unsigned int, unsigned int);  // each listener's gevDriverLevel
    static void callMercenariesTeam(unsigned int);  // each listener's gevMercenariesTeam
    // 2.0.0's symbols name it. What it does: calls IGfEvent slot 21 (gevOrbParam) of every listener with its arguments.
    // Caller: GfEquipUtil::equipBladeOrb.
    static void callOrbParam(unsigned int, unsigned int);
    // 2.0.0's symbols name it. What it does: calls IGfEvent slot 22 (gevAcceParam) of every listener with its
    // arguments. Caller: GfEquipUtil::equipDriverAcce.
    static void callAcceParam(unsigned int, unsigned int);
    static void callPartyReturnFieldState(unsigned int);  // each listener's gevPartyReturnFieldState
    static void callPlayerControl(GEV);  // each listener's gevPlayerControl
    static void callPartyMover(GF_OBJ_HANDLE*, bool);  // each listener's gevPartyMover
    // 2.0.0's symbols name it. What it does: calls IGfEvent slot 2 (gevHitonowaChanged) of every listener with its
    // arguments. Caller: GfDataNpc::setHitonowaFlag.
    static void callHitonowaChanged(unsigned int);
    static void callExecBuy(unsigned int, unsigned int, unsigned int);  // each listener's gevExecBuy
    static void callGetArts(unsigned int, unsigned int, bool);  // each listener's gevGetArts
    static void callChangeWeather(unsigned int, unsigned int);  // each listener's gevChangeWeather

private:
    // the listeners each call* reaches in turn (addEventCallback, removeEventCallback)
    ::mm::mtl::FixedQueue<IGfEvent*, 32> m_listeners;  // 0x8
    // set when build constructs the instance, cleared by destroy (the name is not the original's)
    bool m_initialized;  // 0x118
};
}  // namespace gf

#endif

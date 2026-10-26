#ifndef CLASSES_GF_IGFEVENT_H
#define CLASSES_GF_IGFEVENT_H

namespace gf { class GF_ASSET_HANDLE; }
namespace gf { class GF_OBJ_HANDLE; }
namespace gf { class GfAchievementRelease; }
namespace gf { class MapjumpCallbackInfo; }
namespace gf { enum ActivateType : int; }
namespace gf { enum EXEC_STATE : int; }
namespace gf { enum GEV : int; }
namespace gf { enum GF_STATE : int; }
namespace gf { enum RELOAD_BDAT : int; }

namespace gf {
// table 0x7100B55698: the game events a listener GfEvent::addEventCallback registers hears. Every slot is inline and
// empty (the table and the destructors are GfGamePlayerCamera's unit's, the slots' bodies the first unit's that
// needed them). Names: 1.0.0's, by the slot each override takes in 3.0.1's derived tables, and by 1.0.0's order
// between those. Slots 2-5, 21-23 and 46 are new in 3.0.1 (1.0.0's table has none of them): placeholder names, each
// the address of this class's own empty body
class IGfEvent {
public:
    virtual ~IGfEvent() {}  // slot 0
    virtual void fn_710000FA14() {}  // slot 2
    virtual void fn_710000FA18() {}  // slot 3
    virtual void fn_710000FA1C() {}  // slot 4
    virtual void fn_710000FA20() {}  // slot 5
    virtual void gevPartyMover(gf::GF_OBJ_HANDLE*, bool) {}  // slot 6
    virtual void gevExecBuy(unsigned int, unsigned int, unsigned int) {}  // slot 7
    virtual void gevGetArts(unsigned int, unsigned int, bool) {}  // slot 8
    virtual void gevSelectHikari(bool) {}  // slot 9
    virtual void gevPlayerControl(gf::GEV) {}  // slot 10
    virtual void gevLoadGameTime(float) {}  // slot 11
    virtual void gevPartyReturnFieldState(unsigned int) {}  // slot 12
    virtual void gevControllFree(bool) {}  // slot 13
    virtual void gevGameState(gf::GF_STATE, gf::GF_STATE) {}  // slot 14
    virtual void gevPartyDriver(gf::GF_OBJ_HANDLE*, unsigned int, bool) {}  // slot 15
    virtual void gevChangeLeader(gf::GF_OBJ_HANDLE*) {}  // slot 16
    virtual void gevSwapFormation(unsigned int, unsigned int) {}  // slot 17
    virtual void gevPartyIDMemberOK(bool, unsigned int) {}  // slot 18
    virtual void gevPartyMemberOK(bool) {}  // slot 19
    virtual void gevItemAdd(unsigned int, int) {}  // slot 20
    virtual void fn_710000FA60(unsigned int) {}  // slot 21
    virtual void fn_710000FA64(unsigned int) {}  // slot 22
    virtual void fn_710000FA68(unsigned int, bool) {}  // slot 23
    virtual void gevMercenariesMissionFlag(unsigned int, unsigned int, unsigned int) {}  // slot 24
    virtual void gevMercenariesTeam(unsigned int) {}  // slot 25
    virtual void gevDriverLevel(unsigned int, unsigned int, unsigned int) {}  // slot 26
    virtual void gevDriverActivate(unsigned int, gf::ActivateType, gf::ActivateType) {}  // slot 27
    virtual void gevBladeActivate(unsigned int, gf::ActivateType, gf::ActivateType) {}  // slot 28
    virtual void gevBladeUnselect(unsigned int, bool) {}  // slot 29
    virtual void gevBladeEnable(unsigned int) {}  // slot 30
    virtual void gevReleaseAchievment(gf::GfAchievementRelease const&) {}  // slot 31
    virtual void gevGameObjEnter(gf::GF_OBJ_HANDLE*) {}  // slot 32
    virtual void gevGameObjLeave(gf::GF_OBJ_HANDLE*) {}  // slot 33
    virtual void gevChangeParty() {}  // slot 34
    virtual void gevChangeBlade(gf::GF_OBJ_HANDLE*, int, int) {}  // slot 35
    virtual void gevPlayEvent(gf::GEV, unsigned int) {}  // slot 36
    virtual void gevPause(unsigned int, unsigned int) {}  // slot 37
    virtual void gevLayerPause(unsigned int, bool) {}  // slot 38
    virtual void gevCameraControl(unsigned int) {}  // slot 39
    virtual void gevChangeTarget(gf::GF_OBJ_HANDLE*) {}  // slot 40
    virtual void gevAccessTarget(gf::GF_OBJ_HANDLE*) {}  // slot 41
    virtual void gevMapjump(gf::GEV, gf::MapjumpCallbackInfo const&) {}  // slot 42
    virtual void gevBattleStart() {}  // slot 43
    virtual void gevBattleEnd() {}  // slot 44
    virtual void gevChangeScenarioFlag(unsigned int, unsigned int) {}  // slot 45
    virtual void fn_710000FAB8(unsigned int) {}  // slot 46 (GfGameManager's override forwards a 32-bit id)
    virtual void gevSalvageStateChange(unsigned int) {}  // slot 47
    virtual void gevGameMapModel(gf::GF_OBJ_HANDLE*, bool) {}  // slot 48
    virtual void gevChangeWeather(unsigned int, unsigned int) {}  // slot 49
    virtual void gevChangeTimeRange(unsigned int) {}  // slot 50
    virtual void gevExecState(gf::EXEC_STATE) {}  // slot 51
    virtual void gevReloadBdat(gf::RELOAD_BDAT, unsigned int) {}  // slot 52
    virtual void gevDebugBladeAttribute(unsigned int, unsigned char) {}  // slot 53
    virtual void gevDebugWeaponTypeActivate(unsigned int) {}  // slot 54
    virtual void gevDebugChangeTime(unsigned int, unsigned int) {}  // slot 55
    virtual void gevDebugItem(unsigned int, bool) {}  // slot 56
    virtual void gevDebugChangeFlag(unsigned int, unsigned int, unsigned int, unsigned int) {}  // slot 57
    virtual void gevDebugChangeIdea(unsigned int, unsigned int, unsigned int, unsigned int) {}  // slot 58
    virtual void gevDebugChangeLevel(unsigned int, unsigned int, unsigned int, unsigned int) {}  // slot 59
    virtual void gevDebugDestroyAsset(gf::GF_ASSET_HANDLE*) {}  // slot 60
    virtual void gevDebugReloadObj(gf::GF_OBJ_HANDLE*) {}  // slot 61
    virtual void gevDebugMapModel(gf::GF_OBJ_HANDLE*, bool) {}  // slot 62
};
}  // namespace gf

#endif

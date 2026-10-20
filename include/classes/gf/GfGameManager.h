#ifndef CLASSES_GF_GFGAMEMANAGER_H
#define CLASSES_GF_GFGAMEMANAGER_H

#include "classes/gf/IQuestEvent.h"

namespace gf { class ActivateType; }
namespace gf { class GF_OBJ_HANDLE; }
namespace gf { class MapjumpCallbackInfo; }
namespace gf { class QuestCompleteChildParam; }
namespace gf { class QuestCompleteParam; }
namespace gf { class QuestOrderParam; }
namespace gf { enum GEV : int; }
namespace gf { enum GF_STATE : int; }
namespace gf { enum RELOAD_BDAT : int; }

namespace gf {
// a base of gf::GfGameManager no evidence names yet
class TUnk_B54938 {
public:
    virtual ~TUnk_B54938();
    virtual void vf2();
    virtual void vf3();
    virtual void vf4();
    virtual void vf5();
    virtual void vf6();
    virtual void vf7();
    virtual void gevGetArts(unsigned int, unsigned int, bool) = 0;
    virtual void gevDriverLevel(unsigned int, unsigned int, unsigned int) = 0;
    virtual void gevSelectHikari(bool) = 0;
    virtual void vf11();
    virtual void vf12();
    virtual void gevPause(unsigned int, unsigned int) = 0;
    virtual void gevChangeBlade(gf::GF_OBJ_HANDLE*, int, int) = 0;
    virtual void gevMapjump(gf::GEV, gf::MapjumpCallbackInfo const&) = 0;
    virtual void gevGameObjEnter(gf::GF_OBJ_HANDLE*) = 0;
    virtual void gevGameObjLeave(gf::GF_OBJ_HANDLE*) = 0;
    virtual void gevDriverActivate(unsigned int, gf::ActivateType, gf::ActivateType) = 0;
    virtual void gevBladeActivate(unsigned int, gf::ActivateType, gf::ActivateType) = 0;
    virtual void gevBladeUnselect(unsigned int, bool) = 0;
    virtual void gevBladeEnable(unsigned int) = 0;
    virtual void gevPlayEvent(gf::GEV, unsigned int) = 0;
    virtual void gevPartyMemberOK(bool) = 0;
    virtual void gevPartyIDMemberOK(bool, unsigned int) = 0;
    virtual void gevItemAdd(unsigned int, int) = 0;
    virtual void gevLayerPause(unsigned int, bool) = 0;
    virtual void gevReloadBdat(gf::RELOAD_BDAT, unsigned int) = 0;
    virtual void gevSalvageStateChange(unsigned int) = 0;
    virtual void vf29();
    virtual void vf30();
    virtual void gevChangeWeather(unsigned int, unsigned int) = 0;
    virtual void gevChangeTimeRange(unsigned int) = 0;
    virtual void gevGameState(gf::GF_STATE, gf::GF_STATE) = 0;
    virtual void gevControllFree(bool) = 0;
    virtual void gevMercenariesMissionFlag(unsigned int, unsigned int, unsigned int) = 0;
    virtual void vf36();
    virtual void vf37();
    virtual void qevOrderQuest(gf::QuestOrderParam const&) = 0;
    virtual void qevCompleteQuest(gf::QuestCompleteParam const&) = 0;
    virtual void qevCompleteChildQuest(gf::QuestCompleteChildParam const&) = 0;
};
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
// table 0x7100B54938; base at 0x0 unknown (TUnk_B54938), base at 0x8 unknown (TUnk_B54A90)
class GfGameManager : public TUnk_B54938, public TUnk_B54A90, public ::gf::IQuestEvent {
public:
    virtual ~GfGameManager();  // slot 0
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

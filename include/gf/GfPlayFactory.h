#ifndef GF_GFPLAYFACTORY_H
#define GF_GFPLAYFACTORY_H

#include "gf/GfQuestInfo.h"
#include "gf/QuestID.h"

namespace gf { class ParamReturnTitle; }
namespace gf { class GfSequentialPlaySignal; }
namespace gf { class GfMapjumpInfo; }
namespace gf { class GfSetupPfTalk; }
namespace fw { class Camera; }
#include "mm/mtl/IntrusivePtr.h"
namespace gf { class GF_OBJ_HANDLE; }
namespace gf { enum MAINMENU : int; }
namespace gf { class MenuCommonWindowParam; }
namespace gf { struct MapJumpForReturnBattle; }
namespace gmk { enum GmkType : int; }
namespace gf { enum GfPlayerDead : int; }
#include "classes/gf/GfMenuObjCommonText.h"

namespace gf {
// the sequential play's factory (functions, by its symbols)
class GfPlayFactory {
public:
    // queues the return to the title; false while one is already running
    static bool createReturnTitle(const ParamReturnTitle& param);
    static bool createOpenMenu(unsigned int menu, GfSequentialPlaySignal* signal);
    static bool createOpenMenu2(unsigned int menu, MAINMENU main, GfSequentialPlaySignal* signal);
    // GfMenuObjBladeCreate::seqCreateStartEvent passes the blade's GfDataBlade::getCreateEvent, 1, the blade and its
    // signal (the return type is unproven; the caller ignores it)
    static bool createBlEvent(unsigned int event, unsigned int, unsigned int blade, GfSequentialPlaySignal* signal);
    // these return nothing: their code leaves the leave-game check's result in the return register
    static void createMiniGame();
    static bool createSalvage(GF_OBJ_HANDLE* handle);
    static bool createCollect(GF_OBJ_HANDLE* handle);
    static bool createFieldTbox(GF_OBJ_HANDLE* handle);
    static bool createMapGimmick(GF_OBJ_HANDLE* handle);
    static bool createGrave(GF_OBJ_HANDLE* handle);
    static bool createJump(GF_OBJ_HANDLE* handle);
    static bool createWarp(GF_OBJ_HANDLE* handle);
    static bool createGmkTutorial(const char* name, unsigned int id);
    static bool createStartTutorial(unsigned int id, GfSequentialPlaySignal* signal);
    // 2.0.0's symbols name it. Caller: the sys plugin's playTutorial (a string and an int from the script).
    static bool createTutorialScript(const char* name, unsigned int id);
    static bool createGmkCamera(mm::mtl::IntrusivePtr<fw::Camera> camera);
    // queues the player's death of a kind (StateUtil::notifyDead's); true when queued or a running one took the kind
    static bool createPlayerDead(GfPlayerDead type);
    static bool createGameOver();
    static bool createTalk(const GfSetupPfTalk& talk);
    static bool createMapjump(const GfMapjumpInfo& info);
    static bool createEventMapjump(const GfMapjumpInfo& info);
    static bool createOneEventForGimmick(unsigned int id);
    static bool createOneEvent(unsigned int id);
    static bool createReserveEvent(const char* name);  // the sys plugin's reserveEvent (a script name)
    // whether a common message window is open, and its result (GfPlayComMenuCommon's)
    static bool createEventWait(float time, GF_OBJ_HANDLE* handle);
    // a common window's handle, -1 when none opens
    static int createCommonMessage(unsigned int id);
    static int createCommonMessage(const MenuCommonWindowParam& param);
    static bool isDispCommonMessage(unsigned int id);
    static int getDispCommonMessage(unsigned int id);
    static bool isDispChapterSave();
    static void createOpenChapterSave(unsigned int id);
    static void createOpenZoneUI(unsigned int id);
    static void createOpenChapterUI(unsigned int id);
    static void createOpenChapterEndUI(unsigned int id);
    static void createOpenDummyTutorial(unsigned int id);
    static void createBattleStart(bool flag);
    static void createGimmickTaskComplete(gmk::GmkType type, unsigned int id, float time);
    static bool createArtsMovie(const char* name);
    // 2.0.0's symbols name it (1.0.0's unit ends at createResetBladeForBladeSwitch). What it does: when the game
    // condition in row 0x2F of BDAT table 0x17E's "cond" column holds, no party slot's blade reset runs or is queued
    // (GfPlayComResetBlade::isPlaying, GfSequentialPlay::isExistResetBladeParty, slots 0-2) and no state 0x14 or
    // special action runs, queues addPartySwitch in state 0x18; true when queued.
    static bool createResetBladeForBattleEnd(unsigned int slot, int setId, bool stopPlayer);
    static bool createResetBladeForBladeSwitch(unsigned int slot, int setId);
    static bool createPartySwitchForIra();
    // 2.0.0's symbols name it. What it does: as createBladeSwitchFR, queues addResetBlade(0, 0) in state 0x18 unless
    // state 0x14 or a special action runs; true when queued.
    static bool createBladeSwitch();
    // 2.0.0's symbols name it. What it does: as createBladeSwitch, queues addResetBlade(0, 1) in state 0x18 unless
    // state 0x14 or a special action runs; true when queued.
    static bool createBladeSwitchFR();
    // 2.0.0's symbols name it. What it does: as createBladeSwitchFR, queues addResetBlade(0, 2) in state 0x18 unless
    // state 0x14 or a special action runs; true when queued.
    static bool createBladeSwitchBR();
    static bool createMenuObjCommonText(GfMenuObjCommonText::OpenKizunaParam& param);
    static bool createEventAfterScript(int id);
    static bool createHoodHomuraBattou();
    // queues the chain attack's play; false while the game is left for debugging or the control is not free
    static bool createChainAttack();
    // queues a quest's order UI; GfQuestEvent::openEntry keeps the result as its entry UI's flag
    static bool createQuestUIOrder(QuestID id, bool flag1, bool flag2);
    static bool createQuestUIComplete(QuestID id, QuestID next, QSTATE state);
    static bool createMenuPrecious(unsigned int id, bool flag);
    // queues a quest's completion UI; GfQuestEvent::openResult keeps the result as its result UI's flag
    static bool createQuestUIComplete(QuestID id);
    // 2.0.0's symbols name it (code in sequential_play's unit_71003214F4, which has no source yet). StateArenaField's
    // onStep calls it with true and moves to state 2 when it answers true. What it does: unless the bool is set,
    // answers false when GfGameManager::isLeaveGameForDebug, else needs isEnableOpenMainMenu and isBattleArenaActive;
    // then builds a map-jump request on the stack.
    static bool createLeaveBattleArena(bool force);
    // 2.0.0's symbols name it (code in unit_71003214F4). GfGameArena::procMsgGameBtlArena (message type 2) and
    // GfArenaBattle::mapjumpForReturnField call it. What it does: builds a GfMapjumpInfo from param's m_mapjumpId and
    // the defaults.
    static void createMapJumpForReturnBattle(const MapJumpForReturnBattle& param);
};
}  // namespace gf

#endif

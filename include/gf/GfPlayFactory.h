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
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because its address sits between
    // GfPlayFactory's unit and gf_sequential_play's and its body is a create* sequence: when isScenarioGame and not
    // isLeaveGameForDebug, beginCommand(0), pushState(6), addEventPlayerStop(true), fn_7100322C64(name, id),
    // fn_7100322808(), addEventPlayerStop(false), popState(), clears the GfSequentialPlay's int at 0x20F0 and answers
    // true. Caller: the sys plugin's playTutorial (a string and an int from the script).
    static bool fn_7100321924(const char* name, unsigned int id);
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
    // Placeholder name: new in 3.0.1 (1.0.0's unit ends at createResetBladeForBladeSwitch). A member because it fills
    // this unit among GfPlayFactory's create functions. What it does: when the game condition in row 0x2F of BDAT
    // table 0x17E's "cond" column holds, no party slot's blade reset runs or is queued (GfPlayComResetBlade::isPlaying,
    // GfSequentialPlay::isExistResetBladeParty, slots 0-2) and no state 0x14 or special action runs, queues
    // addMoverSwitch in state 0x18; true when queued.
    static bool createResetBladeForBattleEnd(unsigned int slot, int setId, bool stopPlayer);
    static bool createResetBladeForBladeSwitch(unsigned int slot, int setId);
    static bool fn_7100321258();
    // Placeholder name: new in 3.0.1, like fn_7100321258. What it does: as createMoverSwitch, queues
    // addResetBlade(0, 0) in state 0x18 unless state 0x14 or a special action runs; true when queued.
    static bool fn_7100321328();
    static bool createMoverSwitch();
    // Placeholder name: new in 3.0.1, like fn_7100321258. What it does: as createMoverSwitch, queues
    // addResetBlade(0, 2) in state 0x18 unless state 0x14 or a special action runs; true when queued.
    static bool fn_71003213F4();
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
};
}  // namespace gf

#endif

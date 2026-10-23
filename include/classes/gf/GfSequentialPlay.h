#ifndef CLASSES_GF_GFSEQUENTIALPLAY_H
#define CLASSES_GF_GFSEQUENTIALPLAY_H

#include "classes/mm/mtl/PtrSingleton.h"
#include "gf/GfQuestInfo.h"
#include "gf/QuestID.h"

namespace gf { class GfSequentialPlay; }
namespace gf { class ParamReturnTitle; }
namespace gf { class GfSequentialPlaySignal; }
namespace gf { class GfMapjumpInfo; }
namespace fw { class Camera; }
#include "mm/mtl/IntrusivePtr.h"
namespace gf { class GfSetupPfTalk; }
namespace gf { class GF_OBJ_HANDLE; }
namespace gf { enum MAINMENU : int; }
namespace gf { class MenuCommonWindowParam; }
namespace gmk { enum GmkType : int; }
#include "classes/gf/GfMenuObjCommonText.h"
namespace gf { enum GF_STATE : int; }  // as GfGameManager.h declares it

namespace gf {
// table 0x7100B590E8
class GfSequentialPlay : public ::mm::mtl::PtrSingleton< ::gf::GfSequentialPlay> {
public:
    // how beginCommand starts a command list (GfPlayFactory passes 0 or 1); no value has a name yet
    enum TYPE {};
    virtual ~GfSequentialPlay();  // slot 0
    // GfPlayFactory's command lists: begun, filled with commands between pushed and popped states and pauses, played
    static void beginCommand(TYPE type);
    static void pushState(GF_STATE state);
    static void popState();
    static void pushPause(unsigned int pause);
    static void popPause();
    static bool play();  // true (GfPlayFactory's create functions answer it)
    static bool isInnerState(GF_STATE state);
    static bool isSequenceSpecialAction();
    static void addReturnTitle(const ParamReturnTitle& param);
    static void addWaitBattleEnd(unsigned int wait);
    static void addMiniGame();
    static void addEventFade();
    static void addMenuZone(unsigned int id);
    static void addMenuChapter(unsigned int id);
    static void addMenuChapterEnd(unsigned int id);
    static void addMenuDummyTutorial(unsigned int id);
    static void addBattleStart(bool flag);
    static void addChainAttack();
    static void addArtsMovie(const char* name);
    static void addResetBlade(unsigned int blade, int mode);
    static void addAfterEventScript(unsigned int id);
    static void addHoodHomuraBattou();
    static void startSignal(GfSequentialPlaySignal* signal);
    static void endSignal(GfSequentialPlaySignal* signal);
    static bool isInnerPause(unsigned int pause);
    static void addOpenMenu(unsigned int menu);
    static void addOpenMenu2(unsigned int menu, MAINMENU main);
    static void addSalvage(GF_OBJ_HANDLE* handle);
    static void addCollect(GF_OBJ_HANDLE* handle);
    static void addFieldTbox(GF_OBJ_HANDLE* handle);
    static void addMapGimmick(GF_OBJ_HANDLE* handle);
    static void addGrave(GF_OBJ_HANDLE* handle);
    static void addJump(GF_OBJ_HANDLE* handle);
    static void addWarp(GF_OBJ_HANDLE* handle);
    static void addWaitPlayerToStartGmkTuto();
    static void addGmkTutorial(const char* name, unsigned int id);
    static void addMapjump(const GfMapjumpInfo& info);
    static void addEventPlayerStop(bool stop);
    static void addCallbackEventSequence(int id, bool begin);
    static void addTalk(const GfSetupPfTalk& talk);
    static void addWait(float time);
    static void addQuestUIOrder(QuestID id, bool flag);
    static void addQuestUIComplete(QuestID id, QuestID next, QSTATE state);
    static void addMenuPrecious(unsigned int id);
    static void addStartTutorial(unsigned int id);
    static void addBattleStartEnd();
    static bool isPlay();
    static void addWaitEvent(float time, GF_OBJ_HANDLE* handle);
    // a common window's handle (GfPlayFactory::createCommonMessage answers it)
    static int addMenuCommon(unsigned int id);
    static int addMenuCommon(const MenuCommonWindowParam& param);
    static void addMenuChapterSave(unsigned int id);
    static void addGimmickTaskComplete(gmk::GmkType type, unsigned int id, float time);
    static bool isExistResetBladeParty(unsigned int slot);
    static void addMoverSwitch();
    static void addWaitGmkCameraEnd(mm::mtl::IntrusivePtr<fw::Camera> camera);
    static void addResetBladePlayerStop(bool stop);
    static void addMenuObjCommonText(GfMenuObjCommonText::OpenKizunaParam& param);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because it fills
    // GfSequentialPlay's unit next to addCallbackEventSequence and its callers use it as one of the command list's
    // add functions (GfPlayFactory::createTalk, createOneEvent, createQuestUIComplete). What it does: when
    // GfGameManager::fn_71002A9E68() holds, makes a command (fn_710031988C) and adds it (addCommand).
    static void fn_71003227E4();
};
}  // namespace gf

#endif

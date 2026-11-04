#ifndef CLASSES_GF_GFSEQUENTIALPLAY_H
#define CLASSES_GF_GFSEQUENTIALPLAY_H

#include "classes/mm/mtl/PtrSingleton.h"
#include "gf/GfQuestInfo.h"
#include "gf/QuestID.h"
#include "mm/mtl/FixedList.h"
#include "classes/gf/GfInfo.h"
#include "mm/mtl/FixedQueue.h"
#include "classes/gf/GfPlayCom.h"
#include "mm/Vec3.h"

namespace gf { class GfSequentialPlay; }
namespace gf { enum WEATYPE : int; }
namespace gf { class ParamReturnTitle; }
namespace fw { class UpdateInfo; }
namespace gf {
// a flag a caller holds while its command list runs: GfPlayComExecuteSignal sets it when the startSignal command
// is made and clears it when the endSignal command starts (the field name is not the original's)
class GfSequentialPlaySignal {
public:
    bool m_active;
};
}  // namespace gf
namespace gf { class GfMapjumpInfo; }
#include "gf/ArenaBattleStart.h"
#include "mm/mtl/FixedVector.h"
namespace fw { class Camera; }
#include "mm/mtl/IntrusivePtr.h"
namespace gf { class GfSetupPfTalk; }
namespace gf { class GF_OBJ_HANDLE; }
namespace gf { enum MAINMENU : int; }
namespace gf { class MenuCommonWindowParam; }
namespace gmk { enum GmkType : int; }
#include "classes/gf/GfMenuObjCommonText.h"
namespace gf { enum GF_STATE : int; }  // as GfGameManager.h declares it
namespace gf { class GfSetupParam; }
namespace gf { struct GF_PAUSE_HANDLE; }
namespace gf { enum GfPlayerDead : int; }
// a command's kind (GfPlayCom::m_kind): hasCommand's first argument; no value has a name yet
namespace gf { enum PCOMTYPE : int {}; }

namespace gf {
// table 0x7100B590E8
class GfSequentialPlay : public ::mm::mtl::PtrSingleton< ::gf::GfSequentialPlay> {
public:
    typedef ::mm::mtl::FixedList<GfPlayCom*, 256> CommandList;
    typedef ::mm::mtl::FixedList<GfPlayCom*, 128> AddList;

    // inline in 3.0.1 (1.0.0's GfSequentialPlay(GfSetupParam const&), initialize and finalize: build and destroy
    // carry them)
    GfSequentialPlay(const GfSetupParam& param) : m_flag(false), m_type(TYPE()) {
        initialize(param);
    }
    void initialize(const GfSetupParam& param) { m_initialized = true; }
    void finalize() {
        while (isPlay()) {
            GfSleep(1);
        }
        destroyCommand();
        m_initialized = false;
    }
    static void build(const GfSetupParam& param);
    static void destroy();
    void destroyCommand();
    static void addCommand(GfPlayCom* com);
    static bool hasCommand(PCOMTYPE type, GfPlayCom* com);
    bool isExistEvent(unsigned int id) const;
    // 2.0.0's symbols name it. A member because both callers (ScriptPlayText's ui isOpenPartyForm and
    // waitCloseFullScreen) call it on PtrSingleton<GfSequentialPlay>::sys(). What it does: for menu 0x24 while
    // GfGameManager::isGameTypeIra holds, looks through the command list at 0x1850 and the one at 0x8 for a
    // GfPlayComOpenMenu2 command of state 0xC whose value at 0x10 is 1; other menus take a second path through the same
    // lists (GfPlayComOpenMenu). The callers pass 0x24 and 0; the MAINMENU is not read.
    bool isOpenMenu2(unsigned int menu, MAINMENU main);
    // 1.0.0's out-of-line copies; isInnerState and isInnerPause inline them in 3.0.1
    bool isExistState(GfPlayCom* com, GF_STATE state) const;
    bool isExistPauseType(GfPlayCom* com, unsigned int pause) const;
    static void postUpdate(const fw::UpdateInfo& info);
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
    static void addEventWeather(WEATYPE weather);
    // 2.0.0's symbols name it (3.0.1's symbols spelled 1.0.0's addEvent(char const*, unsigned int, unsigned int, bool)
    // here; same GfPlayFactory callers). What it does: hands them all to GfPlayComEvent::create and adds the command it makes.
    static void addEvent(int id, unsigned int, unsigned int, const char* bgm, const mm::Vec3* pos,
                              float time);
    static void addPlayerDead(GfPlayerDead dead);
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
    // 2.0.0's symbols name it (3.0.1's symbols spelled 2.0.0's addMoverSwitch; GfPlayFactory::createPartySwitchForIra
    // calls it in both)
    static void addPartySwitch();
    static void addWaitGmkCameraEnd(mm::mtl::IntrusivePtr<fw::Camera> camera);
    static void addResetBladePlayerStop(bool stop);
    static void addMenuObjCommonText(GfMenuObjCommonText::OpenKizunaParam& param);
    // 2.0.0's symbols name it. What it does: when GfGameManager::isGameTypeIra() holds, makes a command
    // (createForEvent) and adds it (addCommand).
    static void addIraCampSaveForEvent();
    // 2.0.0's symbols name it. What it does: when GfGameManager::isGameTypeIra() holds, makes a GfPlayComIraCampSave
    // (GfPlayComIraCampSave::createForTutorial, the one that skips the request unless no other runs) and adds it
    // (addCommand).
    static void addIraCampSaveForTutorial();
    // 2.0.0's symbols name addMapjumpForLeaveArena, addMapjumpForBattleMapFromArena, addWaitArenaStateField; the fn_
    // What they do: addCommand of GfPlayComMapjumpForLeaveArena::create(info),
    // GfPlayComMapjumpForBattleMapFromArena::create(info), GfPlayComWaitArenaStateField::create(),
    // GfPlayComStartChallengeBattle::create(start).
    static void addMapjumpForLeaveArena(const GfMapjumpInfo& info);
    static void addMapjumpForBattleMapFromArena(const GfMapjumpInfo& info);
    static void addWaitArenaStateField();
    static void addStartChallengeBattle(const ArenaBattleStart& start);
    // 2.0.0's symbols name it. A static member because it fills
    // GfSequentialPlay's unit after addMenuObjCommonText and does what the add functions do. What it does:
    // addCommand(GfPlayComScriptTutorialSeq::create(name, startId)); its one caller is
    // GfPlayFactory::createTutorialScript(const char*, unsigned int).
    static void addTutorialScript(const char* name, unsigned int startId);
    // 2.0.0's symbols name it. What it does: addCommand(GfPlayComOpenNpcEntry::create(entries)); its one caller is
    // GfPlayFactory's createNpcEntry (GfMenuManager::gevPlayerControl's), between pushState(6) and popState.
    static void addOpenNpcEntry(const mm::mtl::FixedVector<unsigned short, 256>& entries);
    // what GfPlayComPause and GfPlayComState run when they start
    static void pauseOn(unsigned int pause);
    static void pauseOff();
    // the state before / the state taken off
    static GF_STATE execPushState(GF_STATE state);
    static GF_STATE execPopState();

    CommandList m_list;  // the commands running, first first (the name is not the original's)
    bool m_flag;  // build clears it; nothing in this unit reads it (the name is not the original's)
    ::mm::mtl::FixedQueue<GF_PAUSE_HANDLE*, 128> m_pauses;  // pauseOn's handles, pauseOff's last first
    ::mm::mtl::FixedQueue<GF_STATE, 128> m_states;  // execPushState's states
    AddList m_addList;  // a TYPE 1 list's commands, moved to the front of m_list by postUpdate
    TYPE m_type;  // beginCommand's; play clears it
    bool m_initialized;  // initialize sets it, finalize clears it; postUpdate runs only while it holds
};
}  // namespace gf

#endif

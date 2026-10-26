#include "mm/mtl/FixedList.h"
#include "classes/gf/IFieldSeq.h"
#include "classes/gf/AFieldSeq.h"
#include "classes/gf/GfFieldGrave.h"
#include "classes/gf/GfSequentialPlay.h"
#include "classes/gf/GfPlayComAfterEventScript.h"
#include "classes/gf/GfPlayComEvent.h"
#include "classes/gf/GfPlayComEventFade.h"
#include "classes/gf/GfPlayComGmkCameraSeq.h"
#include "classes/gf/GfPlayComGmkTutorialSeq.h"
#include "classes/gf/GfPlayComMapjump.h"
#include "classes/gf/GfPlayComMenuChapterSave.h"
#include "classes/gf/GfPlayComMenuCommon.h"
#include "classes/gf/GfPlayComMenuCommonFromParam.h"
#include "classes/gf/GfPlayComMenuObjCommonText.h"
#include "classes/gf/GfPlayComMenuPrecious.h"
#include "classes/gf/GfPlayComMoverSwitch.h"
#include "classes/gf/GfPlayComPlayerDead.h"
#include "classes/gf/GfPlayComQuestCompleteUI.h"
#include "classes/gf/GfPlayComQuestOrderUI.h"
#include "classes/gf/GfPlayComResetBlade.h"
#include "classes/gf/GfPlayComResetBladePlayerStop.h"
#include "classes/gf/GfPlayComSalvage.h"
#include "classes/gf/GfPlayComStartTutorial.h"
#include "classes/gf/GfPlayComTalk.h"
#include "classes/gf/GfPlayComWaitBattleEnd.h"
#include "classes/gf/GfPlayComWaitEvent.h"
#include "classes/gf/GfPlayComWaitPlayerToStartGmkTuto.h"
#include "classes/gf/GfPlayComPause.h"
#include "classes/gf/GfPlayComState.h"
#include "classes/gf/GfPlayComWait.h"
#include "classes/gf/GfPlayComCollect.h"
#include "classes/gf/GfPlayComFieldSeq.h"
#include "classes/gf/GfPlayComFieldTbox.h"
#include "classes/gf/GfPlayComMenuZone.h"
#include "classes/gf/GfPlayComMiniGame.h"
#include "classes/gf/GfPlayComOpenMenu.h"
#include "classes/gf/GfPlayComOpenMenu2.h"
#include "classes/gf/GfPlayComArtsMovie.h"
#include "classes/gf/GfPlayComBattleStart.h"
#include "classes/gf/GfPlayComChainAttack.h"
#include "classes/gf/GfPlayComMenuChapter.h"
#include "classes/gf/GfPlayComReturnTitle.h"
#include "classes/gf/GfPlayComExecuteSignal.h"
#include "classes/gf/GfPlayComMenuChapterEnd.h"
#include "classes/gf/GfPlayComEventPlayerStop.h"
#include "classes/gf/GfPlayComHoodHomuraBattou.h"
#include "classes/gf/GfPlayComMenuDummyTutorial.h"
#include "classes/gf/GfPlayComGimmickTaskComplete.h"
#include "classes/gf/GfPlayComCallbackEventSequence.h"
#include "classes/gf/GfPause.h"
#include "classes/gf/GfGameManager.h"
#include "classes/gf/GfManager.h"
#include "classes/gf/GfGameScene.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfFieldMapGimmick.h"
#include "classes/gf/GfFieldJump.h"
#include "classes/gf/GfFieldWarp.h"
#include "classes/fw/Camera.h"
#include "classes/gf/GfPlayComMapjumpForLeaveArena.h"
#include "classes/gf/GfPlayComMapjumpForBattleMapFromArena.h"
#include "classes/gf/GfPlayComWaitArenaStateField.h"
#include "classes/gf/GfPlayComStartChallengeBattle.h"
#include "classes/gf/GfPlayComIraCampSave.h"
#include "classes/gf/GfPlayComScriptTutorialSeq.h"
#include "classes/gf/GfPlayComOpenNpcEntry.h"
#include "classes/gf/GfPlayComEventWeather.h"

namespace gf {

GfSequentialPlay::~GfSequentialPlay() {}

void GfSequentialPlay::build(const GfSetupParam& param) {
#line 52
    new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) GfSequentialPlay(param);
}

void GfSequentialPlay::destroy() {
    GfSequentialPlay* self = get();
    self->finalize();
    delete self;
}

bool GfSequentialPlay::isPlay() {
    return !get()->m_list.empty() || !get()->m_addList.empty();
}

void GfSequentialPlay::destroyCommand() {
    if (!isPlay()) {
        for (CommandList::iterator it = m_list.begin(); it != m_list.end(); ++it) {
            if (*it != nullptr) {
                delete *it;
                *it = nullptr;
            }
        }
        m_list.clear();
        for (AddList::iterator it = m_addList.begin(); it != m_addList.end(); ++it) {
            if (*it != nullptr) {
                delete *it;
                *it = nullptr;
            }
        }
        m_addList.clear();
    }
}

void GfSequentialPlay::postUpdate(const fw::UpdateInfo& info) {
    GfSequentialPlay* self = get();
    if (self == nullptr || !self->m_initialized) {
        return;
    }
    if (self->m_addList.m_num_nodes > 0) {
        for (AddList::iterator it = self->m_addList.begin(); it != self->m_addList.end(); ++it) {
            self->m_list.push_front(*it);
        }
        self->m_addList.clear();
    }
    while (!self->m_list.empty()) {
        CommandList::iterator it = self->m_list.begin();
        GfPlayCom* com = *it;
        if (com->pad_08) {
            com->pad_08 = false;
            com->start();
        }
        if (!com->update(info, GfManager::isDestroyNow())) {
            return;
        }
        com->end();
        bool next = com->pad_09;
        delete com;
        self->m_list.erase(it);
        if (!next) {
            break;
        }
    }
}

bool GfSequentialPlay::play() {
    get()->m_type = TYPE();
    return true;
}

void GfSequentialPlay::beginCommand(TYPE type) {
    get()->m_type = type;
}

void GfSequentialPlay::addCommand(GfPlayCom* com) {
    if (com != nullptr) {
        GfSequentialPlay* self = get();
        if (self->m_type == TYPE(1)) {
            self->m_addList.push_front(com);
        } else {
            self->m_list.push_back(com);
        }
    }
}

void GfSequentialPlay::pauseOn(unsigned int pause) {
    GfSequentialPlay* self = get();
    self->m_pauses.push_back(GfPause::reqPause(pause));
}

void GfSequentialPlay::pauseOff() {
    GfSequentialPlay* self = get();
    GfPause::destroyHandle(self->m_pauses.take_back());
}

GF_STATE GfSequentialPlay::execPushState(GF_STATE state) {
    GfSequentialPlay* self = get();
    GF_STATE prev = GfGameManager::getState();
    self->m_states.push_back(state);
    GfGameManager::setState(state, false);
    return prev;
}

GF_STATE GfSequentialPlay::execPopState() {
    GfSequentialPlay* self = get();
    GF_STATE state = self->m_states.take_back();
    GfGameManager::setState(self->m_states.empty() ? GF_STATE(3) : self->m_states.at((self->m_states.m_size + self->m_states.m_head - 1) % 128), true);
    return state;
}

void GfSequentialPlay::addWait(float time) {
    addCommand(GfPlayComWait::create(time));
}

void GfSequentialPlay::addWaitEvent(float time, GF_OBJ_HANDLE* handle) {
    addCommand(GfPlayComWaitEvent::create(time, handle));
}

void GfSequentialPlay::addMapjump(const GfMapjumpInfo& info) {
    addCommand(GfPlayComMapjump::create(info));
}

void GfSequentialPlay::fn_7100322674(const GfMapjumpInfo& info) {
    addCommand(GfPlayComMapjumpForLeaveArena::create(info));
}

void GfSequentialPlay::fn_7100322688(const GfMapjumpInfo& info) {
    addCommand(GfPlayComMapjumpForBattleMapFromArena::create(info));
}

void GfSequentialPlay::fn_710032269C() {
    addCommand(GfPlayComWaitArenaStateField::create());
}

void GfSequentialPlay::fn_71003226B0(const MsgUnk_1000034::Param& param) {
    addCommand(GfPlayComStartChallengeBattle::create(param));
}

void GfSequentialPlay::addWaitBattleEnd(unsigned int id) {
    addCommand(GfPlayComWaitBattleEnd::create(id));
}

void GfSequentialPlay::addEventPlayerStop(bool flag) {
    addCommand(GfPlayComEventPlayerStop::create(flag));
}

void GfSequentialPlay::addResetBladePlayerStop(bool flag) {
    addCommand(GfPlayComResetBladePlayerStop::create(flag));
}

void GfSequentialPlay::addAfterEventScript(unsigned int id) {
    addCommand(GfPlayComAfterEventScript::create(id));
}

void GfSequentialPlay::pushPause(unsigned int pause) {
    addCommand(GfPlayComPause::create(pause));
}

void GfSequentialPlay::popPause() {
    addCommand(GfPlayComPause::create(0));
}

void GfSequentialPlay::pushState(GF_STATE state) {
    addCommand(GfPlayComState::create(state, get()->m_type != 0));
}

void GfSequentialPlay::popState() {
    addCommand(GfPlayComState::create(GF_STATE(0), false));
}

void GfSequentialPlay::addEventFade() {
    addCommand(GfPlayComEventFade::create());
}

// The symbols name it addEvent(int, ...) (1.0.0's overload at this place, called from createTheaterEvent there and
// here); 3.0.1's body makes a GfPlayComEventWeather from the first argument and reads no other.
void GfSequentialPlay::addEvent(int id, unsigned int, unsigned int, bool) {
    addCommand(GfPlayComEventWeather::fn_7100318730(WEATYPE(id)));
}

void GfSequentialPlay::addCallbackEventSequence(int id, bool begin) {
    addCommand(GfPlayComCallbackEventSequence::create(id, begin));
}

void GfSequentialPlay::fn_71003227E4() {
    if (GfGameManager::fn_71002A9E68()) {
        addCommand(GfPlayComIraCampSave::fn_710031988C());
    }
}

void GfSequentialPlay::fn_7100322808() {
    if (GfGameManager::fn_71002A9E68()) {
        addCommand(GfPlayComIraCampSave::fn_7100319900());
    }
}

void GfSequentialPlay::addMenuPrecious(unsigned int id) {
    addCommand(GfPlayComMenuPrecious::create(id));
}

int GfSequentialPlay::addMenuCommon(unsigned int id) {
    GfPlayComMenuCommon* com = GfPlayComMenuCommon::create(id);
    addCommand(com);
    return com->m_handle;
}

int GfSequentialPlay::addMenuCommon(const MenuCommonWindowParam& param) {
    GfPlayComMenuCommonFromParam* com = GfPlayComMenuCommonFromParam::create(param);
    addCommand(com);
    return com->m_handle;
}

void GfSequentialPlay::addMenuChapterSave(unsigned int id) {
    addCommand(GfPlayComMenuChapterSave::create(id));
}

void GfSequentialPlay::addMenuChapter(unsigned int id) {
    addCommand(GfPlayComMenuChapter::create(id));
}

void GfSequentialPlay::addMenuChapterEnd(unsigned int id) {
    addCommand(GfPlayComMenuChapterEnd::create(id));
}

void GfSequentialPlay::addMenuZone(unsigned int id) {
    addCommand(GfPlayComMenuZone::create(id));
}

void GfSequentialPlay::addMenuDummyTutorial(unsigned int id) {
    addCommand(GfPlayComMenuDummyTutorial::create(id));
}

void GfSequentialPlay::addOpenMenu(unsigned int id) {
    addCommand(GfPlayComOpenMenu::create(id));
}

void GfSequentialPlay::addOpenMenu2(unsigned int menu, MAINMENU main) {
    addCommand(GfPlayComOpenMenu2::create(menu, main));
}

void GfSequentialPlay::addStartTutorial(unsigned int id) {
    addCommand(GfPlayComStartTutorial::create(id));
}

void GfSequentialPlay::fn_7100322930(const mm::mtl::FixedVector<unsigned short, 256>& entries) {
    addCommand(GfPlayComOpenNpcEntry::fn_7100319F34(entries));
}

void GfSequentialPlay::addMiniGame() {
    addCommand(GfPlayComMiniGame::create());
}

void GfSequentialPlay::addReturnTitle(const ParamReturnTitle& param) {
    addCommand(GfPlayComReturnTitle::create(param));
}

void GfSequentialPlay::addBattleStart(bool flag) {
    addCommand(GfPlayComBattleStart::create(flag));
}

void GfSequentialPlay::addBattleStartEnd() {
    if (mm::mtl::PtrSingleton<GfPlayComBattleStart>::get() == nullptr) {
        return;
    }
    addCommand(GfPlayComWait::create(GfGameScene::get() != nullptr && GfGameScene::get()->isRideParty(0) ? 0.6f : 0.3f));
}

void GfSequentialPlay::addSalvage(GF_OBJ_HANDLE* handle) {
    addCommand(GfPlayComSalvage::create(handle));
}

void GfSequentialPlay::addCollect(GF_OBJ_HANDLE* handle) {
    addCommand(GfPlayComCollect::create(handle));
}

void GfSequentialPlay::addFieldTbox(GF_OBJ_HANDLE* handle) {
    addCommand(GfPlayComFieldTbox::create(handle));
}

void GfSequentialPlay::addMapGimmick(GF_OBJ_HANDLE* handle) {
    addCommand(GfPlayComFieldSeq::create(mm::mtl::PtrSingleton<GfFieldMapGimmick>::get(), handle));
}

void GfSequentialPlay::addGrave(GF_OBJ_HANDLE* handle) {
    addCommand(GfPlayComFieldSeq::create(mm::mtl::PtrSingleton<GfFieldGrave>::get(), handle));
}

void GfSequentialPlay::addJump(GF_OBJ_HANDLE* handle) {
    addCommand(GfPlayComFieldSeq::create(mm::mtl::PtrSingleton<GfFieldJump>::get(), handle));
}

void GfSequentialPlay::addWarp(GF_OBJ_HANDLE* handle) {
    addCommand(GfPlayComFieldSeq::create(mm::mtl::PtrSingleton<GfFieldWarp>::get(), handle));
}

void GfSequentialPlay::addWaitPlayerToStartGmkTuto() {
    addCommand(GfPlayComWaitPlayerToStartGmkTuto::create());
}

void GfSequentialPlay::addGmkTutorial(const char* name, unsigned int id) {
    addCommand(GfPlayComGmkTutorialSeq::create(name, id));
}

void GfSequentialPlay::addWaitGmkCameraEnd(mm::mtl::IntrusivePtr<fw::Camera> camera) {
    addCommand(GfPlayComGmkCameraSeq::create(camera));
}

void GfSequentialPlay::addPlayerDead(GfPlayerDead dead) {
    addCommand(GfPlayComPlayerDead::create(dead));
}

void GfSequentialPlay::addTalk(const GfSetupPfTalk& talk) {
    addCommand(GfPlayComTalk::create(talk));
}

void GfSequentialPlay::addQuestUIOrder(QuestID id, bool flag) {
    addCommand(GfPlayComQuestOrderUI::create(id, flag));
}

void GfSequentialPlay::addQuestUIComplete(QuestID id, QuestID next, QSTATE state) {
    addCommand(GfPlayComQuestCompleteUI::create(id, next, state));
}

void GfSequentialPlay::addGimmickTaskComplete(gmk::GmkType type, unsigned int id, float time) {
    addCommand(GfPlayComGimmickTaskComplete::create(type, id, time));
}

void GfSequentialPlay::addChainAttack() {
    addCommand(GfPlayComChainAttack::create());
}

void GfSequentialPlay::addArtsMovie(const char* name) {
    addCommand(GfPlayComArtsMovie::create(name));
}

void GfSequentialPlay::addResetBlade(unsigned int blade, int mode) {
    addCommand(GfPlayComResetBlade::create(blade, mode));
}

void GfSequentialPlay::addMoverSwitch() {
    addCommand(GfPlayComMoverSwitch::create());
}

void GfSequentialPlay::addHoodHomuraBattou() {
    addCommand(GfPlayComHoodHomuraBattou::create());
}

void GfSequentialPlay::addMenuObjCommonText(GfMenuObjCommonText::OpenKizunaParam& param) {
    addCommand(GfPlayComMenuObjCommonText::create(param));
}

void GfSequentialPlay::fn_7100322C64(const char* name, int startId) {
    addCommand(GfPlayComScriptTutorialSeq::fn_710031E044(name, startId));
}

bool GfSequentialPlay::isExistResetBladeParty(unsigned int slot) {
    GfSequentialPlay* self = get();
    for (CommandList::iterator it = self->m_list.begin(); it != self->m_list.end(); ++it) {
        GfPlayCom* com = *it;
        if (com != nullptr && com->m_kind == 42 && com->getRTTI()->isKindOf(&GfPlayComResetBlade::m_rtti) &&
            static_cast<GfPlayComResetBlade*>(com)->m_blade == slot) {
            return true;
        }
    }
    return false;
}

bool GfSequentialPlay::isExistPauseType(GfPlayCom* com, unsigned int pause) const {
    return com->m_kind == 1 && com->getRTTI()->isKindOf(&GfPlayComPause::m_rtti) &&
           (static_cast<GfPlayComPause*>(com)->m_pause & pause) == pause;
}

bool GfSequentialPlay::isInnerPause(unsigned int pause) {
    GfSequentialPlay* self = get();
    for (CommandList::iterator it = self->m_list.begin(); it != self->m_list.end(); ++it) {
        if (self->isExistPauseType(*it, pause)) {
            return true;
        }
    }
    for (AddList::iterator it = self->m_addList.begin(); it != self->m_addList.end(); ++it) {
        if (self->isExistPauseType(*it, pause)) {
            return true;
        }
    }
    return GfPause::isPause(pause);
}

void GfSequentialPlay::startSignal(GfSequentialPlaySignal* signal) {
    addCommand(GfPlayComExecuteSignal::create(true, signal));
}

void GfSequentialPlay::endSignal(GfSequentialPlaySignal* signal) {
    addCommand(GfPlayComExecuteSignal::create(false, signal));
}

}  // namespace gf

#include "classes/gf/GfGameScene.h"
#include "classes/gf/GfMenuManager.h"
#include "gf/GfDataUtil.h"
#include "classes/gf/GfPlayComMenuPrecious.h"
#include "classes/gf/GfPlayComMenuChapterSave.h"
#include "classes/gf/GfPlayComResetBladePlayerStop.h"
#include "classes/gf/GfPlayComEventPlayerStop.h"
#include "classes/gf/GfPlayComStartTutorial.h"
#include "classes/gf/GfPlayComAfterEventScript.h"
#include "gf/GfDataEvent.h"
#include "classes/gf/GfGameEvent.h"
#include "classes/gf/GfReqSmallCom.h"
#include "classes/gf/SCOM_SCRIPT.h"
#include "gf/GfReqCommand.h"
#include "classes/gf/DataParamAcc.h"
#include "classes/gf/GfFieldGmkTutorial.h"
#include "gf/GfGameUtil.h"
#include "classes/gf/GfPlayComWaitEvent.h"
#include "classes/gf/GfPlayComWaitPlayerToStartGmkTuto.h"
#include "classes/tl/TitleMain.h"
#include "gf/ParamReturnTitle.h"
#include "classes/gf/GfPlayComReturnTitle.h"
#include "classes/gf/GfGameManager.h"
#include "gf/ParamReturnTitle.h"
#include "classes/gf/SCOM_SCRIPT.h"
#include "classes/gf/GfReqSmallCom.h"
#include "classes/gf/GfGameEvent.h"
#include "gf/GfDataEvent.h"
#include "classes/tl/TitleMain.h"
#include "classes/gf/GfFieldGmkTutorial.h"
#include "classes/gf/GfGameParty.h"
#include "classes/gf/DataParamAcc.h"
#include "classes/gf/GfFobjManager.h"
#include "classes/gf/GfReqManager.h"
#include "gf/GfReqCommand.h"
#include "mm/Col4.h"
#include "classes/gf/GfScriptManager.h"
#include "plugin/Bdat.h"
#include "gf/GfMenuObjUtil.h"
#include "classes/gf/GfDataBdat.h"
#include "classes/gf/GfGameManager.h"
#include "classes/gf/GfMenuFade.h"
#include "gf/GfDataUtil.h"
#include "gf/GfPlayFactory.h"
#include "gf/GfDataBlade.h"
#include "classes/gf/GfManager.h"
#include "classes/gf/GfGameScene.h"
#include "gf/GfGameUtil.h"
#include "classes/gf/GfPlayComOpenMenu2.h"
#include "classes/gf/GfPlayComBattleStart.h"
#include "classes/gf/GfMenuObjPopup.h"
#include "classes/gf/GfFieldTbox.h"
#include "classes/gf/GfFieldCollect.h"
#include "classes/gf/SCOM_FIELD_VOICE.h"
#include "classes/gf/GfPlayComFieldSeq.h"
#include "classes/gf/GfPlayComFieldTbox.h"
#include "classes/gf/GfPlayComCollect.h"
#include "classes/gf/GfPlayComHoodHomuraBattou.h"
#include "classes/gf/GfPlayComReturnTitle.h"
#include "classes/gf/GfPlayComOpenMenu.h"
#include "classes/gf/GfPlayComMenuDummyTutorial.h"
#include "classes/gf/GfPlayComMenuZone.h"
#include "classes/gf/GfPlayComMenuChapterEnd.h"
#include "classes/gf/GfMenuManager.h"
#include "classes/gf/GfPlayComMenuChapter.h"
#include "gf/FileStaticVec3.h"
#include "classes/gf/IFieldSeq.h"
#include "gf/GfGameUtil.h"
#include "classes/gf/GfMenuObjPopup.h"
#include "classes/gf/GfFieldCollect.h"
#include "classes/gf/SCOM_FIELD_VOICE.h"
#include "classes/gf/GfPlayCom.h"
#include "classes/gf/GfPlayComPause.h"
#include "classes/gf/GfSequentialPlay.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfPlayComState.h"
#include "classes/gf/GfPlayComWait.h"
#include "classes/gf/GfPlayComChainAttack.h"
#include "classes/gf/GfPlayComCallbackEventSequence.h"
#include "classes/gf/GfPlayComMiniGame.h"
#include "classes/gf/GfPlayComExecuteSignal.h"
#include "classes/gf/GfPlayComGimmickTaskComplete.h"
#include "classes/gf/GfPlayComEventPlayerStop.h"
#include "classes/gf/GfEvent.h"
#include "classes/gf/GfMenuManager.h"
#include "classes/gf/GfGameState.h"
#include "classes/gf/GfChainAttack.h"
#include "fw/UpdateInfo.h"
#include "classes/gf/GfGameScene.h"
#include "classes/gf/GfArtsMovie.h"
#include "classes/gf/GfPlayComSalvage.h"
#include "classes/gf/GfPlayComArtsMovie.h"
#include "classes/gf/GfPlayComEventWeather.h"
#include "classes/gf/GfPlayComIraCampSave.h"
#include "classes/gf/GfPlayComOpenNpcEntry.h"
#include "classes/gf/GfPlayComMenuQuestList.h"
#include "classes/gf/GfPlayComMenuKizunaring.h"
#include "classes/gf/GfPlayComMenuCommon.h"
#include "classes/gf/GfPlayComMenuCommonFromParam.h"
#include "classes/gf/GfPlayComResetBlade.h"
#include "classes/gf/GfPlayComMoverSwitch.h"
#include "classes/gf/GfPlayComMapjumpForArena.h"
#include "classes/gf/GfPlayComMapjumpForLeaveArena.h"
#include "classes/gf/GfPlayComMapjumpForBattleMapFromArena.h"
#include "classes/gf/GfPlayComWaitArenaStateField.h"
#include "classes/gf/GfPlayComStartChallengeBattle.h"
#include "classes/gf/GfPlayComScriptTutorialSeq.h"
#include "classes/gf/GfPlayCom.h"
#include "classes/gf/GfPlayComEventFade.h"
#include "classes/gf/GfPlayComWaitEvent.h"
#include "classes/gf/GfPlayComWaitBattleEnd.h"
#include "classes/gf/GfPlayComEventPlayerStop.h"
#include "classes/gf/GfPlayComResetBladePlayerStop.h"
#include "classes/gf/GfPlayComAfterEventScript.h"
#include "classes/gf/GfPlayComEvent.h"
#include "classes/gf/GfPlayComOpenMenu2.h"
#include "classes/gf/GfPlayComStartTutorial.h"
#include "classes/gf/GfPlayComMenuChapterSave.h"
#include "classes/gf/GfPlayComMenuPrecious.h"
#include "classes/gf/GfPlayComCollect.h"
#include "classes/gf/GfPlayComFieldTbox.h"
#include "classes/gf/GfPlayComFieldSeq.h"
#include "classes/gf/GfPlayComWaitPlayerToStartGmkTuto.h"
#include "classes/gf/GfPlayComGmkTutorialSeq.h"
#include "classes/gf/GfPlayComPlayerDead.h"
#include "classes/gf/GfPlayComTalk.h"
#include "classes/gf/GfPlayComQuestOrderUI.h"
#include "classes/gf/GfPlayComQuestCompleteUI.h"
#include "classes/gf/GfPlayComGimmickTaskComplete.h"
#include "classes/gf/GfPlayComReturnTitle.h"
#include "classes/gf/GfPlayComBattleStart.h"
#include "classes/gf/GfPlayComExecuteSignal.h"
#include "classes/gf/GfPlayComChainAttack.h"
#include "classes/gf/GfPlayComArtsMovie.h"
#include "classes/gf/GfPlayComMenuObjCommonText.h"
#include "classes/gf/GfPlayComCallbackEventSequence.h"
#include "classes/gf/GfPlayComGmkCameraSeq.h"
#include "classes/gf/GfPlayComHoodHomuraBattou.h"
#include "classes/gf/GfPlayComMapjump.h"
#include "classes/gf/GfPlayComMenuChapter.h"
#include "classes/gf/GfPlayComMenuChapterEnd.h"
#include "classes/gf/GfPlayComMenuCommon.h"
#include "classes/gf/GfPlayComMenuCommonFromParam.h"
#include "classes/gf/GfPlayComMenuDummyTutorial.h"
#include "classes/gf/GfPlayComMenuZone.h"
#include "classes/gf/GfPlayComMiniGame.h"
#include "classes/gf/GfPlayComOpenMenu.h"
#include "classes/gf/GfPlayComPause.h"
#include "classes/gf/GfPlayComResetBlade.h"
#include "classes/gf/GfPlayComSalvage.h"
#include "classes/gf/GfPlayComState.h"
#include "classes/gf/GfPlayComWait.h"

namespace gf {

void GfPlayComPause::start() {
    if (m_pause != 0) {
        GfSequentialPlay::pauseOn(m_pause);
    } else {
        GfSequentialPlay::pauseOff();
    }
}

void GfPlayComPause::end() {}

bool GfPlayComPause::update(const fw::UpdateInfo& info, bool flag) { return true; }

GfPlayComPause* GfPlayComPause::create(unsigned int pause) {
#line 309
    return new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) GfPlayComPause(pause);
}

void GfPlayComState::start() {
    if (m_state != 0) {
        GfSequentialPlay::execPushState(m_state);
    } else {
        GfSequentialPlay::execPopState();
    }
}

void GfPlayComState::end() {}

bool GfPlayComState::update(const fw::UpdateInfo& info, bool flag) { return true; }

// check: set GfGameState's reserved state only when the reserve holds 3 (the name is not the original's)
GfPlayComState* GfPlayComState::create(GF_STATE state, bool check) {
#line 351
    GfPlayComState* com = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) GfPlayComState(state, check);
    if (!check || GfGameState::getStateReserve() == GF_STATE(3)) {
        GfGameState::setStateReserve(state);
    }
    return com;
}

void GfPlayComWait::start() {}

void GfPlayComWait::end() {}

bool GfPlayComWait::update(const fw::UpdateInfo& info, bool flag) {
    if (flag) {
        return true;
    }
    m_time -= info.m_frameTime;
    return m_time <= 0.0f;
}

GfPlayComWait* GfPlayComWait::create(float time) {
#line 393
    return new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) GfPlayComWait(time);
}

void GfPlayComMapjump::end() {}

void GfPlayComCallbackEventSequence::start() { GfEvent::callEventPlay(GEV(m_begin ? 12 : 13), m_id); }

void GfPlayComCallbackEventSequence::end() {}

bool GfPlayComCallbackEventSequence::update(const fw::UpdateInfo& info, bool flag) { return true; }

GfPlayComCallbackEventSequence* GfPlayComCallbackEventSequence::create(int id, bool begin) {
#line 942
    return new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) GfPlayComCallbackEventSequence(id, begin);
}

// hand: begin GfPlayComOpenMenu::~GfPlayComOpenMenu
GfPlayComWaitEvent::~GfPlayComWaitEvent() { s_activate--; }

void GfPlayComWaitEvent::start() { m_req = GfReqCommand::reqWaitEvent(m_time, m_handle); }

void GfPlayComWaitEvent::end() {
    GfFobjManager* manager = mm::mtl::PtrSingleton<GfFobjManager>::sys();
    manager->m_unusedInt = 0;
    manager->m_unusedFlag = false;
}

bool GfPlayComWaitEvent::update(const fw::UpdateInfo& info, bool flag) {
    for (unsigned int i = 0; i < 3; i++) {
        DataParamAcc acc(GfGameParty::getHandleDriver(i, 0));
        if (acc.isValid() && acc.getHp() == 0) {
            GfGameUtil::setHp(acc.m_handle, 1);
        }
    }
    return !GfReqManager::isValid(m_req);
}

GfPlayComWaitEvent* GfPlayComWaitEvent::create(float time, GF_OBJ_HANDLE* handle) {
#line 462
    return new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) GfPlayComWaitEvent(time, handle);
}

GfPlayComAfterEventScript::~GfPlayComAfterEventScript() { s_activate--; }

void GfPlayComAfterEventScript::start() {
    int startId = GfDataEvent::getEventAfterScriptStartID(m_id);
    const char* name = GfDataEvent::getEventAfterScriptName(m_id);
    if (name != nullptr && name[0] != '\0') {
        GfGameEvent::setAfterEventStartID(startId);
        m_script = SCOM_SCRIPT::create(3, name, true);
        if (GfGameScene* scene = mm::mtl::PtrSingleton<GfGameScene>::sys()) {
            scene->fn_71002C4B80(name);
        }
    }
}

void GfPlayComAfterEventScript::end() { GfGameEvent::setAfterEventStartID(0); }

bool GfPlayComAfterEventScript::update(const fw::UpdateInfo& info, bool flag) {
    if (flag) {
        SCOM_SCRIPT::create(3, nullptr, false);
        return true;
    }
    return !mm::mtl::PtrSingleton<GfReqSmallCom>::sys()->isValid(m_script);
}

GfPlayComAfterEventScript* GfPlayComAfterEventScript::create(unsigned int id) {
    if (GfGameManager::isAdvertize()) {
        GfMenuFade::setFade(1, 0, mm::Col4::black);
    }
#line 788
    return new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) GfPlayComAfterEventScript(id);
}

void GfPlayComEventPlayerStop::start() {
    if (!m_stop) {
        if (--s_stop > 0) {
            return;
        }
        if (GfGameScene* scene = mm::mtl::PtrSingleton<GfGameScene>::sys()) {
            scene->setEventPlayerStop(false);
        }
    }
}

GfPlayComEventPlayerStop* GfPlayComEventPlayerStop::create(bool stop) {
#line 676
    GfPlayComEventPlayerStop* com = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) GfPlayComEventPlayerStop(stop);
    if (stop) {
        if (GfGameScene* scene = mm::mtl::PtrSingleton<GfGameScene>::sys()) {
            scene->setEventPlayerStop(true);
        }
        s_stop++;
    }
    return com;
}

void GfPlayComResetBladePlayerStop::start() {
    if (!m_stop) {
        if (GfGameScene* scene = mm::mtl::PtrSingleton<GfGameScene>::sys()) {
            scene->fn_71002C3450(false);
        }
    }
}

GfPlayComResetBladePlayerStop* GfPlayComResetBladePlayerStop::create(bool stop) {
#line 706
    GfPlayComResetBladePlayerStop* com = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) GfPlayComResetBladePlayerStop(stop);
    if (stop) {
        if (GfGameScene* scene = mm::mtl::PtrSingleton<GfGameScene>::sys()) {
            scene->fn_71002C3450(true);
        }
    }
    return com;
}

// hand: end
GfPlayComOpenMenu::~GfPlayComOpenMenu() { s_active--; }

void GfPlayComOpenMenu::start() {
    GfMenuManager::openMenu(m_menu);
}

void GfPlayComOpenMenu::end() {}

bool GfPlayComOpenMenu::update(const fw::UpdateInfo& info, bool flag) {
    bool result = true;
    if (GfMenuManager::isOpenFullScreen()) {
        result = false;
    }
    if (flag && !result) {
        GfMenuManager::closeFullScreen(true, true);
        result = false;
    }
    return result;
}

GfPlayComOpenMenu* GfPlayComOpenMenu::create(unsigned int menu) {
#line 1064
    return new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) GfPlayComOpenMenu(menu);
}

void GfPlayComMiniGame::start() { GfMenuManager::openFullScreen(4, true, true); }

void GfPlayComMiniGame::end() {}

bool GfPlayComMiniGame::update(const fw::UpdateInfo& info, bool flag) {
    bool result = true;
    if (GfMenuManager::isOpenFullScreen()) {
        result = false;
    }
    if (flag && !result) {
        GfMenuManager::closeFullScreen(true, true);
        result = false;
    }
    return result;
}

GfPlayComMiniGame* GfPlayComMiniGame::create() {
#line 1321
    return new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) GfPlayComMiniGame();
}

// hand: begin GfPlayComMenuChapter::~GfPlayComMenuChapter
void GfPlayComStartTutorial::start() {
    unsigned char* fp = GfDataBdat::getFP(0xFF);
    if (GfMenuObjUtil::fn_710048FD30(3)) {
        if (unsigned char* fpLayer = GfDataBdat::getFP(0x100)) {
            Bdat::getIdTop(fpLayer);
            fp = fpLayer;
        }
    }
    if (fp != nullptr && m_id >= Bdat::getIdTop(fp) && m_id - Bdat::getIdTop(fp) < Bdat::getIdCount(fp)) {
        GfScriptManager::loadScript(4, Bdat::getVal(fp, "script_file", m_id));
        GfScriptManager::startScript(4);
        s_activateCount++;
    }
}

void GfPlayComStartTutorial::end() { s_activateCount--; }

bool GfPlayComStartTutorial::update(const fw::UpdateInfo& info, bool flag) { return GfScriptManager::isScriptFinish(4); }

GfPlayComStartTutorial* GfPlayComStartTutorial::create(unsigned int id) {
#line 1229
    return new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) GfPlayComStartTutorial(id);
}

void GfPlayComMenuChapterSave::start() {
    GfDataUtil::setChapterSave(m_id, GfDataBlade::fn_7100231884());
    m_open = false;
}

void GfPlayComMenuChapterSave::end() {
    GfPlayFactory::createOneEvent(m_id);
    s_bExist = false;
}

bool GfPlayComMenuChapterSave::update(const fw::UpdateInfo& info, bool flag) {
    if (!m_open) {
        GfMenuManager::openSave();
        m_open = true;
        return false;
    }
    return !GfMenuManager::isOpenFullScreen();
}

bool GfPlayComMenuChapterSave::isDisp() { return s_bExist; }

GfPlayComMenuChapterSave* GfPlayComMenuChapterSave::create(unsigned int id) {
#line 1405
    return new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) GfPlayComMenuChapterSave(id);
}

// hand: end
GfPlayComMenuChapter::~GfPlayComMenuChapter() { s_activate--; }

void GfPlayComMenuChapter::start() {
    GfMenuManager::openChapterTelop(m_id);
}

void GfPlayComMenuChapter::end() {}

bool GfPlayComMenuChapter::update(const fw::UpdateInfo& info, bool flag) {
    return !GfMenuManager::isOpenChapterTelop();
}

GfPlayComMenuChapter* GfPlayComMenuChapter::create(unsigned int id) {
#line 1454
    return new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) GfPlayComMenuChapter(id);
}

GfPlayComMenuChapterEnd::~GfPlayComMenuChapterEnd() { s_activate--; }

void GfPlayComMenuChapterEnd::start() {
    GfMenuManager::openChapterEndTelop(m_id);
}

void GfPlayComMenuChapterEnd::end() {}

bool GfPlayComMenuChapterEnd::update(const fw::UpdateInfo& info, bool flag) {
    return !GfMenuManager::isOpenChapterTelop();
}

GfPlayComMenuChapterEnd* GfPlayComMenuChapterEnd::create(unsigned int id) {
#line 1502
    return new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) GfPlayComMenuChapterEnd(id);
}

GfPlayComMenuZone::~GfPlayComMenuZone() { s_activate--; }

void GfPlayComMenuZone::start() {
    GfMenuManager::openZoneTelop(m_id);
    m_time = 10.0f;
}

void GfPlayComMenuZone::end() {}

bool GfPlayComMenuZone::update(const fw::UpdateInfo& info, bool flag) {
    m_time -= info.m_deltaTime;
    if (m_time <= 0.0f) {
        return true;
    }
    return !GfMenuManager::isOpenZoneTelop();
}

GfPlayComMenuZone* GfPlayComMenuZone::create(unsigned int id) {
#line 1558
    return new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) GfPlayComMenuZone(id);
}

GfPlayComMenuDummyTutorial::~GfPlayComMenuDummyTutorial() { s_activate--; }

void GfPlayComMenuDummyTutorial::start() {
    GfMenuManager::openDummyTutorial(m_id);
}

void GfPlayComMenuDummyTutorial::end() {}

bool GfPlayComMenuDummyTutorial::update(const fw::UpdateInfo& info, bool flag) {
    return !GfMenuManager::isOpenDummyTutorial();
}

GfPlayComMenuDummyTutorial* GfPlayComMenuDummyTutorial::create(unsigned int id) {
#line 1602
    return new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) GfPlayComMenuDummyTutorial(id);
}

// hand: begin void GfPlayComMenuCommon::end
GfPlayComMenuPrecious::~GfPlayComMenuPrecious() { s_activate--; }

void GfPlayComMenuPrecious::start() {
    if (!GfManager::isExecModeThater()) {
        GfMenuManager::openPreciousWindow(m_id);
    }
    s_start++;
}

void GfPlayComMenuPrecious::end() { s_start--; }

bool GfPlayComMenuPrecious::update(const fw::UpdateInfo& info, bool flag) { return !GfMenuManager::isOpenPreciousWindow(); }

GfPlayComMenuPrecious* GfPlayComMenuPrecious::create(unsigned int id) {
#line 1739
    return new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) GfPlayComMenuPrecious(id);
}

// hand: end
void GfPlayComMenuCommon::end() {}

void GfPlayComMenuCommonFromParam::end() {}

void GfPlayComSalvage::start() {}

void GfPlayComSalvage::end() {
    if (GfGameScene* scene = mm::mtl::PtrSingleton<GfGameScene>::sys()) {
        scene->destroyPlayerPause(m_pause);
    }
}

void GfPlayComGmkCameraSeq::start() {}

void GfPlayComResetBlade::end() {}

void GfPlayComHoodHomuraBattou::start() {}

void GfPlayComHoodHomuraBattou::end() {}

void GfPlayComChainAttack::start() { m_state = 3; }

void GfPlayComChainAttack::end() { GfChainAttack::destroy(); }

GfPlayComChainAttack* GfPlayComChainAttack::create() {
#line 3191
    return new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) GfPlayComChainAttack();
}

void GfPlayComArtsMovie::start() {
    if (GfArtsMovie* movie = mm::mtl::PtrSingleton<GfArtsMovie>::sys()) {
        movie->startSetup(m_name.m_str);
    }
}

void GfPlayComArtsMovie::end() { GfArtsMovie::destroy(); }

bool GfPlayComArtsMovie::update(const fw::UpdateInfo& info, bool flag) {
    if (GfArtsMovie* movie = mm::mtl::PtrSingleton<GfArtsMovie>::sys()) {
        movie->update(info);
        return false;
    }
    return true;
}

void GfPlayComExecuteSignal::start() {
    if (!m_start) {
        m_signal->m_active = false;
    }
}

GfPlayComExecuteSignal* GfPlayComExecuteSignal::create(bool start, GfSequentialPlaySignal* signal) {
    if (signal == nullptr) {
        return nullptr;
    }
#line 3130
    GfPlayComExecuteSignal* com = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) GfPlayComExecuteSignal(start, signal);
    if (start) {
        signal->m_active = true;
    }
    return com;
}

// generated: GfPlayComReturnTitle
void GfPlayComReturnTitle::start() {
    GfMenuObjPopup::closeAll();
}

GfPlayComReturnTitle* GfPlayComReturnTitle::create(const ParamReturnTitle& param) {
#line 3058
    return new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) GfPlayComReturnTitle(param);
}
// end generated: GfPlayComReturnTitle

// generated: GfPlayComHoodHomuraBattou
GfPlayComHoodHomuraBattou* GfPlayComHoodHomuraBattou::create() {
#line 3519
    return new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) GfPlayComHoodHomuraBattou();
}
// end generated: GfPlayComHoodHomuraBattou

// generated: GfPlayComCollect
void GfPlayComCollect::start() {
    GfFieldCollect::get()->start(m_handle);
    SCOM_FIELD_VOICE::create(CV_FIELD(4), CV_PRIO(1));
}

void GfPlayComCollect::end() {
    if (GfGameScene* scene = mm::mtl::PtrSingleton<GfGameScene>::sys()) {
        scene->destroyPlayerPause(m_pause);
    }
}

GfPlayComCollect* GfPlayComCollect::create(GF_OBJ_HANDLE* handle) {
#line 2117
    GfPlayComCollect* com = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) GfPlayComCollect(handle);
    if (GfGameScene* scene = mm::mtl::PtrSingleton<GfGameScene>::sys()) {
        com->m_pause = scene->createPlayerPause();
    }
    return com;
}
// end generated: GfPlayComCollect

// generated: GfPlayComFieldTbox
void GfPlayComFieldTbox::start() {
    GfFieldTbox::get()->start(m_handle);
    SCOM_FIELD_VOICE::create(CV_FIELD(3), CV_PRIO(1));
}

void GfPlayComFieldTbox::end() {
    if (GfGameScene* scene = mm::mtl::PtrSingleton<GfGameScene>::sys()) {
        scene->destroyPlayerPause(m_pause);
    }
}

GfPlayComFieldTbox* GfPlayComFieldTbox::create(GF_OBJ_HANDLE* handle) {
#line 2258
    return new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) GfPlayComFieldTbox(handle);
}
// end generated: GfPlayComFieldTbox

// generated: GfPlayComFieldSeq
void GfPlayComFieldSeq::start() {
    m_seq->create(m_handle);
}

void GfPlayComFieldSeq::end() {
    m_seq->dispose();
    if (GfGameScene* scene = mm::mtl::PtrSingleton<GfGameScene>::sys()) {
        scene->destroyPlayerPause(m_pause);
    }
}

GfPlayComFieldSeq* GfPlayComFieldSeq::create(IFieldSeq* seq, GF_OBJ_HANDLE* handle) {
    if (get() != nullptr) {
        return nullptr;
    }
#line 2322
    GfPlayComFieldSeq* com = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) GfPlayComFieldSeq(seq, handle);
    if (GfGameScene* scene = mm::mtl::PtrSingleton<GfGameScene>::sys()) {
        com->m_pause = scene->createPlayerPause();
    }
    return com;
}
// end generated: GfPlayComFieldSeq

// generated: GfPlayComBattleStart
bool GfPlayComBattleStart::update(const fw::UpdateInfo& info, bool flag) {
    switch (m_state) {
    case 0:
        if (!GfGameUtil::enterPlayerBattle(m_flag, reinterpret_cast<GF_OBJ_HANDLE*>(-1), false)) {
            m_time += info.m_deltaTime;
            if (m_time < 3.0f) {
                return false;
            }
        }
        m_time = 0.0f;
        m_state = 1;
        return false;
    case 1:
        m_time += info.m_deltaTime;
        if (m_time < 1.0f) {
            return false;
        }
        break;
    }
    if (GfGameScene* scene = mm::mtl::PtrSingleton<GfGameScene>::sys()) {
        scene->setAutoBattle(false);
    }
    return true;
}

GfPlayComBattleStart* GfPlayComBattleStart::create(bool flag) {
#line 3097
    GfPlayComBattleStart* com = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) GfPlayComBattleStart(flag);
    if (GfGameScene* scene = mm::mtl::PtrSingleton<GfGameScene>::sys()) {
        scene->setAutoBattle(true);
    }
    return com;
}
// end generated: GfPlayComBattleStart

// generated: GfPlayComOpenMenu2
void GfPlayComOpenMenu2::start() {
    m_state = 3;
}
// end generated: GfPlayComOpenMenu2

// hand: begin mm::mtl::RTTI GfPlayCom::m_rtti(
bool GfPlayComWaitPlayerToStartGmkTuto::update(const fw::UpdateInfo& info, bool flag) {
    if (!flag) {
        m_time += info.m_deltaTime;
        if (!GfGameManager::isGmkTutorialMoverOK()) {
            if (m_time > 3.0f) {
                mm::mtl::PtrSingleton<GfFieldGmkTutorial>::sys()->m_waitMover = true;
                return true;
            }
            return false;
        }
        mm::mtl::PtrSingleton<GfFieldGmkTutorial>::sys()->m_waitMover = false;
    }
    return true;
}

GfPlayComWaitPlayerToStartGmkTuto* GfPlayComWaitPlayerToStartGmkTuto::create() {
#line 2361
    return new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) GfPlayComWaitPlayerToStartGmkTuto();
}

// hand: end
mm::mtl::RTTI GfPlayCom::m_rtti("GfPlayCom", nullptr, nullptr);
mm::mtl::RTTI GfPlayComEventFade::m_rtti("GfPlayComEventFade", &GfPlayCom::m_rtti, nullptr);
mm::mtl::RTTI GfPlayComEventWeather::m_rtti("GfPlayComEventWeather", &GfPlayCom::m_rtti, nullptr);
mm::mtl::RTTI GfPlayComPause::m_rtti("GfPlayComPause", &GfPlayCom::m_rtti, nullptr);
mm::mtl::RTTI GfPlayComState::m_rtti("GfPlayComState", &GfPlayCom::m_rtti, nullptr);
mm::mtl::RTTI GfPlayComWait::m_rtti("GfPlayComWait", &GfPlayCom::m_rtti, nullptr);
mm::mtl::RTTI GfPlayComWaitEvent::m_rtti("GfPlayComWaitEvent", &GfPlayCom::m_rtti, nullptr);
int GfPlayComWaitEvent::s_activate;
mm::mtl::RTTI GfPlayComMapjump::m_rtti("GfPlayComMapjump", &GfPlayCom::m_rtti, nullptr);
mm::mtl::RTTI GfPlayComWaitBattleEnd::m_rtti("GfPlayComWaitBattleEnd", &GfPlayCom::m_rtti, nullptr);
mm::mtl::RTTI GfPlayComEventPlayerStop::m_rtti("GfPlayComEventPlayerStop", &GfPlayCom::m_rtti, nullptr);
int GfPlayComEventPlayerStop::s_stop;
mm::mtl::RTTI GfPlayComResetBladePlayerStop::m_rtti("GfPlayComResetBladePlayerStop", &GfPlayCom::m_rtti, nullptr);
mm::mtl::RTTI GfPlayComAfterEventScript::m_rtti("GfPlayComAfterEventScript", &GfPlayCom::m_rtti, nullptr);
int GfPlayComAfterEventScript::s_activate;
mm::mtl::RTTI GfPlayComEvent::m_rtti("GfPlayComEvent", &GfPlayCom::m_rtti, nullptr);
mm::mtl::RTTI GfPlayComCallbackEventSequence::m_rtti("GfPlayComCallbackEventSequence", &GfPlayCom::m_rtti, nullptr);
mm::mtl::RTTI GfPlayComIraCampSave::m_rtti("GfPlayComIraCampSave", &GfPlayCom::m_rtti, nullptr);
int GfPlayComOpenMenu::s_active;
mm::mtl::RTTI GfPlayComOpenMenu::m_rtti("GfPlayComOpenMenu", &GfPlayCom::m_rtti, nullptr);
mm::mtl::RTTI GfPlayComOpenMenu2::m_rtti("GfPlayComOpenMenu2", &GfPlayCom::m_rtti, nullptr);
mm::mtl::RTTI GfPlayComStartTutorial::m_rtti("GfPlayComStartTutorial", &GfPlayCom::m_rtti, nullptr);
int GfPlayComStartTutorial::s_activateCount;
mm::mtl::RTTI GfPlayComOpenNpcEntry::m_rtti("GfPlayComOpenNpcEntry", &GfPlayCom::m_rtti, nullptr);
mm::mtl::RTTI GfPlayComMiniGame::m_rtti("GfPlayComMiniGame", &GfPlayCom::m_rtti, nullptr);
mm::mtl::RTTI GfPlayComMenuChapterSave::m_rtti("GfPlayComMenuChapterSave", &GfPlayCom::m_rtti, nullptr);
bool GfPlayComMenuChapterSave::s_bExist;
mm::mtl::RTTI GfPlayComMenuChapter::m_rtti("GfPlayComMenuChapter", &GfPlayCom::m_rtti, nullptr);
int GfPlayComMenuChapter::s_activate;
mm::mtl::RTTI GfPlayComMenuChapterEnd::m_rtti("GfPlayComMenuChapterEnd", &GfPlayCom::m_rtti, nullptr);
int GfPlayComMenuChapterEnd::s_activate;
mm::mtl::RTTI GfPlayComMenuZone::m_rtti("GfPlayComMenuZone", &GfPlayCom::m_rtti, nullptr);
int GfPlayComMenuZone::s_activate;
mm::mtl::RTTI GfPlayComMenuDummyTutorial::m_rtti("GfPlayComMenuDummyTutorial", &GfPlayCom::m_rtti, nullptr);
int GfPlayComMenuDummyTutorial::s_activate;
mm::mtl::RTTI GfPlayComMenuQuestList::m_rtti("GfPlayComMenuQuestList", &GfPlayCom::m_rtti, nullptr);
mm::mtl::RTTI GfPlayComMenuKizunaring::m_rtti("GfPlayComMenuKizunaring", &GfPlayCom::m_rtti, nullptr);
mm::mtl::RTTI GfPlayComMenuPrecious::m_rtti("GfPlayComMenuPrecious", &GfPlayCom::m_rtti, nullptr);
int GfPlayComMenuPrecious::s_activate;
int GfPlayComMenuPrecious::s_start;
mm::mtl::RTTI GfPlayComMenuCommon::m_rtti("GfPlayComMenuCommon", &GfPlayCom::m_rtti, nullptr);
mm::mtl::FixedQueue<unsigned int, 32> GfPlayComMenuCommon::s_list;
mm::mtl::RTTI GfPlayComMenuCommonFromParam::m_rtti("GfPlayComMenuCommonFromParam", &GfPlayCom::m_rtti, nullptr);
mm::mtl::FixedQueue<unsigned int, 32> GfPlayComMenuCommonFromParam::s_list;
mm::mtl::RTTI GfPlayComSalvage::m_rtti("GfPlayComSalvage", &GfPlayCom::m_rtti, nullptr);
mm::mtl::RTTI GfPlayComCollect::m_rtti("GfPlayComCollect", &GfPlayCom::m_rtti, nullptr);
mm::mtl::RTTI GfPlayComFieldTbox::m_rtti("GfPlayComFieldTbox", &GfPlayCom::m_rtti, nullptr);
mm::mtl::RTTI GfPlayComFieldSeq::m_rtti("GfPlayComFieldSeq", &GfPlayCom::m_rtti, nullptr);
mm::mtl::RTTI GfPlayComWaitPlayerToStartGmkTuto::m_rtti("GfPlayComWaitPlayerToStartGmkTuto", &GfPlayCom::m_rtti, nullptr);
mm::mtl::RTTI GfPlayComGmkTutorialSeq::m_rtti("GfPlayComGmkTutorialSeq", &GfPlayCom::m_rtti, nullptr);
mm::mtl::RTTI GfPlayComGmkCameraSeq::m_rtti("GfPlayComGmkCameraSeq", &GfPlayCom::m_rtti, nullptr);
mm::mtl::RTTI GfPlayComPlayerDead::m_rtti("GfPlayComPlayerDead", &GfPlayCom::m_rtti, nullptr);
mm::mtl::RTTI GfPlayComTalk::m_rtti("GfPlayComTalk", &GfPlayCom::m_rtti, nullptr);
mm::mtl::RTTI GfPlayComQuestOrderUI::m_rtti("GfPlayComQuestOrderUI", &GfPlayCom::m_rtti, nullptr);
mm::mtl::RTTI GfPlayComQuestCompleteUI::m_rtti("GfPlayComQuestCompleteUI", &GfPlayCom::m_rtti, nullptr);
mm::mtl::RTTI GfPlayComGimmickTaskComplete::m_rtti("GfPlayComGimmickTaskComplete", &GfPlayCom::m_rtti, nullptr);
mm::mtl::RTTI GfPlayComReturnTitle::m_rtti("GfPlayComReturnTitle", &GfPlayCom::m_rtti, nullptr);
mm::mtl::RTTI GfPlayComBattleStart::m_rtti("GfPlayComBattleStart", &GfPlayCom::m_rtti, nullptr);
mm::mtl::RTTI GfPlayComExecuteSignal::m_rtti("GfPlayComExecuteSignal", &GfPlayCom::m_rtti, nullptr);
mm::mtl::RTTI GfPlayComChainAttack::m_rtti("GfPlayComChainAttack", &GfPlayCom::m_rtti, nullptr);
mm::mtl::RTTI GfPlayComArtsMovie::m_rtti("GfPlayComArtsMovie", &GfPlayCom::m_rtti, nullptr);
mm::mtl::RTTI GfPlayComResetBlade::m_rtti("GfPlayComResetBlade", &GfPlayCom::m_rtti, nullptr);
mm::mtl::FixedVector<signed char, 3> GfPlayComResetBlade::s_execFlag;
mm::mtl::RTTI GfPlayComMoverSwitch::m_rtti("GfPlayComMoverSwitch", &GfPlayCom::m_rtti, nullptr);
mm::mtl::RTTI GfPlayComHoodHomuraBattou::m_rtti("GfPlayComHoodHomuraBattou", &GfPlayCom::m_rtti, nullptr);
mm::mtl::RTTI GfPlayComMenuObjCommonText::m_rtti("GfPlayComMenuObjCommonText", &GfPlayCom::m_rtti, nullptr);
mm::mtl::RTTI GfPlayComMapjumpForArena::m_rtti("GfPlayComMapjumpForArena", &GfPlayCom::m_rtti, nullptr);
mm::mtl::RTTI GfPlayComMapjumpForLeaveArena::m_rtti("GfPlayComMapjumpForLeaveArena", &GfPlayCom::m_rtti, nullptr);
mm::mtl::RTTI GfPlayComMapjumpForBattleMapFromArena::m_rtti("GfPlayComMapjumpForBattleMapFromArena", &GfPlayCom::m_rtti, nullptr);
mm::mtl::RTTI GfPlayComWaitArenaStateField::m_rtti("GfPlayComWaitArenaStateField", &GfPlayCom::m_rtti, nullptr);
mm::mtl::RTTI GfPlayComStartChallengeBattle::m_rtti("GfPlayComStartChallengeBattle", &GfPlayCom::m_rtti, nullptr);
mm::mtl::RTTI GfPlayComScriptTutorialSeq::m_rtti("GfPlayComScriptTutorialSeq", &GfPlayCom::m_rtti, nullptr);

}  // namespace gf

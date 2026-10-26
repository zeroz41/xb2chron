#include "classes/gf/GfGameEvent.h"
#include "classes/gf/GfFieldBgm.h"
#include "classes/gf/GfPlayComEvent.h"
#include "classes/gf/GfPlayComPlayerDead.h"
#include "btl/Utility.h"
#include "classes/gf/GfGameScene.h"
#include "classes/gf/GfPlayComWaitBattleEnd.h"
#include "gf/MsgObjectHealHp.h"
#include "gf/GfObjUtil.h"
#include "classes/gf/GfObj.h"
#include "classes/gf/GfPlayComScriptTutorialSeq.h"
#include "classes/gf/GfGameScene.h"
#include "classes/gf/GfFieldWeather.h"
#include "classes/gf/GfPlayComEventWeather.h"
#include "classes/gf/GfPlayComIraCampSave.h"
#include "gf/GfReqParam.h"
#include "gf/GfReqCommand.h"
#include "classes/gf/GfPlayComMapjump.h"
#include "classes/gf/GfMenuObjCommonText.h"
#include "classes/gf/GfPlayComResetBlade.h"
#include "classes/gf/GfPlayComMenuObjCommonText.h"
#include "classes/gf/GfGameParty.h"
#include "gf/GfReqCommand.h"
#include "algorithm"
#include "classes/gf/GfPlayComGmkCameraSeq.h"
#include "classes/gf/GfPlayComGmkTutorialSeq.h"
#include "classes/gf/GfMenuManager.h"
#include "classes/gf/MenuCommonWindowParam.h"
#include "classes/gf/GfPlayComMenuCommon.h"
#include "classes/gf/GfPlayComMenuCommonFromParam.h"
#include "classes/gf/GfPlayComQuestOrderUI.h"
#include "classes/gf/GfPlayComQuestCompleteUI.h"
#include "classes/gf/GfMenuObjQuestLog.h"
#include "classes/gf/GfQuestManager.h"
#include "classes/gf/GfGameScene.h"
#include "classes/gf/GfGameEvent.h"
#include "classes/gf/GfFieldGimmick.h"
#include "classes/gf/GfPlayComEventFade.h"
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
// hand4: begin #include "fw/UpdateInfo.h"
#include "gf/GfQuestTask.h"
#include "classes/gf/SCOM_FADE.h"
#include "classes/gf/GfMenuCallContext.h"
#include "classes/gf/GfQuestEvent.h"
#include "gf/GfQuestInfo.h"
#include "classes/gf/GfFieldGimmick.h"

// hand4: end
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
#include "classes/gf/TUnk_B535D0.h"
#include "gf/MsgUnk_1000034.h"
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
// hand5: begin #include "classes/gf/GfPlayComMenuObjCommonText.h"
#include "gf/GfObjAcc.h"
#include <algorithm>

// hand5: end
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

void GfPlayComMapjump::start() { m_req = GfReqCommand::reqMapjump(m_info); }

void GfPlayComMapjump::end() {}

bool GfPlayComMapjump::update(const fw::UpdateInfo& info, bool flag) {
    if (flag) {
        return true;
    }
    return !GfReqManager::isValid(m_req);
}

GfPlayComMapjump* GfPlayComMapjump::create(const GfMapjumpInfo& info) {
#line 501
    return new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) GfPlayComMapjump(info);
}

void GfPlayComWaitBattleEnd::start() {
    if (GfGameScene* scene = mm::mtl::PtrSingleton<GfGameScene>::sys()) {
        scene->setForceStopBattle(true);
        if (m_eventId != 0) {
            unsigned int type = GfDataEvent::getEventType(m_eventId) - 1;
            if (type < 3 && scene->isNeedResetBladeForBattleEndForBattleEnd()) {
                btl::Utility::fn_71000100F0();
            }
        }
    }
    m_time = 0.0f;
    s_activate++;
}

void GfPlayComWaitBattleEnd::end() {
    if (GfGameScene* scene = mm::mtl::PtrSingleton<GfGameScene>::sys()) {
        scene->setForceStopBattle(false);
    }
    s_activate--;
}

GfPlayComWaitBattleEnd* GfPlayComWaitBattleEnd::create(unsigned int eventId) {
#line 637
    return new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) GfPlayComWaitBattleEnd(eventId);
}

GfPlayComEvent::~GfPlayComEvent() { m_activate--; }

void GfPlayComEvent::start() {
    GfEvent::addEventCallback(this);
    GfGameEvent::setAfterEventStartID(0);
    GfGameEvent::fn_71002A0CDC(m_event, pad_1C, pad_20, &m_pos, m_time);
}

void GfPlayComEvent::end() { GfEvent::removeEventCallback(this); }

bool GfPlayComEvent::update(const fw::UpdateInfo& info, bool flag) {
    if (flag) {
        return true;
    }
    if (!GfGameEvent::isPlaying()) {
        return true;
    }
    if (GfPlayComPlayerDead* dead = mm::mtl::PtrSingleton<GfPlayComPlayerDead>::sys()) {
        dead->m_eventPlaying = true;
        return false;
    }
    return false;
}

void GfPlayComEvent::gevPlayEvent(GEV gev, unsigned int id) {
    if (gev == GEV(10)) {
        m_eventStarted = true;
    } else if (gev == GEV(14)) {
        if (m_bgm.m_nLen != 0) {
            if (GfFieldBgm* bgm = mm::mtl::PtrSingleton<GfFieldBgm>::sys()) {
                bgm->fn_7100262E58(m_bgm);
            }
            m_bgm.clear();
        }
    }
}

void GfPlayComCallbackEventSequence::start() { GfEvent::callEventPlay(GEV(m_begin ? 12 : 13), m_id); }

void GfPlayComCallbackEventSequence::end() {}

bool GfPlayComCallbackEventSequence::update(const fw::UpdateInfo& info, bool flag) { return true; }

GfPlayComCallbackEventSequence* GfPlayComCallbackEventSequence::create(int id, bool begin) {
#line 942
    return new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) GfPlayComCallbackEventSequence(id, begin);
}

GfPlayComIraCampSave::~GfPlayComIraCampSave() { s_activate--; }

void GfPlayComIraCampSave::start() {
    if (s_activate == 1 && !m_skip) {
        GfGameScene* scene = GfGameScene::get();
        if (scene != nullptr && scene->m_iraCampSolo) {
            scene->m_iraCampSolo = false;
            m_req = GfReqCommand::reqSoloParty(22);
        }
    }
}

void GfPlayComIraCampSave::end() {}

bool GfPlayComIraCampSave::update(const fw::UpdateInfo& info, bool flag) {
    if (GfReqManager::isValid(m_req)) {
        return false;
    }
    m_req = -1;
    return true;
}

// hand: begin GfPlayComOpenMenu::~GfPlayComOpenMenu
// hand4: begin GfPlayComWaitEvent::~GfPlayComWaitEvent
void GfPlayComEventFade::start() {
    s_start++;
    m_wait = GfGameEvent::getFadeInWaitSec();
    m_fadeTime = GfGameEvent::getFadeInSec();
    m_timeout = 10.0f;
    m_mapId = GfGameManager::getMapID();
}

void GfPlayComEventFade::end() {
    if (m_state >= 1) {
        if (GfGameScene* scene = mm::mtl::PtrSingleton<GfGameScene>::sys()) {
            scene->setPlayerTalkForce(false);
        }
        mm::mtl::PtrSingleton<GfFieldGimmick>::sys()->m_eventFade.m_active = false;
    }
    s_start--;
}

GfPlayComEventFade* GfPlayComEventFade::create() {
#line 254
    return new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) GfPlayComEventFade();
}

void GfPlayComEventWeather::start() {
    if (GfFieldWeather::get() == nullptr) {
        return;
    }
    if (m_weather == 0x15) {
        return;
    }
    GfFieldWeather::setWeatherForEvent(m_weather, nullptr);
}

GfPlayComEventWeather* GfPlayComEventWeather::fn_7100318730(WEATYPE weather) {
#line 276
    return new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) GfPlayComEventWeather(weather);
}

// hand4: end
GfPlayComWaitEvent::~GfPlayComWaitEvent() { s_activate--; }

void GfPlayComWaitEvent::start() { m_req = GfReqCommand::reqWaitEvent(m_time, m_handle); }

void GfPlayComWaitEvent::end() {
    GfFobjManager* manager = mm::mtl::PtrSingleton<GfFobjManager>::sys();
    manager->m_waitEventValue = 0;
    manager->m_waitEvent = false;
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
            scene->setResetBladePlayerStop(false);
        }
    }
}

GfPlayComResetBladePlayerStop* GfPlayComResetBladePlayerStop::create(bool stop) {
#line 706
    GfPlayComResetBladePlayerStop* com = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) GfPlayComResetBladePlayerStop(stop);
    if (stop) {
        if (GfGameScene* scene = mm::mtl::PtrSingleton<GfGameScene>::sys()) {
            scene->setResetBladePlayerStop(true);
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
        GfScriptManager::loadScript(4, reinterpret_cast<const char*>(Bdat::getVal(fp, "script_file", m_id)));
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
// hand4: begin void GfPlayComMenuCommon::end
void GfPlayComMenuCommon::start() {
    if (!GfGameManager::isAdvertize()) {
        SCOM_FADE::create(1, 15, mm::Col4::zero);
    }
    GfMenuManager::openCommonWindow(m_id);
}

// hand4: end
void GfPlayComMenuCommon::end() {}

// hand4: begin void GfPlayComMenuCommonFromParam::end
bool GfPlayComMenuCommon::update(const fw::UpdateInfo& info, bool flag) {
    if (!flag && GfMenuManager::isOpenCommonWindow()) {
        if (!GfGameManager::isLeaveGameForDebug()) {
            return false;
        }
        GfMenuManager::closeCommonWindow();
    }
    return true;
}

GfPlayComMenuCommon::~GfPlayComMenuCommon() {
    for (mm::mtl::FixedQueue<unsigned int, 32>::iterator it = s_list.begin(); it != s_list.end(); ++it) {
        if ((*it & 0xFFFFFF) == m_handle) {
            *it = ((GfMenuManager::getCommonWindowResult() + 1) << 24) | m_handle;
            break;
        }
    }
}

bool GfPlayComMenuCommon::isDisp(unsigned int id) {
    for (mm::mtl::FixedQueue<unsigned int, 32>::iterator it = s_list.begin(); it != s_list.end(); ++it) {
        if ((*it >> 24) == 0 && (*it & 0xFFFFFF) == id) {
            return true;
        }
    }
    return false;
}

int GfPlayComMenuCommon::getResult(unsigned int id) {
    for (mm::mtl::FixedQueue<unsigned int, 32>::iterator it = s_list.begin(); it != s_list.end(); ++it) {
        if ((*it & 0xFFFFFF) == id) {
            return *it >> 24;
        }
    }
    return 0;
}

GfPlayComMenuCommon* GfPlayComMenuCommon::create(unsigned int id) {
    unsigned int handle = s_gblHandle++;
#line 1837
    GfPlayComMenuCommon* com = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) GfPlayComMenuCommon(id, handle);
    if (s_list.size() >= 32) {
        s_list.pop_front();
    }
    s_list.push_back(com->m_handle);
    return com;
}

void GfPlayComMenuCommonFromParam::start() {
    if (!GfGameManager::isAdvertize()) {
        SCOM_FADE::create(1, 15, mm::Col4::zero);
    }
    GfMenuManager::openCommonWindow(m_param);
}

// hand4: end
void GfPlayComMenuCommonFromParam::end() {}

void GfPlayComSalvage::start() {}

// hand4: begin void GfPlayComSalvage::end
bool GfPlayComMenuCommonFromParam::update(const fw::UpdateInfo& info, bool flag) {
    if (!flag && GfMenuManager::isOpenCommonWindow()) {
        if (!GfGameManager::isLeaveGameForDebug()) {
            return false;
        }
        GfMenuManager::closeCommonWindow();
    }
    return true;
}

GfPlayComMenuCommonFromParam::~GfPlayComMenuCommonFromParam() {
    for (mm::mtl::FixedQueue<unsigned int, 32>::iterator it = s_list.begin(); it != s_list.end(); ++it) {
        if ((*it & 0xFFFFFF) == m_handle) {
            *it = ((GfMenuManager::getCommonWindowResult() + 1) << 24) | m_handle;
            break;
        }
    }
}

GfPlayComMenuCommonFromParam* GfPlayComMenuCommonFromParam::create(const MenuCommonWindowParam& param) {
    unsigned int handle = s_gblHandle++;
#line 1935
    GfPlayComMenuCommonFromParam* com = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) GfPlayComMenuCommonFromParam(param, handle);
    if (s_list.size() >= 32) {
        s_list.pop_front();
    }
    s_list.push_back(com->m_handle);
    return com;
}

// hand4: end
void GfPlayComSalvage::end() {
    if (GfGameScene* scene = mm::mtl::PtrSingleton<GfGameScene>::sys()) {
        scene->destroyPlayerPause(m_pause);
    }
}

// hand5: begin void GfPlayComGmkCameraSeq::start() {}
GfPlayComGmkCameraSeq::~GfPlayComGmkCameraSeq() {
    s_activate--;
}

// hand5: end
// hand5: begin void GfPlayComGmkCameraSeq::start() {}
GfPlayComGmkTutorialSeq::GfPlayComGmkTutorialSeq(const char* name, unsigned int id) : GfPlayCom(30, false) {
    m_name = name;
    m_id = id;
    if (GfGameScene* scene = mm::mtl::PtrSingleton<GfGameScene>::sys()) {
        m_pause = scene->createPlayerPause();
    }
    s_activate++;
}

GfPlayComGmkTutorialSeq::~GfPlayComGmkTutorialSeq() {
    s_activate--;
}

void GfPlayComGmkTutorialSeq::start() {
    GfFieldGmkTutorial* tutorial = mm::mtl::PtrSingleton<GfFieldGmkTutorial>::sys();
    if (!tutorial->m_waitMover) {
        tutorial->create(m_name.m_str, m_id);
    }
}

void GfPlayComGmkTutorialSeq::end() {
    mm::mtl::PtrSingleton<GfFieldGmkTutorial>::sys()->dispose();
    if (GfGameScene* scene = mm::mtl::PtrSingleton<GfGameScene>::sys()) {
        scene->destroyPlayerPause(m_pause);
    }
}

GfPlayComGmkTutorialSeq* GfPlayComGmkTutorialSeq::create(const char* name, unsigned int id) {
#line 2458
    return new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) GfPlayComGmkTutorialSeq(name, id);
}

// hand5: end
void GfPlayComGmkCameraSeq::start() {}

// hand5: begin void GfPlayComResetBlade::end() {}
void GfPlayComResetBlade::start() {
    m_wait = 3;
}

bool GfPlayComResetBlade::update(const fw::UpdateInfo& info, bool flag) {
    switch (m_state) {
    case 0: {
        if (GfGameManager::isBattle()) {
            return true;
        }
        if (m_blade <= 2) {
            GfObjAcc acc(GfGameParty::getHandleDriver(m_blade, 0));
            if (acc.isBattle()) {
                return true;
            }
        }
        if (--m_wait > 0) {
            return false;
        }
        if (GfSequentialPlay::isSequenceSpecialAction()) {
            return true;
        }
        if (GfGameManager::fn_71002A9E68()) {
            if (m_blade <= 2) {
                if (m_mode == 0) {
                    GfGameParty::fn_71002BC718(m_blade);
                } else if (m_mode == 1) {
                    GfGameParty::fn_71002BC7AC(m_blade);
                } else if (m_mode == 2) {
                    GfGameParty::fn_71002BC840(m_blade);
                }
                return true;
            }
            // the original passes no second argument (w1 is never set before the call; 3.0.1's
            // reqChangeBladeWithBladeId reads neither): an uninitialized local reproduces that
            unsigned int blade;
            m_req = GfReqCommand::reqChangeBladeWithBladeId(m_blade, blade);
        } else {
            m_req = GfReqCommand::reqChangeBladeWithSetId(m_blade, m_mode, true);
        }
        m_state = 1;
        return false;
    }
    case 1:
        if (GfReqManager::isValid(m_req)) {
            return false;
        }
        m_req = -1;
        return true;
    }
    return true;
}

GfPlayComResetBlade* GfPlayComResetBlade::create(unsigned int blade, int mode) {
#line 3349
    return new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) GfPlayComResetBlade(blade, mode);
}

GfPlayComResetBlade::~GfPlayComResetBlade() {
    signed char* it = std::find(s_execFlag.begin(), s_execFlag.end(), static_cast<signed char>(m_blade));
    if (it != s_execFlag.end()) {
        s_execFlag.erase(it);
    }
}

bool GfPlayComResetBlade::isPlaying(unsigned int slot) {
    return std::find(s_execFlag.begin(), s_execFlag.end(), static_cast<signed char>(slot)) != s_execFlag.end();
}

void GfPlayComMenuObjCommonText::start() {
    m_context = GfMenuCallContext::create();
    GfMenuObjCommonText::openKizunaDialog(m_context, m_param);
}

void GfPlayComMenuObjCommonText::end() {
    if (m_context != nullptr) {
        GfMenuObjCommonText::close();
        if (m_context != nullptr) {
            m_context->release();
            m_context = nullptr;
        }
    }
}

bool GfPlayComMenuObjCommonText::update(const fw::UpdateInfo& info, bool flag) {
    if (flag) {
        return true;
    }
    return m_context->isTerm();
}


GfPlayComMenuObjCommonText::~GfPlayComMenuObjCommonText() {
    s_activate--;
}

GfPlayComMenuObjCommonText* GfPlayComMenuObjCommonText::create(GfMenuObjCommonText::OpenKizunaParam& param) {
#line 3577
    return new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) GfPlayComMenuObjCommonText(param);
}

void GfPlayComMapjumpForLeaveArena::start() {
    m_started = true;
    if (TUnk_B535D0* arena = mm::mtl::PtrSingleton<TUnk_B535D0>::sys()) {
        MsgUnk_1000034 msg(9);
        arena->recieveMessage(arena, msg);
    }
}

void GfPlayComMapjumpForLeaveArena::end() {
    if (TUnk_B535D0* arena = mm::mtl::PtrSingleton<TUnk_B535D0>::sys()) {
        MsgUnk_1000034 msg(10);
        arena->recieveMessage(arena, msg);
    }
}

bool GfPlayComMapjumpForLeaveArena::update(const fw::UpdateInfo& info, bool flag) {
    if (flag) {
        return true;
    }
    TUnk_B535D0* arena = mm::mtl::PtrSingleton<TUnk_B535D0>::sys();
    if (arena && !arena->fn_7100291CAC()) {
        return false;
    }
    if (m_req == -1) {
        m_req = GfReqCommand::reqMapjump(m_info);
    }
    return !GfReqManager::isValid(m_req);
}

GfPlayComMapjumpForLeaveArena* GfPlayComMapjumpForLeaveArena::create(const GfMapjumpInfo& info) {
#line 3707
    return new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) GfPlayComMapjumpForLeaveArena(info);
}

void GfPlayComMapjumpForBattleMapFromArena::start() {
    m_started = true;
    m_req = GfReqCommand::reqMapjump(m_info);
}

void GfPlayComMapjumpForBattleMapFromArena::end() {
    if (TUnk_B535D0* arena = mm::mtl::PtrSingleton<TUnk_B535D0>::sys()) {
        MsgUnk_1000034 msg(1);
        arena->recieveMessage(arena, msg);
    }
}

bool GfPlayComMapjumpForBattleMapFromArena::update(const fw::UpdateInfo& info, bool flag) {
    if (flag) {
        return true;
    }
    return !GfReqManager::isValid(m_req);
}

GfPlayComMapjumpForBattleMapFromArena* GfPlayComMapjumpForBattleMapFromArena::create(const GfMapjumpInfo& info) {
#line 3753
    return new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) GfPlayComMapjumpForBattleMapFromArena(info);
}

bool GfPlayComWaitArenaStateField::update(const fw::UpdateInfo& info, bool flag) {
    if (!flag) {
        TUnk_B535D0* arena = mm::mtl::PtrSingleton<TUnk_B535D0>::sys();
        if (arena && !arena->fn_7100291DA0()) {
            return false;
        }
    }
    return true;
}

GfPlayComWaitArenaStateField* GfPlayComWaitArenaStateField::create() {
#line 3785
    return new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) GfPlayComWaitArenaStateField();
}

void GfPlayComStartChallengeBattle::start() {
    GfEvent::addEventCallback(this);
    if (TUnk_B535D0* arena = mm::mtl::PtrSingleton<TUnk_B535D0>::sys()) {
        MsgUnk_1000034 msg(13);
        msg.m_param8 = m_param.pad_8;
        msg.m_param0 = m_param.pad_0;
        arena->recieveMessage(arena, msg);
    }
}

void GfPlayComStartChallengeBattle::end() { GfEvent::removeEventCallback(this); }

void GfPlayComStartChallengeBattle::gevMapjump(GEV gev, const MapjumpCallbackInfo& info) {
    if (gev == 2) {
        m_mapjumped = true;
    }
}

GfPlayComStartChallengeBattle* GfPlayComStartChallengeBattle::create(const MsgUnk_1000034::Param& param) {
#line 3851
    return new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) GfPlayComStartChallengeBattle(param);
}

// hand5: end
// hand5: begin void GfPlayComResetBlade::end() {}
void GfPlayComGmkCameraSeq::end() {
    if (GfGameScene* scene = mm::mtl::PtrSingleton<GfGameScene>::sys()) {
        scene->destroyPlayerPause(m_pause);
    }
}

bool GfPlayComGmkCameraSeq::update(const fw::UpdateInfo& info, bool flag) {
    if (!flag && m_camera->m_pushed) {
        return false;
    }
    GfGameManager::setGmkTutorialSequenceOK(false);
    GfGameManager::setGmkTutorialMoverOK(false);
    return true;
}

GfPlayComGmkCameraSeq* GfPlayComGmkCameraSeq::create(mm::mtl::IntrusivePtr<fw::Camera> camera) {
#line 2515
    return new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) GfPlayComGmkCameraSeq(camera);
}

// hand5: end
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

// hand4: begin GfPlayComReturnTitle* GfPlayComReturnTitle::create
bool GfPlayComGimmickTaskComplete::update(const fw::UpdateInfo& info, bool flag) {
    m_time -= info.m_deltaTime;
    if (m_time > 0.0f) {
        return false;
    }
    GfQuestTask::completeGimmickTask(m_type, m_id);
    return true;
}

GfPlayComGimmickTaskComplete* GfPlayComGimmickTaskComplete::create(gmk::GmkType type, unsigned int id, float time) {
#line 3004
    return new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) GfPlayComGimmickTaskComplete(type, id, time);
}

// hand4: end
// hand4: begin GfPlayComReturnTitle* GfPlayComReturnTitle::create
GfPlayComQuestOrderUI::~GfPlayComQuestOrderUI() {
    if (m_context != nullptr) {
        m_context->release();
        m_context = nullptr;
    }
}

void GfPlayComQuestOrderUI::start() {
    if (GfQuestInfo::isDispUI(m_id)) {
        m_context = GfMenuCallContext::create();
        GfMenuObjQuestLog::order(m_context, m_id);
    }
}

void GfPlayComQuestOrderUI::end() {
    if (GfGameScene* scene = mm::mtl::PtrSingleton<GfGameScene>::sys()) {
        scene->setPlayerTalkForce(false);
    }
}

bool GfPlayComQuestOrderUI::update(const fw::UpdateInfo& info, bool flag) {
    if (m_context != nullptr) {
        if (!m_context->isTerm()) {
            return false;
        }
        GfQuestEvent::clearDispUI();
    }
    return true;
}

GfPlayComQuestOrderUI* GfPlayComQuestOrderUI::create(QuestID id, bool flag) {
#line 2905
    GfPlayComQuestOrderUI* com = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) GfPlayComQuestOrderUI(id, flag);
    if (GfGameScene* scene = mm::mtl::PtrSingleton<GfGameScene>::sys()) {
        scene->setPlayerTalkForce(true);
    }
    return com;
}

GfPlayComQuestCompleteUI::~GfPlayComQuestCompleteUI() {
    if (m_context != nullptr) {
        m_context->release();
        m_context = nullptr;
    }
    s_active--;
}

void GfPlayComQuestCompleteUI::start() {
    m_context = GfMenuCallContext::create();
    GfMenuObjQuestLog::complete(m_context, m_id);
    s_start++;
}

void GfPlayComQuestCompleteUI::end() {
    s_start--;
    GfQuestManager::requestRefreshQuestTaskState();
}

bool GfPlayComQuestCompleteUI::update(const fw::UpdateInfo& info, bool flag) {
    if (!m_context->isTerm()) {
        return false;
    }
    GfQuestEvent::clearDispUI();
    return true;
}

GfPlayComQuestCompleteUI* GfPlayComQuestCompleteUI::create(QuestID id, QuestID next, QSTATE state) {
#line 2969
    GfPlayComQuestCompleteUI* com = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) GfPlayComQuestCompleteUI(id, next, state);
    GfQuestManager::setCompleteQuest(id, next, state);
    return com;
}

// hand4: end
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

GfPlayComScriptTutorialSeq::~GfPlayComScriptTutorialSeq() { s_activate--; }

void GfPlayComScriptTutorialSeq::end() {
    if (GfGameScene* scene = mm::mtl::PtrSingleton<GfGameScene>::sys()) {
        scene->setEventPlayerStop(false);
    }
}

bool GfPlayComScriptTutorialSeq::update(const fw::UpdateInfo& info, bool flag) {
    if (flag) {
        SCOM_SCRIPT::create(3, nullptr, false);
        return true;
    }
    return !mm::mtl::PtrSingleton<GfReqSmallCom>::sys()->isValid(m_script);
}

GfPlayComScriptTutorialSeq* GfPlayComScriptTutorialSeq::fn_710031E044(const char* name, int startId) {
#line 3922
    return new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) GfPlayComScriptTutorialSeq(name, startId);
}

// hand: end
mm::mtl::RTTI GfPlayCom::m_rtti("GfPlayCom", nullptr, nullptr);
mm::mtl::RTTI GfPlayComEventFade::m_rtti("GfPlayComEventFade", &GfPlayCom::m_rtti, nullptr);
mm::mtl::RTTI GfPlayComEventWeather::m_rtti("GfPlayComEventWeather", &GfPlayCom::m_rtti, nullptr);
mm::mtl::RTTI GfPlayComPause::m_rtti("GfPlayComPause", &GfPlayCom::m_rtti, nullptr);
mm::mtl::RTTI GfPlayComState::m_rtti("GfPlayComState", &GfPlayCom::m_rtti, nullptr);
mm::mtl::RTTI GfPlayComWait::m_rtti("GfPlayComWait", &GfPlayCom::m_rtti, nullptr);
// hand4: begin mm::mtl::RTTI GfPlayComWaitEvent::m_rtti
int GfPlayComEventFade::s_start;

// hand4: end
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
int GfPlayComIraCampSave::s_activate;
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
// hand4: begin mm::mtl::FixedQueue<unsigned int, 32> GfPlayComMenuCommon::s_list;
unsigned int GfPlayComMenuCommon::s_gblHandle;

// hand4: end
mm::mtl::FixedQueue<unsigned int, 32> GfPlayComMenuCommon::s_list;
mm::mtl::RTTI GfPlayComMenuCommonFromParam::m_rtti("GfPlayComMenuCommonFromParam", &GfPlayCom::m_rtti, nullptr);
// hand4: begin mm::mtl::FixedQueue<unsigned int, 32> GfPlayComMenuCommonFromParam::s_list;
unsigned int GfPlayComMenuCommonFromParam::s_gblHandle;

// hand4: end
mm::mtl::FixedQueue<unsigned int, 32> GfPlayComMenuCommonFromParam::s_list;
mm::mtl::RTTI GfPlayComSalvage::m_rtti("GfPlayComSalvage", &GfPlayCom::m_rtti, nullptr);
mm::mtl::RTTI GfPlayComCollect::m_rtti("GfPlayComCollect", &GfPlayCom::m_rtti, nullptr);
mm::mtl::RTTI GfPlayComFieldTbox::m_rtti("GfPlayComFieldTbox", &GfPlayCom::m_rtti, nullptr);
mm::mtl::RTTI GfPlayComFieldSeq::m_rtti("GfPlayComFieldSeq", &GfPlayCom::m_rtti, nullptr);
mm::mtl::RTTI GfPlayComWaitPlayerToStartGmkTuto::m_rtti("GfPlayComWaitPlayerToStartGmkTuto", &GfPlayCom::m_rtti, nullptr);
mm::mtl::RTTI GfPlayComGmkTutorialSeq::m_rtti("GfPlayComGmkTutorialSeq", &GfPlayCom::m_rtti, nullptr);
// hand5: begin mm::mtl::RTTI GfPlayComGmkCameraSeq::m_rtti
int GfPlayComGmkTutorialSeq::s_activate;

// hand5: end
mm::mtl::RTTI GfPlayComGmkCameraSeq::m_rtti("GfPlayComGmkCameraSeq", &GfPlayCom::m_rtti, nullptr);
// hand5: begin mm::mtl::RTTI GfPlayComPlayerDead::m_rtti
int GfPlayComGmkCameraSeq::s_activate;

// hand5: end
mm::mtl::RTTI GfPlayComPlayerDead::m_rtti("GfPlayComPlayerDead", &GfPlayCom::m_rtti, nullptr);
mm::mtl::RTTI GfPlayComTalk::m_rtti("GfPlayComTalk", &GfPlayCom::m_rtti, nullptr);
mm::mtl::RTTI GfPlayComQuestOrderUI::m_rtti("GfPlayComQuestOrderUI", &GfPlayCom::m_rtti, nullptr);
mm::mtl::RTTI GfPlayComQuestCompleteUI::m_rtti("GfPlayComQuestCompleteUI", &GfPlayCom::m_rtti, nullptr);
// hand4: begin mm::mtl::RTTI GfPlayComGimmickTaskComplete::m_rtti
int GfPlayComQuestCompleteUI::s_active;
int GfPlayComQuestCompleteUI::s_start;

// hand4: end
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
// hand5: begin mm::mtl::RTTI GfPlayComMapjumpForArena::m_rtti
int GfPlayComMenuObjCommonText::s_activate;

// hand5: end
mm::mtl::RTTI GfPlayComMapjumpForArena::m_rtti("GfPlayComMapjumpForArena", &GfPlayCom::m_rtti, nullptr);
mm::mtl::RTTI GfPlayComMapjumpForLeaveArena::m_rtti("GfPlayComMapjumpForLeaveArena", &GfPlayCom::m_rtti, nullptr);
mm::mtl::RTTI GfPlayComMapjumpForBattleMapFromArena::m_rtti("GfPlayComMapjumpForBattleMapFromArena", &GfPlayCom::m_rtti, nullptr);
mm::mtl::RTTI GfPlayComWaitArenaStateField::m_rtti("GfPlayComWaitArenaStateField", &GfPlayCom::m_rtti, nullptr);
mm::mtl::RTTI GfPlayComStartChallengeBattle::m_rtti("GfPlayComStartChallengeBattle", &GfPlayCom::m_rtti, nullptr);
mm::mtl::RTTI GfPlayComScriptTutorialSeq::m_rtti("GfPlayComScriptTutorialSeq", &GfPlayCom::m_rtti, nullptr);
int GfPlayComScriptTutorialSeq::s_activate;

}  // namespace gf

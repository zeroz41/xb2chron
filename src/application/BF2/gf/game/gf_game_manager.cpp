#include "classes/gf/GfGameManager.h"
#include "classes/gf/GfGameScene.h"
#include "gf/GfTargetProperty.h"
#include "classes/gf/GfGameScene.h"
#include "classes/gf/GfAchievManager.h"
#include "gf/GfGameUtilHana.h"
#include "classes/gf/GfGameManager.h"
#include "gf/SDataBlade.h"
#include "gf/GfTargetProperty.h"
#include "gf/GfGameUtilHana.h"
#include "classes/gf/GfObj.h"
#include "classes/gf/GfObjProperty.h"
#include "classes/gf/GfGameCamera.h"
#include "classes/gf/GfGameManager.h"
#include "classes/gf/GfGameScene.h"
#include "classes/tl/TitleMain.h"
#include "classes/gf/GfWeapon.h"
#include "gf/GfDataBlade.h"
#include "btl/challenge_battle_manager.h"
#include "classes/gf/GfGameEvent.h"
#include "classes/gf/IGfEvent.h"
#include "classes/gf/GfGameScene.h"
#include "classes/gf/GfFieldGimmick.h"
#include "gf/GfDataBlade.h"
#include "classes/gf/GfFieldGimmick.h"
#include "gf/SDataSaveIra.h"
#include "btl/Utility.h"
#include "classes/gf/GfGameEnv.h"
#include "classes/gf/GfGameManager.h"
#include "classes/gf/GfGameEnv.h"
#include "classes/gf/IGfEvent.h"
#include "classes/gf/GfGameManager.h"
#include "classes/gf/GfGameScene.h"
#include "classes/gf/GfGameParty.h"
#include "gf/GfGameUtil.h"
#include "gf/GfQuestTask.h"
#include "classes/gf/GfQuestManager.h"
#include "gf/GfObjAcc.h"
#include "classes/gf/DataParamAcc.h"
#include "classes/gf/GfGameParty.h"
#include "classes/gf/GfGameVoice.h"
#include "gf/GfGameUtil.h"
#include "classes/gf/GfGameObj.h"
#include "classes/gf/GfGameScene.h"
#include "classes/gf/GfGameManager.h"
#include "classes/gf/GfObjManager.h"
#include "classes/gf/GfGameMercenaries.h"
#include "classes/gf/GfGameEnv.h"
#include "classes/gf/GfGameVoice.h"
#include "classes/gf/GfQuestManager.h"
#include "classes/gf/GfAchievManager.h"
#include "classes/gf/GfGameSpeed.h"
#include "classes/gf/GfGameObj.h"
#include "classes/gf/GfReqSmallCom.h"
#include "classes/gf/GfMenuManager.h"
#include "gf/GfObjAcc.h"
#include "classes/fw/Framework.h"
#include "classes/gf/GfGameManager.h"
#include "classes/gf/GfGameScene.h"
#include "classes/gf/GfGameEvent.h"
#include "classes/gf/IQuestEvent.h"
#include "gf/QuestCompleteChildParam.h"
#include "classes/gf/GfGameManager.h"
#include "classes/gf/GfGameScene.h"
#include "classes/gf/GfGameObj.h"
#include "classes/gf/GfGameEnv.h"
#include "classes/gf/GfEvent.h"
#include "classes/gf/GfGameParty.h"
#include "classes/gf/GfGameVoice.h"
#include "classes/gf/GfGameMercenaries.h"
#include "classes/gf/SCOM_POPUP.h"
#include "classes/gf/GfMenuManager.h"
#include "classes/gf/GfPlayComPlayerDead.h"
#include "gf/GfGameUtil.h"
#include "classes/gf/GfBdatRsc.h"
#include "classes/gf/GfAssetManager.h"
#include "classes/gf/GfFieldTime.h"
#include "gf/GfObjUtil.h"
#include "gf/GfDataMap.h"
#include "classes/gf/GfQuestManager.h"
#include "classes/gf/GfAchievManager.h"
#include "classes/gf/GfLayerPause.h"
#include "classes/gf/GfGameEvent.h"
#include "classes/gf/GfGameSpeed.h"
#include "classes/gf/GfSequentialPlay.h"
#include "classes/gf/GfGameFlag.h"
#include "classes/gf/GfMountManager.h"
#include "classes/gf/GfGameCond.h"
#include "classes/gf/GfGamePlayerFormation.h"
#include "classes/gf/GfGameState.h"
#include "fw/UpdateInfo.h"
#include "classes/gf/GfManager.h"
#include "classes/gf/GfAllocator.h"
#include "gf/GfDataBlade.h"
#include "classes/gf/GfPlayComQuestCompleteUI.h"
#include "gf/GfItemUtil.h"
#include "classes/gf/GfMenuObjTutorial.h"
#include "classes/gf/GfPlayComStartTutorial.h"
#include "classes/gf/GfPlayComResetBlade.h"
#include "classes/btl/BattleManager.h"
#include "classes/gf/GfObjManager.h"
#include "mm/Col4.h"
#include "classes/gf/GfKizunaringManager.h"
#include "gf/GfObjAcc.h"
#include "classes/fw/Framework.h"
#include "classes/gf/GfReqSmallCom.h"
#include "mm/mtl/FixedArray.h"

#include "classes/tl/TitleMain.h"
#include "classes/gf/GfGameCamera.h"
#include "classes/gf/SCOM_TARGET_UI.h"
#include "classes/gf/SCOM_ACCESS_TARGET.h"
#include "classes/gf/GfPlayComHoodHomuraBattou.h"
#include "gf/GfDataEvent.h"
#include "btl/challenge_battle_manager.h"
#include "classes/gf/GfWeapon.h"
#include "classes/gf/GfGameArena.h"
#include "classes/gf/GfMenuObjNpcTelop.h"
#include "classes/gf/GfPlayComOpenNpcEntry.h"
#include "gf/GfDataDriver.h"
#include "gf/GfQuestTask.h"
#include "classes/gf/GfPause.h"
#include "gf/GfDataEnemy.h"
#include "classes/gf/DataParamAcc.h"
#include "classes/gf/GfObjSetup.h"
#include "gf/GfDataHitonowa.h"
#include "gf/GfDataUtil.h"
#include "gf/GfGameUtilDiff.h"
#include "classes/gf/GfSound.h"
#include "classes/gf/GfDataManager.h"
#include "classes/gf/GfBladeManager.h"
#include "gf/SDataGame.h"
#include "classes/gf/GfGameRide.h"
#include "classes/gf/GfGameMoverSwitcher.h"
#include "classes/gf/GfGameInsideBattleLock.h"
#include "classes/gf/GfGamePlayerCamera.h"
#include "classes/gf/GfSmnEnemyManager.h"
#include "classes/gf/GfGameDepopMeterManager.h"
#include "classes/gf/GfGamePlayerUniqueScheduler.h"
#include "classes/gf/GfGameVisible.h"
#include "classes/gf/GfGameSalvage.h"
#include "classes/gf/GfGameTalk.h"
#include "classes/gf/GfGamePad.h"
#include "classes/gf/GfAutoTalkManager.h"
#include "classes/gf/GfGameTarget.h"
#include "classes/gf/GfItemManager.h"

namespace gf {

namespace _gfgm {
// 2.0.0's symbols name it. While it is set, GfGameManager::isPlayerCameraPause answers false; clear() resets it and
// setDisablePlayerCameraPauseForTitle sets it (reached through the GOT, so not a file static)
bool s_bDisablePlayerCamPause;
}  // namespace _gfgm

GfGameManager::~GfGameManager() {
    ;
}

void GfGameManager::initialize(const GfSetupParam& param) {
    GfEvent::addEventCallback(this);
    GfGameAoc::build(param);
    GfGameState::build(param);
    GfLayerPause::build(param);
    GfGameSpeed::build(param);
    GfGameEnv::build(param);
    GfGamePad::build(param);
    GfGameCamera::build(param);
    GfGameCond::build(param);
    GfGameObj::build(param);
    GfMountManager::build(param);
    GfGameParty::build(param);
    GfItemManager::build(param);
    GfQuestManager::build(param);
    GfGameMercenaries::build(param);
    GfGameTalk::build(param);
    GfGameEvent::build(param);
    GfGameTarget::build(param);
    GfGameSalvage::build(param);
    GfGameArena::build(param);
    GfSequentialPlay::build(param);
    GfAutoTalkManager::build(param);
    GfGamePlayerFormation::build(param);
    GfBladeManager::build(param);
    GfAchievManager::build(param);
    GfKizunaringManager::build(param);
    GfGameVisible::build(param);
    GfGamePlayerUniqueScheduler::build(param);
    GfGameScene::build(param);
    GfGameDepopMeterManager::create(4);
    GfSmnEnemyManager::create();
    GfGamePlayerCamera::build(param);
    GfGameRide::build(param);
    GfGameMoverSwitcher::build(param);
    GfGameVoice::build(param);
    GfGameInsideBattleLock::build(param);
    GfQuestManager::addEvent(this);
    GfMenuManager::initOptionData(*GfDataManager::getDataOption());
    resetGameType(param.m_dlcCameraParam);
    m_initialized = true;
}

void GfGameManager::destroy() {
    GfGameManager* manager = get();
    manager->finalize();
    delete manager;
}

void GfGameManager::finalize() {
    GfLayerPause::destroyLayerPause();
    if (!GfGameObj::isEmpty()) {
        GfSleep(1);
    }
    if (GfGameState::getState() != static_cast<GF_STATE>(3)) {
        GfSleep(1);
    }
    GfGameState::setState(static_cast<GF_STATE>(2), false);
    GfQuestManager::removeEvent(this);
    GfGameInsideBattleLock::destroy();
    GfGameVoice::destroy();
    GfGameMoverSwitcher::destroy();
    GfGameRide::destroy();
    GfGamePlayerCamera::destroy();
    GfSmnEnemyManager::dispose();
    GfGameDepopMeterManager::dispose();
    GfGameScene::destroy();
    GfGamePlayerUniqueScheduler::destroy();
    GfGameVisible::destroy();
    GfKizunaringManager::destroy();
    GfAchievManager::destroy();
    GfBladeManager::destroy();
    GfGamePlayerFormation::destroy();
    GfAutoTalkManager::destroy();
    GfSequentialPlay::destroy();
    GfGameArena::destroy();
    GfGameSalvage::destroy();
    GfGameTarget::destroy();
    GfGameEvent::destroy();
    GfGameTalk::destroy();
    GfGameMercenaries::destroy();
    GfItemManager::destroy();
    GfQuestManager::destroy();
    GfGameParty::destroy();
    GfMountManager::destroy();
    GfGameObj::destroy();
    GfGameCond::destroy();
    GfGameCamera::destroy();
    GfGamePad::destroy();
    GfGameEnv::destroy();
    GfGameSpeed::destroy();
    GfLayerPause::destroy();
    GfGameState::destroy();
    GfGameAoc::destroy();
    GfEvent::removeEventCallback(this);
    m_initialized = false;
}

bool GfGameManager::isGameObjEmpty() {
    return GfGameObj::isEmpty();
}

void GfGameManager::clear() {
    GfGameManager* manager = GfGameManager::get();
    SCOM_ACCESS_TARGET::create(reinterpret_cast<GF_OBJ_HANDLE*>(-1));
    SCOM_TARGET_UI::create(reinterpret_cast<GF_OBJ_HANDLE*>(-1));
    manager->m_leaveGameForDebug = false;
    GfGameCamera::clear();
    GfGameState::clear();
    GfGameEnv::clear();
    GfGameEvent::clear();
    if (GfGameScene* scene = GfGameScene::get()) {
        scene->clear();
    }
    GfGameSpeed::clear();
    _gfgm::s_bDisablePlayerCamPause = false;
}

GF_STATE GfGameManager::getState() {
    return GfGameState::getState();
}

void GfGameManager::setState(GF_STATE state, bool flag) {
    GfGameState::setState(state, flag);
}

void GfGameManager::gevHanaCondenser(unsigned int value, bool flag, unsigned int slot) {
    if (GfGameScene* scene = GfGameScene::get()) {
        scene->gevHanaCondenser(value, flag, slot);
    }
}

void GfGameManager::gevOrbParam(unsigned int value, unsigned int value1) {
    if (GfGameScene* scene = GfGameScene::get()) {
        scene->gevOrbParam(value, value1);
    }
}

void GfGameManager::gevAcceParam(unsigned int value, unsigned int value1) {
    if (GfGameScene* scene = GfGameScene::get()) {
        scene->gevAcceParam(value, value1);
    }
}

void GfGameManager::gevChangeGameDifficult() {
    if (GfGameScene* scene = GfGameScene::get()) {
        scene->gevChangeGameDifficult();
    }
}

void GfGameManager::gevExecBuy(unsigned int id, unsigned int value, unsigned int shop) {
    if (GfGameScene* scene = GfGameScene::get()) {
        scene->gevExecBuy(id, value, shop);
    }
}

void GfGameManager::gevChangeParty() {
    if (GfGameScene* scene = GfGameScene::get()) {
        scene->gevChangeParty();
    }
}

void GfGameManager::gevGetArts(unsigned int blade, unsigned int arts, bool popup) {
    if (popup) {
        SCOM_POPUP::createArts(blade, arts);
    }
}

void GfGameManager::gevDriverLevel(unsigned int a0, unsigned int a1, unsigned int a2) {
    if (GfGameScene* scene = GfGameScene::get()) {
        scene->gevDriverLevel(a0, a1, a2);
    }
}

void GfGameManager::gevSelectHikari(bool hikari) {
    if (GfGameScene* scene = GfGameScene::get()) {
        scene->gevSelectHikari(hikari);
    }
}

void GfGameManager::gevBattleStart() {
    if (GfGameScene* scene = GfGameScene::get()) {
        scene->gevBattleStart();
    }
    if (GfGameParty* party = GfGameParty::get()) {
        party->gevBattleStart();
    }
}

void GfGameManager::gevBattleEnd() {
    if (GfGameParty* party = GfGameParty::get()) {
        party->gevBattleEnd();
    }
    if (GfGameScene* scene = GfGameScene::get()) {
        scene->gevBattleEnd();
    }
    GfQuestManager::gevBattleEnd();
}

void GfGameManager::gevPause(unsigned int flags0, unsigned int flags1) {
    GfLayerPause::gevPause(flags0, flags1);
    GfGameEvent::gevPause(flags0, flags1);
    if (flags1 & 2) {
        GfGameSpeed::setGlobalSpeed(0.0f);
    }
    if (flags0 & 2) {
        GfGameSpeed::setGlobalSpeed(1.0f);
    }
}

void GfGameManager::gevChangeBlade(GF_OBJ_HANDLE* handle, int from, int to) {
    GfGameParty::gevChangeBlade(handle, from, to);
}

void GfGameManager::gevGameObjEnter(GF_OBJ_HANDLE* handle) {
    GfMountManager::gevGameObjEnter(handle);
    GfGameParty::gevGameObjEnter(handle);
    if (GfGameScene* scene = GfGameScene::get()) {
        scene->gevGameObjEnter(handle);
    }
}

void GfGameManager::gevGameObjLeave(GF_OBJ_HANDLE* handle) {
    if (GfGameScene* scene = GfGameScene::get()) {
        scene->gevGameObjLeave(handle);
    }
    GfGameParty::gevGameObjLeave(handle);
    GfMountManager::gevGameObjLeave(handle);
}

void GfGameManager::gevDriverActivate(unsigned int id, ActivateType from, ActivateType to) {
    if (GfGameScene* scene = GfGameScene::get()) {
        scene->gevDriverActivate(id, from, to);
    }
}

void GfGameManager::gevBladeActivate(unsigned int id, ActivateType from, ActivateType to) {
    if (from == 0 && to != 0) {
        GfKizunaringManager::orderAchievement(id);
    }
    if (GfAchievManager* achiev = GfAchievManager::get()) {
        achiev->gevBladeActivate(id, from, to);
    }
    if (GfGameScene* scene = GfGameScene::get()) {
        scene->gevBladeActivate(id, from, to);
    }
}

void GfGameManager::gevBladeUnselect(unsigned int id, bool flag) {
    if (GfGameScene* scene = GfGameScene::get()) {
        scene->gevBladeUnselect(id, flag);
    }
}

void GfGameManager::gevBladeEnable(unsigned int blade) {
    GfGameUtilHana::setupDefaultParts(blade);
    if (blade == 1050 && GfDataBlade::getCreator(1050) == 0) {
        GfDataBlade::setCreator(1050, GfDataBlade::getCreator(1022));
    }
    if (GfFieldTime* time = GfFieldTime::get()) {
        SDataBlade* data = GfDataBlade::getSDataBlade(blade);
        if (data->m_bornTime == 0) {
            data->m_bornTime = reinterpret_cast<const unsigned int&>(time->getElapseTime());
        }
    }
}

void GfGameManager::gevItemAdd(unsigned int item, int count) {
    if (GfAchievManager* achiev = GfAchievManager::get()) {
        achiev->gevItemAdd(item, count);
    }
    GfQuestManager::gevItemAdd(item, count);
    if (GfGameScene* scene = GfGameScene::get()) {
        scene->gevItemAdd(item, count);
    }
}

void GfGameManager::gevPlayEvent(GEV gev, unsigned int id) {
    GfQuestManager::gevPlayEvent(gev, id);
    if (GfGameEvent* event = GfGameEvent::get()) {
        event->gevPlayEvent(gev, id);
    }
    GfGameEnv::gevPlayEvent(gev, id);
    if (GfGameScene* scene = GfGameScene::get()) {
        scene->gevPlayEvent(gev, id);
    }
    if (GfGameParty* party = GfGameParty::get()) {
        party->gevPlayEvent(gev, id);
    }
}

void GfGameManager::gevPartyMemberOK(bool) {}

void GfGameManager::gevLayerPause(unsigned int layer, bool pause) {
    GfGameVoice::gevLayerPause(layer, pause);
}

void GfGameManager::gevPartyIDMemberOK(bool ok, unsigned int id) {
    GfGameParty::gevPartyIDMemberOK(ok, id);
}

void GfGameManager::gevReloadBdat(RELOAD_BDAT type, unsigned int id) {
    GfQuestManager::gevReloadBdat(type, id);
    if (type == 1) {
        GfGameObj::bdatReload();
    }
}

void GfGameManager::gevSalvageStateChange(unsigned int state) {
    if (state == 20) {
        unsigned short count = GfGameFlag::getLocal(16, 1547);
        if (count != 0xFFFF) {
            count++;
        }
        GfGameFlag::setLocal(16, 1547, count);
    }
}

void GfGameManager::gevChangeScenarioFlag(unsigned int flag, unsigned int value) {
    if (GfGameScene* scene = GfGameScene::get()) {
        scene->gevChangeScenarioFlag(flag, value);
    }
}

void GfGameManager::gevChangeAocFlag(unsigned int id) {
    if (GfGameAoc* aoc = GfGameAoc::get()) {
        aoc->gevChangeAocFlag(id);
    }
}

void GfGameManager::gevChangeWeather(unsigned int a0, unsigned int a1) {
    if (GfGameScene* scene = GfGameScene::get()) {
        scene->gevChangeWeather(a0, a1);
    }
    GfQuestManager::gevChangeWeather(a0, a1);
}

void GfGameManager::gevChangeTimeRange(unsigned int range) {
    if (GfGameScene* scene = GfGameScene::get()) {
        scene->gevChangeTimeRange(range);
    }
    GfQuestManager::gevChangeTimeRange(range);
}

void GfGameManager::gevGameState(GF_STATE prev, GF_STATE next) {
    GfGameEnv::gevGameState(prev, next);
}

void GfGameManager::gevControllFree(bool flag) {
    if (GfGameScene* scene = GfGameScene::get()) {
        scene->gevControllFree(flag);
    }
}

void GfGameManager::qevOrderQuest(const QuestOrderParam& param) {
    GfGameMercenaries::qevOrderQuest(param);
}

bool GfGameManager::isInnerState(GF_STATE state) {
    return GfSequentialPlay::isInnerState(state);
}

GF_OBJ_HANDLE* GfGameManager::getControlMover() {
    if (GfGamePlayerFormation* formation = GfGamePlayerFormation::get()) {
        GF_OBJ_HANDLE* handle = formation->m_players[0].m_handle;
        if (handle != reinterpret_cast<GF_OBJ_HANDLE*>(-1)) {
            return handle;
        }
    }
    return getPartyLeader();
}

GF_OBJ_HANDLE* GfGameManager::getControlMoverForGimmick() {
    GfGamePlayerFormation* formation = GfGamePlayerFormation::get();
    if (formation) {
        GF_OBJ_HANDLE* handle = formation->m_players[0].m_handle;
        if (handle != reinterpret_cast<GF_OBJ_HANDLE*>(-1)) {
            return handle;
        }
    }
    GF_OBJ_HANDLE* leader = getPartyLeader();
    if (leader != reinterpret_cast<GF_OBJ_HANDLE*>(-1)) {
        return leader;
    }
    return GfGameParty::getDummpMover();
}

bool GfGameManager::isPlayerPause() {
    if (GfGameScene* scene = GfGameScene::get()) {
        return scene->isPlayerPause();
    }
    return false;
}

void GfGameManager::enterBattle(bool flag) {
    if (GfGameScene* scene = GfGameScene::get()) {
        scene->enterBattle(flag);
    }
}

bool GfGameManager::isBattle() {
    if (GfGameScene* scene = GfGameScene::get()) {
        return scene->isBattle();
    }
    return false;
}

bool GfGameManager::isEventWait() {
    return GfGameState::getState() == static_cast<GF_STATE>(7);
}

bool GfGameManager::isPlaySequenceClear() {
    return !GfSequentialPlay::isPlay();
}

bool GfGameManager::isControlFree() {
    if (GfGameScene* scene = GfGameScene::get()) {
        return scene->isControlFree();
    }
    return false;
}

bool GfGameManager::isBladeChange() {
    return GfSequentialPlay::isInnerState(static_cast<GF_STATE>(24));
}

bool GfGameManager::isTalkOK() {
    if (GfGameScene* scene = GfGameScene::get()) {
        return scene->isControlFree();
    }
    return false;
}

bool GfGameManager::isTalking() {
    if (GfGameScene* scene = GfGameScene::get()) {
        if (scene->isPlayerTalkForce()) {
            return true;
        }
    }
    return GfGameState::test(0x20);
}

bool GfGameManager::isFullScreenMenu() {
    return GfMenuManager::isOpenFullScreen();
}

bool GfGameManager::isGmkTutorialMoverOK() {
    if (GfGameScene* scene = GfGameScene::get()) {
        return scene->isPlayerStopFlag(static_cast<PLSTOP>(2));
    }
    return false;
}

void GfGameManager::setGmkTutorialMoverOK(bool ok) {
    if (GfGameScene* scene = GfGameScene::get()) {
        scene->setPlayerStopFlag(static_cast<PLSTOP>(2), ok);
    }
}

void GfGameManager::setGmkTutorialSequenceOK(bool ok) {
    if (GfGameScene* scene = GfGameScene::get()) {
        scene->setPlayerStopFlag(static_cast<PLSTOP>(1), ok);
    }
}

bool GfGameManager::isGameOver() {
    if (isGameTypeIra()) {
        if (GfDataUtil::getScenarioFlag() >= 11115 && GfDataUtil::getScenarioFlag() < 11130) {
            return true;
        }
        return false;
    }
    if (GfDataUtil::getScenarioFlag() >= 10034 && GfDataUtil::getScenarioFlag() / 64 < 157) {
        return true;
    }
    return false;
}

bool GfGameManager::isEnemyChangeBattleOK() {
    if (GfGameScene* scene = GfGameScene::get()) {
        if (scene->isPlayerPauseForBattle()) {
            return false;
        }
    }
    bool ok = false;
    if (GfObj* obj = GfObjUtil::getObj(getControlMover())) {
        if (GfObjProperty* property = GfObjUtil::getProperty(obj->m_handle)) {
            if (GfObjProperty::TargetInfo* target = property->m_target) {
                ok = target->m_state != 3;
            }
        }
    }
    return ok;
}

bool GfGameManager::isFieldLockMsgOK() {
    if (isEnableFieldAccess()) {
        if (GfGameScene* scene = GfGameScene::get()) {
            return scene->isControlFree();
        }
    }
    return false;
}

bool GfGameManager::isEnableFieldAccess() {
    if (GfSequentialPlay::isInnerState(static_cast<GF_STATE>(24))) {
        return false;
    }
    if (GfSequentialPlay::isInnerState(static_cast<GF_STATE>(10))) {
        return false;
    }
    if (!isEnableOpenMainMenuSequence()) {
        return false;
    }
    if (GfGameScene* scene = GfGameScene::get()) {
        DataParamAcc acc(GfGameParty::getHandleDriver(0, static_cast<PTPOS>(0)));
        if (acc.isValid() && (acc.isValid() && acc.getObjType() == 3 ? acc.getBdatId() : 0) == 2) {
            bool needChange = scene->isNeedFieldBladeChange(0);
            if (needChange) {
                return false;
            }
            unsigned int id = acc.isValid() && acc.getObjType() == 3 ? acc.getBdatId() : 0;
            if (GfDataDriver::getBlade(id, -1) == 1004 &&
                GfObjUtil::getParentHandle(acc.m_handle) != GfGameParty::getHandleBlade(0, -1)) {
                return false;
            }
        }
    }
    return true;
}

bool GfGameManager::isEnableFieldBattleTarget() {
    GfObjAcc acc(getPartyLeaderDriver());
    bool battle = acc.isBattle();
    if (!battle && GfPlayComOpenNpcEntry::get() == nullptr) {
        if (isInnerState(static_cast<GF_STATE>(6)) ||
            isInnerState(static_cast<GF_STATE>(11)) ||
            isInnerState(static_cast<GF_STATE>(21)) ||
            isInnerState(static_cast<GF_STATE>(14)) ||
            isInnerState(static_cast<GF_STATE>(12)) ||
            isInnerState(static_cast<GF_STATE>(13)) ||
            isInnerState(static_cast<GF_STATE>(4)) ||
            isInnerState(static_cast<GF_STATE>(19)) ||
            isInnerState(static_cast<GF_STATE>(16)) ||
            isInnerState(static_cast<GF_STATE>(17)) ||
            isInnerState(static_cast<GF_STATE>(18))) {
            return false;
        }
        return !isInnerState(static_cast<GF_STATE>(20));
    }
    return true;
}

bool GfGameManager::isRoom() {
    return GfGameEnv::isRoom();
}

unsigned int GfGameManager::getMapJumpID() {
    return GfGameEnv::getMapJumpID();
}

int GfGameManager::getMapID() {
    return GfGameEnv::getMapID();
}

void GfGameManager::setMapID(unsigned int map, unsigned int jump) {
    GfGameEnv::setMapID(map, jump);
}

unsigned int GfGameManager::getMapZoneID() {
    return GfDataMap::getZoneIdForGameMap(GfGameEnv::getMapID());
}

void GfGameManager::setAccessTarget(GF_OBJ_HANDLE* handle) {
    GfEvent::callTargetAccess(handle);
}

void GfGameManager::setTargetUI(GF_OBJ_HANDLE* handle) {
    GfEvent::callTargetChange(handle);
}

bool GfGameManager::isMapjump() {
    return GfGameEnv::isMapjump();
}

bool GfGameManager::isMapjumpWithSaveData() {
    return GfGameEnv::isMapjumpWithSaveData();
}

GfPlayerDead GfGameManager::getDeadType() {
    if (GfGameScene* scene = GfGameScene::get()) {
        return scene->getDeadType();
    }
    return static_cast<GfPlayerDead>(0);
}

bool GfGameManager::isScenarioGame() {
    return GfManager::isExecModeScenarioGame();
}

bool GfGameManager::isAdvertize() {
    return GfManager::isExecModeAdvertize();
}

bool GfGameManager::isPartyCreateForMapjump() {
    return !GfManager::isExecKillPartyCreate();
}

bool GfGameManager::isInMetJIJI() {
    return GfGameCond::isGameCond(GfBdatRsc::get()->getDriverParamExtMountCond(1));
}

namespace _gfgm {

// Inferred helper (its name is not the original's): getControlMoverPosition and setControlMoverPositionForNoPlayer share one guarded
// static Vec3, so it lives in a function both inline.
static mm::Vec3& getMoverPosition() {
    // Proposed name, not the original's: the symbols leave it unnamed (lbl_7100D6CBF0, guard lbl_7100D6CC00)
    static mm::Vec3 s_pos = mm::Vec3::zero;
    return s_pos;
}

}  // namespace _gfgm

const mm::Vec3& GfGameManager::getControlMoverPosition() {
    GfObjAcc acc(getControlMover());
    if (acc.isValidTransform()) {
        return acc.getWorldTransform().position;
    }
    return _gfgm::getMoverPosition();
}

mm::Vec3 GfGameManager::getControlMoverRotation() {
    GfObjAcc acc(getControlMover());
    if (!acc.isValidTransform()) {
        return mm::Vec3::zero;
    }
    const mm::Quat& q = acc.getWorldTransform().rotation;
    float x2 = q.x + q.x;
    float y2 = q.y + q.y;
    float z2 = q.z + q.z;
    float xx = q.x * x2;
    float xy = q.x * y2;
    float xz = q.x * z2;
    float yy = q.y * y2;
    float yz = q.y * z2;
    float zz = q.z * z2;
    float wx = q.w * x2;
    float wy = q.w * y2;
    float wz = q.w * z2;
    float m00 = 1.0f - (yy + zz);
    float m01 = xy + wz;
    float m02 = xz - wy;
    float m11 = 1.0f - (xx + zz);
    float m20 = xz + wy;
    float m21 = yz - wx;
    float m22 = 1.0f - (xx + yy);
    mm::Vec3 r;
    r.x = mm::asin(-m21);
    if (r.x < 1.57079637f) {
        if (r.x > -1.57079637f) {
            r.z = ::atan2f(m01, m11);
            r.y = ::atan2f(m20, m22);
        } else {
            r.z = -::atan2f(m02, m00);
            r.y = 0.0f;
        }
    } else {
        r.z = ::atan2f(m02, m00);
        r.y = 0.0f;
    }
    return r;
}

float GfGameManager::getFieldSpeed(const fw::UpdateInfo& info) {
    float speed = GfGameSpeed::getLayerSpeed(0);
    float pause = GfLayerPause::isLayerPause(0) ? 0.0f : 1.0f;
    return info.m_speed * (speed * pause);
}

bool GfGameManager::isEnableOpenMainMenuSequence() {
    if (isStartGame()) {
        return false;
    }
    if (isMapjump()) {
        return false;
    }
    if (isLeaveGameForDebug()) {
        return false;
    }
    if (GfSequentialPlay::isInnerPause(0x40)) {
        return false;
    }
    if (GfMenuObjNpcTelop::isOpen()) {
        return false;
    }
    if (isBattle()) {
        return false;
    }
    {
        GfObjAcc acc(getControlMover());
        if (acc.isBattle()) {
            return false;
        }
    }
    {
        DataParamAcc param(getPartyLeaderDriver());
        if (param.isValid() && param.getHp() == 0) {
            return false;
        }
    }
    if (isInnerState(static_cast<GF_STATE>(11))) {
        return false;
    }
    if (GfGameScene* scene = GfGameScene::get()) {
        if (scene->isNeedResetBladeForBattleEndForMenuOpen()) {
            return false;
        }
    }
    return true;
}

bool GfGameManager::isEnableOpenMainMenu() {
    if (isGameTypeIra() && GfDataUtil::getScenarioFlag() == 11002) {
        return false;
    }
    if (!isEnableOpenMainMenuSequence()) {
        return false;
    }
    if (GfFieldGimmick* gimmick = GfFieldGimmick::get()) {
        if (!gimmick->m_enableOpenMainMenu) {
            return false;
        }
    }
    if (GfGameScene* scene = GfGameScene::get()) {
        if (scene->m_stopMainMenuOpenForGimmick) {
            return false;
        }
    }
    if (GfSequentialPlay::isInnerState(static_cast<GF_STATE>(24))) {
        return false;
    }
    if (btl::BattleManager::isInitialized() && !btl::Utility::IsEnableEventStart()) {
        return false;
    }
    GfGameScene* scene = GfGameScene::get();
    if (scene == nullptr) {
        return false;
    }
    if (scene->isFullScreenMenuAfter() || scene->isMaskMainMenu()) {
        return false;
    }
    int state = scene->m_partyStates[0].m_state;
    bool open = (state == 0 || state == 1) && !scene->isMoverGetFieldDamage();
    if (!open) {
        return false;
    }
    if (GfGameCond::isGameCond(2592)) {
        if (!isClearGame() || GfDataUtil::getScenarioFlag() != 1031) {
            return false;
        }
    }
    return !scene->m_partyStates[0].m_targetValueSet;
}

bool GfGameManager::isClearGame() {
    if (GfManager::isExecModeAdvertize() || GfManager::isExecModeThater()) {
        tl::TitleMain* title = tl::TitleMain::get();
        if (title != nullptr && title->m_saveBuffer != nullptr &&
            GfDataUtil::isClearGame(title->getSaveBuffer()->m_game)) {
            return true;
        }
    }
    return GfDataUtil::isClearGame();
}

bool GfGameManager::isEnableHoodHomuraScenes() {
    return !GfSequentialPlay::isInnerState(static_cast<GF_STATE>(24)) && !GfSequentialPlay::isInnerState(static_cast<GF_STATE>(10));
}

bool GfGameManager::isEnableGimmickPhantomDamage() {
    return !GfSequentialPlay::isInnerPause(89);
}

bool GfGameManager::isEnableGetFieldPrecious() {
    return isEnableOpenMainMenuSequence() && isEnableOpenMainMenu();
}

bool GfGameManager::isEnableCreateBattleLock() {
    return !GfSequentialPlay::isInnerPause(89);
}

bool GfGameManager::isPartyMover(GF_OBJ_HANDLE* handle) {
    unsigned int id = GfObjUtil::getPartyID(handle);
    if (id == static_cast<unsigned int>(-1)) {
        return false;
    }
    return GfGameParty::getHandleMover(id) == handle;
}

bool GfGameManager::isPlayerDeadSequence() {
    return GfPlayComPlayerDead::isDead();
}

bool GfGameManager::isForceBossBattleBgm() {
    if (GfGameScene* scene = GfGameScene::get()) {
        return scene->isForceBossBattleBgm();
    }
    return false;
}

bool GfGameManager::isForceEventBgm() {
    if (GfGameScene* scene = GfGameScene::get()) {
        return scene->isForceEventBgm();
    }
    return false;
}

bool GfGameManager::isNight() {
    if (GfFieldTime* time = GfFieldTime::get()) {
        return time->getTimeRangeDN() == 7;
    }
    return false;
}

bool GfGameManager::isRexAwakening() {
    return GfGameUtil::isCondDriverModel(1);
}

void GfGameManager::setHomuriWeaponExtraMesh(bool flag, float time) {
    if (GfGameScene* scene = GfGameScene::get()) {
        scene->setHomuriWeaponExtraMesh(flag, time);
    }
}

bool GfGameManager::isDispPreciousMenu() {
    return GfPlayComQuestCompleteUI::s_disp > 0;
}

bool GfGameManager::isDispQuestCompleteMenu() {
    return GfPlayComQuestCompleteUI::s_disp > 0;
}

bool GfGameManager::isInvalidBattleStop() {
    if (GfPlayComQuestCompleteUI::s_active > 0 || GfPlayComOpenNpcEntry::get()) {
        return true;
    }
    if (GfGameScene* scene = GfGameScene::get()) {
        return scene->isOpenPreciousMenu();
    }
    return false;
}

bool GfGameManager::isStopEnemyAttack() {
    if (GfGameScene* scene = GfGameScene::get()) {
        return scene->m_value630 > 0;
    }
    return false;
}

bool GfGameManager::isPartyMemberPlayVoice() {
    if (GfGameVoice* voice = GfGameVoice::get()) {
        for (unsigned int i = 0; i < 3; i++) {
            if (voice->isPlayVoice(GfGameParty::getHandleDriver(i, static_cast<PTPOS>(0)))) {
                return true;
            }
            if (voice->isPlayVoice(GfGameParty::getHandleBlade(i, -1))) {
                return true;
            }
        }
    }
    return false;
}

bool GfGameManager::isPlayEnemyVoice() {
    if (GfGameVoice* voice = GfGameVoice::get()) {
        return voice->isPlayEnemyVoice();
    }
    return false;
}

bool GfGameManager::isDisableJumpForRide() {
    if (GfGameScene* scene = GfGameScene::get()) {
        return scene->isDisableJumpForRide();
    }
    return false;
}

bool GfGameManager::isDisableAutoRun() {
    return GfMenuManager::isEnableQuestOpen();
}

bool GfGameManager::isChangeNormalHomuraForce(unsigned int blade) {
    if (blade == 1001) {
        if (GfPlayComHoodHomuraBattou::get()) {
            return true;
        }
        if (GfGameArena* arena = GfGameArena::get()) {
            if (arena->isBattleNow()) {
                return true;
            }
        }
    }
    return false;
}

bool GfGameManager::isAssetNumberInvalid() {
    return GfAssetManager::getUsedAssetPackInfo() > 511;
}

void GfGameManager::resetGameType(bool flag) {
    if (GfGameAoc* aoc = GfGameAoc::get()) {
        aoc->setupGame(GAME_TYPE(flag));
    }
}

void GfGameManager::setupGame(GAME_TYPE type) {
    if (GfGameAoc* aoc = GfGameAoc::get()) {
        aoc->setupGame(type);
        GfGameFlag::setLocal(1, 0xD788, 1);
        GfGameFlag::setLocal(1, 0xD789, 1);
    }
    GfBladeManager::setupGame();
    GfItemUtil::setupItemDataFollow();
    GfGameUtil::setupGameDataFollow();
    GfDataEnemy::initializeEnemySuppress();
    if (!GfManager::isContinueGame()) {
        GfManager::isNewGame();
    }
    GfQuestManager::setupGame();
    GfKizunaringManager::setupGame();
    GfMenuManager::setupGame();
    if (GfGameScene* scene = GfGameScene::get()) {
        scene->setupGame();
    }
    if (GfSound* sound = GfSound::get()) {
        sound->setupGame();
    }
    if (GfGameArena* arena = GfGameArena::get()) {
        arena->setupGame();
    }
    if (GfGameParty* party = GfGameParty::get()) {
        party->setupGame();
    }
    GfGameFlag::setLocal(1, 0xD861, GfDataManager::getDataGame()->m_gameClearCount != 0);
}

void GfGameManager::getBtlDifParam(unsigned int value) {
    GfGameUtilDiff::getBtlDifParam(value);
}

unsigned int GfGameManager::getBtlDifficult() {
    return GfGameUtilDiff::getBtlDifficult();
}

bool GfGameManager::isBattleArenaActive() {
    if (GfGameArena* arena = GfGameArena::get()) {
        return arena->isActiveArena();
    }
    return false;
}

bool GfGameManager::isInstalledBattleArenaContents() {
    if (GfGameAoc* aoc = GfGameAoc::get()) {
        return aoc->isExistGameAoc(GAMEAOC(0x30101));
    }
    return false;
}

unsigned int GfGameManager::getBattleArenaEtherCube() {
    if (GfGameArena* arena = GfGameArena::get()) {
        return arena->m_record.m_value2C;
    }
    return 0;
}

ArenaMenuInfo* GfGameManager::getBattleArenaMenuInfo() {
    return &GfGameArena::get()->m_record;
}

unsigned int GfGameManager::getBattleArenaScore() {
    if (GfGameArena* arena = GfGameArena::get()) {
        return arena->m_record.m_value28;
    }
    return 0;
}

bool GfGameManager::getBattleArenaMenuInfo(ArenaMenuInfo& info, unsigned int id, GFDIFF diff) {
    if (GfGameArena* arena = GfGameArena::get()) {
        arena->getMenuInfo(info, id, diff);
        return true;
    }
    return false;
}

bool GfGameManager::isEnableNamedRecord() {
    return GfDataUtil::isVersion150();
}

bool GfGameManager::isEnableInGameSF() {
    return GfItemUtil::getItemBoxCount(25472) != 0;
}

bool GfGameManager::isEnableInGameElma() {
    return GfItemUtil::getItemBoxCount(25541) != 0;
}

void GfGameManager::reqestEventAutoSave() {
    if (GfGameUtilDiff::isEnableAutoSave()) {
        if (GfGameScene* scene = GfGameScene::get()) {
            scene->m_iraCampSave = true;
        }
    }
}

bool GfGameManager::isVibrationDisable() {
    if (GfGameScene* scene = GfGameScene::get()) {
        return scene->isPlayEvent();
    }
    return false;
}

void GfGameManager::reqestCraftPopupForIra() {
    if (GfGameScene* scene = GfGameScene::get()) {
        scene->m_flag8C0 = true;
    }
}

bool GfGameManager::isDisableUnieqIdle() {
    int type = GfDataEvent::getEventType(GfGameEvent::getPlayEventId());
    if (type != 0 && type != 1) {
        return true;
    }
    if (!isFadeClear()) {
        return true;
    }
    if (GfGameScene* scene = GfGameScene::get()) {
        return scene->isBattle();
    }
    return false;
}

bool GfGameManager::isSepiaFilter() {
    if (GfGameScene* scene = GfGameScene::get()) {
        return scene->isSepiaFilter();
    }
    return false;
}

bool GfGameManager::fn_71002AC77C(unsigned int party) {
    GfGameAoc* aoc = GfGameAoc::get();
    if (aoc && aoc->m_mode == 1) {
        GfObjAcc driver0(GfGameParty::getHandleDriver(party, static_cast<PTPOS>(0)));
        GfObjAcc driver1(GfGameParty::getHandleDriver(party, static_cast<PTPOS>(1)));
        GfObjAcc driver2(GfGameParty::getHandleDriver(party, static_cast<PTPOS>(2)));
        return driver0.isBattle() || driver1.isBattle() || driver2.isBattle();
    }
    GfObjAcc driver(GfGameParty::getHandleDriver(party, static_cast<PTPOS>(0)));
    GfObjAcc blade(GfGameParty::getHandleBlade(party, -1));
    if (!driver.m_obj) {
        return false;
    }
    GfObj* bladeObj = blade.m_obj;
    bool battle = driver.isBattle();
    if (bladeObj) {
        return battle || blade.isBattle();
    }
    return battle;
}


bool GfGameManager::isEnableSpecialBgm() {
    GfGameAoc* aoc = GfGameAoc::get();
    if (aoc && aoc->m_mode != 1 && aoc->isExistGameAoc(GAMEAOC(0x30101))) {
        return GfGameUtilDiff::isEnableSpecialBgm();
    }
    return false;
}

unsigned int GfGameManager::getHitonowaLevel() {
    return GfDataHitonowa::getFlag4Level();
}

bool GfGameManager::isCompleteBothGame() {
    if (tl::TitleMain* title = tl::TitleMain::get()) {
        return title->m_flag21B;
    }
    return false;
}

bool GfGameManager::isDisableFieldDamage() {
    if (GfGameArena* arena = GfGameArena::get()) {
        if (arena->isBattleNow()) {
            if (btl::ChallengeBattleManager* challenge = btl::ChallengeBattleManager::get()) {
                if (challenge->IsResult()) {
                    return true;
                }
                if (challenge->IsWaveFinished() && btl::Utility::AI_GetEnemyNum() == 0) {
                    return true;
                }
            }
        }
    }
    return false;
}

bool GfGameManager::isEnableAutoBattle() {
    return GfGameUtilDiff::isEnableAutoBattle();
}

bool GfGameManager::isEnableAutoButtonChallenge() {
    return GfGameUtilDiff::isEnableAutoButtonChallenge();
}

bool GfGameManager::isEnableEnemyAgg() {
    return GfGameUtilDiff::isEnableEnemyAgg();
}

void GfGameManager::update(const fw::UpdateInfo& info) {
    GfGameState::update(info);
    GfGameSpeed::update(info);
    GfGamePad::update(info);
    GfGameEnv::update(info);
    if (GfAchievManager* achiev = GfAchievManager::get()) {
        achiev->update(info);
    }
    GfGameObj::update(info);
    if (GfGameParty* party = GfGameParty::get()) {
        party->update(info);
    }
    GfQuestManager::update(info);
    GfGameMercenaries::update(info);
    if (!GfPause::isPause(1)) {
        if (GfGameScene* scene = GfGameScene::get()) {
            scene->update(info);
        }
    }
    GfGameTalk::update(info);
    GfGameEvent::update(info);
    if (GfGameTarget::get() != nullptr) {
        GfGameTarget::update(info);
    }
    if (!GfPause::isPause(1)) {
        GfGameSalvage::update(info);
        if (GfGameArena* arena = GfGameArena::get()) {
            arena->update(info);
        }
        GfAutoTalkManager::update(info);
        if (GfGamePlayerFormation::get() != nullptr) {
            GfGamePlayerFormation::update(info);
        }
        if (!isEvent(false)) {
            GfGameVisible::update(info);
        }
        GfGamePlayerUniqueScheduler::update(info);
        GfGameInsideBattleLock::update(info);
    }
    GfGameDepopMeterManager::update(info.m_deltaTime);
    GfSmnEnemyManager::update(info.m_deltaTime);
    GfGameVoice::update(info);
}

void GfGameManager::updateParam(const fw::UpdateInfo& info) {
    if (GfGameScene* scene = GfGameScene::get()) {
        scene->updateParam(info);
    }
}

void GfGameManager::updateAfterLayer(const fw::UpdateInfo& info) {
    if (GfGameScene* scene = GfGameScene::get()) {
        scene->updateAfterLayer(info);
    }
}

void GfGameManager::postUpdate(const fw::UpdateInfo& info) {
    GfSequentialPlay::postUpdate(info);
    GfGameObj::postUpdate(info);
    if (GfGameScene* scene = GfGameScene::get()) {
        scene->postUpdate(info);
    }
    GfGameEvent::postUpdate(info);
}


void GfGameManager::build(const GfSetupParam& param) {
#line 138
    GfGameManager* self = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) GfGameManager();
    self->initialize(param);
}

bool GfGameManager::isValidCollisionVelocity() {
    if (GfGameScene* scene = GfGameScene::get()) {
        return scene->m_validCollisionVelocity;
    }
    return false;
}

void GfGameManager::setValidCollisionVelocity(bool valid) {
    if (GfGameScene* scene = GfGameScene::get()) {
        scene->m_validCollisionVelocity = valid;
    }
}

bool GfGameManager::isLeaveGameForDebug() {
    if (GfGameManager* manager = get()) {
        if (manager->m_leaveGameForDebug) {
            return true;
        }
        return GfManager::isDestroyNow();
    }
    return false;
}

void GfGameManager::leaveGameForDebug() {
    if (GfGameManager* manager = get()) {
        manager->m_leaveGameForDebug = true;
        GfGameEvent::finishNewGameWait();
        GfGameEvent::stop();
        if (GfGameScene* scene = GfGameScene::get()) {
            scene->setForceStopBattle(true);
        }
    }
}

const OwnerBonus& GfGameManager::getOwnerBonus() {
    return *GfGameScene::get()->getOwnerBonus();
}

bool GfGameManager::isStartGame() {
    if (GfGameScene* scene = GfGameScene::get()) {
        return scene->m_startGame;
    }
    return true;
}

int GfGameManager::getScenarioId() {
    if (GfManager::isExecModeScenarioGame()) {
        unsigned short scenario = GfDataUtil::getScenarioFlag();
        return scenario == 0 ? 1 : scenario / 1000;
    }
    return 0;
}

void GfGameManager::setStartGame() {
    if (GfGameScene* scene = GfGameScene::get()) {
        scene->m_startGame = true;
    }
}

bool GfGameManager::isEnableRoomForHikariLv4() {
    if (GfGameScene* scene = GfGameScene::get()) {
        return scene->m_enableRoomForHikariLv4;
    }
    return false;
}

void GfGameManager::setStopMainMenuOpenForGimmick(bool stop) {
    if (GfGameScene* scene = GfGameScene::get()) {
        scene->m_stopMainMenuOpenForGimmick = stop;
    }
}


GF_OBJ_HANDLE* GfGameManager::getPartyLeader() {
    GF_OBJ_HANDLE* leader = GfGameParty::getLeader();
    GfObjAcc acc(leader);
    if (acc.m_obj != nullptr) {
        if (GfGameObj::isValidGameObj(leader, true, nullptr) || GfGameObj::isEnterGameObj(leader)) {
            return leader;
        }
        if (fw::Framework::isLayerPause(acc.getLayer()) && GfObjUtil::isUpdate(leader)) {
            return leader;
        }
    }
    return reinterpret_cast<GF_OBJ_HANDLE*>(-1);
}

GF_OBJ_HANDLE* GfGameManager::getPartyLeaderDriver() {
    GF_OBJ_HANDLE* driver = GfGameParty::getLeaderDriver();
    GfObjAcc acc(driver);
    if (GfGameObj::isValidGameObj(driver, true, nullptr) || GfGameObj::isEnterGameObj(driver)) {
        return driver;
    }
    if (fw::Framework::isLayerPause(acc.getLayer()) && GfObjUtil::isUpdate(driver)) {
        return driver;
    }
    return reinterpret_cast<GF_OBJ_HANDLE*>(-1);
}

void GfGameManager::collectPadCharList(mm::mtl::FixedArray<GF_OBJ_HANDLE*, 2>* list) {
    (*list)[0] = getControlMover();
}

bool GfGameManager::isEvent(bool sequential) {
    if (get() == nullptr) {
        return false;
    }
    if (GfGameState::test(2)) {
        return true;
    }
    if (!sequential) {
        return false;
    }
    return GfSequentialPlay::isInnerState(static_cast<GF_STATE>(20));
}

bool GfGameManager::isPlayEventHideChar(GF_OBJ_HANDLE* handle) {
    bool hidden = false;
    if (GfGameScene* scene = GfGameScene::get()) {
        GfObjAcc acc(handle);
        if (scene->isPlayEvent()) {
            hidden = !acc.isDisp(static_cast<OBJDISP>(0));
        }
    }
    return hidden;
}

bool GfGameManager::isField() {
    if (get() == nullptr || GfGameState::getState() != static_cast<GF_STATE>(3)) {
        return false;
    }
    if (isPlayerPause()) {
        return false;
    }
    if (isBattle()) {
        return false;
    }
    return GfGameState::getStateReserve() == static_cast<GF_STATE>(3);
}

namespace {
// the state or the reserved one is state (the name is not the original's)
bool isStateOrReserve(GF_STATE state) {
    return GfGameState::getState() == state || GfGameState::getStateReserve() == state;
}
}  // namespace

bool GfGameManager::isMapjumpOK() {
    return !isStateOrReserve(static_cast<GF_STATE>(8)) && !isStateOrReserve(static_cast<GF_STATE>(9));
}

bool GfGameManager::isFading(unsigned int layer) {
    if (layer == 0xFFFFFFFF) {
        return GfMenuManager::isFading(0) || GfMenuManager::isFading(1) || GfMenuManager::isFading(2);
    }
    return GfMenuManager::isFading(layer) || GfReqSmallCom::isExistCommand(static_cast<SCOM_TYPE>(27));
}


void GfGameManager::gevMapjump(GEV gev, const MapjumpCallbackInfo& info) {
    GfGameEnv::gevMapjump(gev, info);
    GfGameEvent::gevMapjump(gev, info);
    if (GfGameScene* scene = GfGameScene::get()) {
        scene->gevMapjump(gev, info);
    }
    GfGameVoice::gevMapjump(gev, info);
    GfQuestManager::gevMapjump(gev, info);
    GfGameMercenaries::gevMapjump(gev, info);
}

void GfGameManager::gevMercenariesMissionFlag(unsigned int a, unsigned int b, unsigned int c) {
    if (GfAchievManager* achiev = GfAchievManager::get()) {
        achiev->gevMercenariesMissionFlag(a, b, c);
    }
    if (GfGameScene* scene = GfGameScene::get()) {
        scene->gevMercenariesMissionFlag(a, b, c);
    }
    GfQuestManager::gevMercenariesMissionFlag(a, b, c);
    GfGameMercenaries::gevMercenariesMissionFlag(a, b, c);
}

void GfGameManager::gevOpenPortal() {
    if (GfGameScene* scene = GfGameScene::get()) {
        scene->gevOpenPortal();
    }
}

void GfGameManager::gevOpenMainMenu() {
    if (GfGameScene* scene = GfGameScene::get()) {
        scene->gevOpenMainMenu();
    }
}

void GfGameManager::qevCompleteQuest(const QuestCompleteParam& param) {
    GfGameMercenaries::qevCompleteQuest(param);
    if (GfKizunaringManager* kizunaring = GfKizunaringManager::get()) {
        kizunaring->qevCompleteQuest(param);
    }
    if (GfGameScene* scene = GfGameScene::get()) {
        scene->qevCompleteQuest(param);
    }
}

void GfGameManager::qevCompleteChildQuest(const QuestCompleteChildParam& param) {
    if (isGameTypeIra()) {
        return;
    }
    if (param.m_questId.m_id != 210) {
        return;
    }
    if (GfDataUtil::getScenarioFlag() != 8024) {
        return;
    }
    if (GfGameScene* scene = GfGameScene::get()) {
        if (!scene->isForceBossBattleBgm()) {
            scene->setForceBossBattleBgm(true);
        }
    }
}

bool GfGameManager::isGameTypeIra() {
    if (GfGameAoc* aoc = GfGameAoc::get()) {
        return aoc->m_mode == 1;
    }
    return false;
}


bool GfGameManager::isDisableBattou() {
    if (GfPlayComResetBlade::isPlaying(0)) {
        return true;
    }
    GfObjAcc acc(GfGameParty::getHandleBlade(0, -1));
    if (acc.isRebuild()) {
        return true;
    }
    return isEnableBattouWithHoodHomura(true);
}

bool GfGameManager::isEnableBattouWithHoodHomura(bool flag) {
    if (GfGameScene* scene = GfGameScene::get()) {
        if (scene->isBattle()) {
            return false;
        }
    }
    GfObjAcc leader(getControlMover());
    if (leader.getType() != 3) {
        return false;
    }
    if (leader.getDriverId() != 1) {
        return false;
    }
    if (GfDataDriver::getBlade(1, -1) != 1001) {
        return false;
    }
    GfObjAcc blade(GfGameParty::getHandleBlade(0, -1));
    if (blade.getBladeId() != 1001) {
        return false;
    }
    if (leader.isBattle()) {
        return false;
    }
    if (blade.isRebuild()) {
        return false;
    }
    if (GfGameScene::get() != nullptr && !GfGameScene::isPlayerWalkAndRun()) {
        return false;
    }
    if (flag && GfPlayComResetBlade::isPlaying(0)) {
        return false;
    }
    GfObjAcc target(leader.getTarget());
    if (target.getType() != 5) {
        return false;
    }
    if (flag && !GfGameCond::isGameCond(GfDataBlade::getSDataBlade(blade.getBladeId())->m_modelCondition)) {
        return false;
    }
    if (!isEnableOpenMainMenuSequence()) {
        return false;
    }
    if (flag && !isEnableOpenMainMenu()) {
        return false;
    }
    return true;
}

bool GfGameManager::isStopBattleSequence() {
    if (get() == nullptr || btl::BattleManager::get() == nullptr) {
        return true;
    }
    if (!btl::BattleManager::isInitialized()) {
        return true;
    }
    if (GfReqSmallCom::isExistCommand(static_cast<SCOM_TYPE>(53))) {
        return true;
    }
    if (GfObjManager* manager = GfObjManager::get()) {
        if (manager->hasReloadObjForDebug()) {
            return true;
        }
    }
    return false;
}

bool GfGameManager::isFadeout() {
    for (unsigned int layer = 0; layer < 3; layer++) {
        mm::Col4 color;
        GfMenuManager::getFadeColor(layer, color);
        if (color.a >= 0.9f) {
            return true;
        }
    }
    return false;
}

bool GfGameManager::isPlayerCameraPause() {
    if (GfManager::isDestroyNow() || _gfgm::s_bDisablePlayerCamPause) {
        return false;
    }
    if (isFadeout()) {
        return true;
    }
    if (GfGameScene* scene = GfGameScene::get()) {
        return scene->isPlayerCameraPause();
    }
    return false;
}

void GfGameManager::setDisablePlayerCameraPauseForTitle(bool flag) {
    _gfgm::s_bDisablePlayerCamPause = flag;
}

bool GfGameManager::isExecTutorial() {
    return GfMenuObjTutorial::isWaiting() | (GfPlayComStartTutorial::s_activateCount > 0);
}


bool GfGameManager::isPlayEvent() {
    if (GfGameScene* scene = GfGameScene::get()) {
        return scene->isPlayEvent();
    }
    return false;
}

bool GfGameManager::isGmkTutorialSequenceOK() {
    GfGameScene* scene = GfGameScene::get();
    if (scene == nullptr) {
        return false;
    }
    return scene->isPlayerStopFlag(static_cast<PLSTOP>(1)) || scene->isPlayerStopFlag(static_cast<PLSTOP>(3)) ||
           scene->isPlayerStopFlag(static_cast<PLSTOP>(4)) || scene->isPlayerStopFlag(static_cast<PLSTOP>(5));
}

bool GfGameManager::isAutoTalkOK() {
    if (isBattle()) {
        return false;
    }
    if (GfManager::isExecModeThater()) {
        return false;
    }
    return isControlFree();
}

bool GfGameManager::isExecCompleteUI() {
    return GfPlayComQuestCompleteUI::s_active > 0;
}


bool GfGameManager::isBattleStop() {
    if (GfGameScene* scene = GfGameScene::get()) {
        if (scene->isBattleStop()) {
            return true;
        }
        if (isBattle()) {
            return false;
        }
    }
    if (GfGameParty::getBladeBdatId(0, -1) != 1001) {
        return false;
    }
    GfObjAcc driver(GfGameParty::getHandleDriver(0, static_cast<PTPOS>(0)));
    GfObjAcc blade(GfGameParty::getHandleBlade(0, -1));
    if (blade.getBladeId() == 1001 && !driver.isBattle() && blade.isRebuild()) {
        return true;
    }
    return false;
}

bool GfGameManager::isFadeClear() {
    if (isFadeout()) {
        return false;
    }
    if (isFading(0xFFFFFFFF)) {
        return false;
    }
    for (unsigned int layer = 0; layer < 3; layer++) {
        mm::Col4 color;
        GfMenuManager::getFadeColor(layer, color);
        if (color.a > 0.0f) {
            return false;
        }
    }
    return true;
}

void GfGameManager::setControlMoverPositionForNoPlayer(const mm::Vec3& pos) {
    _gfgm::getMoverPosition() = pos;
}

bool GfGameManager::isPlayerFinishBattleState() {
    if (GfGameParty::isLeaderBlade()) {
        return true;
    }
    DataParamAcc acc(GfGameParty::getLeader());
    if (acc.getObjType() == 3 && acc.isValid() && acc.getObjType() == 3 && acc.getBdatId() == 2 &&
        acc.getBlade(-1, false) == 1004) {
        return true;
    }
    return false;
}

namespace {
// a create type a blade's creation event shows (6, 7 and 12) (the name is not the original's)
bool isBladeCreateType(int type) {
    switch (type) {
    case 6:
    case 7:
    case 12:
        return true;
    default:
        return false;
    }
}
}  // namespace

bool GfGameManager::isBusyBladeCreateEvent() {
    if (!GfPause::isPause(1)) {
        return false;
    }
    if (isEvent(false)) {
        return true;
    }
    mm::mtl::FixedList<GF_OBJ_HANDLE*, 1024>& list = *GfGameObj::getList(0);
    for (mm::mtl::FixedList<GF_OBJ_HANDLE*, 1024>::iterator it = list.begin(); it != list.end(); ++it) {
        GfObjSetup* setup = GfObjUtil::getObjSetup(*it);
        if (setup == nullptr) {
            continue;
        }
        if (!isBladeCreateType(setup->m_createType)) {
            continue;
        }
        GfObjAcc acc(*it);
        if (acc.getAlpha() <= 0.0f) {
            continue;
        }
        if (acc.isDisp(static_cast<OBJDISP>(0))) {
            return true;
        }
    }
    return false;
}

bool GfGameManager::isExistBossEnemy() {
    mm::mtl::FixedList<GF_OBJ_HANDLE*, 1024>& list = *GfGameObj::getList(5);
    for (mm::mtl::FixedList<GF_OBJ_HANDLE*, 1024>::iterator it = list.begin(); it != list.end(); ++it) {
        GfObjAcc acc(*it);
        if (GfDataEnemy::isBoss(acc.getEnArrangeId())) {
            return true;
        }
    }
    return false;
}

void GfGameManager::destroyBattleEnemy() {
    mm::mtl::FixedList<GF_OBJ_HANDLE*, 1024>& list = *GfGameObj::getList(5);
    for (mm::mtl::FixedList<GF_OBJ_HANDLE*, 1024>::iterator it = list.begin(); it != list.end(); ++it) {
        GfObjAcc acc(*it);
        if (acc.isBattle()) {
            DataParamAcc param(*it);
            if (param.getHp() != 0) {
                GfGameUtil::debugHpZero(*it);
            }
        }
    }
}

bool GfGameManager::isWaitGimmickPopForMapjump() {
    tl::TitleMain* title = tl::TitleMain::get();
    if (title == nullptr) {
        return true;
    }
    if (title->m_reqReturnTitle) {
        return false;
    }
    return !title->isStateReturnTitle();
}


bool GfGameManager::isExistBossEnemyWithHp() {
    mm::mtl::FixedList<GF_OBJ_HANDLE*, 1024>& list = *GfGameObj::getList(5);
    for (mm::mtl::FixedList<GF_OBJ_HANDLE*, 1024>::iterator it = list.begin(); it != list.end(); ++it) {
        GfObjAcc acc(*it);
        if (!acc.isBattle()) {
            continue;
        }
        DataParamAcc param(*it);
        unsigned int id = param.isValid() ? param.getBdatId() : 0;
        if ((GfDataEnemy::isBoss(id) || (param.isValid() && param.getBdatId() == 1683)) && param.getHp() != 0 &&
            param.getHp() < param.getHpMax(false)) {
            return true;
        }
    }
    return false;
}



}  // namespace gf


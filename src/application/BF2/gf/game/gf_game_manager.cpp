#include "classes/gf/IQuestEvent.h"
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

namespace gf {

GfGameManager::~GfGameManager() {
    ;
}

void GfGameManager::destroy() {
    GfGameManager* manager = get();
    manager->finalize();
    delete manager;
}

bool GfGameManager::isGameObjEmpty() {
    return GfGameObj::isEmpty();
}

GF_STATE GfGameManager::getState() {
    return GfGameState::getState();
}

void GfGameManager::setState(GF_STATE state, bool flag) {
    GfGameState::setState(state, flag);
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

void GfGameManager::gevBladeUnselect(unsigned int id, bool flag) {
    if (GfGameScene* scene = GfGameScene::get()) {
        scene->gevBladeUnselect(id, flag);
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

void GfGameManager::gevChangeScenarioFlag(unsigned int a0, unsigned int a1) {
    if (GfGameScene* scene = GfGameScene::get()) {
        scene->gevChangeScenarioFlag(a0, a1);
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

bool GfGameManager::isFieldLockMsgOK() {
    if (isEnableFieldAccess()) {
        if (GfGameScene* scene = GfGameScene::get()) {
            return scene->isControlFree();
        }
    }
    return false;
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

float GfGameManager::getFieldSpeed(const fw::UpdateInfo& info) {
    float speed = GfGameSpeed::getLayerSpeed(0);
    float pause = GfLayerPause::isLayerPause(0) ? 0.0f : 1.0f;
    return info.m_speed * (speed * pause);
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

bool GfGameManager::isAssetNumberInvalid() {
    return GfAssetManager::getUsedAssetPackInfo() > 511;
}

void GfGameManager::updateParam(const fw::UpdateInfo& info) {
    if (GfGameScene* scene = GfGameScene::get()) {
        scene->updateParam(info);
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

}  // namespace gf


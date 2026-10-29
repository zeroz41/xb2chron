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
#include "gf/SDataSave.h"
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
#include "classes/gf/TUnk_B535D0.h"
#include "classes/gf/GfPlayComOpenNpcEntry.h"
#include "gf/GfDataDriver.h"
#include "gf/GfQuestTask.h"
#include "classes/gf/GfPause.h"
#include "gf/GfDataEnemy.h"
#include "classes/gf/DataParamAcc.h"
#include "classes/gf/GfObjSetup.h"

namespace gf {

// Proposed name, not the original's: the symbols leave it unnamed (lbl_7100D6CBE8)
bool GfGameManager::s_disablePlayerCameraPause;

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
    s_disablePlayerCameraPause = false;
}

GF_STATE GfGameManager::getState() {
    return GfGameState::getState();
}

void GfGameManager::setState(GF_STATE state, bool flag) {
    GfGameState::setState(state, flag);
}

void GfGameManager::fn_710000FA68(unsigned int value, bool flag, unsigned int) {
    if (GfGameScene* scene = GfGameScene::get()) {
        scene->fn_71002C5200(value, flag);
    }
}

void GfGameManager::fn_710000FA60(unsigned int value, unsigned int) {
    if (GfGameScene* scene = GfGameScene::get()) {
        scene->fn_71002C56CC(value);
    }
}

void GfGameManager::fn_710000FA64(unsigned int value, unsigned int) {
    if (GfGameScene* scene = GfGameScene::get()) {
        scene->fn_71002C56D4(value);
    }
}

void GfGameManager::fn_710000FA20() {
    if (GfGameScene* scene = GfGameScene::get()) {
        scene->fn_71002C5994();
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
        party->fn_71002B8D3C();
    }
}

void GfGameManager::gevBattleEnd() {
    if (GfGameParty* party = GfGameParty::get()) {
        party->fn_71002B8D70();
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
        party->fn_71002B8D74(gev, id);
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

void GfGameManager::fn_710000FAB8(unsigned int id) {
    if (TUnk_B54858* aoc = TUnk_B54858::get()) {
        aoc->fn_71002A7734(id);
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

GF_OBJ_HANDLE* GfGameManager::fn_71002AA074() {
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
    return GfGameParty::fn_71002BC6F8();
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

bool GfGameManager::fn_71002AAA0C() {
    if (fn_71002A9E68()) {
        if (GfDataBlade::fn_7100231884() >= 11115 && GfDataBlade::fn_7100231884() < 11130) {
            return true;
        }
        return false;
    }
    if (GfDataBlade::fn_7100231884() >= 10034 && GfDataBlade::fn_7100231884() / 64 < 157) {
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
            if (GfTargetProperty* target = property->m_target) {
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

// Inferred helper (its name is not the original's): getControlMoverPosition and fn_71002AB894 share one guarded
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

float GfGameManager::getFieldSpeed(const fw::UpdateInfo& info) {
    float speed = GfGameSpeed::getLayerSpeed(0);
    float pause = GfLayerPause::isLayerPause(0) ? 0.0f : 1.0f;
    return info.m_speed * (speed * pause);
}

bool GfGameManager::isEnableOpenMainMenu() {
    if (fn_71002A9E68() && GfDataBlade::fn_7100231884() == 11002) {
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
    if (scene->fn_71002C4A14() || scene->isMaskMainMenu()) {
        return false;
    }
    int state = scene->m_openMainMenuState;
    bool open = (state == 0 || state == 1) && !scene->isMoverGetFieldDamage();
    if (!open) {
        return false;
    }
    if (GfGameCond::isGameCond(2592)) {
        if (!isClearGame() || GfDataBlade::fn_7100231884() != 1031) {
            return false;
        }
    }
    return !scene->m_disableOpenMainMenu;
}

bool GfGameManager::isClearGame() {
    if (GfManager::isExecModeAdvertize() || GfManager::isExecModeThater()) {
        tl::TitleMain* title = tl::TitleMain::get();
        if (title != nullptr && title->m_saveBuffer != nullptr &&
            GfDataBlade::fn_7100232054(title->fn_710014FB00()->m_game)) {
            return true;
        }
    }
    return GfDataBlade::fn_7100231FF8();
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

bool GfGameManager::fn_71002AC310() {
    return GfPlayComQuestCompleteUI::s_start > 0;
}

bool GfGameManager::fn_71002AC328() {
    return GfPlayComQuestCompleteUI::s_start > 0;
}

bool GfGameManager::fn_71002AC340() {
    if (GfPlayComQuestCompleteUI::s_active > 0 || GfPlayComOpenNpcEntry::get()) {
        return true;
    }
    if (GfGameScene* scene = GfGameScene::get()) {
        return scene->fn_71002C4B38();
    }
    return false;
}

bool GfGameManager::fn_71002AC384() {
    if (GfGameScene* scene = GfGameScene::get()) {
        return scene->m_value630 > 0;
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
        if (TUnk_B535D0* arena = TUnk_B535D0::get()) {
            if (arena->fn_7100291D54()) {
                return true;
            }
        }
    }
    return false;
}

bool GfGameManager::isAssetNumberInvalid() {
    return GfAssetManager::getUsedAssetPackInfo() > 511;
}

void GfGameManager::fn_71002AC558(bool flag) {
    if (TUnk_B54858* aoc = TUnk_B54858::get()) {
        aoc->fn_71002A7430(flag);
    }
}

void GfGameManager::fn_71002AC578(unsigned int value) {
    fn_71002EE904(value);
}

unsigned int GfGameManager::fn_71002AC57C() {
    return fn_71002EC634();
}

bool GfGameManager::fn_71002AC580() {
    if (TUnk_B535D0* arena = TUnk_B535D0::get()) {
        return arena->fn_7100291DB4();
    }
    return false;
}

bool GfGameManager::fn_71002AC598() {
    if (TUnk_B54858* aoc = TUnk_B54858::get()) {
        return aoc->fn_71002A75DC(0x30101);
    }
    return false;
}

unsigned int fn_71002AC5B8() {
    if (TUnk_B535D0* arena = TUnk_B535D0::get()) {
        return arena->m_record.m_value2C;
    }
    return 0;
}

GfGameManager::BattleChallengeRecord* GfGameManager::fn_71002AC5D8() {
    return &TUnk_B535D0::get()->m_record;
}

unsigned int GfGameManager::fn_71002AC5EC() {
    if (TUnk_B535D0* arena = TUnk_B535D0::get()) {
        return arena->m_record.m_value28;
    }
    return 0;
}

bool GfGameManager::fn_71002AC60C(BattleChallengeRecord* record, unsigned int id, unsigned int mode) {
    if (TUnk_B535D0* arena = TUnk_B535D0::get()) {
        arena->fn_7100291E40(record, id, mode);
        return true;
    }
    return false;
}

bool GfGameManager::fn_71002AC64C() {
    return GfDataBlade::fn_7100232754();
}

bool GfGameManager::fn_71002AC650() {
    return GfItemUtil::getItemBoxCount(25472) != 0;
}

bool GfGameManager::fn_71002AC670() {
    return GfItemUtil::getItemBoxCount(25541) != 0;
}

void GfGameManager::fn_71002AC6A8() {
    if (fn_71002EDA8C()) {
        if (GfGameScene* scene = GfGameScene::get()) {
            scene->m_iraCampSolo = true;
        }
    }
}

bool GfGameManager::fn_71002AC6D8() {
    if (GfGameScene* scene = GfGameScene::get()) {
        return scene->isPlayEvent();
    }
    return false;
}

void GfGameManager::fn_71002AC6F0() {
    if (GfGameScene* scene = GfGameScene::get()) {
        scene->m_flag8C0 = true;
    }
}

bool GfGameManager::fn_71002AC70C() {
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

bool GfGameManager::fn_71002AC764() {
    if (GfGameScene* scene = GfGameScene::get()) {
        return scene->fn_71002C4BFC();
    }
    return false;
}

bool GfGameManager::fn_71002AC77C(unsigned int party) {
    TUnk_B54858* aoc = TUnk_B54858::get();
    if (aoc && aoc->m_mode == 1) {
        GfObjAcc driver0(GfGameParty::getHandleDriver(party, 0));
        GfObjAcc driver1(GfGameParty::getHandleDriver(party, 1));
        GfObjAcc driver2(GfGameParty::getHandleDriver(party, 2));
        return driver0.isBattle() || driver1.isBattle() || driver2.isBattle();
    }
    GfObjAcc driver(GfGameParty::getHandleDriver(party, 0));
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

bool GfGameManager::fn_71002AC89C() {
    TUnk_B54858* aoc = TUnk_B54858::get();
    if (aoc && aoc->m_mode != 1 && aoc->fn_71002A75DC(0x30101)) {
        return fn_71002EE9A4();
    }
    return false;
}

unsigned int GfGameManager::fn_71002AC8E0() {
    return GfDataBlade::fn_710024DD88();
}

bool GfGameManager::fn_71002AC908() {
    if (tl::TitleMain* title = tl::TitleMain::get()) {
        return title->m_flag21B;
    }
    return false;
}

bool GfGameManager::fn_71002AC930() {
    if (TUnk_B535D0* arena = TUnk_B535D0::get()) {
        if (arena->fn_7100291D54()) {
            if (btl::TUnk_B3A9C8* challenge = btl::TUnk_B3A9C8::get()) {
                if (challenge->fn_7100026A48()) {
                    return true;
                }
                if (challenge->fn_7100026814() && btl::Utility::AI_GetEnemyNum() == 0) {
                    return true;
                }
            }
        }
    }
    return false;
}

bool GfGameManager::fn_71002AC99C() {
    return fn_71002EE9EC();
}

bool GfGameManager::fn_71002AC9A0() {
    return fn_71002EEA34();
}

bool GfGameManager::fn_71002AC9A4() {
    return fn_71002EEA7C();
}

void GfGameManager::updateParam(const fw::UpdateInfo& info) {
    if (GfGameScene* scene = GfGameScene::get()) {
        scene->updateParam(info);
    }
}

void GfGameManager::fn_71002AC9C0(const fw::UpdateInfo& info) {
    if (GfGameScene* scene = GfGameScene::get()) {
        scene->fn_71002CC060(info);
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
        unsigned short scenario = GfDataBlade::fn_7100231884();
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

bool GfGameManager::fn_71002AA25C(GF_OBJ_HANDLE* handle) {
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

void GfGameManager::fn_710000FA1C() {
    if (GfGameScene* scene = GfGameScene::get()) {
        scene->fn_71002C79B8();
    }
}

void GfGameManager::fn_710000FA18() {
    if (GfGameScene* scene = GfGameScene::get()) {
        scene->fn_71002C7C44();
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
    if (fn_71002A9E68()) {
        return;
    }
    if (param.m_questId.m_id != 210) {
        return;
    }
    if (GfDataBlade::fn_7100231884() != 8024) {
        return;
    }
    if (GfGameScene* scene = GfGameScene::get()) {
        if (!scene->isForceBossBattleBgm()) {
            scene->setForceBossBattleBgm(true);
        }
    }
}

bool GfGameManager::fn_71002A9E68() {
    if (TUnk_B54858* aoc = TUnk_B54858::get()) {
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
    if (GfManager::isDestroyNow() || s_disablePlayerCameraPause) {
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

void GfGameManager::fn_71002AB4F8(bool flag) {
    s_disablePlayerCameraPause = flag;
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

bool GfGameManager::isQuestCompleteUI() {
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
    GfObjAcc driver(GfGameParty::getHandleDriver(0, 0));
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

void GfGameManager::fn_71002AB894(const mm::Vec3& pos) {
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


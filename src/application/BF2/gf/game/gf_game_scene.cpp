#include "classes/gf/GfGameScene.h"
#include "gf/GfGameUtil.h"
#include "mm/mtl/Bitflag.h"
#include "classes/gf/GfGameScene.h"
#include "gf/GfObjAcc.h"
#include "gf/GfDataParty.h"
#include "gf/GfDataAchievement.h"
#include "classes/gf/GfFieldBgm.h"
#include "classes/gf/SCOM_FIELD_VOICE.h"
#include "classes/gf/GfGameScene.h"
#include "classes/gf/GfFieldBgm.h"
#include "classes/gf/GfAllocator.h"
#include "gf/GfSetupParam.h"
#include "classes/gf/GfGameManager.h"
#include "classes/gf/GfGameParty.h"
#include "classes/gf/GfGameState.h"
#include "classes/gf/GfManager.h"
#include "classes/gf/GfPause.h"
#include "classes/gf/GfPlayComResetBlade.h"
#include "classes/gf/GfGameFlag.h"
#include "classes/gf/GfObjProperty.h"
#include "classes/gf/SCOM_FIELD_VOICE.h"
#include "gf/GfDataAchievement.h"
#include "gf/GfDataBlade.h"
#include "gf/GfDataParty.h"
#include "gf/GfDataShop.h"
#include "gf/GfGameUtil.h"
#include "gf/GfGameUtilNanakoori.h"
#include "gf/GfObjAcc.h"
#include "gf/GfObjUtil.h"
#include "gf/GfSelectBlade.h"
#include "gf/GfTargetProperty.h"
#include "classes/gf/GfEvent.h"
#include "gf/GfPartySelect.h"
#include "classes/gf/DataParamAcc.h"
#include "classes/gf/GfObjSetup.h"
#include "gf/GfDataEnemy.h"
#include "classes/gf/GfGameRide.h"
#include "classes/gf/GfSound.h"
#include "classes/gf/GfSlowAttack.h"
#include "classes/gf/GfTrinityAttack.h"
#include "classes/gf/GfPlayComEventFade.h"
#include "string.h"

namespace gf {

void GfGameScene::setPlayerStopFlag(PLSTOP flag, bool stop) {
    m_playerStopQueue.push_back(flag | (stop ? 0x80 : 0));
}

bool GfGameScene::isPlayerStopFlag(PLSTOP flag) {
    return m_playerStopFlag.test(flag);
}

void GfGameScene::EvtPlayerStop::setPlayerStop(bool stop) {
    if (GfManager::isExecModeThater()) {
        return;
    }
    if (stop) {
        if (m_state != 1) {
            m_scene->setPlayerStopFlag(m_type, true);
            m_state = 1;
        }
    } else {
        if (m_scene->isPlayerStopFlag(m_type)) {
            m_scene->setPlayerStopFlag(m_type, false);
            GfGameManager::setGmkTutorialMoverOK(false);
        }
        m_state = 0;
    }
}

void GfGameScene::build(const GfSetupParam& param) {
#line 461
    new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) GfGameScene(param);
}

void GfGameScene::destroy() {
    GfGameScene* scene = get();
    if (GfSound* sound = GfSound::get()) {
        sound->releaseCategoryHandle(scene->m_seCategoryHandles[0]);
        sound->releaseCategoryHandle(scene->m_seCategoryHandles[1]);
        sound->releaseCategoryHandle(scene->m_seCategoryHandles[2]);
    }
    GfSlowAttack::destroy();
    GfTrinityAttack::destroy();
    scene->m_alive = false;
    delete scene;
}

bool GfGameScene::isPlayerSwimOnCloud() {
    GfObjProperty* property = GfObjUtil::getProperty(GfGameManager::getControlMover());
    return property != nullptr && property->m_target->m_state == 2;
}

bool GfGameScene::isPlayerWalkAndRun() {
    GfObjProperty* property = GfObjUtil::getProperty(GfGameManager::getControlMover());
    return property != nullptr && property->m_target->m_state == 0;
}

bool GfGameScene::isPlayEvent() const {
    return m_playEvent;
}

bool GfGameScene::isMaskMainMenu() const {
    return m_maskMainMenu;
}

bool GfGameScene::isMoverGetFieldDamage() const {
    return _gfgsc::isPartyMemberGetFieldDamage(0);
}

void GfGameScene::setEventPlayerStop(bool stop) {
    m_eventPlayerStop.setPlayerStop(stop);
}

void GfGameScene::setResetBladePlayerStop(bool stop) {
    m_resetBladePlayerStop.setPlayerStop(stop);
}

void GfGameScene::fn_71002C345C(bool stop) {
    m_gimmickPlayerStop.setPlayerStop(stop);
}

bool GfGameScene::isControlFree() const {
    if (GfGameState::getState() == static_cast<GF_STATE>(3) && GfGameManager::getState() == static_cast<GF_STATE>(3) &&
        m_playerPause == 0) {
        return GfGameState::getStateReserve() == static_cast<GF_STATE>(3);
    }
    return false;
}

bool GfGameScene::isEnableFieldBladeChange() const {
    if (m_fieldBladeChangeTime >= 0.5f && GfGameManager::isEnableOpenMainMenu()) {
        return GfGameManager::isControlFree();
    }
    return false;
}

void GfGameScene::setForceBossBattleBgm(bool force) {
    m_forceBossBattleBgm = force;
}

bool GfGameScene::isForceBossBattleBgm() const {
    return m_forceBossBattleBgm;
}

void GfGameScene::setForceEventBgm(float time) {
    m_forceEventBgm = time;
}

bool GfGameScene::isForceEventBgm() const {
    return m_forceEventBgm > 0.0f;
}

bool GfGameScene::isPlayerTalkForce() {
    return m_playerTalkForce[0] || m_playerTalkForce[1];
}

void GfGameScene::setPlayerTalkForce(bool force) {
    m_playerTalkForce[0] = force;
}

void GfGameScene::refreshGimmickFlag() {}

void GfGameScene::setAutoBattle(bool flag) {
    m_autoBattle = flag;
}

bool GfGameScene::isRide(unsigned int id) const {
    if (id == 0xFFFFFFFF) {
        return false;
    }
    GfObjAcc acc(GfGameParty::getHandleDriver(id, 0));
    return GfDataParty::isNiaByakko(id) && !acc.isBattle();
}

bool GfGameScene::isRideObj(GF_OBJ_HANDLE* handle) const {
    GfObjAcc acc(handle);
    if (acc.getPartyID() == 0xFFFFFFFF) {
        return false;
    }
    return GfDataParty::isRideChar(acc.getBdatId());
}

bool GfGameScene::isRideParty(unsigned int id) const {
    return GfDataParty::isNiaByakko(id);
}

unsigned int GfGameScene::createPlayerPause() {
    unsigned int bit = 1;
    for (unsigned int i = 0; i < 32; i++, bit <<= 1) {
        if ((m_playerPause & bit) == 0) {
            m_playerPause |= bit;
            return i;
        }
    }
    return 0xFFFFFFFF;
}

void GfGameScene::destroyPlayerPause(unsigned int pause) {
    m_playerPause &= ~(1 << pause);
}

bool GfGameScene::isPlayerPause() const {
    if (GfGameManager::getState() == static_cast<GF_STATE>(3)) {
        return m_playerPause != 0;
    }
    return true;
}

bool GfGameScene::isPlayerPauseForBattle() const {
    if (GfGameManager::getState() == static_cast<GF_STATE>(3) || GfGameManager::getState() == static_cast<GF_STATE>(24)) {
        return m_playerPause != 0;
    }
    return true;
}

void GfGameScene::setDeadType(GfPlayerDead type) {
    m_deadType = type;
}

GfPlayerDead GfGameScene::getDeadType() {
    return m_deadType;
}

void GfGameScene::setDamageCharacter(GF_OBJ_HANDLE* handle) {
    for (DamageCharacter& character : m_damageCharacters) {
        if (character.m_handle == handle) {
            character.m_time = 0;
            return;
        }
    }
}

void GfGameScene::saveBattleHpForEnemy(GF_OBJ_HANDLE* handle) {
    if (!GfGameManager::isScenarioGame()) {
        return;
    }
    DataParamAcc acc(handle);
    GfObjSetup* setup = GfObjUtil::getObjSetup(handle);
    bool skip = false;
    if (setup != nullptr) {
        switch (setup->m_createType) {
        case 2:
        case 3:
        case 11:
            skip = true;
            break;
        default:
            break;
        }
    }
    if (!skip) {
        unsigned int hp = acc.getHp();
        if (hp != 0) {
            unsigned int type = GfDataEnemy::getSavedHpType(acc.isValid() ? acc.getBdatId() : 0);
            if (type >= 1 && type <= 3) {
                GfDataEnemy::setSavedHp(type, hp);
            }
        }
    }
}

bool GfGameScene::isDisableJumpForRide() const {
    if (m_frameCount690 < 30) {
        return true;
    }
    if (!m_rideActive) {
        return false;
    }
    GfObjAcc acc(GfGameParty::getHandleDriver(0, 0));
    if (isBattle() && !acc.isBattle() && m_openMainMenuState != 2) {
        return false;
    }
    return m_rideActive;
}

bool GfGameScene::fn_71002C4A14() {
    return m_frameCount690 < 30;
}

bool GfGameScene::isBattle() const {
    GfGameScene* scene = get();
    return scene != nullptr && scene->m_battle;
}

bool GfGameScene::fn_71002C4B38() {
    return m_value698 < 2;
}

bool GfGameScene::isResetBladePlay() const {
    return GfPlayComResetBlade::isPlaying(0) || GfPlayComResetBlade::isPlaying(1) || GfPlayComResetBlade::isPlaying(2);
}

void GfGameScene::fn_71002C4B80(const char* name) {
    if (strstr(name, "aoc_tut24") != nullptr || strstr(name, "aoc_tut04") != nullptr ||
        strstr(name, "aoc_tut10") != nullptr) {
        m_tutorialPlayerControl = true;
    }
}

void GfGameScene::fn_71002C4BE4() {
    if (m_tutorialPlayerControl) {
        m_tutorialPlayerControl = false;
        GfEvent::callPlayerControl(GEV(15));
    }
}

bool GfGameScene::fn_71002C4BFC() {
    return m_value68C != 0;
}

void GfGameScene::gevExecBuy(unsigned int, unsigned int, unsigned int shop) {
    if (shop == 39 && GfGameFlag::getLocal(1, 50547) == 0 && GfDataShop::getPrivilegeItem(39) != 0) {
        GfGameFlag::setLocal(1, 50547, 1);
    }
}

void GfGameScene::gevChangeParty() {
    GfSelectBlade::resetStartBattleSetId(0);
    GfSelectBlade::resetStartBattleSetId(1);
    GfSelectBlade::resetStartBattleSetId(2);
}

void GfGameScene::gevBladeUnselect(unsigned int blade, bool flag) {
    if (!flag && !GfDataBlade::isActivateUnuse(blade)) {
        GfGameUtil::execSaveAchievementPopup(blade);
    }
}

void GfGameScene::gevChangeWeather(unsigned int weather, unsigned int arg) {
    int controlFree = GfGameManager::isControlFree();
    if (weather - 3 <= 2 && arg == 0 && controlFree) {
        SCOM_FIELD_VOICE::createBadWeather();
    }
}

void GfGameScene::gevChangeTimeRange(unsigned int range) {
    if (GfGameManager::isControlFree()) {
        if (range == 3) {
            SCOM_FIELD_VOICE::createTime(static_cast<CV_FIELD>(32));
        } else if (range == 0) {
            SCOM_FIELD_VOICE::createTime(static_cast<CV_FIELD>(31));
        }
    }
}

void GfGameScene::gevControllFree(bool) {}

void GfGameScene::gevBattleStart() {
    m_battleAchievement.m_battleStarted = true;
    GfDataAchievement::clearTotalCount(146);
    if (m_forceBossBattleBgm) {
        if (GfGameManager::isExistBossEnemy() || GfFieldBgm::get()->isBossBgmCopied()) {
            m_bossBattleBgm = true;
        } else {
            m_forceBossBattleBgm = false;
        }
    }
    m_forceEventBgm = 0.0f;
}

void GfGameScene::gevMercenariesMissionFlag(unsigned int mission, unsigned int flag, unsigned int) {
    if (GfGameUtilNanakoori::checkCompleteMission(mission, flag)) {
        m_completeQuest = true;
    }
}

void GfGameScene::fn_71002C7C44() {
    if (GfGameManager::fn_71002A9E68()) {
        return;
    }
    if (GfDataBlade::fn_7100231884() >= 8003 && GfGameFlag::getLocal(1, 52962) == 0) {
        GfGameFlag::setLocal(1, 52962, 1);
    }
}

void GfGameScene::qevCompleteQuest(const QuestCompleteParam&) {
    m_completeQuest = true;
}

void GfGameScene::postUpdate(const fw::UpdateInfo& info) {
    updateAppendModel(info);
    if (GfPause::isPause(1) || GfPlayComEventFade::s_start != 0) {
        m_frameCount690 = 0;
    } else if (m_frameCount690 < 999) {
        m_frameCount690++;
    }
}

const OwnerBonus* GfGameScene::getOwnerBonus() const {
    return &m_ownerBonus;
}

void GfGameScene::setCameraAvtivateOneTime() {
    m_cameraActivateOneTime = true;
}

bool GfGameScene::isPlayerCameraPause() {
    if (m_playerCameraPause) {
        return true;
    }
    if (m_cameraActivateOneTime) {
        m_cameraActivateOneTime = false;
        return false;
    }
    return GfPause::isPause(1);
}

void GfGameScene::setPlayerCameraPause(bool pause) {
    if (pause) {
        m_playerCameraPause = true;
    } else {
        m_playerCameraPause = false;
    }
}

void GfGameScene::setForceBattleTime(float time) {
    GfGameScene* scene = get();
    if (scene != nullptr) {
        scene->m_forceBattleTime = time;
    }
}

void GfGameScene::setForceStopBattle(bool stop) {
    GfGameScene* scene = get();
    if (scene != nullptr) {
        scene->m_forceStopBattle = stop;
    }
}

void GfGameScene::addDamage(GF_OBJ_HANDLE* handle, const MsgObjectNotifyDamage& msg) {
    m_battleAchievement.addDamage(handle, msg);
    setDamageCharacter(handle);
    if (GfObjUtil::getObjType(handle) == 5) {
        saveBattleHpForEnemy(handle);
    }
}

void GfGameScene::addMoneyLog() {
    m_moneyLogTime = 0.5f;
}

QuestID GfGameScene::getQuestIdForTaskLog() const {
    return m_questIdForTaskLog;
}

void GfGameScene::updateRideRequest(const fw::UpdateInfo&) {
    if (!m_rideRequest) {
        return;
    }
    if (!GfGameRide::testRideOn() && isRide(0)) {
        if (isEnableRideCondition(0)) {
            m_rideRequest = false;
            GfGameRide::setRideOn(true);
        }
    } else {
        m_rideRequest = false;
    }
}

void GfGameScene::setRideOn(unsigned int id) {
    if (id == 0xFFFFFFFF) {
        return;
    }
    GfObjAcc acc(GfGameParty::getHandleDriver(id, 0));
    if (GfDataParty::isNiaByakko(id) && !acc.isBattle()) {
        m_rideRequest = false;
        if (!GfGameRide::testRideOn()) {
            m_rideRequest = true;
        }
    }
}

}  // namespace gf
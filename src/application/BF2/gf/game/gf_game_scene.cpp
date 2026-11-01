#include "classes/gf/GfGameScene.h"
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
#include "classes/gf/GfAppendWire.h"
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
#include "classes/gf/GfMenuObjExpGet.h"
#include "classes/gf/GfGameObj.h"
#include "classes/gf/GfObj.h"
#include "gf/MsgObjectHealHp.h"
#include "gf/MapjumpCallbackInfo.h"
#include "classes/gf/SCOM_ZONE.h"
#include "classes/gf/GfWeapon.h"
#include "classes/gf/SCOM_HOMURI_PARTS.h"
#include "gf/GfEquipUtil.h"
#include "gf/SDataDriver.h"
#include "gf/GfDataDriver.h"
#include "gf/GfItemUtil.h"
#include "classes/gf/GfGameTarget.h"
#include "classes/gf/GfArtsMovie.h"
#include "classes/gf/GfChainAttack.h"
#include "gf/QuestListAcc.h"
#include "classes/gf/GfQuestManager.h"
#include "fw/UpdateInfo.h"
#include "btl/Utility.h"
#include "classes/gf/GfLayerPause.h"
#include "classes/gf/GfItemBox.h"

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

GfGameScene::~GfGameScene() {}

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

void GfGameScene::setHomuriWeaponExtraMesh(bool flag, float value) {
    if (GfGameManager::isClearGame()) {
        unsigned int party = GfGameParty::getPartyId(3, 1);
        if (party != 0xFFFFFFFF) {
            DataParamAcc acc(GfGameParty::getHandleBlade(party, -1));
            if (acc.isValid() && acc.getBdatId() == 1003) {
                SCOM_HOMURI_PARTS::create(party, flag, value);
            }
        }
    }
}

bool GfGameScene::isEnableFieldBladeChange() const {
    if (m_fieldBladeChangeTime >= 0.5f && GfGameManager::isEnableOpenMainMenu()) {
        return GfGameManager::isControlFree();
    }
    return false;
}

bool GfGameScene::isEnableRideCondition(unsigned int id) const {
    if (id != 0) {
        return true;
    }
    if (GfGameRide::testRideOn()) {
        return false;
    }
    if (GfGameManager::isPlayerDeadSequence()) {
        return false;
    }
    GfObjAcc acc(GfGameManager::getPartyLeaderDriver());
    if (acc.isBattle()) {
        return false;
    }
    if (acc.getPartyID() != 0) {
        return true;
    }
    if (!GfDataParty::isRideChar(acc.getDriverId())) {
        return true;
    }
    if (m_value258 < 3) {
        return false;
    }
    if (GfLayerPause::isLayerPause(4)) {
        return false;
    }
    return m_openMainMenuState != 2;
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

void GfGameScene::destroyDriverAppendModelControl(GF_OBJ_HANDLE* handle) {
    mm::mtl::FixedList<GfAppendWire*, 8>::iterator it = m_appendWires.find_if(
        [handle](GfAppendWire* wire) { return wire->m_wire == handle || wire->m_owner == handle; });
    if (it != m_appendWires.end()) {
        delete *it;
        m_appendWires.erase(it);
    }
}

void GfGameScene::enterExtraControlForHanaJS(GF_OBJ_HANDLE* handle) {
    if (m_hanaJSObjs.size() == m_hanaJSObjs.capacity()) {
        return;
    }
    GfObjAcc acc(handle);
    if (acc.getBdatId() != 1005) {
        return;
    }
    GfObjSetup* setup = GfObjUtil::getObjSetup(handle);
    if (setup == nullptr) {
        return;
    }
    bool skip = false;
    switch (setup->m_createType) {
    case 2:
    case 3:
    case 11:
        skip = true;
        break;
    default:
        break;
    }
    if (skip) {
        return;
    }
    m_hanaJSObjs.push_back(handle);
}

GfAppendWire* GfGameScene::getAppendControl(GF_OBJ_HANDLE* handle) {
    mm::mtl::FixedList<GfAppendWire*, 8>::iterator it = m_appendWires.find_if(
        [handle](GfAppendWire* wire) { return wire->m_wire == handle || wire->m_owner == handle; });
    if (it == m_appendWires.end()) {
        return nullptr;
    }
    return *it;
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

const mm::Vec3& GfGameScene::getEnableSavePos() const {
    int i = 0;
    for (;;) {
        if (i < 7) {
            if (m_savePos[i++].m_enable) {
                break;
            }
        } else {
            return GfGameManager::getControlMoverPosition();
        }
    }
    i--;
    return reinterpret_cast<const mm::Vec3&>(m_savePos[i].m_pos);
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

void GfGameScene::applyMapjumpForStart(const MapjumpCallbackInfo&) {
    for (unsigned int i = 0; i < 3; i++) {
        GF_OBJ_HANDLE* handle = GfGameParty::getHandleDriver(i, 0);
        if (handle != reinterpret_cast<GF_OBJ_HANDLE*>(-1)) {
            DataParamAcc acc(handle);
            if (acc.isValid()) {
                if (GfObj* obj = GfObjUtil::getObj(handle)) {
                    MsgObjectHealHp msg(0, 1);
                    msg.m_flags = MsgObjectHealHp::Flags();
                    fw::MessageObject* object = obj;
                    object->recieveMessage(object, msg);
                }
            }
        }
    }
    reinterpret_cast<mm::Vec3&>(m_pos2C0) = mm::Vec3::zero;
    for (int i = 0; i < 7; i++) {
        m_savePos[i].m_enable = false;
        reinterpret_cast<mm::Vec3&>(m_savePos[i].m_pos) = mm::Vec3::zero;
    }
    m_flag3B0 = false;
}

void GfGameScene::applyMapjumpForEnd(const MapjumpCallbackInfo& info) {
    SCOM_ZONE::create(info.m_mapId);
    if (GfSound* sound = mm::mtl::PtrSingleton<GfSound>::sys()) {
        sound->setCategoryVolume(m_seCategoryHandles[1], static_cast<fw::SoundCategory>(8), 1.0f, 1.0f);
        sound->setCategoryVolume(m_seCategoryHandles[1], static_cast<fw::SoundCategory>(1), 1.0f, 1.0f);
        sound->setCategoryVolume(m_seCategoryHandles[1], static_cast<fw::SoundCategory>(10), 1.0f, 1.0f);
        sound->setCategoryVolume(m_seCategoryHandles[1], static_cast<fw::SoundCategory>(5), 1.0f, 1.0f);
        sound->setCategoryVolume(m_seCategoryHandles[1], static_cast<fw::SoundCategory>(6), 1.0f, 1.0f);
        sound->setCategoryVolume(m_seCategoryHandles[1], static_cast<fw::SoundCategory>(7), 1.0f, 1.0f);
    }
    if (m_flag6A0) {
        m_flag6A0 = false;
        m_flag6A1 = true;
    }
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

void GfGameScene::fn_71002C5994() {
    mm::mtl::FixedList<GF_OBJ_HANDLE*, 1024>& list = *GfGameObj::getList(5);
    for (mm::mtl::FixedList<GF_OBJ_HANDLE*, 1024>::iterator it = list.begin(); it != list.end(); ++it) {
        fn_71002E0F28(*it);
    }
}

void GfGameScene::gevDriverActivate(unsigned int driver, ActivateType from, ActivateType to) {
    if (from != 0 && to == 0) {
        switch (driver) {
        case 5:
            if (GfDataBlade::fn_710023220C()) {
                GfGameUtil::execDriverDead(5);
            }
            break;
        case 12: {
            unsigned int acce = GfEquipUtil::getEquipDriverAcce(12, 0);
            GfGameUtil::execDriverDead(12);
            if (acce != 0) {
                GfItemUtil::addItemBox(acce, -1);
            }
            GfDataDriver::getSDataDriver(12)->m_defaultAcceDone = false;
            break;
        }
        }
    } else if (from == 0 && to != 0) {
        GfGameUtil::execEquipDriverDefaultAcce(driver);
        GfGameUtil::fn_71002EB4B8(driver);
    }
}

void GfGameScene::gevBladeActivate(unsigned int blade, ActivateType from, ActivateType to) {
    if (blade == 1008 && from != 0 && to == 0) {
        if (GfDataBlade::fn_7100231884() == 3048 && GfDataBlade::getEquipOrbMax(1008) != 0) {
            unsigned int slot = 0;
            do {
                GfEquipUtil::equipBladeOrb(1008, 0, slot, GfItemHandle());
                slot++;
            } while (slot < GfDataBlade::getEquipOrbMax(1008));
        }
    }
    if (from == 0 && to != 0 && !GfDataBlade::isUnselect(blade)) {
        GfGameUtil::execSaveAchievementPopup(blade);
    }
}

void GfGameScene::gevBladeUnselect(unsigned int blade, bool flag) {
    if (!flag && !GfDataBlade::isActivateUnuse(blade)) {
        GfGameUtil::execSaveAchievementPopup(blade);
    }
}

void GfGameScene::gevDriverLevel(unsigned int driver, unsigned int level, unsigned int) {
    GF_OBJ_HANDLE* handle = GfGameParty::getHandleDriverByBdatID(driver);
    if (handle != reinterpret_cast<GF_OBJ_HANDLE*>(-1) && !GfGameManager::isStartGame()) {
        GfMenuObjExpGet::OpenParam param;
        param.m_extra = 0;
        param.m_type = 0;
        param.m_value = 0;
        param.m_bonus = false;
        param.m_type = 3;
        param.m_value = level;
        param.m_object = handle;
        GfMenuObjExpGet::fn_7100406D3C(param);
    }
}

void GfGameScene::gevMapjump(GEV gev, const MapjumpCallbackInfo& info) {
    switch (gev) {
    case 4:
        m_forceStopBattle = false;
        if (info.m_mapId != 0 && info.m_mapId != info.pad_8) {
            m_forceBossBattleBgm = false;
            m_bossBattleBgm = false;
            m_forceEventBgm = 0.0f;
        }
        break;
    case 1:
        applyMapjumpForStart(info);
        break;
    case 7:
        applyMapjumpForEnd(info);
        break;
    }
}

void GfGameScene::gevGameObjEnter(GF_OBJ_HANDLE* handle) {
    GfObjAcc acc(handle);
    switch (acc.getType()) {
    case 13:
        createDriverAppendModelControl(handle);
        break;
    case 6:
        enterExtraControlForHanaJS(handle);
        break;
    case 4: {
        enterExtraControlForHanaJS(handle);
        ActivateType type = GfDataBlade::getBladeActivateType(acc.getBladeId());
        GfEvent::callBladeActivate(acc.getBladeId(), type, type);
        break;
    }
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

void GfGameScene::gevPlayEvent(GEV gev, unsigned int id) {
    switch (gev) {
    case 8:
        if (!GfManager::isExecModeThater()) {
            GfGameUtil::setWatchedEvent(id);
        }
        break;
    case 10:
        if (!m_eraseQuestEnemies.empty()) {
            for (GF_OBJ_HANDLE* handle : m_eraseQuestEnemies) {
                GfObjUtil::destroy(handle);
            }
            m_eraseQuestEnemies.clear();
        }
        m_playEvent = true;
        break;
    case 11:
        playEventPlayEnd(id);
        break;
    case 12:
        playEventSequenceStart(id);
        break;
    case 13:
        playEventSequenceEnd(id);
        break;
    case 14:
        fn_71002C6D48(id);
        break;
    default:
        break;
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

void GfGameScene::enterBattle(bool battle) {
    if (battle != m_battle) {
        if (battle) {
            m_battle = true;
            GfEvent::callBattleStart();
        } else {
            m_battle = false;
            GfEvent::callBattleEnd();
        }
    }
    m_homuraBattle = false;
    if (battle) {
        unsigned int party = GfGameParty::getPartyId(3, 1);
        if (party != 0xFFFFFFFF) {
            DataParamAcc acc(GfGameParty::getHandleBlade(party, -1));
            if (acc.isValid() && acc.getBdatId() == 1003) {
                m_homuraBattle = true;
            }
        }
    }
    for (unsigned int i = 0; i < 3; i++) {
        GfObjUtil::setDisableAutoHeal(GfGameParty::getHandleDriver(i, 0), false);
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

void GfGameScene::updateParam(const fw::UpdateInfo&) {
    if (m_ownerBonusDirty) {
        m_ownerBonusDirty = false;
        GfGameUtil::getOwnerBonus(m_ownerBonus);
    }
    {
        mm::mtl::FixedVector<unsigned short, 32> drivers;
        GfPartySelect::getDriverList(drivers, GfPartySelect::LIST_TYPE(1), 0);
        GfPartySelect::getDriverList(drivers, GfPartySelect::LIST_TYPE(0), 0);
        for (unsigned short driver : drivers) {
            GfGameUtil::refreshEnhanceState(driver);
        }
    }
    updatePlayerState();
}

void GfGameScene::updateBladeChangeInField(const fw::UpdateInfo& info) {
    float time = m_fieldBladeChangeTime;
    m_fieldBladeChangeTime = 0.0f;
    if (!GfGameManager::isControlFree() || GfGameManager::isBattle() || GfManager::isDestroyNow() ||
        !btl::Utility::IsEnableFieldBladeChange()) {
        return;
    }
    GfObjAcc acc(GfGameManager::getPartyLeaderDriver());
    if (acc.isBattle()) {
        return;
    }
    if (!GfGameObj::isValidGameObj(acc.getHandle(), false, nullptr)) {
        return;
    }
    if (!GfGameObj::isValidGameObj(GfGameParty::getHandleBlade(GfGameParty::getPartyId(acc.getHandle()), -1), false,
                                   nullptr)) {
        return;
    }
    m_fieldBladeChangeTime = time + info.m_deltaTime;
}

void GfGameScene::updateQuestTaskLog(const fw::UpdateInfo&) {
    QuestID id = GfQuestManager::getProgressCurrentQuest(QTYPE(0));
    if (m_questIdForTaskLog.empty()) {
        if (!id.empty()) {
            m_questIdForTaskLog = id;
        }
        return;
    }
    if (m_questIdForTaskLog == id) {
        return;
    }
    if (GfGameManager::isFadeout() ||
        (GfGameManager::isControlFree() && !GfGameManager::isTalking() && !GfGameManager::isEvent(false)) ||
        GfGameManager::isFullScreenMenu()) {
        m_questIdForTaskLog = id;
    }
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
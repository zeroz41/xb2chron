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
#include "gf/MsgObjectSetHp.h"
#include "classes/gf/GfObjManager.h"
#include "classes/gf/GfObjSetupEnemy.h"
#include "classes/fw/MessageObject.h"
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
#include "gf/GfUtil.h"
#include "fw/Transform.h"
#include "classes/fw/CameraManager.h"
#include "classes/fw/SoundManager.h"
#include "mm/Mat44.h"
#include "classes/fw/EffectManager.h"
#include "effect/SendParam.h"
#include "classes/gf/GfGameEvent.h"
#include "classes/gf/GfGameArena.h"
#include "classes/gf/GfSequentialPlay.h"
#include "classes/gf/GfPlayComQuestCompleteUI.h"
#include "classes/gf/GfPlayComGmkTutorialSeq.h"
#include "gf/QuestListAcc.h"
#include "classes/gf/GfQuestManager.h"
#include "fw/UpdateInfo.h"
#include "btl/Utility.h"
#include "classes/gf/GfLayerPause.h"
#include "classes/gf/GfItemBox.h"
#include "classes/gf/GfGameInsideBattleLock.h"
#include "classes/gf/GfPlayComWaitBattleEnd.h"
#include "gf/GfPouchUtil.h"
#include "classes/gf/SCOM_ACHIEV_INC.h"
#include "gf/MsgObjectDamage.h"
#include "gf/MsgUnk_100003A.h"
#include "gf/GfPlayFactory.h"
#include "classes/gf/GfMountManager.h"
#include "classes/gf/GfBdatItem.h"
#include "classes/gf/GfGameCond.h"
#include "classes/gf/SCOM_POPUP.h"
#include "classes/gf/GfQuestTarget.h"

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

void GfGameScene::BattleAchievement::addDamage(GF_OBJ_HANDLE* handle, const MsgObjectNotifyDamage& msg) {
    switch (GfObjUtil::getObjType(handle)) {
    case 5: {
        unsigned int party = GfObjUtil::getPartyID(msg.m_handle);
        if (party != 0xFFFFFFFF) {
            GF_OBJ_HANDLE* blade = GfGameParty::getHandleBlade(party, -1);
            if (blade != reinterpret_cast<GF_OBJ_HANDLE*>(-1)) {
                SCOM_ACHIEV_INC::createDamageMax(blade, msg.m_damage->m_damage);
            }
        }
        SCOM_ACHIEV_INC::createDamageAdd(msg.m_handle, msg.m_damage->m_damage);
        if (msg.m_damage->m_attackFlags & 2) {
            SCOM_ACHIEV_INC::createCriticalHit(msg.m_handle);
        }
        break;
    }
    case 3:
        SCOM_ACHIEV_INC::createDamageGet(handle, msg.m_damage->m_damage);
        if (msg.m_damage->m_attackFlags & 2) {
            SCOM_ACHIEV_INC::createCriticalGet(handle);
        }
        break;
    default:
        return;
    }
    m_damageCount++;
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

void GfGameScene::setArenaPlayerStop(bool stop) {
    m_gimmickPlayerStop.setPlayerStop(stop);
}

void GfGameScene::setEraseQuestEnemyForEventStart(QuestID quest) {
    mm::mtl::FixedList<GF_OBJ_HANDLE*, 1024>* list = GfGameObj::getList(5);
    for (mm::mtl::FixedList<GF_OBJ_HANDLE*, 1024>::iterator it = list->begin(); it != list->end(); ++it) {
        DataParamAcc acc(*it);
        if (acc.getHp() == 0) {
            if (m_eraseQuestEnemies.size() != m_eraseQuestEnemies.capacity()) {
                m_eraseQuestEnemies.push_back(*it);
            }
        } else if (!quest.empty() && GfQuestTarget::getIconType(*it, quest) != 0) {
            if (m_eraseQuestEnemies.size() != m_eraseQuestEnemies.capacity()) {
                m_eraseQuestEnemies.push_back(*it);
            }
        }
    }
    m_forceBossBattleBgm = true;
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

void GfGameScene::checkFieldBladeChange() {
    if (GfManager::isDestroyNow() || GfGameManager::isBattle() || GfGameManager::isGameOver() ||
        GfGameManager::isPlayerDeadSequence()) {
        return;
    }
    for (unsigned int i = 0; i < 3; i++) {
        GfObjAcc acc(GfGameParty::getHandleDriver(i, 0));
        if (acc.isBattle()) {
            continue;
        }
        DataParamAcc param(acc.getHandle());
        if (param.getHp() == 0) {
            continue;
        }
        int setId = GfSelectBlade::getStartBattleSetId(i);
        if (setId >= 0) {
            DataParamAcc driver(GfGameParty::getHandleDriver(i, 0));
            if (setId != driver.getBladeSet(false)) {
                if (isEnableRideCondition(i)) {
                    GfPlayFactory::createResetBladeForBattleEnd(i, setId, false);
                }
                continue;
            }
        }
        m_partyBattleStartCount[i] = 0;
    }
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

void GfGameScene::createDriverAppendModelControl(GF_OBJ_HANDLE* handle) {
    GfObjAcc acc(handle);
    if (!acc.isValidModel()) {
        return;
    }
    GF_OBJ_HANDLE* owner = GfMountManager::getHandle(handle, static_cast<GFATTACH>(2), static_cast<OPTMNT>(2));
    if (GfObjUtil::getObjType(owner) != 3) {
        return;
    }
#line 1342
    m_appendWires.push_back(new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) GfAppendWire(owner, handle));
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

bool GfGameScene::isFullScreenMenuAfter() const {
    return m_frameCount690 < 30;
}

bool GfGameScene::isNeedResetBladeForBattleEndForBattleEnd() const {
    if (isNeedResetBladeForBattleEndForMenuOpen()) {
        return true;
    }
    for (unsigned int i = 0; i < 3; i++) {
        bool homura;  // Rex (driver 1) with blade 1003
        if (GfGameParty::getDriverBdatId(i, 0) == 1) {
            homura = GfDataDriver::getBlade(1, -1) == 1003;
        } else {
            continue;
        }
        if (homura) {
            return true;
        }
    }
    return false;
}

bool GfGameScene::isBattle() const {
    GfGameScene* scene = get();
    return scene != nullptr && scene->m_battle;
}

bool GfGameScene::isOpenPreciousMenu() const {
    return m_value698 < 2;
}

bool GfGameScene::isResetBladePlay() const {
    return GfPlayComResetBlade::isPlaying(0) || GfPlayComResetBlade::isPlaying(1) || GfPlayComResetBlade::isPlaying(2);
}

void GfGameScene::eventAfterScriptEvent(const char* name) {
    if (strstr(name, "aoc_tut24") != nullptr || strstr(name, "aoc_tut04") != nullptr ||
        strstr(name, "aoc_tut10") != nullptr) {
        m_tutorialPlayerControl = true;
    }
}

void GfGameScene::eventTutorialSequence() {
    if (m_tutorialPlayerControl) {
        m_tutorialPlayerControl = false;
        GfEvent::callPlayerControl(GEV(15));
    }
}

bool GfGameScene::isSepiaFilter() const {
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

void GfGameScene::gevChangeGameDifficult() {
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
        GfGameUtil::execEquipIraDefaultWpnAcce(driver);
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

void GfGameScene::playEventSequenceEnd(unsigned int id) {
    if (id == 30053) {
        GfGameUtil::addTrusuPointByLastKizunaTalk();
    }
    m_playEvent = false;
    if (GfSound* sound = GfSound::get()) {
        sound->setCategoryVolume(m_seCategoryHandles[0], static_cast<fw::SoundCategory>(13), 1.0f, 0.2f);
        sound->setCategoryVolume(m_seCategoryHandles[0], static_cast<fw::SoundCategory>(14), 1.0f, 0.2f);
        sound->setCategoryVolume(m_seCategoryHandles[2], static_cast<fw::SoundCategory>(7), 1.0f, 0.2f);
        sound->setCategoryVolume(m_seCategoryHandles[2], static_cast<fw::SoundCategory>(6), 1.0f, 0.2f);
        sound->setCategoryVolume(m_seCategoryHandles[2], static_cast<fw::SoundCategory>(8), 1.0f, 0.2f);
        sound->setCategoryVolume(m_seCategoryHandles[2], static_cast<fw::SoundCategory>(1), 1.0f, 0.2f);
    }
    if (!GfManager::isExecModeThater()) {
        GfGameUtil::setWatchedEvent(id);
    }
    SCOM_ACHIEV_INC::createKizunaTalk();
    if (GfGameEvent::getPlayEventId() == 21671) {
        m_flag6A1 = false;
    }
    GfGameManager::reqestCraftPopupForIra();
    pad_8BC = 0;
    GfGameManager::setControlMoverPositionForNoPlayer(mm::Vec3::zero);
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
        playEventStartFrame(id);
        break;
    default:
        break;
    }
}

void GfGameScene::createSepiaFilter() {
    fw::EffectManager* manager = fw::EffectManager::get();
    if (manager == nullptr) {
        return;
    }
    if (m_value68C != 0) {
        if (manager->isExist(m_value68C)) {
            return;
        }
        m_value68C = 0;
    }
    GfGameEvent::setColorFilter(true, 5000, 5000, 0.0f);
    unsigned int handle = fw::EffectManager::get()->create("cmn_205_000", nullptr, true);
    m_value68C = handle;
    // the matrix, scale, colour, first range and first flag set again: the original stores them after the matrix
    // copy, where the default constructor's stores would sit before it
    effect::SendParam param;
    param.m_mtx = mm::Mat44::identity;
    param.m_scale.x = 1.0f;
    param.m_scale.y = 1.0f;
    param.m_scale.z = 1.0f;
    param.m_color[0] = 1.0f;
    param.m_color[1] = 1.0f;
    param.m_color[2] = 1.0f;
    param.m_color[3] = 1.0f;
    param.m_rangeA = 1.0f;
    param.m_valueA = 0.0f;
    param.m_flagA = false;
    manager->setViewnum(handle, 0);
    manager->setParam(m_value68C, &param);
}

void GfGameScene::gevOpenMainMenu() {
    if (GfGameManager::isGameTypeIra()) {
        return;
    }
    if (GfDataBlade::fn_7100231884() >= 8003 && GfGameFlag::getLocal(1, 52962) == 0) {
        GfGameFlag::setLocal(1, 52962, 1);
    }
}

void GfGameScene::qevCompleteQuest(const QuestCompleteParam&) {
    m_completeQuest = true;
}

void GfGameScene::updateAppendModel(const fw::UpdateInfo& info) {
    for (mm::mtl::FixedList<GfAppendWire*, 8>::iterator it = m_appendWires.begin(); it != m_appendWires.end(); ++it) {
        (*it)->update(info);
    }
    for (mm::mtl::FixedList<GfAppendWire*, 8>::iterator it = m_appendWires.begin(); it != m_appendWires.end();) {
        GfAppendWire*& wire = *it;
        if (!GfObjUtil::isValid(wire->m_wire)) {
            delete wire;
            it = m_appendWires.erase(it);
        } else {
            ++it;
        }
    }
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

void GfGameScene::updatePartyBattle(const fw::UpdateInfo&) {
    for (unsigned int i = 0; i < 3; i++) {
        GfObjAcc acc(GfGameParty::getHandleDriver(i, 0));
        if (acc.isBattle() && m_partyBattleStartCount[i] < 3) {
            m_partyBattleStartCount[i]++;
            GfGameParty::setupBattleStart(i);
            GfObjUtil::setDisableAutoHeal(acc.getHandle(), false);
        }
    }
}

void GfGameScene::updateHikariLv4Room(const fw::UpdateInfo&) {
    if (GfGameManager::isGameTypeIra()) {
        return;
    }
    m_enableRoomForHikariLv4 = false;
    if (GfGameManager::isMapjump()) {
        return;
    }
    unsigned int party = GfGameParty::getPartyId(3, 1);
    if (party == static_cast<unsigned int>(-1)) {
        return;
    }
    unsigned int blade = 0;
    {
        DataParamAcc acc(GfGameParty::getHandleBlade(party, -1));
        if (acc.isValid()) {
            blade = acc.getBdatId();
        }
    }
    if (blade == 1002 && !GfGameManager::isRoom()) {
        GfObjAcc acc(GfGameParty::getHandleDriver(0, 0));
        mm::Vec3 hit;
        mm::Vec3 from = acc.getWorldTransform().position + mm::Vec3(0.0f, 1.0f, 0.0f);
        if (!util::getUpperHitCollision(hit, from, 100.0f)) {
            m_enableRoomForHikariLv4 = true;
        }
    }
}

void GfGameScene::updateControlFreeEvent(const fw::UpdateInfo&) {
    if (GfManager::isExecModeThater()) {
        return;
    }
    // whether the player has free control (written as a lambda: the original's early returns are threaded into the
    // branches; the helper's name, if it had one, is not known)
    bool controlFree = [] {
        if (GfGameArena::get() != nullptr && GfGameArena::get()->isBusy()) {
            return false;
        }
        if (GfPlayComQuestCompleteUI::s_active > 0) {
            return false;
        }
        if (GfPlayComGmkTutorialSeq::s_activate > 0) {
            return true;
        }
        if (GfGameManager::isBladeChange() && !GfSequentialPlay::isInnerState(static_cast<GF_STATE>(11))) {
            return true;
        }
        return GfGameManager::isControlFree();
    }();
    if (controlFree) {
        if (GfManager::isExecModeAdvertize()) {
            return;
        }
        if (m_controlFreeCount < 10) {
            if (++m_controlFreeCount == 10 && m_controlFreeEvent != 15) {
                m_controlFreeEvent = 15;
                GfEvent::callPlayerControl(GEV(15));
            }
        }
    } else {
        if (m_controlFreeCount > 0) {
            if (--m_controlFreeCount == 0 && m_controlFreeEvent != 16) {
                m_controlFreeEvent = 16;
                GfEvent::callPlayerControl(GEV(16));
            }
        }
    }
}

void GfGameScene::updatePartyObjFlag(const fw::UpdateInfo&) {
    mm::mtl::FixedList<GF_OBJ_HANDLE*, 1024>* list = GfGameObj::getList(3);
    for (mm::mtl::FixedList<GF_OBJ_HANDLE*, 1024>::iterator it = list->begin(); it != list->end(); ++it) {
        GfObjUtil::applyExecUpdate(*it);
    }
    list = GfGameObj::getList(4);
    for (mm::mtl::FixedList<GF_OBJ_HANDLE*, 1024>::iterator it = list->begin(); it != list->end(); ++it) {
        GfObjUtil::applyExecUpdate(*it);
    }
    list = GfGameObj::getList(10);
    for (mm::mtl::FixedList<GF_OBJ_HANDLE*, 1024>::iterator it = list->begin(); it != list->end(); ++it) {
        GfObjUtil::applyExecUpdate(*it);
    }
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

void GfGameScene::updateCrystalPopup(const fw::UpdateInfo&) {
    GfBdatItem* item = GfBdatItem::get();
    if (GfGameFlag::getLocal(1, 54665) == 0) {
        unsigned short condition = item->getCrystalListCondition(45005);
        if (condition != 0 && GfGameCond::isGameCond(condition)) {
            SCOM_POPUP::createCrystalOK(38);
            GfGameFlag::setLocal(1, 54665, 1);
        }
    }
    if (GfGameFlag::getLocal(1, 54666) == 0) {
        unsigned short condition = item->getCrystalListCondition(45006);
        if (condition != 0 && GfGameCond::isGameCond(condition)) {
            SCOM_POPUP::createCrystalOK(40);
            GfGameFlag::setLocal(1, 54666, 1);
        }
    }
    if (GfGameFlag::getLocal(1, 54667) == 0) {
        unsigned short condition = item->getCrystalListCondition(45007);
        if (condition != 0 && GfGameCond::isGameCond(condition)) {
            SCOM_POPUP::createCrystalOK(42);
            GfGameFlag::setLocal(1, 54667, 1);
        }
    }
    if (GfGameFlag::getLocal(1, 54668) == 0) {
        unsigned short condition = item->getCrystalListCondition(45008);
        if (condition != 0 && GfGameCond::isGameCond(condition)) {
            SCOM_POPUP::createCrystalOK(44);
            GfGameFlag::setLocal(1, 54668, 1);
        }
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

namespace _gfgsc {
// an enemy's setup when its info holds one of its own kind (5), as DataParamAcc.cpp's _gfdac::getEnemySetup (inline,
// the name is not the original's)
static inline GfObjSetupEnemy* getEnemySetup(GF_OBJ_HANDLE* handle) {
    GFOBJ_INFO* info = GfObjManager::getObjInfo(handle);
    if (info != nullptr && info->m_setup != nullptr && info->m_setup->m_type == info->m_obj->m_type &&
        info->m_obj->m_type == 5) {
        return mm::mtl::rttiCast<GfObjSetupEnemy>(info->m_setup);
    }
    return nullptr;
}
}  // namespace _gfgsc

void GfGameScene::updateEnemySaveHp(const fw::UpdateInfo&) {
    mm::mtl::FixedList<GF_OBJ_HANDLE*, 1024>* list = GfGameObj::getList(5);
    for (mm::mtl::FixedList<GF_OBJ_HANDLE*, 1024>::iterator it = list->begin(); it != list->end(); ++it) {
        GfObjSetupEnemy* setup = _gfgsc::getEnemySetup(*it);
        if (setup != nullptr && setup->pad_b4 != 0) {
            GfObjAcc acc(*it);
            if (acc.isBattle()) {
                MsgObjectSetHp msg(setup->pad_b4);
                acc.getObj()->sendMessage(acc.getObj(), msg);
                setup->pad_b4 = 0;
            }
        }
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

void GfGameScene::fn_71002CC890(unsigned int driver, const fw::UpdateInfo& info) {
    if (GfGameManager::isEvent(false) || GfGameManager::isTalking() || GfGameManager::isMapjump() ||
        GfGameManager::isStartGame()) {
        return;
    }
    for (unsigned int i = 0; i < 3; i++) {
        GfPouchUtil::updatePouch(driver, i, GfPouchUtil::getPouch(driver, i), info);
    }
}

}  // namespace gf

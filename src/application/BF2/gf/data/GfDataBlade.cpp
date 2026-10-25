#include "gf/GfDataQuest.h"
#include "gf/SDataGame.h"
#include "gf/GfDataAchievement.h"
#include "gf/GfDataBlade.h"
#include "gf/GfDataBladeArts.h"
#include "gf/GfDataBladeCreate.h"
#include "gf/GfDataBladeSkill.h"
#include "gf/GfDataDevelop.h"
#include "gf/GfDataDriver.h"
#include "gf/GfDataDriverArts.h"
#include "gf/GfDataEnBook.h"
#include "gf/GfDataEnemy.h"
#include "gf/GfDataEvent.h"
#include "gf/GfDataHana.h"
#include "gf/GfDataItem.h"
#include "gf/GfDataMap.h"
#include "gf/GfDataMercenaries.h"
#include "gf/GfDataMob.h"
#include "gf/GfDataNanakoori.h"
#include "gf/GfDataParty.h"
#include "gf/GfDataQuest.h"
#include "gf/GfDataUtil.h"
#include "gf/GfDataWeapon.h"
#include "classes/gf/GfBdatBtl.h"
#include "classes/gf/GfBdatChrDr.h"
#include "classes/gf/GfBdatChrEnArrange.h"
#include "classes/gf/GfBdatItem.h"
#include "classes/gf/GfBdatMaplist.h"
#include "classes/gf/GfBdatRsc.h"
#include "gf/SDataGame.h"
#include "classes/gf/GfDataManager.h"
#include "classes/gf/GfGameFlag.h"
#include "ml/MtRand.h"
#include "classes/gf/GfEvent.h"
#include "classes/gf/GfBdatMsg.h"
#include "gf/QuestListAcc.h"
#include "gf/GfDataNpc.h"
#include "gf/GfDataBladeArtsN.h"
#include "gf/GfDataDriverSkill.h"
#include "plugin/Bdat.h"

namespace gf {

const char* GfDataEnemy::getSePack(unsigned int arrange) {
    if (arrange == 0) {
        return nullptr;
    }
    return GfBdatRsc::get()->getRscEnSePack(arrange);
}

unsigned int GfDataEnemy::getBladeID(unsigned int arrange) {
    if (arrange == 0) {
        return 0;
    }
    return GfBdatChrEnArrange::get()->getChrEnArrangeBladeID(arrange);
}

unsigned int GfDataEnemy::getEquipBladeEnArrangeID(unsigned int arrange) {
    if (arrange == 0) {
        return 0;
    }
    return GfBdatChrEnArrange::get()->getChrEnArrangeEnemyBladeID(arrange);
}

bool GfDataEnemy::isNamed(unsigned int arrange) {
    if (GfBdatChrEnArrange* bdat = GfBdatChrEnArrange::get()) {
        return bdat->isChrEnArrangeFlagNamed(arrange);
    }
    return false;
}

bool GfDataEnemy::isBoss(unsigned int arrange) {
    if (GfBdatChrEnArrange* bdat = GfBdatChrEnArrange::get()) {
        return bdat->isChrEnArrangeFlagmBoss(arrange);
    }
    return false;
}

unsigned int GfDataEnemy::getSavedHpType(unsigned int arrange) {
    return GfBdatChrEnArrange::get()->getChrEnArrangeHpOver(arrange);
}

unsigned int GfDataBlade::getRoleByWpnType(unsigned int wpnType) {
    if (wpnType == 0) {
        return 1;
    }
    return GfBdatItem::get()->getPcWpnTypeRole(wpnType);
}

unsigned int GfDataHana::getCondenserNum(unsigned int hana) {
    return GfBdatBtl::get()->getBTL_HanaBaseNCondNum(hana - 1004);
}

unsigned int GfDataDriver::fn_7100241C04(unsigned int driver) {
    return GfBdatChrDr::get()->getChrDrChestHeight(driver);
}

unsigned int GfDataDriver::fn_7100241C1C(unsigned int driver) {
    return GfBdatChrDr::get()->getChrDrLandingHeight(driver);
}

unsigned int GfDataDriver::fn_7100241C34(unsigned int driver) {
    return GfBdatChrDr::get()->getChrDrStill(driver);
}

unsigned int GfDataDriver::getRace(unsigned int driver) {
    return GfBdatChrDr::get()->getChrDrRace(driver);
}

unsigned int GfDataDriver::getFootStep(unsigned int driver) {
    return GfBdatChrDr::get()->getChrDrFootStep(driver);
}

unsigned int GfDataDriver::getFootStepEffect(unsigned int driver) {
    return GfBdatChrDr::get()->getChrDrFootStepEffect(driver);
}

unsigned int GfDataDriver::fn_7100241C94(unsigned int driver) {
    return GfBdatChrDr::get()->getChrDrGender(driver);
}

int GfDataDriver::fn_7100241CAC(unsigned int driver) {
    return GfBdatChrDr::get()->getChrDrOffsetID(driver);
}

const char* GfDataDriver::fn_7100241CC4(unsigned int driver) {
    return GfBdatChrDr::get()->getChrDrCenterBone(driver);
}

const char* GfDataDriver::fn_7100241CDC(unsigned int driver) {
    return GfBdatChrDr::get()->getChrDrCamBone(driver);
}

const char* GfDataDriver::getModelResourceName(unsigned int driver) {
    return GfBdatChrDr::get()->getChrDrModel(driver);
}

const char* GfDataDriver::getMotionResourceName(unsigned int driver) {
    return GfBdatChrDr::get()->getChrDrMotion(driver);
}

const char* GfDataDriver::getDebugName(unsigned int driver) {
    return GfBdatChrDr::get()->getChrDrCom_Eff(driver);
}

unsigned int GfDataDriver::getAiID(unsigned int driver) {
    return GfBdatChrDr::get()->getChrDrAiID(driver);
}

unsigned int GfDataDriver::getExtraMountNpcRsc(unsigned int driver) {
    return GfBdatRsc::get()->getDriverParamExtMountNpc(driver);
}

const char* GfDataDriver::getExtraMountBone(unsigned int driver) {
    return GfBdatRsc::get()->getDriverParamExtMountBone(driver);
}

unsigned int GfDataDriver::getEyeRotControl(unsigned int driver) {
    if (driver == 0) {
        return 0;
    }
    return GfBdatChrDr::get()->getChrDrEyeRot(driver);
}

unsigned int GfDataDriverArts::getLevelCap(unsigned int arts, unsigned int index) {
    return GfBdatBtl::get()->getArtsDrReleaseLv(arts, index);
}

unsigned int GfDataDriverArts::getNameID(unsigned int arts) {
    return GfBdatBtl::get()->getArtsDrName(arts);
}

unsigned short GfDataDriverArts::getIconID(unsigned int arts) {
    return GfBdatBtl::get()->getArtsDrUI(arts);
}

unsigned short GfDataDriverArts::getDebugName(unsigned int arts) {
    return GfBdatBtl::get()->getArtsDrDebugName(arts);
}

unsigned int GfDataDriverArts::getWpnType(unsigned int arts) {
    if (arts == 0) {
        return 0;
    }
    return GfBdatBtl::get()->getArtsDrWpnType(arts);
}

int GfDataDriverArts::getArtsType(unsigned int arts) {
    if (arts == 0) {
        return 0;
    }
    return GfBdatBtl::get()->getArtsDrArtsType(arts);
}

unsigned int GfDataBladeArts::getEnhance(unsigned int arts, unsigned int index) {
    return GfBdatBtl::get()->getArtsBlEnhance(arts, index - 1);
}

unsigned int GfDataBladeSkill::getEnhance(unsigned int skill, unsigned int index) {
    return GfBdatBtl::get()->getBTL_Skill_BlEnhance(skill, index - 1);
}

unsigned int GfDataMob::getRace(unsigned int mob) {
    return GfBdatRsc::get()->getRscMobListRace(mob);
}

const char* GfDataMob::getMotionName(unsigned int mob) {
    return GfBdatRsc::get()->getRscMobListMotion(mob);
}

unsigned int GfDataMob::getFootStep(unsigned int mob) {
    return GfBdatRsc::get()->getRscMobListFootStep(mob);
}

unsigned int GfDataMob::getFootStepEffect(unsigned int mob) {
    return GfBdatRsc::get()->getRscMobListFootStepEffect(mob);
}

const char* GfDataMap::getMapResourceNameByMapID(unsigned int mapId) {
    if (mapId == 0) {
        return nullptr;
    }
    return GfBdatMaplist::get()->getMaplistresource(mapId);
}

unsigned int GfDataMap::getWeatherForceConditionOn(unsigned int mapId, WEATHERID weather) {
    return GfBdatMaplist::get()->getMaplistw_ON_cndID(mapId, weather - 1);
}

unsigned int GfDataMap::getWeatherForceConditionOff(unsigned int mapId, WEATHERID weather) {
    return GfBdatMaplist::get()->getMaplistw_OFF_cndID(mapId, weather - 1);
}

unsigned int GfDataMap::getWeatherTimeBonus(unsigned int mapId, WEATHERID weather) {
    return GfBdatMaplist::get()->getMaplistw_time_BNS(mapId, weather - 1);
}

unsigned int GfDataMap::getWeatherTimeEnd(unsigned int mapId, WEATHERID weather) {
    return GfBdatMaplist::get()->getMaplistw_end_time(mapId, weather - 1);
}

unsigned int GfDataMap::getWeatherPopRate(unsigned int mapId, WEATHERID weather) {
    return GfBdatMaplist::get()->getMaplistw_pop_rate(mapId, weather - 1);
}

const char* GfDataWeapon::getModelName(unsigned int weapon) {
    return GfBdatRsc::get()->getRSC_PcWpnModel(weapon);
}

int GfDataWeapon::getDamage(unsigned int weapon) {
    return GfBdatItem::get()->getPcWpnDamage(weapon);
}

int GfDataWeapon::getGuardRatio(unsigned int weapon) {
    return GfBdatItem::get()->getPcWpnGuardRate(weapon);
}

int GfDataWeapon::getCriticalRatio(unsigned int weapon) {
    return GfBdatItem::get()->getPcWpnCriRate(weapon);
}

int GfDataWeapon::getStability(unsigned int weapon) {
    return GfBdatItem::get()->getPcWpnStability(weapon);
}

unsigned int GfDataWeapon::getEnhance(unsigned int weapon) {
    return GfBdatItem::get()->getPcWpnEnhance1(weapon);
}

unsigned int GfDataWeapon::getAsmWeaponType(unsigned int weapon) {
    if (weapon == 0) {
        return 0;
    }
    return GfBdatItem::get()->getPcWpnTypeMotion(weapon);
}

unsigned int GfDataMercenaries::getPointLimit() {
    return GfBdatBtl::get()->getWildcardDatavalueU2(0x3e);
}

unsigned int GfDataHana::getNartsNum(unsigned int hana) {
    return GfBdatBtl::get()->getBTL_HanaBaseNArtsNum(hana - 1004);
}

unsigned int GfDataHana::getNeedRolePartsEther(unsigned int hana) {
    return GfBdatItem::get()->getITM_HanaRoleNeedEther(hana);
}

unsigned int GfDataHana::getNeedAttributePartsEther(unsigned int hana) {
    return GfBdatItem::get()->getITM_HanaAtrNeedEther(hana);
}

unsigned int GfDataHana::getNeedArtsPartsEther(unsigned int hana) {
    return GfBdatItem::get()->getITM_HanaArtsEnhNeedEther(hana);
}

unsigned int GfDataHana::getNeedNArtsPartsEther(unsigned int hana) {
    return GfBdatItem::get()->getITM_HanaNArtsSetNeedEther(hana);
}

unsigned int GfDataHana::getNeedCondenserPartsEther(unsigned int hana) {
    return GfBdatItem::get()->getITM_HanaAssistNeedEther(hana);
}

unsigned int GfDataHana::getDefaultRoleParts(unsigned int hana) {
    return GfBdatBtl::get()->getBTL_HanaChipsetRoleParts(hana - 1004);
}

unsigned int GfDataHana::getDefaultAttributeParts(unsigned int hana) {
    return GfBdatBtl::get()->getBTL_HanaChipsetAtrParts(hana - 1004);
}

unsigned int GfDataHana::getDefaultNArtsParts(unsigned int hana, unsigned int index) {
    return GfBdatBtl::get()->getBTL_HanaChipsetNArtsParts(hana - 1004, index);
}

unsigned int GfDataHana::getDefaultCondenserParts(unsigned int hana, unsigned int index) {
    return GfBdatBtl::get()->getBTL_HanaChipsetNCondParts(hana - 1004, index);
}

unsigned int GfDataHana::getOpenCircuitEther(unsigned int hana, unsigned int index) {
    return GfBdatBtl::get()->getBTL_HanaBaseCircuitNum(hana - 1004, index);
}

unsigned int GfDataEnBook::getEnBoolId(unsigned int arrange) {
    if (arrange == 0) {
        return 0;
    }
    return GfBdatChrEnArrange::get()->getChrEnArrangeBookID(arrange);
}

void GfDataUtil::setScenarioFlag(unsigned short flag) {
    GfGameFlag::setLocal(16, 1, flag);
}

void GfDataUtil::setRandomInn() {
    GfGameFlag::setLocal(4, 516, ml::mtRand(16));
}

void GfDataBlade::setHomuriNameHikari(bool hikari) {
    GfGameFlag::setLocal(1, 35323, hikari);
}

int GfDataDevelop::getPoint(unsigned int zone) {
    return GfGameFlag::getLocal(16, zone + 5);
}

void GfDataDevelop::setPoint(unsigned int zone, unsigned int point) {
    if (point > 0xFFFF) {
        point = 0xFFFF;
    }
    GfGameFlag::setLocal(16, zone + 5, point);
}

int GfDataDevelop::getLevel(unsigned int zone) {
    if (zone == 0 || zone > 8) {
        return 0;
    }
    return GfGameFlag::getLocal(4, zone + 635);
}

void GfDataDevelop::setLevel(unsigned int zone, unsigned int level) {
    unsigned int value = level > 5 ? 5 : level;
    if (level == 0) {
        value = 1;
    }
    GfGameFlag::setLocal(4, zone + 635, value);
}

bool GfDataMap::isMapCompleteFlag(unsigned int mapId) {
    return GfGameFlag::getLocal(1, mapId + 13266) != 0;
}

void GfDataMap::setMapCompleteFlag(unsigned int mapId) {
    GfGameFlag::setLocal(1, mapId + 13266, 1);
}

int GfDataMercenaries::getLevel() {
    return GfGameFlag::getLocal(4, 2);
}

void GfDataMercenaries::setLevel(unsigned int level) {
    GfGameFlag::setLocal(4, 2, level);
}

int GfDataMercenaries::getPoint() {
    return GfGameFlag::getLocal(16, 3);
}

void GfDataMercenaries::setPoint(unsigned int point) {
    GfGameFlag::setLocal(16, 3, point);
}

unsigned int GfDataMercenaries::getMissionFlag(unsigned int mission) {
    if (mission == 0) {
        return 0;
    }
    return GfGameFlag::getLocal(4, mission + 5);
}

bool GfDataMercenaries::isMissionCompleteFlag(unsigned int mission) {
    return GfGameFlag::getLocal(1, mission + 46285) != 0;
}

void GfDataMercenaries::setMissionCompleteFlag(unsigned int mission) {
    GfGameFlag::setLocal(1, mission + 46285, 1);
}

bool GfDataMercenaries::isMissionComplete(unsigned int mission) {
    if (mission == 0) {
        return false;
    }
    return GfGameFlag::getLocal(4, mission + 5) == 4;
}

bool GfDataMercenaries::isNewMission(unsigned int mission) {
    return GfGameFlag::getLocal(1, mission + 39575) == 0;
}

void GfDataMercenaries::clearNewMission(unsigned int mission) {
    GfGameFlag::setLocal(1, mission + 39575, 1);
}

unsigned int GfDataNanakoori::getVocalLevel() {
    return GfGameFlag::getLocal(8, 2127);
}

unsigned int GfDataNanakoori::getVisualLevel() {
    return GfGameFlag::getLocal(8, 2128);
}

unsigned int GfDataNanakoori::getSoulLevel() {
    return GfGameFlag::getLocal(8, 2129);
}

int GfDataUtil::getMoney() {
    return GfDataManager::getDataGame()->m_money;
}

void GfDataUtil::setMoney(unsigned int value) {
    SDataGame* game = GfDataManager::getDataGame();
    game->m_money = value < 999999999 ? value : 999999999;
}

unsigned int GfDataUtil::getEventChapterSave() {
    return GfDataManager::getDataGame()->m_eventChapterSave;
}

QuestID GfDataQuest::getScenario() {
    return GfDataManager::getDataGame()->m_scenario;
}

QuestID GfDataQuest::getSelect() {
    return GfDataManager::getDataGame()->m_select;
}

unsigned int GfDataUtil::getSkipTravelID() {
    return GfDataManager::getDataGame()->m_skipTravelID;
}

unsigned int GfDataMercenaries::getTeamNum() {
    return GfDataManager::getDataGame()->m_teams.size();
}

float GfDataUtil::getPlayerCameraDistance() {
    return GfDataManager::getDataGame()->m_playerCameraDistance;
}

void GfDataUtil::setPlayerCameraDistance(float value) {
    GfDataManager::getDataGame()->m_playerCameraDistance = value;
}

int GfDataHana::getEther() {
    return GfDataManager::getDataGame()->m_ether;
}

void GfDataHana::setEther(unsigned int value) {
    GfDataManager::getDataGame()->m_ether = value;
}

unsigned int GfDataBladeCreate::getAssurePoint() {
    return GfDataManager::getDataGame()->m_assurePoint;
}

void GfDataBladeCreate::resetAssurePoint() {
    GfDataManager::getDataGame()->m_assurePoint = 0;
}

unsigned int GfDataBladeCreate::getAssureCount() {
    return GfDataManager::getDataGame()->m_assureCount;
}

void GfDataBladeCreate::resetAssureCount() {
    GfDataManager::getDataGame()->m_assureCount = 0;
}

unsigned int GfDataBladeCreate::getRareBladeAppearType() {
    return GfDataManager::getDataGame()->m_rareBladeAppearType;
}

void GfDataBladeCreate::setRareBladeAppearType(unsigned int value) {
    GfDataManager::getDataGame()->m_rareBladeAppearType = static_cast<unsigned char>(value);
}

unsigned int GfDataUtil::getCoin() {
    return GfDataManager::getDataGame()->m_coin;
}

void GfDataUtil::setCoin(unsigned int value) {
    SDataGame* game = GfDataManager::getDataGame();
    game->m_coin = value < 9999 ? value : 9999;
}

float GfDataUtil::getCameraHeight() {
    return GfDataManager::getDataGame()->m_cameraHeight;
}

void GfDataUtil::setCameraHeight(float value) {
    GfDataManager::getDataGame()->m_cameraHeight = value;
}

float GfDataUtil::getCameraYaw() {
    return GfDataManager::getDataGame()->m_cameraYaw;
}

void GfDataUtil::setCameraYaw(float value) {
    GfDataManager::getDataGame()->m_cameraYaw = value;
}

float GfDataUtil::getCameraPitch() {
    return GfDataManager::getDataGame()->m_cameraPitch;
}

void GfDataUtil::setCameraPitch(float value) {
    GfDataManager::getDataGame()->m_cameraPitch = value;
}

bool GfDataUtil::isCameraFreeMode() {
    return GfDataManager::getDataGame()->m_cameraFreeMode != 0;
}

void GfDataUtil::setCameraFreeMode(bool value) {
    SDataGame* game = GfDataManager::getDataGame();
    game->m_cameraFreeMode = value;
}

bool GfDataBlade::isHikariCurrent() {
    return GfDataManager::getDataGame()->m_hikariCurrent != 0;
}

void GfDataBlade::setHikariCurrent(bool value) {
    SDataGame* game = GfDataManager::getDataGame();
    game->m_hikariCurrent = value;
}

unsigned int GfDataUtil::getAutoEventAfterLoad() {
    return GfDataManager::getDataGame()->m_autoEventAfterLoad;
}

bool GfDataUtil::isCollectFlagNewVersion() {
    return GfDataManager::getDataGame()->m_collectFlagNewVersion != 0;
}

unsigned char GfDataUtil::getCameraSide() {
    return GfDataManager::getDataGame()->m_cameraSide;
}

void GfDataUtil::setCameraSide(unsigned char value) {
    GfDataManager::getDataGame()->m_cameraSide = value;
}

unsigned int GfDataBlade::getStartCommonBlade() {
    return 1197;
}

unsigned int GfDataBlade::getEndCommonBlade() {
    return 1401;
}

unsigned int GfDataBlade::getStartUiCommonBlade() {
    return 1397;
}

bool GfDataBlade::isCommonBlade(unsigned int blade) {
    return blade >= 1197 && blade < 1423;
}

bool GfDataBlade::isRegularBlade(unsigned int blade) {
    return blade >= 1001 && blade < 1014;
}

bool GfDataBlade::isValid(unsigned int blade) {
    return blade >= 1001 && blade < 1423;
}

bool GfDataBlade::isBladeID(unsigned int blade) {
    return blade >= 1001 && blade < 1423;
}

bool GfDataBlade::isNeedChangeWeapon(unsigned int blade) {
    return (blade >= 1043 && blade < 1051) || blade == 1039;
}

unsigned int GfDataBlade::getActBlade2CommonBlade(unsigned int blade) {
    if (blade < 1051 || blade > 1072) {
        return blade;
    }
    return blade + 350;
}

bool GfDataHana::isValid(unsigned int blade) {
    return blade >= 1005 && blade < 1008;
}

bool GfDataDriver::isDriver(unsigned int driver) {
    return driver >= 1 && driver < 26;
}

bool GfDataDriver::isDummyDriver(unsigned int driver) {
    return false;
}

unsigned int GfDataDriver::getDebugAppendDeathBlowEfbFileIdx(unsigned int index) {
    return index + 2183;
}

unsigned int GfDataDriver::getDebugAppendDeathBlowEabFileIdx(unsigned int index) {
    return index + 1182;
}

unsigned int GfDataDriver::getWeaponEfbFileIdx(int index) {
    return (index < 0 ? 0 : index) + 1277;
}

unsigned int GfDataDriver::getWeaponEabFileIdx(int index) {
    return (index < 0 ? 0 : index) + 276;
}

unsigned int GfDataDriver::getWeaponSwtFileIdx(int index) {
    return (index < 0 ? 0 : index) + 175;
}

unsigned int GfDataDriver::getWeaponAnmFileIdx(int index) {
    return (index < 0 ? 0 : index) + 74;
}

bool GfDataItem::isFavoriteCategoryFood(unsigned int category) {
    return category >= 12 && category < 18;
}

bool GfDataItem::isMayItem(unsigned int item) {
    return item >= 40307 && item < 40312;
}

bool GfDataItem::isTukiItem(unsigned int item) {
    return item >= 40290 && item < 40295;
}

bool GfDataEvent::isBladeCreateEvent(unsigned int event) {
    return event >= 19001 && event < 19062;
}

unsigned int GfDataMercenaries::getLevelMax() {
    return 5;
}

unsigned int GfDataNanakoori::getItemForVocalLevelUp() {
    return 25175;
}

unsigned int GfDataNanakoori::getItemForVisualLevelUp() {
    return 25176;
}

unsigned int GfDataNanakoori::getItemForSoulLevelUp() {
    return 25177;
}

void GfDataUtil::convertNewCollectFlagPatch() {
}

bool GfDataMob::getName(unsigned char*& bdat, unsigned int& id, unsigned int mob) {
    return false;
}

bool GfDataParty::isRideChar(unsigned int chara) {
    return chara == 2 || chara == 1004;
}

bool GfDataAchievement::isWaitControllFreeStats(unsigned int stats) {
    switch (stats) {
    case 34:
    case 35:
    case 37:
        return true;
    }
    return false;
}



unsigned int GfDataBlade::getBladeWpnType(unsigned int blade) {
    if (blade == 0) {
        return 0;
    }
    SDataBlade& data = GfDataManager::getDataGame()->m_blades[getBladeIndex(blade)];
    return data.m_weaponType;
}

bool GfDataBlade::isEnableEngageRex(unsigned int blade) {
    SDataBlade& data = GfDataManager::getDataGame()->m_blades[getBladeIndex(blade)];
    return data.m_enableEngageRex != 0;
}

unsigned int GfDataBlade::getBornTime(unsigned int blade) {
    if (blade == 0) {
        return 0;
    }
    SDataBlade& data = GfDataManager::getDataGame()->m_blades[getBladeIndex(blade)];
    return data.m_bornTime;
}

SDataIdea* GfDataBlade::getSDataIdea(unsigned int blade) {
    SDataBlade& data = GfDataManager::getDataGame()->m_blades[getBladeIndex(blade)];
    return &data.m_idea;
}

bool GfDataBlade::isAttachedParty(unsigned int blade) {
    SDataBlade& data = GfDataManager::getDataGame()->m_blades[getBladeIndex(blade)];
    return data.m_attachedParty != 0;
}

bool GfDataBlade::isUnselect(unsigned int blade) {
    SDataBlade& data = GfDataManager::getDataGame()->m_blades[getBladeIndex(blade)];
    return data.m_unselect != 0;
}

bool GfDataBlade::isActivateDriver(unsigned int blade) {
    SDataBlade& data = GfDataManager::getDataGame()->m_blades[getBladeIndex(blade)];
    return data.m_setDriver != 0;
}

unsigned int GfDataBlade::getSetDriver(unsigned int blade) {
    if (blade == 0) {
        return 0;
    }
    SDataBlade& data = GfDataManager::getDataGame()->m_blades[getBladeIndex(blade)];
    return data.m_setDriver;
}

bool GfDataBlade::isActivateUnuse(unsigned int blade) {
    if (blade == 0) {
        return true;
    }
    SDataBlade& data = GfDataManager::getDataGame()->m_blades[getBladeIndex(blade)];
    return data.m_dataType == 0;
}

const char* GfDataBlade::getResourceNameModel(unsigned int blade) {
    SDataBlade& data = GfDataManager::getDataGame()->m_blades[getBladeIndex(blade)];
    return data.m_modelName;
}

bool GfDataBlade::isKizunaringComplete(unsigned int blade) {
    SDataBlade& data = GfDataManager::getDataGame()->m_blades[getBladeIndex(blade)];
    return data.m_kizunaringComplete == 1;
}

bool GfDataBlade::isReleasedRareBlade(unsigned int blade) {
    SDataBlade& data = GfDataManager::getDataGame()->m_blades[getBladeIndex(blade)];
    return data.m_attachedParty == 2;
}

unsigned int GfDataBlade::getTrustRank(unsigned int blade) {
    SDataBlade& data = GfDataManager::getDataGame()->m_blades[getBladeIndex(blade)];
    return data.m_trustRank;
}

unsigned int GfDataBlade::getKeyReleaseLevel(unsigned int blade) {
    SDataBlade& data = GfDataManager::getDataGame()->m_blades[getBladeIndex(blade)];
    return data.m_keyLevel;
}

bool GfDataBlade::isSetBlade(unsigned int blade) {
    SDataBlade& data = GfDataManager::getDataGame()->m_blades[getBladeIndex(blade)];
    return data.m_setDriver != 0;
}

unsigned int GfDataBlade::getBladeWeapon(unsigned int blade) {
    if (blade == 0) {
        return 0;
    }
    SDataBlade& data = GfDataManager::getDataGame()->m_blades[getBladeIndex(blade)];
    return data.m_equipWeapon;
}

const char* GfDataBlade::getResourceNameMotion(unsigned int blade) {
    SDataBlade& data = GfDataManager::getDataGame()->m_blades[getBladeIndex(blade)];
    return data.m_motionName;
}

const char* GfDataBlade::getResourceNameAddMotion(unsigned int blade) {
    SDataBlade& data = GfDataManager::getDataGame()->m_blades[getBladeIndex(blade)];
    return data.m_addMotionName;
}

unsigned int GfDataBlade::getRace(unsigned int blade) {
    if (blade == 0) {
        return 0;
    }
    SDataBlade& data = GfDataManager::getDataGame()->m_blades[getBladeIndex(blade)];
    return data.m_race;
}

unsigned int GfDataBlade::getQuestRace(unsigned int blade) {
    if (blade == 0) {
        return 1;
    }
    SDataBlade& data = GfDataManager::getDataGame()->m_blades[getBladeIndex(blade)];
    return data.m_questRace;
}

bool GfDataBlade::isAnimal(unsigned int blade) {
    if (blade == 0) {
        return false;
    }
    SDataBlade& data = GfDataManager::getDataGame()->m_blades[getBladeIndex(blade)];
    return data.m_questRace == 2;
}

float GfDataBlade::getWpnScale(unsigned int blade) {
    if (blade == 0) {
        return 1.0f;
    }
    SDataBlade& data = GfDataManager::getDataGame()->m_blades[getBladeIndex(blade)];
    return data.m_wpnScale * 0.01f;
}

float GfDataBlade::getScale(unsigned int blade) {
    if (blade == 0) {
        return 1.0f;
    }
    SDataBlade& data = GfDataManager::getDataGame()->m_blades[getBladeIndex(blade)];
    return data.m_scale * 0.01f;
}

int GfDataBlade::getOffsetID(unsigned int blade) {
    if (blade == 0) {
        return 0;
    }
    SDataBlade& data = GfDataManager::getDataGame()->m_blades[getBladeIndex(blade)];
    return data.m_offsetId;
}

unsigned int GfDataBlade::getSize(unsigned int blade) {
    if (blade == 0) {
        return 0;
    }
    SDataBlade& data = GfDataManager::getDataGame()->m_blades[getBladeIndex(blade)];
    return data.m_size;
}

unsigned int GfDataBlade::getEquipOrbMax(unsigned int blade) {
    if (blade == 0) {
        return 0;
    }
    SDataBlade& data = GfDataManager::getDataGame()->m_blades[getBladeIndex(blade)];
    return data.m_equipOrbMax;
}

unsigned int GfDataBlade::getCreateEvent(unsigned int blade) {
    SDataBlade& data = GfDataManager::getDataGame()->m_blades[getBladeIndex(blade)];
    return data.m_createEvent;
}

unsigned int GfDataBlade::getNormalTalk(unsigned int blade) {
    SDataBlade& data = GfDataManager::getDataGame()->m_blades[getBladeIndex(blade)];
    return data.m_normalTalk;
}

unsigned int GfDataBlade::getTrustPoint(unsigned int blade) {
    SDataBlade& data = GfDataManager::getDataGame()->m_blades[getBladeIndex(blade)];
    return data.m_trustPoint;
}

unsigned int GfDataBlade::getFootStep(unsigned int blade) {
    SDataBlade& data = GfDataManager::getDataGame()->m_blades[getBladeIndex(blade)];
    return data.m_footStep;
}

unsigned int GfDataBlade::getFootStepEffect(unsigned int blade) {
    SDataBlade& data = GfDataManager::getDataGame()->m_blades[getBladeIndex(blade)];
    return data.m_footStepEffect;
}

bool GfDataBlade::isReleaseLock(unsigned int blade) {
    SDataBlade& data = GfDataManager::getDataGame()->m_blades[getBladeIndex(blade)];
    return data.m_releaseLock != 0;
}

const char* GfDataBlade::getVoiceStr(unsigned int blade) {
    SDataBlade& data = GfDataManager::getDataGame()->m_blades[getBladeIndex(blade)];
    return data.m_voiceStr;
}

const char* GfDataBlade::getSePack(unsigned int blade) {
    SDataBlade& data = GfDataManager::getDataGame()->m_blades[getBladeIndex(blade)];
    return data.m_seName;
}

void GfDataBlade::setKizunaringComplete(unsigned int blade) {
    GfDataManager::getDataGame()->m_blades[getBladeIndex(blade)].m_kizunaringComplete = 1;
}

bool GfDataBlade::setActivateMercenaryTeam(unsigned int blade) {
    GfDataManager::getDataGame()->m_blades[getBladeIndex(blade)].m_dataType = 2;
    return true;
}

void GfDataBlade::setBladeWeapon(unsigned int blade, unsigned int weapon) {
    if (blade != 0) {
        GfDataManager::getDataGame()->m_blades[getBladeIndex(blade)].m_equipWeapon = weapon;
    }
}

void GfDataBlade::setTrustPoint(unsigned int blade, unsigned int point) {
    GfDataManager::getDataGame()->m_blades[getBladeIndex(blade)].m_trustPoint = point;
    GfEvent::callDebugChangeIdea(4, blade, 0, 0);
}


unsigned int GfDataMercenaries::getFieldSkill(unsigned int mission, unsigned int slot) {
    switch (slot) {
    case 0:
        return getFieldSkill1(mission);
    case 1:
        return getFieldSkill2(mission);
    case 2:
        return getFieldSkill3(mission);
    }
    return 0;
}

unsigned int GfDataMercenaries::getStartMissionID() {
    return QuestListAcc::get()->getFLD_MercenariesMissionStart();
}

QuestID GfDataMercenaries::getMissionQuestID(unsigned int mission) {
    return QuestID(QuestListAcc::get()->getFLD_MercenariesMissionQuestID(mission));
}

bool GfDataMercenaries::isOrderOnlyOne(unsigned int mission) {
    return QuestListAcc::get()->getFLD_MercenariesMissionRepeatable(mission) == 0;
}

unsigned int GfDataMercenaries::getMissionTime(unsigned int mission) {
    return QuestListAcc::get()->getFLD_MercenariesMissionRequestPerformance(mission);
}

GfDataMercenaries::Team* GfDataMercenaries::getTeamByTeamID(unsigned int teamId) {
    SDataGame* game = GfDataManager::getDataGame();
    for (Team* team = game->m_teams.begin(); team != game->m_teams.end(); ++team) {
        if (team->m_teamId == teamId) {
            return team;
        }
    }
    return nullptr;
}

bool GfDataMercenaries::isValidTeamID(unsigned int teamId) {
    return getTeamByTeamID(teamId) != nullptr;
}

GfDataMercenaries::Team* GfDataMercenaries::getTeamByIndex(unsigned int index) {
    return &GfDataManager::getDataGame()->m_teams[index];
}

GfDataMercenaries::Team* GfDataMercenaries::getTeamByMissionID(unsigned int mission) {
    if (mission == 0) {
        return nullptr;
    }
    SDataGame* game = GfDataManager::getDataGame();
    for (Team* team = game->m_teams.begin(); team != game->m_teams.end(); ++team) {
        if (team->m_mission == mission) {
            return team;
        }
    }
    return nullptr;
}

unsigned int GfDataMercenaries::getTeamIDByMissionID(unsigned int mission) {
    if (mission == 0) {
        return 0;
    }
    Team* team = getTeamByMissionID(mission);
    if (team == nullptr) {
        return 0;
    }
    return team->m_teamId;
}

unsigned short* GfDataMercenaries::getTeamMember(unsigned int teamId) {
    Team* team = getTeamByTeamID(teamId);
    if (team == nullptr) {
        return nullptr;
    }
    return team->m_members;
}

unsigned int GfDataMercenaries::getTeamMission(unsigned int teamId) {
    Team* team = getTeamByTeamID(teamId);
    if (team == nullptr) {
        return 0;
    }
    return team->m_mission;
}

ElapseTime GfDataMercenaries::getTeamMissionTime(unsigned int teamId) {
    Team* team = getTeamByTeamID(teamId);
    if (team == nullptr) {
        ElapseTime none = {0, 0, 0};
        return none;
    }
    return team->m_missionTime;
}

bool GfDataMercenaries::isTeamStateEmpty(unsigned int teamId) {
    Team* team = getTeamByTeamID(teamId);
    if (team == nullptr) {
        return true;
    }
    return team->m_mission == 0;
}

bool GfDataMercenaries::isTeamStateExpedition(unsigned int teamId) {
    Team* team = getTeamByTeamID(teamId);
    if (team == nullptr || team->m_mission == 0) {
        return false;
    }
    return GfGameFlag::getLocal(4, team->m_mission + 5) == 2;
}

unsigned int GfDataMercenaries::getTeamLeader(unsigned int teamId) {
    if (teamId == 0) {
        return 0;
    }
    Team* team = getTeamByTeamID(teamId);
    if (team == nullptr) {
        return 0;
    }
    return team->m_members[0];
}

bool GfDataMercenaries::isTeamStateReward(unsigned int teamId) {
    Team* team = getTeamByTeamID(teamId);
    if (team == nullptr || team->m_mission == 0) {
        return false;
    }
    return GfGameFlag::getLocal(4, team->m_mission + 5) == 3;
}

unsigned int GfDataMercenaries::getTeamID(unsigned int blade) {
    SDataGame* game = GfDataManager::getDataGame();
    for (Team* team = game->m_teams.begin(); team != game->m_teams.end(); ++team) {
        for (int i = 0; i < 6; i++) {
            if (team->m_members[i] == blade) {
                return team->m_teamId;
            }
        }
    }
    return 0;
}

bool GfDataEnemy::getName(unsigned char*& bdat, unsigned int& id, unsigned int row) {
    id = GfBdatChrEnArrange::get()->getChrEnArrangeName(row);
    bdat = GfBdatMsg::getFpEnemy();
    return id != 0;
}

bool GfDataBladeArts::getName(unsigned char*& bdat, unsigned int& id, unsigned int row) {
    id = GfBdatBtl::get()->getArtsBlName(row);
    bdat = GfBdatMsg::getFpBlArtsMs();
    return id != 0;
}

bool GfDataBladeSkill::getName(unsigned char*& bdat, unsigned int& id, unsigned int row) {
    id = GfBdatBtl::get()->getBTL_Skill_BlName(row);
    bdat = GfBdatMsg::getFpBlSkill();
    return id != 0;
}

bool GfDataDriver::getName(unsigned char*& bdat, unsigned int& id, unsigned int row) {
    id = GfBdatChrDr::get()->getChrDrName(row);
    bdat = GfBdatMsg::getFpChrDr();
    return id != 0;
}

bool GfDataBladeArts::getCaption(unsigned char*& bdat, unsigned int& id, unsigned int row) {
    id = GfBdatBtl::get()->getArtsBlCaption(row);
    bdat = GfBdatMsg::getFpBlArtsMs();
    return id != 0;
}

bool GfDataBladeArts::getExName(unsigned char*& bdat, unsigned int& id, unsigned int row) {
    id = GfBdatBtl::get()->getArtsBlSpName(row);
    bdat = GfBdatMsg::getFpBlSpArtsMs();
    return id != 0;
}

bool GfDataBladeArts::getExCaption(unsigned char*& bdat, unsigned int& id, unsigned int row) {
    id = GfBdatBtl::get()->getArtsBlSpCaption(row);
    bdat = GfBdatMsg::getFpBlSpArtsMs();
    return id != 0;
}

bool GfDataBladeArtsN::getName(unsigned char*& bdat, unsigned int& id, unsigned int row) {
    id = GfBdatBtl::get()->getBTL_BuffName(row);
    bdat = GfBdatMsg::getFpBlBuffMs();
    return id != 0;
}

bool GfDataBladeArtsN::getCaption(unsigned char*& bdat, unsigned int& id, unsigned int row) {
    id = GfBdatBtl::get()->getBTL_BuffCaption(row);
    bdat = GfBdatMsg::getFpBlBuffCap();
    return id != 0;
}

bool GfDataDriverSkill::getName(unsigned char*& bdat, unsigned int& id, unsigned int row) {
    id = GfBdatBtl::get()->getBTL_Skill_DrName(row);
    bdat = GfBdatMsg::getFpBtlSkillDr();
    return id != 0;
}

bool GfDataWeapon::getWeaponTypeName(unsigned char*& bdat, unsigned int& id, unsigned int row) {
    id = GfBdatItem::get()->getPcWpnTypeName(row);
    bdat = GfBdatMsg::getFpPcWpnType();
    return id != 0;
}

const char* GfDataNpc::getName(unsigned int npc) {
    unsigned char* bdat;
    unsigned int id;
    if (getName(bdat, id, npc)) {
        return Bdat::getMSText(bdat, id);
    }
    return nullptr;
}

const char* GfDataItem::getName(unsigned int item) {
    unsigned char* bdat;
    unsigned int id;
    const char* name = getName(bdat, id, item) ? Bdat::getMSText(bdat, id) : nullptr;
    return name == nullptr ? "" : name;
}

const char* GfDataEnemy::getName(unsigned int arrange) {
    unsigned char* bdat;
    unsigned int id;
    const char* name = getName(bdat, id, arrange) ? Bdat::getMSText(bdat, id) : nullptr;
    return name == nullptr ? "" : name;
}

const char* GfDataDriver::getName(unsigned int driver) {
    unsigned char* bdat;
    unsigned int id;
    if (getName(bdat, id, driver)) {
        return Bdat::getMSText(bdat, id);
    }
    return nullptr;
}

const char* GfDataBladeSkill::getName(unsigned int skill) {
    unsigned char* bdat;
    unsigned int id;
    const char* name = getName(bdat, id, skill) ? Bdat::getMSText(bdat, id) : nullptr;
    return name == nullptr ? "" : name;
}

unsigned int GfDataNpc::getRace(unsigned int npc) {
    if (npc <= 25) {
        return GfBdatChrDr::get()->getChrDrRace(npc);
    }
    if (npc <= 2000) {
        SDataBlade& data = GfDataManager::getDataGame()->m_blades[GfDataBlade::getBladeIndex(npc)];
        return data.m_race;
    }
    return GfBdatRsc::get()->getRscNpcListRace(npc);
}

unsigned int GfDataNpc::getGender(unsigned int npc) {
    if (npc <= 25) {
        return GfBdatChrDr::get()->getChrDrGender(npc);
    }
    if (npc <= 2000) {
        SDataBlade& data = GfDataManager::getDataGame()->m_blades[GfDataBlade::getBladeIndex(npc)];
        return data.m_gender;
    }
    return GfBdatRsc::get()->getRscNpcListGender(npc);
}

const char* GfDataNpc::getModelName(unsigned int npc) {
    if (npc <= 25) {
        return GfBdatChrDr::get()->getChrDrModel(npc);
    }
    if (npc <= 2000) {
        SDataBlade& data = GfDataManager::getDataGame()->m_blades[GfDataBlade::getBladeIndex(npc)];
        return data.m_modelName;
    }
    return GfBdatRsc::get()->getRscNpcListModel(npc);
}

const char* GfDataNpc::getMotionName(unsigned int npc) {
    if (npc <= 25) {
        return GfBdatChrDr::get()->getChrDrMotion(npc);
    }
    if (npc <= 2000) {
        SDataBlade& data = GfDataManager::getDataGame()->m_blades[GfDataBlade::getBladeIndex(npc)];
        return data.m_motionName;
    }
    return GfBdatRsc::get()->getRscNpcListMotion(npc);
}

unsigned int GfDataNpc::getCollisionId(unsigned int npc) {
    if (npc <= 25) {
        return GfBdatChrDr::get()->getChrDrCollisionId(npc);
    }
    if (npc <= 2000) {
        SDataBlade& data = GfDataManager::getDataGame()->m_blades[GfDataBlade::getBladeIndex(npc)];
        return data.m_collisionId;
    }
    return GfBdatRsc::get()->getRscNpcListCollisionId(npc);
}

int GfDataNpc::getOffsetID(unsigned int npc) {
    if (npc <= 25) {
        return GfBdatChrDr::get()->getChrDrOffsetID(npc);
    }
    if (npc <= 2000) {
        SDataBlade& data = GfDataManager::getDataGame()->m_blades[GfDataBlade::getBladeIndex(npc)];
        return data.m_offsetId;
    }
    return GfBdatRsc::get()->getRscNpcListOffsetID(npc);
}

unsigned int GfDataNpc::getFootStep(unsigned int npc) {
    if (npc <= 1000) {
        return GfBdatChrDr::get()->getChrDrFootStep(npc);
    }
    if (npc <= 2000) {
        SDataBlade& data = GfDataManager::getDataGame()->m_blades[GfDataBlade::getBladeIndex(npc)];
        return data.m_footStep;
    }
    return GfBdatRsc::get()->getRscNpcListFootStep(npc);
}

unsigned int GfDataNpc::getFootStepEffect(unsigned int npc) {
    if (npc <= 1000) {
        return GfBdatChrDr::get()->getChrDrFootStepEffect(npc);
    }
    if (npc <= 2000) {
        SDataBlade& data = GfDataManager::getDataGame()->m_blades[GfDataBlade::getBladeIndex(npc)];
        return data.m_footStepEffect;
    }
    return GfBdatRsc::get()->getRscNpcListFootStepEffect(npc);
}

unsigned int GfDataNpc::getEyeRotControl(unsigned int npc) {
    if (npc <= 1000) {
        if (npc == 0) {
            return 0;
        }
        return GfBdatChrDr::get()->getChrDrEyeRot(npc);
    }
    if (npc <= 2000) {
        SDataBlade& data = GfDataManager::getDataGame()->m_blades[GfDataBlade::getBladeIndex(npc)];
        return data.m_eyeRotControl;
    }
    return GfBdatRsc::get()->getRscNpcListEyeRot(npc);
}

float GfDataNpc::getScale(unsigned int npc) {
    if (npc < 26) {
        return 1.0f;
    }
    if (npc <= 2000) {
        SDataBlade& data = GfDataManager::getDataGame()->m_blades[GfDataBlade::getBladeIndex(npc)];
        return data.m_scale * 0.01f;
    }
    return GfBdatRsc::get()->getRscNpcListScale(npc) / 100.0f;
}

bool GfDataNpc::getExtraParts(unsigned int npc, unsigned int part) {
    if (npc < 26) {
        return true;
    }
    if (npc <= 2000) {
        SDataBlade& data = GfDataManager::getDataGame()->m_blades[GfDataBlade::getBladeIndex(npc)];
        return data.m_extraParts[part] != 0;
    }
    return GfBdatRsc::get()->getRscNpcListExtraParts(npc, part) != 0;
}

const char* GfDataNpc::getAddMotionName(unsigned int npc) {
    if (npc > 2000) {
        const char* name = GfBdatRsc::get()->getRscNpcListAddMotion(npc);
        if (name != nullptr && name[0] != '\0') {
            return name;
        }
    }
    return nullptr;
}

const char* GfDataNpc::getEffectName(unsigned int npc) {
    if (npc > 2000) {
        const char* name = GfBdatRsc::get()->getRscNpcListComp_Eff(npc);
        if (name != nullptr && name[0] != '\0') {
            return name;
        }
    }
    return nullptr;
}

bool GfDataNpc::isNeedResourceEvent(unsigned int npc) {
    if (npc <= 2000) {
        return false;
    }
    const char* name = GfBdatRsc::get()->getRscNpcListAddMotion(npc);
    return name != nullptr && name[0] != '\0';
}

unsigned int GfDataQuest::getListTalker(QuestID id) {
    if (id.empty()) {
        return 0;
    }
    return QuestListAcc::get()->getListTalker(id);
}

unsigned int GfDataQuest::getListRewardSetA(QuestID id) {
    if (id.empty()) {
        return 0;
    }
    return QuestListAcc::get()->getListRewardSetA(id);
}

unsigned int GfDataQuest::getListRewardSetB(QuestID id) {
    if (id.empty()) {
        return 0;
    }
    return QuestListAcc::get()->getListRewardSetB(id);
}

unsigned int GfDataQuest::getListResultA(QuestID id) {
    if (id.empty()) {
        return 0;
    }
    return QuestListAcc::get()->getListResultA(id);
}

unsigned int GfDataQuest::getListResultB(QuestID id) {
    if (id.empty()) {
        return 0;
    }
    return QuestListAcc::get()->getListResultB(id);
}

unsigned int GfDataQuest::getListSummary(QuestID id) {
    if (id.empty()) {
        return 0;
    }
    return QuestListAcc::get()->getListSummary(id);
}

int GfDataQuest::getListFlagPRT(QuestID id) {
    if (id.empty()) {
        return 0;
    }
    return QuestListAcc::get()->getListFlagPRT(id);
}

int GfDataQuest::getListFlagCLD(QuestID id) {
    if (id.empty()) {
        return 0;
    }
    return QuestListAcc::get()->getListFlagCLD(id);
}

unsigned int GfDataQuest::getListCallEventA(QuestID id) {
    if (id.empty()) {
        return 0;
    }
    return QuestListAcc::get()->getListCallEventA(id);
}

unsigned int GfDataQuest::getListCallEventB(QuestID id) {
    if (id.empty()) {
        return 0;
    }
    return QuestListAcc::get()->getListCallEventB(id);
}

unsigned int GfDataQuest::getListHintsID(QuestID id) {
    if (id.empty()) {
        return 0;
    }
    return QuestListAcc::get()->getListHintsID(id);
}

unsigned int GfDataQuest::getListPurposeID(QuestID id) {
    if (id.empty()) {
        return 0;
    }
    return QuestListAcc::get()->getListPurposeID(id);
}

bool GfDataQuest::getListVisible(QuestID id) {
    if (id.empty()) {
        return false;
    }
    return QuestListAcc::get()->getListVisible(id) != 0;
}

unsigned short GfDataQuest::m_achieve2blade[0x4D80];

unsigned int GfDataQuest::getAchievementBlade(unsigned int achieveId) {
    return m_achieve2blade[achieveId];
}

void GfDataQuest::registAchievementBlade(unsigned int achieveId, unsigned short blade) {
    m_achieve2blade[achieveId] = blade;
}

const char* GfDataQuest::getTaskLog(QuestID id, unsigned int msg) {
    const char* s = GfBdatMsg::getNameQuest(id, msg);
    return s != nullptr ? s : "";
}


bool GfDataBlade::getExtraParts(unsigned int blade, unsigned int part) {
    SDataBlade& data = GfDataManager::getDataGame()->m_blades[getBladeIndex(blade)];
    return data.m_extraParts[part] != 0;
}

const BladeArtsSlot* GfDataBlade::getArts(unsigned int blade, unsigned int index) {
    SDataBlade& data = GfDataManager::getDataGame()->m_blades[getBladeIndex(blade)];
    return &data.m_arts[index];
}

const BladeSkillSlot* GfDataBlade::getSkill(unsigned int blade, unsigned int index) {
    SDataBlade& data = GfDataManager::getDataGame()->m_blades[getBladeIndex(blade)];
    return &data.m_skills[index];
}

void GfDataBlade::setEnableEngageRex(unsigned int blade, bool enable) {
    SDataBlade& data = GfDataManager::getDataGame()->m_blades[getBladeIndex(blade)];
    data.m_enableEngageRex = enable;
}

void GfDataBlade::setUnselect(unsigned int blade, bool unselect) {
    SDataBlade& data = GfDataManager::getDataGame()->m_blades[getBladeIndex(blade)];
    data.m_unselect = unselect;
    GfEvent::callBladeUnselect(blade, unselect);
}

SDataDriver* GfDataDriver::getSDataDriver(unsigned int driver) {
    if (driver - 0x11 < 9) {
        return &GfDataManager::fn_7100224A10()[driver - 0x11].m_driver;
    }
    unsigned int index = driver - 1;
    SDataGame* game = GfDataManager::getDataGame();
    return &game->m_drivers[index < 0x10 ? index : 1];
}

unsigned int GfDataDriver::getLevel(const SDataDriver& data) {
    unsigned int driver = data.m_id;
    if (driver - 0x11 < 9) {
        GfBdatChrDr* bdat = GfBdatChrDr::get();
        if (bdat->fn_71001F16A4(bdat->fn_71001F13E0(data.m_id)) != 0) {
            return getLevel(fn_71002417DC(data.m_id));
        }
    }
    return data.m_level;
}

unsigned int GfDataDriver::getExp(const SDataDriver& data) {
    unsigned int driver = data.m_id;
    if (driver - 0x11 < 9) {
        GfBdatChrDr* bdat = GfBdatChrDr::get();
        if (bdat->fn_71001F16A4(bdat->fn_71001F13E0(data.m_id)) != 0) {
            return getExp(*getSDataDriver(fn_71002417DC(data.m_id)));
        }
    }
    return data.m_exp;
}

unsigned int GfDataDriver::getBattleExp(const SDataDriver& data) {
    unsigned int driver = data.m_id;
    if (driver - 0x11 < 9) {
        GfBdatChrDr* bdat = GfBdatChrDr::get();
        if (bdat->fn_71001F16A4(bdat->fn_71001F13E0(data.m_id)) != 0) {
            return getBattleExp(*getSDataDriver(fn_71002417DC(data.m_id)));
        }
    }
    return data.m_battleExp;
}

unsigned int GfDataDriver::getSkillPoint(const SDataDriver& data) {
    return data.m_skillPoint;
}

int GfDataDriver::getBladeSet(const SDataDriver& data) {
    return data.m_bladeSet;
}

int GfDataDriver::getMaxSetBladeNum(const SDataDriver& data) {
    if (data.m_id == 0) {
        return 0;
    }
    return data.m_id == 1 ? 5 : 3;
}

const char* GfDataDriver::getVoiceStr(const SDataDriver& data) {
    return GfBdatChrDr::get()->getChrDrVoice(data.m_id);
}

unsigned int GfDataDriver::getEquipAcce(const SDataDriver& data, unsigned int slot) {
    if (slot < 2) {
        return data.m_equipAcce[slot].m_item;
    }
    return data.m_equipAcceEx & 0xFFFF;
}

void GfDataDriver::setEquipAcce(SDataDriver& data, unsigned int slot, unsigned int accessory) {
    if (slot < 2) {
        data.m_equipAcce[slot].m_item = accessory;
        return;
    }
    data.m_equipAcceEx = (data.m_equipAcceEx & 0xFFFF0000) | accessory;
}

void GfDataDriver::addSkillPoint(SDataDriver& data, int point) {
    int skillPoint = data.m_skillPoint + point;
    if (skillPoint < 0) {
        skillPoint = 0;
    } else if (skillPoint > 9999999) {
        skillPoint = 9999999;
    }
    data.m_skillPoint = skillPoint;
    if (point > 0) {
        int total = data.m_totalSkillPoint + point;
        if (total < 0) {
            total = 0x7FFFFFFF;
        }
        data.m_totalSkillPoint = total;
    }
}

int GfDataMercenaries::getTeamMaleNum(unsigned int teamId) {
    Team* team = getTeamByTeamID(teamId);
    if (team == nullptr) {
        return 0;
    }
    int num = 0;
    for (int i = 0; i < 6; i++) {
        unsigned int blade = team->m_members[i];
        if (blade != 0) {
            unsigned int index = GfDataBlade::getBladeIndex(blade);
            SDataGame* game = GfDataManager::getDataGame();
            SDataBlade& data = game->m_blades[index];
            if (data.m_gender == 1 && data.m_questRace == 1) {
                num++;
            }
        }
    }
    return num;
}

int GfDataMercenaries::getTeamFemaleNum(unsigned int teamId) {
    Team* team = getTeamByTeamID(teamId);
    if (team == nullptr) {
        return 0;
    }
    int num = 0;
    for (int i = 0; i < 6; i++) {
        unsigned int blade = team->m_members[i];
        if (blade != 0) {
            unsigned int index = GfDataBlade::getBladeIndex(blade);
            SDataGame* game = GfDataManager::getDataGame();
            SDataBlade& data = game->m_blades[index];
            if (data.m_gender == 2 && data.m_questRace == 1) {
                num++;
            }
        }
    }
    return num;
}

}  // namespace gf

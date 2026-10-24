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

unsigned int GfDataQuest::getScenario() {
    return GfDataManager::getDataGame()->m_scenario;
}

unsigned int GfDataQuest::getSelect() {
    return GfDataManager::getDataGame()->m_select;
}

unsigned int GfDataUtil::getSkipTravelID() {
    return GfDataManager::getDataGame()->m_skipTravelID;
}

unsigned int GfDataMercenaries::getTeamNum() {
    return GfDataManager::getDataGame()->m_teamNum;
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


}  // namespace gf

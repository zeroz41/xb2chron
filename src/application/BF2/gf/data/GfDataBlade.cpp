#include "gf/SDataDriver.h"
#include "classes/gf/GfBdatBlade.h"
#include "classes/gf/GfBdatItem.h"
#include "classes/gf/GfBdatShop.h"
#include "gf/GfDataBlade.h"
#include "gf/GfDataHana.h"
#include "gf/GfDataMercenaries.h"
#include "gf/GfDataParty.h"
#include "gf/SDataBlade.h"
#include "gf/QuestID.h"
#include "classes/gf/GfBdatBlade.h"
#include "classes/gf/GfBdatBtl.h"
#include "gf/GfDataBattle.h"
#include "gf/GfDataBlade.h"
#include "gf/GfDataDriver.h"
#include "gf/GfDataEnBook.h"
#include "gf/GfDataEnemy.h"
#include "gf/GfDataEvent.h"
#include "gf/GfDataHana.h"
#include "gf/GfDataIdea.h"
#include "gf/GfDataItem.h"
#include "gf/GfDataMercenaries.h"
#include "gf/GfDataNanakoori.h"
#include "gf/GfDataParty.h"
#include "gf/GfDataQuest.h"
#include "gf/GfDataShop.h"
#include "gf/GfDataUtil.h"
#include "gf/SDataBlade.h"
#include "gf/SDataGame.h"
#include "gf/GfDataIdea.h"
#include "gf/GfDataBattle.h"
#include "classes/gf/GfInitParamDriver.h"
#include "classes/gf/GfBdatChrBl.h"
#include "classes/gf/GfBdatChrEnParam.h"
#include "classes/gf/GfBdatBlade.h"
#include "string.h"
#include "classes/gf/GfBdatBtl.h"
#include "classes/gf/GfBdatItem.h"
#include "classes/gf/GfBdatMaplist.h"
#include "gf/GfDataBladeCreate.h"
#include "gf/GfDataBlade.h"
#include "gf/GfDataDriver.h"
#include "gf/GfDataEnBook.h"
#include "gf/GfDataEnemy.h"
#include "gf/GfDataFieldSkill.h"
#include "gf/GfDataHana.h"
#include "gf/GfDataItem.h"
#include "gf/GfDataMap.h"
#include "gf/GfDataMercenaries.h"
#include "gf/GfDataMob.h"
#include "gf/GfDataNanakoori.h"
#include "gf/GfDataSound.h"
#include "gf/GfDataUtil.h"
#include "gf/GfDataWeapon.h"
#include "gf/SDataGame.h"
#include "gf/GfUtil.h"
#include "gf/GfDataSound.h"
#include "classes/gf/GfDataBdat.h"
#include "mm/mtl/FixStr.h"
#include "mm/mtl/FixedArray.h"
#include "mm/mtl/FixedVector.h"
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
#include "gf/SDataOption.h"
#include "gf/GfDataNpc.h"
#include "gf/GfDataBladeArtsN.h"
#include "gf/GfDataDriverSkill.h"
#include "plugin/Bdat.h"
#include "classes/gf/GfGameManager.h"

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

unsigned int GfDataEnemy::getEquipBlade(unsigned int arrange) {
    if (arrange == 0) {
        return 0;
    }
    GfBdatChrEnArrange* bdat = GfBdatChrEnArrange::get();
    unsigned int enemy = bdat->getChrEnArrangeEnemyBladeID(arrange);
    if (bdat->getChrEnArrangeStart() > enemy || bdat->getChrEnArrangeEnd() <= enemy) {
        return 0;
    }
    return GfBdatChrEnArrange::get()->getChrEnArrangeBladeID(enemy);
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

unsigned int GfDataBlade::getBladeWeaponRank(unsigned int blade) {
    unsigned int weapon = getSDataBlade(blade)->m_equipWeapon;
    if (weapon == 0) {
        return 0;
    }
    return GfBdatItem::get()->getPcWpnRank(weapon);
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

void GfDataDriver::fn_7100241CF4(unsigned int driver, bool flag) {
    SDataDriver* data = getSDataDriver(driver);
    data->m_kizunaRingFlags |= flag ? 2 : 1;
}

bool GfDataDriver::fn_7100241D64(unsigned int driver, bool flag) {
    return (getSDataDriver(driver)->m_kizunaRingFlags & (flag ? 2 : 1)) != 0;
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

bool GfDataDriver::fn_7100249170(unsigned int driver) {
    if (driver == 0) {
        return false;
    }
    return getSDataDriver(driver)->m_stateFlag != 0;
}

unsigned int GfDataDriverArts::getLevelCap(unsigned int arts, unsigned int index) {
    return GfBdatBtl::get()->getArtsDrReleaseLv(arts, index);
}

unsigned int GfDataDriverArts::getNameID(unsigned int arts) {
    return GfBdatBtl::get()->getArtsDrName(arts);
}

unsigned int GfDataDriverArts::getIconID(unsigned int arts) {
    return GfBdatBtl::get()->fn_71001E6BDC(arts);
}

unsigned int GfDataDriverArts::getDebugName(unsigned int arts) {
    return GfBdatBtl::get()->fn_71001E6B54(arts);
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

bool GfDataBladeArts::getEnhanceCaption(unsigned char*& bdat, unsigned int& id, unsigned int arts, unsigned int level) {
    unsigned int enhance = GfBdatBtl::get()->getArtsBlEnhance(arts, level - 1);
    if (enhance == 0) {
        return false;
    }
    id = GfBdatBtl::get()->getBTL_EnhanceCaption(enhance);
    if (GfGameManager::fn_71002A9E68()) {
        unsigned int caption = GfBdatBtl::get()->fn_71001E7F28(enhance);
        if (caption != 0) {
            id = caption;
        }
    }
    bdat = GfBdatMsg::getFpBtlEnhanceCap();
    return id != 0;
}

unsigned int GfDataBladeSkill::getEnhance(unsigned int skill, unsigned int index) {
    return GfBdatBtl::get()->getBTL_Skill_BlEnhance(skill, index - 1);
}

bool GfDataBladeSkill::getEnhanceCaption(unsigned char*& bdat, unsigned int& id, unsigned int skill, unsigned int level) {
    unsigned int enhance = GfBdatBtl::get()->getBTL_Skill_BlEnhance(skill, level - 1);
    if (enhance == 0) {
        return false;
    }
    id = GfBdatBtl::get()->getBTL_EnhanceCaption(enhance);
    if (GfGameManager::fn_71002A9E68()) {
        unsigned int caption = GfBdatBtl::get()->fn_71001E7F28(enhance);
        if (caption != 0) {
            id = caption;
        }
    }
    bdat = GfBdatMsg::getFpBtlEnhanceCap();
    return id != 0;
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

bool GfDataMap::getTimeRangeName(unsigned char*& bdat, unsigned int& id, unsigned int range) {
    bool result = false;
    if (range <= 8) {
        GfBdatMaplist* maplist = GfBdatMaplist::get();
        bdat = GfBdatMsg::getFpMapInfo();
        id = maplist->getTimeInfomsg(range);
        result = id != 0;
    }
    return result;
}

const char* GfDataMap::getWeatherName(WEATYPE type) {
    if (type == 0) {
        return "Default";
    }
    const char* name = nullptr;
    if (type > 0) {
        GfBdatMaplist* maplist = GfBdatMaplist::get();
        unsigned char* bdat = GfBdatMsg::getFpMapInfo();
        unsigned int id = maplist->getWeatherInfomsg(type);
        if (id != 0) {
            name = Bdat::getMSText(bdat, id);
        }
    }
    return name == nullptr ? "" : name;
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

unsigned int GfDataBlade::makeNormalTalkByPersonality(unsigned int personality) {
    // Proposed name, not the original's: the symbols leave it unnamed (lbl_71009BA078)
    static const unsigned short s_normalTalks[] = {
        0xA235, 0xA235, 0xA236, 0xA237, 0xA238, 0xA238, 0xA239, 0xA239, 0xA23A, 0xA23A, 0xA23B,
        0xA23B, 0xA23C, 0xA23C, 0xA23D, 0xA23D, 0xA23E, 0xA23E, 0xA23F, 0xA23F, 0xA240, 0xA240,
        0xA241, 0xA241, 0xA242, 0xA242, 0xA243, 0xA243, 0xA244, 0xA244, 0xA245, 0xA246,
    };
    unsigned int voice = GfBdatBtl::get()->getBTL_Bl_PersonalityVoiceID(personality);
    unsigned int index = voice == 0 ? 0 : voice - 61;
    if (index < 32) {
        return s_normalTalks[index];
    }
    return 0;
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

int GfDataMercenaries::getPointMax() {
    // Proposed name, not the original's: the symbols leave it unnamed (lbl_71009BA368)
    static const unsigned short s_pointMaxDatavalues[6] = {0, 0x3B, 0x3C, 0x3D, 0x3E, 0};
    unsigned int level = getLevel();
    if (level == 0 || level == 5) {
        return 0;
    }
    return GfBdatBtl::get()->getWildcardDatavalueU2(s_pointMaxDatavalues[level]);
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

unsigned int GfDataMercenaries::getMissionMapID(unsigned int mission) {
    if (mission != 0) {
        QuestID quest = getMissionQuestID(mission);
        if (!quest.empty()) {
            unsigned int hints = GfDataQuest::getListHintsID(quest);
            if (hints != 0) {
                unsigned int zone = QuestListAcc::get()->getHintsZoneID(hints);
                if (GfDataBlade::fn_7100231884() > 8036 && zone == 12) {
                    return 14;
                }
                return zone;
            }
        }
    }
    return 0;
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

unsigned int GfDataMercenaries::getFieldSkill1(unsigned int mission) {
    QuestID quest = getMissionQuestID(mission);
    if (!quest.empty()) {
        unsigned int hints = GfDataQuest::getListHintsID(quest);
        if (hints != 0) {
            return QuestListAcc::get()->getHintsFSkillID1(hints);
        }
    }
    return 0;
}

unsigned int GfDataMercenaries::getFieldSkill2(unsigned int mission) {
    QuestID quest = getMissionQuestID(mission);
    if (!quest.empty()) {
        unsigned int hints = GfDataQuest::getListHintsID(quest);
        if (hints != 0) {
            return QuestListAcc::get()->getHintsFSkillID2(hints);
        }
    }
    return 0;
}

unsigned int GfDataMercenaries::getFieldSkill3(unsigned int mission) {
    QuestID quest = getMissionQuestID(mission);
    if (!quest.empty()) {
        QuestListAcc* acc = QuestListAcc::get();
        unsigned int hints = GfDataQuest::getListHintsID(quest);
        if (hints != 0) {
            return acc->getHintsFSkillID3(hints);
        }
    }
    return 0;
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

unsigned int GfDataUtil::getMoney() {
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

// Proposed name, not the original's: the symbols leave it unnamed (lbl_7100B50BE8)
static const char* s_attributeFileNames[] = {"none", "fire", "water", "wind", "earth", "volt", "ice", "light", "dark"};

const char* GfDataUtil::getAttributeFileName(unsigned int attribute) {
    return s_attributeFileNames[attribute];
}

unsigned int GfDataBlade::getStartCommonBlade() {
    return 1197;
}

unsigned int GfDataBlade::getEndCommonBlade() {
    return 1401;
}

ActivateType GfDataBlade::getBladeActivateType(unsigned int blade) {
    unsigned int index = getBladeIndex(blade);
    SDataGame* game = GfDataManager::getDataGame();
    return getBladeActivateType(game->m_blades[index]);
}

bool GfDataBlade::fn_710023978C(unsigned int blade) {
    GfBdatChrBl* bdat = GfBdatChrBl::get();
    if (blade >= bdat->getChrBlEnd()) {
        return false;
    }
    return bdat->fn_71001ED49C(blade);
}

bool GfDataBlade::fn_71002397DC(unsigned int blade) {
    GfBdatChrBl* bdat = GfBdatChrBl::get();
    if (blade >= bdat->getChrBlEnd()) {
        return false;
    }
    return bdat->fn_71001ED52C(blade);
}

ActivateType GfDataBlade::getBladeActivateType(const SDataBlade& blade) {
    int type = 0;
    switch (blade.m_dataType) {
    case 1:
        type = blade.m_setDriver != 0 ? 2 : 1;
        break;
    case 2:
        type = 3;
        break;
    }
    return ActivateType(type);
}

unsigned int GfDataBlade::fn_710023982C(unsigned int blade) {
    if (blade == 0) {
        return 0;
    }
    unsigned int index = getBladeIndex(blade);
    SDataGame* game = GfDataManager::getDataGame();
    return game->m_blades[index].m_gender;
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

bool GfDataDriver::fn_7100237A94(unsigned int driver) {
    if (driver - 0x11 <= 8) {
        GfBdatChrDr* bdat = GfBdatChrDr::get();
        return bdat->fn_71001F16A4(bdat->fn_71001F13E0(driver)) == 0;
    }
    return true;
}

bool GfDataDriver::isActivateParty(unsigned int driver) {
    if (driver == 0) {
        return false;
    }
    if (getSDataDriver(driver)->m_dataType != 1) {
        return false;
    }
    return static_cast<unsigned int>(GfDataParty::getDriverPartyID(driver)) < 3;
}

bool GfDataBlade::isBladeID(unsigned int blade) {
    return blade >= 1001 && blade < 1423;
}

SDataPouch* GfDataDriver::getPouchData(unsigned int driver, unsigned int pouch) {
    return getSDataDriver(driver)->m_pouches + pouch;
}

bool GfDataBlade::isNeedChangeWeapon(unsigned int blade) {
    return (blade >= 1043 && blade < 1051) || blade == 1039;
}

unsigned int GfDataDriver::fn_7100241640(unsigned int driver, unsigned int slot) {
    return GfBdatChrDr::get()->getChrDrDefBlade(driver, slot);
}

bool GfDataDriver::fn_7100241660(unsigned int driver) {
    GfBdatChrDr* bdat = GfBdatChrDr::get();
    unsigned int row = bdat->fn_71001F13E0(driver);
    if (row == 0) {
        return false;
    }
    return bdat->fn_71001F183C(row);
}

unsigned int GfDataDriver::fn_710024198C(unsigned int driver) {
    if (driver - 0x11 <= 8) {
        return GfDataManager::fn_7100224A10()[driver - 0x11].m_partyIndex;
    }
    return 0;
}

unsigned int GfDataDriver::fn_71002419C8(unsigned int driver) {
    GfBdatChrDr* bdat = GfBdatChrDr::get();
    unsigned int row = bdat->fn_71001F13E0(driver);
    if (row == 0) {
        return 0;
    }
    return bdat->fn_71001F172C(row);
}

SDataDriverDlc* GfDataDriver::fn_7100241BB4(unsigned int driver) {
    driver = driver - 0x11 < 9 ? driver : 0x11;
    unsigned int index;
    if (driver - 0x11 < 9) {
        index = driver - 0x11;
    } else {
        index = driver - 1 < 16 ? driver - 1 : 1;
    }
    return &GfDataManager::fn_7100224A10()[index];
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

bool GfDataDriver::fn_7100247580(mm::mtl::FixedVector<unsigned short, 64>& enhances, int driver) {
    return fn_71002475DC(enhances, *getSDataDriver(driver));
}

bool GfDataDriver::fn_71002475DC(mm::mtl::FixedVector<unsigned short, 64>& enhances, const SDataDriver& data) {
    GfBdatItem* bdat = GfBdatItem::get();
    for (int i = 0; i < 2; i++) {
        unsigned int item = data.m_equipAcce[i].m_item;
        if (item != 0) {
            unsigned int enhance = bdat->getPcEquipEnhance1(item);
            if (enhance != 0) {
                enhances.push_back(enhance);
            }
        }
    }
    unsigned int item = static_cast<unsigned short>(data.m_equipAcceEx);
    if (item != 0) {
        unsigned int enhance = bdat->getPcEquipEnhance1(item);
        if (enhance != 0) {
            enhances.push_back(enhance);
        }
    }
    unsigned int dlc = data.m_id - 0x11;
    if (dlc < 9) {
        unsigned int item = GfDataManager::fn_7100224A10()[dlc].m_item;
        if (item != 0) {
            unsigned int enhance = bdat->getPcEquipEnhance1(item);
            if (enhance != 0) {
                enhances.push_back(enhance);
            }
        }
    }
    return enhances.size() != 0;
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

unsigned int GfDataDriver::getLevel(unsigned int driver) {
    return getLevel(*getSDataDriver(driver));
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

const char* GfDataBlade::getName(unsigned int blade, unsigned int kind) {
    if (fn_71002364B8(blade)) {
        unsigned int row = blade - 1107;
        unsigned int id = GfBdatChrDr::get()->getChrDrName(row);
        unsigned char* fp = GfBdatMsg::getFpChrDr();
        if (id == 0) {
            return nullptr;
        }
        return Bdat::getMSText(fp, id);
    }
    const char* name = nullptr;
    if (blade != 0) {
        unsigned int index = getBladeIndex(blade);
        SDataGame* game = GfDataManager::getDataGame();
        unsigned int id = game->m_blades[index].m_bladeId;
        if (id != 0) {
            unsigned int msg = kind;
            unsigned char* fp;
            if (kind != 0) {
                if (id < GfBdatChrBl::get()->getChrBlEnd()) {
                    fp = GfDataBdat::getFP(423);
                } else {
                    fp = GfDataBdat::getFP(396);
                }
            } else if (game->m_blades[index].m_nameMsg != 0) {
                msg = game->m_blades[index].m_nameMsg;
                fp = GfDataBdat::getFP(423);
            } else {
                msg = game->m_blades[index].m_nameMsgAlt;
                fp = GfDataBdat::getFP(396);
            }
            if (msg != 0) {
                name = Bdat::getMSText(fp, msg);
            }
        }
    }
    return name == nullptr ? "" : name;
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

const char* GfDataBlade::getDebugName(unsigned int blade) {
    if (isCommonBlade(blade)) {
        unsigned int index = getBladeIndex(blade);
        SDataGame* game = GfDataManager::getDataGame();
        if (game->m_blades[index].m_hasDebugName != 0) {
            return game->m_blades[index].m_debugName;
        }
        return getName(blade, 0);
    }
    return GfBdatChrBl::get()->getChrBlDebugName(blade);
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

bool GfDataBlade::isMale(unsigned int blade) {
    if (blade == 0) {
        return false;
    }
    unsigned int index = getBladeIndex(blade);
    SDataGame* game = GfDataManager::getDataGame();
    return game->m_blades[index].m_gender == 1 && game->m_blades[index].m_questRace == 1;
}

bool GfDataBlade::isFemale(unsigned int blade) {
    if (blade == 0) {
        return false;
    }
    unsigned int index = getBladeIndex(blade);
    SDataGame* game = GfDataManager::getDataGame();
    return game->m_blades[index].m_gender == 2 && game->m_blades[index].m_questRace == 1;
}

bool GfDataAchievement::getAchievementType(ACHIEVEMENT_TYPE& type, unsigned int& index, unsigned int line) {
    if (line <= 2) {
        type = ACHIEVEMENT_TYPE(0);
        index = line;
        return true;
    }
    if (line <= 5) {
        type = ACHIEVEMENT_TYPE(1);
        index = line - 3;
        return true;
    }
    if (line <= 8) {
        type = ACHIEVEMENT_TYPE(2);
        index = line - 6;
        return true;
    }
    if (line == 9) {
        type = ACHIEVEMENT_TYPE(3);
        index = 0;
        return true;
    }
    return false;
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

bool GfDataBlade::getEquipOrb(mm::mtl::FixedArray<unsigned short, 3ul>& orbs, unsigned int blade) {
    if (blade == 0) {
        return false;
    }
    unsigned int index = getBladeIndex(blade);
    SDataGame* game = GfDataManager::getDataGame();
    SDataBlade& data = game->m_blades[index];
    orbs = data.m_equipOrbs;
    return true;
}

bool GfDataBlade::setEquipOrb(unsigned int blade, unsigned short orb, unsigned int slot) {
    if (blade == 0) {
        return false;
    }
    SDataBlade* data = getSDataBlade(blade);
    // the original reads the orb count here without using it
    getEquipOrbMax(blade);
    data->m_equipOrbs[slot] = orb;
    return true;
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

unsigned int GfDataBlade::getParmor(unsigned int blade) {
    if (blade == 0) {
        return 0;
    }
    if (GfDataHana::isValid(blade)) {
        unsigned int index = getBladeIndex(blade);
        SDataGame* game = GfDataManager::getDataGame();
        unsigned int parts = game->m_blades[index].m_equipHana.m_roleParts;
        return GfBdatItem::get()->getITM_HanaRolePArmor(parts);
    }
    return getSDataBlade(blade)->m_pArmor;
}

unsigned int GfDataBlade::getEarmor(unsigned int blade) {
    if (blade == 0) {
        return 0;
    }
    if (GfDataHana::isValid(blade)) {
        unsigned int index = getBladeIndex(blade);
        SDataGame* game = GfDataManager::getDataGame();
        unsigned int parts = game->m_blades[index].m_equipHana.m_roleParts;
        return GfBdatItem::get()->getITM_HanaRoleEArmor(parts);
    }
    return getSDataBlade(blade)->m_eArmor;
}

unsigned int GfDataBlade::getHpMaxRev(unsigned int blade) {
    if (GfDataHana::isValid(blade)) {
        unsigned int index = getBladeIndex(blade);
        SDataGame* game = GfDataManager::getDataGame();
        unsigned int parts = game->m_blades[index].m_equipHana.m_roleParts;
        return GfBdatItem::get()->getITM_HanaRoleHpMaxRev(parts);
    }
    return getSDataBlade(blade)->m_hpMaxRev;
}

unsigned int GfDataBlade::getStrengthRev(unsigned int blade) {
    if (GfDataHana::isValid(blade)) {
        unsigned int index = getBladeIndex(blade);
        SDataGame* game = GfDataManager::getDataGame();
        unsigned int parts = game->m_blades[index].m_equipHana.m_roleParts;
        return GfBdatItem::get()->getITM_HanaRoleStrengthRev(parts);
    }
    return getSDataBlade(blade)->m_strengthRev;
}

unsigned int GfDataBlade::getPowerEtherRev(unsigned int blade) {
    if (GfDataHana::isValid(blade)) {
        unsigned int index = getBladeIndex(blade);
        SDataGame* game = GfDataManager::getDataGame();
        unsigned int parts = game->m_blades[index].m_equipHana.m_roleParts;
        return GfBdatItem::get()->getITM_HanaRolePowEtherRev(parts);
    }
    return getSDataBlade(blade)->m_powerEtherRev;
}

unsigned int GfDataBlade::getDexRev(unsigned int blade) {
    if (GfDataHana::isValid(blade)) {
        unsigned int index = getBladeIndex(blade);
        SDataGame* game = GfDataManager::getDataGame();
        unsigned int parts = game->m_blades[index].m_equipHana.m_roleParts;
        return GfBdatItem::get()->getITM_HanaRoleDexRev(parts);
    }
    return getSDataBlade(blade)->m_dexRev;
}

unsigned int GfDataBlade::getAgilityRev(unsigned int blade) {
    if (GfDataHana::isValid(blade)) {
        unsigned int index = getBladeIndex(blade);
        SDataGame* game = GfDataManager::getDataGame();
        unsigned int parts = game->m_blades[index].m_equipHana.m_roleParts;
        return GfBdatItem::get()->getITM_HanaRoleAgilityRev(parts);
    }
    return getSDataBlade(blade)->m_agilityRev;
}

unsigned int GfDataBlade::getLuckRev(unsigned int blade) {
    if (GfDataHana::isValid(blade)) {
        unsigned int index = getBladeIndex(blade);
        SDataGame* game = GfDataManager::getDataGame();
        unsigned int parts = game->m_blades[index].m_equipHana.m_roleParts;
        return GfBdatItem::get()->getITM_HanaRoleLuckRev(parts);
    }
    return getSDataBlade(blade)->m_luckRev;
}

bool GfDataBlade::isUsedFavorite(unsigned int blade, FAVORITE favorite) {
    unsigned int index = getBladeIndex(blade);
    SDataGame* game = GfDataManager::getDataGame();
    SDataBlade& data = game->m_blades[index];
    switch (favorite) {
    case 0:
        return data.m_favorites[0].m_categoryUsed != 0;
    case 1:
        return data.m_favorites[1].m_categoryUsed != 0;
    case 2:
        return data.m_favorites[0].m_itemUsed != 0;
    case 3:
        return data.m_favorites[1].m_itemUsed != 0;
    }
    return false;
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

unsigned int GfDataMercenaries::getMissionPurposeID(unsigned int mission) {
    QuestID quest = getMissionQuestID(mission);
    if (quest.empty()) {
        return 0;
    }
    QuestID next = GfDataQuest::getListNextQuestA(quest);
    if (next.empty()) {
        return 0;
    }
    return GfDataQuest::getListPurposeID(next);
}

bool GfDataMercenaries::isOrderOnlyOne(unsigned int mission) {
    return QuestListAcc::get()->getFLD_MercenariesMissionRepeatable(mission) == 0;
}

unsigned int GfDataMercenaries::getMissionTime(unsigned int mission) {
    return QuestListAcc::get()->getFLD_MercenariesMissionRequestPerformance(mission);
}

bool GfDataMercenaries::getFieldSkillInfo(unsigned char*& bdat, unsigned int& id, unsigned int mission, unsigned int slot) {
    unsigned int skill;
    switch (slot) {
    case 0:
        skill = getFieldSkill1(mission);
        if (skill == 0) {
            return false;
        }
        break;
    case 1:
        skill = getFieldSkill2(mission);
        if (skill == 0) {
            return false;
        }
        break;
    case 2:
        skill = getFieldSkill3(mission);
        if (skill == 0) {
            return false;
        }
        break;
    default:
        return false;
    }
    id = QuestListAcc::get()->getFLD_FieldSkillListName(skill);
    bdat = GfBdatMsg::getFpFieldSkill();
    return id != 0;
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

int GfDataMercenaries::getMissionTaskType(unsigned int mission) {
    int result = 0;
    for (unsigned int i = 0; i < 4; i++) {
        QuestListAcc* acc = QuestListAcc::get();
        unsigned int purpose = getMissionPurposeID(mission);
        int type = purpose == 0 ? 0 : acc->getTaskTaskType(purpose, i);
        if (type != 9) {
            result = type;
            break;
        }
    }
    return result;
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

const char* GfDataBladeArts::getName(unsigned int arts) {
    unsigned char* bdat;
    unsigned int id;
    if (getName(bdat, id, arts)) {
        if (const char* name = Bdat::getMSText(bdat, id)) {
            return name;
        }
    }
    return GfBdatBtl::get()->getArtsBlDebugName(arts);
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

bool GfDataDriverSkill::getEnhanceCaption(unsigned char*& bdat, unsigned int& id, unsigned int skill) {
    unsigned int enhance = GfBdatBtl::get()->getBTL_Skill_DrEnhance(skill);
    if (enhance == 0) {
        return false;
    }
    id = GfBdatBtl::get()->getBTL_EnhanceCaption(enhance);
    if (GfGameManager::fn_71002A9E68()) {
        unsigned int caption = GfBdatBtl::get()->fn_71001E7F28(enhance);
        if (caption != 0) {
            id = caption;
        }
    }
    bdat = GfBdatMsg::getFpBtlEnhanceCap();
    return id != 0;
}

bool GfDataWeapon::getWeaponTypeName(unsigned char*& bdat, unsigned int& id, unsigned int row) {
    id = GfBdatItem::get()->getPcWpnTypeName(row);
    bdat = GfBdatMsg::getFpPcWpnType();
    return id != 0;
}

bool GfDataWeapon::getWeaponTypeNameByItem(unsigned char*& bdat, unsigned int& id, unsigned int weapon) {
    unsigned int type = GfBdatItem::get()->getPcWpnWpnType(weapon);
    if (type == 0) {
        return false;
    }
    id = GfBdatItem::get()->getPcWpnTypeName(type);
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

bool GfDataBlade::fn_710024D82C(unsigned int id) {
    if (id <= 2000) {
        return false;
    }
    return GfBdatRsc::get()->fn_7100219574(id) != 0;
}

void GfDataBlade::fn_710024D86C(unsigned int id, unsigned int value) {
    GfGameFlag::setLocal(1, id > 43877 ? id + 11651 : id, value);
}

bool GfDataBlade::fn_710024D890(unsigned int id) {
    return GfGameFlag::getLocal(1, id > 43877 ? id + 11651 : id) != 0;
}

bool GfDataBlade::fn_710024DA20(unsigned char*& bdat, unsigned int& id, unsigned int rsc) {
    if (rsc <= 2000) {
        return false;
    }
    bdat = GfDataBdat::getFP(452);
    id = GfBdatRsc::get()->fn_710021A010(rsc);
    return id != 0;
}

unsigned int GfDataBlade::fn_710024DA88(unsigned int id) {
    if (id <= 2000) {
        return 0;
    }
    return GfBdatRsc::get()->fn_7100219C58(id);
}

unsigned int GfDataBlade::fn_710024DAB0(unsigned int id) {
    if (id <= 2000) {
        return 0;
    }
    return GfBdatRsc::get()->fn_7100219CE0(id);
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

unsigned int GfDataBlade::getLinkChNum(unsigned int blade) {
    unsigned int linkSet = getSDataBlade(blade)->m_kizunaLinkSet;
    if (linkSet == 0) {
        return 0;
    }
    return GfBdatBtl::get()->getBTL_Bl_KizunaLinkSetLinkChNum(linkSet);
}

const BladeArtsSlot* GfDataBlade::getArts(unsigned int blade, unsigned int index) {
    SDataBlade& data = GfDataManager::getDataGame()->m_blades[getBladeIndex(blade)];
    return &data.m_arts[index];
}

unsigned int GfDataBlade::getArtsEnhance(unsigned int blade, unsigned int index) {
    if (GfDataHana::isValid(blade)) {
        unsigned int bladeIndex = getBladeIndex(blade);
        SDataGame* game = GfDataManager::getDataGame();
        return GfBdatItem::get()->getITM_HanaArtsEnhEnhance(game->m_blades[bladeIndex].m_equipHana.m_artsParts[index].m_item);
    }
    return 0;
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

bool GfDataDriver::fn_7100245794(unsigned int* level, unsigned int* value, unsigned int driver) {
    return fn_7100245800(level, value, *getSDataDriver(driver));
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

void GfDataDriver::fn_7100247E88(unsigned int driver, int point) {
    addSkillPoint(*getSDataDriver(driver), point);
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

unsigned int GfDataDriver::getBlade(unsigned int driver, int slot) {
    if (driver == 0) {
        return 0;
    }
    SDataDriver* data = getSDataDriver(driver);
    unsigned int id = data->m_id;
    if (id - 0x11 < 9) {
        return GfBdatChrDr::get()->getChrDrDefBlade1(id);
    }
    int bladeSet = data->m_bladeSet;
    int index = slot < 0 ? bladeSet : slot;
    if (index < 0) {
        return 0;
    }
    return data->m_blades[index];
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

GfItemHandle GfDataDriver::getEquipAcceHandle(unsigned int driver, unsigned int slot) {
    SDataDriver* data = getSDataDriver(driver);
    if (slot < 2) {
        return data->m_equipAcce[slot].m_handle;
    }
    return data->m_equipAcceHandleEx;
}

void GfDataDriver::fn_7100247A08(unsigned int driver, unsigned int slot, unsigned int accessory) {
    if (driver == 0) {
        return;
    }
    setEquipAcce(*getSDataDriver(driver), slot, accessory);
}

void GfDataDriver::setEquipAcce(SDataDriver& data, unsigned int slot, unsigned int accessory) {
    if (slot < 2) {
        data.m_equipAcce[slot].m_item = accessory;
        return;
    }
    data.m_equipAcceEx = (data.m_equipAcceEx & 0xFFFF0000) | accessory;
}

void GfDataDriver::fn_7100247ABC(unsigned int driver, unsigned int slot, const GfItemHandle& handle) {
    if (driver == 0) {
        return;
    }
    SDataDriver* data = getSDataDriver(driver);
    if (slot < 2) {
        data->m_equipAcce[slot].m_handle = handle;
    } else {
        data->m_equipAcceHandleEx = handle;
    }
}

void GfDataDriver::fn_7100247B40(unsigned int driver, bool flag) {
    SDataDriver* data = getSDataDriver(getSDataDriver(driver)->m_id);
    if (flag) {
        data->m_equipAcceEx |= 0x80000000;
    } else {
        data->m_equipAcceEx &= 0x7FFFFFFF;
    }
}

bool GfDataDriver::fn_7100247BF0(unsigned int driver) {
    return getSDataDriver(getSDataDriver(driver)->m_id)->m_equipAcceEx >> 31;
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

void GfDataDriver::fn_7100247F74(mm::mtl::FixedVector<unsigned short, 64>& enhances, unsigned int driver) {
    fn_7100247FD0(enhances, *getSDataDriver(driver));
}

bool GfDataDriver::fn_7100248668(mm::mtl::FixedVector<unsigned short, 64>& enhances, const SDataDriverDlc& data) {
    unsigned int item = data.m_item;
    if (item != 0) {
        unsigned int enhance = GfBdatItem::get()->getPcEquipEnhance1(item);
        if (enhance != 0) {
            enhances.push_back(enhance);
        }
    }
    return enhances.size() != 0;
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


unsigned char* GfDataDriverArts::getNameFP() {
    return GfDataBdat::getFP(400);
}

unsigned char* GfDataDriverArts::getCaptionFP() {
    return GfDataBdat::getFP(401);
}

unsigned int GfDataDriverArts::getDamageMul(unsigned int arts, unsigned int level) {
    if (arts == 0 || level == 0) {
        return 0;
    }
    return GfBdatBtl::get()->getArtsDrDmgMgn(arts, level - 1);
}

unsigned int GfDataDriverArts::getRecast(unsigned int arts, unsigned int level) {
    if (arts == 0 || level == 0) {
        return 0;
    }
    return GfBdatBtl::get()->getArtsDrRecast(arts, level - 1);
}

unsigned int GfDataDriverArts::getEnhance(unsigned int arts, unsigned int level) {
    if (arts == 0 || level == 0) {
        return 0;
    }
    return GfBdatBtl::get()->getArtsDrEnhance(arts, level - 1);
}

const char* GfDataDriver::getBelongingMountBone() {
    return "MT_wire";
}

const char* GfDataDriver::getBelongingMountBoneA() {
    return "EX_wireA";
}

const char* GfDataDriver::getBelongingMountBoneB() {
    return "EX_wireB";
}

unsigned int GfDataDriver::getFavorite(unsigned int driver, FAVORITE favorite) {
    if (driver == 0) {
        return 0;
    }
    if (static_cast<unsigned int>(favorite) <= 1) {
        return GfBdatChrDr::get()->getChrDrFavoriteCategory(driver, favorite);
    }
    switch (favorite) {
    case 2:
    case 3:
        return GfBdatChrDr::get()->getChrDrFavoriteItem(driver, favorite - 2);
    }
    return 0;
}

void GfDataDriver::setPouchData(unsigned int driver, unsigned int pouch, const SDataPouch& data) {
    SDataPouch* dst = getSDataDriver(driver)->m_pouches + pouch;
    dst->m_open = data.m_open;
    dst->itemId = data.itemId;
    dst->remainTime = data.remainTime;
}

bool GfDataDriver::fn_710023F9A8(unsigned int driver) {
    return driver - 0x11 < 9;
}

unsigned int GfDataMercenaries::getEndMissionID() {
    return QuestListAcc::get()->getFLD_MercenariesMissionEnd();
}

int GfDataMercenaries::getMissionCategory(unsigned int mission) {
    return QuestListAcc::get()->getFLD_MercenariesMissionCategory(mission);
}

unsigned int GfDataMercenaries::getMissionRewardID(unsigned int mission) {
    QuestListAcc* acc = QuestListAcc::get();
    if (isMissionCompleteFlag(mission) && !isOrderOnlyOne(mission)) {
        return acc->getListRewardSetB(getMissionQuestID(mission));
    }
    return acc->getListRewardSetA(getMissionQuestID(mission));
}

bool GfDataMercenaries::getReserver(mm::mtl::FixedVector<unsigned short, 422>& list) {
    GfDataBlade::getListReserver(list);
    return !list.empty();
}

unsigned int GfDataMercenaries::getTeamMax() {
    unsigned int level = GfGameFlag::getLocal(4, 2);
    unsigned int max = 1;
    if (level > 1) {
        max++;
    }
    if (level > 3) {
        max++;
    }
    return max;
}

void GfDataBlade::fn_71002320AC(SDataGame* game, bool flag) {
    GfGameFlag::setLocal(game->m_gameFlag, 1, 0xBDCD, flag);
}

unsigned short GfDataBlade::fn_7100231884() {
    return GfGameFlag::getLocal(GfDataManager::getDataGame()->m_gameFlag, 0x10, 1);
}

void GfDataSound::getFullPath(mm::mtl::FixStr<128>& path, const char* name) {
    path.format("sound/se/%s%s", name, ".xsp");
}

// Proposed name, not the original's: the symbols leave it unnamed (lbl_7100B50E10)
static const char* s_weaponTypeSeFiles[50] = {
    "", "se_btl_dr_sworda", "se_btl_dr_lsword", "se_btl_dr_wring", "se_btl_dr_toraa", "se_btl_dr_torab",
    "se_btl_dr_torac", "se_btl_dr_wsword", "se_btl_dr_gsword", "se_btl_dr_wsickle", "se_btl_dr_tomahawk",
    "se_btl_dr_lance", "se_btl_dr_ecannon", "se_btl_dr_shammer", "se_btl_dr_katana", "se_btl_dr_bitball",
    "se_btl_dr_kcrow", "se_btl_dr_swordd", "se_btl_dr_lkatana", "se_btl_dr_tonfa", "", "", "", "", "", "", "", "",
    "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""};

const char* GfDataSound::getSeFileByWeaponType(unsigned int type) {
    if (type > 19) {
        return "";
    }
    return s_weaponTypeSeFiles[type];
}

void fn_7100254DC4(SSoundUiOption* option, unsigned int index, unsigned char value) {
    if (GfBdatBtl::get() == nullptr) {
        return;
    }
    option->m_keyD = 4;
    option->m_list[index - 1] = value;
    fn_7100254DF0(option);
}

unsigned char fn_71002550C0(const SSoundUiOption* option, unsigned int index) {
    if (GfBdatBtl::get() == nullptr) {
        return 0;
    }
    return option->m_list[index - 1];
}

unsigned int GfDataBlade::fn_71002557C8(unsigned int id) {
    if (id <= 2000) {
        return 0;
    }
    unsigned int rsc = GfBdatRsc::get()->fn_7100219C58(id);
    if (rsc == 0) {
        return 0;
    }
    for (unsigned int i = 0; i < 256; i++) {
        if (GfGameFlag::getLocal(8, i + 0x10C4) == rsc - 0xED02) {
            return i + 1;
        }
    }
    return 0;
}

unsigned int GfDataBlade::fn_7100255848(unsigned int id) {
    if (id <= 2000) {
        return 0;
    }
    unsigned int rsc = GfBdatRsc::get()->fn_7100219C58(id);
    if (rsc == 0) {
        return 0;
    }
    for (unsigned int i = 0; i < 256; i++) {
        if (GfGameFlag::getLocal(8, i + 0x11C5) == rsc - 0xED02) {
            return i + 1;
        }
    }
    return 0;
}

unsigned int GfDataMap::getFieldZoneId(unsigned int id) {
    switch (id) {
    case 0: return 1;
    case 1: return 2;
    case 2: return 3;
    case 3: return 4;
    case 4: return 7;
    case 5: return 5;
    case 6: return 6;
    }
    return 0;
}

int GfDataUtil::getObjTypeByCharaId(unsigned int chara) {
    if (chara - 1 < 25) {
        return 3;
    }
    return chara - 1001 < 1000 ? 4 : 0;
}

const char* GfDataMob::getName(unsigned int mob) {
    return util::getFilePtrFromPath(GfBdatRsc::get()->getRscMobListModel(mob));
}

unsigned int GfDataMap::getZoneIdForDevelopPoint(unsigned int point) {
    if (point == 0) {
        return 0;
    }
    if (GfBdatMaplist* bdat = GfBdatMaplist::get()) {
        return bdat->getMaplistzone(point);
    }
    return 0;
}

const char* GfDataMap::getWeatherEffName(WEATYPE type) {
    if (type == 0) {
        return "";
    }
    return GfBdatMaplist::get()->getWeatherInfoeff(type);
}

const char* GfDataMap::getWeatherSndBeginName(WEATYPE type) {
    if (type == 0) {
        return "";
    }
    return GfBdatMaplist::get()->getWeatherInfosndBegin(type);
}

int GfDataMap::getWeatherType(unsigned int mapId, WEATHERID id) {
    unsigned int index = id - 1;
    if (index > 3) {
        return 0x15;
    }
    return GfBdatMaplist::get()->getMaplistw_type(mapId, index);
}

CLOUD_SEA GfDataBlade::fn_710024E8D4(unsigned int map) {
    return CLOUD_SEA(fn_710024E1C8(map)->m_cloudSea != 0);
}

void GfDataBlade::fn_710024E8F4(unsigned int map, CLOUD_SEA cloudSea) {
    fn_710024E1C8(map)->m_cloudSea = cloudSea != 0;
}

bool GfDataBlade::isNeedAttributeResource(unsigned int blade) {
    if (blade >= 1197 && blade < 1423) {
        return true;
    }
    if (blade >= 1051 && blade < 1073) {
        return true;
    }
    return blade >= 1005 && blade < 1008;
}

bool GfDataItem::isMusubiCookItem(unsigned int item) {
    switch (item) {
    case 40269:
    case 40270:
    case 40271:
    case 40272:
    case 40305:
        return true;
    }
    return false;
}


bool GfDataBlade::isHomuriNameHikari() {
    return GfGameFlag::getLocal(GfDataManager::getDataGame()->m_gameFlag, 1, 0x89FB) != 0;
}


const char* GfDataMob::getEffectName(unsigned int mob) {
    const char* name = GfBdatRsc::get()->getRscMobListComp_Eff(mob);
    return *name == '\0' ? nullptr : name;
}

unsigned int GfDataWeapon::getEffWeaponType(unsigned int type) {
    if (type == 0) {
        return 0;
    }
    if (type == 17) {
        return 17;
    }
    return GfBdatItem::get()->getPcWpnTypeMotion(type);
}

unsigned int GfDataItem::getItemType(unsigned int item) {
    ItemType::Type type;
    unsigned int index;
    return getItemType(type, index, item) ? type : 0;
}

unsigned int GfDataItem::getItemStartID(ItemType::Type type) {
    unsigned int begin;
    unsigned int end;
    return getItemBdatCount(begin, end, type) ? begin : 0;
}

float GfDataItem::getFavoriteItemTime(unsigned int item) {
    return GfBdatItem::get()->getFavoriteTime(item) * 60.0f;
}


const char* GfDataEnemy::getAddMotionName(unsigned int rsc) {
    const char* name = GfBdatRsc::get()->getRscEnRefMotion(rsc);
    if (name != nullptr && *name != '\0') {
        return name;
    }
    return nullptr;
}

const char* GfDataEnemy::getResourceNameModel(unsigned int arrange) {
    unsigned int param = GfBdatChrEnArrange::get()->getChrEnArrangeParamID(arrange);
    if (param == 0) {
        return nullptr;
    }
    unsigned int rsc = GfBdatChrEnParam::get()->getChrEnParamResourceID(param);
    if (rsc == 0) {
        return nullptr;
    }
    return GfBdatRsc::get()->getRscEnModel(rsc);
}

bool GfDataEnemy::fn_7100235424(unsigned int rsc, unsigned int part) {
    return GfBdatRsc::get()->getRscEnExtraParts(rsc, part) == 2;
}

unsigned int GfDataEnemy::getSavedHp(unsigned int type) {
    SDataGame* game = GfDataManager::getDataGame();
    return game->m_enemySavedHp[type - 4];
}

void GfDataEnemy::setSavedHp(unsigned int type, unsigned int hp) {
    SDataGame* game = GfDataManager::getDataGame();
    game->m_enemySavedHp[type - 1] = hp;
}

void GfDataBlade::fn_71002355AC() {
    unsigned int count = GfGameFlag::getLocal(8, 0x874);
    if (count > 0xFE) {
        return;
    }
    GfGameFlag::setLocal(8, 0x874, count + 1);
}

bool GfDataBlade::isDummyBlade(unsigned int blade) {
    return blade - 1124 < 9 || blade - 1012 < 2 || blade == 1073 || blade == 1110;
}

unsigned int GfDataBlade::getBladeRelativeID(unsigned int blade) {
    unsigned int id = 0;
    if (blade - 1001 < 13) {
        id = blade - 1001;
    } else if (blade - 1014 < 176) {
        id = blade - 994;
    } else if (blade - 1197 < 226) {
        id = blade - 1001;
    }
    return id;
}

const char* GfDataMob::getAddMotionName(unsigned int mob) {
    const char* name = GfBdatRsc::get()->getRscMobListAddMotion(mob);
    if (name != nullptr && *name != '\0') {
        return name;
    }
    return nullptr;
}

bool GfDataHana::isEquipRoleParts(unsigned int hana, unsigned int item) {
    GfBdatItem* bdat = GfBdatItem::get();
    if (hana == 1005) {
        return bdat->isITM_HanaRoleFlagJS(item);
    }
    if (hana == 1006) {
        return bdat->isITM_HanaRoleFlagJK(item);
    }
    if (hana == 1007) {
        return bdat->isITM_HanaRoleFlagJD(item);
    }
    return false;
}

bool GfDataHana::isEquipAttributeParts(unsigned int hana, unsigned int item) {
    GfBdatItem* bdat = GfBdatItem::get();
    if (hana == 1005) {
        return bdat->isITM_HanaAtrFlagJS(item);
    }
    if (hana == 1006) {
        return bdat->isITM_HanaAtrFlagJK(item);
    }
    if (hana == 1007) {
        return bdat->isITM_HanaAtrFlagJD(item);
    }
    return false;
}

bool GfDataHana::isEquipArtsParts(unsigned int hana, unsigned int item) {
    GfBdatItem* bdat = GfBdatItem::get();
    if (hana == 1005) {
        return bdat->isITM_HanaArtsEnhFlagJS(item);
    }
    if (hana == 1006) {
        return bdat->isITM_HanaArtsEnhFlagJK(item);
    }
    if (hana == 1007) {
        return bdat->isITM_HanaArtsEnhFlagJD(item);
    }
    return false;
}

bool GfDataHana::isEquipNArtsParts(unsigned int hana, unsigned int item) {
    GfBdatItem* bdat = GfBdatItem::get();
    if (hana == 1005) {
        return bdat->isITM_HanaNArtsSetFlagJS(item);
    }
    if (hana == 1006) {
        return bdat->isITM_HanaNArtsSetFlagJK(item);
    }
    if (hana == 1007) {
        return bdat->isITM_HanaNArtsSetFlagJD(item);
    }
    return false;
}

bool GfDataHana::isEquipCondenserParts(unsigned int hana, unsigned int item) {
    GfBdatItem* bdat = GfBdatItem::get();
    if (hana == 1005) {
        return bdat->isITM_HanaAssistFlagJS(item);
    }
    if (hana == 1006) {
        return bdat->isITM_HanaAssistFlagJK(item);
    }
    if (hana == 1007) {
        return bdat->isITM_HanaAssistFlagJD(item);
    }
    return false;
}

bool GfDataFieldSkill::isFieldSkillSettingAccessed(unsigned int skill) {
    unsigned int start = QuestListAcc::get()->getFLD_FieldSkillSettingStart();
    unsigned int index = skill + 59675 - start;
    return GfGameFlag::getLocal(2, index) & 1;
}

void GfDataFieldSkill::setFieldSkillSettingAccessed(unsigned int skill) {
    unsigned int start = QuestListAcc::get()->getFLD_FieldSkillSettingStart();
    unsigned int index = skill + 59675 - start;
    GfGameFlag::setLocal(2, index, GfGameFlag::getLocal(2, index) | 1);
}

bool GfDataFieldSkill::isFieldSkillSettingComplete(unsigned int skill) {
    unsigned int start = QuestListAcc::get()->getFLD_FieldSkillSettingStart();
    unsigned int index = skill + 59675 - start;
    return GfGameFlag::getLocal(2, index) >> 1 & 1;
}

void GfDataFieldSkill::setFieldSkillSettingComplete(unsigned int skill) {
    unsigned int start = QuestListAcc::get()->getFLD_FieldSkillSettingStart();
    unsigned int index = skill + 59675 - start;
    GfGameFlag::setLocal(2, index, GfGameFlag::getLocal(2, index) | 2);
}

bool GfDataNanakoori::setVocalLevel(unsigned int level) {
    unsigned int old = GfGameFlag::getLocal(8, 0x84F);
    GfGameFlag::setLocal(8, 0x84F, level);
    return old != level;
}

bool GfDataNanakoori::setVisualLevel(unsigned int level) {
    unsigned int old = GfGameFlag::getLocal(8, 0x850);
    GfGameFlag::setLocal(8, 0x850, level);
    return old != level;
}

bool GfDataNanakoori::setSoulLevel(unsigned int level) {
    unsigned int old = GfGameFlag::getLocal(8, 0x851);
    GfGameFlag::setLocal(8, 0x851, level);
    return old != level;
}

bool GfDataNanakoori::setFan(unsigned int fan) {
    unsigned int old = GfGameFlag::getLocal(16, 0x60E);
    GfGameFlag::setLocal(16, 0x60E, fan);
    return old != fan;
}

unsigned int GfDataHana::getAutoHate(unsigned int hana) {
    GfBdatItem* bdat = GfBdatItem::get();
    SDataBlade& data = GfDataManager::getDataGame()->m_blades[GfDataBlade::getBladeIndex(hana)];
    return bdat->getITM_HanaRoleAutoHate(data.m_equipHana.m_roleParts);
}

unsigned int GfDataHana::getArtsHate(unsigned int hana) {
    GfBdatItem* bdat = GfBdatItem::get();
    SDataBlade& data = GfDataManager::getDataGame()->m_blades[GfDataBlade::getBladeIndex(hana)];
    return bdat->getITM_HanaRoleArtsHate(data.m_equipHana.m_roleParts);
}

void GfDataBladeCreate::addAssurePoint(unsigned int point) {
    unsigned int total = GfDataManager::getDataGame()->m_assurePoint + point;
    if (total < GfDataManager::getDataGame()->m_assurePoint) {
        total = 0xFFFFFFFF;
    }
    GfDataManager::getDataGame()->m_assurePoint = total;
}

void GfDataBladeCreate::addAssureCount(unsigned int count) {
    unsigned int total = GfDataManager::getDataGame()->m_assureCount + count;
    if (total < GfDataManager::getDataGame()->m_assureCount) {
        total = 0xFFFFFFFF;
    }
    GfDataManager::getDataGame()->m_assureCount = total;
}

const char* GfDataEnemy::getLoopEffect(unsigned int rsc) {
    if (rsc == 0) {
        return nullptr;
    }
    const char* name = GfBdatRsc::get()->getRscEnLoopEffect(rsc);
    if (name == nullptr) {
        return nullptr;
    }
    return *name == '\0' ? nullptr : name;
}

unsigned int GfDataEnBook::getDefeatNum(unsigned int arrange) {
    if (arrange == 0) {
        return 0;
    }
    unsigned int book = GfBdatChrEnArrange::get()->getChrEnArrangeBookID(arrange);
    if (book == 0) {
        return 0;
    }
    return GfGameFlag::getLocal(0x20, book + 0x142);
}

void GfDataEnBook::incDefeatNum(unsigned int arrange) {
    if (arrange == 0) {
        return;
    }
    unsigned int book = GfBdatChrEnArrange::get()->getChrEnArrangeBookID(arrange);
    if (book == 0) {
        return;
    }
    unsigned int num = GfGameFlag::getLocal(0x20, book + 0x142);
    if (num == 0xFFFFFFFF) {
        return;
    }
    GfGameFlag::setLocal(0x20, book + 0x142, num + 1);
}

void GfDataEnBook::incDeadNum(unsigned int arrange) {
    if (arrange == 0) {
        return;
    }
    unsigned int book = GfBdatChrEnArrange::get()->getChrEnArrangeBookID(arrange);
    if (book == 0) {
        return;
    }
    unsigned int num = GfGameFlag::getLocal(0x20, book + 0x52B);
    if (num == 0xFFFFFFFF) {
        return;
    }
    GfGameFlag::setLocal(0x20, book + 0x52B, num + 1);
}

bool GfDataEnemy::getExtraParts(unsigned int rsc, unsigned int part) {
    if (part > 3) {
        return true;
    }
    return GfBdatRsc::get()->getRscEnExtraParts(rsc, part) != 0;
}


int GfDataEvent::getEventType(unsigned int eventId) {
    if (eventId == 0) {
        return 0;
    }
    unsigned char* fp = GfDataBdat::getFP(fn_710024EBD8(eventId));
    if (fp == nullptr) {
        return 0;
    }
    return static_cast<unsigned char>(Bdat::getValCheck(fp, "category", eventId, 1));
}

int GfDataEvent::getEventAfterScriptStartID(unsigned int event) {
    unsigned char* fp = GfDataBdat::getFP(fn_710024EBD8(event));
    if (fp == nullptr) {
        return 0;
    }
    return static_cast<int>(Bdat::getValCheck(fp, "scriptStartId", event, 6));
}

const char* GfDataEvent::getEventAfterScriptName(unsigned int event) {
    unsigned char* fp = GfDataBdat::getFP(fn_710024EBD8(event));
    if (fp == nullptr) {
        return nullptr;
    }
    return reinterpret_cast<const char*>(Bdat::getValCheck(fp, "scriptName", event, 7));
}


SDataBlade* GfDataBlade::getSDataBlade(unsigned int blade) {
    return &GfDataManager::getDataGame()->m_blades[getBladeIndex(blade)];
}

unsigned int GfDataDriver::getDriverBySetBlade(unsigned int blade) {
    return GfDataManager::getDataGame()->m_blades[GfDataBlade::getBladeIndex(blade)].m_setDriver;
}

unsigned int GfDataDriver::fn_710023A9C8(unsigned int driver) {
    switch (driver) {
    case 1:
        return 0x3F4;
    case 7:
        return 0x3F5;
    case 9:
        return 0x431;
    case 12:
        return 0x456;
    default:
        return 0;
    }
}

bool GfDataBlade::isActivateParty(unsigned int blade) {
    if (blade == 0) {
        return false;
    }
    if (GfDataManager::getDataGame()->m_blades[getBladeIndex(blade)].m_dataType != 1) {
        return false;
    }
    unsigned int driver = GfDataManager::getDataGame()->m_blades[getBladeIndex(blade)].m_setDriver;
    return static_cast<unsigned int>(GfDataParty::getDriverPartyID(driver)) < 3;
}

bool GfDataBlade::getCommonBladeName(const char* path) {
    if (path == nullptr || strlen(path) < 6) {
        return false;
    }
    return strncmp(path, "bl/bl2", 6) == 0;
}

unsigned int GfDataBlade::getFavorite(unsigned int blade, FAVORITE favorite) {
    if (blade == 0) {
        return 0;
    }
    unsigned int index = getBladeIndex(blade);
    SDataGame* game = GfDataManager::getDataGame();
    SDataBlade& data = game->m_blades[index];
    switch (favorite) {
    case 2:
    case 3:
        return data.m_favorites[favorite - 2].m_item;
    }
    if (static_cast<unsigned int>(favorite) <= 1) {
        return data.m_favorites[favorite].m_category;
    }
    return 0;
}

SDataIdea* GfDataDriver::getSDataIdea(unsigned int driver) {
    return &getSDataDriver(driver)->m_idea;
}

bool GfDataDriver::isEnableLevelUp(unsigned int driver) {
    return fn_7100245C98(*getSDataDriver(driver));
}

unsigned int GfDataDriver::fn_7100245EA8(unsigned int driver) {
    return getExp(*getSDataDriver(driver));
}

unsigned int GfDataDriver::fn_7100245EFC(unsigned int driver) {
    return getBattleExp(*getSDataDriver(driver));
}

unsigned int GfDataDriver::fn_7100245F50(unsigned int driver) {
    return getBattleExpNextLevel(*getSDataDriver(driver));
}

unsigned int GfDataMap::getZoneIdForGameMap(unsigned int map) {
    unsigned int zone = getZoneIdForDevelopPoint(map);
    if (zone == 0) {
        return 0;
    }
    if (map == 15) {
        return 8;
    }
    return zone;
}

unsigned int GfDataHana::getEquipPowerRank(unsigned int hana) {
    return GfDataManager::getDataGame()->m_blades[GfDataBlade::getBladeIndex(hana)].m_hanaPowerRank;
}

void GfDataHana::setEquipPowerRank(unsigned int hana, unsigned int rank) {
    GfDataManager::getDataGame()->m_blades[GfDataBlade::getBladeIndex(hana)].m_hanaPowerRank = rank;
}

bool GfDataEnBook::isAttackFlag(unsigned int arrange) {
    if (arrange == 0) {
        return false;
    }
    unsigned int book = GfBdatChrEnArrange::get()->getChrEnArrangeBookID(arrange);
    if (book == 0) {
        return false;
    }
    return GfGameFlag::getLocal(1, book + 48590) != 0;
}

void GfDataEnBook::setAttackFlag(unsigned int arrange) {
    if (arrange == 0) {
        return;
    }
    unsigned int book = GfBdatChrEnArrange::get()->getChrEnArrangeBookID(arrange);
    if (book == 0) {
        return;
    }
    if (GfGameFlag::getLocal(1, book + 48590) != 0) {
        return;
    }
    GfGameFlag::setLocal(1, book + 48590, 1);
    for (unsigned int i = 1892; i < 2892; i++) {
        if (GfGameFlag::getLocal(0x10, i) == 0) {
            GfGameFlag::setLocal(0x10, i, (unsigned short)arrange);
            return;
        }
    }
}

bool GfDataQuest::getTitle(unsigned char*& fp, unsigned int& id, QuestID quest) {
    id = QuestListAcc::get()->getListQuestTitle(quest);
    if (id == 0) {
        return false;
    }
    fp = GfBdatMsg::getFpQuest(quest);
    return true;
}

bool GfDataBattle::getClassName(unsigned char*& fp, unsigned int& id, unsigned int cls) {
    if (cls == 0) {
        return false;
    }
    id = GfBdatBtl::get()->getBTL_ClassName(cls);
    if (id == 0) {
        return false;
    }
    fp = GfBdatMsg::getFpBtlClass();
    return true;
}

bool GfDataParty::isPartyMember(unsigned int chara) {
    return fn_710024BF60(chara, 10);
}

bool GfDataParty::isPartyBattleMember(unsigned int chara) {
    return fn_710024BF60(chara, 3);
}

void GfDataDriver::openDriverArtsForLevelup(unsigned int driver) {
    fn_7100244A44(driver, 0, true);
}

unsigned int GfDataDriver::fn_7100244E78(const SDataDriver& data, int slot) {
    if ((unsigned int)(data.m_id - 0x11) <= 8) {
        return GfBdatChrDr::get()->getChrDrDefBlade1(data.m_id);
    }
    if (slot < 0) {
        slot = data.m_bladeSet;
    }
    if (slot < 0) {
        return 0;
    }
    return data.m_blades[slot];
}

unsigned int GfDataParty::getFixedHandleForBlade(unsigned int driver, int index) {
    return driver * 5 + 3 + index;
}

bool GfDataBlade::getExtraParts(const SDataBlade& data, unsigned int part) {
    return data.m_extraParts[part] != 0;
}

SDataParty* GfDataParty::getSDataParty() {
    return &GfDataManager::getDataGame()->m_party;
}

mm::mtl::FixedVector<TaskAchieve, 128>* GfDataQuest::getTaskAchieve() {
    return &GfDataManager::getDataGame()->m_taskAchieve;
}

GfDataMercenaries::Preset* GfDataMercenaries::getPreset(unsigned int index) {
    return &GfDataManager::getDataGame()->m_mercenaryPresets[index];
}

unsigned int GfDataShop::getPrivilegeItem(unsigned int shop) {
    unsigned int bit = getItemBit(shop);
    if (bit == 0) {
        return 0;
    }
    GfBdatShop* bdat = GfBdatShop::get();
    unsigned int table = bdat->getShopListTableID(shop);
    unsigned int flag = GfBdatShop::get()->getShopNormalPrivilegeFlag(table);
    if (bit != GfGameFlag::getLocal(0x20, flag)) {
        return 0;
    }
    return bdat->getShopNormalPrivilegeItem(table);
}

void GfDataUtil::setChapterSave(unsigned int id, unsigned short value) {
    SDataGame* game = GfDataManager::getDataGame();
    game->m_chapterSaveValue = value;
    game->m_eventChapterSave = id;
}

void GfDataQuest::setScenario(QuestID id) {
    GfDataManager::getDataGame()->m_scenario = id;
}

void GfDataQuest::setSelect(QuestID id) {
    GfDataManager::getDataGame()->m_select = id;
}

const char* GfDataMap::getMapResourceName(unsigned int mapId) {
    unsigned int id = getMapID(mapId);
    if (id == 0) {
        return "";
    }
    return GfBdatMaplist::get()->getMaplistresource(id);
}

const char* GfDataDriver::getBelongingModelName(const GfInitParamDriver& param) {
    if (param.m_objId == 1) {
        return param.m_createType == 9 || param.m_createType == 13 ? "oj/oj300002" : "oj/oj300001";
    }
    return nullptr;
}

unsigned int GfDataMercenaries::getRewardAchievmentRatio() {
    unsigned int ratio = QuestListAcc::get()->getFLD_MercenariesConfigValue(16);
    return GfGameFlag::getLocal(4, 2) * 5 + ratio;
}

bool GfDataMercenaries::getMsgTitleName(unsigned char*& bdat, unsigned int& id, unsigned int mission) {
    if (mission == 0) {
        return false;
    }
    return GfDataQuest::getTitle(bdat, id, getMissionQuestID(mission));
}

bool GfDataNanakoori::isMissionComplete(unsigned int mission) {
    unsigned int flag = getNanakooriMissionClearFlg1Offset(mission);
    if (flag == 0) {
        return true;
    }
    return GfGameFlag::getLocal(1, flag) != 0;
}

bool GfDataParty::isLeader(unsigned int chara) {
    if (chara == 0) {
        return false;
    }
    return GfDataManager::getDataGame()->m_party.m_leader == chara;
}

float GfDataUtil::getMoveDistance(AMOVE move) {
    SDataGame* game = GfDataManager::getDataGame();
    return move == 0 ? game->m_moveDistance[0] : game->m_moveDistance[1];
}

void GfDataUtil::setMoveDistance(AMOVE move, float distance) {
    SDataGame* game = GfDataManager::getDataGame();
    switch (move) {
    case 0:
        game->m_moveDistance[0] = distance;
        break;
    case 1:
        game->m_moveDistance[1] = distance;
        break;
    }
}

bool GfDataBlade::isRareBlade(unsigned int blade) {
    return blade >= 1014 && blade < GfBdatChrBl::get()->getChrBlEnd();
}

bool GfDataDriver::isExistBlade(unsigned int driver) {
    mm::mtl::FixedVector<unsigned short, 422> list;
    return getListBlade(list, driver);
}

mm::Vec3* GfDataParty::getSavePos(unsigned int index, bool flag) {
    SDataGame* game = GfDataManager::getDataGame();
    if (flag) {
        return &game->m_savePos[index];
    }
    return &game->m_savePos2[index];
}

mm::Vec3* GfDataParty::getSaveRot(unsigned int index, bool flag) {
    SDataGame* game = GfDataManager::getDataGame();
    if (flag) {
        return &game->m_saveRot[index];
    }
    return &game->m_saveRot2[index];
}

unsigned int GfDataEnemy::getRscIdByArrangeId(unsigned int arrange) {
    unsigned int param = GfBdatChrEnArrange::get()->getChrEnArrangeParamID(arrange);
    if (param == 0) {
        return 0;
    }
    return GfBdatChrEnParam::get()->getChrEnParamResourceID(param);
}

const char* GfDataEnemy::getVoiceStr(unsigned int arrange) {
    unsigned int param = GfBdatChrEnArrange::get()->getChrEnArrangeParamID(arrange);
    if (param == 0) {
        return nullptr;
    }
    unsigned int rsc = GfBdatChrEnParam::get()->getChrEnParamResourceID(param);
    if (rsc == 0) {
        return nullptr;
    }
    return GfBdatRsc::get()->getRscEnVoice(rsc);
}

unsigned int GfDataQuest::getListQuestCategory(QuestID id) {
    unsigned int quest = id.m_id;
    if (quest == 0) {
        return 0;
    }
    if (quest < 1000) {
        return 1;
    }
    if (quest < 5000) {
        return 3;
    }
    if (quest < 6000) {
        return 2;
    }
    if (quest < 7000) {
        return 5;
    }
    return 6;
}

void SDataIdea::setPoint(unsigned int idea, unsigned int point) {
    Idea& data = m_ideas[idea];
    data.m_point = point;
    data.m_level = GfDataIdea::calcLevel(point);
}

void SDataIdea::setLevel(unsigned int idea, int level) {
    m_ideas[idea].m_level = level;
    unsigned int point = 0;
    if (level >= 0 && level <= 10u) {
        point = GfBdatBlade::get()->getBLD_IdeaNeedPoint(level);
    }
    m_ideas[idea].m_point = point;
}

bool GfDataEvent::isSaveScenarioEvent(unsigned int event) {
    // Proposed name, not the original's: the symbols leave it unnamed (lbl_71009BA1BE)
    static const unsigned short s_saveScenarioEvents[] = {
        10001, 10003, 10007, 10008, 10009, 10011, 10012, 10013, 10015, 10018, 10022, 10023,
        10025, 10026, 10029, 10032, 10033, 10035, 10037, 10039, 10043, 10044, 10049, 10051,
        10052, 10055, 10058, 10062, 10064, 10067, 10068, 10069, 10072, 10073, 10075, 10076,
        10077, 10078, 10079, 10082, 10085, 10086, 10090, 10091, 10092, 10093, 10094, 10095,
        10096, 10097, 10098, 10099, 10100, 10102, 10105, 10106, 10108, 10109, 10110, 10112,
        10113, 10114, 10116, 10119, 10125, 10128, 10130, 10131, 10139, 10140, 10141, 10145,
        10146, 10148, 10149, 10150, 10151, 10152, 10153, 10154, 10156, 10157, 10159, 10162,
        10163, 10164, 10165, 10168, 10172, 10173, 10174, 10176, 10178, 10179, 10180, 10181,
        10182, 10185, 10186, 10188, 10189, 10191, 10195, 10200, 10201, 10202, 10204, 10205,
        10206, 10211, 10212, 10214, 10215, 10216, 10220, 10225, 10230, 10231, 10232, 10233,
        10235, 10236, 10237, 10239, 10240, 10242, 10246, 10252, 10253, 10256, 10259, 10261,
        10262, 10263, 10264, 10265, 10266, 10270, 10276, 10277, 10278, 10279, 10280, 10286,
        10287, 10289, 10290, 10295, 10297, 10300, 10303, 10304, 10306, 10314, 10318, 10319,
        10325, 10326, 10327, 10333, 10334, 10335, 10336, 10344, 10345, 10348, 10350, 10355,
        10360, 10361, 10362, 10363, 10366, 10367, 10370, 10371, 10372, 10376, 10381, 10382,
        10384, 10386, 10391, 10392, 10395, 10397, 10399, 10400, 10404, 10405, 10406, 10410,
        10411, 10418, 10428, 10433, 10437, 10439, 10444, 10451, 10456, 10458, 10461, 10463,
        10464, 10465, 10468, 10471, 10473, 10485, 10488, 10491, 10494,
    };
    for (unsigned int i = 0; i < 213; i++) {
        if (s_saveScenarioEvents[i] == event) {
            return true;
        }
    }
    return false;
}

void GfDataEvent::fn_710024F2B8(unsigned int event) {
    fn_710024F2DC(*GfDataManager::getDataGame(), event);
}

// the event theater row of event (0 when none; F2DC and F454 inline it)
static inline unsigned int findEventTheaterRow(unsigned int event) {
    GfBdatShop* bdat = GfBdatShop::get();
    for (unsigned int i = bdat->getMNU_EventTheaterStart(), end = bdat->getMNU_EventTheaterEnd(); i < end; i++) {
        if (bdat->getMNU_EventTheaterevent_id(i) == event) {
            return i;
        }
    }
    return 0;
}

// true when event's event theater row has category 2 (fn_710024F2DC inlines it)
static inline bool isEventTheaterCategory2(GfBdatShop* bdat, unsigned int event) {
    for (unsigned int i = bdat->getMNU_EventTheaterStart(), end = bdat->getMNU_EventTheaterEnd(); i < end; i++) {
        if (bdat->getMNU_EventTheaterevent_id(i) == event) {
            return bdat->getMNU_EventTheatercategory(i) == 2;
        }
    }
    return false;
}

void GfDataEvent::fn_710024F2DC(SDataGame& game, unsigned int event) {
    GfBdatShop* bdat = GfBdatShop::get();
    if (event == 0x5461) {
        event = 0x5462;
    }
    unsigned int base;
    if (event - 0x50E3 < 0x1F8 || isEventTheaterCategory2(bdat, event)) {
        base = 0xB6C2;
    } else if (event - 0x4A39 <= 0x3C) {
        base = 0xB78B;
    } else {
        return;
    }
    unsigned int row = findEventTheaterRow(event);
    if (row == 0) {
        return;
    }
    unsigned int index = bdat->getMNU_EventTheaterflag_index(row);
    if (index == 0) {
        return;
    }
    GfGameFlag::setLocal(game.m_gameFlag, 1, index + base, 1);
}

bool GfDataEvent::fn_710024F430(unsigned int event) {
    return fn_710024F454(*GfDataManager::getDataGame(), event);
}

bool GfDataEvent::fn_710024F454(const SDataGame& game, unsigned int event) {
    GfBdatShop* bdat = GfBdatShop::get();
    unsigned int base;
    if (event - 0x50E3 < 0x1F8) {
        base = 0xB6C2;
    } else {
        bool category2 = false;
        for (unsigned int i = bdat->getMNU_EventTheaterStart(), end = bdat->getMNU_EventTheaterEnd(); i < end; i++) {
            if (bdat->getMNU_EventTheaterevent_id(i) == event) {
                category2 = bdat->getMNU_EventTheatercategory(i) == 2;
                break;
            }
        }
        if (category2) {
            base = 0xB6C2;
        } else if (event - 0x4A39 <= 0x3C) {
            base = 0xB78B;
        } else {
            return false;
        }
    }
    unsigned int row = findEventTheaterRow(event);
    if (row == 0) {
        return false;
    }
    unsigned int index = bdat->getMNU_EventTheaterflag_index(row);
    if (index == 0) {
        return false;
    }
    return game.m_gameFlag.m_flag1[index + base];
}

bool GfDataEvent::isSavedEvent(unsigned int event, const SDataGame& game) {
    for (unsigned int i = 0; i < game.m_savedEventCount; i++) {
        if (game.m_savedEvents[i].m_event == event) {
            return true;
        }
    }
    return false;
}

bool GfDataEvent::fn_710024F910(unsigned int event) {
    unsigned char* fp = GfDataBdat::getFP(fn_710024EBD8(event));
    if (fp == nullptr) {
        return false;
    }
    return static_cast<bool>(static_cast<unsigned char>(Bdat::getValCheck(fp, "noRetarget", event, 1)));
}


unsigned int GfDataItem::getTypeByItemCategory(unsigned int category) {
    if (category < 4) {
        return 11;
    }
    if (category < 12) {
        return 7;
    }
    if (category < 24) {
        return 10;
    }
    if (category < 28) {
        return 8;
    }
    if (category < 30) {
        return 6;
    }
    return 0;
}

unsigned int GfDataMercenaries::getReserverMax() {
    unsigned int level = GfGameFlag::getLocal(4, 2);
    return level * 24 + (GfDataManager::getDataGame()->m_gameClearCount != 0 ? 48 : 0) + 24;
}

int GfDataBlade::fn_710023C478(const SDataGame& game, unsigned int blade) {
    if (blade == 0) {
        return 0;
    }
    return game.m_blades[getBladeIndex(blade)].m_creator;
}



const EquipHana* GfDataHana::getEquipParts(unsigned int hana) {
    return &GfDataManager::getDataGame()->m_blades[GfDataBlade::getBladeIndex(hana)].m_equipHana;
}

void GfDataHana::setEquipParts(unsigned int hana, const EquipHana& equip) {
    GfDataManager::getDataGame()->m_blades[GfDataBlade::getBladeIndex(hana)].m_equipHana = equip;
}

void EquipHana::setArtsParts(unsigned int item, unsigned int handle, unsigned int slot) {
    Parts& parts = m_artsParts[slot];
    parts.m_item = item;
    parts.m_handle = handle;
    parts.m_value = GfBdatItem::get()->getITM_HanaArtsEnhEnhance(item);
}

void EquipHana::setNArtsParts(unsigned int item, unsigned int handle, unsigned int slot) {
    Parts& parts = m_nArtsParts[slot];
    parts.m_item = item;
    parts.m_handle = handle;
    parts.m_value = GfBdatItem::get()->getITM_HanaNArtsSetNArts(item);
    parts.m_value2 = GfBdatItem::get()->getITM_HanaNArtsSetNArtsRecastRev(item);
}

int GfDataHana::getEquipPower(unsigned int hana) {
    return getEquipPower(*getEquipParts(hana));
}

int GfDataHana::getEquipPower(const EquipHana& equip) {
    GfBdatItem* bdat = GfBdatItem::get();
    int power = 0;
    if (equip.m_roleParts != 0) {
        power = bdat->getITM_HanaRoleNeedPow(equip.m_roleParts);
    }
    if (equip.m_attributeParts != 0) {
        power += bdat->getITM_HanaAtrNeedPow(equip.m_attributeParts);
    }
    for (int i = 0; i < 3; i++) {
        if (equip.m_artsParts[i].m_value != 0) {
            power += bdat->getITM_HanaArtsEnhNeedPow(equip.m_artsParts[i].m_item);
        }
    }
    for (int i = 0; i < 3; i++) {
        if (equip.m_nArtsParts[i].m_value != 0) {
            power += bdat->getITM_HanaNArtsSetNeedPow(equip.m_nArtsParts[i].m_item);
        }
    }
    for (int i = 0; i < 6; i++) {
        if (equip.m_condenserParts[i] != 0) {
            power += bdat->getITM_HanaAssistNeedPow(equip.m_condenserParts[i]);
        }
    }
    return power;
}

bool GfDataFieldSkill::getName(unsigned char*& bdat, unsigned int& id, unsigned int skill) {
    if (skill == 0) {
        return false;
    }
    id = QuestListAcc::get()->getFLD_FieldSkillListName(skill);
    bdat = GfBdatMsg::getFpFieldSkill();
    return id != 0;
}

bool GfDataFieldSkill::getCaption(unsigned char*& bdat, unsigned int& id, unsigned int skill) {
    if (skill == 0) {
        return false;
    }
    id = QuestListAcc::get()->getFLD_FieldSkillListCaption(skill);
    bdat = GfBdatMsg::getFpFieldSkill();
    return id != 0;
}

bool GfDataWeapon::getName(unsigned char*& bdat, unsigned int& id, unsigned int weapon) {
    GfBdatItem* item = GfBdatItem::get();
    bdat = nullptr;
    id = item->getPcWpnName(weapon);
    bdat = GfBdatMsg::getFpPcWpn();
    return id != 0 && bdat != nullptr;
}

bool GfDataBlade::getMercenaryName(unsigned char*& bdat, unsigned int& id, unsigned int blade) {
    if (blade - 1197 < 226) {
        return false;
    }
    id = GfBdatChrBl::get()->getChrBlMerceName(blade);
    bdat = GfBdatMsg::getFpMerceName();
    return id != 0;
}

unsigned int GfDataBlade::getVoiceID(unsigned int blade) {
    unsigned int personality = getSDataBlade(blade)->m_personality;
    if (personality == 0) {
        return 0;
    }
    return GfBdatBtl::get()->getBTL_Bl_PersonalityVoiceID(personality);
}

bool GfDataMercenaries::getMsgZoneName(unsigned char*& bdat, unsigned int& id, unsigned int mission) {
    unsigned int map = getMissionMapID(mission);
    if (map == 0) {
        return false;
    }
    id = GfBdatMaplist::get()->getMaplistnameID(map);
    bdat = GfBdatMsg::getFpMapInfo();
    return id != 0;
}

bool GfDataMercenaries::getMsgSummaryName(unsigned char*& bdat, unsigned int& id, unsigned int mission) {
    if (mission == 0) {
        return false;
    }
    QuestID quest = getMissionQuestID(mission);
    id = QuestListAcc::get()->getListSummary(quest);
    if (id == 0) {
        return false;
    }
    bdat = GfBdatMsg::getFpQuest(quest);
    return true;
}

void GfDataBlade::setCreator(unsigned int blade, unsigned int creator) {
    if (blade == 0) {
        return;
    }
    getSDataBlade(blade)->m_creator = creator;
    // blade 1050 shares its creator with blade 1022
    if (blade == 1050) {
        getSDataBlade(1022)->m_creator = creator;
    }
}

int GfDataBlade::getCreator(unsigned int blade) {
    if (blade == 0) {
        return 0;
    }
    return GfDataManager::getDataGame()->m_blades[getBladeIndex(blade)].m_creator;
}

bool GfDataBlade::isActivateMercenaryTeam(unsigned int blade) {
    return GfDataManager::getDataGame()->m_blades[getBladeIndex(blade)].m_activateMercenaryTeam != 0;
}

void GfDataBlade::fn_7100239934(unsigned int blade, bool flag) {
    unsigned int index = getBladeIndex(blade);
    SDataGame* game = GfDataManager::getDataGame();
    game->m_blades[index].m_activateMercenaryTeam = flag;
}

const char* GfDataBlade::getCommonBladeName(unsigned int blade) {
    unsigned int name = GfBdatBlade::get()->getNameListCategory(blade);
    unsigned char* fp = GfBdatMsg::getFpCommonBladeName();
    const char* text = name != 0 ? Bdat::getMSText(fp, name) : nullptr;
    return text == nullptr ? "" : text;
}

unsigned int GfDataMercenaries::getMissionZoneID(unsigned int mission) {
    unsigned int map = getMissionMapID(mission);
    if (map == 0) {
        return 0;
    }
    return GfDataMap::getZoneIdForGameMap(map);
}

unsigned int GfDataMercenaries::getMissionByQuestID(QuestID quest) {
    for (unsigned int mission = getStartMissionID(); mission < getEndMissionID(); mission++) {
        if (quest == getMissionQuestID(mission)) {
            return mission;
        }
    }
    return 0;
}

bool GfDataMercenaries::isMissionOrderParty(unsigned int mission) {
    if (mission == 0) {
        return false;
    }
    if (isMissionOrderTeam(mission)) {
        return false;
    }
    switch (GfGameFlag::getLocal(4, mission + 5)) {
    case 2:
    case 3:
        return true;
    }
    return false;
}

bool GfDataMercenaries::isMissionOrderTeam(unsigned int mission) {
    return getTeamIDByMissionID(mission) != 0;
}

bool GfDataBlade::fn_71002383C8(unsigned int blade) {
    if (blade == 0) {
        return false;
    }
    return GfDataManager::getDataGame()->m_blades[getBladeIndex(blade)].m_dataType == 2;
}

QuestID GfDataQuest::getListNextQuestA(QuestID id) {
    if (!id.empty()) {
        unsigned short next = QuestListAcc::get()->getListNextQuestA(id);
        if (next != 30000 && next != 30001) {
            QuestID quest;
            quest.m_id = next;
            quest.m_achieveId = id.m_achieveId;
            return quest;
        }
    }
    return QuestID();
}

QuestID GfDataQuest::getListNextQuestB(QuestID id) {
    if (!id.empty()) {
        unsigned short next = QuestListAcc::get()->getListNextQuestB(id);
        if (next != 30000 && next != 30001) {
            QuestID quest;
            quest.m_id = next;
            quest.m_achieveId = id.m_achieveId;
            return quest;
        }
    }
    return QuestID();
}

bool GfDataParty::empty() {
    for (int i = 0; i < 3; i++) {
        if (GfDataManager::getDataGame()->m_party.m_members[i].m_driver != 0) {
            return false;
        }
    }
    return true;
}

unsigned int GfDataHana::getRole(unsigned int hana) {
    GfBdatItem* bdat = GfBdatItem::get();
    SDataBlade& data = GfDataManager::getDataGame()->m_blades[GfDataBlade::getBladeIndex(hana)];
    return bdat->getITM_HanaRoleRole(data.m_equipHana.m_roleParts);
}

bool GfDataDriver::isActivateUnuse(unsigned int driver) {
    return getSDataDriver(driver)->m_dataType == 0;
}

void GfDataDriver::fn_71002447AC(SDataDriver& data, unsigned int level) {
    unsigned int driver = data.m_id;
    if (driver - 0x11 < 9) {
        GfBdatChrDr* bdat = GfBdatChrDr::get();
        if (bdat->fn_71001F16A4(bdat->fn_71001F13E0(data.m_id)) != 0) {
            fn_71002447AC(*getSDataDriver(fn_71002417DC(data.m_id)), level);
            return;
        }
    }
    data.m_level = level;
    calcDriverBaseParamByLevel(data);
}

void GfDataDriver::fn_710024487C(unsigned int driver, unsigned int level) {
    fn_71002447AC(*getSDataDriver(driver), level);
}

void GfDataDriver::fn_71002448D8(unsigned int driver, unsigned int exp) {
    if (driver - 0x11 < 9) {
        GfBdatChrDr* bdat = GfBdatChrDr::get();
        if (bdat->fn_71001F16A4(bdat->fn_71001F13E0(driver)) != 0) {
            fn_71002448D8(fn_71002417DC(driver), exp);
            return;
        }
    }
    getSDataDriver(driver)->m_exp = exp;
}

void GfDataDriver::fn_7100244988(unsigned int driver, unsigned int exp) {
    if (driver - 0x11 < 9) {
        GfBdatChrDr* bdat = GfBdatChrDr::get();
        if (bdat->fn_71001F16A4(bdat->fn_71001F13E0(driver)) != 0) {
            fn_7100244988(fn_71002417DC(driver), exp);
            return;
        }
    }
    getSDataDriver(driver)->m_battleExp = exp;
}

bool GfDataMercenaries::isEnableOrder(unsigned int mission) {
    if (mission == 0) {
        return true;
    }
    unsigned int state = GfGameFlag::getLocal(4, mission + 5);
    if (state == 0) {
        return true;
    }
    QuestListAcc* acc = QuestListAcc::get();
    if (state == 4) {
        return acc->getFLD_MercenariesMissionRepeatable(mission) != 0;
    }
    return false;
}

void GfDataNanakoori::setMissionComplete(unsigned int mission) {
    unsigned int flag = getNanakooriMissionClearFlg1Offset(mission);
    if (flag == 0 || GfGameFlag::getLocal(1, flag) != 0) {
        return;
    }
    flag = getNanakooriMissionClearFlg1Offset(mission);
    if (flag != 0) {
        GfGameFlag::setLocal(1, flag, 1);
    }
}

unsigned int GfDataBlade::getBladeID(unsigned int index) {
    if (index < 20) {
        unsigned int blade = index + 1001;
        return blade > 1013 ? 0 : blade;
    }
    if (index < 196) {
        unsigned int blade = index + 994;
        return blade < GfBdatChrBl::get()->getChrBlEnd() ? blade : 0;
    }
    return index < 422 ? index + 1001 : 0;
}


int GfDataHana::getAttribute(unsigned int hana) {
    SDataBlade& data = GfDataManager::getDataGame()->m_blades[GfDataBlade::getBladeIndex(hana)];
    if (data.m_equipHana.m_attributeParts == 0) {
        return 0;
    }
    return GfBdatItem::get()->getITM_HanaAtrAtr(data.m_equipHana.m_attributeParts);
}

int GfDataHana::getPowerCapacity(unsigned int hana) {
    SDataBlade& data = GfDataManager::getDataGame()->m_blades[GfDataBlade::getBladeIndex(hana)];
    unsigned int rank = data.m_hanaPowerRank;
    return GfBdatBtl::get()->getBTL_HanaPowerPowerNum(rank, hana - 1005);
}

bool GfDataHana::isOpenCircuit(unsigned int hana, unsigned int circuit) {
    SDataBlade& data = GfDataManager::getDataGame()->m_blades[GfDataBlade::getBladeIndex(hana)];
    return (data.m_openCircuit & (1 << circuit)) != 0;
}

unsigned int GfDataBlade::getBladePower(unsigned int blade) {
    if (blade == 0) {
        return 0;
    }
    return getBladePower(GfDataManager::getDataGame()->m_blades[getBladeIndex(blade)]);
}

int GfDataDriver::getBladeSet(unsigned int driver) {
    if (driver == 0) {
        return -1;
    }
    return getBladeSet(*getSDataDriver(driver));
}

bool GfDataDriver::isScenarioMask(unsigned int driver) {
    if (driver == 0) {
        return false;
    }
    return getSDataDriver(driver)->m_scenarioMask == 1;
}

unsigned int GfDataWeapon::getNewWeapon(unsigned int weapon, unsigned int chip) {
    GfBdatItem* bdat = GfBdatItem::get();
    unsigned int type = bdat->getPcWpnWpnType(weapon);
    if (type < 37 || type - 1 < 16) {
        return bdat->getPcWpnChipCreateWpn(chip, type - 1);
    }
    return 0;
}

bool GfDataDriver::fn_71002491D4(unsigned int driver) {
    if (driver == 0) {
        return false;
    }
    return getSDataDriver(driver)->m_defaultAcceDone;
}

int GfDataDriver::getMaxSetBladeNum(unsigned int driver) {
    if (driver == 0) {
        return 0;
    }
    return getMaxSetBladeNum(*getSDataDriver(driver));
}

unsigned char* GfDataItem::getFavoriteItemType() {
    return GfDataManager::getDataGame()->m_favoriteItemType;
}

unsigned char* GfDataItem::getItemBox() {
    return GfDataManager::getDataGame()->m_itemBox;
}

unsigned short GfDataBlade::fn_7100231EB8(const SDataGame& game) {
    return GfGameFlag::getLocal(game.m_gameFlag, 0x10, 1);
}

bool GfDataBlade::fn_7100232244(const SDataGame& game) {
    return GfGameFlag::getLocal(game.m_gameFlag, 1, 0xD791) != 0;
}

bool GfDataBlade::fn_7100235F94(const SDataGame& game) {
    return GfGameFlag::getLocal(game.m_gameFlag, 1, 0x89FB) != 0;
}

bool GfDataBlade::fn_7100232054(const SDataGame& game) {
    return GfGameFlag::getLocal(game.m_gameFlag, 1, 0xBDCD) != 0 || GfGameFlag::getLocal(game.m_gameFlag, 1, 0xD880) != 0;
}

bool GfDataBlade::fn_71002320C8(const SDataGame& game) {
    return GfGameFlag::getLocal(game.m_gameFlag, 1, 0xD793) != 0 || GfGameFlag::getLocal(game.m_gameFlag, 1, 0xD882) != 0;
}

bool GfDataBlade::fn_710023217C(const SDataGame& game) {
    return GfGameFlag::getLocal(game.m_gameFlag, 1, 0xD77E) != 0 || GfGameFlag::getLocal(game.m_gameFlag, 1, 0xD87E) != 0;
}

bool GfDataBlade::fn_7100231FF8() {
    return fn_7100232054(*GfDataManager::getDataGame());
}

bool GfDataBlade::fn_7100232120() {
    return fn_710023217C(*GfDataManager::getDataGame());
}

bool GfDataBlade::fn_7100232290() {
    return GfGameFlag::getLocal(GfDataManager::getDataGame()->m_gameFlag, 1, 0xD795) != 0;
}

bool GfDataBlade::fn_71002324C8() {
    return GfGameFlag::getLocal(GfDataManager::getDataGame()->m_gameFlag, 1, 0xD860) != 0;
}

bool GfDataBlade::fn_710023220C() {
    return fn_7100231884() > 0xBE7;
}

bool GfDataBlade::fn_710024E91C() {
    return fn_7100231884() > 0x1F64;
}

bool GfDataBlade::fn_710024E9A8() {
    return GfGameFlag::getLocal(1, 0xD862) != 0;
}

bool GfDataBlade::fn_710024E9DC() {
    return GfGameFlag::getLocal(1, 0xD863) != 0;
}

unsigned int GfDataBlade::fn_710024DD88() {
    return GfGameFlag::getLocal(4, 652);
}

unsigned int GfDataBlade::fn_710024DD94(unsigned int id) {
    if (id > 2000) {
        unsigned int flag = GfBdatRsc::get()->fn_7100219C58(id);
        if (flag != 0) {
            return GfGameFlag::getLocal(2, flag);
        }
    }
    return 0;
}

bool GfDataBlade::fn_710024DE6C(unsigned int id) {
    if (id <= 2000) {
        return false;
    }
    unsigned int flag = GfBdatRsc::get()->fn_7100219CE0(id);
    if (flag == 0) {
        return false;
    }
    return GfGameFlag::getLocal(1, flag) != 0;
}

bool GfDataBlade::fn_710024DED0(unsigned int id) {
    if (id <= 2000) {
        return false;
    }
    unsigned int flag = GfBdatRsc::get()->fn_7100219C58(id);
    if (flag == 0) {
        return false;
    }
    unsigned int value = GfGameFlag::getLocal(2, flag);
    return value == 1 || value == 3;
}

void GfDataBlade::fn_710024DF38(unsigned int id, bool value) {
    unsigned int flag;
    if (id <= 2000) {
        flag = 0;
    } else {
        flag = GfBdatRsc::get()->fn_7100219CE0(id);
    }
    GfGameFlag::setLocal(1, flag + 2160, value);
}

bool GfDataBlade::fn_710024DF88(unsigned int id) {
    unsigned int flag;
    if (id <= 2000) {
        flag = 0;
    } else {
        flag = GfBdatRsc::get()->fn_7100219CE0(id);
    }
    return GfGameFlag::getLocal(1, flag + 2160) != 0;
}

void GfDataBlade::fn_710024E9CC(bool flag) {
    GfGameFlag::setLocal(1, 0xD862, flag);
}

void GfDataBlade::fn_710024EA00(bool flag) {
    GfGameFlag::setLocal(1, 0xD863, flag);
}

unsigned int GfDataEvent::fn_710024ED1C(unsigned int event) {
    unsigned char* fp = GfDataBdat::getFP(fn_710024EBD8(event));
    if (fp == nullptr) {
        return 0;
    }
    return static_cast<unsigned short>(Bdat::getValCheck(fp, "scenarioFlag", event, 2));
}

void GfDataBlade::fn_71002321D4(bool flag) {
    GfGameFlag::setLocal(1, 0xD77E, flag);
    GfGameFlag::setLocal(1, 0xD87E, flag);
}

void GfDataBlade::fn_7100232274(SDataGame* game, bool flag) {
    GfGameFlag::setLocal(game->m_gameFlag, 1, 0xD791, flag);
}

void GfDataBlade::fn_71002322C4(SDataGame* game, bool flag) {
    GfGameFlag::setLocal(game->m_gameFlag, 1, 0xD795, flag);
}

void GfDataBlade::fn_71002324FC(SDataGame* game, bool flag) {
    GfGameFlag::setLocal(game->m_gameFlag, 1, 0xD860, flag);
}

unsigned int GfDataBlade::fn_71002326F0(unsigned int id) {
    GfBdatBtl* bdat = GfBdatBtl::get();
    if (fn_71002324C8()) {
        return bdat->fn_71001E77DC(id);
    }
    return bdat->getGrowLevelExp(id);
}

bool GfDataBlade::fn_710023182C() {
    SDataGame* game = GfDataManager::getDataGame();
    unsigned short value = game->m_chapterSaveValue;
    bool same = value == fn_7100231884();
    bool saved = game->m_eventChapterSave != 0;
    return same && saved;
}

bool GfDataDriver::fn_7100238094(unsigned int driver) {
    return driver != 0 && getSDataDriver(driver)->m_dataType == 1;
}

unsigned int GfDataDriver::fn_7100247E28(unsigned int driver) {
    return getSkillPoint(*getSDataDriver(driver));
}

void GfDataDriver::setScenarioMask(unsigned int driver, bool mask) {
    getSDataDriver(driver)->m_scenarioMask = mask;
}

unsigned int GfDataDriver::getEquipAcce(unsigned int driver, unsigned int slot) {
    return getEquipAcce(*getSDataDriver(driver), slot);
}

unsigned int GfDataBlade::fn_7100231754() {
    return 1397;
}

void GfDataBlade::fn_710023493C() {
}

unsigned int GfDataBlade::fn_7100234940(unsigned int enemy) {
    if (enemy == 0) {
        return 0;
    }
    if (enemy >= 1500) {
        return GfDataManager::getDataGame()->m_enemySuppressCount[static_cast<int>(enemy) - 1500];
    }
    return GfGameFlag::getLocal(16, enemy + 0x2E);
}

bool GfDataBlade::fn_7100234998(unsigned int enemy) {
    if (enemy == 0) {
        return false;
    }
    unsigned int count = fn_7100234940(enemy);
    if (count < 0xFFFF) {
        count++;
        if (enemy >= 1500) {
            GfDataManager::getDataGame()->m_enemySuppressCount[static_cast<int>(enemy) - 1500] = count;
        } else {
            GfGameFlag::setLocal(16, enemy + 0x2E, count);
        }
        return true;
    }
    return false;
}

bool GfDataBlade::fn_71002327B0(unsigned int id) {
    return id - 25501 < 499;
}

bool GfDataBlade::fn_71002364B8(unsigned int blade) {
    return blade - 1124 < 9;
}

unsigned int GfDataBlade::fn_7100236518(unsigned int blade) {
    switch (blade) {
    case 1124:
        return 17;
    case 1125:
        return 18;
    case 1126:
        return 19;
    case 1127:
        return 20;
    case 1128:
        return 21;
    case 1129:
        return 22;
    case 1130:
        return 23;
    case 1131:
        return 24;
    case 1132:
        return 25;
    default:
        return 0;
    }
}

const char* GfDataBlade::getName(const SDataBlade& data, unsigned int kind) {
    const char* name = nullptr;
    unsigned int id = data.m_bladeId;
    if (id != 0) {
        unsigned int msg = kind;
        unsigned char* fp;
        if (kind != 0) {
            if (id < GfBdatChrBl::get()->getChrBlEnd()) {
                fp = GfDataBdat::getFP(423);
            } else {
                fp = GfDataBdat::getFP(396);
            }
        } else if (data.m_nameMsg != 0) {
            msg = data.m_nameMsg;
            fp = GfDataBdat::getFP(423);
        } else {
            msg = data.m_nameMsgAlt;
            fp = GfDataBdat::getFP(396);
        }
        if (msg != 0) {
            name = Bdat::getMSText(fp, msg);
        }
    }
    return name == nullptr ? "" : name;
}

bool GfDataBlade::fn_710024F258(unsigned int id) {
    return id - 10001 < 744;
}

bool GfDataBlade::fn_710023384C(unsigned int id) {
    switch (id) {
    case 40260: case 40261: case 40262: case 40263: case 40264: case 40265: case 40266: case 40267: case 40268:
    case 40312:
        return true;
    default:
        return false;
    }
}

unsigned int GfDataDriver::getDeathBlowEfbFileIdx(DBSLOT slot, int index) {
    int idx = index >= 0 ? slot * 5 + index : slot + 1;
    return idx + 0x881;
}

unsigned int GfDataDriver::getDeathBlowEabFileIdx(DBSLOT slot, int index) {
    int idx = index >= 0 ? slot * 5 + index : slot + 1;
    return idx + 0x498;
}

GfItemHandle GfDataDriver::fn_71002474B0(unsigned int driver) {
    if (driver - 0x11 < 9) {
        return GfDataManager::fn_7100224A10()[driver - 0x11].m_handle;
    }
    return GfItemHandle();
}

void GfDataDriver::fn_71002474F4(unsigned int driver, unsigned short item) {
    if (driver - 0x11 < 9) {
        GfDataManager::fn_7100224A10()[driver - 0x11].m_item = item;
    }
}

void GfDataDriver::fn_710024752C(SDataDriverDlc& data, unsigned short item) {
    data.m_item = item;
}

void GfDataDriver::fn_7100247534(unsigned int driver, GfItemHandle handle) {
    if (driver - 0x11 < 9) {
        SDataDriverDlc& data = GfDataManager::fn_7100224A10()[driver - 0x11];
        data.m_handle.m_handle = handle.m_handle;
    }
}

unsigned int GfDataDriver::fn_7100247474(unsigned int driver) {
    if (driver - 0x11 < 9) {
        return GfDataManager::fn_7100224A10()[driver - 0x11].m_item;
    }
    return 0;
}

}  // namespace gf

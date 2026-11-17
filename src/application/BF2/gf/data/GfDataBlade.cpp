#include "gf/FileStaticVec3.h"
#include "gf/SDataDriver.h"
#include "gf/SDataDlc.h"
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
#include "gf/GfQuestInfo.h"
#include "gf/GfDataIdea.h"
#include "gf/GfDataBattle.h"
#include "classes/gf/GfInitParamDriver.h"
#include "classes/gf/GfBdatChrBl.h"
#include "classes/gf/GfBdatChrEnParam.h"
#include "classes/gf/GfBdatBlade.h"
#include "string.h"
#include <algorithm>
#include "math.h"
#include "classes/gf/GfBdatCond.h"
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
#include "gf/GfDataSalvage.h"
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
#include "gf/GfReqParam.h"
#include "classes/gf/GfGameFlag.h"
#include "classes/gf/GfGameCond.h"
#include "ml/MTRand.h"
#include "classes/gf/GfEvent.h"
#include "classes/gf/GfBdatMsg.h"
#include "gf/QuestListAcc.h"
#include "gf/QuestTaskParam.h"
#include "classes/gf/GfDataAoc.h"
#include "gf/SDataOption.h"
#include "gf/GfDataNpc.h"
#include "gf/GfDataBladeArtsN.h"
#include "gf/GfDataDriverSkill.h"
#include "plugin/Bdat.h"
#include "classes/gf/GfGameManager.h"
#include "btl/Utility.h"
#include "classes/btl/BattleManager.h"
#include "gf/GfDataBtlDif.h"
#include "gf/GfDataFobj.h"
#include "gf/GfDataHitonowa.h"
#include "gf/GfDataField.h"

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

unsigned int GfDataEnemy::getWeaponType(unsigned int arrange) {
    unsigned int blade = getEquipBlade(arrange);
    if (blade == 0) {
        return 0;
    }
    return GfDataManager::getDataGame()->m_blades[GfDataBlade::getBladeIndex(blade)].m_weaponType;
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

void GfDataEnemy::setupNamedDefeatNum() {
    GfBdatChrEnArrange* bdat = GfBdatChrEnArrange::get();
    unsigned int arrange = bdat->getChrEnArrangeStart();
    unsigned int end = bdat->getChrEnArrangeEnd();
    unsigned int count = 0;
    for (; arrange < end; arrange++) {
        bool named = bdat->isChrEnArrangeFlagNamed(arrange);
        if (named && getEnemySuppress(arrange) != 0) {
            count++;
            if (count > 0xFE) {
                break;
            }
        }
    }
    GfGameFlag::setLocal(8, 0x874, count);
}

// Proposed name, not the original's: the symbols leave it unnamed (lbl_7100B50DC8)
__attribute__((used)) static const char* s_attributeEfbSuffixes[9] = {
    "", "_fire", "_water", "_wind", "_earth", "_volt", "_ice", "_light", "_dark",
};

const char* GfDataBlade::getBaseEfbAttributeName(unsigned int blade, unsigned int attribute) {
    if (attribute != 0) {
        return s_attributeEfbSuffixes[attribute];
    }
    unsigned char own = getAttribute(blade);
    if (!GfDataHana::isValid(blade) && !isCommonBlade(blade)) {
        return s_attributeEfbSuffixes[0];
    }
    return s_attributeEfbSuffixes[own];
}

unsigned char GfDataBlade::getAttribute(unsigned int blade) {
    if (blade == 0) {
        return 0;
    }
    if (GfDataHana::isValid(blade)) {
        return GfDataHana::getAttribute(blade);
    }
    return GfDataManager::getDataGame()->m_blades[getBladeIndex(blade)].m_attribute;
}

// Proposed name, not the original's: the symbols leave it unnamed (lbl_7100B50C30)
static const char* s_weaponNameSuffixes[51] = {
    "", "_01", "_02", "_03", "_04", "_05", "_06", "_07", "_08", "_09", "_10", "_11", "_12", "_13", "_14", "_15", "_16",
    "_17", "_18", "_19", "_20", "_20", "_21", "_22", "_23", "_24", "_25", "_26", "_27", "_28", "_29", "_30", "_31",
    "_32", "_33", "_34", "_35", "_36", "_37", "_38", "_39", "_40", "_41", "_42", "_43", "_44", "_45", "_46", "_47",
    "_48", "_49"};

const char* GfDataBlade::getDeathBlowWeaponName(unsigned int blade) {
    return s_weaponNameSuffixes[blade == 0 ? 0 : getSDataBlade(blade)->m_weaponType];
}

unsigned int GfDataBlade::getRoleByWpnType(unsigned int wpnType) {
    if (wpnType == 0) {
        return 1;
    }
    return GfBdatItem::get()->getPcWpnTypeRole(wpnType);
}

unsigned int GfDataBlade::getRole(unsigned int blade) {
    if (blade == 0) {
        return 0;
    }
    SDataBlade& data = GfDataManager::getDataGame()->m_blades[getBladeIndex(blade)];
    if (GfDataHana::isValid(blade)) {
        return GfDataHana::getRole(blade);
    }
    return getRoleByWpnType(data.m_weaponType);
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

void GfDataBlade::setUsedFavoriteItemForPouch(unsigned int blade, unsigned int item) {
    if (blade == 0) {
        return;
    }
    if (!(blade - 1124 < 9)) {
        switch (blade) {
        case 1001:
            if (isHikariCurrent()) {
                return;
            }
            break;
        case 1002:
            if (!isHikariCurrent()) {
                return;
            }
            break;
        case 1012:
        case 1013:
        case 1073:
        case 1110:
            return;
        }
    }
    unsigned int index = getBladeIndex(blade);
    SDataGame* game = GfDataManager::getDataGame();
    SDataBlade& data = game->m_blades[index];
    for (int i = 0; i < 2; i++) {
        BladeFavorite& favorite = data.m_favorites[i];
        if (favorite.m_itemUsed == 0 && favorite.m_item == item) {
            favorite.m_itemUsed = 1;
        }
        if (favorite.m_categoryUsed == 0) {
            unsigned int category = GfDataItem::getCategory(item);
            if (favorite.m_category == category) {
                favorite.m_categoryUsed = 1;
            }
        }
    }
}

const char* GfDataBlade::getFieldSkillVoice(unsigned int blade, unsigned int skill) {
    QuestListAcc* acc = QuestListAcc::get();
    unsigned int index = getBladeIndex(blade);
    SDataGame* game = GfDataManager::getDataGame();
    SDataBlade& data = game->m_blades[index];
    if (data.m_fieldSkills[0].m_id == skill || data.m_fieldSkills[1].m_id == skill ||
        data.m_fieldSkills[2].m_id == skill) {
        unsigned int category = acc->getFLD_FieldSkillListVoiceCategory(skill);
        if (category != 0) {
            return GfDataField::getFieldSkillVoice(blade, category);
        }
    }
    return nullptr;
}

const char* GfDataField::getFieldSkillVoice(unsigned int driver, unsigned int category) {
    if (category == 0) {
        return nullptr;
    }
    GfBdatRsc* rsc = GfBdatRsc::get();
    const char* voice = nullptr;
    if (driver - 1 < 6) {
        voice = rsc->getVoiceTableDriver(category, driver - 1);
    } else if (driver - 0x11 < 9) {
        voice = rsc->getVoiceTableIra(category, driver - 0x11);
    } else if (driver - 0x464 < 9) {
        voice = rsc->getVoiceTableIra(category, driver - 0x464);
    } else if (driver - 0x3E9 < 11) {
        voice = rsc->getVoiceTableBladeBlade(category, driver - 0x3E9);
    } else if (driver - 0x3F6 < 37) {
        voice = rsc->getVoiceTableRareBlade(category, driver - 0x3F6);
    } else {
        switch (driver) {
        case 0x450:
            voice = rsc->getVoiceTableRareBlade(category, 37);
            break;
        case 0x451:
            voice = rsc->getVoiceTableRareBlade(category, 38);
            break;
        case 0x452:
            voice = rsc->getVoiceTableRareBlade(category, 39);
            break;
        case 0x453:
            voice = rsc->getVoiceTableRareBlade(category, 40);
            break;
        case 0x454:
            voice = rsc->getVoiceTableRareBlade(category, 41);
            break;
        case 0x455:
            voice = rsc->getVoiceTableRareBlade(category, 42);
            break;
        case 0x457:
            voice = rsc->getVoiceTableRareBlade(category, 43);
            break;
        default:
            if (driver - 0x4AD < 200) {
                unsigned int personality = GfDataBlade::getSDataBlade(driver)->m_personality;
                unsigned int id = GfBdatBtl::get()->getBTL_Bl_PersonalityVoiceID(personality);
                if (id - 0x3D < 0x20) {
                    voice = rsc->getVoiceTableCommonCommonBlade(category, id - 0x3D);
                }
            }
            break;
        }
    }
    if (voice == nullptr || *voice == '\0') {
        return nullptr;
    }
    return voice;
}

void GfDataBlade::fn_710024121C(mm::mtl::FixedVector<unsigned short, 64>& enhances, bool keep) {
    GfBdatBtl* btl = GfBdatBtl::get();
    for (unsigned short* it = enhances.begin(); it != enhances.end();) {
        if (btl->isBTL_EnhanceEffFlagCondition(btl->getBTL_EnhanceEnhanceEffect(*it)) && !keep) {
            it = enhances.erase(it);
        } else {
            ++it;
        }
    }
}

bool GfDataDriver::getListDriver(mm::mtl::FixedVector<unsigned short, 32>& drivers) {
    for (unsigned int driver = 1; driver <= 9; driver++) {
        drivers.push_back(driver);
    }
    return !drivers.empty();
}

bool GfDataDriver::getListIra(mm::mtl::FixedVector<unsigned short, 32>& drivers) {
    GfBdatChrDr* bdat = GfBdatChrDr::get();
    unsigned int row = bdat->getChrIrStart();
    unsigned int end = bdat->getChrIrEnd();
    for (; row < end; row++) {
        drivers.push_back(bdat->getChrIrdriverID(row));
    }
    return !drivers.empty();
}

bool GfDataDriver::getIraBack(mm::mtl::FixedVector<unsigned short, 32>& list, unsigned int driver) {
    if (driver - 0x11 < 9) {
        GfBdatChrDr* bdat = GfBdatChrDr::get();
        unsigned int group = bdat->getChrIrGroupID(bdat->getChrDrIraParam(driver));
        unsigned int row = bdat->getChrIrStart();
        unsigned int end = bdat->getChrIrEnd();
        for (; row < end; row++) {
            if (bdat->getChrIrType(row) == 1 && bdat->getChrIrGroupID(row) == group) {
                list.push_back(bdat->getChrIrdriverID(row));
            }
        }
        return !list.empty();
    }
    return false;
}

unsigned int GfDataDriver::getIraFront(unsigned int driver) {
    if (driver - 0x11 < 9) {
        GfBdatChrDr* bdat = GfBdatChrDr::get();
        if (bdat->getChrIrType(bdat->getChrDrIraParam(driver)) != 0) {
            bdat = GfBdatChrDr::get();
            unsigned int group = bdat->getChrIrGroupID(bdat->getChrDrIraParam(driver));
            unsigned int row = bdat->getChrIrStart();
            unsigned int end = bdat->getChrIrEnd();
            for (; row < end; row++) {
                if (bdat->getChrIrType(row) == 0 && bdat->getChrIrGroupID(row) == group) {
                    return bdat->getChrIrdriverID(row);
                }
            }
            return 0x11;
        }
    }
    return driver;
}

unsigned int GfDataDriver::getIraFromPos(unsigned int driver, PTPOS pos) {
    mm::mtl::FixedVector<unsigned short, 32> list;
    unsigned int front = getIraFront(driver);
    list.push_back(front);
    getIraBack(list, front);
    for (unsigned short& id : list) {
        if (getPartyPos(id) == pos) {
            return id;
        }
    }
    return 0;
}

unsigned int GfDataDriver::getIraBack(unsigned int driver) {
    if (driver == 0 || driver - 0x11 >= 9) {
        return 0;
    }
    unsigned int front = getIraFront(driver);
    mm::mtl::FixedVector<unsigned short, 32> list;
    getIraBack(list, front);
    list.push_back(front);
    for (unsigned short& id : list) {
        if (!isActivateParty(id)) {
            continue;
        }
        if (getPartyPos(id) == 1) {
            return id;
        }
    }
    return 0;
}

unsigned int GfDataDriver::getChestHeight(unsigned int driver) {
    return GfBdatChrDr::get()->getChrDrChestHeight(driver);
}

unsigned int GfDataDriver::getLandingHeight(unsigned int driver) {
    return GfBdatChrDr::get()->getChrDrLandingHeight(driver);
}

unsigned int GfDataDriver::getIconData(unsigned int driver) {
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

unsigned int GfDataDriver::getGender(unsigned int driver) {
    return GfBdatChrDr::get()->getChrDrGender(driver);
}

int GfDataDriver::getMenuOffset(unsigned int driver) {
    return GfBdatChrDr::get()->getChrDrOffsetID(driver);
}

const char* GfDataDriver::getCenterBone(unsigned int driver) {
    return GfBdatChrDr::get()->getChrDrCenterBone(driver);
}

const char* GfDataDriver::getCamBone(unsigned int driver) {
    return GfBdatChrDr::get()->getChrDrCamBone(driver);
}

void GfDataDriver::setKizunaringComplete(unsigned int driver, bool flag) {
    SDataDriver* data = &getSDataDriver(driver);
    data->m_kizunaRingFlags |= flag ? 2 : 1;
}

bool GfDataDriver::isKizunaringComplete(unsigned int driver, bool flag) {
    return (getSDataDriver(driver).m_kizunaRingFlags & (flag ? 2 : 1)) != 0;
}

bool GfDataDriver::equipDriverBladeFromReserverBlade(unsigned int driver) {
    mm::mtl::FixedVector<unsigned short, 424> list;
    return fn_7100241E10(driver, list);
}

const char* GfDataDriver::getModelResourceName(unsigned int driver) {
    return GfBdatChrDr::get()->getChrDrModel(driver);
}

const char* GfDataDriver::getMotionResourceName(unsigned int driver) {
    return GfBdatChrDr::get()->getChrDrMotion(driver);
}

const char* GfDataDriver::getEffectResourceName(unsigned int driver) {
    return GfBdatChrDr::get()->getChrDrCom_Eff(driver);
}

unsigned int GfDataDriver::getAiID(unsigned int driver) {
    return GfBdatChrDr::get()->getChrDrAiID(driver);
}

bool GfDataDriver::getDriverAddAnim(mm::mtl::FixStr<128>& name, unsigned int driver, unsigned int weaponType) {
    GfBdatChrDr* bdat = GfBdatChrDr::get();
    DataParamAcc acc(3, driver, static_cast<GimmickType>(0));
    bool result = false;
    if (acc.isValid()) {
        if (bdat->getChrDrWpnType(driver, weaponType - 1) == 0) {
            result = false;
        } else {
            const char* model = acc.getModelResourceName();
            if (weaponType >= 10) {
                name.format("%s_%d", model, weaponType);
            } else {
                name.format("%s_0%d", model, weaponType);
            }
            result = true;
        }
    }
    return result;
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

bool GfDataDriver::isAttachedParty(unsigned int driver) {
    if (driver == 0) {
        return false;
    }
    return getSDataDriver(driver).m_stateFlag != 0;
}

unsigned int GfDataDriverArts::getNeedLevelupWp(unsigned int driver, unsigned int arts) {
    unsigned int level = getArtsLevel(driver, arts);
    if (level >= 5) {
        return 0;
    }
    return GfBdatBtl::get()->getArtsDrNeedWP(arts, level + 1);
}

unsigned int GfDataDriverArts::getLevelCap(unsigned int arts, unsigned int index) {
    return GfBdatBtl::get()->getArtsDrReleaseLv(arts, index);
}

unsigned int GfDataDriverArts::getNameID(unsigned int arts) {
    return GfBdatBtl::get()->getArtsDrName(arts);
}

unsigned int GfDataDriverArts::getCaptionID(unsigned int arts) {
    unsigned int caption = GfBdatBtl::get()->getArtsDrCaption(arts);
    unsigned int param = static_cast<unsigned short>(Bdat::getValCheck(GfDataBdat::getFP(30), "Param01", 0, 2));
    btl::BattleManager* battle = btl::BattleManager::get();
    if (param == arts && battle != nullptr && btl::Utility::IsSatisfyCondition(0)) {
        caption++;
    }
    return caption;
}

unsigned int GfDataDriverArts::getTalentCaptionID(unsigned int arts) {
    return GfBdatBtl::get()->getArtsDrTalentCap(arts);
}

unsigned int GfDataDriverArts::getCondTalentCaptionID(unsigned int arts) {
    return GfBdatBtl::get()->getArtsDrCondCap(arts);
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
    if (GfGameManager::isGameTypeIra()) {
        unsigned int caption = GfBdatBtl::get()->getBTL_EnhanceCaption2(enhance);
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
    if (GfGameManager::isGameTypeIra()) {
        unsigned int caption = GfBdatBtl::get()->getBTL_EnhanceCaption2(enhance);
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

unsigned int GfDataMap::getMapJumpID(unsigned int mapId) {
    unsigned char* bdat = GfDataBdat::getFP(182);
    unsigned int top = Bdat::getIdTop(bdat);
    unsigned int end = Bdat::getIdCount(bdat) + top;
    for (unsigned int id = top; id < end; id++) {
        if (static_cast<unsigned char>(Bdat::getValCheck(bdat, "MapList", id, 1)) == mapId) {
            return id;
        }
    }
    return 0;
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

unsigned int GfDataWeapon::getDamageForIra(unsigned int driver) {
    if (driver - 0x11 > 2) {
        return 0;
    }
    unsigned int row = driver - 0x10;
    unsigned int level = GfDataDriver::getLevel(driver) - 1;
    GfBdatItem* item = GfBdatItem::get();
    unsigned int min = item->getITM_PcWpnIrAtkLv1(row);
    unsigned int max = item->getITM_PcWpnIrAtkLv99(row);
    return min + (max - min) * level / 98;
}

unsigned int GfDataWeapon::getGuardRatioForIra(unsigned int driver) {
    if (driver - 0x11 > 2) {
        return 0;
    }
    unsigned int row = driver - 0x10;
    unsigned int level = GfDataDriver::getLevel(driver) - 1;
    GfBdatItem* item = GfBdatItem::get();
    unsigned int min = item->getITM_PcWpnIrGuardRateLv1(row);
    unsigned int max = item->getITM_PcWpnIrGuardRateLv99(row);
    return min + (max - min) * level / 98;
}

unsigned int GfDataWeapon::getCriticalRatioForIra(unsigned int driver) {
    if (driver - 0x11 > 2) {
        return 0;
    }
    unsigned int row = driver - 0x10;
    unsigned int level = GfDataDriver::getLevel(driver) - 1;
    GfBdatItem* item = GfBdatItem::get();
    unsigned int min = item->getITM_PcWpnIrCriRateLv1(row);
    unsigned int max = item->getITM_PcWpnIrCriRateLv99(row);
    return min + (max - min) * level / 98;
}

unsigned int GfDataWeapon::getStabilityForIra(unsigned int driver) {
    if (driver - 0x11 > 2) {
        return 0;
    }
    unsigned int row = driver - 0x10;
    unsigned int level = GfDataDriver::getLevel(driver) - 1;
    GfBdatItem* item = GfBdatItem::get();
    unsigned int min = item->getITM_PcWpnIrStbLv1(row);
    unsigned int max = item->getITM_PcWpnIrStbLv99(row);
    return min + (max - min) * level / 98;
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

bool GfDataMercenaries::getTeamByZoneMissionWorking(mm::mtl::FixedVector<unsigned short, 3>& teams, unsigned int zone) {
    SDataGame* game = GfDataManager::getDataGame();
    for (Team* team = game->m_teams.begin(); team != game->m_teams.end(); ++team) {
        if (team->m_mission == 0 || GfGameFlag::getLocal(4, team->m_mission + 5) != 2) {
            continue;
        }
        unsigned int map = getMissionMapID(team->m_mission);
        if (map != 0 && GfDataMap::getZoneIdForGameMap(map) == zone) {
            teams.push_back(team->m_teamId);
        }
    }
    return teams.size() != 0;
}

unsigned int GfDataMercenaries::getMissionMapID(unsigned int mission) {
    if (mission != 0) {
        QuestID quest = getMissionQuestID(mission);
        if (!quest.empty()) {
            unsigned int hints = GfDataQuest::getListHintsID(quest);
            if (hints != 0) {
                unsigned int zone = QuestListAcc::get()->getHintsZoneID(hints);
                if (GfDataUtil::getScenarioFlag() > 8036 && zone == 12) {
                    return 14;
                }
                return zone;
            }
        }
    }
    return 0;
}

bool GfDataMercenaries::getTeamByZoneMissionComplete(mm::mtl::FixedVector<unsigned short, 3>& teams, unsigned int zone) {
    SDataGame* game = GfDataManager::getDataGame();
    for (Team* team = game->m_teams.begin(); team != game->m_teams.end(); ++team) {
        if (!isTeamStateReward(team->m_teamId)) {
            continue;
        }
        unsigned int map = getMissionMapID(team->m_mission);
        if (map != 0 && GfDataMap::getZoneIdForGameMap(map) == zone) {
            teams.push_back(team->m_teamId);
        }
    }
    return teams.size() != 0;
}

bool GfDataMercenaries::isMissionCompleteFlag(unsigned int mission) {
    return GfGameFlag::getLocal(1, mission + 46285) != 0;
}

void GfDataMercenaries::setMissionCompleteFlag(unsigned int mission) {
    GfGameFlag::setLocal(1, mission + 46285, 1);
}

unsigned int GfDataMercenaries::getTeamMissionTime(unsigned int teamId, unsigned int mission) {
    unsigned int time = QuestListAcc::get()->getFLD_MercenariesMissionRequestPerformance(mission);
    if (time == 0) {
        return 0;
    }
    float result = time;
    unsigned short* members = getTeamMember(teamId);
    if (members != nullptr) {
        float level = 0.0f;
        for (unsigned int slot = 0; slot < 3; slot++) {
            unsigned int skill = getFieldSkill(mission, slot);
            if (skill == 0) {
                continue;
            }
            for (int i = 0; i < 6; i++) {
                if (members[i] == 0) {
                    continue;
                }
                float bladeLevel = 0.0f;
                {
                    DataParamAcc acc(4, members[i], GimmickType(0));
                    if (acc.isValid()) {
                        if (acc.getFieldSkill(0, false) == skill) {
                            bladeLevel = acc.getFieldSkillLevel(0, false);
                        }
                        if (acc.getFieldSkill(1, false) == skill) {
                            bladeLevel += acc.getFieldSkillLevel(1, false);
                        }
                        if (acc.getFieldSkill(2, false) == skill) {
                            bladeLevel += acc.getFieldSkillLevel(2, false);
                        }
                    }
                }
                level += bladeLevel;
            }
        }
        float shortened = time * (100.0f - level * 6.0f) * 0.01f;
        float least = time * (QuestListAcc::get()->getFLD_MercenariesConfigValue(17) * 0.01f + 0.001f);
        result = shortened < least ? least : shortened;
        result = result < 1.0f ? 1.0f : result;
    }
    return result;
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

AchievQuest* GfDataQuest::getAchievQuest(QuestID id) {
    unsigned int achieveId = id.m_achieveId;
    if (achieveId == 0) {
        return nullptr;
    }
    // the original looks the PRT quest up here without using it
    getListPRTQuestID(id);
    unsigned int blade = m_achieve2blade[achieveId];
    if (blade == 0) {
        return nullptr;
    }
    unsigned int bladeIndex = GfDataBlade::getBladeIndex(blade);
    SDataGame* game = GfDataManager::getDataGame();
    SDataBlade& data = game->m_blades[bladeIndex];
    unsigned int index = (achieveId - 1) % 50;
    unsigned int line = index / 5;
    unsigned int level = index % 5;
    switch (line) {
    case 0:
    case 1:
    case 2:
        return &data.m_artsAchievement[line].m_quests[level];
    case 3:
    case 4:
    case 5:
        return &data.m_skillAchievement[line - 3].m_quests[level];
    case 6:
    case 7:
    case 8:
        return &data.m_fieldSkillAchievement[line - 6].m_quests[level];
    case 9:
        return &data.m_keyAchievement.m_quests[level];
    default:
        return nullptr;
    }
}

bool GfDataQuest::getHanyouFlg(unsigned int& type, unsigned int& flag, unsigned int& count, unsigned int& limit,
                               const QuestTaskParam& param) {
    QuestListAcc* acc = QuestListAcc::get();
    unsigned int purpose = param.m_purposeId;
    if (purpose == 0) {
        // the original looks the purpose up here and returns without using it
        getListPurposeID(param.m_questId);
        return false;
    }
    GfBdatCond* bdat = GfBdatCond::get();
    if (acc->getTaskTaskType(purpose, param.m_task) != 10) {
        return false;
    }
    unsigned int cond = acc->getConditionConditionID(acc->getTaskTaskID(purpose, param.m_task));
    if (cond == 0) {
        return false;
    }
    for (unsigned int i = 0; i < 8; i++) {
        if (bdat->getConditionListConditionType(cond, i) != 4) {
            continue;
        }
        unsigned int flagCond = bdat->getConditionListCondition(cond, i);
        if (flagCond == 0) {
            return false;
        }
        type = bdat->getConditionFlagFlagType(flagCond);
        flag = bdat->getConditionFlagFlagID(flagCond);
        bool hanyou = false;
        switch (type) {
        case 16:
            if (flag - 1550 >= 10) {
                break;
            }
            hanyou = true;
            break;
        case 8:
            if (flag - 2224 >= 1500) {
                break;
            }
            hanyou = true;
            break;
        }
        if (hanyou) {
            count = bdat->getConditionFlagFlagMin(flagCond);
            limit = bdat->getConditionFlagFlagMax(flagCond);
            return true;
        }
    }
    return false;
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

unsigned int GfDataBlade::getStartActCommonBlade() {
    return 1401;
}

bool GfDataBlade::getListIraBlade(mm::mtl::FixedVector<unsigned short, 422>& list) {
    for (unsigned int blade = 1124; blade < 1133; blade++) {
        list.push_back(blade);
    }
    return !list.empty();
}

void GfDataBlade::removeSameBlade(mm::mtl::FixedVector<unsigned short, 422>& list) {
    mm::mtl::FixedVector<unsigned short, 422> group;
    group.push_back(1001);
    group.push_back(1002);
    group.push_back(1003);
    fn_7100239560(list, group);
    group.clear();
    group.push_back(1005);
    group.push_back(1006);
    group.push_back(1007);
    fn_7100239560(list, group);
    group.clear();
    group.push_back(1022);
    group.push_back(1050);
    fn_7100239560(list, group);
}

ActivateType GfDataBlade::getBladeActivateType(unsigned int blade) {
    unsigned int index = getBladeIndex(blade);
    SDataGame* game = GfDataManager::getDataGame();
    return getBladeActivateType(game->m_blades[index]);
}

bool GfDataBlade::isFreeEngage(unsigned int blade) {
    GfBdatChrBl* bdat = GfBdatChrBl::get();
    if (blade >= bdat->getChrBlEnd()) {
        return false;
    }
    return bdat->isChrBlFlagFreeEngage(blade);
}

bool GfDataBlade::isNoMapRev(unsigned int blade) {
    GfBdatChrBl* bdat = GfBdatChrBl::get();
    if (blade >= bdat->getChrBlEnd()) {
        return false;
    }
    return bdat->isChrBlFlagNoMapRev(blade);
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

unsigned int GfDataBlade::getGender(unsigned int blade) {
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

void GfDataBlade::setUiCommonBlade(const SDataBlade& data, unsigned int blade) {
    SDataBlade& slot = GfDataManager::getDataGame()->m_blades[getBladeIndex(blade)];
    slot = data;
    slot.m_bladeId = blade;
}

bool GfDataBlade::isCommonBlade(unsigned int blade) {
    return blade >= 1197 && blade < 1423;
}

unsigned int GfDataBlade::getCrownPoint(unsigned int blade) {
    // Proposed name, not the original's: the symbols leave it unnamed (lbl_71009BA070)
    static const unsigned short s_crownDatavalues[4] = {0x3F, 0x40, 0x41, 0x42};
    if (blade - 1001 < 13) {
        return 5;
    }
    if (blade >= 1014 && blade < GfBdatChrBl::get()->getChrBlEnd()) {
        return 5;
    }
    if (blade - 1197 < 226) {
        GfBdatBtl* btl = GfBdatBtl::get();
        unsigned int max = getKizunaringMax(blade);
        for (unsigned long i = 0; i < 4; i++) {
            if (max <= btl->getWildcardDatavalueU2(s_crownDatavalues[i])) {
                return i + 1;
            }
        }
    }
    return 1;
}

unsigned int GfDataBlade::getKizunaringMax(unsigned int blade) {
    unsigned int num = 0;
    for (unsigned int line = 0; line < 10; line++) {
        AchievInfo* info = getAchievInfo(blade, line);
        if (info->m_achievementId != 0) {
            for (int i = 0; i < 5; i++) {
                if (info->m_quests[i].m_achievementId != 0) {
                    num++;
                }
            }
        }
    }
    return num;
}

bool GfDataBlade::isRegularBlade(unsigned int blade) {
    return blade >= 1001 && blade < 1014;
}

bool GfDataBlade::isValid(unsigned int blade) {
    return blade >= 1001 && blade < 1423;
}

bool GfDataBlade::getListParty(mm::mtl::FixedVector<unsigned short, 422>& list) {
    if (GfDataUtil::isIra()) {
        for (unsigned int driver = 17; driver < 26; driver++) {
            if (!GfDataDriver::isIraFront(driver) && GfDataDriver::isActivatePartyAll(driver)) {
                unsigned int party = GfDataParty::getDriverPartyID(driver);
                if (party < 3) {
                    unsigned int blade = GfDataDriver::getIraBlade(driver, -1);
                    if (!isUnselect(blade)) {
                        list.push_back(blade);
                    }
                }
            }
        }
    } else {
        for (unsigned int i = 0; i < 422; i++) {
            unsigned int blade = getBladeID(i);
            if (blade == 0) {
                continue;
            }
            if (!isActivateDriver(blade)) {
                continue;
            }
            unsigned int driver = getSetDriver(blade);
            if (GfDataDriver::isActivatePartyAll(driver)) {
                unsigned int party = GfDataParty::getDriverPartyID(driver);
                if (party < 3 && GfDataParty::isExistBlade(blade) && !isDummyBlade(blade) && !isUnselect(blade)) {
                    list.push_back(blade);
                }
            }
        }
    }
    return !list.empty();
}

bool GfDataDriver::isIraFront(unsigned int driver) {
    if (driver - 0x11 <= 8) {
        GfBdatChrDr* bdat = GfBdatChrDr::get();
        return bdat->getChrIrType(bdat->getChrDrIraParam(driver)) == 0;
    }
    return true;
}

bool GfDataDriver::isActivateParty(unsigned int driver) {
    if (driver == 0) {
        return false;
    }
    if (getSDataDriver(driver).m_dataType != 1) {
        return false;
    }
    return static_cast<unsigned int>(GfDataParty::getDriverPartyID(driver)) < 3;
}

bool GfDataBlade::isBladeID(unsigned int blade) {
    return blade >= 1001 && blade < 1423;
}

SDataPouch* GfDataDriver::getPouchData(unsigned int driver, unsigned int pouch) {
    return getSDataDriver(driver).m_pouches + pouch;
}

bool GfDataBlade::isMatchIdeaAttribute(unsigned int blade, unsigned int idea) {
    switch (getAttribute(blade)) {
    case 1:
    case 2:
        return idea == 0;
    case 3:
    case 6:
        return idea == 1;
    case 4:
    case 5:
        return idea == 2;
    case 7:
    case 8:
        return idea == 3;
    }
    return false;
}

unsigned int GfDataBlade::getIdeaTypeByAttribute(unsigned int blade) {
    switch (getAttribute(blade)) {
    case 1:
    case 2:
        return 0;
    case 3:
    case 6:
        return 1;
    case 4:
    case 5:
        return 2;
    case 7:
    case 8:
        return 3;
    }
    return 0;
}

bool GfDataBlade::isNeedChangeWeapon(unsigned int blade) {
    return (blade >= 1043 && blade < 1051) || blade == 1039;
}

unsigned int GfDataDriver::getDefaultBlade(unsigned int driver, unsigned int slot) {
    return GfBdatChrDr::get()->getChrDrDefBlade(driver, slot);
}

bool GfDataDriver::isIraHideWeaponOnField(unsigned int driver) {
    GfBdatChrDr* bdat = GfBdatChrDr::get();
    unsigned int row = bdat->getChrDrIraParam(driver);
    if (row == 0) {
        return false;
    }
    return bdat->isChrIrFlagWpnInNonView(row);
}

unsigned int GfDataDriver::getPartyPos(unsigned int driver) {
    if (driver - 0x11 <= 8) {
        return GfDataManager::getDataGameIra()->m_drivers[driver - 0x11].m_partyIndex;
    }
    return 0;
}

unsigned int GfDataDriver::getIraGroup(unsigned int driver) {
    GfBdatChrDr* bdat = GfBdatChrDr::get();
    unsigned int row = bdat->getChrDrIraParam(driver);
    if (row == 0) {
        return 0;
    }
    return bdat->getChrIrGroupID(row);
}

SDataIra* GfDataDriver::getSDataIra(unsigned int driver) {
    driver = driver - 0x11 < 9 ? driver : 0x11;
    unsigned int index;
    if (driver - 0x11 < 9) {
        index = driver - 0x11;
    } else {
        index = driver - 1 < 16 ? driver - 1 : 1;
    }
    return &GfDataManager::getDataGameIra()->m_drivers[index];
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

bool GfDataDriver::isActivateWeaponType(unsigned int driver, unsigned int index) {
    if (driver == 0) {
        return false;
    }
    if (index >= 0x1C) {
        SDataDriverArtsEx* ex = getSDataDriverArtsEx(driver);
        return ex->m_flags.test(index - 0x1C);
    }
    SDataDriver* data = &getSDataDriver(driver);
    return data->m_flags.test(index);
}

void GfDataDriver::setActivateWeaponType(unsigned int driver, unsigned int index) {
    if (driver == 0) {
        return;
    }
    if (index >= 0x1C) {
        SDataDriverArtsEx* ex = getSDataDriverArtsEx(driver);
        ex->m_flags.set(index - 0x1C);
        return;
    }
    SDataDriver* data = &getSDataDriver(driver);
    data->m_flags.set(index);
}

bool GfDataDriver::isDriver(unsigned int driver) {
    return driver >= 1 && driver < 26;
}

bool GfDataParty::isExistDriver(unsigned int driver) {
    for (int i = 0; i < 3; i++) {
        if (GfDataManager::getDataGame()->m_party.m_members[i].m_driver == driver) {
            return true;
        }
    }
    return false;
}

bool GfDataDriver::isEnableEquipBlade(unsigned int driver, unsigned int blade) {
    if (blade == 0) {
        return false;
    }
    unsigned int setDriver = GfDataBlade::getSetDriver(blade);
    if (setDriver != 0 && setDriver != driver) {
        return false;
    }
    if (driver != 4 && blade >= 1005 && blade < 1008) {
        return false;
    }
    unsigned int creator = GfDataBlade::getCreator(blade);
    if (driver == 1) {
        if (creator == 0) {
            return false;
        }
        if (creator == 1) {
            return true;
        }
        return GfGameManager::isRexAwakening();
    }
    return creator != 0 && creator == driver;
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

bool GfDataDriver::getEquipAcceEnahnce(mm::mtl::FixedVector<unsigned short, 64>& enhances, unsigned int driver) {
    return getEquipAcceEnhance(enhances, getSDataDriver(driver));
}

bool GfDataDriver::getEquipAcceEnhance(mm::mtl::FixedVector<unsigned short, 64>& enhances, const SDataDriver& data) {
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
        unsigned int item = GfDataManager::getDataGameIra()->m_drivers[dlc].m_item;
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
    return getLevel(getSDataDriver(driver));
}

bool GfDataEvent::isBladeCreateEvent(unsigned int event) {
    return event >= 19001 && event < 19062;
}

bool GfDataEvent::isBladeQuestEvent(unsigned int event) {
    if (event - 20707 < 504) {
        return true;
    }
    GfBdatShop* shop = GfBdatShop::get();
    unsigned int row = shop->getMNU_EventTheaterStart();
    unsigned int end = shop->getMNU_EventTheaterEnd();
    for (; row < end; row++) {
        if (shop->getMNU_EventTheaterevent_id(row) == event) {
            goto found;
        }
    }
    return false;
found:
    return shop->getMNU_EventTheatercategory(row) == 2;
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

unsigned int GfDataNanakoori::getClearMissionForSpecial() {
    // Proposed name, not the original's (the loop is unrolled; the array leaves no data)
    static const unsigned short s_specialMissions[6] = {0xC5, 0xC6, 0xC7, 0xD0, 0xD1, 0xD2};
    unsigned int count = 0;
    for (int i = 0; i < 6; i++) {
        unsigned int offset = getNanakooriMissionClearFlg1Offset(s_specialMissions[i]);
        if (offset != 0 && GfGameFlag::getLocal(1, offset) != 0) {
            count++;
        }
    }
    return count;
}

unsigned int GfDataNanakoori::getClearMissionForLive() {
    // Proposed name, not the original's (the loop is unrolled; the array leaves no data)
    static const unsigned short s_liveMissions[9] = {0xC1, 0xC2, 0xC3, 0xC4, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF};
    unsigned int count = 0;
    for (int i = 0; i < 9; i++) {
        unsigned int offset = getNanakooriMissionClearFlg1Offset(s_liveMissions[i]);
        if (offset != 0 && GfGameFlag::getLocal(1, offset) != 0) {
            count++;
        }
    }
    return count;
}

unsigned int GfDataNanakoori::getClearMissionForLesson() {
    // Proposed name, not the original's: the symbols leave it unnamed (lbl_71009BA37A)
    static const unsigned short s_lessonMissions[15] = {
        0xB2, 0xB3, 0xB4, 0xB5, 0xB6, 0xB7, 0xB8, 0xB9, 0xBA, 0xBB, 0xBC, 0xBD, 0xBE, 0xBF, 0xC0,
    };
    unsigned int count = 0;
    for (int i = 0; i < 15; i++) {
        unsigned int offset = getNanakooriMissionClearFlg1Offset(s_lessonMissions[i]);
        if (offset != 0 && GfGameFlag::getLocal(1, offset) != 0) {
            count++;
        }
    }
    return count;
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

void GfDataAchievement::clearTotalCount(unsigned int type) {
    int index = getAchievementTotalFlgIndex8(type);
    if (index >= 0) {
        GfGameFlag::setLocal(8, index, 0);
        return;
    }
    index = getAchievementTotalFlgIndex32(type);
    if (index < 0) {
        return;
    }
    GfGameFlag::setLocal(32, index, 0);
}

GfDataParty::PartyMember* GfDataParty::getPartyMember(unsigned int index, PTPOS party) {
    switch (party) {
    case 1:
        return &GfDataManager::getDataGameIra()->m_partyMembers[0][index];
    case 2:
        return &GfDataManager::getDataGameIra()->m_partyMembers[1][index];
    default:
        return &GfDataManager::getDataGame()->m_party.m_members[index];
    }
}



unsigned int GfDataBlade::getBladeWpnType(unsigned int blade) {
    if (blade == 0) {
        return 0;
    }
    SDataBlade& data = GfDataManager::getDataGame()->m_blades[getBladeIndex(blade)];
    return data.m_weaponType;
}

bool GfDataEnemy::getDriverAddAnim(mm::mtl::FixStr<128>& name, unsigned int arrange, unsigned int index) {
    DataParamAcc acc(5, arrange, static_cast<GimmickType>(0));
    bool result = false;
    if (acc.isValid()) {
        const char* model = acc.getModelResourceName();
        if (index >= 10) {
            name.format("%s_%d", model, index);
        } else {
            name.format("%s_0%d", model, index);
        }
        result = true;
    }
    return result;
}

bool GfDataEnemy::getDriverEffect(mm::mtl::FixStr<128>& model, mm::mtl::FixStr<128>& name, unsigned int arrange,
                                  unsigned int index) {
    DataParamAcc acc(5, arrange, static_cast<GimmickType>(0));
    bool result = false;
    if (acc.isValid()) {
        const char* resource = acc.getModelResourceName();
        if (index >= 10) {
            name.format("%s_%d", resource, index);
        } else {
            name.format("%s_0%d", resource, index);
        }
        model.format("%s", acc.getModelResourceName());
        result = true;
    }
    return result;
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

// the blade whose menu data (voice actor, illustrator, voices) a blade shows: for a common blade, 1051 unless a compare
// of its SE resource name matches (it compares the blade's own entry with itself, so the blade itself); any other
// blade itself. Inlined into all three users (1.0.0's too, no copy): the name is not the original's.
static inline unsigned int getMenuDataBlade(unsigned int blade) {
    unsigned int id = blade;
    if (blade - 1197 < 226) {
        const char* name = GfDataManager::getDataGame()->m_blades[GfDataBlade::getBladeIndex(blade)].m_seName;
        id = 1051;
        for (unsigned int i = 1051; i <= 1072; i++) {
            if (strcmp(GfDataManager::getDataGame()->m_blades[GfDataBlade::getBladeIndex(blade)].m_seName, name) == 0) {
                id = blade;
                break;
            }
        }
    }
    return id;
}

unsigned int GfDataBlade::getMenuCastName(unsigned int blade) {
    unsigned int id = getMenuDataBlade(blade);
    return GfBdatChrBl::get()->getChrBlMnuCastName(id);
}

unsigned int GfDataBlade::getMenuIlustName(unsigned int blade) {
    unsigned int id = getMenuDataBlade(blade);
    return GfBdatChrBl::get()->getChrBlMnuIlustName(id);
}

const char* GfDataBlade::getMenuVoiceName(unsigned int blade, unsigned int slot) {
    unsigned int id = getMenuDataBlade(blade);
    return GfBdatChrBl::get()->getChrBlMnuVoice(id, slot);
}

SDataIdea* GfDataBlade::getSDataIdea(unsigned int blade) {
    SDataBlade& data = GfDataManager::getDataGame()->m_blades[getBladeIndex(blade)];
    return &data.m_idea;
}

const char* GfDataBlade::getName(unsigned int blade, unsigned int kind) {
    if (isIra(blade)) {
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

bool GfDataBlade::getName(unsigned char*& bdat, unsigned int& id, unsigned int blade) {
    id = 0;
    if (blade == 0) {
        return false;
    }
    return getNameWithMsgID(bdat, id, GfDataManager::getDataGame()->m_blades[getBladeIndex(blade)]);
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

void GfDataBlade::resetAttachedParty(unsigned int blade) {
    unsigned int index = getBladeIndex(blade);
    SDataGame* game = GfDataManager::getDataGame();
    game->m_blades[index].m_attachedParty = 2;
    if (blade >= 1014 && blade < GfBdatChrBl::get()->getChrBlEnd()) {
        game->m_blades[index].m_equipWeapon = GfBdatChrBl::get()->getChrBlDefWeapon(blade);
    }
    GfEvent::callBladeActivate(blade, ActivateType(0), ActivateType(0));
}

bool GfDataBlade::setActivateReserver(unsigned int blade) {
    if (isIra(blade)) {
        return [&]() -> bool {
            if (isActivateReserver(blade)) {
                return false;
            }
            unsigned int index = getBladeIndex(blade);
            SDataGame* game = GfDataManager::getDataGame();
            SDataBlade& data = game->m_blades[index];
            ActivateType from = getBladeActivateType(data);
            if (data.m_dataType != 1) {
                data.m_dataType = 1;
            }
            data.m_attachedParty = 1;
            data.m_unselect = 0;
            ActivateType to = getBladeActivateType(data);
            if (from == 0) {
                GfEvent::callBladeEnable(blade);
                GfEvent::callBladeActivate(blade, ActivateType(0), to);
            }
            return from != to;
        }();
    }
    if (isActivateReserver(blade) && !GfDataParty::isExistBlade(blade)) {
        return false;
    }
    unsigned int driver = GfDataManager::getDataGame()->m_blades[getBladeIndex(blade)].m_setDriver;
    int slot = getDriverSetID(blade);
    if (GfDataDriver::unsetBlade(blade)) {
        if (GfDataDriver::getDummyBlade(driver) != 0) {
            DataParamAcc acc(3, driver, GimmickType(0));
            if (acc.getBladeSet(false) < 0) {
                GfDataDriver::setBlade(driver, GfDataDriver::getDummyBlade(driver), -1);
            }
        }
        if (blade == 1001 && getDriverSetID(1002) == 3) {
            SDataDriver& data = GfDataDriver::getSDataDriver(driver);
            data.m_blades[slot] = 1002;
            data.m_altBlades[0] = 0;
        }
    }
    return fn_710023AEA4(blade);
}

bool GfDataBlade::isActivateReserver(unsigned int blade) {
    if (GfDataManager::getDataGame()->m_blades[getBladeIndex(blade)].m_dataType != 1) {
        return false;
    }
    unsigned int driver = getSetDriver(blade);
    if (driver == 0) {
        return true;
    }
    unsigned int party = GfDataParty::getDriverPartyID(driver);
    return party > 2 && party != 0xFFFFFFFF;
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

unsigned int GfDataBlade::getBladeWeaponByRank(unsigned int blade, unsigned int chip) {
    GfBdatItem* bdat = GfBdatItem::get();
    unsigned int type = getBladeWpnType(blade);
    if (type < 37 || type - 1 < 16) {
        return bdat->getPcWpnChipCreateWpn(chip, type - 1);
    }
    return 0;
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

bool GfDataBlade::getTaskSkillMessage(unsigned char*& bdat, unsigned int& id, unsigned int blade, unsigned int line) {
    id = 0;
    ACHIEVEMENT_TYPE type;
    unsigned int index;
    if (GfDataAchievement::getAchievementType(type, index, line)) {
        unsigned int bladeIndex = getBladeIndex(blade);
        SDataGame* game = GfDataManager::getDataGame();
        SDataBlade& data = game->m_blades[bladeIndex];
        switch (type) {
        case 3:
            id = 1;
            bdat = GfBdatMsg::getFpAchievement();
            break;
        case 1: {
            unsigned int skill = data.m_skills[index].m_id;
            id = GfBdatBtl::get()->getBTL_Skill_BlName(skill);
            bdat = GfBdatMsg::getFpBlSkill();
            break;
        }
        case 2: {
            unsigned short skill = data.m_fieldSkills[index].m_id;
            if (skill == 0) {
                break;
            }
            id = QuestListAcc::get()->getFLD_FieldSkillListName(skill);
            bdat = GfBdatMsg::getFpFieldSkill();
            break;
        }
        default: {
            unsigned int arts = data.m_arts[index].m_id;
            id = GfBdatBtl::get()->getArtsBlName(arts);
            bdat = GfBdatMsg::getFpBlArtsMs();
            break;
        }
        }
    }
    return id != 0;
}

bool GfDataBlade::getTaskTitleMessage(unsigned char*& bdat, unsigned int& id, unsigned int blade, unsigned int line,
                                      unsigned int level) {
    AchievInfo* info = getAchievInfo(blade, line);
    QuestID& quest = info->m_quests[level - 1].m_questId;
    if (quest.empty()) {
        return false;
    }
    QuestID next = GfDataQuest::getListNextQuestA(quest);
    if (next.empty()) {
        return false;
    }
    if (GfDataQuest::getListPurposeID(next) == 0) {
        return false;
    }
    id = QuestListAcc::get()->getTaskTaskLog(GfDataQuest::getListPurposeID(next), 0);
    bdat = GfBdatMsg::getFpQuest(next);
    return id != 0;
}

bool GfDataBlade::getTaskResultMessage(unsigned char*& bdat, unsigned int& id, unsigned int blade, unsigned int line,
                                       unsigned int level) {
    AchievInfo* info = getAchievInfo(blade, line);
    QuestID& quest = info->m_quests[level - 1].m_questId;
    if (quest.empty()) {
        return false;
    }
    id = QuestListAcc::get()->getListResultA(quest);
    bdat = GfBdatMsg::getFpQuest(quest);
    return id != 0;
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

bool GfDataBlade::setEquipOrbHandle(unsigned int blade, GfItemHandle handle, unsigned int slot) {
    if (blade == 0) {
        return false;
    }
    SDataBlade* data = getSDataBlade(blade);
    // the original reads the orb count here without using it
    getEquipOrbMax(blade);
    data->m_equipOrbHandles[slot] = handle.m_handle;
    return true;
}

bool GfDataBlade::getEquipOrbEnance(mm::mtl::FixedVector<unsigned short, 64>& enhances, unsigned int blade) {
    if (blade == 0) {
        return false;
    }
    return getEquipOrbEnance(enhances, GfDataManager::getDataGame()->m_blades[getBladeIndex(blade)]);
}

bool GfDataBlade::getEquipOrbEnance(mm::mtl::FixedVector<unsigned short, 64>& enhances, SDataBlade& data) {
    unsigned int max = data.m_equipOrbMax;
    GfBdatItem* item = GfBdatItem::get();
    for (unsigned int i = 0; i < max; i++) {
        if (data.m_equipOrbs[i] != 0) {
            unsigned short enhance = item->getEquipOrbEnhance(data.m_equipOrbs[i]);
            if (enhance != 0) {
                enhances.push_back(enhance);
            }
        }
    }
    if (GfDataHana::isValid(data.m_bladeId)) {
        unsigned int num = GfDataHana::getCondenserNum(data.m_bladeId);
        for (unsigned int i = 0; i < num; i++) {
            if (data.m_equipHana.m_condenserParts[i] != 0) {
                unsigned short enhance = GfBdatItem::get()->getITM_HanaAssistEnhance(data.m_equipHana.m_condenserParts[i]);
                if (enhance != 0) {
                    enhances.push_back(enhance);
                }
            }
        }
        num = GfBdatBtl::get()->getBTL_HanaBaseECondNum(data.m_bladeId - 1004);
        for (unsigned int i = 0; i < num; i++) {
            if (((1 << (i + 3)) & data.m_openCircuit) && data.m_equipHana.m_extendCondenserParts[i] != 0) {
                unsigned short enhance =
                    GfBdatItem::get()->getITM_HanaAssistEnhance(data.m_equipHana.m_extendCondenserParts[i]);
                if (enhance != 0) {
                    enhances.push_back(enhance);
                }
            }
        }
    }
    return enhances.size() != 0;
}

unsigned int GfDataBlade::getCreateEvent(unsigned int blade) {
    SDataBlade& data = GfDataManager::getDataGame()->m_blades[getBladeIndex(blade)];
    return data.m_createEvent;
}

unsigned int GfDataBlade::getNormalTalk(unsigned int blade) {
    SDataBlade& data = GfDataManager::getDataGame()->m_blades[getBladeIndex(blade)];
    return data.m_normalTalk;
}

unsigned int GfDataBlade::getBladeByWeaponType(unsigned int weaponType, unsigned int driver, bool) {
    if (weaponType == 0) {
        return 0;
    }
    if (driver - 17 < 9) {
        return GfBdatChrDr::get()->getChrDrDefBlade1(driver);
    }
    switch (weaponType) {
    case 17:
        return 1012;
    case 4:
        return 1005;
    case 5:
        return 1006;
    case 6:
        return 1007;
    case 18:
        if (driver == 9) {
            return 1073;
        }
        if (driver == 12) {
            return 1110;
        }
        return 1013;
    }
    for (unsigned int i = 0; i < 422; i++) {
        unsigned int blade = getBladeID(i);
        if (blade == 0) {
            continue;
        }
        SDataBlade& data = GfDataManager::getDataGame()->m_blades[getBladeIndex(blade)];
        if (data.m_weaponType == weaponType) {
            return blade;
        }
    }
    return 0;
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

void GfDataBlade::setTrustRank(unsigned int blade, GfIdea rank) {
    GfDataManager::getDataGame()->m_blades[getBladeIndex(blade)].m_trustRank = rank;
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

unsigned int GfDataMercenaries::getTeamPower(unsigned int teamId) {
    Team* team = getTeamByTeamID(teamId);
    if (team == nullptr) {
        return 0;
    }
    unsigned int power = 0;
    for (int i = 0; i < 6; i++) {
        power += GfDataBlade::getBladePower(team->m_members[i]);
    }
    return power;
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

bool GfDataMercenaries::decTeamMissionTime(unsigned int teamId, float time) {
    Team* team = getTeamByTeamID(teamId);
    if (team == nullptr) {
        return false;
    }
    if (team->m_missionTime.hour == 0 && team->m_missionTime.min == 0 && team->m_missionTime.sec == 0) {
        return false;
    }
    team->m_secondCount += time;
    float second = team->m_secondCount;
    unsigned int hour = second / 3600.0f;
    second = fmodf(second, 3600.0f);
    unsigned int min = second / 60.0f;
    second = fmodf(second, 60.0f);
    unsigned int sec = second;
    team->m_secondCount = fmodf(second, 1.0f);
    ElapseTime dec;
    dec.sec = sec;
    dec.hour = hour;
    dec.min = min;
    ElapseTime remain = team->m_missionTime;
    team->m_missionTime = team->m_missionTime - dec;
    bool end = team->m_missionTime.hour == 0 && team->m_missionTime.min == 0 && team->m_missionTime.sec == 0;
    return !(remain.hour == 0 && remain.min == 0 && remain.sec == 0) && end;
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

void GfDataMercenaries::setMissionFlag(unsigned int mission, unsigned int flag) {
    GfGameFlag::setLocal(4, mission + 5, flag);
    int state = GfGameFlag::getLocal(2, mission + 0x87CF);
    if (state >= 2) {
        return;
    }
    int value;
    switch (flag) {
    case 2:
    case 3:
        value = 1;
        break;
    case 4:
        value = 2;
        break;
    default:
        value = 0;
        break;
    }
    if (state != value) {
        GfGameFlag::setLocal(2, mission + 0x87CF, value);
        GfGameFlag::setLocal(2, mission + 0x89C4, value);
    }
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

unsigned int GfDataMercenaries::getMissionIdByBlade(unsigned int blade) {
    SDataGame* game = GfDataManager::getDataGame();
    for (Team* team = game->m_teams.begin(); team != game->m_teams.end(); ++team) {
        for (int i = 0; i < 6; i++) {
            if (team->m_members[i] == blade) {
                return team->m_mission;
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

unsigned int GfDataBlade::getSkillLineId(unsigned int blade, unsigned int line) {
    unsigned int bladeIndex = getBladeIndex(blade);
    SDataGame* game = GfDataManager::getDataGame();
    SDataBlade& data = game->m_blades[bladeIndex];
    ACHIEVEMENT_TYPE type;
    unsigned int index;
    if (!GfDataAchievement::getAchievementType(type, index, line)) {
        return 0;
    }
    unsigned short id = 0;
    switch (type) {
    case 0:
        id = data.m_arts[index].m_id;
        break;
    case 1:
        id = data.m_skills[index].m_id;
        break;
    case 2:
        id = data.m_fieldSkills[index].m_id;
        break;
    }
    return id;
}

bool GfDataDriver::getName(unsigned char*& bdat, unsigned int& id, unsigned int row) {
    id = GfBdatChrDr::get()->getChrDrName(row);
    bdat = GfBdatMsg::getFpChrDr();
    return id != 0;
}

bool GfDataDriverArts::getEnableArts(mm::mtl::FixedArray<unsigned int, 4>& list, unsigned int driver,
                                     unsigned int wpnType, PTPOS mode) {
    list.assign(0);
    GfBdatBtl* bdat = GfBdatBtl::get();
    unsigned int start = bdat->getArtsDrStart();
    unsigned int end = bdat->getArtsDrEnd();
    unsigned int count = 0;
    for (unsigned int arts = start; arts < end; arts++) {
        if (bdat->getArtsDrDriver(arts) != driver) {
            continue;
        }
        if (bdat->getArtsDrWpnType(arts) != wpnType) {
            continue;
        }
        if (bdat->isArtsDrFlagNormal(arts)) {
            continue;
        }
        if (GfDataDriver::isIra(driver) && bdat->getArtsDrIrType(arts) != mode) {
            continue;
        }
        list[count++] = arts;
        if (count >= 4) {
            break;
        }
    }
    return count != 0;
}

void GfDataDriverArts::getSlotArts(mm::mtl::FixedArray<unsigned int, 3>& list, unsigned int driver,
                                   unsigned int wpnType, PTPOS mode) {
    unsigned int* arts;
    switch (mode) {
    case 1:
        arts = GfDataDriver::getDriverWeaponTypeIraBack(driver, wpnType);
        break;
    case 2:
        arts = GfDataDriver::getDriverWeaponTypeIraSwitch(driver, wpnType);
        break;
    default:
        arts = GfDataDriver::getDriverWeaponType(driver, wpnType);
        break;
    }
    memcpy(list.begin(), arts, sizeof(unsigned int) * 3);
}

void GfDataDriverArts::setSlotArts(unsigned int driver, unsigned int wpnType,
                                   const mm::mtl::FixedArray<unsigned int, 3>& list, PTPOS mode) {
    unsigned int* arts;
    switch (mode) {
    case 1:
        arts = GfDataDriver::getDriverWeaponTypeIraBack(driver, wpnType);
        break;
    case 2:
        arts = GfDataDriver::getDriverWeaponTypeIraSwitch(driver, wpnType);
        break;
    default:
        arts = GfDataDriver::getDriverWeaponType(driver, wpnType);
        break;
    }
    memcpy(arts, list.begin(), sizeof(unsigned int) * 3);
}

int GfDataDriverArts::getWp(unsigned int driver, unsigned int wpnType, PTPOS mode) {
    unsigned int* arts;
    switch (mode) {
    case 1:
        arts = GfDataDriver::getDriverWeaponTypeIraBack(driver, wpnType);
        break;
    case 2:
        arts = GfDataDriver::getDriverWeaponTypeIraSwitch(driver, wpnType);
        break;
    default:
        arts = GfDataDriver::getDriverWeaponType(driver, wpnType);
        break;
    }
    return arts[3];
}

void GfDataDriverArts::addWp(unsigned int driver, unsigned int wpnType, int point) {
    int count = GfDataDriver::isIra(driver) ? 3 : 1;
    for (int mode = 0; mode < count; mode++) {
        unsigned int* arts;
        switch (mode) {
        case 1:
            arts = GfDataDriver::getSDataIra(driver)->m_dlcArts[wpnType];
            break;
        case 2:
            arts = GfDataDriver::getSDataIra(driver)->m_dlcArts2[wpnType];
            break;
        default:
            arts = GfDataDriver::getDriverWeaponType(driver, wpnType);
            break;
        }
        unsigned int wp = arts[3] + point;
        if (point < 0 && static_cast<int>(wp) < 0) {
            arts[3] = 0;
        } else {
            arts[3] = wp < 10000000 ? wp : 9999999;
            if (point > 0) {
                int total = arts[4] + point;
                arts[4] = total < 0 ? 0x7FFFFFFF : total;
            }
        }
    }
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
    if (GfGameManager::isGameTypeIra()) {
        unsigned int caption = GfBdatBtl::get()->getBTL_EnhanceCaption2(enhance);
        if (caption != 0) {
            id = caption;
        }
    }
    bdat = GfBdatMsg::getFpBtlEnhanceCap();
    return id != 0;
}

// the skill tree tables of drivers 1 to 6 and 17 to 19. Proposed names, not the original's: the symbols leave them
// unnamed (lbl_7100B50BA0, lbl_7100B50BD0).
static const char* const sSkillTables[] = {"BTL_Skill_Dr_Table01", "BTL_Skill_Dr_Table02", "BTL_Skill_Dr_Table03",
                                           "BTL_Skill_Dr_Table04", "BTL_Skill_Dr_Table05", "BTL_Skill_Dr_Table06"};
static const char* const sSkillTablesEx[] = {"BTL_Skill_Dr_Table17", "BTL_Skill_Dr_Table18", "BTL_Skill_Dr_Table19"};

// the driver's skill tree table; null for a driver without one (the helper's name is not the original's: inlined)
static inline const char* getSkillTableName(unsigned int driver) {
    if (driver - 1 < 6) {
        return sSkillTables[driver - 1];
    }
    if (driver - 17 < 3) {
        return sSkillTablesEx[driver - 17];
    }
    return nullptr;
}

unsigned int GfDataDriverSkill::getSkillFromBdat(unsigned int driver, unsigned int line, unsigned int level,
                                                 bool round) {
    if (level == 0) {
        return 0;
    }
    const char* name = getSkillTableName(driver);
    if (name == nullptr) {
        return 0;
    }
    unsigned char* fp = Bdat::getFP(name);
    return (unsigned short)Bdat::getValCheck(fp, "SkillID", line * 3 + level + (round ? 15 : 0), 2);
}

int GfDataDriverSkill::getSkillCategoryFromBdat(unsigned int driver, unsigned int line, unsigned int level,
                                                bool round) {
    if (level == 0) {
        return 0;
    }
    const char* name = getSkillTableName(driver);
    if (name == nullptr) {
        return 0;
    }
    unsigned char* fp = Bdat::getFP(name);
    unsigned int skill = (unsigned short)Bdat::getValCheck(fp, "SkillID", line * 3 + level + (round ? 15 : 0), 2);
    if (skill == 0) {
        return 0;
    }
    GfBdatBtl* btl = GfBdatBtl::get();
    unsigned int enhance = btl->getBTL_Skill_DrEnhance(skill);
    if (enhance == 0) {
        return 0;
    }
    unsigned int effect = btl->getBTL_EnhanceEnhanceEffect(enhance);
    if (effect == 0) {
        return 0;
    }
    return btl->getBTL_EnhanceEffCategory(effect);
}

int GfDataDriverSkill::getSkillPointFromBdat(unsigned int driver, unsigned int line, unsigned int level, bool round) {
    if (level == 0) {
        return 0;
    }
    const char* name = getSkillTableName(driver);
    if (name == nullptr) {
        return 0;
    }
    unsigned char* fp = Bdat::getFP(name);
    return (unsigned short)Bdat::getValCheck(fp, "NeedSp", line * 3 + level + (round ? 15 : 0), 2);
}

unsigned int GfDataDriverSkill::getEnhanceFromBdat(unsigned int driver, unsigned int line, unsigned int level,
                                                   bool round) {
    if (level == 0) {
        return 0;
    }
    const char* name = getSkillTableName(driver);
    if (name == nullptr) {
        return 0;
    }
    unsigned char* fp = Bdat::getFP(name);
    unsigned int skill = (unsigned short)Bdat::getValCheck(fp, "SkillID", line * 3 + level + (round ? 15 : 0), 2);
    if (skill == 0) {
        return 0;
    }
    return GfBdatBtl::get()->getBTL_Skill_DrEnhance(skill);
}

unsigned int GfDataDriverSkill::getSkill(unsigned int driver, unsigned int line, unsigned int level, bool round) {
    if (level == 0) {
        return 0;
    }
    SDataDriver* data = &GfDataDriver::getSDataDriver(driver);
    unsigned int index = level - 1;
    if (index >= 3) {
        return 0;
    }
    unsigned int id = data->m_id;
    if (id - 1 >= 6 && id - 0x11 < 9) {
        GfBdatChrDr* bdat = GfBdatChrDr::get();
        if (bdat->getChrIrType(bdat->getChrDrIraParam(id)) != 0) {
            return 0;
        }
    }
    return (round ? data->m_roundSkills : data->m_skills)[line][index];
}

bool GfDataDriverSkill::isSkillLevelUnlock(unsigned int driver, unsigned int level, bool round) {
    if (level < 2) {
        return true;
    }
    unsigned char* fp = Bdat::getFP("BTL_SystemBalance");
    unsigned int need = 0;
    if (level == 2) {
        need = static_cast<short>(Bdat::getValCheck(fp, "Param", 136, 5));
    } else if (level == 3) {
        need = static_cast<short>(Bdat::getValCheck(fp, "Param", 137, 5));
    }
    return need <= getValidSkillNum(driver, round);
}

unsigned int GfDataDriverSkill::getSkillLevelUnlockNum(unsigned int driver, unsigned int level, bool round) {
    if (level < 2) {
        return 0;
    }
    unsigned char* fp = Bdat::getFP("BTL_SystemBalance");
    unsigned int need = 0;
    if (level == 2) {
        need = static_cast<short>(Bdat::getValCheck(fp, "Param", 136, 5));
    } else if (level == 3) {
        need = static_cast<short>(Bdat::getValCheck(fp, "Param", 137, 5));
    }
    unsigned int num = getValidSkillNum(driver, round);
    return need > num ? need - num : 0;
}

bool GfDataDriverSkill::isSkillUnlock(unsigned int driver, unsigned int line, unsigned int level, bool round) {
    if (level == 0) {
        return false;
    }
    if (level == 1) {
        return true;
    }
    unsigned char* fp = Bdat::getFP("BTL_SystemBalance");
    unsigned int need = 0;
    if (level == 2) {
        need = static_cast<short>(Bdat::getValCheck(fp, "Param", 136, 5));
    } else if (level == 3) {
        need = static_cast<short>(Bdat::getValCheck(fp, "Param", 137, 5));
    }
    return need <= getValidSkillNum(driver, round);
}

unsigned int GfDataDriverSkill::getSkillLevel(unsigned int driver, unsigned int line, bool round) {
    SDataDriver* data = &GfDataDriver::getSDataDriver(driver);
    unsigned int id = data->m_id;
    if (id - 1 >= 6 && id - 0x11 < 9) {
        GfBdatChrDr* bdat = GfBdatChrDr::get();
        if (bdat->getChrIrType(bdat->getChrDrIraParam(id)) != 0) {
            return 0;
        }
    }
    return (round ? data->m_roundSkills : data->m_skills)[line][4];
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

bool GfDataNpc::getName(unsigned char*& bdat, unsigned int& id, unsigned int npc) {
    if (npc <= 25) {
        id = GfBdatChrDr::get()->getChrDrName(npc);
        bdat = GfBdatMsg::getFpChrDr();
        return id != 0;
    }
    if (npc <= 2000) {
        return GfDataBlade::getName(bdat, id, npc);
    }
    GfDataBdat::getFP(0xA8);
    int n = npc;
    if (n < 26) {
        bdat = GfDataBdat::getFP(424);
    } else if (n < static_cast<int>(GfBdatChrBl::get()->getChrBlEnd())) {
        bdat = GfDataBdat::getFP(423);
    } else if (npc - 1197 < 226) {
        bdat = GfDataBdat::getFP(396);
    } else {
        bdat = GfDataBdat::getFP(437);
    }
    id = GfBdatRsc::get()->getRscNpcListName(npc);
    return id != 0;
}

bool GfDataItem::getName(unsigned char*& bdat, unsigned int& id, unsigned int item) {
    GfBdatItem* data = GfBdatItem::get();
    bdat = nullptr;
    id = 0;
    switch (getItemType(item)) {
    case 1:
        id = data->getPcWpnChipName(item);
        bdat = GfBdatMsg::getFpPcWpnChip();
        break;
    default:
        break;
    case 2:
        id = data->getPcEquipName(item);
        bdat = GfBdatMsg::getFpPcEquip();
        break;
    case 3:
        id = data->getEquipOrbName(item);
        bdat = GfBdatMsg::getFpOrb();
        break;
    case 4:
        id = data->getPcWpnName(item);
        bdat = GfBdatMsg::getFpPcWpn();
        break;
    case 5:
        id = data->getSalvageName(item);
        bdat = GfBdatMsg::getFpSalvage();
        break;
    case 6:
        if (isValidPreciousIra(item)) {
            id = data->getPreciousIraName(item);
        } else {
            id = data->getPreciousName(item);
        }
        bdat = GfBdatMsg::getFpPrecious();
        break;
    case 7:
        id = data->getCollectionListName(item);
        bdat = GfBdatMsg::getFpCollection();
        break;
    case 8:
        id = data->getTresureName(item);
        bdat = GfBdatMsg::getFpTresure();
        break;
    case 9:
        id = data->getEmptyOrbName(item);
        bdat = GfBdatMsg::getFpOrb();
        break;
    case 10:
        id = data->getFavoriteName(item);
        bdat = GfBdatMsg::getFpFavorite();
        break;
    case 11:
        id = data->getCrystalListName(item);
        bdat = GfBdatMsg::getFpCrystal();
        break;
    case 12:
        id = data->getBoosterName(item);
        bdat = GfBdatMsg::getFpBooster();
        break;
    case 13:
        id = 0;
        bdat = nullptr;
        break;
    case 14:
        id = data->getInfoName(item);
        bdat = GfBdatMsg::getFpInfo();
        break;
    case 15:
        id = data->getEventName(item);
        bdat = GfBdatMsg::getFpEvent();
        break;
    case 16:
        id = GfBdatItem::get()->getITM_HanaRoleName(item);
        bdat = GfBdatMsg::getFpBtlHanaRole();
        break;
    case 17:
        id = GfBdatItem::get()->getITM_HanaAtrName(item);
        bdat = GfBdatMsg::getFpBtlHanaAtr();
        break;
    case 18:
        id = GfBdatItem::get()->getITM_HanaArtsEnhName(item);
        bdat = GfBdatMsg::getFpOrb();
        break;
    case 19:
        id = GfBdatItem::get()->getITM_HanaNArtsSetName(item);
        bdat = GfBdatMsg::getFpBtlHanaNArts();
        break;
    case 20:
        id = GfBdatItem::get()->getITM_HanaAssistName(item);
        bdat = GfBdatMsg::getFpOrb();
        break;
    }
    return id != 0 && bdat != nullptr;
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

unsigned char* GfDataNpc::getRscBdatFp(int npc) {
    unsigned char* npcList = GfDataBdat::getFP(0x88);
    unsigned char* npcList2 = GfDataBdat::getFP(0x8A);
    unsigned char* npcList3 = GfDataBdat::getFP(0xA8);
    unsigned char* fp = nullptr;
    if (npc >= Bdat::getIdTop(npcList) && npc < Bdat::getIdTop(npcList) + Bdat::getIdCount(npcList)) {
        fp = npcList;
    } else if (npc >= Bdat::getIdTop(npcList2) && npc < Bdat::getIdTop(npcList2) + Bdat::getIdCount(npcList2)) {
        fp = npcList2;
    } else if (npc >= Bdat::getIdTop(npcList3) && npc < Bdat::getIdTop(npcList3) + Bdat::getIdCount(npcList3)) {
        fp = npcList3;
    }
    return fp;
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

bool GfDataNpc::isEventRetarget(unsigned int id) {
    if (id <= 2000) {
        return false;
    }
    return GfBdatRsc::get()->getRscNpcListEvtRetarget(id) != 0;
}

void GfDataNpc::setTalkBonusFlag(unsigned int id, unsigned int value) {
    GfGameFlag::setLocal(1, id > 43877 ? id + 11651 : id, value);
}

bool GfDataNpc::isTalkBonusFlag(unsigned int id) {
    return GfGameFlag::getLocal(1, id > 43877 ? id + 11651 : id) != 0;
}

bool GfDataNpc::getJobMsg(unsigned char*& bdat, unsigned int& id, unsigned int blade) {
    if (blade <= 2000) {
        return false;
    }
    bdat = GfDataBdat::getFP(0x1C3);
    id = GfBdatRsc::get()->getRscNpcListJob(blade);
    return id != 0;
}

unsigned int GfDataNpc::getPlaceMsgId(unsigned int id) {
    if (id <= 2000) {
        return 0;
    }
    if (GfGameCond::isGameCond(static_cast<unsigned short>(GfBdatRsc::get()->getRscNpcListCondition1(id)))) {
        return GfBdatRsc::get()->getRscNpcListMSGID2(id);
    }
    if (GfGameCond::isGameCond(static_cast<unsigned short>(GfBdatRsc::get()->getRscNpcListCondition2(id)))) {
        return GfBdatRsc::get()->getRscNpcListMSGID3(id);
    }
    return GfBdatRsc::get()->getRscNpcListMSGID(id);
}

bool GfDataNpc::getPlaceMsg(unsigned char*& bdat, unsigned int& id, unsigned int rsc) {
    if (rsc <= 2000) {
        return false;
    }
    bdat = GfDataBdat::getFP(435);
    id = GfDataNpc::getPlaceMsgId(rsc);
    return id != 0;
}

bool GfDataNpc::getResultMsg(unsigned char*& bdat, unsigned int& id, unsigned int rsc) {
    if (rsc <= 2000) {
        return false;
    }
    bdat = GfDataBdat::getFP(452);
    id = GfBdatRsc::get()->getRscNpcListresult(rsc);
    return id != 0;
}

unsigned int GfDataNpc::getHitonowaFlag2Index(unsigned int id) {
    if (id <= 2000) {
        return 0;
    }
    return GfBdatRsc::get()->getRscNpcListHitonowaFlag(id);
}

unsigned int GfDataNpc::getHitonowaMeetsFlag1Index(unsigned int id) {
    if (id <= 2000) {
        return 0;
    }
    return GfBdatRsc::get()->getRscNpcListNpcMeetFlag(id);
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

void GfDataQuest::setOrderTimming(QuestID quest) {
    // quests below 6000 (the main and blade quest ranges; an inline the original passes the id to by value)
    auto isOrderTimmingQuest = [](QuestID id) { return id.m_id < 6000; };
    if (!isOrderTimmingQuest(quest)) {
        return;
    }
    if (QuestListAcc::get()->getListAutoStart(quest) != 0) {
        return;
    }
    for (unsigned int i = 0x619; i < 0x763; i++) {
        unsigned int value = GfGameFlag::getLocal(16, i);
        if (value == quest.m_id) {
            return;
        }
        if (value == 0) {
            GfGameFlag::setLocal(16, i, quest.m_id);
            return;
        }
    }
}

unsigned short GfDataQuest::m_achieve2blade[0x4D80];

unsigned int GfDataQuest::getAchievementBlade(unsigned int achieveId) {
    return m_achieve2blade[achieveId];
}

void GfDataQuest::registAchievementBlade(unsigned int achieveId, unsigned short blade) {
    m_achieve2blade[achieveId] = blade;
}

void GfDataBlade::setupAchievQuest(AchievQuest& quest) {
    quest.m_count = 0;
    quest.m_countMax = 0;
    quest.m_stats = 0;
    QuestListAcc* acc = QuestListAcc::get();
    unsigned int purpose = GfDataQuest::getListPurposeID(GfDataQuest::getListNextQuestA(quest.m_questId));
    if (purpose == 0) {
        return;
    }
    unsigned int type = acc->getTaskTaskType(purpose, 0);
    unsigned int task = acc->getTaskTaskID(purpose, 0);
    if (type == 0) {
        return;
    }
    quest.m_countType = type;
    unsigned int count;
    switch (type) {
    case 1:
        count = acc->getBattleCount(task);
        break;
    case 3:
        count = acc->getCollectCount(task);
        break;
    case 4:
        count = acc->getUseItemNumber(task);
        break;
    case 11:
        count = acc->getFieldSkillCountCount(task);
        break;
    case 12:
        quest.m_countMax = acc->getAchievementCount(task);
        quest.m_stats = acc->getAchievementStatsID(task);
        return;
    default:
        return;
    }
    quest.m_countMax = count;
}

unsigned int GfDataBlade::getKizunaringCompleteNum(unsigned int blade) {
    unsigned int num = 0;
    for (unsigned int line = 0; line < 10; line++) {
        AchievInfo* info = getAchievInfo(blade, line);
        if (info->m_achievementId != 0) {
            for (int i = 0; i < 5; i++) {
                if (info->m_quests[i].m_achievementId != 0) {
                    num += info->m_quests[i].m_flags & 1;
                }
            }
        }
    }
    return num;
}

AchievInfo* GfDataBlade::getAchievInfo(unsigned int blade, unsigned int line) {
    unsigned int bladeIndex = getBladeIndex(blade);
    SDataGame* game = GfDataManager::getDataGame();
    SDataBlade& data = game->m_blades[bladeIndex];
    ACHIEVEMENT_TYPE type;
    unsigned int index;
    if (!GfDataAchievement::getAchievementType(type, index, line)) {
        return data.m_artsAchievement;
    }
    AchievInfo* info = &data.m_keyAchievement;
    switch (type) {
    case 0:
        info = &data.m_artsAchievement[index];
        break;
    case 1:
        info = &data.m_skillAchievement[index];
        break;
    case 2:
        info = &data.m_fieldSkillAchievement[index];
        break;
    }
    return info;
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

unsigned int GfDataBlade::getBLD_NameList(unsigned int blade) {
    if (blade - 1197 < 226) {
        SDataBlade& data = GfDataManager::getDataGame()->m_blades[getBladeIndex(blade)];
        if (data.m_nameMsgAlt != 0) {
            GfBdatBlade* bdat = GfBdatBlade::get();
            for (unsigned int i = bdat->getNameListStart(), end = bdat->getNameListEnd(); i < end; i++) {
                if (bdat->getNameListCategory(i) == data.m_nameMsgAlt) {
                    return i;
                }
            }
        }
    }
    return 0;
}

void GfDataBlade::setUnselect(unsigned int blade, bool unselect) {
    SDataBlade& data = GfDataManager::getDataGame()->m_blades[getBladeIndex(blade)];
    data.m_unselect = unselect;
    GfEvent::callBladeUnselect(blade, unselect);
}

SDataDriver& GfDataDriver::getSDataDriver(unsigned int driver) {
    if (driver - 0x11 < 9) {
        return GfDataManager::getDataGameIra()->m_drivers[driver - 0x11].m_driver;
    }
    unsigned int index = driver - 1;
    SDataGame* game = GfDataManager::getDataGame();
    return game->m_drivers[index < 0x10 ? index : 1];
}

void GfDataDriver::calcDriverBaseParamByLevel(SDataDriver& data) {
    unsigned int id = data.m_id;
    GfBdatChrDr* bdat = GfBdatChrDr::get();
    if (bdat->getChrDrStart() > data.m_id) {
        return;
    }
    unsigned int level = data.m_level;
    data.m_hpMax = bdat->getChrDrHpMaxLv1(id) +
        (bdat->getChrDrHpMaxLv99(id) - bdat->getChrDrHpMaxLv1(id)) * (level - 1) / 98;
    data.m_strength = bdat->getChrDrStrengthLv1(id) +
        (bdat->getChrDrStrengthLv99(id) - bdat->getChrDrStrengthLv1(id)) * (level - 1) / 98;
    data.m_powEther = bdat->getChrDrPowEtherLv1(id) +
        (bdat->getChrDrPowEtherLv99(id) - bdat->getChrDrPowEtherLv1(id)) * (level - 1) / 98;
    data.m_dex = bdat->getChrDrDexLv1(id) +
        (bdat->getChrDrDexLv99(id) - bdat->getChrDrDexLv1(id)) * (level - 1) / 98;
    data.m_agility = bdat->getChrDrAgilityLv1(id) +
        (bdat->getChrDrAgilityLv99(id) - bdat->getChrDrAgilityLv1(id)) * (level - 1) / 98;
    data.m_luck = bdat->getChrDrLuckLv1(id) +
        (bdat->getChrDrLuckLv99(id) - bdat->getChrDrLuckLv1(id)) * (level - 1) / 98;
}

inline SDataDriverArtsEx* GfDataDriver::getSDataDriverArtsEx(unsigned int driver) {
    if (driver - 0x11 < 9) {
        return &GfDataManager::getDataGameIra()->m_driverArtsEx[driver - 0x11];
    }
    unsigned int index = driver - 1;
    SDataGame* game = GfDataManager::getDataGame();
    return &game->m_driverArtsEx[index < 0x10 ? index : 1];
}

unsigned int GfDataDriver::getLevel(const SDataDriver& data) {
    unsigned int driver = data.m_id;
    if (driver - 0x11 < 9) {
        GfBdatChrDr* bdat = GfBdatChrDr::get();
        if (bdat->getChrIrType(bdat->getChrDrIraParam(data.m_id)) != 0) {
            return getLevel(getIraFront(data.m_id));
        }
    }
    return data.m_level;
}

bool GfDataDriver::getEnableLevel(unsigned int& level, unsigned int& value, unsigned int driver) {
    return GfDataDriver::getEnableLevel(level, value, getSDataDriver(driver));
}

unsigned int GfDataDriver::getExp(const SDataDriver& data) {
    unsigned int driver = data.m_id;
    if (driver - 0x11 < 9) {
        GfBdatChrDr* bdat = GfBdatChrDr::get();
        if (bdat->getChrIrType(bdat->getChrDrIraParam(data.m_id)) != 0) {
            return getExp(getSDataDriver(getIraFront(data.m_id)));
        }
    }
    return data.m_exp;
}

unsigned int GfDataDriver::getBattleExp(const SDataDriver& data) {
    unsigned int driver = data.m_id;
    if (driver - 0x11 < 9) {
        GfBdatChrDr* bdat = GfBdatChrDr::get();
        if (bdat->getChrIrType(bdat->getChrDrIraParam(data.m_id)) != 0) {
            return getBattleExp(getSDataDriver(getIraFront(data.m_id)));
        }
    }
    return data.m_battleExp;
}

bool GfDataDriver::isEnableLevelUp(const SDataDriver& data) {
    unsigned int driver = data.m_id;
    if (driver - 0x11 < 9) {
        GfBdatChrDr* bdat = GfBdatChrDr::get();
        if (bdat->getChrIrType(bdat->getChrDrIraParam(data.m_id)) != 0) {
            return isEnableLevelUp(getSDataDriver(getIraFront(data.m_id)));
        }
    }
    unsigned int level = getLevel(data);
    unsigned int end = GfBdatBtl::get()->getGrowEnd();
    if (level >= 99 || level >= end - 1) {
        return false;
    }
    unsigned int exp = getExp(data) + getBattleExp(data);
    return exp >= GfDataUtil::getGrowLevelExp(level + 1);
}

unsigned int GfDataDriver::getBattleExpNextLevel(const SDataDriver& data) {
    unsigned int driver = data.m_id;
    if (driver - 0x11 < 9) {
        GfBdatChrDr* bdat = GfBdatChrDr::get();
        if (bdat->getChrIrType(bdat->getChrDrIraParam(data.m_id)) != 0) {
            return getBattleExpNextLevel(getSDataDriver(getIraFront(data.m_id)));
        }
    }
    unsigned int level = getLevel(data);
    unsigned int exp = getBattleExp(data);
    unsigned int next = GfDataUtil::getGrowLevelExp(level + 1);
    if (exp > next) {
        return next;
    }
    if (level >= 99) {
        return 0;
    }
    return next - exp;
}

unsigned int GfDataDriver::getExpNextLevel(const SDataDriver& data) {
    unsigned int driver = data.m_id;
    if (driver - 0x11 < 9) {
        GfBdatChrDr* bdat = GfBdatChrDr::get();
        if (bdat->getChrIrType(bdat->getChrDrIraParam(data.m_id)) != 0) {
            return getExpNextLevel(getSDataDriver(getIraFront(data.m_id)));
        }
    }
    unsigned int level = getLevel(data);
    unsigned int exp = getBattleExp(data);
    unsigned int next = GfDataUtil::getGrowLevelExp(level + 1);
    if (exp > next) {
        return next;
    }
    if (level >= 99) {
        return 0;
    }
    return next - exp;
}

unsigned int GfDataDriver::getExpUsed(unsigned int driver) {
    if (driver - 0x11 < 9) {
        GfBdatChrDr* bdat = GfBdatChrDr::get();
        if (bdat->getChrIrType(bdat->getChrDrIraParam(driver)) != 0) {
            return getExpUsed(getIraFront(driver));
        }
    }
    unsigned int level = getLevel(getSDataDriver(driver));
    unsigned int exp = 0;
    for (unsigned int i = 0; i < level; i++) {
        exp += GfDataUtil::getGrowLevelExp(i + 1);
    }
    return exp;
}

unsigned int GfDataDriver::getHpMaxRev(const SDataDriver& data) {
    unsigned int driver = data.m_id;
    if (driver - 0x11 < 9) {
        GfBdatChrDr* bdat = GfBdatChrDr::get();
        if (bdat->getChrIrType(bdat->getChrDrIraParam(data.m_id)) != 0) {
            return getHpMaxRev(getSDataDriver(getIraFront(data.m_id)));
        }
    }
    unsigned int rev = 0;
    bool set1002 = false;
    for (int i = 0; i < getMaxSetBladeNum(data); i++) {
        unsigned int blade = getBlade(data, i);
        if (blade != 0) {
            rev += GfDataBlade::getHpMaxRev(blade);
            set1002 |= blade == 1002;
        }
    }
    if (data.m_id == 1 && !GfDataBlade::isActivateUnuse(1002) && !set1002) {
        rev += GfDataBlade::getHpMaxRev(1002);
    }
    return rev;
}

unsigned int GfDataDriver::getStrengthRev(const SDataDriver& data) {
    unsigned int driver = data.m_id;
    if (driver - 0x11 < 9) {
        GfBdatChrDr* bdat = GfBdatChrDr::get();
        if (bdat->getChrIrType(bdat->getChrDrIraParam(data.m_id)) != 0) {
            return getStrengthRev(getSDataDriver(getIraFront(data.m_id)));
        }
    }
    unsigned int rev = 0;
    for (int i = 0; i < getMaxSetBladeNum(data); i++) {
        unsigned int blade = getBlade(data, i);
        if (blade != 0) {
            rev += GfDataBlade::getStrengthRev(blade);
        }
    }
    return rev;
}

unsigned int GfDataDriver::getPowEtherRev(const SDataDriver& data) {
    unsigned int driver = data.m_id;
    if (driver - 0x11 < 9) {
        GfBdatChrDr* bdat = GfBdatChrDr::get();
        if (bdat->getChrIrType(bdat->getChrDrIraParam(data.m_id)) != 0) {
            return getPowEtherRev(getSDataDriver(getIraFront(data.m_id)));
        }
    }
    unsigned int rev = 0;
    for (int i = 0; i < getMaxSetBladeNum(data); i++) {
        unsigned int blade = getBlade(data, i);
        if (blade != 0) {
            rev += GfDataBlade::getPowerEtherRev(blade);
        }
    }
    return rev;
}

unsigned int GfDataDriver::getDexRev(const SDataDriver& data) {
    unsigned int driver = data.m_id;
    if (driver - 0x11 < 9) {
        GfBdatChrDr* bdat = GfBdatChrDr::get();
        if (bdat->getChrIrType(bdat->getChrDrIraParam(data.m_id)) != 0) {
            return getDexRev(getSDataDriver(getIraFront(data.m_id)));
        }
    }
    unsigned int rev = 0;
    for (int i = 0; i < getMaxSetBladeNum(data); i++) {
        unsigned int blade = getBlade(data, i);
        if (blade != 0) {
            rev += GfDataBlade::getDexRev(blade);
        }
    }
    return rev;
}

unsigned int GfDataDriver::getAgilityRev(const SDataDriver& data) {
    unsigned int driver = data.m_id;
    if (driver - 0x11 < 9) {
        GfBdatChrDr* bdat = GfBdatChrDr::get();
        if (bdat->getChrIrType(bdat->getChrDrIraParam(data.m_id)) != 0) {
            return getAgilityRev(getSDataDriver(getIraFront(data.m_id)));
        }
    }
    unsigned int rev = 0;
    for (int i = 0; i < getMaxSetBladeNum(data); i++) {
        unsigned int blade = getBlade(data, i);
        if (blade != 0) {
            rev += GfDataBlade::getAgilityRev(blade);
        }
    }
    return rev;
}

unsigned int GfDataDriver::getLuckRev(const SDataDriver& data) {
    unsigned int driver = data.m_id;
    if (driver - 0x11 < 9) {
        GfBdatChrDr* bdat = GfBdatChrDr::get();
        if (bdat->getChrIrType(bdat->getChrDrIraParam(data.m_id)) != 0) {
            return getLuckRev(getSDataDriver(getIraFront(data.m_id)));
        }
    }
    unsigned int rev = 0;
    for (int i = 0; i < getMaxSetBladeNum(data); i++) {
        unsigned int blade = getBlade(data, i);
        if (blade != 0) {
            rev += GfDataBlade::getLuckRev(blade);
        }
    }
    return rev;
}

unsigned int GfDataDriver::getSkillPoint(const SDataDriver& data) {
    return data.m_skillPoint;
}

void GfDataDriver::addSkillPoint(unsigned int driver, int point) {
    addSkillPoint(getSDataDriver(driver), point);
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
    SDataDriver* data = &getSDataDriver(driver);
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

bool GfDataBlade::getListRegular(mm::mtl::FixedVector<unsigned short, 422>& list) {
    for (unsigned int blade = 1001; blade < 1014; blade++) {
        if (blade != 1012 && blade != 1013) {
            list.push_back(blade);
        }
    }
    return !list.empty();
}

bool GfDataBlade::getListRare(mm::mtl::FixedVector<unsigned short, 422>& list) {
    for (unsigned int blade = 1014; blade < 1051; blade++) {
        list.push_back(blade);
    }
    list.push_back(1104);
    return !list.empty();
}

bool GfDataBlade::getListCommon(mm::mtl::FixedVector<unsigned short, 422>& list) {
    for (unsigned int blade = 1197; blade < 1397; blade++) {
        if (!isActivateUnuse(blade) || isUnselect(blade)) {
            list.push_back(blade);
        }
    }
    return !list.empty();
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

unsigned int* GfDataDriver::getDriverWeaponType(unsigned int driver, unsigned int index) {
    if (index >= 0x1C) {
        SDataDriverArtsEx* ex = getSDataDriverArtsEx(driver);
        return ex->m_arts[index - 0x1C];
    }
    SDataDriver* data = &getSDataDriver(driver);
    return data->m_arts[index];
}

unsigned int* GfDataDriver::getDriverWeaponTypeIraBack(unsigned int driver, unsigned int index) {
    unsigned int row = driver - 0x11 < 9 ? driver : 0x11;
    unsigned int dlc = row - 0x11;
    if (dlc >= 9) {
        unsigned int slot = row - 1;
        dlc = slot < 0x10 ? slot : 1;
    }
    return GfDataManager::getDataGameIra()->m_drivers[dlc].m_dlcArts[index];
}

unsigned int* GfDataDriver::getDriverWeaponTypeIraSwitch(unsigned int driver, unsigned int index) {
    unsigned int row = driver - 0x11 < 9 ? driver : 0x11;
    unsigned int dlc = row - 0x11;
    if (dlc >= 9) {
        unsigned int slot = row - 1;
        dlc = slot < 0x10 ? slot : 1;
    }
    return GfDataManager::getDataGameIra()->m_drivers[dlc].m_dlcArts2[index];
}

GfItemHandle GfDataDriver::getEquipAcceHandle(unsigned int driver, unsigned int slot) {
    SDataDriver* data = &getSDataDriver(driver);
    if (slot < 2) {
        return data->m_equipAcce[slot].m_handle;
    }
    return data->m_equipAcceHandleEx;
}

void GfDataDriver::setEquipAcce(unsigned int driver, unsigned int slot, unsigned int accessory) {
    if (driver == 0) {
        return;
    }
    setEquipAcce(getSDataDriver(driver), slot, accessory);
}

void GfDataDriver::setEquipAcce(SDataDriver& data, unsigned int slot, unsigned int accessory) {
    if (slot < 2) {
        data.m_equipAcce[slot].m_item = accessory;
        return;
    }
    data.m_equipAcceEx = (data.m_equipAcceEx & 0xFFFF0000) | accessory;
}

void GfDataDriver::setEquipAcceHandle(unsigned int driver, unsigned int slot, GfItemHandle handle) {
    if (driver == 0) {
        return;
    }
    SDataDriver* data = &getSDataDriver(driver);
    if (slot < 2) {
        data->m_equipAcce[slot].m_handle = handle;
    } else {
        data->m_equipAcceHandleEx = handle;
    }
}

void GfDataDriver::setEnableExtendEquipAcce(unsigned int driver, bool flag) {
    SDataDriver* data = &getSDataDriver(getSDataDriver(driver).m_id);
    if (flag) {
        data->m_equipAcceEx |= 0x80000000;
    } else {
        data->m_equipAcceEx &= 0x7FFFFFFF;
    }
}

bool GfDataDriver::isEnableExtendEquipAcce(unsigned int driver) {
    return getSDataDriver(getSDataDriver(driver).m_id).m_equipAcceEx >> 31;
}

void GfDataDriver::getEquipWpnType(mm::mtl::FixedVector<unsigned int, 50>& types, unsigned int driver) {
    getEquipWpnType(types, getSDataDriver(driver));
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

void GfDataDriver::getValidEnhance(mm::mtl::FixedVector<unsigned short, 64>& enhances, unsigned int driver) {
    getValidEnhance(enhances, getSDataDriver(driver));
}

bool GfDataDriver::getValidEnhance(mm::mtl::FixedVector<unsigned short, 64>& enhances, const SDataIra& data) {
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

int GfDataMercenaries::getTeamAnimalNum(unsigned int teamId) {
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
            if (data.m_questRace == 2) {
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
    SDataPouch* dst = getSDataDriver(driver).m_pouches + pouch;
    dst->m_open = data.m_open;
    dst->itemId = data.itemId;
    dst->remainTime = data.remainTime;
}

bool GfDataDriver::isIra(unsigned int driver) {
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

void GfDataUtil::setClearGame(SDataGame& game, bool flag) {
    GfGameFlag::setLocal(game.m_gameFlag, 1, 0xBDCD, flag);
}

unsigned short GfDataUtil::getScenarioFlag() {
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

// the event tables fn_710024EBD8 and getEventID walk: a GfDataBdat table id each, with a second value (100 in each;
// nothing seen here reads it). The type and its names are not the original's (its constructor is not constexpr:
// the static initialiser stores the pairs).
struct EventBdat {
    EventBdat(unsigned int bdat, unsigned int value) : m_bdat(bdat), m_value(value) {}
    unsigned int m_bdat;
    unsigned int m_value;
};

static EventBdat s_eventBdats[5] = {EventBdat(0xE8, 100), EventBdat(0xEC, 100), EventBdat(0xE9, 100),
                                    EventBdat(0xEA, 100), EventBdat(0xEB, 100)};
// the maps' weather records when the game data has no free or matching one (GfDataMap::getEmptyWeatherParam, GfDataMap::getWeatherParam; the
// name is not the original's)
static SDataWeather s_weather;

WeatherParam* GfDataMap::getEmptyWeatherParam() {
    SDataGame* game = GfDataManager::getDataGame();
    int i = game->m_weather.find(0);
    if (i >= 0) {
        return &game->m_weather.m_params[i];
    }
    i = s_weather.find(0);
    if (i >= 0) {
        return &s_weather.m_params[i];
    }
    static WeatherParam s_param;
    return &s_param;
}

WeatherParam* GfDataMap::getWeatherParam(unsigned int map) {
    static WeatherParam s_param;
    if (map != 0) {
        SDataGame* game = GfDataManager::getDataGame();
        int i;
        if (GfBdatMaplist::get()->getMaplistresource(map) != nullptr && (i = game->m_weather.find(map)) >= 0) {
            return &game->m_weather.m_params[i];
        }
        if (GfBdatMaplist::get()->getMaplistresource(map) != nullptr && (i = s_weather.find(map)) >= 0) {
            return &s_weather.m_params[i];
        }
        s_param.m_mapId = 0;
    }
    return &s_param;
}

unsigned int GfDataEvent::fn_710024EBD8(unsigned int event) {
    for (int i = 0; i < 5; i++) {
        unsigned char* fp = GfDataBdat::getFP(s_eventBdats[i].m_bdat);
        unsigned int top = Bdat::getIdTop(fp);
        unsigned int count = Bdat::getIdCount(fp);
        if (top <= event && event < top + count) {
            return s_eventBdats[i].m_bdat;
        }
    }
    return 0;
}

void GfDataBtlDif::setOptionGameDifficultCustom(SSoundUiOption& option, unsigned int index, unsigned char value) {
    if (GfBdatBtl::get() == nullptr) {
        return;
    }
    option.m_keyD = 4;
    option.m_list[index - 1] = value;
    GfDataBtlDif::setCustomFollow(option);
}

// a BTL_DifSetting row's value for slot (0 without GfBdatBtl); every user inlines it, so the name is not the
// original's
static unsigned int getDifSettingValue(unsigned int id, unsigned int slot) {
    GfBdatBtl* bdat = GfBdatBtl::get();
    if (bdat == nullptr) {
        return 0;
    }
    return bdat->getBTL_DifSettingDiff(id, slot);
}

// a BTL_DifSetting value as a level: (value - ParamMin) / Interval, 0 without GfBdatBtl or with Interval 0; every
// user inlines it, so the name is not the original's
static unsigned char getDifSettingLevel(unsigned int id, unsigned int value) {
    GfBdatBtl* bdat = GfBdatBtl::get();
    if (bdat == nullptr) {
        return 0;
    }
    unsigned int min = bdat->getBTL_DifSettingParamMin(id);
    bdat->getBTL_DifSettingParamMax(id);
    unsigned int interval = bdat->getBTL_DifSettingInterval(id);
    if (interval == 0) {
        return 0;
    }
    return (value - min) / interval;
}

void GfDataBtlDif::setCustomFollow(SSoundUiOption& option) {
    option.m_list[11 - 1] = getDifSettingLevel(11, getDifSettingValue(11, 0));
    option.m_list[12 - 1] = getDifSettingLevel(12, getDifSettingValue(12, 0));
}

void GfDataBtlDif::setOptionGameDifficult(SSoundUiOption& option, GFDIFF type) {
    option.m_keyD = 6;
    if (GfBdatBtl::get() == nullptr) {
        return;
    }
    if (type == 4) {
        GfDataBtlDif::setCustomFollow(option);
    } else {
        for (unsigned int i = 0; i < 0xF; i++) {
            option.m_list[i] = getDifSettingLevel(i + 1, getDifSettingValue(i + 1, type));
        }
    }
    option.m_keyD = type;
}

unsigned int GfDataBtlDif::getBtlDifParam(const SSoundUiOption& option, unsigned int index) {
    GfBdatBtl* bdat = GfBdatBtl::get();
    if (bdat == nullptr) {
        return 0;
    }
    unsigned char level;
    if (option.m_keyD == 4) {
        level = option.m_list[index - 1];
    } else {
        level = getDifSettingLevel(index, getDifSettingValue(index, option.m_keyD));
    }
    unsigned int min = bdat->getBTL_DifSettingParamMin(index);
    bdat->getBTL_DifSettingParamMax(index);
    unsigned int interval = bdat->getBTL_DifSettingInterval(index);
    return min + interval * level;
}

unsigned char GfDataBtlDif::getBtlDifStep(const SSoundUiOption& option, unsigned int index) {
    if (GfBdatBtl::get() == nullptr) {
        return 0;
    }
    return option.m_list[index - 1];
}

// the hitonowa list with one NPC per hitonowa flag value (GfDataHitonowa::bdatRefresh fills it): a function-static list whose
// accessor every user inlines (no copy of its own), so the name is not the original's
static mm::mtl::FixedVector<unsigned short, 256>& getHitonowaFlagNpcList();


void GfDataHitonowa::initialize() {
    GfDataHitonowa::getList().clear();
    getHitonowaFlagNpcList().clear();
}
void GfDataHitonowa::finalize() {
    GfDataHitonowa::getList().clear();
    getHitonowaFlagNpcList().clear();
}
void GfDataHitonowa::bdatRefresh() {
    GfDataHitonowa::getList().clear();
    getHitonowaFlagNpcList().clear();
    GfBdatRsc* bdat = GfBdatRsc::get();
    for (unsigned int id = bdat->getRscNpcListStart(), end = bdat->getRscNpcListEnd(); id < end; id++) {
        unsigned int flag = GfDataNpc::getHitonowaFlag2Index(id);
        if (flag == 0) {
            continue;
        }
        GfDataHitonowa::getList().push_back(id);
        mm::mtl::FixedVector<unsigned short, 256>& list = getHitonowaFlagNpcList();
        bool found = false;
        for (unsigned short other : list) {
            if (GfDataNpc::getHitonowaFlag2Index(other) == flag) {
                found = true;
                break;
            }
        }
        if (!found) {
            getHitonowaFlagNpcList().push_back(id);
        }
    }
}
mm::mtl::FixedVector<unsigned short, 256>& GfDataHitonowa::getList() {
    static mm::mtl::FixedVector<unsigned short, 256> s_list;
    return s_list;
}

static mm::mtl::FixedVector<unsigned short, 256>& getHitonowaFlagNpcList() {
    static mm::mtl::FixedVector<unsigned short, 256> s_list;
    return s_list;
}

void GfDataHitonowa::getCompleteNum(unsigned int& set, unsigned int& total) {
    set = 0;
    total = 0;
    mm::mtl::FixedVector<unsigned short, 256>& list = getHitonowaFlagNpcList();
    for (const unsigned short& id : list) {
        total++;
        unsigned int flag = GfDataNpc::getHitonowaFlag2Index(id);
        if (flag != 0) {
            unsigned int state = GfGameFlag::getLocal(2, flag);
            if (state == 1 || state == 3) {
                set++;
            }
        }
    }
}

int GfDataHitonowa::getMeetsNum() {
    int count = 0;
    mm::mtl::FixedVector<unsigned short, 256>& list = getHitonowaFlagNpcList();
    for (unsigned short id : list) {
        if (id > 2000) {
            unsigned int flag = GfBdatRsc::get()->getRscNpcListNpcMeetFlag(id);
            if (flag != 0 && GfGameFlag::getLocal(1, flag) != 0) {
                count++;
            }
        }
    }
    return count;
}

int GfDataHitonowa::getHitonowaNum() {
    int count = 0;
    mm::mtl::FixedVector<unsigned short, 256>& list = getHitonowaFlagNpcList();
    for (unsigned short id : list) {
        unsigned int flag = GfDataNpc::getHitonowaFlag2Index(id);
        unsigned int state = flag != 0 ? GfGameFlag::getLocal(2, flag) : 0;
        if (state == 1) {
            count++;
        }
    }
    return count;
}

unsigned int GfDataHitonowa::getEntryOn(unsigned int id) {
    if (id <= 2000) {
        return 0;
    }
    unsigned int rsc = GfBdatRsc::get()->getRscNpcListHitonowaFlag(id);
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

unsigned int GfDataHitonowa::getEntryComplete(unsigned int id) {
    if (id <= 2000) {
        return 0;
    }
    unsigned int rsc = GfBdatRsc::get()->getRscNpcListHitonowaFlag(id);
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

const char* GfDataMap::getWeatherSndName(WEATYPE type) {
    if (type == 0) {
        return "";
    }
    GfBdatMaplist* maplist = GfBdatMaplist::get();
    if (GfDataUtil::isIra()) {
        return maplist->getWeatherInfosnd_ira(type);
    }
    return maplist->getWeatherInfosnd(type);
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

unsigned int GfDataMap::getWeatherIdByWeaType(unsigned int mapId, WEATYPE type) {
    GfBdatMaplist* bdat = GfBdatMaplist::get();
    if (bdat->getMaplistw_type(mapId, 0) == type) {
        return 1;
    }
    if (bdat->getMaplistw_type(mapId, 1) == type) {
        return 2;
    }
    if (bdat->getMaplistw_type(mapId, 2) == type) {
        return 3;
    }
    if (bdat->getMaplistw_type(mapId, 3) == type) {
        return 4;
    }
    return 5;
}

CLOUD_SEA GfDataMap::getCloudType(unsigned int map) {
    return CLOUD_SEA(GfDataMap::getWeatherParam(map)->m_cloudSea != 0);
}

void GfDataMap::setCloudType(unsigned int map, CLOUD_SEA cloudSea) {
    GfDataMap::getWeatherParam(map)->m_cloudSea = cloudSea != 0;
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

void GfDataItem::addCraftFlag(unsigned int item) {
    static const unsigned int s_items[] = {108, 109, 110, 111, 112, 113};
    for (int i = 0; i < 6; i++) {
        if (s_items[i] == item) {
            int flag = 2166 + i;
            unsigned int count = GfGameFlag::getLocal(8, flag);
            if (count >= 255) {
                return;
            }
            GfGameFlag::setLocal(8, flag, count + 1);
            return;
        }
    }
}

void GfDataItem::setCraftFlag(unsigned int item, bool set) {
    // each group's first item id (lbl_71009BA398; the name is inferred)
    static const unsigned short s_groupTop[] = {739, 750, 765, 780, 795, 805, 820, 829, 839, 854};
    if (item < 739 || item >= 854) {
        return;
    }
    unsigned int group;
    if (item < 750) {
        group = 0;
    } else if (item < 765) {
        group = 1;
    } else if (item < 780) {
        group = 2;
    } else if (item < 795) {
        group = 3;
    } else if (item < 805) {
        group = 4;
    } else if (item < 820) {
        group = 5;
    } else if (item < 829) {
        group = 6;
    } else if (item < 839) {
        group = 7;
    } else if (item < 854) {
        group = 8;
    } else {
        return;
    }
    int flag = item + group * 32 + 56736 - s_groupTop[group];
    if (flag == 0) {
        return;
    }
    if ((GfGameFlag::getLocal(1, flag) != 0) != set) {
        GfGameFlag::setLocal(1, flag, set);
    }
    for (int i = 0; i < 9; i++) {
        unsigned int count = 0;
        for (int j = 0; j < 32; j++) {
            if (GfGameFlag::getLocal(1, 56736 + i * 32 + j) != 0) {
                count++;
            }
        }
        unsigned int value = count > 255 ? 255 : count;
        GfGameFlag::setLocal(8, 4275 + i, value);
    }
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

const char* GfDataFobj::getFobjModelName(unsigned int id) {
    unsigned char* fp = Bdat::getFP(GfDataUtil::isIra() ? "RSC_dropitemListIra" : "RSC_dropitemList");
    const char* model = nullptr;
    if (fp != nullptr) {
        model = reinterpret_cast<const char*>(Bdat::getValCheck(fp, "mdo", id, 7));
    }
    return model == nullptr ? "" : model;
}

unsigned int GfDataSalvage::getSalvageSkillLevel(unsigned int blade) {
    unsigned char level = 0;
    if (blade != 0) {
        unsigned int index = GfDataBlade::getBladeIndex(blade);
        SDataGame* game = GfDataManager::getDataGame();
        for (int i = 0; i < 3; i++) {
            if (game->m_blades[index].m_fieldSkills[i].m_id == 9 &&
                level < game->m_blades[index].m_fieldSkills[i].m_level) {
                level = game->m_blades[index].m_fieldSkills[i].m_level;
            }
        }
    }
    return level;
}

unsigned int GfDataItem::getItemType(unsigned int item) {
    ItemType::Type type;
    unsigned int index;
    return getItemType(type, index, item) ? type : 0;
}

bool GfDataItem::getCaption(unsigned char*& bdat, unsigned int& id, unsigned int item) {
    GfBdatItem* data = GfBdatItem::get();
    switch (getItemType(item)) {
    case 5:
        id = data->getSalvageCaption(item);
        bdat = GfBdatMsg::getFpSalvage();
        break;
    case 6:
        if (isValidPreciousIra(item)) {
            id = data->getPreciousIraCaption(item);
        } else {
            id = data->getPreciousCaption(item);
        }
        bdat = GfBdatMsg::getFpPrecious();
        return true;
    case 7:
        id = data->getCollectionListCaption(item);
        bdat = GfBdatMsg::getFpCollection();
        break;
    case 8:
        id = data->getTresureCaption(item);
        bdat = GfBdatMsg::getFpTresure();
        break;
    case 10:
        id = data->getFavoriteCaption(item);
        bdat = GfBdatMsg::getFpFavorite();
        break;
    case 12:
        id = data->getBoosterCaption(item);
        bdat = GfBdatMsg::getFpBooster();
        break;
    case 14:
        id = data->getInfoCaption(item);
        bdat = GfBdatMsg::getFpInfo();
        return true;
    case 15:
        id = data->getEventCaption(item);
        bdat = GfBdatMsg::getFpEvent();
        return true;
    }
    return id != 0 && bdat != nullptr;
}

bool GfDataItem::getItemType(ItemType::Type& type, unsigned int& index, unsigned int item) {
    if (item == 0) {
        return false;
    }
    GfBdatItem* data = GfBdatItem::get();
    if (item < data->getPcEquipEnd()) {
        unsigned int armor = GfBdatItem::get()->getPcEquipArmorType(item);
        if (armor == 0) {
            type = static_cast<ItemType::Type>(2);
        } else if (armor == 2) {
            type = static_cast<ItemType::Type>(2);
        }
        index = item - data->getPcEquipStart();
    } else if (item < data->getPcWpnEnd()) {
        type = static_cast<ItemType::Type>(4);
        index = item - data->getPcWpnStart();
    } else if (item < data->getPcWpnChipEnd()) {
        type = static_cast<ItemType::Type>(1);
        index = item - data->getPcWpnChipStart();
    } else if (item < data->getEmptyOrbEnd()) {
        type = static_cast<ItemType::Type>(9);
        index = item - data->getEmptyOrbStart();
    } else if (item < data->getEquipOrbEnd()) {
        type = static_cast<ItemType::Type>(3);
        index = item - data->getEquipOrbStart();
    } else if (item < data->getSalvageEnd()) {
        type = static_cast<ItemType::Type>(5);
        index = item - data->getSalvageStart();
    } else if (item < data->getPreciousIraEnd()) {
        type = static_cast<ItemType::Type>(6);
        index = item - data->getPreciousStart();
    } else if (item < data->getInfoEnd()) {
        type = static_cast<ItemType::Type>(14);
        index = item - data->getInfoStart();
    } else if (item < data->getEventEnd()) {
        type = static_cast<ItemType::Type>(15);
        index = item - data->getEventStart();
    } else if (item < data->getCollectionListEnd()) {
        type = static_cast<ItemType::Type>(7);
        index = item - data->getCollectionListStart();
    } else if (item < data->getTresureEnd()) {
        type = static_cast<ItemType::Type>(8);
        index = item - data->getTresureStart();
    } else if (item < data->getFavoriteEnd()) {
        type = static_cast<ItemType::Type>(10);
        index = item - data->getFavoriteStart();
    } else if (item < data->getCrystalListEnd()) {
        type = static_cast<ItemType::Type>(11);
        index = item - data->getCrystalListStart();
    } else if (item < data->getBoosterEnd()) {
        type = static_cast<ItemType::Type>(12);
        index = item - data->getBoosterStart();
    } else if (item < data->getHealPotEnd()) {
        type = static_cast<ItemType::Type>(13);
        index = item - data->getHealPotStart();
    } else if (item < data->getITM_HanaRoleEnd()) {
        type = static_cast<ItemType::Type>(16);
        index = item - data->getITM_HanaRoleStart();
    } else if (item < data->getITM_HanaAtrEnd()) {
        type = static_cast<ItemType::Type>(17);
        index = item - data->getITM_HanaAtrStart();
    } else if (item < data->getITM_HanaArtsEnhEnd()) {
        type = static_cast<ItemType::Type>(18);
        index = item - data->getITM_HanaArtsEnhStart();
    } else if (item < data->getITM_HanaNArtsSetEnd()) {
        type = static_cast<ItemType::Type>(19);
        index = item - data->getITM_HanaNArtsSetStart();
    } else if (item < data->getITM_HanaAssistEnd()) {
        type = static_cast<ItemType::Type>(20);
        index = item - data->getITM_HanaAssistStart();
    } else {
        return false;
    }
    index++;
    return true;
}

bool GfDataItem::isEnableSell(unsigned int item) {
    ItemType::Type type;
    unsigned int index;
    int kind = getItemType(type, index, item) ? static_cast<int>(type) : 0;
    GfBdatItem* data = GfBdatItem::get();
    bool enable = true;
    switch (kind) {
    case 1:
        enable = !data->isPcWpnChipFlagNoSell(item);
        break;
    case 2:
        enable = !data->isPcEquipFlagNoSell(item);
        break;
    case 3:
        enable = !data->isEquipOrbFlagNoSell(item);
        break;
    default:
    case 4:
    case 6:
        enable = false;
        break;
    case 5:
        enable = data->getSalvageNoSell(item) == 0;
        break;
    case 7:
    case 8:
    case 10:
    case 12:
        break;
    case 9:
        enable = !data->isEmptyOrbFlagNoSell(item);
        break;
    case 11:
        enable = data->getCrystalListNoMultiple(item) == 0;
        break;
    }
    return enable;
}

unsigned int GfDataItem::getItemStartID(ItemType::Type type) {
    unsigned int begin;
    unsigned int end;
    return getItemBdatCount(begin, end, type) ? begin : 0;
}

bool GfDataItem::getItemBdatCount(unsigned int& begin, unsigned int& end, ItemType::Type type) {
    begin = 0;
    end = 0;
    GfBdatItem* data = GfBdatItem::get();
    switch (static_cast<int>(type)) {
    case 1:
        end = data->getPcWpnChipEnd();
        begin = data->getPcWpnChipStart();
        break;
    case 2:
        end = data->getPcEquipEnd();
        begin = data->getPcEquipStart();
        break;
    case 3:
        end = data->getEquipOrbEnd();
        begin = data->getEquipOrbStart();
        break;
    case 5:
        end = data->getSalvageEnd();
        begin = data->getSalvageStart();
        break;
    case 6:
        end = data->getPreciousIraEnd();
        begin = data->getPreciousStart();
        break;
    case 7:
        end = data->getCollectionListEnd();
        begin = data->getCollectionListStart();
        break;
    case 8:
        end = data->getTresureEnd();
        begin = data->getTresureStart();
        break;
    case 9:
        end = data->getEmptyOrbEnd();
        begin = data->getEmptyOrbStart();
        break;
    case 10:
        end = data->getFavoriteEnd();
        begin = data->getFavoriteStart();
        break;
    case 11:
        end = data->getCrystalListEnd();
        begin = data->getCrystalListStart();
        break;
    case 12:
        end = data->getBoosterEnd();
        begin = data->getBoosterStart();
        break;
    case 14:
        end = data->getInfoEnd();
        begin = data->getInfoStart();
        break;
    case 15:
        end = data->getEventEnd();
        begin = data->getEventStart();
        break;
    case 16:
        end = data->getITM_HanaRoleEnd();
        begin = data->getITM_HanaRoleStart();
        break;
    case 17:
        end = data->getITM_HanaAtrEnd();
        begin = data->getITM_HanaAtrStart();
        break;
    case 18:
        end = data->getITM_HanaArtsEnhEnd();
        begin = data->getITM_HanaArtsEnhStart();
        break;
    case 19:
        end = data->getITM_HanaNArtsSetEnd();
        begin = data->getITM_HanaNArtsSetStart();
        break;
    case 20:
        end = data->getITM_HanaAssistEnd();
        begin = data->getITM_HanaAssistStart();
        break;
    default:
        return false;
    }
    return true;
}

unsigned int GfDataItem::getPrice(unsigned int item) {
    ItemType::Type type;
    unsigned int index;
    int kind = getItemType(type, index, item) ? static_cast<int>(type) : 0;
    GfBdatItem* data = GfBdatItem::get();
    unsigned int price = 0;
    switch (kind) {
    case 1:
        if (GfGameFlag::getLocal(GfDataManager::getDataGame()->m_gameFlag, 1, 55392) != 0) {
            price = data->getPcWpnChipPriceIra(item);
        } else {
            price = data->getPcWpnChipPrice(item);
        }
        break;
    case 2:
        price = data->getPcEquipPrice(item);
        break;
    case 3:
        price = data->getEquipOrbPrice(item);
        break;
    case 5:
        price = data->getSalvagePrice(item);
        break;
    case 6:
        if (isValidPreciousIra(item)) {
            price = data->getPreciousIraPrice(item);
        } else {
            price = data->getPreciousPrice(item);
        }
        break;
    case 7:
        price = data->getCollectionListPrice(item);
        break;
    case 8:
        price = data->getTresurePrice(item);
        break;
    case 9:
        price = data->getEmptyOrbPrice(item);
        break;
    case 10:
        price = data->getFavoritePrice(item);
        break;
    case 11:
        price = data->getCrystalListPrice(item);
        break;
    case 12:
        price = data->getBoosterPrice(item);
        break;
    case 14:
        price = data->getInfoPrice(item);
        break;
    }
    return price;
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

bool GfDataEnemy::isHideExtraParts(unsigned int rsc, unsigned int part) {
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

void GfDataEnemy::incNamedDefeatNum() {
    unsigned int count = GfGameFlag::getLocal(8, 0x874);
    if (count > 0xFE) {
        return;
    }
    GfGameFlag::setLocal(8, 0x874, count + 1);
}

bool GfDataBlade::isDisableHomuraHikari(unsigned int blade) {
    if (GfDataParty::isExistBlade(1001) != GfDataParty::isExistBlade(1002)) {
        return false;
    }
    SDataGame* game = GfDataManager::getDataGame();
    (void)game;
    if (blade == 1002) {
        if (!isHikariCurrent()) {
            return true;
        }
    } else if (blade == 1001) {
        if (isHikariCurrent()) {
            return true;
        }
    }
    return false;
}

bool GfDataParty::isExistBlade(unsigned int blade) {
    if (blade == 0) {
        return false;
    }
    return GfDataParty::isExistBlade(0, blade) || GfDataParty::isExistBlade(1, blade) ||
           GfDataParty::isExistBlade(2, blade);
}

unsigned int GfDataDriver::getIraBlade(unsigned int driver, int slot) {
    if (driver - 0x11 < 9) {
        mm::mtl::FixedVector<unsigned short, 32> back;
        getIraBack(back, driver);
        unsigned int id = driver;
        if (slot == 0) {
            if (back.empty()) {
                return 0;
            }
            id = back.begin()[0];
        } else if (slot == 1) {
            if (back.size() >= 2) {
                id = back.begin()[1];
            } else {
                return 0;
            }
        }
        return GfBdatChrDr::get()->getChrDrDefBlade(id, 0);
    }
    return 0;
}

bool GfDataBlade::isDummyBlade(unsigned int blade) {
    return blade - 1124 < 9 || blade - 1012 < 2 || blade == 1073 || blade == 1110;
}

bool GfDataBlade::getListPartyAll(mm::mtl::FixedVector<unsigned short, 422>& list) {
    if (GfDataUtil::isIra()) {
        for (unsigned int driver = 17; driver < 26; driver++) {
            if (!GfDataDriver::isIraFront(driver) && GfDataDriver::isActivatePartyAll(driver)) {
                unsigned int blade = GfDataDriver::getIraBlade(driver, -1);
                if (!isUnselect(blade)) {
                    list.push_back(blade);
                }
            }
        }
    } else {
        for (unsigned int i = 0; i < 422; i++) {
            unsigned int blade = getBladeID(i);
            if (blade == 0) {
                continue;
            }
            if (!isActivateDriver(blade)) {
                continue;
            }
            unsigned int driver = getSetDriver(blade);
            if (GfDataDriver::isActivatePartyAll(driver) && !isDummyBlade(blade) && !isUnselect(blade)) {
                list.push_back(blade);
            }
        }
    }
    return !list.empty();
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

unsigned char GfDataHana::getMercenaryUnuse(unsigned int hana) {
    if (!isValid(hana)) {
        return 0;
    }
    return GfDataManager::getDataGame()->m_blades[GfDataBlade::getBladeIndex(hana)].m_hanaTeamFlag;
}

void GfDataHana::setMercenaryUnuse(unsigned int hana, unsigned char flag) {
    if (isValid(hana)) {
        GfDataManager::getDataGame()->m_blades[GfDataBlade::getBladeIndex(hana)].m_hanaTeamFlag = flag;
    }
}

unsigned int GfDataHana::getMercenary() {
    // Proposed name, not the original's: the symbols leave it unnamed (lbl_71009BA374)
    static const unsigned short s_blades[3] = {1005, 1006, 1007};
    for (const unsigned short& blade : s_blades) {
        if (GfDataBlade::getSDataBlade(blade)->m_dataType == 2) {
            return blade;
        }
    }
    return 0;
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

unsigned int GfDataNanakoori::getLevelForNanakoori(unsigned int count) {
    if (count == 0) {
        return 1;
    }
    if (count < 3) {
        return 2;
    }
    if (count < 9) {
        return 3;
    }
    if (count < 17) {
        return 4;
    }
    if (count < 30) {
        return 5;
    }
    if (count < 50) {
        return 6;
    }
    if (count < 75) {
        return 7;
    }
    if (count < 99) {
        return 8;
    }
    return 9;
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

unsigned int GfDataEnBook::getDefeatNum(const SDataGame& game, unsigned int arrange) {
    if (arrange == 0) {
        return 0;
    }
    unsigned int book = GfBdatChrEnArrange::get()->getChrEnArrangeBookID(arrange);
    if (book == 0) {
        return 0;
    }
    return GfGameFlag::getLocal(game.m_gameFlag, 0x20, book + 0x142);
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

// the id of the row of the event table fp whose "evtName" is name, 0 for none (getEventID's per-table search;
// inlined, so the name is not the original's)
static unsigned int findEventID(unsigned char* fp, const char* name) {
    unsigned int top = Bdat::getIdTop(fp);
    unsigned int end = top + Bdat::getIdCount(fp);
    for (unsigned int id = top; id < end; id++) {
        const char* evtName = reinterpret_cast<const char*>(Bdat::getValCheck(fp, "evtName", id, 7));
        if (evtName == nullptr) {
            continue;
        }
        if (strcmp(evtName, name) == 0) {
            return id;
        }
    }
    return 0;
}

unsigned int GfDataEvent::getEventID(const char* name) {
    for (unsigned int i = 0; i < 5; i++) {
        unsigned int id = findEventID(GfDataBdat::getFP(s_eventBdats[i].m_bdat), name);
        if (id != 0) {
            return id;
        }
    }
    return 0;
}

int GfDataEvent::getEventPlayFlag(unsigned int event) {
    if (event == 0) {
        return -1;
    }
    int offset = 0;
    for (int i = 0; i < 5; i++) {
        unsigned char* fp = GfDataBdat::getFP(s_eventBdats[i].m_bdat);
        int top = Bdat::getIdTop(fp);
        if (static_cast<int>(event) < top + static_cast<int>(Bdat::getIdCount(fp))) {
            if (static_cast<int>(Bdat::getIdCount(fp)) >= static_cast<int>(s_eventBdats[i].m_value)) {
                return -1;
            }
            int flag = Bdat::getIdTop(fp) - event + offset;
            if (flag >= 2000) {
                return -1;
            }
            return flag + 35423;
        }
        offset += s_eventBdats[i].m_value;
    }
    return -1;
}

unsigned int GfDataEvent::getMapjumpID(unsigned int event) {
    if (event == 0) {
        return 0;
    }
    unsigned char* fp = GfDataBdat::getFP(fn_710024EBD8(event));
    if (fp == nullptr) {
        return 0;
    }
    int top = Bdat::getIdTop(fp);
    int count = Bdat::getIdCount(fp);
    unsigned short zone = Bdat::getValCheckU16(fp, "zoneID", event);
    if (zone == 0) {
        return 0;
    }
    unsigned int jump = GfDataMap::getMapJumpID(zone);
    if (jump != 0) {
        return jump;
    }
    unsigned char* dlc = GfDataBdat::getFP(183);
    unsigned int begin = Bdat::getIdTop(dlc);
    unsigned int end = Bdat::getIdCount(dlc) + begin;
    for (unsigned int id = begin; id < end; id++) {
        if (static_cast<unsigned char>(Bdat::getValCheck(dlc, "MapList", id, 1)) == zone) {
            return id;
        }
    }
    return 0;
}


SDataBlade* GfDataBlade::getSDataBlade(unsigned int blade) {
    return &GfDataManager::getDataGame()->m_blades[getBladeIndex(blade)];
}

unsigned int GfDataDriver::getDriverBySetBlade(unsigned int blade) {
    return GfDataManager::getDataGame()->m_blades[GfDataBlade::getBladeIndex(blade)].m_setDriver;
}

unsigned int GfDataBlade::getDriverSetID(unsigned int blade) {
    if (blade == 0) {
        return -1;
    }
    unsigned int driver = getSetDriver(blade);
    if (driver == 0) {
        return -1;
    }
    return GfDataDriver::getSetIdByBlade(driver, blade);
}

unsigned int GfDataDriver::getDummyBlade(unsigned int driver) {
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

int GfDataParty::getDriverPartyID(unsigned int driver) {
    if (driver == 0) {
        return -1;
    }
    for (int i = 0; i < 10; i++) {
        if (GfDataManager::getDataGame()->m_party.m_members[i].m_driver == driver) {
            return i;
        }
    }
    if (driver - 0x11 < 9) {
        for (int i = 0; i < 10; i++) {
            if (GfDataManager::getDataGameIra()->m_partyMembers[0][i].m_driver == driver ||
                GfDataManager::getDataGameIra()->m_partyMembers[1][i].m_driver == driver) {
                return i;
            }
        }
    }
    return -1;
}

int GfDataDriver::getSetIdByBlade(unsigned int driver, unsigned int blade) {
    return getSetIdByBlade(getSDataDriver(driver), blade);
}

// 1.0.0's symbols have it out of line (0x71002A83E0); 3.0.1 keeps no copy, so it is inline here
inline int GfDataDriver::getSetIdByBlade(const SDataDriver& data, unsigned int blade) {
    int max = getMaxSetBladeNum(data);
    for (int slot = 0; slot < max; slot++) {
        if (getBlade(data, slot) == blade) {
            return slot;
        }
    }
    return -1;
}

int GfDataDriver::getSetIdByDummyBlade(unsigned int driver) {
    SDataDriver* data = &getSDataDriver(driver);
    for (int slot = 0; slot < 3; slot++) {
        if (GfDataBlade::isDummyBlade(data->m_blades[slot])) {
            return slot;
        }
    }
    return -1;
}

int GfDataDriver::getRuleSetBlade(unsigned int driver, unsigned int blade, int slot) {
    if (driver == 1) {
        switch (blade) {
        case 0x3EA:
            if (GfDataBlade::getDriverSetID(0x3E9) == 0) {
                slot = 3;
            }
            break;
        case 0x3EB:
            slot = 4;
            break;
        }
    }
    return slot;
}

bool GfDataDriver::leaveOneCommonBlade(unsigned int driver) {
    for (int slot = 2; slot >= 0; slot--) {
        unsigned int blade = getBlade(driver, slot);
        if (blade == 0) {
            return true;
        }
        if (GfDataBlade::isCommonBlade(blade)) {
            unsetBlade(blade);
            return true;
        }
    }
    return false;
}

bool GfDataDriver::leaveOneRareBlade(unsigned int driver) {
    for (int slot = 2; slot >= 0; slot--) {
        unsigned int blade = getBlade(driver, slot);
        if (blade == 0) {
            return true;
        }
        if (GfDataBlade::isRareBlade(blade)) {
            unsetBlade(blade);
            return true;
        }
    }
    return false;
}

bool GfDataDriver::leaveOneScenarioBlade(unsigned int driver) {
    for (int slot = 2; slot >= 0; slot--) {
        unsigned int blade = getBlade(driver, slot);
        if (blade == 0) {
            return true;
        }
        if (blade != 1001 && GfDataBlade::isRegularBlade(blade)) {
            unsetBlade(blade);
            return true;
        }
    }
    return false;
}

bool GfDataBlade::getCommonBladeName(const char* path) {
    if (path == nullptr || strlen(path) < 6) {
        return false;
    }
    return strncmp(path, "bl/bl2", 6) == 0;
}

unsigned int GfDataBlade::addCommonBlade(const SDataBlade& data) {
    unsigned int start = data.m_bladeId != 0 ? data.m_bladeId : 1198;
    unsigned int end = data.m_bladeId != 0 ? data.m_bladeId + 1 : 1397;
    for (unsigned int blade = start; blade < end; blade++) {
        if (!isActivateUnuse(blade)) {
            continue;
        }
        GfDataManager::getDataGame()->m_blades[getBladeIndex(blade)] = data;
        GfDataManager::getDataGame()->m_blades[getBladeIndex(blade)].m_bladeId = blade;
        setupSDataBladeAchievement(GfDataManager::getDataGame()->m_blades[getBladeIndex(blade)], false);
        setActivateReserver(blade);
        unsigned int creator = getCreator(blade);
        DataParamAcc acc(4, blade, GimmickType(0));
        GfDataDriver::setActivateWeaponType(creator, acc.getWeaponType(-1, false));
        GfDataDriver::fn_7100244A44(creator, blade, false);
        return blade;
    }
    return 0;
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
    return &getSDataDriver(driver).m_idea;
}

bool GfDataDriver::getListBlade(mm::mtl::FixedVector<unsigned short, 422>& list, unsigned int driver) {
    int num = getMaxSetBladeNum(driver);
    for (int i = 0; i < num; i++) {
        unsigned int blade = getBlade(driver, i);
        if (blade != 0) {
            list.push_back(blade);
        }
    }
    return !list.empty();
}

unsigned int GfDataDriver::getDriverWpnType(unsigned int driver) {
    unsigned int blade = getBlade(getSDataDriver(driver), -1);
    if (blade == 0) {
        return 0;
    }
    return GfDataManager::getDataGame()->m_blades[GfDataBlade::getBladeIndex(blade)].m_weaponType;
}

unsigned short GfDataDriver::getDefaultWpnType(unsigned int driver) {
    return getDefaultWpnType(getSDataDriver(driver));
}

unsigned short GfDataDriver::getDefaultWpnType(const SDataDriver& data) {
    unsigned int blade = getBlade(data, -1);
    if (blade != 0) {
        unsigned char type = GfDataManager::getDataGame()->m_blades[GfDataBlade::getBladeIndex(blade)].m_weaponType;
        if (type != 0) {
            return type;
        }
    }
    mm::mtl::FixedVector<unsigned short, 32> types;
    unsigned int id = data.m_id;
    GfBdatChrDr* chrDr = GfBdatChrDr::get();
    for (unsigned int type = 1; type < 50; type++) {
        if (type < 37 && chrDr->getChrDrWpnType(id, type - 1) - 1 < 4 &&
            GfDataBlade::getBladeByWeaponType(type, id, false) != 0) {
            types.push_back(type);
        }
    }
    if (types.empty()) {
        return 0;
    }
    return types[0];
}

bool GfDataDriver::isEnableLevelUp(unsigned int driver) {
    return isEnableLevelUp(getSDataDriver(driver));
}

unsigned int GfDataDriver::getExp(unsigned int driver) {
    return getExp(getSDataDriver(driver));
}

unsigned int GfDataDriver::getBattleExp(unsigned int driver) {
    return getBattleExp(getSDataDriver(driver));
}

unsigned int GfDataDriver::getBattleExpNextLevel(unsigned int driver) {
    return getBattleExpNextLevel(getSDataDriver(driver));
}

unsigned int GfDataDriver::getExpSetLevel(unsigned int driver, unsigned int level) {
    getSDataDriver(driver);
    return GfDataUtil::getGrowLevelExp(level);
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

bool GfDataQuest::getResult(unsigned char*& bdat, unsigned int& id, QuestID quest) {
    QuestListAcc* acc = QuestListAcc::get();
    id = acc->getListResultA(quest);
    if (id == 0) {
        id = acc->getListResultB(quest);
        if (id == 0) {
            return false;
        }
    }
    bdat = GfBdatMsg::getFpQuest(quest);
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

void GfDataIdea::getIdeaAttribute(mm::mtl::FixedVector<unsigned int, 2>& attributes, unsigned int idea) {
    switch (idea) {
    case 0:
        attributes.push_back(1);
        attributes.push_back(2);
        break;
    case 1:
        attributes.push_back(3);
        attributes.push_back(6);
        break;
    case 2:
        attributes.push_back(4);
        attributes.push_back(5);
        break;
    case 3:
        attributes.push_back(7);
        attributes.push_back(8);
        break;
    }
}

bool GfDataParty::isPartyMember(unsigned int chara) {
    return fn_710024BF60(chara, 10);
}

bool GfDataParty::isPartyBattleMember(unsigned int chara) {
    return fn_710024BF60(chara, 3);
}

bool GfDataParty::isActivateMember(unsigned int chara) {
    if (chara <= 1000) {
        return GfDataDriver::getSDataDriver(chara).m_dataType != 0;
    } else if (chara <= 2000) {
        if (chara != 1011) {
            unsigned int driver = GfDataManager::getDataGame()->m_blades[GfDataBlade::getBladeIndex(chara)].m_setDriver;
            if (driver == 0 || GfDataDriver::getSDataDriver(driver).m_dataType == 0) {
                return false;
            }
        }
        if (GfDataBlade::isActivateMercenaryTeam(chara)) {
            return false;
        }
        return GfDataManager::getDataGame()->m_blades[GfDataBlade::getBladeIndex(chara)].m_dataType != 0;
    }
    return false;
}

void GfDataParty::getIraParty(RQ_SETUP_PARTY& party, unsigned int id) {
    if (id == 0) {
        return;
    }
    GfBdatChrDr* bdat = GfBdatChrDr::get();
    for (unsigned int i = 0; i < 3; i++) {
        party.m_iraDrivers[i][0] = bdat->getIRA_PartyDriver(id, i);
        party.m_iraDrivers[i][1] = bdat->getIRA_PartyBlade1(id, i);
        party.m_iraDrivers[i][2] = bdat->getIRA_PartyBlade2(id, i);
    }
}

void GfDataDriver::fn_71002443AC(SDataDriver& data) {
    unsigned int blade = getBlade(data, -1);
    if (blade == 0x3E9) {
        if (GfDataBlade::isHikariCurrent()) {
            int slot = getSetIdByBlade(data, 0x3EA);
            if (slot >= 0) {
                data.m_bladeSet = slot;
                return;
            }
            GfDataBlade::setHikariCurrent(false);
        }
    } else if (blade == 0x3EA) {
        if (!GfDataBlade::isHikariCurrent()) {
            int slot = getSetIdByBlade(data, 0x3E9);
            if (slot >= 0) {
                data.m_bladeSet = slot;
                return;
            }
            GfDataBlade::setHikariCurrent(true);
        }
    }
}

void GfDataDriver::openDriverArtsForLevelup(unsigned int driver) {
    fn_7100244A44(driver, 0, true);
}

unsigned int GfDataDriver::getBlade(const SDataDriver& data, int slot) {
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

bool GfDataParty::isNiaByakko(unsigned int id) {
    if (id == 0xFFFFFFFF) {
        return false;
    }
    SDataGame* game = GfDataManager::getDataGame();
    if (game->m_party.m_members[id].m_driver != 2) {
        return false;
    }
    DataParamAcc acc(3, 2, static_cast<GimmickType>(0));
    bool result = false;
    if (acc.getBlade(-1, false) == 1004) {
        result = game->m_party.m_leader == 2 || game->m_party.m_leader == 1004;
    }
    return result;
}

bool GfDataBlade::getExtraParts(const SDataBlade& data, unsigned int part) {
    return data.m_extraParts[part] != 0;
}

SDataParty* GfDataParty::getSDataParty() {
    return &GfDataManager::getDataGame()->m_party;
}

PTPOS GfDataParty::getDriverPartyPos(unsigned int driver) {
    if (driver == 0 || !(driver - 0x11 < 9)) {
        return static_cast<PTPOS>(0);
    }
    for (int i = 0; i < 10; i++) {
        if (GfDataManager::getDataGame()->m_party.m_members[i].m_driver == driver) {
            return static_cast<PTPOS>(0);
        }
    }
    for (int i = 0; i < 10; i++) {
        if (GfDataManager::getDataGameIra()->m_partyMembers[0][i].m_driver == driver) {
            return static_cast<PTPOS>(1);
        }
        if (GfDataManager::getDataGameIra()->m_partyMembers[1][i].m_driver == driver) {
            return static_cast<PTPOS>(2);
        }
    }
    return static_cast<PTPOS>(0);
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

unsigned int GfDataMap::getMapID(unsigned int mapJumpId) {
    if (mapJumpId == 0) {
        return 0;
    }
    unsigned char* jump = GfDataBdat::getFP(182);
    unsigned char* jumpDlc = GfDataBdat::getFP(183);
    int id = mapJumpId;
    unsigned char map = 0;
    if (id >= Bdat::getIdTop(jump) && id < Bdat::getIdTop(jump) + Bdat::getIdCount(jump)) {
        map = Bdat::getValCheck(jump, "MapList", id, 1);
    } else if (id >= Bdat::getIdTop(jumpDlc) && id < Bdat::getIdTop(jumpDlc) + Bdat::getIdCount(jumpDlc)) {
        map = Bdat::getValCheck(jumpDlc, "MapList", id, 1);
    }
    return map;
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

unsigned int GfDataDriverArts::getArtsLevel(unsigned int driver, unsigned int arts) {
    if (arts >= 0x280) {
        SDataDriverArtsEx* ex = GfDataDriver::getSDataDriverArtsEx(driver);
        return ex->m_artsLevels[arts - 0x280];
    }
    SDataDriver* data = &GfDataDriver::getSDataDriver(driver);
    return data->m_artsLevels[arts];
}

unsigned int GfDataDriver::getDriverArtsLevel(unsigned int driver, unsigned int arts) {
    if (arts >= 0x280) {
        SDataDriverArtsEx* ex = getSDataDriverArtsEx(driver);
        return ex->m_artsLevels[arts - 0x280];
    }
    SDataDriver* data = &getSDataDriver(driver);
    return data->m_artsLevels[arts];
}

void GfDataDriver::setDriverArtsLevel(unsigned int driver, unsigned int arts, unsigned int level) {
    if (arts >= 0x280) {
        SDataDriverArtsEx* ex = getSDataDriverArtsEx(driver);
        ex->m_artsLevels[arts - 0x280] = level;
        return;
    }
    SDataDriver* data = &getSDataDriver(driver);
    data->m_artsLevels[arts] = level;
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

bool GfDataParty::isExistBlade(unsigned int index, unsigned int blade) {
    PartyMember& member = GfDataManager::getDataGame()->m_party.m_members[index];
    if (member.m_driver == 0) {
        return false;
    }
    for (int i = 0; i < GfDataDriver::getMaxSetBladeNum(member.m_driver); i++) {
        if (GfDataDriver::getBlade(member.m_driver, i) == blade) {
            return true;
        }
    }
    return false;
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

unsigned int GfDataQuest::getQuestCategory(QuestID id) {
    if (id.empty()) {
        return 0;
    }
    unsigned int category = QuestListAcc::get()->getListQuestCategory(id);
    if (category != 0) {
        return category;
    }
    unsigned int prt = getListPRTQuestID(id).m_id;
    if (prt == 0) {
        return 0;
    }
    if (prt < 1000) {
        return 1;
    }
    if (prt < 5000) {
        return 3;
    }
    if (prt < 6000) {
        return 2;
    }
    if (prt < 7000) {
        return 5;
    }
    return 6;
}

QuestID GfDataQuest::getListPRTQuestID(QuestID id) {
    QuestID quest;
    if (id.empty()) {
        return quest;
    }
    unsigned int prt = QuestListAcc::get()->getListPRTQuestID(id);
    quest.m_id = prt;
    quest.m_achieveId = id.m_achieveId == 0 ? static_cast<unsigned short>(prt >> 16) : id.m_achieveId;
    return quest;
}

unsigned int GfDataIdea::calcLevel(unsigned int point) {
    GfBdatBlade* bdat = GfBdatBlade::get();
    if (point < bdat->getBLD_IdeaNeedPoint(1)) {
        return 0;
    }
    if (point < bdat->getBLD_IdeaNeedPoint(2)) {
        return 1;
    }
    if (point < bdat->getBLD_IdeaNeedPoint(3)) {
        return 2;
    }
    if (point < bdat->getBLD_IdeaNeedPoint(4)) {
        return 3;
    }
    if (point < bdat->getBLD_IdeaNeedPoint(5)) {
        return 4;
    }
    if (point < bdat->getBLD_IdeaNeedPoint(6)) {
        return 5;
    }
    if (point < bdat->getBLD_IdeaNeedPoint(7)) {
        return 6;
    }
    if (point < bdat->getBLD_IdeaNeedPoint(8)) {
        return 7;
    }
    if (point < bdat->getBLD_IdeaNeedPoint(9)) {
        return 8;
    }
    if (point < bdat->getBLD_IdeaNeedPoint(10)) {
        return 9;
    }
    return 10;
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

void GfDataEvent::setWatchedEventFlag(unsigned int event) {
    setWatchedEventFlag(*GfDataManager::getDataGame(), event);
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

// true when event's event theater row has category 2 (setWatchedEventFlag inlines it)
static inline bool isEventTheaterCategory2(GfBdatShop* bdat, unsigned int event) {
    for (unsigned int i = bdat->getMNU_EventTheaterStart(), end = bdat->getMNU_EventTheaterEnd(); i < end; i++) {
        if (bdat->getMNU_EventTheaterevent_id(i) == event) {
            return bdat->getMNU_EventTheatercategory(i) == 2;
        }
    }
    return false;
}

void GfDataEvent::setWatchedEventFlag(SDataGame& game, unsigned int event) {
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

bool GfDataEvent::isWatchedEventFlag(unsigned int event) {
    return isWatchedEventFlag(*GfDataManager::getDataGame(), event);
}

bool GfDataEvent::isWatchedEventFlag(const SDataGame& game, unsigned int event) {
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

int GfDataEvent::getBladeQuestDriver(unsigned int event) {
    return GfDataBlade::getCreator(getBladeQuestBlade(event));
}

unsigned int GfDataEvent::getBladeQuestBlade(unsigned int event) {
    GfBdatShop* shop = GfBdatShop::get();
    unsigned int row = shop->getMNU_EventTheaterStart();
    unsigned int end = shop->getMNU_EventTheaterEnd();
    for (; row < end; row++) {
        if (shop->getMNU_EventTheaterevent_id(row) != event) {
            continue;
        }
        unsigned int blade = shop->getMNU_EventTheaterblade_id(row);
        if (blade > 1000) {
            return blade;
        }
        switch (shop->getMNU_EventTheatermaincast(row)) {
        case 1:
            return 1007;
        case 2:
            return 1015;
        case 3:
            return 1016;
        case 4:
            return 1017;
        case 5:
            return 1020;
        case 6:
            return 1022;
        case 7:
            return 1021;
        case 8:
            return 1038;
        case 9:
            return 1023;
        case 11:
            return 1024;
        case 12:
            return 1025;
        case 13:
            return 1026;
        case 14:
            return 1027;
        case 15:
            return 1028;
        case 16:
            return 1029;
        case 17:
            return 1030;
        case 18:
            return 1031;
        case 19:
            return 1032;
        case 20:
            return 1033;
        case 21:
            return 1034;
        case 22:
            return 1035;
        case 23:
            return 1036;
        case 24:
            return 1037;
        case 25:
            return 1039;
        case 26:
            return 1040;
        case 27:
            return 1018;
        case 28:
            return 1019;
        case 29:
            return 1041;
        case 30:
            return 1104;
        case 34:
            return 1108;
        case 35:
            return 1109;
        default:
            return 0;
        }
    }
    return 0;
}

unsigned int GfDataEvent::getBladeIdByEnentId(unsigned int event) {
    GfBdatChrBl* bl = GfBdatChrBl::get();
    unsigned int row = bl->getChrBlStart();
    unsigned int end = bl->getChrBlEnd();
    for (; row < end; row++) {
        unsigned int createEvent = bl->getChrBlCreateEventID(row);
        if (createEvent == event) {
            return row;
        }
    }
    return 0;
}

bool GfDataEvent::getMapJumpPosition(mm::Vec3& pos, float& angle, unsigned int event) {
    unsigned char* fp = GfDataBdat::getFP(fn_710024EBD8(event));
    if (fp == nullptr) {
        return false;
    }
    Bdat::uVal val;
    val.uint = Bdat::getValCheck(fp, "zoneX", event, 8);
    pos.x = val.real;
    val.uint = Bdat::getValCheck(fp, "zoneY", event, 8);
    pos.y = val.real;
    val.uint = Bdat::getValCheck(fp, "zoneZ", event, 8);
    pos.z = val.real;
    val.uint = Bdat::getValCheck(fp, "zoneR", event, 8);
    angle = val.real * 0.017453292f;
    return true;
}

bool GfDataEvent::isInvalidMelefRetarget(unsigned int event) {
    unsigned char* fp = GfDataBdat::getFP(fn_710024EBD8(event));
    if (fp == nullptr) {
        return false;
    }
    return static_cast<bool>(static_cast<unsigned char>(Bdat::getValCheck(fp, "noRetarget", event, 1)));
}


int GfDataItem::getRarity(unsigned int item) {
    ItemType::Type type;
    unsigned int index;
    int kind = getItemType(type, index, item) ? static_cast<int>(type) : 0;
    int rarity = 0;
    GfBdatItem* bdat = GfBdatItem::get();
    switch (kind) {
    case 1:
        rarity = bdat->getPcWpnChipRarity(item);
        break;
    case 2:
        rarity = bdat->getPcEquipRarity(item);
        break;
    case 3:
        rarity = bdat->getEquipOrbRarity(item);
        break;
    case 5:
        rarity = bdat->getSalvageRarity(item);
        break;
    case 7:
        rarity = bdat->getCollectionListRarity(item);
        break;
    case 8:
        rarity = bdat->getTresureRarity(item);
        break;
    case 9:
        rarity = bdat->getEmptyOrbRarity(item);
        break;
    case 10:
        rarity = bdat->getFavoriteRarity(item);
        break;
    case 11:
        rarity = bdat->getCrystalListRarity(item);
        break;
    case 12:
        rarity = bdat->getBoosterRarity(item);
        break;
    }
    return rarity;
}

unsigned int GfDataItem::getCategory(unsigned int item) {
    GfBdatItem* bdat = GfBdatItem::get();
    unsigned int category = 0;
    switch (getItemType(item)) {
    case 6:
        if (item >= 25501 && item <= 25999) {
            category = bdat->getPreciousIraCategory(item);
        } else {
            category = bdat->getPreciousCategory(item);
        }
        break;
    case 7:
        category = bdat->getCollectionListCategory(item);
        break;
    case 8:
        category = bdat->getTresureCategory(item);
        break;
    case 10:
        category = bdat->getFavoriteCategory(item);
        break;
    case 11:
        category = bdat->getPreciousCategory(item);
        break;
    case 12:
        category = bdat->getBoosterCategory(item);
        break;
    }
    return category;
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

bool GfDataItem::isNoMultiple(unsigned int item) {
    unsigned int flag;
    switch (getItemType(item)) {
    case 11: {
        unsigned int index = GfBdatItem::get()->getCrystalListNoMultiple(item);
        if (index == 0) {
            return false;
        }
        flag = index + 51061;
        break;
    }
    case 6: {
        unsigned int index;
        if (item - 25501 < 499) {
            index = GfBdatItem::get()->getPreciousIraNoMultiple(item);
        } else {
            index = GfBdatItem::get()->getPreciousNoMultiple(item);
        }
        if (index == 0) {
            return false;
        }
        flag = index + 51091;
        break;
    }
    default:
        return false;
    }
    return GfGameFlag::getLocal(1, flag) != 0;
}

void GfDataItem::setNoMultiple(unsigned int item, bool set) {
    unsigned int flag;
    switch (getItemType(item)) {
    case 11: {
        unsigned int index = GfBdatItem::get()->getCrystalListNoMultiple(item);
        if (index == 0) {
            return;
        }
        flag = index + 51061;
        break;
    }
    case 6: {
        unsigned int index;
        if (item - 25501 < 499) {
            index = GfBdatItem::get()->getPreciousIraNoMultiple(item);
        } else {
            index = GfBdatItem::get()->getPreciousNoMultiple(item);
        }
        if (index == 0) {
            return;
        }
        flag = index + 51091;
        break;
    }
    default:
        return;
    }
    GfGameFlag::setLocal(1, flag, set);
}

unsigned int GfDataMercenaries::getReserverMax() {
    unsigned int level = GfGameFlag::getLocal(4, 2);
    return level * 24 + (GfDataManager::getDataGame()->m_gameClearCount != 0 ? 48 : 0) + 24;
}

int GfDataBlade::getCreator(const SDataGame& game, unsigned int blade) {
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
    for (int i = 0; i < 3; i++) {
        if (equip.m_condenserParts[i] != 0) {
            power += bdat->getITM_HanaAssistNeedPow(equip.m_condenserParts[i]);
        }
    }
    for (int i = 0; i < 3; i++) {
        if (equip.m_extendCondenserParts[i] != 0) {
            power += bdat->getITM_HanaAssistNeedPow(equip.m_extendCondenserParts[i]);
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

const char* GfDataBlade::getBaseEabWeaponName(unsigned int blade) {
    if (blade == 0) {
        return "";
    }
    unsigned int type = getSDataBlade(blade)->m_weaponType;
    if ((blade >= 1005 && blade < 1008) || (blade >= 1197 && blade <= 1422)) {
        return s_weaponNameSuffixes[type];
    }
    if (blade >= 1051 && blade <= 1072) {
        return s_weaponNameSuffixes[type];
    }
    if (blade < 1082 || blade == 1103) {
        return "";
    }
    return s_weaponNameSuffixes[type];
}

const char* GfDataBlade::getBaseEfbWeaponName(unsigned int blade) {
    if (blade == 0) {
        return "";
    }
    unsigned int type = getSDataBlade(blade)->m_weaponType;
    if (blade == 1004 || (blade >= 1005 && blade < 1008) || blade == 1010) {
        return s_weaponNameSuffixes[type];
    }
    if (blade >= 1197 && blade <= 1422) {
        return s_weaponNameSuffixes[type];
    }
    if (blade >= 1051 && blade <= 1072) {
        return s_weaponNameSuffixes[type];
    }
    if (blade < 1082 || blade == 1103) {
        return "";
    }
    return s_weaponNameSuffixes[type];
}

bool GfDataFieldSkill::getCaption(unsigned char*& bdat, unsigned int& id, unsigned int skill) {
    if (skill == 0) {
        return false;
    }
    id = QuestListAcc::get()->getFLD_FieldSkillListCaption(skill);
    bdat = GfBdatMsg::getFpFieldSkill();
    return id != 0;
}

// Proposed name, not the original's: the symbols leave it unnamed (lbl_71009BA0B8). The statistics whose totals are
// kept in 32-bit local flags 258 on (getAchievementTotalFlgIndex32).
static const unsigned short s_achievementTotalStats[64] = {
        0x31, 0x36, 0x3C, 0x3E, 0x63, 0x72, 0x74, 0x76, 0x78, 0x7A, 0x7C, 0x7E,
        0x80, 0x82, 0x84, 0x86, 0x88, 0x8A, 0x8C, 0x8E, 0x90, 0x92, 0x94, 0x33,
        0x34, 0x35, 0x16, 0x2, 0x4, 0x17, 0x14, 0x20, 0x21, 0x5, 0xE, 0x13,
        0x1, 0x39, 0x3B, 0x22, 0x3A, 0x23, 0x25, 0x65, 0x41, 0x97, 0x98, 0x99,
        0x9A, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4A, 0x4B, 0x9D, 0x9F, 0x0, 0x0,
        0x0, 0x0, 0x0, 0x0,
};

int GfDataAchievement::getAchievementTotalFlgIndex32(unsigned short stats) {
    if (stats == 0) {
        return -1;
    }
    for (int i = 0; i < 64; i++) {
        if (s_achievementTotalStats[i] == stats) {
            return i + 258;
        }
    }
    return -1;
}

int GfDataAchievement::getAchievementTotalFlgIndex8(unsigned short stats) {
    if (stats >= 184 && stats < 214) {
        return stats + 3834;
    }
    return -1;
}

bool GfDataAchievement::isAddAchievementBonusCount(const AchievQuest& quest) {
    // the statistics that always count (lbl_71009BA138; the name is not the original's)
    static const unsigned short s_bonusStats[67] = {
        0x6, 0x7, 0x8, 0x9, 0xA, 0xB, 0xC, 0xD, 0xF, 0x10, 0x11, 0x12, 0x43, 0x18, 0x19,
        0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F, 0x32, 0x37, 0x3D, 0x3F, 0x42, 0x44, 0x5D, 0x5E, 0x5F,
        0x62, 0x61, 0x64, 0x66, 0x67, 0x68, 0x69, 0x6A, 0x6B, 0x6C, 0x6D, 0x6E, 0x6F, 0x70, 0x71,
        0x97, 0x98, 0x99, 0x9A, 0x73, 0x75, 0x77, 0x79, 0x7B, 0x7D, 0x7F, 0x81, 0x83, 0x85, 0x87,
        0x89, 0x8B, 0x8D, 0x8F, 0x91, 0x95, 0x96,
    };
    for (unsigned long i = 0; i < 67; i++) {
        if (s_bonusStats[i] == quest.m_stats) {
            return true;
        }
    }
    QuestTaskParam param(GfDataQuest::getListNextQuestA(quest.m_questId), 0, TASK_STATE(0));
    switch (param.m_taskType) {
    case 1:
    case 4:
    case 6:
    case 11:
        return true;
    }
    return false;
}

unsigned int GfDataAchievement::getTotalCount(unsigned int stats) {
    int index = getAchievementTotalFlgIndex8(stats);
    if (index >= 0) {
        return GfGameFlag::getLocal(8, index);
    }
    index = getAchievementTotalFlgIndex32(stats);
    if (index < 0) {
        return 0;
    }
    return GfGameFlag::getLocal(32, index);
}

void GfDataAchievement::addTotalCount(unsigned int type, unsigned int value) {
    int index = getAchievementTotalFlgIndex8(type);
    if (index >= 0) {
        unsigned int count = GfGameFlag::getLocal(8, index) + value;
        GfGameFlag::setLocal(8, index, count > 255 ? 255 : count);
        return;
    }
    index = getAchievementTotalFlgIndex32(type);
    if (index < 0) {
        return;
    }
    unsigned int count = GfGameFlag::getLocal(32, index);
    unsigned int total = count + value;
    GfGameFlag::setLocal(32, index, total < count ? 0xFFFFFFFF : total);
}

void GfDataAchievement::setTotalCount(unsigned int type, unsigned int value) {
    int index = getAchievementTotalFlgIndex8(type);
    if (index >= 0) {
        GfGameFlag::setLocal(8, index, value > 255 ? 255 : value);
        return;
    }
    index = getAchievementTotalFlgIndex32(type);
    if (index < 0) {
        return;
    }
    GfGameFlag::setLocal(32, index, value);
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

bool GfDataMercenaries::getRequestCondition(GfRequestBladeData& data, unsigned int mission, unsigned int slot) {
    QuestListAcc* acc = QuestListAcc::get();
    unsigned int purpose = getMissionPurposeID(mission);
    if (slot >= 4 || purpose == 0) {
        return false;
    }
    if (acc->getTaskTaskType(purpose, slot) != 9) {
        return false;
    }
    unsigned int id = acc->getTaskTaskID(purpose, slot);
    if (id == 0) {
        return false;
    }
    data.m_count = acc->getRequestBladeRequestNumber(id);
    int value = acc->getRequestBladeRequestCategory(id);
    if (value != 0) {
        data.m_type = 1;
        data.m_param = value;
        return true;
    }
    value = acc->getRequestBladeRequestAtr(id);
    if (value != 0) {
        data.m_type = 7;
        data.m_param = value;
        return true;
    }
    value = acc->getRequestBladeRequestPerformance(id);
    if (value != 0) {
        data.m_type = 2;
        data.m_level = value;
        return true;
    }
    value = acc->getRequestBladeRequestRace(id);
    if (value != 0) {
        data.m_param = value > 2 ? 1 : value;
        data.m_type = 3;
        return true;
    }
    value = acc->getRequestBladeRequestGender(id);
    if (value != 0) {
        data.m_type = 4;
        data.m_param = value;
        return true;
    }
    value = acc->getRequestBladeRequestArts(id);
    int level = acc->getRequestBladeRequestArtsLevel(id);
    if (value != 0) {
        data.m_type = 5;
        data.m_param = value;
        data.m_level = level;
        return true;
    }
    value = acc->getRequestBladeRequestFSkill(id);
    level = acc->getRequestBladeRequestFSLevel(id);
    if (value != 0) {
        data.m_type = 6;
        data.m_param = value;
        data.m_level = level;
        return true;
    }
    return false;
}

unsigned int GfDataMercenaries::getBladeWithLeader(unsigned int mission) {
    QuestListAcc* acc = QuestListAcc::get();
    QuestID quest = acc->getFLD_MercenariesMissionQuestID(mission);
    unsigned int purpose = acc->getListPurposeID(GfDataQuest::getListNextQuestA(quest));
    for (unsigned int i = 0; i < 4; i++) {
        unsigned int cond = acc->getTaskTaskCondition(purpose, i);
        GfBdatCond* bdat = GfBdatCond::get();
        for (unsigned int j = 0; j < 8; j++) {
            if (bdat->getConditionListConditionType(cond, j) != 6) {
                continue;
            }
            unsigned int pt = bdat->getConditionListCondition(cond, j);
            if (bdat->getConditionPTCategory(pt) != 4) {
                continue;
            }
            for (unsigned int k = 0; k < 3; k++) {
                unsigned int blade = bdat->getConditionPTPCID(pt, k);
                if (GfDataBlade::isBladeID(blade)) {
                    return blade;
                }
            }
        }
    }
    return 0;
}

void GfDataBlade::initSaveData(SDataGame& game) {
    for (unsigned int i = 0; i < 422; i++) {
        unsigned int blade = getBladeID(i);
        if (blade == 0) {
            continue;
        }
        unsigned int index = getBladeIndex(blade);
        SDataBlade data;
        setupSDataBlade(data, blade, false);
        game.m_blades[index] = data;
        setupSDataBladeAchievement(GfDataManager::getDataGame()->m_blades[getBladeIndex(blade)], true);
    }
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

bool GfDataBlade::isBladeLock(unsigned int blade) {
    return GfDataManager::getDataGame()->m_blades[getBladeIndex(blade)].m_bladeLock != 0;
}

void GfDataBlade::setBladeLock(unsigned int blade, bool flag) {
    unsigned int index = getBladeIndex(blade);
    SDataGame* game = GfDataManager::getDataGame();
    game->m_blades[index].m_bladeLock = flag;
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

bool GfDataBlade::isActivateMercenaryTeam(unsigned int blade) {
    if (blade == 0) {
        return false;
    }
    return GfDataManager::getDataGame()->m_blades[getBladeIndex(blade)].m_dataType == 2;
}

bool GfDataBlade::getListReserverWithSolo(mm::mtl::FixedVector<unsigned short, 422>& list) {
    getListReserver(list);
    for (unsigned short* it = list.begin(); it != list.end();) {
        if (*it != 0 && isActivateDriver(*it)) {
            it = list.erase(it);
        } else {
            ++it;
        }
    }
    return !list.empty();
}

bool GfDataBlade::getListForAchievement(mm::mtl::FixedVector<unsigned short, 422>& list) {
    for (unsigned int i = 0; i < 422; i++) {
        unsigned int blade = getBladeID(i);
        if (blade == 0) {
            continue;
        }
        DataParamAcc acc(4, blade, GimmickType(0));
        if (!acc.isValid()) {
            continue;
        }
        if (isActivateUnuse(blade) && !isAttachedParty(blade)) {
            continue;
        }
        if (isIra(blade) || !isDummyBlade(blade)) {
            const char* name = acc.getName();
            if (name != nullptr && name[0] != '\0') {
                list.push_back(blade);
            }
        }
    }
    return !list.empty();
}

unsigned int GfDataParty::getDriver(unsigned int index, PTPOS party) {
    return getPartyMember(index, party)->m_driver;
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

unsigned int GfDataParty::getFixedHandleForDriver(unsigned int handle, unsigned int driver) {
    if (driver - 0x11 < 9) {
        switch (fn_710024BCEC(driver)) {
        case 1:
            return getFixedHandleForBlade(handle, 0);
        case 2:
            return getFixedHandleForBlade(handle, 1);
        }
    }
    return handle;
}

unsigned int GfDataParty::fn_710024BCEC(unsigned int driver) {
    GfBdatChrDr* bdat = GfBdatChrDr::get();
    unsigned int ira = bdat->getChrDrIraParam(driver);
    if (ira != 0) {
        unsigned int group = bdat->getChrIrGroupID(ira);
        unsigned int row = bdat->getChrIrStart();
        unsigned int end = bdat->getChrIrEnd();
        unsigned int count = 0;
        for (; row < end; row++) {
            if (bdat->getChrIrdriverID(row) == driver) {
                return count;
            }
            if (bdat->getChrIrGroupID(row) == group) {
                count++;
            }
        }
    }
    return 0;
}

unsigned int GfDataHana::getRole(unsigned int hana) {
    GfBdatItem* bdat = GfBdatItem::get();
    SDataBlade& data = GfDataManager::getDataGame()->m_blades[GfDataBlade::getBladeIndex(hana)];
    return bdat->getITM_HanaRoleRole(data.m_equipHana.m_roleParts);
}

bool GfDataDriver::isActivateUnuse(unsigned int driver) {
    return getSDataDriver(driver).m_dataType == 0;
}

void GfDataDriver::setLevel(SDataDriver& data, unsigned int level) {
    unsigned int driver = data.m_id;
    if (driver - 0x11 < 9) {
        GfBdatChrDr* bdat = GfBdatChrDr::get();
        if (bdat->getChrIrType(bdat->getChrDrIraParam(data.m_id)) != 0) {
            setLevel(getSDataDriver(getIraFront(data.m_id)), level);
            return;
        }
    }
    data.m_level = level;
    calcDriverBaseParamByLevel(data);
}

void GfDataDriver::setLevel(unsigned int driver, unsigned int level) {
    setLevel(getSDataDriver(driver), level);
}

void GfDataDriver::setExp(unsigned int driver, unsigned int exp) {
    if (driver - 0x11 < 9) {
        GfBdatChrDr* bdat = GfBdatChrDr::get();
        if (bdat->getChrIrType(bdat->getChrDrIraParam(driver)) != 0) {
            setExp(getIraFront(driver), exp);
            return;
        }
    }
    getSDataDriver(driver).m_exp = exp;
}

void GfDataDriver::setBattleExp(unsigned int driver, unsigned int exp) {
    if (driver - 0x11 < 9) {
        GfBdatChrDr* bdat = GfBdatChrDr::get();
        if (bdat->getChrIrType(bdat->getChrDrIraParam(driver)) != 0) {
            setBattleExp(getIraFront(driver), exp);
            return;
        }
    }
    getSDataDriver(driver).m_battleExp = exp;
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

int GfDataHana::getPartsPower(unsigned int parts) {
    GfBdatItem* bdat = GfBdatItem::get();
    int power = 0;
    switch (GfDataItem::getItemType(parts)) {
    case 16:
        power = bdat->getITM_HanaRoleNeedPow(parts);
        break;
    case 17:
        power = bdat->getITM_HanaAtrNeedPow(parts);
        break;
    case 18:
        power = bdat->getITM_HanaArtsEnhNeedPow(parts);
        break;
    case 19:
        power = bdat->getITM_HanaNArtsSetNeedPow(parts);
        break;
    case 20:
        power = bdat->getITM_HanaAssistNeedPow(parts);
        break;
    }
    return power;
}

bool GfDataHana::isOpenCircuit(unsigned int hana, unsigned int circuit) {
    SDataBlade& data = GfDataManager::getDataGame()->m_blades[GfDataBlade::getBladeIndex(hana)];
    return (data.m_openCircuit & (1 << circuit)) != 0;
}

void GfDataHana::setOpenCircuit(unsigned int hana, unsigned int circuit, bool open) {
    unsigned short bit = 1 << circuit;
    if (open) {
        GfDataManager::getDataGame()->m_blades[GfDataBlade::getBladeIndex(hana)].m_openCircuit |= bit;
    } else {
        GfDataManager::getDataGame()->m_blades[GfDataBlade::getBladeIndex(hana)].m_openCircuit &= ~bit;
    }
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
    return getBladeSet(getSDataDriver(driver));
}

bool GfDataDriver::isScenarioMask(unsigned int driver) {
    if (driver == 0) {
        return false;
    }
    return getSDataDriver(driver).m_scenarioMask == 1;
}

unsigned int GfDataWeapon::getNewWeapon(unsigned int weapon, unsigned int chip) {
    GfBdatItem* bdat = GfBdatItem::get();
    unsigned int type = bdat->getPcWpnWpnType(weapon);
    if (type < 37 || type - 1 < 16) {
        return bdat->getPcWpnChipCreateWpn(chip, type - 1);
    }
    return 0;
}

bool GfDataDriver::isEquipDefaultAcce(unsigned int driver) {
    if (driver == 0) {
        return false;
    }
    return getSDataDriver(driver).m_defaultAcceDone;
}

int GfDataDriver::getMaxSetBladeNum(unsigned int driver) {
    if (driver == 0) {
        return 0;
    }
    return getMaxSetBladeNum(getSDataDriver(driver));
}

ItemBox* GfDataItem::getItemBox() {
    return &GfDataManager::getDataGame()->m_itemBox;
}

ItemBoxEx* GfDataItem::getItemBoxExtend() {
    return &GfDataManager::getDataGame()->m_itemBoxExtend;
}

unsigned short GfDataUtil::getScenarioFlag(const SDataGame& game) {
    return GfGameFlag::getLocal(game.m_gameFlag, 0x10, 1);
}

bool GfDataUtil::isAdvanceSaved(const SDataGame& game) {
    return GfGameFlag::getLocal(game.m_gameFlag, 1, 0xD791) != 0;
}

bool GfDataBlade::isHomuriNameHikari(const SDataGame& game) {
    return GfGameFlag::getLocal(game.m_gameFlag, 1, 0x89FB) != 0;
}

bool GfDataUtil::isClearGame(const SDataGame& game) {
    return GfGameFlag::getLocal(game.m_gameFlag, 1, 0xBDCD) != 0 || GfGameFlag::getLocal(game.m_gameFlag, 1, 0xD880) != 0;
}

bool GfDataUtil::isClearTwiceGame(const SDataGame& game) {
    return GfGameFlag::getLocal(game.m_gameFlag, 1, 0xD793) != 0 || GfGameFlag::getLocal(game.m_gameFlag, 1, 0xD882) != 0;
}

bool GfDataUtil::isClearGameCheck(const SDataGame& game) {
    return GfGameFlag::getLocal(game.m_gameFlag, 1, 0xD77E) != 0 || GfGameFlag::getLocal(game.m_gameFlag, 1, 0xD87E) != 0;
}

bool GfDataUtil::isClearGame() {
    return GfDataUtil::isClearGame(*GfDataManager::getDataGame());
}

bool GfDataUtil::isClearGameCheck() {
    return GfDataUtil::isClearGameCheck(*GfDataManager::getDataGame());
}

bool GfDataUtil::isAdvanceContinue() {
    return GfGameFlag::getLocal(GfDataManager::getDataGame()->m_gameFlag, 1, 0xD795) != 0;
}

bool GfDataUtil::isIra() {
    return GfGameFlag::getLocal(GfDataManager::getDataGame()->m_gameFlag, 1, 0xD860) != 0;
}

bool GfDataUtil::isVandammeDead() {
    return GfDataUtil::getScenarioFlag() > 0xBE7;
}

bool GfDataMap::isArcadiaDestroy() {
    return GfDataUtil::getScenarioFlag() > 0x1F64;
}

bool GfDataMap::isIraLastMapCloud2() {
    return GfGameFlag::getLocal(1, 0xD862) != 0;
}

bool GfDataMap::isIraOutoAttackCloud() {
    return GfGameFlag::getLocal(1, 0xD863) != 0;
}

void GfDataNpc::setHitonowaFlag(unsigned int id, unsigned int value) {
    unsigned int flag = GfDataNpc::getHitonowaFlag2Index(id);
    if (flag == 0) {
        return;
    }
    unsigned int old = GfGameFlag::getLocal(2, flag);
    GfGameFlag::setLocal(2, flag, value);
    GfDataHitonowa::setHitonowaEntry(id, value);
    unsigned int rank = GfDataHitonowa::getFlagLevel();
    if (GfGameFlag::getLocal(4, 652) < rank) {
        GfGameFlag::setLocal(4, 652, rank);
    }
    if (old != value) {
        GfEvent::callHitonowaChanged(id);
    }
}

void GfDataHitonowa::setHitonowaEntry(unsigned int id, unsigned int mode) {
    unsigned int flag = GfDataNpc::getHitonowaFlag2Index(id);
    if (flag == 0) {
        return;
    }
    int base;
    switch (mode) {
    case 0:
        if (!GfDataNpc::isHitonowaMeetsFlag(id)) {
            return;
        }
        base = 0x10C4;
        break;
    case 1:
        if (!GfDataNpc::isHitonowaMeetsFlag(id)) {
            return;
        }
        base = 0x11C5;
        break;
    case 2:
        base = 0x12C6;
        break;
    case 3:
        base = 0x11C5;
        break;
    default:
        return;
    }
    unsigned int value = flag - 0xED02;
    for (unsigned int i = 0; i < 256; i++) {
        unsigned int cur = GfGameFlag::getLocal(8, base + i);
        if (cur == value) {
            return;
        }
        if (cur == 0) {
            GfGameFlag::setLocal(8, base + i, value);
            return;
        }
    }
}

unsigned int GfDataHitonowa::getFlagLevel() {
    unsigned int set;
    unsigned int total;
    GfDataHitonowa::getCompleteNum(set, total);
    GfBdatBtl* btl = GfBdatBtl::get();
    if (btl->getWildcardDatavalueU2(95) <= set) {
        return 6;
    }
    if (btl->getWildcardDatavalueU2(80) <= set) {
        return 5;
    }
    if (btl->getWildcardDatavalueU2(79) <= set) {
        return 4;
    }
    if (btl->getWildcardDatavalueU2(78) <= set) {
        return 3;
    }
    if (btl->getWildcardDatavalueU2(77) <= set) {
        return 2;
    }
    if (btl->getWildcardDatavalueU2(76) <= set) {
        return 1;
    }
    return 0;
}

unsigned int GfDataHitonowa::getFlag4Level() {
    return GfGameFlag::getLocal(4, 652);
}

unsigned int GfDataNpc::getHitonowaFlag(unsigned int id) {
    if (id > 2000) {
        unsigned int flag = GfBdatRsc::get()->getRscNpcListHitonowaFlag(id);
        if (flag != 0) {
            return GfGameFlag::getLocal(2, flag);
        }
    }
    return 0;
}

bool GfDataNpc::isHitonowaMeetsFlag(unsigned int id) {
    if (id <= 2000) {
        return false;
    }
    unsigned int flag = GfBdatRsc::get()->getRscNpcListNpcMeetFlag(id);
    if (flag == 0) {
        return false;
    }
    return GfGameFlag::getLocal(1, flag) != 0;
}

bool GfDataNpc::isDispHitonowa(unsigned int id) {
    if (id <= 2000) {
        return false;
    }
    unsigned int flag = GfBdatRsc::get()->getRscNpcListHitonowaFlag(id);
    if (flag == 0) {
        return false;
    }
    unsigned int value = GfGameFlag::getLocal(2, flag);
    return value == 1 || value == 3;
}

void GfDataNpc::setHitonowaNewFlag(unsigned int id, bool value) {
    unsigned int flag;
    if (id <= 2000) {
        flag = 0;
    } else {
        flag = GfBdatRsc::get()->getRscNpcListNpcMeetFlag(id);
    }
    GfGameFlag::setLocal(1, flag + 2160, value);
}

bool GfDataNpc::isHitonowaNewFlag(unsigned int id) {
    unsigned int flag;
    if (id <= 2000) {
        flag = 0;
    } else {
        flag = GfBdatRsc::get()->getRscNpcListNpcMeetFlag(id);
    }
    return GfGameFlag::getLocal(1, flag + 2160) != 0;
}

void GfDataMap::setIraLastMapCloud2(bool flag) {
    GfGameFlag::setLocal(1, 0xD862, flag);
}

void GfDataMap::setIraOutoAttackCloud(bool flag) {
    GfGameFlag::setLocal(1, 0xD863, flag);
}

unsigned int GfDataMap::getErasedEthCloudNum() {
    Bdat::getFP("FLD_MapGimmick");
    unsigned int count = 0;
    if (GfGameFlag::getLocal(1, 0xABFA) != 0) count++;
    for (int flag = 0xAC00; flag <= 0xAC08; flag++) {
        if (GfGameFlag::getLocal(1, flag) != 0) count++;
    }
    return count;
}

unsigned int GfDataEvent::getEventScenario(unsigned int event) {
    unsigned char* fp = GfDataBdat::getFP(fn_710024EBD8(event));
    if (fp == nullptr) {
        return 0;
    }
    return static_cast<unsigned short>(Bdat::getValCheck(fp, "scenarioFlag", event, 2));
}

void GfDataUtil::setClearGameCheck(bool flag) {
    GfGameFlag::setLocal(1, 0xD77E, flag);
    GfGameFlag::setLocal(1, 0xD87E, flag);
}

void GfDataUtil::setAdvanceSaved(SDataGame& game, bool flag) {
    GfGameFlag::setLocal(game.m_gameFlag, 1, 0xD791, flag);
}

void GfDataUtil::setAdvanceContinue(SDataGame& game, bool flag) {
    GfGameFlag::setLocal(game.m_gameFlag, 1, 0xD795, flag);
}

void GfDataUtil::setupUi1868ForSDataGame(SDataGame& game) {
    GameFlag& flag = game.m_gameFlag;
    if (GfGameFlag::getLocal(flag, 8, 0x856) == 1 && GfQuestInfo::getState(game, QuestID(0x46B)) == 3) {
        unsigned int count = 1;
        if (GfGameFlag::getLocal(flag, 1, 0xC51B) != 0) {
            count++;
        }
        if (GfGameFlag::getLocal(flag, 1, 0xC4D6) != 0) {
            count++;
        }
        if (GfGameFlag::getLocal(flag, 1, 0xC436) != 0) {
            count++;
        }
        if (GfGameFlag::getLocal(flag, 1, 0xC437) != 0) {
            count++;
        }
        if (GfGameFlag::getLocal(flag, 1, 0xC438) != 0) {
            count++;
        }
        if (GfGameFlag::getLocal(flag, 1, 0xC439) != 0) {
            count++;
        }
        GfGameFlag::setLocal(flag, 8, 0x856, count);
    }
    if (GfQuestInfo::getState(game, QuestID(0x46B)) == 3) {
        unsigned int count = 0;
        if (GfGameFlag::getLocal(flag, 1, 0xC51B) != 0) {
            count++;
        }
        if (GfGameFlag::getLocal(flag, 1, 0xC4D6) != 0) {
            count++;
        }
        count += (GfGameFlag::getLocal(flag, 1, 0xC436) != 0) + (GfGameFlag::getLocal(flag, 1, 0xC437) != 0) +
                 (GfGameFlag::getLocal(flag, 1, 0xC438) != 0) + (GfGameFlag::getLocal(flag, 1, 0xC439) != 0);
        GfGameFlag::setLocal(flag, 8, 0x856, count + 1);
    }
}

void GfDataUtil::setIra(SDataGame& game, bool flag) {
    GfGameFlag::setLocal(game.m_gameFlag, 1, 0xD860, flag);
}

void GfDataUtil::saveAocVersion(SDataGame& game) {
    game.m_aocIds[0] = GfDataAoc::getContentVersion(static_cast<AOC_TYPE>(0)) + 1;
    game.m_aocIds[1] = GfDataAoc::getContentVersion(static_cast<AOC_TYPE>(1)) + 1;
    game.m_aocIds[2] = GfDataAoc::getContentVersion(static_cast<AOC_TYPE>(2)) + 1;
    game.m_aocIds[3] = GfDataAoc::getContentVersion(static_cast<AOC_TYPE>(3)) + 1;
    game.m_aocIds[4] = GfDataAoc::getContentVersion(static_cast<AOC_TYPE>(4)) + 1;
}

bool GfDataUtil::isInvalidVersionAoc(const SDataGame& game) {
    for (int i = 1; i < 5; i++) {
        if (GfDataAoc::getContentVersion(static_cast<AOC_TYPE>(i)) < game.m_aocIds[i] - 1) {
            return true;
        }
    }
    return false;
}

// Proposed name, not the original's: the symbols leave it unnamed (lbl_71009BA04C)
static const unsigned int s_componentValues[9] = {300, 4, 3, 1, 2, 0, 0, 0, 0};

unsigned int GfDataUtil::getPlayerColiPriority(unsigned int index) {
    return s_componentValues[index];
}

bool GfDataUtil::isEffectKagutsuchi(const DataParamAcc& acc) {
    if (acc.getObjType() == 4 && acc.isValid() && acc.getBdatId() == 1009) {
        return true;
    }
    if (acc.getObjType() == 3 && acc.isValid()) {
        unsigned int driver = acc.getObjType() == 3 ? acc.getBdatId() : 0;
        return driver == 24;
    }
    return false;
}

unsigned int GfDataUtil::getGrowLevelExp(unsigned int id) {
    GfBdatBtl* bdat = GfBdatBtl::get();
    if (GfDataUtil::isIra()) {
        return bdat->getGrowLevelExp2(id);
    }
    return bdat->getGrowLevelExp(id);
}

bool GfDataUtil::isVersion150() {
    if (GfGameFlag::getLocal(1, 0xD788) != 0) {
        return true;
    }
    if (GfDataAoc::sys() != nullptr && GfDataAoc::getContentVersion(static_cast<AOC_TYPE>(3)) > 0) {
        return true;
    }
    return false;
}

bool GfDataUtil::isStartChapterSave() {
    SDataGame* game = GfDataManager::getDataGame();
    unsigned short value = game->m_chapterSaveValue;
    bool same = value == GfDataUtil::getScenarioFlag();
    bool saved = game->m_eventChapterSave != 0;
    return same && saved;
}

bool GfDataDriver::isActivatePartyAll(unsigned int driver) {
    return driver != 0 && getSDataDriver(driver).m_dataType == 1;
}

bool GfDataBlade::getListReserver(mm::mtl::FixedVector<unsigned short, 422>& list) {
    for (unsigned int i = 0; i < 422; i++) {
        unsigned int blade = getBladeID(i);
        if (blade == 0) {
            continue;
        }
        if (isActivateUnuse(blade)) {
            continue;
        }
        if (isActivateMercenaryTeam(blade)) {
            continue;
        }
        unsigned int driver = getSetDriver(blade);
        // the DLC drivers' blades and the blades of drivers in the party's first three slots are not reserves
        if (GfDataDriver::isActivatePartyAll(driver)) {
            unsigned int party = GfDataParty::getDriverPartyID(driver);
            if (getIraDriver(blade) != 0 || party < 3) {
                continue;
            }
        } else if (getIraDriver(blade) != 0) {
            continue;
        }
        if (isDummyBlade(blade)) {
            continue;
        }
        if (isUnselect(blade) || blade == 1113 || blade == 1114) {
            continue;
        }
        list.push_back(blade);
    }
    return !list.empty();
}

// all: false leaves out blades 1002 and 1003; withDummy: true keeps the dummy blades (the parameter names are not
// the original's)
bool GfDataBlade::getListParty(mm::mtl::FixedVector<unsigned short, 422>& list, bool all, bool withDummy) {
    list.clear();
    if (GfDataUtil::isIra()) {
        for (unsigned int blade = 1127; blade < 1133; blade++) {
            if (!isActivateUnuse(blade) && !isUnselect(blade)) {
                list.push_back(blade);
            }
        }
    } else {
        for (unsigned int i = 0; i < 422; i++) {
            unsigned int blade = getBladeID(i);
            if (blade == 0) {
                continue;
            }
            if (!all && (blade == 1002 || blade == 1003)) {
                continue;
            }
            if (!isActivateDriver(blade)) {
                continue;
            }
            if (!withDummy && isDummyBlade(blade)) {
                continue;
            }
            if (isUnselect(blade)) {
                continue;
            }
            list.push_back(blade);
        }
    }
    return !list.empty();
}

unsigned int GfDataDriver::getSkillPoint(unsigned int driver) {
    return getSkillPoint(getSDataDriver(driver));
}

void GfDataDriver::setScenarioMask(unsigned int driver, bool mask) {
    SDataDriver* data = &getSDataDriver(driver);
    data->m_scenarioMask = mask;
}

unsigned int GfDataDriver::getEquipAcce(unsigned int driver, unsigned int slot) {
    return getEquipAcce(getSDataDriver(driver), slot);
}

unsigned int GfDataBlade::getEndCommonBlade() {
    return 1397;
}

void GfDataEnemy::initializeEnemySuppress() {
}

unsigned int GfDataEnemy::getEnemySuppress(unsigned int enemy) {
    if (enemy == 0) {
        return 0;
    }
    if (enemy >= 1500) {
        return GfDataManager::getDataGame()->m_enemySuppressCount[static_cast<int>(enemy) - 1500];
    }
    return GfGameFlag::getLocal(16, enemy + 0x2E);
}

bool GfDataEnemy::incEnemySuppress(unsigned int enemy) {
    if (enemy == 0) {
        return false;
    }
    unsigned int count = GfDataEnemy::getEnemySuppress(enemy);
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

bool GfDataItem::isValidPreciousIra(unsigned int id) {
    return id - 25501 < 499;
}

bool GfDataBlade::isIra(unsigned int blade) {
    return blade - 1124 < 9;
}

unsigned int GfDataBlade::getIraDriver(unsigned int blade) {
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

bool GfDataBlade::getNameWithMsgID(unsigned char*& bdat, unsigned int& id, const SDataBlade& data) {
    unsigned int blade = data.m_bladeId;
    if (blade == 0) {
        return false;
    }
    if (id != 0) {
        if (blade < GfBdatChrBl::get()->getChrBlEnd()) {
            bdat = GfDataBdat::getFP(423);
        } else {
            bdat = GfDataBdat::getFP(396);
        }
        return true;
    }
    unsigned int msg = data.m_nameMsg;
    if (msg == 0) {
        msg = data.m_nameMsgAlt;
    }
    id = msg;
    if (data.m_nameMsg != 0) {
        bdat = GfDataBdat::getFP(423);
    } else {
        bdat = GfDataBdat::getFP(396);
    }
    return id != 0;
}

bool GfDataEvent::isScenarioEvent(unsigned int id) {
    return id - 10001 < 744;
}

bool GfDataItem::isHomuraCookItem(unsigned int id) {
    switch (id) {
    case 40260: case 40261: case 40262: case 40263: case 40264: case 40265: case 40266: case 40267: case 40268:
    case 40312:
        return true;
    default:
        return false;
    }
}

void GfDataBlade::fn_7100234FF8(mm::mtl::FixedVector<unsigned short, 64>& enhances, unsigned int blade, bool keep) {
    unsigned int weapon = 0;
    if (blade != 0) {
        weapon = getSDataBlade(blade)->m_equipWeapon;
    }
    unsigned int enhance = GfBdatItem::get()->getPcWpnEnhance1(weapon);
    if (enhance != 0) {
        mm::mtl::FixedVector<unsigned short, 64> list;
        list.push_back(enhance);
        fn_710024121C(list, keep);
        for (unsigned short* it = list.begin(); it != list.end(); ++it) {
            enhances.push_back(*it);
        }
    }
}

void GfDataBlade::fn_710023510C(mm::mtl::FixedVector<unsigned short, 64>& enhances, unsigned int blade, bool keep) {
    GfBdatBtl* btl = GfBdatBtl::get();
    mm::mtl::FixedVector<unsigned short, 64> list;
    for (int i = 0; i < 3; i++) {
        SDataGame* game = GfDataManager::getDataGame();
        SDataBlade& data = game->m_blades[getBladeIndex(blade)];
        unsigned int level = data.m_skills[i].m_level;
        if (level != 0 && data.m_skills[i].m_id != 0) {
            unsigned int enhance = btl->getBTL_Skill_BlEnhance(data.m_skills[i].m_id, level - 1);
            if (enhance != 0) {
                list.push_back(enhance);
            }
        }
    }
    fn_710024121C(list, keep);
    for (unsigned short* it = list.begin(); it != list.end(); ++it) {
        enhances.push_back(*it);
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

GfItemHandle GfDataDriver::getEquipWpnAcceHandle(unsigned int driver) {
    if (driver - 0x11 < 9) {
        return GfDataManager::getDataGameIra()->m_drivers[driver - 0x11].m_handle;
    }
    return GfItemHandle();
}

void GfDataDriver::setEquipWpnAcce(unsigned int driver, unsigned int item) {
    if (driver - 0x11 < 9) {
        GfDataManager::getDataGameIra()->m_drivers[driver - 0x11].m_item = item;
    }
}

void GfDataDriver::setEquipWpnAcce(SDataIra& data, unsigned int item) {
    data.m_item = item;
}

void GfDataDriver::setEquipWpnAcceHandle(unsigned int driver, GfItemHandle handle) {
    if (driver - 0x11 < 9) {
        SDataIra& data = GfDataManager::getDataGameIra()->m_drivers[driver - 0x11];
        data.m_handle.m_handle = handle.m_handle;
    }
}

unsigned int GfDataDriver::getEquipWpnAcce(unsigned int driver) {
    if (driver - 0x11 < 9) {
        return GfDataManager::getDataGameIra()->m_drivers[driver - 0x11].m_item;
    }
    return 0;
}

}  // namespace gf

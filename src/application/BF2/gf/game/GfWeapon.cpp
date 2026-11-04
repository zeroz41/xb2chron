#include "classes/gf/GfWeapon.h"
#include "gf/GfGameUtil.h"
#include "classes/gf/GfObjPropertyCharacter.h"
#include "gf/GfGameUtil.h"
#include "gf/GfMenuObjUtil.h"
#include "classes/gf/GfFieldSound.h"
#include "string.h"
#include "gf/GfGameUtilSaveData.h"
#include "gf/SDataOption.h"
#include "classes/gf/GfInfo.h"
#include "classes/gf/GfScriptManager.h"
#include "mm/mtl/FixedVector.h"
#include "classes/gf/GfStatusProperty.h"
#include "classes/gf/GfObjPropertyCharacter.h"
#include "classes/gf/GfObjProperty.h"
#include "classes/gf/GfObj.h"
#include "classes/gf/GfComProperty.h"
#include "classes/gmk/GmkMapObj.h"
#include "classes/gmk/GmkRoutedMapObj.h"
#include "classes/gmk/GmkNpc.h"
#include "classes/gf/GfFieldLocator.h"
#include "classes/gmk/GmkRoutedNpc.h"
#include "classes/gmk/GmkManager.h"
#include "classes/gmk/GmkEnemy.h"
#include "classes/gmk/GmkRoutedEnemy.h"
#include "classes/gmk/GmkMob.h"
#include "classes/gmk/GmkRoutedMob.h"
#include "gf/GfGameUtil.h"
#include "classes/gmk/GmkMapObj.h"
#include "classes/gmk/GmkRoutedMapObj.h"
#include "classes/gmk/GmkNpc.h"
#include "classes/gmk/GmkRoutedNpc.h"
#include "classes/gmk/GmkManager.h"
#include "classes/gmk/GmkEnemy.h"
#include "classes/gmk/GmkRoutedEnemy.h"
#include "classes/gmk/GmkMob.h"
#include "classes/gmk/GmkRoutedMob.h"
#include "mm/mtl/FixedList.h"
#include "gf/GfUtil.h"
#include "gf/GfDataHana.h"
#include "gf/GfGameUtilHana.h"
#include "classes/gf/GfEvent.h"
#include "classes/gf/GfWeapon.h"
#include "gf/SDataBlade.h"
#include "classes/gf/GfGameParty.h"
#include "classes/gf/GfGameManager.h"
#include "gf/GfGameUtil.h"
#include "gf/GfDataNanakoori.h"
#include "gf/GfGameUtilNanakoori.h"
#include "gf/GfDataBlade.h"
#include "gf/GfDataHana.h"
#include "gf/SDataDriver.h"
#include "gf/GfDataDriver.h"
#include "gf/GfEquipUtil.h"
#include "classes/gf/GfGameManager.h"
#include "gf/SDataGame.h"
#include "gf/GfGameUtil.h"
#include "gf/GfGameUtilHana.h"
#include "gf/MsgObjectHealHp.h"
#include "gf/MsgObjectMaxHp.h"
#include "classes/gf/GfBdatBtl.h"
#include "classes/gf/GfGameParty.h"
#include "gf/GfDataBlade.h"
#include "gf/GfDataBlade.h"
#include "gf/GfGameUtil.h"
#include "gf/GfGameUtil.h"
#include "gf/GfGameUtilHana.h"
#include "gf/GfGameUtilHana.h"
#include "gf/GfGameUtilCloudSea.h"
#include "gf/GfGameUtilCloudSea.h"
#include "gf/GfGameUtilNanakoori.h"
#include "gf/GfGameUtilNanakoori.h"
#include "classes/gmk/AGmkBase.h"
#include "classes/gmk/AGmkBase.h"
#include "classes/gf/GfFieldGimmick.h"
#include "classes/gf/GfFieldGimmick.h"
#include "classes/gf/GfFieldWeather.h"
#include "classes/gf/GfFieldWeather.h"
#include "gf/GfDataHana.h"
#include "gf/GfDataHana.h"
#include "gf/GfDataNanakoori.h"
#include "gf/GfDataNanakoori.h"
#include "classes/gf/GfGameVoice.h"
#include "classes/gf/GfGameVoice.h"
#include "classes/gf/GfBdatMaplist.h"
#include "classes/gf/GfBdatMaplist.h"
#include "classes/gf/GfGameScene.h"
#include "classes/gf/GfGameScene.h"
#include "classes/gf/GfEvent.h"
#include "classes/gf/GfEvent.h"
#include "classes/gf/GfGameObj.h"
#include "classes/gf/GfGameObj.h"
#include "gf/GfObjUtil.h"
#include "gf/GfObjUtil.h"
#include "classes/btl/DataManager.h"
#include "classes/btl/DataManager.h"
#include "classes/gf/GfAppendWire.h"
#include "classes/gf/GfAppendWire.h"
#include "gf/GfDataUtil.h"
#include "classes/gf/GfMountManager.h"
#include "classes/gf/GfGameManager.h"
#include "classes/gf/GfGameCond.h"
#include "classes/gf/SCOM_ACHIEV_INC.h"
#include "classes/gf/DataParamAcc.h"
#include "classes/gf/GfBdatChrDr.h"
#include "gf/GfObjAcc.h"
#include "classes/gf/GfWeapon.h"
#include "classes/gf/GfManager.h"
#include "classes/gf/GfDataManager.h"
#include "classes/tl/TitleMain.h"
#include "gf/GfItemUtil.h"
#include "mm/mtl/FixStr.h"
#include "gf/MsgObjectHealHp.h"
#include "gf/MsgObjectMaxHp.h"
#include "classes/gf/GfBdatBtl.h"
#include "classes/gf/GfGameParty.h"
#include "classes/gf/SCOM_ADD_ETHER.h"
#include "gf/GfDataItem.h"
#include "gf/GfEquipUtil.h"
#include "classes/gf/GfItemBox.h"
#include "gf/SDataGame.h"
#include "gf/GfDataDriver.h"
#include "classes/gf/GfBdatChrEnArrange.h"
#include "classes/gf/GfGameFlag.h"
#include "classes/fw/MessageObject.h"
#include "gf/SDataBlade.h"
#include "classes/gf/GfMenuManager.h"
#include "classes/gf/GfSound.h"
#include "classes/gf/SCOM_OBJ_ALPHA.h"
#include "gf/GfAppend.h"
#include "fw/LangUtil.h"
#include "classes/gf/GfBdatItem.h"
#include "classes/gf/GfGameEvent.h"
#include "gf/GfDataEvent.h"
#include "gf/QuestTaskParam.h"
#include "gf/GfPartySelect.h"
#include "gf/MsgGameBtlArena.h"
#include "gf/MsgUnk_1000045.h"
#include "classes/gf/SCOM_POPUP.h"
#include "classes/gf/SCOM_LEVELUP_DEVELOP.h"
#include "gf/GfDataDevelop.h"
#include "gf/QuestListAcc.h"
#include "classes/gf/GfGameArena.h"
#include "classes/gf/GfGameEnv.h"
#include "classes/gf/GfGameMercenaries.h"
#include "gf/GfDataMercenaries.h"
#include "gf/SDataSaveIra.h"
#include "gf/GfGameUtilSkipTravel.h"
#include "gf/GfDataMap.h"
#include "classes/gf/GfGameSave.h"
#include "classes/gmk/GmkRoutedEnemy.h"
#include "classes/gmk/GmkTargetPoint.h"
#include "classes/gmk/DistCond.h"
#include "fw/Transform.h"
#include "classes/gf/GfDataBdat.h"
#include "plugin/Bdat.h"
#include "gf/GfGameUtilShop.h"
#include "classes/gf/GfBdatShop.h"
#include "classes/gf/SCOM_ADD_MONEY.h"
#include "classes/gf/SCOM_ADD_DEVELOP.h"
#include "gf/GfKizunaringBlade.h"
#include "gf/GfAchievementRelease.h"
#include "gf/GfDataAchievement.h"
#include "classes/gf/SCOM_ADD_IDEA.h"
#include "classes/gf/SCOM_PARTY_ADD.h"
#include "gf/GfQuestUtil.h"
#include "gf/GfQuestReward.h"
#include "gf/GfKizunaringUtil.h"
#include "classes/gf/GfQuestManager.h"
#include "gf/OwnerBonus.h"
#include "classes/gf/GfBdatBlade.h"
#include "gf/SDataDlc.h"
#include "gf/GfDataDriverSkill.h"
#include "classes/gf/GfComAsm.h"
#include "classes/gf/GfObjSetup.h"
#include "classes/gf/GfGamePlayerFormation.h"
#include "classes/gf/GfFieldTime.h"
#include "classes/gf/GfComBehaviorEvent.h"
#include "classes/gf/GfComBehaviorEnemy.h"
#include "classes/gf/GfComBehaviorNpc.h"
#include "classes/gf/GfObjSetupDriver.h"
#include "classes/gf/GfObjSetupBlade.h"
#include "classes/gf/GfObjSetupEnemy.h"
#include "classes/gf/GfBdatChrEnParam.h"
#include "gf/GfDataEnemy.h"
#include "gf/GfObjInfo.h"
#include "classes/gf/GfObjManager.h"
#include "mm/mtl/RTTI.h"
#include "classes/gf/GfObjSetupWeapon.h"
#include "classes/gf/GfObjSetupNpc.h"
#include "classes/gmk/GmkFieldVolume.h"
#include <algorithm>
#include "classes/gf/SCOM_MAXIMUM_HEAL.h"
#include "classes/gf/SCOM_FIELD_VOICE.h"
#include "mm/mtl/UniquePtr.h"
#include "gf/GfDataBtlDif.h"
#include "gf/GfGameUtilFieldEnhance.h"
#include "gf/GfBootUtil.h"
#include "gf/GfGameUtilDiff.h"
#include "gf/ItemCountLowLevel.h"

namespace gf {

bool GfGameUtil::isUiInfoIconDistMatch(GF_OBJ_HANDLE* handle) {
    if (handle == reinterpret_cast<GF_OBJ_HANDLE*>(-1)) {
        return false;
    }
    {
        GfObjAcc acc(handle);
        if (acc.m_obj == nullptr || acc.isDestroy() || acc.testFlag(17)) {
            return false;
        }
    }
    GfObjAcc acc(handle);
    switch (acc.getType()) {
    case 5:
    case 6:
    case 8:
        break;
    default:
        return false;
    }
    Bdat::uVal val;
    float dist;
    gmk::AGmkBase* gmk = gmk::getBindedGmkInst(handle);
    if (gmk != nullptr) {
        switch (static_cast<int>(gmk->getGmkType())) {
        case 0x9:
        case 0x1C:
        case 0x21:
        case 0x23:
        case 0x29:
        case 0x2A:
        case 0x3A:
        case 0x3C:
            dist = getUiNameDist(handle);
            if (!(dist > 0.0f)) {
                return false;
            }
            val.ulong = Bdat::getValCheck(GfDataBdat::getFP(0x7B), 0, 0x39, 8);
            dist *= val.real;
            break;
        default:
            val.ulong = Bdat::getValCheck(GfDataBdat::getFP(0x7B), 0, 0xC, 8);
            dist = val.real;
            break;
        }
    } else {
        val.ulong = Bdat::getValCheck(GfDataBdat::getFP(0x7B), 0, 0xC, 8);
        dist = val.real;
    }
    if (dist <= 0.0f) {
        return false;
    }
    const mm::Vec3& pos = acc.getWorldTransform().position;
    return gmk::DistCond::isMatch(dist * dist, pos);
}

bool GfGameUtil::isUiNameDistMatch(GF_OBJ_HANDLE* handle) {
    if (handle == reinterpret_cast<GF_OBJ_HANDLE*>(-1)) {
        return false;
    }
    {
        GfObjAcc acc(handle);
        if (acc.m_obj == nullptr || acc.isDestroy() || acc.testFlag(17)) {
            return false;
        }
    }
    GfObjAcc acc(handle);
    float dist = getUiNameDist(handle);
    if (dist <= 0.0f) {
        return false;
    }
    const mm::Vec3& pos = acc.getWorldTransform().position;
    return gmk::DistCond::isMatch(dist * dist, pos);
}

void GfGameUtil::addMoney(int money) {
    int value = GfDataUtil::getMoney() + money;
    value = value < 0 ? 0 : (value > 999999999 ? 999999999 : value);
    GfDataUtil::setMoney(value);
    if (GfGameScene* scene = mm::mtl::PtrSingleton<GfGameScene>::sys()) {
        scene->addMoneyLog();
    }
    if (money > 0) {
        SCOM_ACHIEV_INC::addTotalCount(54, money);
        SCOM_ACHIEV_INC::create(54, money, 0);
        SCOM_ACHIEV_INC::createParty(55, money);
        SCOM_ACHIEV_INC::createParty(56, 1);
    }
}

void GfGameUtil::addCoin(int coin) {
    int value = GfDataUtil::getCoin() + coin;
    value = value < 0 ? 0 : (value > 9999 ? 9999 : value);
    GfDataUtil::setCoin(value);
}

void GfGameUtil::addEther(int ether) {
    int value = GfDataHana::getEther() + ether;
    value = value < 0 ? 0 : (value > 999999999 ? 999999999 : value);
    GfDataHana::setEther(value);
}

void GfGameUtil::addWpForReserve(int wp) {
    mm::mtl::FixedVector<unsigned short, 32> drivers;
    GfPartySelect::getDriverList(drivers, GfPartySelect::LIST_TYPE(1), 0);
    for (unsigned short* it = drivers.begin(); it != drivers.end(); ++it) {
        addWp(*it, 0, wp);
    }
}

bool GfGameUtil::collectGfObjHandleByGmkType(mm::mtl::FixedList<GF_OBJ_HANDLE*, 1024>& list, gmk::GmkType type) {
    gmk::GmkManager* manager = gmk::GmkManager::sys();
    if (manager == nullptr || !manager->isValid()) {
        return false;
    }
    switch (type) {
    case gmk::GmkEnemy::TYPE:
        gmk::GmkManager::sys()->collectGameObjsUnbound<gmk::GmkEnemy>(list);
        break;
    case gmk::GmkRoutedEnemy::TYPE:
        gmk::GmkManager::sys()->collectGameObjsUnbound<gmk::GmkRoutedEnemy>(list);
        break;
    case gmk::GmkNpc::TYPE:
        gmk::GmkManager::sys()->collectGameObjs<gmk::GmkNpc>(list);
        break;
    case gmk::GmkRoutedNpc::TYPE:
        gmk::GmkManager::sys()->collectGameObjs<gmk::GmkRoutedNpc>(list);
        break;
    case gmk::GmkMapObj::TYPE:
        gmk::GmkManager::sys()->collectGameObjs<gmk::GmkMapObj>(list);
        break;
    case gmk::GmkRoutedMapObj::TYPE:
        gmk::GmkManager::sys()->collectGameObjs<gmk::GmkRoutedMapObj>(list);
        break;
    case gmk::GmkMob::TYPE:
        gmk::GmkManager::sys()->collectGameObjsUnbound<gmk::GmkMob>(list);
        break;
    case gmk::GmkRoutedMob::TYPE:
        gmk::GmkManager::sys()->collectGameObjsUnbound<gmk::GmkRoutedMob>(list);
        break;
    default:
        return false;
    }
    return true;
}

void GfGameUtil::setDispByGmkType(gmk::GmkType type, bool disp) {
    gmk::setDispByGmkType(type, disp);
}

void GfGameUtil::setDispByGmkTypeAndBdatId(gmk::GmkType type, int bdatId, bool flag) {
    gmk::setDispByGmkTypeAndBdatId(type, bdatId, flag);
}

void GfGameUtil::setDispByGmkTypeAndGmkIdx(gmk::GmkType type, unsigned int idx, bool flag) {
    gmk::setDispByGmkTypeAndGmkIdx(GfFieldGimmick::getBdatIdFrom_FLD_maplist_To_RSC_GmkSetList(gmk::getCurrentMapBdatId()),
                                   type, idx, flag);
}

int GfGameUtil::getAntiBladeAreaBdatId() {
    return GfFieldGimmick::getBdatIdOfActiveGmkAntiBladeArea();
}

bool GfGameUtil::isGameObjWait(GF_OBJ_HANDLE* handle) {
    return GfObjUtil::testFlag(handle, 0x10);
}

bool GfGameUtil::isPlayVoice(GF_OBJ_HANDLE* handle) {
    return GfGameVoice::getResult(handle) == 2;
}

GF_OBJ_HANDLE* GfGameUtil::getBlade(GF_OBJ_HANDLE* handle) {
    return GfMountManager::getHandle(handle, static_cast<GFATTACH>(0), static_cast<OPTMNT>(3));
}

RESULT_HANA GfGameUtilHana::isOpenArtsCircuit(unsigned int hana, unsigned int circuit) {
    if (!GfDataHana::isValid(hana)) return static_cast<RESULT_HANA>(4);
    return static_cast<RESULT_HANA>(GfDataHana::isOpenCircuit(hana, circuit) ? 0 : 10);
}

int GfGameUtilHana::getEtherForOpenArtsCircuit(unsigned int hana, unsigned int circuit) {
    if (!GfDataHana::isValid(hana)) return 0;
    return GfDataHana::getOpenCircuitEther(hana, circuit);
}

RESULT_HANA GfGameUtilHana::isOpenCondenserCircuit(unsigned int hana, unsigned int circuit) {
    if (!GfDataHana::isValid(hana)) return static_cast<RESULT_HANA>(4);
    return static_cast<RESULT_HANA>(GfDataHana::isOpenCircuit(hana, circuit + 3) ? 0 : 10);
}

int GfGameUtilHana::getEtherForOpenCondenserCircuit(unsigned int hana, unsigned int circuit) {
    if (!GfDataHana::isValid(hana)) return 0;
    return GfDataHana::getOpenCircuitEther(hana, circuit + 3);
}

unsigned int GfGameUtilHana::getPowerRank(unsigned int hana) {
    return GfDataHana::getEquipPowerRank(hana);
}

bool GfGameUtilCloudSea::isEnableChangeInn() {
    unsigned int map = GfGameManager::getMapID();
    if (map == 0) return false;
    unsigned int cond = mm::mtl::PtrSingleton<GfBdatMaplist>::sys()->getMaplistebb_inn_cndID(map);
    if (cond == 0) return false;
    return GfGameCond::isGameCond(cond);
}

int GfGameUtilCloudSea::getCloudSea() {
    return GfFieldWeather::getCurrentCloudSea();
}

void fn_71002E8CD4(unsigned int item) {
    unsigned int begin;
    unsigned int end;
    if (item != 0 &&
        GfDataItem::getItemBdatCount(begin, end, static_cast<ItemType::Type>(GfDataItem::getItemType(item)))) {
        int total = 0;
        for (unsigned int id = begin; id < end; ++id) {
            total += GfItemUtil::getItemBoxCount(id);
        }
        if (GfItemUtil::getEnableStock(item) != total) {
            return;
        }
    }
    if (GfDataItem::getItemBdatCount(begin, end, static_cast<ItemType::Type>(GfDataItem::getItemType(item)))) {
        unsigned int bestCount = 0;
        unsigned int best = 0;
        for (unsigned int id = begin; id < end; ++id) {
            unsigned int count = GfItemUtil::getItemBoxCount(id);
            if (count > bestCount && GfItemUtil::getNoEquipItemHandle(id).m_handle != 0) {
                best = id;
                bestCount = count;
            }
        }
        if (best != 0) {
            GfItemUtil::addItemBox(best, -1);
        }
    }
}

bool GfGameUtilSkipTravel::isEnableSkipTravel(unsigned int mapJump) {
    const char* resource = GfDataMap::getMapResourceName(mapJump);
    mm::mtl::FixStr<64> name;
    name.format("%s_FLD_LandmarkPop", resource);
    unsigned char* fp = Bdat::getFP(name.m_str);
    if (fp == nullptr) {
        return true;
    }
    unsigned int id = Bdat::getIdTop(fp);
    unsigned int end = id + Bdat::getIdCount(fp);
    bool found = false;
    bool enable;
    for (; id < end; ++id) {
        if (Bdat::getValCheckU16(fp, "MAPJUMPID", id) == mapJump) {
            unsigned short cond = Bdat::getValCheckU16(fp, "stoff_cndID", id);
            enable = cond == 0 || !GfGameCond::isGameCond(cond);
            found = true;
            break;
        }
    }
    return !found || enable;
}

bool GfGameUtilNanakoori::checkCompleteMission(unsigned int mission, unsigned int flag) {
    if (flag != 4 || GfDataNanakoori::isMissionComplete(mission)) return false;
    GfDataNanakoori::setMissionComplete(mission);
    return true;
}

}  // namespace gf

namespace gf {

bool GfGameUtil::isCondDriverModel(unsigned int driver) {
    return GfGameCond::isGameCond(mm::mtl::PtrSingleton<GfBdatChrDr>::sys()->getChrDrCondition(driver));
}

const char* GfGameUtil::getAcceDriverModel(unsigned int driverId, bool check, bool flag) {
    if (check && driverId == 6) {
        flag = flag | GfDataEvent::isInvalidMelefRetarget(GfGameEvent::getStartEventId());
    }
    return fn_71002DF4C4(driverId, flag);
}

const char* GfGameUtil::getSalvageDriverModel(unsigned int driver) {
    if (driver == 1) {
        return GfGameCond::isGameCond(mm::mtl::PtrSingleton<GfBdatChrDr>::sys()->getChrDrCondition(1)) ? "pc/pc000104"
                                                                                                        : "pc/pc000102";
    }
    return "";
}

unsigned int GfGameUtil::getNowHp(GF_OBJ_HANDLE* handle, unsigned int type, unsigned int id) {
    fn_71002DF8B0(handle);
    if (GfObj* obj = GfObjUtil::getObj(handle)) {
        if (GfComProperty* property = obj->getComponent<GfComProperty>(5)) {
            if (GfStatusProperty* status = property->m_status.get()) {
                return status->m_hp;
            }
        }
    }
    DataParamAcc acc(type, id, GimmickType(0));
    return acc.getHpMax(true);
}

void GfGameUtil::changeStopLayer(GF_OBJ_HANDLE* handle, bool stop) {
    GfObjAcc acc(handle);
    if (acc.m_obj == nullptr) {
        return;
    }
    unsigned int layer = stop ? 1 : 4;
    GfObj* obj = acc.getObj();
    unsigned int section = GfObjUtil::getLayerSection(layer);
    unsigned int current = acc.getLayer();
    unsigned int currentSection = GfObjUtil::getLayerSection(current);
    if (section != currentSection && GfObjUtil::getParentHandle(handle) == reinterpret_cast<GF_OBJ_HANDLE*>(-1)) {
        int diff = section - currentSection;
        mm::mtl::IntrusiveList<fw::UpdatableObject>& children = obj->m_children;
        for (mm::mtl::IntrusiveList<fw::UpdatableObject>::iterator it = children.begin(), end = children.end();
             it != end; ++it) {
            fw::UpdatableObject& child = *it;
            GfObj* childObj = child.getRTTI()->isKindOf(&GfObj::m_rtti) ? static_cast<GfObj*>(&child) : nullptr;
            GfObjUtil::changeLayer(childObj, childObj->m_updateBit + diff);
        }
        GfObjUtil::changeLayer(obj, current + diff);
    }
}

void GfGameUtil::fn_71002DF8B0(GF_OBJ_HANDLE*& handle) {
    DataParamAcc acc(handle);
    if (GfObjUtil::isValid(handle) && acc.getObjType() == 3 &&
        GfDataDriver::isIra(acc.isValid() && acc.getObjType() == 3 ? acc.getBdatId() : 0)) {
        mm::mtl::FixedVector<unsigned short, 32> drivers;
        drivers.push_back(GfDataDriver::getIraFront(acc.isValid() && acc.getObjType() == 3 ? acc.getBdatId() : 0));
        GfDataDriver::getIraBack(drivers, acc.isValid() && acc.getObjType() == 3 ? acc.getBdatId() : 0);
        for (unsigned short id : drivers) {
            GF_OBJ_HANDLE* driver = GfGameParty::getHandleDriverByBdatID(id);
            if (GfObjUtil::isValid(driver)) {
                handle = driver;
                break;
            }
        }
    }
}

unsigned int GfGameUtil::getMaxHp(GF_OBJ_HANDLE* handle, unsigned int type, unsigned int id) {
    fn_71002DF8B0(handle);
    if (GfObj* obj = GfObjUtil::getObj(handle)) {
        if (GfComProperty* property = obj->getComponent<GfComProperty>(5)) {
            if (GfStatusProperty* status = property->m_status.get()) {
                return status->m_maxHp;
            }
        }
    }
    DataParamAcc acc(type, id, GimmickType(0));
    return acc.getHpMax(true);
}

bool GfGameUtil::getNowHpForUi(GF_OBJ_HANDLE* handle, unsigned int* hp) {
    fn_71002DF8B0(handle);
    if (GfObjProperty* property = GfObjUtil::getProperty(handle)) {
        if (property->m_character == nullptr) {
            return false;
        }
        *hp = property->m_character->m_uiHp;
        return true;
    }
    return false;
}

void GfGameUtil::setGameObjWait(GF_OBJ_HANDLE* handle, bool wait) {
    GfObjUtil::setFlag(handle, 0x10, wait);
    GfObjManager::ResultList list;
    GfObjManager* manager = mm::mtl::PtrSingleton<GfObjManager>::sys();
    if (manager != nullptr && manager->getFollowObj(list, handle)) {
        for (GfObjManager::ResultList::iterator it = list.begin(); it != list.end(); ++it) {
            setGameObjWait(*it, wait);
        }
    }
}

void GfGameUtil::levelupForEnemy(GF_OBJ_HANDLE* handle, unsigned int add) {
    DataParamAcc acc(handle);
    GFOBJ_INFO* info = GfObjManager::getObjInfo(handle);
    if (info == nullptr || info->m_setup == nullptr) {
        return;
    }
    GfObjSetup* setup = info->m_setup;
    if (setup->m_type != info->m_obj->m_type || info->m_obj->m_type != 5) {
        return;
    }
    GfObjSetupEnemy* enemy = mm::mtl::rttiCast<GfObjSetupEnemy>(setup);
    if (enemy == nullptr) {
        return;
    }
    unsigned int last = mm::mtl::PtrSingleton<GfBdatChrEnParam>::sys()->getChrEnParamTableEnd() - 1;
    unsigned int level = acc.getLevel(false) + add;
    if (level > last) {
        level = last;
    }
    GfDataEnemy::setupGameParamForLevel(*enemy->m_sdata, level);
    GfObj* obj = GfObjUtil::getObj(handle);
    MsgObjectMaxHp maxHp(acc.getHpMax(false));
    obj->sendMessage(obj, maxHp);
    unsigned int hpMax = acc.getHpMax(false);
    unsigned int hp = acc.getHp();
    if (hpMax > hp) {
        MsgObjectHealHp msg(hpMax - hp, 0);
        msg.m_flags = MsgObjectHealHp::Flags();
        GfObj* healed = GfObjUtil::getObj(handle);
        healed->sendMessage(healed, msg);
    }
    GfGameUtil::refreshEnemyHp(handle);
}

bool GfGameUtil::getMaxHpForUi(GF_OBJ_HANDLE* handle, unsigned int* hp) {
    fn_71002DF8B0(handle);
    if (GfObjProperty* property = GfObjUtil::getProperty(handle)) {
        if (property->m_character == nullptr) {
            return false;
        }
        *hp = property->m_character->m_uiMaxHp;
        return true;
    }
    return false;
}

void GfGameUtil::requestFieldDamage(GF_OBJ_HANDLE* handle) {
    if (GfGameScene* scene = mm::mtl::PtrSingleton<GfGameScene>::sys()) {
        scene->setDamageCharacter(handle);
    }
}

int GfGameUtil::getObjAttribute(GF_OBJ_HANDLE* handle) {
    DataParamAcc acc(handle);
    return acc.getAttribute(-1, false);
}

void GfGameUtil::startWire(GF_OBJ_HANDLE* handle, GF_OBJ_HANDLE* target, float time) {
    if (GfGameScene* scene = mm::mtl::PtrSingleton<GfGameScene>::sys()) {
        if (GfAppendWire* wire = scene->getAppendControl(handle)) {
            wire->startWire(target, time);
        }
    }
}

void GfGameUtil::startWireWithClose(GF_OBJ_HANDLE* handle, GF_OBJ_HANDLE* target, float time, float a, float b) {
    if (GfGameScene* scene = mm::mtl::PtrSingleton<GfGameScene>::sys()) {
        if (GfAppendWire* wire = scene->getAppendControl(handle)) {
            wire->startWireWithClose(target, time, a, b);
        }
    }
}

void GfGameUtil::endWire(GF_OBJ_HANDLE* handle, float time) {
    if (GfGameScene* scene = mm::mtl::PtrSingleton<GfGameScene>::sys()) {
        if (GfAppendWire* wire = scene->getAppendControl(handle)) {
            wire->endWire(time);
        }
    }
}

void GfGameUtil::changeHikariCurrent(bool hikari) {
    GfDataBlade::setHikariCurrent(hikari);
    GfEvent::callHikariCurrent(hikari);
}

int GfGameUtil::getObjNumberByEnArrangeId(unsigned int arrangeId) {
    int num = 0;
    if (GfGameObj* obj = mm::mtl::PtrSingleton<GfGameObj>::sys()) {
        num = obj->getObjNumberByEnArrangeId(arrangeId);
    }
    return GfObjUtil::getSetupObjNumberByEnArrangeId(arrangeId) + num;
}

void GfGameUtil::setMaxPartyGauge() {
    if (btl::DataManager* data = mm::mtl::PtrSingleton<btl::DataManager>::sys()) {
        data->SetPartyGauge(300, false);
    }
}

}  // namespace gf

namespace gf {

bool GfGameUtil::isDispRexCrystal() {
    unsigned short blade = GfDataUtil::getScenarioFlag();
    return blade != 0 && !(blade >= 1001 && blade <= 1030);
}

bool GfGameUtil::isDispHomuraCrystal() {
    unsigned short blade = GfDataUtil::getScenarioFlag();
    return !(blade >= 1001 && blade <= 1030);
}

bool GfGameUtil::isDispMetsuCrystal() {
    return !GfGameCond::isGameCond(2695);
}

void GfGameUtil::dispRexCrystal(GF_OBJ_HANDLE* handle, bool disp) {
    GfObjAcc acc(handle);
    int mesh = acc.getExtMeshIdx("cc_rex");
    if (mesh >= 0) {
        acc.setExtMeshAlpha(mesh, disp ? 1.0f : 0.0f);
    }
}

void GfGameUtil::dispHomuraCrystal(GF_OBJ_HANDLE* handle, bool disp) {
    if (handle == reinterpret_cast<GF_OBJ_HANDLE*>(-1)) return;
    GfObjAcc acc(handle);
    int mesh = acc.getExtMeshIdx("cc_homu");
    if (mesh >= 0) {
        acc.setExtMeshAlpha(mesh, disp ? 1.0f : 0.0f);
    }
    mesh = acc.getExtMeshIdx("cc_zohar");
    if (mesh >= 0) {
        acc.setExtMeshAlpha(mesh, disp ? 0.0f : 1.0f);
    }
}

void GfGameUtil::dispMetsuCrystal(GF_OBJ_HANDLE* handle, bool disp) {
    if (handle == reinterpret_cast<GF_OBJ_HANDLE*>(-1)) return;
    GfObjAcc acc(handle);
    int mesh = acc.getExtMeshIdx("Front_Armor");
    if (mesh >= 0) {
        acc.setExtMeshAlpha(mesh, disp ? 1.0f : 0.0f);
    }
}

void GfGameUtil::setKosmosArts3EnableBothWeapon(GF_OBJ_HANDLE* handle, bool enable) {
    GfObjAcc acc(handle);
    if (acc.getType() != 4 || acc.getBladeId() != 0x40f) {
        return;
    }
    GfWeapon* weapon = GfMountManager::getGfWeapon(handle, static_cast<GFATTACH>(0));
    if (weapon == nullptr) {
        return;
    }
    bool useSecond = weapon->m_useSecond;
    weapon->m_useSecond = false;
    GfObjAcc weaponAcc(weapon->getObjHandles()[1]);
    weaponAcc.setDisp(static_cast<OBJDISP>(0x20), enable);
    if (GfObj* obj = weaponAcc.getObj()) {
        obj->setUpdateComponent(enable);
    }
    weapon->m_useSecond = useSecond;
}

GF_OBJ_HANDLE* GfGameUtil::getDriverWeaponRight(GF_OBJ_HANDLE* handle) {
    if (GfWeapon* weapon = GfMountManager::getGfWeapon(handle, static_cast<GFATTACH>(0))) {
        GF_OBJ_HANDLE* obj = weapon->getObjHandles()[0];
        if (obj != reinterpret_cast<GF_OBJ_HANDLE*>(-1)) return obj;
    }
    if (GfWeapon* weapon = GfMountManager::getGfWeapon(handle, static_cast<GFATTACH>(3))) {
        GF_OBJ_HANDLE* obj = weapon->getObjHandles()[0];
        if (obj != reinterpret_cast<GF_OBJ_HANDLE*>(-1)) return obj;
    }
    return reinterpret_cast<GF_OBJ_HANDLE*>(-1);
}

GF_OBJ_HANDLE* GfGameUtil::getDriverWeaponLeft(GF_OBJ_HANDLE* handle) {
    if (GfWeapon* weapon = GfMountManager::getGfWeapon(handle, static_cast<GFATTACH>(0))) {
        GF_OBJ_HANDLE* obj = weapon->getObjHandles()[1];
        if (obj != reinterpret_cast<GF_OBJ_HANDLE*>(-1)) return obj;
    }
    if (GfWeapon* weapon = GfMountManager::getGfWeapon(handle, static_cast<GFATTACH>(3))) {
        GF_OBJ_HANDLE* obj = weapon->getObjHandles()[0];
        if (obj != reinterpret_cast<GF_OBJ_HANDLE*>(-1)) return obj;
    }
    return reinterpret_cast<GF_OBJ_HANDLE*>(-1);
}

}  // namespace gf

namespace gf {

void GfGameUtil::makeWeaponStateIdle(mm::mtl::FixStr<32>& out, GF_OBJ_HANDLE* owner, bool battle) {
    const char* name = util::getFilePtrFromPath(GfObjUtil::getMotionResourceName(owner));
    out = "S_";
    out += name;
    out += "_";
    out += battle ? "btidle" : "idle";
}

void GfGameUtil::makeWeaponStateIdle(mm::mtl::FixStr<32>& out, unsigned int weaponId, bool battle) {
    const char* name = util::getFilePtrFromPath(GfDataDriver::getMotionResourceName(weaponId));
    out = "S_";
    out += name;
    out += "_";
    out += battle ? "btidle" : "idle";
}

// "S_<weapon type, two digits>_btidle" (inline: makeStateIdle and makeStateIdleByBlade inline it, its string
// first on their stacks; the name is not the original's)
static void makeStateIdleByWpnType(mm::mtl::FixStr<32>& out, unsigned int type) {
    mm::mtl::FixStr<16> num;
    if (type >= 10) {
        num.format("%d_", type);
    } else {
        num.format("0%d_", type);
    }
    out = "S_";
    out += num.m_str;
    out += "btidle";
}

void GfGameUtil::makeStateIdle(mm::mtl::FixStr<32>& out, GF_OBJ_HANDLE* handle, bool battle) {
    if (!battle) {
        out = "S_idle";
        return;
    }
    DataParamAcc param(handle);
    if (param.getObjType() == 4 || param.getObjType() == 5) {
        out = "S_btidle";
        return;
    }
    unsigned int blade = param.getBlade(-1, false);
    if (blade == 0) {
        return;
    }
    if (GfGameManager::isEvent(false)) {
        unsigned int type = GfDataBlade::getBladeWpnType(blade);
        if (param.getObjType() == 3 && (type == 18 || type == 19)) {
            out = "S_btidle";
            return;
        }
    }
    unsigned int type = GfDataBlade::getBladeWpnType(blade);
    makeStateIdleByWpnType(out, type);
}

void GfGameUtil::makeStateIdleByBlade(mm::mtl::FixStr<32>& out, unsigned int blade, bool battle) {
    if (!battle) {
        out = "S_idle";
        return;
    }
    if (blade == 0) {
        return;
    }
    if (GfDataDriver::isIra(GfDataBlade::getIraDriver(blade))) {
        out = "S_01_btidle";
        return;
    }
    unsigned int type = GfDataBlade::getBladeWpnType(blade);
    if (GfGameManager::isEvent(false) && (type == 18 || type == 19)) {
        out = "S_btidle";
        return;
    }
    makeStateIdleByWpnType(out, type);
}

// the name of a weapon's battle (or field) command for its owner (motion: from the motion resource's name, else
// the model's; the parameter names are not the original's)
void GfGameUtil::makeWeaponCommandBattle(mm::mtl::FixStr<32>& out, GF_OBJ_HANDLE* owner, bool battle, bool motion) {
    const char* name = util::getFilePtrFromPath(motion ? GfObjUtil::getMotionResourceName(owner)
                                                       : GfObjUtil::getResourceName(owner));
    out = "C_";
    out += name;
    out += "_";
    out += battle ? "btstart" : "btend";
}

void GfGameUtil::makeWeaponCommandBattle(mm::mtl::FixStr<32>& out, unsigned int weaponId, bool battle, bool motion) {
    const char* name = util::getFilePtrFromPath(motion ? GfDataDriver::getMotionResourceName(weaponId)
                                                       : GfDataDriver::getModelResourceName(weaponId));
    out = "C_";
    out += name;
    out += "_";
    out += battle ? "btstart" : "btend";
}

unsigned int GfGameUtil::getKizunaLink(unsigned int blade) {
    GfBdatBtl* bdat = mm::mtl::PtrSingleton<GfBdatBtl>::sys();
    unsigned int set = GfDataBlade::getSDataBlade(blade)->m_kizunaLinkSet;
    unsigned int type = bdat->getBTL_Bl_KizunaLinkSetLinkChType(set);
    unsigned int num = bdat->getBTL_Bl_KizunaLinkSetLinkChNum(set);
    switch (type) {
    case 0:
        return bdat->getBTL_Bl_KizunaLinkSetKizunaLink1(set);
    case 1:
        if (getTrustRank(blade) >= static_cast<int>(num)) {
            return bdat->getBTL_Bl_KizunaLinkSetKizunaLink2(set);
        }
        return bdat->getBTL_Bl_KizunaLinkSetKizunaLink1(set);
    case 2:
        if (GfGameCond::isGameCond(num)) {
            return bdat->getBTL_Bl_KizunaLinkSetKizunaLink2(set);
        }
        return bdat->getBTL_Bl_KizunaLinkSetKizunaLink1(set);
    }
    return 0;
}

void GfGameUtil::makeCommandBattle(mm::mtl::FixStr<32>& out, bool battle) {
    out = "C_";
    out += battle ? "btstart" : "btend";
}

void GfGameUtil::makeStateBattle(mm::mtl::FixStr<32>& out, GF_OBJ_HANDLE* handle, bool battle) {
    GfObjAcc acc(handle);
    int type = acc.getType();
    unsigned int bdatId = acc.getBdatId();
    if (type == 3 && !(bdatId >= 7 && bdatId <= 9)) {
        DataParamAcc param(handle);
        out.format("S_%02d_", param.getWeaponType(-1, false));
    } else {
        out = "S_";
    }
    out += battle ? "btstart" : "btend";
}

void GfGameUtil::makeStateBattleByBlade(mm::mtl::FixStr<32>& out, unsigned int blade, bool battle) {
    DataParamAcc param(4, blade, GimmickType(0));
    out.format("S_%02d_", param.getWeaponType(-1, false));
    out += battle ? "btstart" : "btend";
}

void GfGameUtil::setPartyChange10020() {
    for (unsigned int i = 0; i != 422; i++) {
        unsigned int blade = GfDataBlade::getBladeID(i);
        if (blade != 0 && GfDataBlade::isUnselect(blade)) {
            if (GfDataBlade::isRegularBlade(blade) && GfDataBlade::isUnselect(blade) &&
                GfDataBlade::isActivateUnuse(blade)) {
                GfDataBlade::setActivateReserver(blade);
            }
            GfDataBlade::setUnselect(blade, false);
        }
    }
    if (!GfGameManager::isClearGame()) {
        SCOM_PARTY_ADD::addBlade(1002, 1, -1);
        SCOM_PARTY_ADD::addBlade(1001, 1, -1);
        SCOM_PARTY_ADD::addBlade(1003, 1, -1);
    }
    SCOM_PARTY_ADD::addDriver(2, -1);
    SCOM_PARTY_ADD::addDriver(4, -1);
    SCOM_PARTY_ADD::addDriver(6, -1);
    SCOM_PARTY_ADD::addDriver(3, -1);
}

bool GfGameUtil::isBladeInVillage(unsigned int blade) {
    if (blade - 1001 < 3) return false;
    if (GfDataHana::isValid(blade)) return false;
    if (GfDataBlade::isActivateUnuse(blade)) return false;
    if (GfDataBlade::isUnselect(blade)) return false;
    return GfDataBlade::getSetDriver(blade) == 0;
}

int GfGameUtilHana::getConvertToEther(unsigned int item) {
    ItemProperty property;
    GfItemUtil::getProperty(property, item, 0);
    if (static_cast<unsigned int>(property.m_type - 16) > 4) return 0;
    return GfItemUtil::getItemBoxCountWithoutEquip(item);
}

}  // namespace gf

namespace gf {

void GfGameUtil::addTrustPointIra(unsigned int driver, unsigned int point) {
    addTrustPoint(GfDataDriver::getIraBlade(driver, -1), point);
}

void GfGameUtil::setAchievementReleaseLevel(unsigned int blade, unsigned int line, unsigned int level) {
    if (level > 5) {
        level = 5;
    }
    ACHIEVEMENT_TYPE type;
    unsigned int index;
    if (!GfDataAchievement::getAchievementType(type, index, line)) return;
    if (!GfDataBlade::setAchievReleaseLevel(blade, line, level)) return;
    if (unsigned int id = GfDataBlade::getAchievementID(blade, line, level)) {
        QuestListAcc* acc = QuestListAcc::get();
        unsigned int category = acc->getFLD_AchievementListIdeaCategory(id);
        if (int point = acc->getFLD_AchievementListIdeaCategory(id)) {
            SCOM_ADD_IDEA::create(reinterpret_cast<GF_OBJ_HANDLE*>(-1), category, point);
        }
    }
    GfAchievementRelease release;
    release.m_blade = blade;
    release.m_type = type;
    release.m_level = level;
    GfEvent::callAchievmentRelease(release);
}

bool GfGameUtil::execActivateMercenaryTeamForBlade(unsigned int blade) {
    if (GfDataBlade::isActivateMercenaryTeam(blade)) return false;
    ActivateType from = GfDataBlade::getBladeActivateType(*GfDataBlade::getSDataBlade(blade));
    GfDataBlade::setActivateMercenaryTeam(blade);
    GfEvent::callBladeActivate(blade, from, static_cast<ActivateType>(3));
    return true;
}

bool GfGameUtil::isDummyBlade(GF_OBJ_HANDLE* handle) {
    DataParamAcc acc(handle);
    if (acc.getObjType() != 4) return false;
    return GfDataBlade::isDummyBlade(acc.isValid() ? acc.getBdatId() : 0);
}

}  // namespace gf

namespace gf {

void GfGameUtilCloudSea::setInnCloudSea(CLOUD_SEA cloudSea) {
    GfDataMap::setCloudType(GfGameManager::getMapID(), cloudSea);
    GfFieldWeather::setCloudSea(GfGameManager::getMapID(), cloudSea);
}

}  // namespace gf

namespace gf {

void GfGameUtil::incGameClearCount() {
    SDataGame* game = GfDataManager::getDataGame();
    GfDataUtil::setClearGame(*game, true);
    if (game->m_gameClearCount < 9999) {
        game->m_gameClearCount++;
    }
}

void GfGameUtil::setHp(GF_OBJ_HANDLE* handle, unsigned int hp) {
    if (GfObj* obj = GfObjUtil::getObj(handle)) {
        MsgObjectHealHp msg(hp, 2);
        fw::MessageObject* object = obj;
        object->recieveMessage(object, msg);
    }
}

void GfGameUtil::incEnemySuppress(unsigned int enemy) {
    if (!GfGameManager::isBattleArenaActive() && GfDataEnemy::incEnemySuppress(enemy) &&
        mm::mtl::PtrSingleton<GfBdatChrEnArrange>::sys()->isChrEnArrangeFlagNamed(enemy) &&
        GfDataEnemy::getEnemySuppress(enemy) == 1) {
        GfDataEnemy::incNamedDefeatNum();
    }
}

void GfGameUtil::subExpInn(unsigned int driver, unsigned int exp) {
    if (driver == 0) {
        return;
    }
    DataParamAcc acc(3, driver, static_cast<GimmickType>(0));
    unsigned int now = acc.getExp();
    unsigned int value = now < exp ? 0 : now - exp;
    if (value > 999999999) {
        value = 999999999;
    }
    GfDataDriver::setExp(driver, value);
    if (GfDataDriver::isIra(driver)) {
        GfDataDriver::getIraFront(driver);
    }
}

// inline: adds the driver's battle experience to its experience (capped at 999999999) and clears it; the name is
// not the original's
static inline void flushDriverBattleExp(unsigned int driver) {
    unsigned int exp = GfDataDriver::getBattleExp(driver) + GfDataDriver::getExp(driver);
    GfDataDriver::setExp(driver, exp > 999999999 ? 999999999 : exp);
    GfDataDriver::setBattleExp(driver, 0);
}

void GfGameUtil::execLevelDown(unsigned int driver, unsigned int level) {
    unsigned int current = GfDataDriver::getLevel(driver);
    if (current <= level) {
        return;
    }
    flushDriverBattleExp(driver);
    do {
        current--;
        GfDataDriver::setLevel(driver, current);
        GfDataDriver::setBattleExp(driver, GfDataDriver::getBattleExpNextLevel(driver));
        flushDriverBattleExp(driver);
    } while (level != current);
}

void GfGameUtil::execDriverArtsLevelUp(unsigned int driver, unsigned int arts, unsigned int level) {
    GfBdatBtl* bdat = mm::mtl::PtrSingleton<GfBdatBtl>::sys();
    DataParamAcc acc(3, driver, GimmickType(0));
    if (!acc.isScenarioMask()) {
        unsigned int type = bdat->getArtsDrWpnType(arts);
        unsigned int current = acc.getDriverArtsLevel(arts);
        while (current < level && current < 5) {
            unsigned int point = acc.getWeaponPoint(type);
            unsigned int need = bdat->getArtsDrNeedWP(arts, current + 1);
            if (point < need) {
                break;
            }
            acc.setDriverArtsLevel(arts, current + 1);
            acc.addWeaponPoint(type, -need);
            current = acc.getDriverArtsLevel(arts);
        }
    }
}

int GfGameUtil::execDriverSkillLevelUp(unsigned int driver, unsigned int line, unsigned int level, bool round) {
    int result = checkDriverSkillLevelUp(driver, line, level, round);
    if (result != 0) {
        return result;
    }
    GfDataDriver::addSkillPoint(driver, -static_cast<int>(GfDataDriverSkill::getNextSkillPoint(driver, line, round)));
    GfDataDriverSkill::setSkillLevel(driver, line, level, round);
    return 0;
}

int GfGameUtil::checkDriverSkillLevelUp(unsigned int driver, unsigned int line, unsigned int level, bool round) {
    unsigned int now = GfDataDriverSkill::getSkillLevel(driver, line, round);
    if (now > 2) {
        return 1;
    }
    if (now + 1 != level) {
        return 2;
    }
    if (!GfDataDriverSkill::isSkillUnlock(driver, line, level, round)) {
        return 4;
    }
    if (GfDataDriverSkill::getNextSkillPoint(driver, line, round) > GfDataDriver::getSkillPoint(driver)) {
        return 3;
    }
    return 0;
}

void GfGameUtil::addWp(unsigned int driver, unsigned int id, int wp) {
    if (driver == 0) {
        GfObjAcc acc(GfGameManager::getPartyLeaderDriver());
        driver = acc.getDriverId();
        if (driver == 0) {
            return;
        }
    }
    DataParamAcc acc(3, driver, static_cast<GimmickType>(0));
    if (!acc.isScenarioMask()) {
        if (id == 0) {
            id = acc.getWeaponType(-1, false);
        }
        acc.addWeaponPoint(id, wp);
    }
}

void GfGameUtil::execLevelUp(unsigned int driver, unsigned int level) {
    DataParamAcc acc(3, driver, static_cast<GimmickType>(0));
    if (acc.isScenarioMask()) {
        return;
    }
    unsigned int prev = acc.getLevel(false);
    unsigned int exp = acc.getExp();
    exp += acc.getBattleExp();
    if (prev >= 99) {
        return;
    }
    GfBdatBtl* btl = mm::mtl::PtrSingleton<GfBdatBtl>::sys();
    for (unsigned int lv = acc.getLevel(false); lv < level; lv = acc.getLevel(false)) {
        if (lv < btl->getGrowStart() || lv >= btl->getGrowEnd() - 1) {
            break;
        }
        unsigned int need = GfDataUtil::getGrowLevelExp(lv + 1);
        if (exp < need) {
            break;
        }
        exp -= need;
        GfDataDriver::setLevel(driver, lv + 1);
    }
    if (acc.getLevel(false) == prev) {
        return;
    }
    GfDataDriver::setExp(driver, exp);
    GfDataDriver::setBattleExp(driver, 0);
    if (GfDataDriver::isIra(driver)) {
        GfDataDriver::getIraFront(driver);
    }
    if (GfMenuManager::isOpenCampMenu()) {
        SCOM_FIELD_VOICE::createLevelupForCamp(ParamObj(3, driver));
    } else {
        SCOM_FIELD_VOICE::createLevelup(ParamObj(3, driver));
    }
    GF_OBJ_HANDLE* handle = GfGameParty::getHandleDriverByBdatID(driver);
    if (handle != reinterpret_cast<GF_OBJ_HANDLE*>(-1)) {
        SCOM_MAXIMUM_HEAL::create(handle);
    }
    GfEvent::callDriverLevel(driver, acc.getLevel(false), prev);
    GfDataDriver::openDriverArtsForLevelup(driver);
    if (GfDataDriver::isIraFront(driver)) {
        mm::mtl::FixedVector<unsigned short, 32> list;
        GfDataDriver::getIraBack(list, driver);
        for (const unsigned short& id : list) {
            if (GfDataDriver::isAttachedParty(id)) {
                GfDataDriver::openDriverArtsForLevelup(id);
            }
        }
    }
}

void GfGameUtil::addWpForObject(unsigned int driver, unsigned int id, int wp) {
    if (!GfDataDriver::isIra(driver)) {
        addWp(driver, id, wp);
        return;
    }
    mm::mtl::FixedVector<unsigned short, 32> drivers;
    drivers.push_back(driver);
    unsigned int base = GfDataDriver::getIraFront(driver);
    if (std::find(drivers.begin(), drivers.end(), static_cast<unsigned short>(base)) == drivers.end() &&
        GfDataDriver::isAttachedParty(base)) {
        drivers.push_back(base);
    }
    mm::mtl::FixedVector<unsigned short, 32> list;
    GfDataDriver::getIraBack(list, base);
    for (const unsigned short& other : list) {
        if (GfDataDriver::isAttachedParty(other) && std::find(drivers.begin(), drivers.end(), other) == drivers.end()) {
            drivers.push_back(other);
        }
    }
    for (const unsigned short& target : drivers) {
        unsigned int blade = GfDataDriver::getIraBlade(target, -1);
        addWp(target, GfDataBlade::getBladeWpnType(blade), wp);
    }
}

void GfGameUtil::addSp(unsigned int driver, int sp) {
    if (driver == 0) {
        mm::mtl::FixedVector<unsigned short, 32> drivers;
        GfPartySelect::getDriverList(drivers, static_cast<GfPartySelect::LIST_TYPE>(2), 0);
        for (unsigned short* it = drivers.begin(); it != drivers.end(); ++it) {
            addSp(*it, sp);
        }
    } else {
        DataParamAcc acc(3, driver, static_cast<GimmickType>(0));
        if (!acc.isScenarioMask()) {
            GfDataDriver::addSkillPoint(driver, sp);
        }
    }
}

void GfGameUtil::addSpForObject(unsigned int driver, int sp) {
    if (!GfGameManager::isGameTypeIra()) {
        addSp(driver, sp);
        return;
    }
    if (driver != 0) {
        GfBdatChrDr* bdat = mm::mtl::PtrSingleton<GfBdatChrDr>::sys();
        fn_71002DBB58(bdat->getChrIrGroupID(bdat->getChrDrIraParam(driver)), sp);
        return;
    }
    for (unsigned int i = 0; i < 10; i++) {
        if (unsigned int id = GfGameParty::getDriverBdatId(i, static_cast<PTPOS>(0))) {
            GfBdatChrDr* bdat = mm::mtl::PtrSingleton<GfBdatChrDr>::sys();
            fn_71002DBB58(bdat->getChrIrGroupID(bdat->getChrDrIraParam(id)), sp);
        }
    }
}

void GfGameUtil::addIdeaPoint(unsigned int driver, unsigned int type, int point) {
    point += GfGameManager::getOwnerBonus().m_values[4];
    if (driver == 0) {
        mm::mtl::FixedVector<unsigned short, 32> drivers;
        GfPartySelect::getDriverList(drivers, static_cast<GfPartySelect::LIST_TYPE>(2), 0);
        for (unsigned short* it = drivers.begin(); it != drivers.end(); ++it) {
            addIdeaPoint(*it, type, point);
        }
    } else {
        DataParamAcc acc(3, driver, static_cast<GimmickType>(0));
        DataIdeaAcc idea(acc);
        unsigned int level = idea.getLevel(type);
        idea.addPoint(type, point);
        if (level != idea.getLevel(type)) {
            SCOM_POPUP::createIdea(driver, type, idea.getLevel(type));
        }
    }
}

void GfGameUtil::addDevelopPoint(unsigned int zone, unsigned int point) {
    if (GfGameManager::isGameTypeIra()) {
        return;
    }
    if (GfDataMap::isArcadiaDestroy() && zone == 6) {
        zone = 5;
    }
    unsigned int add = GfGameManager::getOwnerBonus().m_values[5] + point;
    if (zone == 0) {
        zone = 1;
    }
    unsigned int max = QuestListAcc::get()->getFLD_DevelopmentLevelValue(7);
    unsigned int value = GfDataDevelop::getPoint(zone) + add;
    if (value > max) {
        value = max;
    }
    GfDataDevelop::setPoint(zone, value);
    SCOM_LEVELUP_DEVELOP::create();
}

void GfGameUtil::execDevelopLevelUp() {
    if (GfGameManager::isGameTypeIra()) {
        return;
    }
    QuestListAcc* acc = QuestListAcc::get();
    unsigned int level1 = acc->getFLD_DevelopmentLevelValue(3);
    unsigned int level2 = acc->getFLD_DevelopmentLevelValue(4);
    unsigned int level3 = acc->getFLD_DevelopmentLevelValue(5);
    unsigned int level4 = acc->getFLD_DevelopmentLevelValue(6);
    unsigned int level5 = acc->getFLD_DevelopmentLevelValue(7);
    // the map of each development zone (1-8), for the popup
    static const unsigned int s_zoneMaps[8] = {3, 6, 9, 10, 14, 12, 13, 15};
    for (unsigned int zone = 1; zone <= 8; zone++) {
        unsigned int level = GfDataDevelop::getLevel(zone);
        unsigned int point = GfDataDevelop::getPoint(zone);
        if (level < level5 && point >= level5) {
            GfDataDevelop::setLevel(zone, 5);
        } else if (level < level4 && point >= level4) {
            GfDataDevelop::setLevel(zone, 4);
        } else if (level < level3 && point >= level3) {
            GfDataDevelop::setLevel(zone, 3);
        } else if (level < level2 && point >= level2) {
            GfDataDevelop::setLevel(zone, 2);
        } else if (level < level1 && point >= level1) {
            GfDataDevelop::setLevel(zone, 1);
        }
        unsigned int now = GfDataDevelop::getLevel(zone);
        if (level != now) {
            SCOM_POPUP::createDevelop(s_zoneMaps[zone - 1], now);
        }
    }
    GfQuestManager::eventCheckTaskAll();
}

void GfGameUtil::addTrustPoint(unsigned int blade, unsigned int point) {
    unsigned int trust = GfDataBlade::getTrustPoint(blade) + point;
    if (GfGameManager::isGameTypeIra()) {
        trust += GfGameManager::getOwnerBonus().m_values[14] * 50;
    }
    if (trust > 0xFFFF) {
        trust = 0xFFFF;
    }
    GfDataBlade::setTrustPoint(blade, trust);
    GfEvent::callDebugChangeIdea(4, blade, 0, 0);
    int before = GfDataBlade::getTrustRank(blade);
    if (GfDataBlade::isCompleteAchievement(blade)) {
        int rank = GfDataBlade::getTrustRank(blade);
        while (rank >= 6 && rank <= 15 &&
               mm::mtl::PtrSingleton<GfBdatBlade>::sys()->getFLD_IdeaTableTrustPoint(rank) <= trust) {
            GfDataBlade::setTrustRank(blade, static_cast<GfIdea>(rank + 1));
            rank = GfDataBlade::getTrustRank(blade);
        }
        if (before < static_cast<int>(GfDataBlade::getTrustRank(blade))) {
            unsigned int driver = GfDataBlade::getSetDriver(blade);
            if (driver == 0) {
                driver = GfDataBlade::getCreator(blade);
            }
            if (driver != 0) {
                SCOM_POPUP::createAffinity(blade, driver, GfDataBlade::getTrustRank(blade));
            }
        }
    }
    GfQuestManager::eventCheckTaskAll();
}

unsigned int GfGameUtil::getGroupClass(unsigned int driver) {
    mm::mtl::FixedVector<unsigned short, 32> drivers;
    GfDataDriver::getIraBack(drivers, driver);
    unsigned int total = 0;
    unsigned int count = 0;
    for (const unsigned short& id : drivers) {
        if (GfDataDriver::isActivateParty(id)) {
            total += GfGameUtil::getTrustRank(GfDataDriver::getIraBlade(id, -1));
            count++;
        }
    }
    if (count != 0) {
        total /= count;
    }
    if (total > 6) {
        total = 6;
    }
    if (total == 0) {
        total = 1;
    }
    GfBdatChrDr* chr = mm::mtl::PtrSingleton<GfBdatChrDr>::sys();
    unsigned int group = chr->getChrIrGroupID(chr->getChrDrIraParam(driver));
    return mm::mtl::PtrSingleton<GfBdatBtl>::sys()->getBTL_IrGroupRevGroupRev(total, group - 1);
}

bool GfGameUtil::isPointSavable(const mm::Vec3& pos) {
    const gmk::GmkManager* manager = gmk::GmkManager::sys();
    if (manager == nullptr) {
        return true;
    }
    for (gmk::GmkSet* const* it = manager->m_gmkSets.begin(); it != manager->m_gmkSets.end(); ++it) {
        gmk::IGmkList* list = (*it)->getGmkList(gmk::GmkFieldVolume::TYPE);
        if (list == nullptr) {
            continue;
        }
        unsigned int num = list->getInstNum();
        for (unsigned int i = 0; i < num; i++) {
            gmk::AGmkBase* gmk = list->getInst(i);
            if (gmk != nullptr && gmk->isValid() && gmk->isInsideShape(pos, 0.0f)) {
                return false;
            }
        }
    }
    return true;
}

void GfGameUtil::addTrustRankForKizunaRing(unsigned int blade) {
    int rank = GfDataBlade::getTrustRank(blade);
    if (rank > 5) {
        return;
    }
    unsigned int next = rank + 1;
    GfDataBlade::setTrustRank(blade, static_cast<GfIdea>(next));
    GfEvent::callDebugChangeIdea(4, blade, 0, 0);
    unsigned int driver = GfDataBlade::getSetDriver(blade);
    if (driver == 0) {
        driver = GfDataBlade::getCreator(blade);
    }
    if (GfGameManager::isGameTypeIra()) {
        driver = GfDataDriver::getIraFront(GfDataBlade::getIraDriver(blade));
    }
    if (driver != 0) {
        SCOM_POPUP::createAffinity(blade, driver, next);
    }
}

bool GfGameUtil::getUiGetHitonowa(GF_OBJ_HANDLE* handle) {
    if (handle == reinterpret_cast<GF_OBJ_HANDLE*>(-1)) {
        return false;
    }
    {
        GfObjAcc acc(handle);
        if (acc.m_obj == nullptr || acc.isDestroy() || acc.testFlag(0x11)) {
            return false;
        }
    }
    {
        GfObjAcc acc(handle);
        if (acc.getType() != 6) {
            return false;
        }
    }
    gmk::AGmkBase* gimmick = gmk::getBindedGmkInst(handle);
    if (gimmick == nullptr || gimmick->getGmkType() != static_cast<gmk::GmkType>(3)) {
        return false;
    }
    return Bdat::getFlagVal(gimmick->getBindedBdatFp(), "flag", gimmick->m_createInfo.m_bdatId, "HITONOWAGET") != 0;
}

bool GfGameUtil::isBattleWeapon(GF_OBJ_HANDLE* handle) {
    if (GfObjUtil::getObjType(handle) == 3) {
        GfObjAcc acc(handle);
        if (acc.getDriverId() == 0x11) {
            if (GfComAsm* comAsm = acc.getObj()->getComponent<GfComAsm>(2)) {
                if (comAsm->getStateName(static_cast<AnimLayer>(0)) != nullptr &&
                    strstr(comAsm->getStateName(static_cast<AnimLayer>(0)), "btstart") != nullptr) {
                    return true;
                }
            }
        }
        OPTMNT type = GfMountManager::getMountType(handle, static_cast<GFATTACH>(0));
        if (type == 1 || type == 3) {
            return true;
        }
    }
    return false;
}

void GfGameUtil::addEtherCube(unsigned int value) {
    if (GfGameArena* arena = mm::mtl::PtrSingleton<GfGameArena>::sys()) {
        MsgGameBtlArena msg(0xE);
        msg.pad_28 = value;
        static_cast<fw::MessageObject*>(arena)->recieveMessage(arena, msg);
    }
}

void GfGameUtil::addScore(unsigned int value) {
    if (GfGameArena* arena = mm::mtl::PtrSingleton<GfGameArena>::sys()) {
        MsgGameBtlArena msg(0xF);
        msg.pad_2C = value;
        static_cast<fw::MessageObject*>(arena)->recieveMessage(arena, msg);
    }
}

void GfGameUtil::applyClearTimeForArena(unsigned int value) {
    if (GfGameArena* arena = mm::mtl::PtrSingleton<GfGameArena>::sys()) {
        MsgGameBtlArena msg(0x10);
        msg.pad_30 = value;
        static_cast<fw::MessageObject*>(arena)->recieveMessage(arena, msg);
    }
}

void GfGameUtil::addExpInn(unsigned int exp) {
    if (exp == 0) {
        return;
    }
    mm::mtl::FixedVector<unsigned short, 32> drivers;
    GfPartySelect::getDriverList(drivers, static_cast<GfPartySelect::LIST_TYPE>(8), 0);
    GfPartySelect::getDriverList(drivers, static_cast<GfPartySelect::LIST_TYPE>(7), 0);
    if (!GfGameManager::isGameTypeIra()) {
        for (int id = 1; id < 7; id++) {
            if (std::find(drivers.begin(), drivers.end(), static_cast<unsigned short>(id)) != drivers.end()) {
                continue;
            }
            if (id == 5 && GfDataUtil::getScenarioFlag() > 0xBE8) {
                continue;
            }
            drivers.push_back(id);
        }
    }
    if (GfGameManager::isGameTypeIra()) {
        unsigned int seen = 0;
        for (unsigned short* it = drivers.begin(); it != drivers.end();) {
            unsigned int bit = 1 << GfDataDriver::getIraGroup(*it);
            if (seen & bit) {
                it = drivers.erase(it);
            } else {
                seen |= bit;
                ++it;
            }
        }
    }
    for (unsigned short id : drivers) {
        fn_71002DA8FC(id, exp);
    }
}

void GfGameUtil::addExpBattle(unsigned int driver, unsigned int exp) {
    if (exp == 0) {
        return;
    }
    if (driver != 0) {
        fn_71002DAD5C(driver, exp);
        return;
    }
    mm::mtl::FixedVector<unsigned short, 32> drivers;
    GfPartySelect::getDriverList(drivers, static_cast<GfPartySelect::LIST_TYPE>(8), 0);
    GfPartySelect::getDriverList(drivers, static_cast<GfPartySelect::LIST_TYPE>(7), 0);
    if (GfGameManager::isGameTypeIra()) {
        unsigned int seen = 0;
        for (unsigned short* it = drivers.begin(); it != drivers.end();) {
            unsigned int bit = 1 << GfDataDriver::getIraGroup(*it);
            if (seen & bit) {
                it = drivers.erase(it);
            } else {
                seen |= bit;
                ++it;
            }
        }
    }
    for (unsigned short id : drivers) {
        fn_71002DAD5C(id, exp);
    }
}

bool GfGameUtil::findNpcMat44(mm::Mat44& mtx, int bdatId) {
    if (gmk::GmkManager::sys() == nullptr) {
        return false;
    }
    int mapId = gmk::getCurrentMapBdatId();
    int setId = gmk::GmkManager::sys()->findFirstBdatId_RSC_GmkSetList(mapId);
    if (setId <= 0) {
        return false;
    }
    const gmk::GmkSet* set = gmk::GmkManager::sys()->findGmkSet(setId);
    if (set == nullptr) {
        return false;
    }
    const gmk::AGmkBase* npc = set->findFirstGmkInstByBdatId(gmk::GmkNpc::TYPE, bdatId);
    if (npc == nullptr) {
        return false;
    }
    npc->getMatrix(mtx, true);
    return true;
}

bool GfGameUtil::getGmkTargetPointPos(mm::Vec3& pos, unsigned int id) {
    if (id == 0) {
        return false;
    }
    const gmk::GmkManager* manager = gmk::GmkManager::sys();
    if (manager == nullptr) {
        return false;
    }
    for (gmk::GmkSet* const* it = manager->m_gmkSets.begin(); it != manager->m_gmkSets.end(); ++it) {
        gmk::IGmkList* list = (*it)->getGmkList(gmk::GmkTargetPoint::TYPE);
        if (list == nullptr || !list->isValid() || list->getInstNum() < id) {
            continue;
        }
        gmk::AGmkBase* gmk = list->getInst(id - 1);
        if (gmk == nullptr || !gmk->isValid()) {
            continue;
        }
        const mm::Vec3* point = gmk->m_pos;
        pos.x = point->x;
        pos.y = point->y;
        pos.z = point->z;
        return true;
    }
    return false;
}

bool GfGameUtil::getGmkTargetPointPos(mm::Vec3& pos, GF_OBJ_HANDLE* handle) {
    gmk::AGmkBase* gmk = gmk::getBindedGmkInst(handle);
    if (gmk != nullptr) {
        switch (gmk->getGmkType()) {
        case gmk::GmkEnemy::TYPE:
        case gmk::GmkRoutedEnemy::TYPE: {
            const gmk::GmkEnemy::BdatInfo* info = static_cast<const gmk::GmkEnemy::BdatInfo*>(gmk->m_createInfo.m_bdatInfo);
            return getGmkTargetPointPos(pos, info->m_targetPointName);
        }
        default:
            break;
        }
    }
    return false;
}

void GfGameUtil::clearEnemyRepopCounter(int enemy) {
    gmk::GmkManager* manager = gmk::GmkManager::sys();
    if (manager == nullptr) {
        return;
    }
    auto f = [enemy](const gmk::AGmkBase& gmk) {
        if (!gmk.isValid()) {
            return;
        }
        switch (gmk.getGmkType()) {
        case gmk::GmkEnemy::TYPE: {
            const gmk::GmkEnemy& e = static_cast<const gmk::GmkEnemy&>(gmk);
            if (e.m_insts.m_popInfo.hasEneID(enemy, true)) {
                e.m_insts.reqClearRepopCounter();
            }
            break;
        }
        case gmk::GmkRoutedEnemy::TYPE: {
            const gmk::GmkRoutedEnemy& e = static_cast<const gmk::GmkRoutedEnemy&>(gmk);
            if (e.m_insts.m_popInfo.hasEneID(enemy, true)) {
                e.m_insts.reqClearRepopCounter();
            }
            break;
        }
        default:
            break;
        }
    };
    manager->traverseGmkInst(gmk::GmkEnemy::TYPE, f);
    manager->traverseGmkInst(gmk::GmkRoutedEnemy::TYPE, f);
}

bool GfGameUtil::execTurnCmd(const ExecTurnCmdInfo& info) {
    GfObjAcc acc(info.m_handle);
    GfObj* obj = acc.getObj();
    if (obj == nullptr) {
        return false;
    }
    if (GfComBehaviorEvent* behavior = obj->getComponent<GfComBehaviorEvent>(6)) {
        behavior->execTurnCmd(info.m_rotY, info.m_arg1, info.m_arg2, info.m_arg3);
        return true;
    }
    if (GfComBehaviorEnemy* behavior = obj->getComponent<GfComBehaviorEnemy>(6)) {
        behavior->execTurnCmd(info.m_rotY, info.m_arg1, info.m_arg2, info.m_arg3);
        return true;
    }
    if (GfComBehaviorNpc* behavior = obj->getComponent<GfComBehaviorNpc>(6)) {
        behavior->execTurnCmd(info.m_rotY, info.m_arg1, info.m_arg2, info.m_arg3);
        return true;
    }
    return false;
}

bool GfGameUtil::isTurnEnd(GF_OBJ_HANDLE* handle) {
    GfObjAcc acc(handle);
    GfObj* obj = acc.getObj();
    if (obj == nullptr) {
        return false;
    }
    if (GfComBehaviorEvent* behavior = obj->getComponent<GfComBehaviorEvent>(6)) {
        return behavior->m_turnCmd.pad_6c;
    }
    if (GfComBehaviorEnemy* behavior = obj->getComponent<GfComBehaviorEnemy>(6)) {
        return behavior->m_turnCmd.pad_6c;
    }
    if (GfComBehaviorNpc* behavior = obj->getComponent<GfComBehaviorNpc>(6)) {
        return behavior->m_turnCmd.pad_6c;
    }
    return false;
}

int GfGameUtil::fn_71002DE83C(GF_OBJ_HANDLE* handle) {
    if (GfObjUtil::isTrinityBlade(handle)) {
        return -1;
    }
    unsigned int party = GfGameParty::getPartyId(handle);
    int type = GfObjUtil::getObjType(handle);
    unsigned int id = GfObjUtil::getPartyPos(handle);
    GfGamePlayerFormation* formation = mm::mtl::PtrSingleton<GfGamePlayerFormation>::sys();
    for (unsigned long i = 0; i < 9; i++) {
        GfObjSetup* setup = GfObjUtil::getObjSetup(formation->m_players[i].m_handle);
        if (setup != nullptr && setup->m_partyId == party &&
            GfObjUtil::getObjType(formation->m_players[i].m_handle) == type &&
            GfObjUtil::getPartyPos(formation->m_players[i].m_handle) == id) {
            return i;
        }
    }
    return -1;
}

int GfGameUtil::getFormationPlayerID(GF_OBJ_HANDLE* handle) {
    if (GfObjUtil::isTrinityBlade(handle)) {
        return -1;
    }
    GfGameParty::getPartyId(handle);
    unsigned int hierarchy = GfGameParty::getHierarchyByHandle(handle);
    if (hierarchy == 0) {
        return -1;
    }
    GfObjAcc acc(handle);
    if (acc.isRebuild()) {
        const int* id;
        if (acc.getType() == 3) {
            id = &mm::mtl::rttiCast<GfObjSetupDriver>(GfObjManager::getObjInfo(handle)->m_setup)->pad_70;
        } else if (acc.getType() == 4) {
            id = &mm::mtl::rttiCast<GfObjSetupBlade>(GfObjManager::getObjInfo(handle)->m_setup)->pad_74;
        } else {
            return hierarchy - 1;
        }
        if (*id >= 0) {
            return *id;
        }
    }
    return hierarchy - 1;
}

void GfGameUtil::resetFormationParam(GF_OBJ_HANDLE* handle) {
    if (GfObjUtil::isTrinityBlade(handle)) {
        return;
    }
    GfGamePlayerFormation* formation = mm::mtl::PtrSingleton<GfGamePlayerFormation>::sys();
    for (unsigned int i = 0; i < 9; i++) {
        if (formation->m_players[i].m_handle == handle) {
            formation->m_players[i].m_followIndex = -1;
            formation->m_players[i].m_handle = reinterpret_cast<GF_OBJ_HANDLE*>(-1);
            formation->m_players[i].m_standalone = true;
            return;
        }
    }
}

bool GfGameUtil::execActivateUnuseForBlade(unsigned int blade, bool releaseOrbs) {
    if (GfDataBlade::isCommonBlade(blade)) {
        GfKizunaringBlade::removeAchievement(blade);
    }
    if (releaseOrbs) {
        for (unsigned int slot = 0; slot < GfDataBlade::getEquipOrbMax(blade); slot++) {
            GfEquipUtil::equipBladeOrb(blade, 0, slot, GfItemHandle());
        }
    }
    ActivateType from = GfDataBlade::getBladeActivateType(*GfDataBlade::getSDataBlade(blade));
    if (GfDataBlade::setActivateUnuse(blade)) {
        if (releaseOrbs && GfDataBlade::isRareBlade(blade)) {
            GfDataBlade::resetAttachedParty(blade);
        }
        GfEvent::callBladeActivate(blade, from, static_cast<ActivateType>(0));
    }
    return false;
}

bool GfGameUtil::equipDriverBladeForce(unsigned int driver) {
    if (GfDataDriver::equipDriverBladeFromReserverBlade(driver)) {
        return false;
    }
    switch (driver) {
    case 1:
        return execEquipMercenariesBlade(1, GfDataBlade::getStartCommonBlade(), false);
    case 2:
        return execEquipMercenariesBlade(2, 1004, false);
    case 3:
        return execEquipMercenariesBlade(3, 1010, false);
    case 6:
        return execEquipMercenariesBlade(6, 1009, false);
    }
    return false;
}

bool GfGameUtil::execEquipMercenariesBlade(unsigned int driver, unsigned int blade, bool flag) {
    if (!GfDataBlade::isActivateMercenaryTeam(blade)) {
        return false;
    }
    if (flag || GfDataDriver::getBladeSet(driver) < 0 || GfDataBlade::isDummyBlade(GfDataDriver::getBlade(driver, -1))) {
        unsigned int team = GfDataMercenaries::getTeamID(blade);
        GfGameMercenaries::cancelMission(GfDataMercenaries::getMissionIdByBlade(blade));
        GfGameMercenaries::clearTeamMember(team);
        if (GfDataBlade::isActivateReserver(blade)) {
            GfDataBlade::setActivateDriver(blade, -1, driver, 0);
        }
    }
    return true;
}

void GfGameUtil::execClearMercenariesInHomuraHikari() {
    unsigned int blade = 1001;
    if (!GfDataBlade::isActivateMercenaryTeam(blade)) {
        blade = 1002;
        if (!GfDataBlade::isActivateMercenaryTeam(blade)) {
            return;
        }
    }
    unsigned int team = GfDataMercenaries::getTeamID(blade);
    GfGameMercenaries::cancelMission(GfDataMercenaries::getMissionIdByBlade(blade));
    GfGameMercenaries::clearTeamMember(team);
}

void GfGameUtil::setSaikaLensOff(GF_OBJ_HANDLE* handle) {
    unsigned short progress = GfDataUtil::getScenarioFlag();
    GfObjAcc acc(handle);
    switch (acc.getType()) {
    case 4:
        if (acc.getBladeId() != 0x3F2) {
            return;
        }
        break;
    case 5:
        if (mm::mtl::PtrSingleton<GfBdatChrEnArrange>::sys()->getChrEnArrangeBladeID(acc.getEnArrangeId()) != 0x3F2) {
            return;
        }
        break;
    case 6: {
        GFOBJ_INFO* info = GfObjManager::getObjInfo(handle);
        if (info != nullptr && info->m_setup != nullptr) {
            GfObjSetup* setup = info->m_setup;
            if (setup->m_type == info->m_obj->m_type && info->m_obj->m_type == 6) {
                GfObjSetupNpc* npc = mm::mtl::rttiCast<GfObjSetupNpc>(setup);
                if (npc != nullptr && npc->m_bdatId != 0x3F2) {
                    return;
                }
            }
        }
        break;
    }
    }
    int left = acc.getExtMeshIdx("mt_lens_L");
    if (left >= 0) {
        acc.setExtMeshAlpha(left, progress > 7024 ? 0.0f : 1.0f);
    }
    int right = acc.getExtMeshIdx("mt_lens_R");
    if (right >= 0) {
        acc.setExtMeshAlpha(right, progress > 7024 ? 0.0f : 1.0f);
    }
}

void GfGameUtil::setSaikaLensOff() {
    mm::mtl::FixedVector<GF_OBJ_HANDLE*, 8> handles;
    GfGameObj::ObjList& blades = *GfGameObj::getList(4);
    for (GfGameObj::ObjList::iterator it = blades.begin(); it != blades.end(); ++it) {
        DataParamAcc acc(*it);
        if (acc.isValid() && acc.getBdatId() == 0x3F2) {
            handles.push_back(*it);
        }
    }
    GfBdatChrEnArrange* arrange = mm::mtl::PtrSingleton<GfBdatChrEnArrange>::sys();
    GfGameObj::ObjList& enemyBlades = *GfGameObj::getListEnemyBlade();
    for (GfGameObj::ObjList::iterator it = enemyBlades.begin(); it != enemyBlades.end(); ++it) {
        DataParamAcc acc(*it);
        unsigned int id = 0;
        if (acc.isValid()) {
            id = acc.getBdatId();
        }
        if (arrange->getChrEnArrangeBladeID(id) == 0x3F2) {
            handles.push_back(*it);
        }
    }
    GfGameObj::ObjList& npcs = *GfGameObj::getList(6);
    for (GfGameObj::ObjList::iterator it = npcs.begin(); it != npcs.end(); ++it) {
        DataParamAcc acc(*it);
        if (acc.isValid() && acc.getBdatId() == 0x3F2) {
            handles.push_back(*it);
        }
    }
    for (GF_OBJ_HANDLE* handle : handles) {
        setSaikaLensOff(handle);
    }
}

void GfGameUtil::dispLauraMedal(GF_OBJ_HANDLE* handle, bool show) {
    if (handle == reinterpret_cast<GF_OBJ_HANDLE*>(-1)) {
        return;
    }
    GfObjAcc acc(handle);
    int mesh = acc.getExtMeshIdx("medal");
    if (mesh >= 0) {
        acc.setExtMeshAlpha(mesh, show ? 1.0f : 0.0f);
    }
}

GF_OBJ_HANDLE* GfGameUtil::getWeaponOwner(GF_OBJ_HANDLE* handle) {
    GF_OBJ_HANDLE* owner = GfObjUtil::getOwner(handle);
    const GfAppendInfo* append = GfObjUtil::getAppendInfo(handle, static_cast<GFATTACH>(0));
    if (append == nullptr) {
        return owner;
    }
    GFOBJ_INFO* info = GfObjManager::getObjInfo(handle);
    if (info == nullptr || info->m_setup == nullptr) {
        return owner;
    }
    GfObjSetup* setup = info->m_setup;
    if (setup->m_type != info->m_obj->m_type || info->m_obj->m_type != 10) {
        return owner;
    }
    GfObjSetupWeapon* weapon = mm::mtl::rttiCast<GfObjSetupWeapon>(setup);
    if (weapon == nullptr || append->m_appends[1].size() == 0 || weapon->m_param.pad_98.m_secondList) {
        return owner;
    }
    return GfMountManager::getHandle(owner, static_cast<GFATTACH>(0), static_cast<OPTMNT>(3));
}

void GfGameUtil::setBladeSelect(GF_OBJ_HANDLE* handle, int select) {
    DataParamAcc acc(handle);
    unsigned int prev = acc.getAttribute(-1, false);
    acc.setBladeSet(select);
    if (GfObj* obj = GfObjUtil::getObj(handle)) {
        MsgUnk_1000045 msg(0);
        msg.m_value = acc.getAttribute(-1, false);
        msg.pad_C = prev;
        static_cast<fw::MessageObject*>(obj)->recieveMessage(obj, msg);
    }
}

bool GfGameUtil::isDriverEquipBlade(unsigned int driver, unsigned int blade) {
    if (driver == 0) {
        return false;
    }
    if (GfDataBlade::isActivateUnuse(blade)) {
        return false;
    }
    unsigned int setDriver = GfDataBlade::getSetDriver(blade);
    if (setDriver != 0 && GfDataDriver::isActivateUnuse(setDriver)) {
        return false;
    }
    int creator = GfDataBlade::getCreator(blade);
    if (creator == 0) {
        return driver == 1;
    }
    if (creator == static_cast<int>(driver)) {
        return true;
    }
    if (GfDataHana::isValid(blade)) {
        return driver == 4;
    }
    if (driver == 11 || driver == 1) {
        if (GfGameCond::isGameCond(mm::mtl::PtrSingleton<GfBdatChrDr>::sys()->getChrDrCondition(1))) {
            return true;
        }
    }
    return false;
}

unsigned int GfGameUtil::execAddRareBlade(const SDataBlade& data) {
    unsigned int blade = GfDataBlade::addRareBlade(data);
    if (blade != 0) {
        SDataBlade* sdata = GfDataBlade::getSDataBlade(blade);
        ActivateType from = GfDataBlade::getBladeActivateType(*sdata);
        if (blade == 0x3FE) {
            GfDataBlade::setCreator(1050, GfDataBlade::getCreator(0x3FE));
        }
        if (sdata->m_createEvent != 0) {
            setWatchedEvent(sdata->m_createEvent);
        }
        GfEvent::callBladeActivate(blade, from, static_cast<ActivateType>(1));
    }
    return blade;
}

unsigned int GfGameUtil::execAddCommonBlade(SDataBlade& data, unsigned int item) {
    if (GfDataUtil::isClearGame() && data.m_bladeId == GfDataBlade::getStartCommonBlade()) {
        GfDataBlade::setActivateReserver(data.m_bladeId);
        return data.m_bladeId;
    }
    data.m_bladeId = item == 45010 ? GfDataBlade::getStartCommonBlade() : 0;
    unsigned int blade = GfDataBlade::addCommonBlade(data);
    if (blade != 0) {
        SDataBlade* sdata = GfDataBlade::getSDataBlade(blade);
        if (sdata->m_createEvent != 0) {
            setWatchedEvent(sdata->m_createEvent);
        }
        GfEvent::callBladeActivate(blade, static_cast<ActivateType>(0), static_cast<ActivateType>(1));
    }
    return blade;
}

bool GfGameUtil::execActivateReserverForBlade(unsigned int blade) {
    ActivateType from = GfDataBlade::getBladeActivateType(*GfDataBlade::getSDataBlade(blade));
    if (GfDataBlade::isActivateReserver(blade)) {
        if (GfDataBlade::getSetDriver(blade) != 0) {
            GfDataDriver::unsetBlade(blade);
        }
        return true;
    }
    if (!GfDataBlade::setActivateReserver(blade)) {
        return false;
    }
    GfEvent::callBladeActivate(blade, from, static_cast<ActivateType>(1));
    return true;
}

bool GfGameUtil::hasBelonging(GF_OBJ_HANDLE* handle, unsigned int slot) {
    GfWeapon* weapon = GfMountManager::getGfWeapon(handle, static_cast<GFATTACH>(2));
    if (weapon == nullptr) {
        return false;
    }
    if (slot == 2) {
        return weapon->getObjHandles()[1] != reinterpret_cast<GF_OBJ_HANDLE*>(-1);
    }
    if (slot == 1) {
        return weapon->getObjHandles()[0] != reinterpret_cast<GF_OBJ_HANDLE*>(-1);
    }
    return false;
}

RESULT_HANA GfGameUtilHana::getEquip(EquipHana& equip, unsigned int hana) {
    if (!GfDataHana::isValid(hana)) {
        return static_cast<RESULT_HANA>(4);
    }
    equip = *GfDataHana::getEquipParts(hana);
    return static_cast<RESULT_HANA>(0);
}

void GfGameUtil::refreshEnhanceState(unsigned int driver) {
    GF_OBJ_HANDLE* handle = GfGameParty::getHandleDriverByBdatID(driver);
    if (GfObj* obj = GfObjUtil::getObj(handle)) {
        DataParamAcc acc(3, driver, static_cast<GimmickType>(0));
        MsgObjectMaxHp msg(acc.getHpMax(false));
        fw::MessageObject* object = obj;
        object->recieveMessage(object, msg);
    }
}

int GfGameUtilHana::getNeedEtherForExecPowerRankup(unsigned int hana, unsigned int rank) {
    unsigned int current = GfDataHana::getEquipPowerRank(hana);
    int ether = 0;
    if (current < rank) {
        GfBdatBtl* bdat = mm::mtl::PtrSingleton<GfBdatBtl>::sys();
        for (unsigned int r = current + 1; r <= rank; r++) {
            ether += bdat->getBTL_HanaPowerEtherNum(r, hana - 1005);
        }
    }
    return ether;
}

RESULT_HANA GfGameUtilHana::execConvertToEther(unsigned int item) {
    ItemProperty property;
    GfItemUtil::getProperty(property, item, 0);
    if (static_cast<unsigned int>(property.m_type - 16) > 4) {
        return static_cast<RESULT_HANA>(0);
    }
    if (GfItemUtil::getItemBoxCountWithoutEquip(item) == 0) {
        return static_cast<RESULT_HANA>(8);
    }
    GfItemUtil::addItemBox(item, -1);
    if (property.m_dustEther != 0) {
        SCOM_ADD_ETHER::create(property.m_dustEther);
    }
    return static_cast<RESULT_HANA>(0);
}

int GfGameUtilHana::getEmptyParts(unsigned int item) {
    if (item == 0) {
        return 0;
    }
    unsigned int begin;
    unsigned int end;
    if (!GfDataItem::getItemBdatCount(begin, end, static_cast<ItemType::Type>(GfDataItem::getItemType(item)))) {
        return 0;
    }
    int count = 0;
    for (unsigned int i = begin; i < end; i++) {
        count += GfItemUtil::getItemBoxCount(i);
    }
    return GfItemUtil::getEnableStock(item) - count;
}

void GfGameUtil::execEquipDriverDefaultAcce(unsigned int driver) {
    if (driver == 0 || GfDataDriver::isEquipDefaultAcce(driver)) {
        return;
    }
    GfDataDriver::getSDataDriver(driver)->m_defaultAcceDone = true;
    unsigned int accessory = mm::mtl::PtrSingleton<GfBdatChrDr>::sys()->getChrDrDefAcce(driver);
    if (accessory != 0) {
        if (GfItemUtil::isEnableAddItemBox(accessory, 1)) {
            GfItemUtil::addItemBoxWithSilent(accessory, 1);
        }
        GfEquipUtil::equipDriverAcce(driver, 0, accessory, GfItemHandle());
    }
}

void GfGameUtil::execEquipIraDefaultWpnAcce(unsigned int driver) {
    if (!GfDataDriver::isIraFront(driver) || GfDataDriver::getEquipWpnAcce(driver) != 0) {
        return;
    }
    unsigned int id = mm::mtl::PtrSingleton<GfBdatChrDr>::sys()->getChrDrIraParam(driver);
    unsigned int accessory = mm::mtl::PtrSingleton<GfBdatChrDr>::sys()->getChrIrDefWpnAcce(id);
    if (accessory != 0) {
        if (GfItemUtil::isEnableAddItemBox(accessory, 1)) {
            GfItemUtil::addItemBoxWithSilent(accessory, 1);
        }
        GfEquipUtil::equipIraWpnAcce(driver, accessory, GfItemHandle());
    }
}

void GfGameUtil::execDriverDead(unsigned int driver) {
    for (unsigned int slot = 0; slot < 3; slot++) {
        GfEquipUtil::equipDriverAcce(driver, slot, 0, GfItemHandle());
    }
    for (int num = GfDataDriver::getMaxSetBladeNum(driver); num > 0; num--) {
        if (unsigned int blade = GfDataDriver::getBlade(driver, num - 1)) {
            GfDataDriver::unsetBlade(blade);
        }
    }
}

}  // namespace gf

namespace gf {

bool GfGameUtil::isCondBladeModel(unsigned int blade) {
    if (GfGameManager::isChangeNormalHomuraForce(blade)) {
        return false;
    }
    GfObjAcc acc(GfGameParty::getHandleDriver(GfGameParty::getPartyId(4, blade), static_cast<PTPOS>(0)));
    if (acc.m_obj != nullptr && acc.isBattle()) {
        return false;
    }
    if (GfGameManager::isBattle()) {
        return false;
    }
    return GfGameCond::isGameCond(GfDataBlade::getSDataBlade(blade)->m_modelCondition);
}

void GfGameUtil::changeAlphaBelonging(GF_OBJ_HANDLE* handle, unsigned int slot, float alpha, float time) {
    GfWeapon* weapon = GfMountManager::getGfWeapon(handle, static_cast<GFATTACH>(2));
    if (weapon == nullptr) {
        return;
    }
    if (slot == 2) {
        SCOM_OBJ_ALPHA::create(weapon->getObjHandles()[1], time, alpha);
    } else if (slot == 1) {
        SCOM_OBJ_ALPHA::create(weapon->getObjHandles()[0], time, alpha);
    }
}

void GfGameUtilNanakoori::calcLevelAndFan() {
    GfDataNanakoori::setVocalLevel(
        GfDataNanakoori::getLevelForNanakoori(GfItemUtil::getItemBoxCount(GfDataNanakoori::getItemForVocalLevelUp())));
    GfDataNanakoori::setVisualLevel(
        GfDataNanakoori::getLevelForNanakoori(GfItemUtil::getItemBoxCount(GfDataNanakoori::getItemForVisualLevelUp())));
    GfDataNanakoori::setSoulLevel(
        GfDataNanakoori::getLevelForNanakoori(GfItemUtil::getItemBoxCount(GfDataNanakoori::getItemForSoulLevelUp())));
    unsigned int level =
        GfDataNanakoori::getSoulLevel() + GfDataNanakoori::getVisualLevel() + GfDataNanakoori::getVocalLevel();
    unsigned int mission = GfDataNanakoori::getClearMissionForSpecial() * 16 +
                           GfDataNanakoori::getClearMissionForLive() * 12 +
                           GfDataNanakoori::getClearMissionForLesson() * 3;
    GfDataNanakoori::setFan(mission * level);
}

unsigned int GfWeapon::getRscRight() const {
    const GfAppendInfo* info = GfObjUtil::getAppendInfo(getObjHandles()[0], static_cast<GFATTACH>(0));
    if (info == nullptr) {
        return 0;
    }
    const mm::mtl::FixedVector<GfAppend*, 10>& appends = info->m_appends[info->m_list];
    if (static_cast<int>(appends.size()) == 0) {
        return 0;
    }
    return appends[0]->getRscID();
}

unsigned int GfWeapon::getRscLeft() const {
    const GfAppendInfo* info = GfObjUtil::getAppendInfo(getObjHandles()[1], static_cast<GFATTACH>(0));
    if (info == nullptr) {
        return 0;
    }
    const mm::mtl::FixedVector<GfAppend*, 10>& appends = info->m_appends[info->m_list];
    if (static_cast<int>(appends.size()) == 0) {
        return 0;
    }
    return appends[0]->getRscID();
}

const char* GfGameUtil::getBladeModel(unsigned int blade, bool flag) {
    SDataBlade* data = GfDataBlade::getSDataBlade(blade);
    const char* name = fn_71002DEFBC(blade);
    if (name == nullptr) {
        name = data->m_modelName;
    }
    if (data->m_hasCondModel != 0 && !flag && isCondBladeModel(blade)) {
        name = data->m_condModelName;
    }
    return name;
}

const char* GfGameUtil::getAcceBladeModel(unsigned int blade) {
    return GfGameUtil::fn_71002DEFBC(blade);
}

const char* GfGameUtil::getBladeMotion(unsigned int blade, bool flag) {
    SDataBlade* data = GfDataBlade::getSDataBlade(blade);
    if (data->m_hasCondMotion != 0 && !flag && isCondBladeModel(blade)) {
        return data->m_condMotionName;
    }
    return data->m_motionName;
}

const char* fn_71002DF4C4(unsigned int driverId, bool flag) {
    GfBdatItem* bdat = mm::mtl::PtrSingleton<GfBdatItem>::sys();
    for (unsigned int slot = 0; slot < 3; slot++) {
        unsigned int acce = GfDataDriver::getEquipAcce(driverId, slot);
        if (acce == 0) {
            continue;
        }
        const char* name = bdat->getPcEquipModel(acce);
        if (name == nullptr || *name == '\0' || bdat->getPcEquipDriver(acce) != driverId) {
            continue;
        }
        if (flag && driverId == 6 && strcmp(name, "pc/pc110601") == 0) {
            return "pc/pc110602";
        }
        return name;
    }
    return nullptr;
}

bool GfGameUtil::getDriverAcceList(mm::mtl::FixedVector<unsigned short, 32>& list) {
    if (GfDataUtil::isIra()) {
        for (unsigned int driver = 17; driver < 26; ++driver) {
            if (GfDataDriver::isIraFront(driver)) {
                list.push_back(driver);
            }
        }
    } else {
        for (unsigned int driver = 1; driver < 9; ++driver) {
            if (driver == 5 && GfDataUtil::isVandammeDead()) {
                continue;
            }
            list.push_back(driver);
        }
    }
    return !list.empty();
}

void GfGameUtilShop::execPayInn(unsigned int shop, unsigned int money, bool twice) {
    GfBdatShop* bdat = mm::mtl::PtrSingleton<GfBdatShop>::sys();
    unsigned int point = money;
    if (bdat->getShopListShopType(shop) == 2) {
        point = bdat->getShopInnPrice(bdat->getShopListTableID(shop)) << twice;
    }
    SCOM_ADD_MONEY::create(-money);
    unsigned int zone = GfGameManager::getMapZoneID();
    float rate = QuestListAcc::get()->getFLD_DevelopmentLevelValue(1) / 10000.0f;
    SCOM_ADD_DEVELOP::create(zone, point * rate);
}

unsigned int GfGameUtilShop::getNeedMoneyForInn(unsigned int shop) {
    GfBdatShop* bdat = mm::mtl::PtrSingleton<GfBdatShop>::sys();
    if (bdat->getShopListShopType(shop) != 2) return 0;
    unsigned int price = bdat->getShopInnPrice(bdat->getShopListTableID(shop));
    if (int level = GfDataDevelop::getLevel(GfGameManager::getMapZoneID())) {
        price -= static_cast<unsigned int>(static_cast<float>(price) * bdat->getShopListDiscount(shop, level - 1) * 0.01f);
    }
    return price == 0 ? 1 : price;
}

RESULT_HANA GfGameUtilHana::openArtsCircuit(unsigned int hana, unsigned int circuit) {
    if (!GfDataHana::isValid(hana)) return static_cast<RESULT_HANA>(4);
    if (GfDataHana::isOpenCircuit(hana, circuit)) return static_cast<RESULT_HANA>(1);
    unsigned int ether = GfDataHana::getOpenCircuitEther(hana, circuit);
    if (ether == 0) return static_cast<RESULT_HANA>(2);
    if (ether > static_cast<unsigned int>(GfDataHana::getEther())) return static_cast<RESULT_HANA>(3);
    GfDataHana::setEther(GfDataHana::getEther() - ether);
    GfDataHana::setOpenCircuit(hana, circuit, true);
    return static_cast<RESULT_HANA>(0);
}

RESULT_HANA GfGameUtilHana::openCondenserCircuit(unsigned int hana, unsigned int circuit) {
    if (!GfDataHana::isValid(hana)) return static_cast<RESULT_HANA>(4);
    if (GfDataHana::isOpenCircuit(hana, circuit + 3)) return static_cast<RESULT_HANA>(1);
    unsigned int ether = GfDataHana::getOpenCircuitEther(hana, circuit + 3);
    if (ether == 0) return static_cast<RESULT_HANA>(2);
    if (ether > static_cast<unsigned int>(GfDataHana::getEther())) return static_cast<RESULT_HANA>(3);
    GfDataHana::setEther(GfDataHana::getEther() - ether);
    GfDataHana::setOpenCircuit(hana, circuit + 3, true);
    return static_cast<RESULT_HANA>(0);
}

RESULT_HANA GfGameUtilHana::exchangeRoleParts(unsigned int item) {
    if (getEmptyParts(item) == 0) return static_cast<RESULT_HANA>(7);
    unsigned int ether = GfDataHana::getNeedRolePartsEther(item);
    if (static_cast<unsigned int>(GfDataHana::getEther()) < ether) return static_cast<RESULT_HANA>(3);
    GfGameUtil::addEther(-static_cast<int>(ether));
    GfItemUtil::addItemBox(item, 1);
    return static_cast<RESULT_HANA>(0);
}

RESULT_HANA GfGameUtilHana::isExchangeRoleParts(unsigned int item) {
    if (getEmptyParts(item) == 0) return static_cast<RESULT_HANA>(7);
    unsigned int ether = GfDataHana::getNeedRolePartsEther(item);
    return static_cast<RESULT_HANA>(static_cast<unsigned int>(GfDataHana::getEther()) < ether ? 3 : 0);
}

RESULT_HANA GfGameUtilHana::exchangeAttributeParts(unsigned int item) {
    if (getEmptyParts(item) == 0) return static_cast<RESULT_HANA>(7);
    unsigned int ether = GfDataHana::getNeedAttributePartsEther(item);
    if (static_cast<unsigned int>(GfDataHana::getEther()) < ether) return static_cast<RESULT_HANA>(3);
    GfGameUtil::addEther(-static_cast<int>(ether));
    GfItemUtil::addItemBox(item, 1);
    return static_cast<RESULT_HANA>(0);
}

RESULT_HANA GfGameUtilHana::isExchangeAttributeParts(unsigned int item) {
    if (getEmptyParts(item) == 0) return static_cast<RESULT_HANA>(7);
    unsigned int ether = GfDataHana::getNeedAttributePartsEther(item);
    return static_cast<RESULT_HANA>(static_cast<unsigned int>(GfDataHana::getEther()) < ether ? 3 : 0);
}

RESULT_HANA GfGameUtilHana::exchangeArtsParts(unsigned int item) {
    if (getEmptyParts(item) == 0) return static_cast<RESULT_HANA>(7);
    unsigned int ether = GfDataHana::getNeedArtsPartsEther(item);
    if (static_cast<unsigned int>(GfDataHana::getEther()) < ether) return static_cast<RESULT_HANA>(3);
    GfGameUtil::addEther(-static_cast<int>(ether));
    GfItemUtil::addItemBox(item, 1);
    return static_cast<RESULT_HANA>(0);
}

RESULT_HANA GfGameUtilHana::isExchangeArtsParts(unsigned int item) {
    if (getEmptyParts(item) == 0) return static_cast<RESULT_HANA>(7);
    unsigned int ether = GfDataHana::getNeedArtsPartsEther(item);
    return static_cast<RESULT_HANA>(static_cast<unsigned int>(GfDataHana::getEther()) < ether ? 3 : 0);
}

RESULT_HANA GfGameUtilHana::exchangeNArtsParts(unsigned int item) {
    if (getEmptyParts(item) == 0) return static_cast<RESULT_HANA>(7);
    unsigned int ether = GfDataHana::getNeedNArtsPartsEther(item);
    if (static_cast<unsigned int>(GfDataHana::getEther()) < ether) return static_cast<RESULT_HANA>(3);
    GfGameUtil::addEther(-static_cast<int>(ether));
    GfItemUtil::addItemBox(item, 1);
    return static_cast<RESULT_HANA>(0);
}

RESULT_HANA GfGameUtilHana::isExchangeNArtsParts(unsigned int item) {
    if (getEmptyParts(item) == 0) return static_cast<RESULT_HANA>(7);
    unsigned int ether = GfDataHana::getNeedNArtsPartsEther(item);
    return static_cast<RESULT_HANA>(static_cast<unsigned int>(GfDataHana::getEther()) < ether ? 3 : 0);
}

RESULT_HANA GfGameUtilHana::exchangeCondenserParts(unsigned int item) {
    if (getEmptyParts(item) == 0) return static_cast<RESULT_HANA>(7);
    unsigned int ether = GfDataHana::getNeedCondenserPartsEther(item);
    if (static_cast<unsigned int>(GfDataHana::getEther()) < ether) return static_cast<RESULT_HANA>(3);
    GfGameUtil::addEther(-static_cast<int>(ether));
    GfItemUtil::addItemBox(item, 1);
    return static_cast<RESULT_HANA>(0);
}

RESULT_HANA GfGameUtilHana::isExchangeCondenserParts(unsigned int item) {
    if (getEmptyParts(item) == 0) return static_cast<RESULT_HANA>(7);
    unsigned int ether = GfDataHana::getNeedCondenserPartsEther(item);
    return static_cast<RESULT_HANA>(static_cast<unsigned int>(GfDataHana::getEther()) < ether ? 3 : 0);
}

RESULT_HANA GfGameUtilHana::isEnableEquipRoleParts(unsigned int hana, unsigned int item) {
    if (!GfDataHana::isValid(hana)) return static_cast<RESULT_HANA>(4);
    if (!GfDataHana::isEquipRoleParts(hana, item)) return static_cast<RESULT_HANA>(12);
    if (GfItemUtil::getItemBoxCount(item) == 0) return static_cast<RESULT_HANA>(8);
    GfItemHandle handle = GfItemUtil::getNoEquipItemHandle(item);
    if (handle.m_handle == 0) return static_cast<RESULT_HANA>(9);
    EquipHana equip = *GfDataHana::getEquipParts(hana);
    equip.m_roleParts = item;
    equip.m_roleHandle = handle.m_handle;
    if (!GfDataHana::isValid(hana)) return static_cast<RESULT_HANA>(4);
    unsigned int power = GfDataHana::getEquipPower(equip);
    return static_cast<RESULT_HANA>(static_cast<unsigned int>(GfDataHana::getPowerCapacity(hana)) < power ? 5 : 0);
}

RESULT_HANA GfGameUtilHana::execEquipRoleParts(unsigned int hana, unsigned int item, GfItemHandle handle) {
    if (!GfDataHana::isValid(hana)) return static_cast<RESULT_HANA>(4);
    if (item == 0) return static_cast<RESULT_HANA>(11);
    EquipHana equip = *GfDataHana::getEquipParts(hana);
    unsigned int oldItem = equip.m_roleParts;
    unsigned int oldHandle = equip.m_roleHandle;
    if (GfItemUtil::getItemBoxCount(item) == 0) return static_cast<RESULT_HANA>(8);
    if (handle.m_handle == 0) {
        handle = GfItemUtil::getNoEquipItemHandle(item);
        if (handle.m_handle == 0) return static_cast<RESULT_HANA>(9);
    }
    equip.m_roleParts = item;
    equip.m_roleHandle = handle.m_handle;
    if (GfDataHana::isValid(hana)) {
        unsigned int power = GfDataHana::getEquipPower(equip);
        if (static_cast<unsigned int>(GfDataHana::getPowerCapacity(hana)) < power) return static_cast<RESULT_HANA>(5);
    }
    GfItemUtil::setEquipFlag(item, handle, true);
    if (oldItem != 0) {
        if (oldHandle != 0) {
            GfItemHandle old;
            old.m_handle = oldHandle;
            GfItemUtil::setEquipFlag(oldItem, old, false);
        } else {
            GfItemUtil::addItemBox(oldItem, 1);
        }
    }
    GfDataHana::setEquipParts(hana, equip);
    return static_cast<RESULT_HANA>(0);
}

RESULT_HANA GfGameUtilHana::isEnableEquipAttributeParts(unsigned int hana, unsigned int item) {
    if (!GfDataHana::isValid(hana)) return static_cast<RESULT_HANA>(4);
    if (!GfDataHana::isEquipAttributeParts(hana, item)) return static_cast<RESULT_HANA>(12);
    if (GfItemUtil::getItemBoxCount(item) == 0) return static_cast<RESULT_HANA>(8);
    GfItemHandle handle = GfItemUtil::getNoEquipItemHandle(item);
    if (handle.m_handle == 0) return static_cast<RESULT_HANA>(9);
    EquipHana equip = *GfDataHana::getEquipParts(hana);
    equip.m_attributeParts = item;
    equip.m_attributeHandle = handle.m_handle;
    if (!GfDataHana::isValid(hana)) return static_cast<RESULT_HANA>(4);
    unsigned int power = GfDataHana::getEquipPower(equip);
    return static_cast<RESULT_HANA>(static_cast<unsigned int>(GfDataHana::getPowerCapacity(hana)) < power ? 5 : 0);
}

RESULT_HANA GfGameUtilHana::execEquipAttributeParts(unsigned int hana, unsigned int item, GfItemHandle handle) {
    if (!GfDataHana::isValid(hana)) return static_cast<RESULT_HANA>(4);
    if (item == 0) return static_cast<RESULT_HANA>(11);
    EquipHana equip = *GfDataHana::getEquipParts(hana);
    unsigned int oldItem = equip.m_attributeParts;
    unsigned int oldHandle = equip.m_attributeHandle;
    if (GfItemUtil::getItemBoxCount(item) == 0) return static_cast<RESULT_HANA>(8);
    if (handle.m_handle == 0) {
        handle = GfItemUtil::getNoEquipItemHandle(item);
        if (handle.m_handle == 0) return static_cast<RESULT_HANA>(9);
    }
    equip.m_attributeParts = item;
    equip.m_attributeHandle = handle.m_handle;
    if (GfDataHana::isValid(hana)) {
        unsigned int power = GfDataHana::getEquipPower(equip);
        if (static_cast<unsigned int>(GfDataHana::getPowerCapacity(hana)) < power) return static_cast<RESULT_HANA>(5);
    }
    GfItemUtil::setEquipFlag(item, handle, true);
    if (oldItem != 0) {
        if (oldHandle != 0) {
            GfItemHandle old;
            old.m_handle = oldHandle;
            GfItemUtil::setEquipFlag(oldItem, old, false);
        } else {
            GfItemUtil::addItemBox(oldItem, 1);
        }
    }
    GfDataHana::setEquipParts(hana, equip);
    return static_cast<RESULT_HANA>(0);
}

RESULT_HANA GfGameUtilHana::isEnableEquipCondenserParts(unsigned int hana, unsigned int item, unsigned int slot) {
    if (!GfDataHana::isValid(hana)) return static_cast<RESULT_HANA>(4);
    if (!GfDataHana::isEquipCondenserParts(hana, item)) return static_cast<RESULT_HANA>(12);
    if (GfDataHana::isExistSameEffectCondenserParts(hana, item, slot, false)) return static_cast<RESULT_HANA>(13);
    if (GfItemUtil::getItemBoxCount(item) == 0) return static_cast<RESULT_HANA>(8);
    GfItemHandle handle = GfItemUtil::getNoEquipItemHandle(item);
    if (handle.m_handle == 0) return static_cast<RESULT_HANA>(9);
    EquipHana equip = *GfDataHana::getEquipParts(hana);
    equip.setCondenserParts(item, handle.m_handle, slot);
    if (!GfDataHana::isValid(hana)) return static_cast<RESULT_HANA>(4);
    unsigned int power = GfDataHana::getEquipPower(equip);
    return static_cast<RESULT_HANA>(static_cast<unsigned int>(GfDataHana::getPowerCapacity(hana)) < power ? 5 : 0);
}

RESULT_HANA GfGameUtilHana::isEnableEquipExtendCondenserParts(unsigned int hana, unsigned int item, unsigned int slot) {
    if (!GfDataHana::isValid(hana)) return static_cast<RESULT_HANA>(4);
    if (!GfDataHana::isEquipCondenserParts(hana, item)) return static_cast<RESULT_HANA>(12);
    if (GfDataHana::isExistSameEffectCondenserParts(hana, item, slot, true)) return static_cast<RESULT_HANA>(13);
    if (GfItemUtil::getItemBoxCount(item) == 0) return static_cast<RESULT_HANA>(8);
    GfItemHandle handle = GfItemUtil::getNoEquipItemHandle(item);
    if (handle.m_handle == 0) return static_cast<RESULT_HANA>(9);
    EquipHana equip = *GfDataHana::getEquipParts(hana);
    equip.setExtendCondenserParts(item, handle.m_handle, slot);
    if (!GfDataHana::isValid(hana)) return static_cast<RESULT_HANA>(4);
    unsigned int power = GfDataHana::getEquipPower(equip);
    return static_cast<RESULT_HANA>(static_cast<unsigned int>(GfDataHana::getPowerCapacity(hana)) < power ? 5 : 0);
}

RESULT_HANA GfGameUtilHana::isEnableEquipArtsParts(unsigned int hana, unsigned int item, unsigned int slot) {
    if (!GfDataHana::isValid(hana)) return static_cast<RESULT_HANA>(4);
    if (!GfDataHana::isEquipArtsParts(hana, item)) return static_cast<RESULT_HANA>(12);
    if (GfItemUtil::getItemBoxCount(item) == 0) return static_cast<RESULT_HANA>(8);
    GfItemHandle handle = GfItemUtil::getNoEquipItemHandle(item);
    if (handle.m_handle == 0) return static_cast<RESULT_HANA>(9);
    EquipHana equip = *GfDataHana::getEquipParts(hana);
    equip.setArtsParts(item, handle.m_handle, slot);
    if (!GfDataHana::isValid(hana)) return static_cast<RESULT_HANA>(4);
    unsigned int power = GfDataHana::getEquipPower(equip);
    return static_cast<RESULT_HANA>(static_cast<unsigned int>(GfDataHana::getPowerCapacity(hana)) < power ? 5 : 0);
}

RESULT_HANA GfGameUtilHana::isEnableEquipNArtsParts(unsigned int hana, unsigned int item, unsigned int slot) {
    if (!GfDataHana::isValid(hana)) return static_cast<RESULT_HANA>(4);
    if (!GfDataHana::isEquipNArtsParts(hana, item)) return static_cast<RESULT_HANA>(12);
    if (GfItemUtil::getItemBoxCount(item) == 0) return static_cast<RESULT_HANA>(8);
    GfItemHandle handle = GfItemUtil::getNoEquipItemHandle(item);
    if (handle.m_handle == 0) return static_cast<RESULT_HANA>(9);
    if (GfDataHana::isExistSameEffectNArtsParts(hana, item, slot)) return static_cast<RESULT_HANA>(13);
    EquipHana equip = *GfDataHana::getEquipParts(hana);
    equip.setNArtsParts(item, handle.m_handle, slot);
    if (!GfDataHana::isValid(hana)) return static_cast<RESULT_HANA>(4);
    unsigned int power = GfDataHana::getEquipPower(equip);
    return static_cast<RESULT_HANA>(static_cast<unsigned int>(GfDataHana::getPowerCapacity(hana)) < power ? 5 : 0);
}

RESULT_HANA GfGameUtilHana::execEquipArtsParts(unsigned int hana, unsigned int item, GfItemHandle handle,
                                                unsigned int slot) {
    if (!GfDataHana::isValid(hana)) return static_cast<RESULT_HANA>(4);
    EquipHana equip = *GfDataHana::getEquipParts(hana);
    unsigned int oldItem = equip.m_artsParts[slot].m_item;
    unsigned int oldHandle = equip.m_artsParts[slot].m_handle;
    if (item != 0) {
        if (GfItemUtil::getItemBoxCount(item) == 0) return static_cast<RESULT_HANA>(8);
        if (handle.m_handle == 0) {
            handle = GfItemUtil::getNoEquipItemHandle(item);
            if (handle.m_handle == 0) return static_cast<RESULT_HANA>(9);
        }
    }
    equip.setArtsParts(item, handle.m_handle, slot);
    if (GfDataHana::isValid(hana)) {
        unsigned int power = GfDataHana::getEquipPower(equip);
        if (static_cast<unsigned int>(GfDataHana::getPowerCapacity(hana)) < power) return static_cast<RESULT_HANA>(5);
    }
    if (item != 0) {
        GfItemUtil::setEquipFlag(item, handle, true);
    }
    if (oldItem != 0) {
        if (oldHandle != 0) {
            GfItemHandle old;
            old.m_handle = oldHandle;
            GfItemUtil::setEquipFlag(oldItem, old, false);
        } else {
            GfItemUtil::addItemBox(oldItem, 1);
        }
    }
    GfDataHana::setEquipParts(hana, equip);
    return static_cast<RESULT_HANA>(0);
}

RESULT_HANA GfGameUtilHana::execEquipNArtsParts(unsigned int hana, unsigned int item, GfItemHandle handle,
                                                unsigned int slot) {
    if (!GfDataHana::isValid(hana)) return static_cast<RESULT_HANA>(4);
    EquipHana equip = *GfDataHana::getEquipParts(hana);
    unsigned int oldItem = equip.m_nArtsParts[slot].m_item;
    unsigned int oldHandle = equip.m_nArtsParts[slot].m_handle;
    if (item != 0) {
        if (GfItemUtil::getItemBoxCount(item) == 0) return static_cast<RESULT_HANA>(8);
        if (handle.m_handle == 0) {
            handle = GfItemUtil::getNoEquipItemHandle(item);
            if (handle.m_handle == 0) return static_cast<RESULT_HANA>(9);
        }
    }
    equip.setNArtsParts(item, handle.m_handle, slot);
    if (GfDataHana::isValid(hana)) {
        unsigned int power = GfDataHana::getEquipPower(equip);
        if (static_cast<unsigned int>(GfDataHana::getPowerCapacity(hana)) < power) return static_cast<RESULT_HANA>(5);
    }
    if (item != 0) {
        GfItemUtil::setEquipFlag(item, handle, true);
    }
    if (oldItem != 0) {
        if (oldHandle != 0) {
            GfItemHandle old;
            old.m_handle = oldHandle;
            GfItemUtil::setEquipFlag(oldItem, old, false);
        } else {
            GfItemUtil::addItemBox(oldItem, 1);
        }
    }
    GfDataHana::setEquipParts(hana, equip);
    return static_cast<RESULT_HANA>(0);
}

RESULT_HANA GfGameUtilHana::execEquipCondenserParts(unsigned int hana, unsigned int item, GfItemHandle handle,
                                                unsigned int slot) {
    if (!GfDataHana::isValid(hana)) return static_cast<RESULT_HANA>(4);
    EquipHana equip = *GfDataHana::getEquipParts(hana);
    unsigned int oldItem = equip.m_condenserParts[slot];
    unsigned int oldHandle = equip.m_condenserHandles[slot];
    if (item != 0) {
        if (GfItemUtil::getItemBoxCount(item) == 0) return static_cast<RESULT_HANA>(8);
        if (handle.m_handle == 0) {
            handle = GfItemUtil::getNoEquipItemHandle(item);
            if (handle.m_handle == 0) return static_cast<RESULT_HANA>(9);
        }
    }
    equip.setCondenserParts(item, handle.m_handle, slot);
    if (GfDataHana::isValid(hana)) {
        unsigned int power = GfDataHana::getEquipPower(equip);
        if (static_cast<unsigned int>(GfDataHana::getPowerCapacity(hana)) < power) return static_cast<RESULT_HANA>(5);
    }
    if (item != 0) {
        GfItemUtil::setEquipFlag(item, handle, true);
    }
    if (oldItem != 0) {
        if (oldHandle != 0) {
            GfItemHandle old;
            old.m_handle = oldHandle;
            GfItemUtil::setEquipFlag(oldItem, old, false);
        } else {
            GfItemUtil::addItemBox(oldItem, 1);
        }
    }
    GfDataHana::setEquipParts(hana, equip);
    GfEvent::callHanaCondenser(hana, false, slot);
    return static_cast<RESULT_HANA>(0);
}

RESULT_HANA GfGameUtilHana::execPowerRankup(unsigned int hana, unsigned int rank) {
    if (!GfDataHana::isValid(hana)) return static_cast<RESULT_HANA>(4);
    unsigned int now = GfDataHana::getEquipPowerRank(hana);
    unsigned int ether = GfDataHana::getEther();
    if (now < rank) {
        GfBdatBtl* bdat = mm::mtl::PtrSingleton<GfBdatBtl>::sys();
        // the power rank goes up to 20
        do {
            now++;
            unsigned int need = bdat->getBTL_HanaPowerEtherNum(now, hana - 1005);
            if (ether < need) return static_cast<RESULT_HANA>(3);
            ether -= need;
            if (now == rank) {
                GfDataHana::setEquipPowerRank(hana, rank);
                GfDataHana::setEther(ether);
                return static_cast<RESULT_HANA>(0);
            }
        } while (now < 20);
    }
    return static_cast<RESULT_HANA>(6);
}

RESULT_HANA GfGameUtilHana::isExecPowerRankup(unsigned int hana, unsigned int rank) {
    if (!GfDataHana::isValid(hana)) return static_cast<RESULT_HANA>(4);
    unsigned int now = GfDataHana::getEquipPowerRank(hana);
    unsigned int ether = GfDataHana::getEther();
    if (now < rank) {
        GfBdatBtl* bdat = mm::mtl::PtrSingleton<GfBdatBtl>::sys();
        // the power rank goes up to 20
        do {
            now++;
            unsigned int need = bdat->getBTL_HanaPowerEtherNum(now, hana - 1005);
            if (ether < need) return static_cast<RESULT_HANA>(3);
            ether -= need;
            if (now == rank) {
                return static_cast<RESULT_HANA>(0);
            }
        } while (now < 20);
    }
    return static_cast<RESULT_HANA>(6);
}

}  // namespace gf

namespace gf {

// inline: the option data in use (tl::TitleMain's in advertize or theater mode, else GfDataManager's); the name is
// not the original's
static inline SDataOption* getActiveOptionData() {
    if (GfManager::isExecModeAdvertize() || GfManager::isExecModeThater()) {
        if (tl::TitleMain* title = mm::mtl::PtrSingleton<tl::TitleMain>::sys()) {
            return &title->getOptionBuffer();
        }
    }
    return GfDataManager::getDataOption();
}

bool fn_71002EE5E0(QuestID quest, unsigned int task) {
    if (quest.m_id == 0x8FD) {
        return true;
    }
    QuestTaskParam param(quest, task, static_cast<TASK_STATE>(0));
    return quest.m_id == 0x80B && task == 1;
}

void fn_71002EE640(unsigned int blade) {
    if (!GfGameManager::isGameTypeIra() || GfDataBlade::getTrustRank(blade) != 5) {
        return;
    }
    if (GfDataBlade::getKizunaringMax(blade) > GfDataBlade::getKizunaringCompleteNum(blade)) {
        return;
    }
    GfDataBlade::getSDataBlade(blade)->m_kizunaringComplete = 0;
    GfGameUtil::addTrustRankForKizunaRing(blade);
    GfQuestReward reward;
    if (GfKizunaringUtil::getCompleteKizunaringReward(reward, blade)) {
        GfQuestUtil::execReward(reward);
    }
}

bool fn_71002EE72C(unsigned int blade) {
    if (!GfGameManager::isGameTypeIra() || GfDataBlade::getTrustRank(blade) != 5) {
        return false;
    }
    return GfDataBlade::getKizunaringMax(blade) == GfDataBlade::getKizunaringCompleteNum(blade);
}

void GfGameUtilSaveData::setupOptionSaveData(SDataOption& option) {
    option = *GfDataManager::getDataOption();
    if (GfSound* sound = mm::mtl::PtrSingleton<GfSound>::sys()) {
        option.m_soundUi.m_volume[0] = GfMasterVolume::getU16Volume(sound->m_masterVolume.m_eventVoiceVolume);
        option.m_soundUi.m_volume[1] = GfMasterVolume::getU16Volume(sound->m_masterVolume.m_eventCsVolume);
        option.m_soundUi.m_volume[2] = GfMasterVolume::getU16Volume(sound->m_masterVolume.m_eventBgmVolume);
        option.m_soundUi.m_volume[3] = GfMasterVolume::getU16Volume(sound->m_masterVolume.m_eventSeVolume);
        option.m_soundUi.m_volume[4] = GfMasterVolume::getU16Volume(sound->m_masterVolume.m_gameBgmVolume);
        option.m_soundUi.m_volume[5] = GfMasterVolume::getU16Volume(sound->m_masterVolume.m_gameEnvVolume);
        option.m_soundUi.m_volume[6] = GfMasterVolume::getU16Volume(sound->m_masterVolume.m_gameWeatherVolume);
        option.m_soundUi.m_volume[7] = GfMasterVolume::getU16Volume(sound->m_masterVolume.m_gameSeVolume);
        option.m_soundUi.m_volume[8] = GfMasterVolume::getU16Volume(sound->m_masterVolume.m_playerVoiceVolume);
        option.m_soundUi.m_volume[9] = GfMasterVolume::getU16Volume(sound->m_masterVolume.m_enemyVoiceVolume);
        option.m_soundUi.m_volume[10] = GfMasterVolume::getU16Volume(sound->m_masterVolume.m_nareVoiceVolume);
        option.m_soundUi.m_volume[12] = GfMasterVolume::getU16Volume(sound->m_masterVolume.m_menuBgmVolume);
    }
    option.m_soundUi.m_langType = fw::LangUtil::getLangType();
}

SDataOption* GfGameUtilSaveData::getValidOptionData() {
    SDataOption* option = GfDataManager::getDataOption();
    if (GfManager::isExecModeThater() || GfManager::isExecModeAdvertize()) {
        if (tl::TitleMain* title = mm::mtl::PtrSingleton<tl::TitleMain>::sys()) {
            option = &title->getOptionBuffer();
        }
    }
    return option;
}

void GfGameUtilSaveData::flushOptionSaveData() {
    SDataOption* option = getValidOptionData();
    GfMenuManager::applyOptionData(*option);
    if (GfMenuManager::isEnableVoiceChange()) {
        fw::LangUtil::setVoiceType(static_cast<fw::LangType>(option->m_soundUi.m_byte1E == 0));
    }
    if (GfSound* sound = mm::mtl::PtrSingleton<GfSound>::sys()) {
        sound->setupGame();
    }
}

void GfGameUtilSaveData::getSaveDataMenuInfo(SaveMenuInfo& info) {
    SDataSaveIra* save;
    tl::TitleMain* title = mm::mtl::PtrSingleton<tl::TitleMain>::sys();
    if (title != nullptr && title->fn_710014FB00()->m_system.m_version == 0x3A15B) {
        save = title->getSaveBuffer();
    } else {
        save = GfGameSave::getIraGameSaveData();
    }
    fn_71002EAF78(info, save);
}

bool GfGameUtil::isDispSinMask() {
    if (GfGameManager::isGameTypeIra()) {
        return !GfGameCond::isGameCond(0xE86);
    }
    return GfDataUtil::getScenarioFlag() < 5048;
}

bool GfGameUtil::isDispLauraMedal() {
    unsigned short id = GfDataUtil::getScenarioFlag();
    return id >= 11100 && id <= 11130;
}

unsigned int GfGameUtilDiff::getBtlDifficult() {
    return getActiveOptionData()->m_soundUi.m_keyD;
}

unsigned int GfGameUtil::getWpnDamage(GF_OBJ_HANDLE* handle) {
    GfGameArena* arena = mm::mtl::PtrSingleton<GfGameArena>::sys();
    if (arena != nullptr && arena->isBattleNow()) {
        return arena->getWeaponDamage(handle);
    }
    DataParamAcc acc(handle);
    return acc.getWeaponDamage(false);
}

unsigned int GfGameUtil::getWpnStability(GF_OBJ_HANDLE* handle) {
    DataParamAcc acc(handle);
    return acc.getWeaponStability(false);
}

bool GfGameUtil::isEnableBladeElma() {
    if (!GfGameManager::isInstalledBattleArenaContents()) {
        return false;
    }
    if (GfItemUtil::getItemBoxCount(25497) == 0) {
        return false;
    }
    const ChBtlInfo& row = GfDataManager::getDataGame()->m_ruleTable.m_rows[25];
    return row.m_rules[1].m_value0 != 0 || row.m_rules[0].m_value0 != 0 || row.m_rules[2].m_value0 != 0 ||
           row.m_rules[3].m_value0 != 0 || row.m_rules[4].m_value0 != 0;
}

// whether the add-on content state (GfGameAoc) owns the encoded add-on item id, false without it (as
// GfGameManager::isInstalledBattleArenaContents does for 0x30101). Inline: no copy exists; GfGameUtil::isEnableBladeDlc's 0x451 case needs it as a
// call of its own to keep the original's block order. The name is not the original's.
static inline bool isAocOwned(unsigned int id) {
    if (GfGameAoc* aoc = GfGameAoc::get()) {
        return aoc->isExistGameAoc(GAMEAOC(id));
    }
    return false;
}

// blade 0x457's test, shared by GfGameUtil::isEnableBladeDlc and GfGameUtil::isEnableGameBlade (both inline it): GfGameManager::isInstalledBattleArenaContents,
// item 25497 in the box and a first rule value set in row 25 of SDataGame's challenge rule table (tested in the
// order 1, 0, 2, 3, 4). Inline: no copy exists. The name is not the original's.
static inline bool isBlade457Unlocked() {
    if (!GfGameManager::isInstalledBattleArenaContents()) {
        return false;
    }
    if (GfItemUtil::getItemBoxCount(25497) == 0) {
        return false;
    }
    const ChBtlInfo& row = GfDataManager::getDataGame()->m_ruleTable.m_rows[25];
    return row.m_rules[1].m_value0 != 0 || row.m_rules[0].m_value0 != 0 || row.m_rules[2].m_value0 != 0 ||
           row.m_rules[3].m_value0 != 0 || row.m_rules[4].m_value0 != 0;
}

bool GfGameUtil::isEnableBladeDlc(unsigned int blade) {
    switch (blade) {
    case 0x451:
        return isAocOwned(0x20101);
    case 0x452:
    case 0x453:
        return GfGameManager::isInstalledBattleArenaContents();
    case 0x457:
        return isBlade457Unlocked();
    default:
        return true;
    }
}

unsigned int GfGameUtil::getNamedListIndex(unsigned int enemy) {
    GfBdatChrEnArrange* bdat = mm::mtl::PtrSingleton<GfBdatChrEnArrange>::sys();
    if (GfGameManager::isGameTypeIra()) {
        for (unsigned int row = bdat->getBTL_NamedListIraStart(), end = bdat->getBTL_NamedListIraEnd(); row < end; row++) {
            if (bdat->getBTL_NamedListIraEnemyID(row) == enemy) {
                return row;
            }
        }
    } else {
        for (unsigned int row = bdat->getBTL_NamedListStart(), end = bdat->getBTL_NamedListEnd(); row < end; row++) {
            if (bdat->getBTL_NamedListEnemyID(row) == enemy) {
                return row;
            }
        }
    }
    return 0;
}

bool GfGameUtil::isDefeatNamed(unsigned int enemy, GFDIFF mode) {
    unsigned int row = GfGameUtil::getNamedListIndex(enemy);
    if (row == 0) {
        return false;
    }
    return (GfDataManager::getDataGame()->m_namedRecords[row].m_flags & (1 << mode)) != 0;
}

void GfGameUtil::setIraBoneMountR(GF_OBJ_HANDLE* handle, GF_OBJ_HANDLE* target, bool flag) {
    if (GfGameScene* scene = mm::mtl::PtrSingleton<GfGameScene>::sys()) {
        scene->setIraBoneMount(handle, target, flag, IRA_MOUNT(0));
    }
}

void GfGameUtil::setIraBoneMountL(GF_OBJ_HANDLE* handle, GF_OBJ_HANDLE* target, bool flag) {
    if (GfGameScene* scene = mm::mtl::PtrSingleton<GfGameScene>::sys()) {
        scene->setIraBoneMount(handle, target, flag, IRA_MOUNT(1));
    }
}

bool GfGameUtil::isEnableIraSatahiko() {
    if (GfDataManager::getDataGameIra()->m_word2 == 0) {
        return false;
    }
    return mm::mtl::PtrSingleton<GfBdatChrDr>::sys()->getIRA_PartyGuest1(GfDataManager::getDataGameIra()->m_word2) != 0;
}

bool GfGameUtil::isEnableIraMilto() {
    if (GfDataManager::getDataGameIra()->m_word2 == 0) {
        return false;
    }
    return mm::mtl::PtrSingleton<GfBdatChrDr>::sys()->getIRA_PartyGuest2(GfDataManager::getDataGameIra()->m_word2) != 0;
}

bool GfGameUtilDiff::isEnableAutoSave() {
    return getActiveOptionData()->m_soundUi.m_flagD != 0;
}

bool GfGameUtil::isEnableGameBlade(unsigned int blade) {
    switch (blade) {
    case 0x451:
    case 0x452:
    case 0x453:
        return GfGameUtil::isEnableBladeDlc(blade);
    case 0x454:
        return GfItemUtil::getItemBoxCount(25498) != 0;
    case 0x455:
        return GfItemUtil::getItemBoxCount(25499) != 0;
    case 0x457:
        return isBlade457Unlocked();
    default:
        return true;
    }
}

bool GfGameUtil::isNeedRetargetDriver(unsigned int driverId, bool createTypeIn2311, bool createType3) {
    if (driverId != 6) {
        return false;
    }
    const char* name = GfGameUtil::getDriverModel(6, createTypeIn2311, createType3);
    return name != nullptr && strstr(name, "pc110601") != nullptr;
}

bool GfGameUtil::isNeedRetargetDriverResource(const char* name) {
    return name != nullptr && strstr(name, "pc110601") != nullptr;
}

int GfGameUtil::getNeedRetargetDriverId(const char* name) {
    if (name == nullptr) {
        return 0;
    }
    return strstr(name, "pc110601") != nullptr ? 6 : 0;
}

bool GfGameUtil::isAdvancedGameOption() {
    SDataGame* game = GfDataManager::getDataGame();
    if (tl::TitleMain* title = mm::mtl::PtrSingleton<tl::TitleMain>::sys()) {
        if (GfManager::isExecModeAdvertize() || GfManager::isExecModeThater()) {
            game = &title->getSaveBuffer()->m_game;
        }
    }
    return ItemCountLowLevel::getCount(game->m_itemBox, game->m_itemBoxExtend, 25495) != 0;
}

bool GfGameUtil::isAdvancedDifficulity() {
    SDataGame* game = GfDataManager::getDataGame();
    if (tl::TitleMain* title = mm::mtl::PtrSingleton<tl::TitleMain>::sys()) {
        if (GfManager::isExecModeAdvertize() || GfManager::isExecModeThater()) {
            game = &title->getSaveBuffer()->m_game;
        }
    }
    return ItemCountLowLevel::getCount(game->m_itemBox, game->m_itemBoxExtend, 25496) != 0;
}

void GfGameUtil::playSeForPartySwitch() {
    GfMenuObjUtil::playSE(0x2E);
}

fw::SoundPack* GfGameUtil::getDlcSePack(const char* name) {
    if (GfFieldSound* sound = mm::mtl::PtrSingleton<GfFieldSound>::sys()) {
        return sound->getDlcSePack(name);
    }
    return nullptr;
}

const char* GfGameUtil::getDlcSeName(const char* name) {
    if (GfFieldSound* sound = mm::mtl::PtrSingleton<GfFieldSound>::sys()) {
        return sound->getDlcSeName(name);
    }
    return nullptr;
}

void* GfGameUtilDiff::getUseSoundUiOption() {
    return &getActiveOptionData()->m_soundUi;
}

void GfGameUtilDiff::getBtlDifParam(unsigned int value) {
    GfDataBtlDif::getBtlDifParam(getActiveOptionData()->m_soundUi, value);
}

void GfGameUtilDiff::setOptionGameDifficult(GFDIFF type) {
    GfDataBtlDif::setOptionGameDifficult(getActiveOptionData()->m_soundUi, type);
}

bool GfGameUtilDiff::isEnableSpecialBgm() {
    return getActiveOptionData()->m_soundUi.m_flagF == 0;
}

bool GfGameUtilDiff::isEnableAutoBattle() {
    return getActiveOptionData()->m_soundUi.m_flagA != 0;
}

bool GfGameUtilDiff::isEnableAutoButtonChallenge() {
    return getActiveOptionData()->m_soundUi.m_flagB != 0;
}

bool GfGameUtilDiff::isEnableEnemyAgg() {
    return getActiveOptionData()->m_soundUi.m_flagC != 0;
}

bool GfGameUtilDiff::isEnableHitonowaSkip() {
    return getActiveOptionData()->m_soundUi.m_flagE != 0;
}

void GfGameUtilDiff::setCustomFollow(SDataOption& option) {
    GfDataBtlDif::setCustomFollow(option.m_soundUi);
}
}  // namespace gf

template void mm::mtl::UniquePtr<gf::GfTargetProperty, mm::mtl::UniquePtrDefaultDeleter<gf::GfTargetProperty> >::_safe_bool_helper::safe_bool_function() const;

namespace gf {

// 2.0.0's symbols name it (the original reaches it through the GOT).
int GfBootUtil::s_bootType;

void GfBootUtil::execBootScriptWithMicroThread(unsigned int type, bool run) {
    if (run) {
        s_bootType = type;
        if (mm::mtl::PtrSingleton<GfScriptManager>::sys() != nullptr) {
            GfScriptManager::loadScript(0x46, "aoc_boot");
            while (!GfScriptManager::isScriptLoaded(0x46)) {
                if (GfScriptManager::isScriptLoadError(0x46)) {
                    break;
                }
                GfSleep(1);
            }
            if (GfScriptManager::isScriptLoaded(0x46) && !GfScriptManager::isScriptLoadError(0x46)) {
                GfScriptManager::startScript(0x46);
                while (GfScriptManager::isScriptActive(0x46)) {
                    GfSleep(1);
                }
            }
            GfScriptManager::destroyScript(0x46);
            s_bootType = 0;
        }
    }
}

int GfBootUtil::getBootType() {
    return s_bootType;
}

float GfGameUtilFieldEnhance::integrateAccessoriesEffect(unsigned int driver, unsigned short effect) {
    if (driver == 0) {
        return 0.0f;
    }
    mm::mtl::FixedVector<unsigned short, 64> enhances;
    if (!GfDataDriver::getEquipAcceEnahnce(enhances, driver)) {
        return 0.0f;
    }
    float sum = 0.0f;
    if (enhances.size() != 0) {
        GfBdatBtl* bdat = mm::mtl::PtrSingleton<GfBdatBtl>::sys();
        for (unsigned short id : enhances) {
            if (static_cast<unsigned short>(bdat->getBTL_EnhanceEnhanceEffect(id)) == effect) {
                sum += bdat->getBTL_EnhanceParam1(id);
            }
        }
    }
    return sum * 0.01f;
}

float GfGameUtilFieldEnhance::integrateOrbEffect(unsigned int driver, int blade, unsigned short effect) {
    float sum = 0.0f;
    if (driver == 0) {
        return sum;
    }
    unsigned int id = GfDataDriver::getBlade(driver, blade);
    if (id == 0) {
        return sum;
    }
    mm::mtl::FixedVector<unsigned short, 64> enhances;
    if (!GfDataBlade::getEquipOrbEnance(enhances, id)) {
        return 0.0f;
    }
    if (enhances.size() != 0) {
        GfBdatBtl* bdat = mm::mtl::PtrSingleton<GfBdatBtl>::sys();
        for (unsigned short id : enhances) {
            if (static_cast<unsigned short>(bdat->getBTL_EnhanceEnhanceEffect(id)) == effect) {
                sum += bdat->getBTL_EnhanceParam1(id);
            }
        }
    }
    return sum * 0.01f;
}

void fn_71002EEDC0(SDataGameSavedEvent& row, unsigned int event) {
    row.m_event = event;
    if (GfFieldTime* time = mm::mtl::PtrSingleton<GfFieldTime>::sys()) {
        row.m_time = time->getGameTime();
    }
    row.m_mapWeather = GfFieldWeather::getCurrentMapWeatherID(false);
    row.m_weather = GfFieldWeather::getCurrentWtrType(false);
    for (unsigned int i = 0; i < 9; i++) {
        DataParamAcc acc(3, i + 1, static_cast<GimmickType>(0));
        row.m_weapons[i] = acc.getEquipWeapon(-1, false);
        row.m_blades[i] = acc.getBlade(-1, false);
    }
}

}  // namespace gf

// the field locator vector's growth (its user is not written yet)
template void mm::mtl::Vector<gf::GfFieldLocator>::expand(size_t, size_t);
template void mm::mtl::Vector<gf::GfFieldLocator>::push_back(const gf::GfFieldLocator&);

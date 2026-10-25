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

namespace gf {

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

const char* GfGameUtil::getSalvageDriverModel(unsigned int driver) {
    if (driver == 1) {
        return GfGameCond::isGameCond(mm::mtl::PtrSingleton<GfBdatChrDr>::sys()->getChrDrCondition(1)) ? "pc/pc000104"
                                                                                                        : "pc/pc000102";
    }
    return "";
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
    unsigned short blade = GfDataBlade::fn_7100231884();
    return blade != 0 && !(blade >= 1001 && blade <= 1030);
}

bool GfGameUtil::isDispHomuraCrystal() {
    unsigned short blade = GfDataBlade::fn_7100231884();
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

void GfGameUtil::dispMetsuCrystal(GF_OBJ_HANDLE* handle, bool disp) {
    if (handle == reinterpret_cast<GF_OBJ_HANDLE*>(-1)) return;
    GfObjAcc acc(handle);
    int mesh = acc.getExtMeshIdx("Front_Armor");
    if (mesh >= 0) {
        acc.setExtMeshAlpha(mesh, disp ? 1.0f : 0.0f);
    }
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

void GfGameUtil::makeCommandBattle(mm::mtl::FixStr<32>& out, bool battle) {
    out = "C_";
    out += battle ? "btstart" : "btend";
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

void GfGameUtil::setTrustPointForDebug(unsigned int driver, unsigned int point) {
    addTrustPoint(GfDataBlade::fn_7100237B70(driver, -1), point);
}

bool GfGameUtil::execActivateMercenaryTeamForBlade(unsigned int blade) {
    if (GfDataBlade::fn_71002383C8(blade)) return false;
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
    GfDataBlade::fn_710024E8F4(GfGameManager::getMapID(), cloudSea);
    GfFieldWeather::setCloudSea(GfGameManager::getMapID(), cloudSea);
}

}  // namespace gf

namespace gf {

void GfGameUtil::incGameClearCount() {
    SDataGame* game = GfDataManager::getDataGame();
    GfDataBlade::fn_71002320AC(game, true);
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
    if (!GfGameManager::fn_71002AC580() && GfDataBlade::fn_7100234998(enemy) &&
        mm::mtl::PtrSingleton<GfBdatChrEnArrange>::sys()->isChrEnArrangeFlagNamed(enemy) &&
        GfDataBlade::fn_7100234940(enemy) == 1) {
        GfDataBlade::fn_71002355AC();
    }
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
    if (driver == 0 || GfDataDriver::fn_71002491D4(driver)) {
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

}  // namespace gf

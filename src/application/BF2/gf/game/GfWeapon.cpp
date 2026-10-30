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

const char* fn_71002DF624(unsigned int driverId, bool check, bool flag) {
    if (check && driverId == 6) {
        flag = flag | GfDataEvent::fn_710024F910(GfGameEvent::fn_71002A0FEC());
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

void GfGameUtil::fn_71002DF8B0(GF_OBJ_HANDLE*& handle) {
    DataParamAcc acc(handle);
    if (GfObjUtil::isValid(handle) && acc.getObjType() == 3 &&
        GfDataDriver::fn_710023F9A8(acc.isValid() && acc.getObjType() == 3 ? acc.getBdatId() : 0)) {
        mm::mtl::FixedVector<unsigned short, 32> drivers;
        drivers.push_back(GfDataDriver::fn_71002417DC(acc.isValid() && acc.getObjType() == 3 ? acc.getBdatId() : 0));
        GfDataDriver::fn_71002416B4(drivers, acc.isValid() && acc.getObjType() == 3 ? acc.getBdatId() : 0);
        unsigned long num = drivers.size();
        for (unsigned long i = 0; i < num; i++) {
            GF_OBJ_HANDLE* driver = GfGameParty::getHandleDriverByBdatID(drivers.begin()[i]);
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
    if (GfDataDriver::fn_710023F9A8(GfDataBlade::fn_7100236518(blade))) {
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

bool GfGameUtil::fn_71002E16F4(unsigned int driver) {
    if (GfDataDriver::fn_7100241DD4(driver)) {
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
    GfObjAcc acc(GfGameParty::getHandleDriver(GfGameParty::getPartyId(4, blade), 0));
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

const char* fn_71002DF344(unsigned int blade) {
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
        const char* name = bdat->fn_7100203698(acce);
        if (name == nullptr || *name == '\0' || bdat->fn_7100203610(acce) != driverId) {
            continue;
        }
        if (flag && driverId == 6 && strcmp(name, "pc/pc110601") == 0) {
            return "pc/pc110602";
        }
        return name;
    }
    return nullptr;
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

RESULT_HANA GfGameUtilHana::isExchangeRoleParts(unsigned int item) {
    if (getEmptyParts(item) == 0) return static_cast<RESULT_HANA>(7);
    unsigned int ether = GfDataHana::getNeedRolePartsEther(item);
    return static_cast<RESULT_HANA>(static_cast<unsigned int>(GfDataHana::getEther()) < ether ? 3 : 0);
}

RESULT_HANA GfGameUtilHana::isExchangeAttributeParts(unsigned int item) {
    if (getEmptyParts(item) == 0) return static_cast<RESULT_HANA>(7);
    unsigned int ether = GfDataHana::getNeedAttributePartsEther(item);
    return static_cast<RESULT_HANA>(static_cast<unsigned int>(GfDataHana::getEther()) < ether ? 3 : 0);
}

RESULT_HANA GfGameUtilHana::isExchangeArtsParts(unsigned int item) {
    if (getEmptyParts(item) == 0) return static_cast<RESULT_HANA>(7);
    unsigned int ether = GfDataHana::getNeedArtsPartsEther(item);
    return static_cast<RESULT_HANA>(static_cast<unsigned int>(GfDataHana::getEther()) < ether ? 3 : 0);
}

RESULT_HANA GfGameUtilHana::isExchangeNArtsParts(unsigned int item) {
    if (getEmptyParts(item) == 0) return static_cast<RESULT_HANA>(7);
    unsigned int ether = GfDataHana::getNeedNArtsPartsEther(item);
    return static_cast<RESULT_HANA>(static_cast<unsigned int>(GfDataHana::getEther()) < ether ? 3 : 0);
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
    GfEvent::fn_71003286B0(hana, false, slot);
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
            return title->getOptionBuffer();
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

bool fn_71002EE72C(unsigned int blade) {
    if (!GfGameManager::fn_71002A9E68() || GfDataBlade::getTrustRank(blade) != 5) {
        return false;
    }
    return GfDataBlade::getKizunaringMax(blade) == GfDataBlade::getKizunaringCompleteNum(blade);
}

bool fn_71002EB3C0() {
    if (GfGameManager::fn_71002A9E68()) {
        return !GfGameCond::isGameCond(0xE86);
    }
    return GfDataBlade::fn_7100231884() < 5048;
}

bool fn_71002EB3FC() {
    unsigned short id = GfDataBlade::fn_7100231884();
    return id >= 11100 && id <= 11130;
}

unsigned int fn_71002EC634() {
    return getActiveOptionData()->m_soundUi.m_keyD;
}

unsigned int fn_71002EC6F4(GF_OBJ_HANDLE* handle) {
    DataParamAcc acc(handle);
    return acc.getWeaponStability(false);
}

unsigned int fn_71002ED4F0(unsigned int enemy) {
    GfBdatChrEnArrange* bdat = mm::mtl::PtrSingleton<GfBdatChrEnArrange>::sys();
    if (GfGameManager::fn_71002A9E68()) {
        for (unsigned int row = bdat->fn_71001F4E70(), end = bdat->fn_71001F4E7C(); row < end; row++) {
            if (bdat->fn_71001F4EB8(row) == enemy) {
                return row;
            }
        }
    } else {
        for (unsigned int row = bdat->fn_71001F4DA0(), end = bdat->fn_71001F4DAC(); row < end; row++) {
            if (bdat->fn_71001F4DE8(row) == enemy) {
                return row;
            }
        }
    }
    return 0;
}

bool fn_71002ED5B0(unsigned int enemy, unsigned int mode) {
    unsigned int row = fn_71002ED4F0(enemy);
    if (row == 0) {
        return false;
    }
    return (GfDataManager::getDataGame()->m_namedRecords[row].m_flags & (1 << mode)) != 0;
}

bool fn_71002EDA8C() {
    return getActiveOptionData()->m_soundUi.m_flagD != 0;
}

bool fn_71002EDBD8(unsigned int driverId, bool createTypeIn2311, bool createType3) {
    if (driverId != 6) {
        return false;
    }
    const char* name = fn_71002DF39C(6, createTypeIn2311, createType3);
    return name != nullptr && strstr(name, "pc110601") != nullptr;
}

bool fn_71002EDC24(const char* name) {
    return name != nullptr && strstr(name, "pc110601") != nullptr;
}

int fn_71002EDC4C(const char* name) {
    if (name == nullptr) {
        return 0;
    }
    return strstr(name, "pc110601") != nullptr ? 6 : 0;
}

void fn_71002EDD60() {
    GfMenuObjUtil::playSE(0x2E);
}

fw::SoundPack* fn_71002EE5A0(const char* name) {
    if (GfFieldSound* sound = mm::mtl::PtrSingleton<GfFieldSound>::sys()) {
        return sound->fn_710027CE60(name);
    }
    return nullptr;
}

const char* fn_71002EE5C0(const char* name) {
    if (GfFieldSound* sound = mm::mtl::PtrSingleton<GfFieldSound>::sys()) {
        return sound->fn_710027CEA4(name);
    }
    return nullptr;
}

void* fn_71002EE8C4() {
    return &getActiveOptionData()->m_soundUi;
}

void fn_71002EE904(unsigned int value) {
    fn_7100254FDC(&getActiveOptionData()->m_soundUi, value);
}

void fn_71002EE954(unsigned int type) {
    fn_7100254EF0(&getActiveOptionData()->m_soundUi, type);
}

bool fn_71002EE9A4() {
    return getActiveOptionData()->m_soundUi.m_flagF == 0;
}

bool fn_71002EE9EC() {
    return getActiveOptionData()->m_soundUi.m_flagA != 0;
}

bool fn_71002EEA34() {
    return getActiveOptionData()->m_soundUi.m_flagB != 0;
}

bool fn_71002EEA7C() {
    return getActiveOptionData()->m_soundUi.m_flagC != 0;
}

bool fn_71002EEAC4() {
    return getActiveOptionData()->m_soundUi.m_flagE != 0;
}

void SDataOption::fn_71002EEB0C() {
    fn_7100254DF0(&m_soundUi);
}

// Proposed name, not the original's: the symbols leave it unnamed (lbl_7100EA4890). Not static: the original
// reaches it through the GOT.
int g_bootType;

void fn_71002EEB14(int type, bool run) {
    if (run) {
        g_bootType = type;
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
            g_bootType = 0;
        }
    }
}

int fn_71002EEBE4() {
    return g_bootType;
}

}  // namespace gf

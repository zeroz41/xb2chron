#include "classes/gf/GfAllocator.h"
#include "gf/GfObjAcc.h"
#include "classes/gf/IDataObj.h"
#include "classes/gf/DataObjDriver.h"
#include "classes/gf/DataObjBlade.h"
#include "gf/GfDataBlade.h"
#include "gf/SDataDriver.h"
#include "gf/GfDataDriver.h"
#include "gf/SDataBlade.h"
#include "gf/SDataDriver.h"
#include "gf/GfDataHana.h"
#include "gf/GfEquipUtil.h"
#include "classes/gf/GfBdatItem.h"
#include "classes/gf/DataParamAcc.h"
#include "gf/GfDataItem.h"
#include "gf/GfDataParty.h"
#include "mm/mtl/FixedVector.h"
#include "classes/gf/GfEvent.h"
#include "classes/gf/GfBdatBtl.h"
#include "classes/gf/GfBdatBlade.h"
#include "classes/gf/GfObjSetup.h"
#include "gf/GfObjUtil.h"
#include "gf/GfDataDriverArts.h"
#include "gf/GfDataWeapon.h"
#include "gf/GfGameUtil.h"
#include "classes/gf/DataObjPcWpn.h"
#include "classes/gf/DataObjEnemy.h"
#include "classes/gf/DataObjEnemyBlade.h"
#include "classes/gf/DataObjNpc.h"
#include "classes/gf/DataObjMap.h"
#include "classes/gf/DataObjMob.h"
#include "classes/gf/DataObjUiObj.h"
#include "classes/gf/DataObjGmk.h"
#include "classes/gf/DataObjBelonging.h"
#include "classes/gf/GfObjSetupGimmick.h"
#include "classes/gf/GfBdatRsc.h"
#include "classes/gf/GfBdatMaplist.h"
#include "gf/GfDataNpc.h"
#include "gf/GfDataMob.h"
#include "gf/GfDataEnemy.h"
#include "gf/SDataEnemy.h"
#include "classes/gf/GfObjSetupEnemy.h"
#include "classes/gf/GfBdatChrEnParam.h"
#include "classes/gf/GfBdatChrEnArrange.h"
#include "classes/gf/GfObjSetupNpc.h"
#include "classes/gf/GfObjSetupMap.h"
#include "classes/gf/GfObjSetupMob.h"
#include "classes/gf/GfObjManager.h"
#include "gf/GfObjInfo.h"
#include "mm/Math.h"
#include "mm/mtl/RTTI.h"
#include "classes/gf/GfObjSetupWeapon.h"
#include "classes/gf/GfGameParty.h"
#include "gf/GfDataUtil.h"

namespace gf {

inline void DataObjDriver::setup(unsigned int id) {
    m_bdatId = id;
    if (id != 0) {
        m_sdata = GfDataDriver::getSDataDriver(id);
        if (GfDataDriver::isIra(m_bdatId)) {
            m_dlc = GfDataDriver::getSDataIra(m_bdatId);
        }
    }
}

DataObjDriver::DataObjDriver(GF_OBJ_HANDLE* handle)
    : m_bdatId(0), m_sdata(nullptr), m_dlc(nullptr), m_handle(handle), m_virtual(nullptr), m_virtualDlc(nullptr),
      m_virtualWeapons(), pad_44(), m_menuParam(false) {
    GfObjAcc acc(handle);
    setup(acc.getDriverId());
}

DataObjDriver::~DataObjDriver() {
    if (m_virtual != nullptr) {
        delete m_virtual;
        m_virtual = nullptr;
    }
    if (m_virtualDlc != nullptr) {
        delete m_virtualDlc;
        m_virtualDlc = nullptr;
    }
}

void DataObjDriver::setVirtualEquipWpn(unsigned int weapon, int slot) {
    setupVirtualParam();
    if (slot < 0) {
        slot = getBladeSet(false);
    }
    if (slot >= 0) {
        m_virtualWeapons[slot] = weapon;
    }
}

void DataObjDriver::setVirtualEquipAcc(unsigned int slot, unsigned int accessory) {
    setupVirtualParam();
    if (GfDataItem::getItemType(accessory) == 2) {
        GfDataDriver::setEquipAcce(*m_sdata, slot, accessory);
    }
}

void DataObjDriver::setVirtualEquipWpnAcce(unsigned int item) {
    setupVirtualParam();
    if (GfDataItem::getItemType(item) == 2 && GfDataDriver::isIra(m_bdatId)) {
        GfDataDriver::setEquipWpnAcce(*m_dlc, item);
    }
}

bool DataObjDriver::isVirtualSetting() const {
    return m_virtual != nullptr;
}

int DataObjDriver::getMenuOffset() const {
    return GfDataDriver::getMenuOffset(getBdatId());
}

const char* DataObjDriver::getCenterBone() const {
    return GfDataDriver::getCenterBone(getBdatId());
}

const char* DataObjDriver::getCamBone() const {
    return GfDataDriver::getCamBone(getBdatId());
}

unsigned int DataObjDriver::getEyeRotControl() const {
    return GfDataDriver::getEyeRotControl(getBdatId());
}

bool DataObjDriver::isValid() const {
    if (m_sdata == nullptr) {
        return false;
    }
    return m_sdata->m_id != 0;
}

const char* DataObjDriver::getModelResourceName() const {
    return GfDataDriver::getModelResourceName(getBdatId());
}

const char* DataObjDriver::getMotionResourceName() const {
    return GfDataDriver::getMotionResourceName(getBdatId());
}

const char* DataObjDriver::getEffectResourceName() const {
    return GfDataDriver::getDebugName(getBdatId());
}

const char* DataObjDriver::getName() const {
    return GfDataDriver::getName(getBdatId());
}

bool DataObjDriver::getName(unsigned char*& bdat, unsigned int& id) const {
    return GfDataDriver::getName(bdat, id, getBdatId());
}

unsigned int DataObjDriver::getBdatId() const {
    return m_bdatId;
}

unsigned short DataObjDriver::getDataType() const {
    return m_sdata->m_dataType;
}

// GEN-HPMAX-BEGIN
void fn_71002255EC(unsigned int& value, const SDataDriver& data, unsigned int rateEffect, unsigned int addEffect);
void fn_710022571C(unsigned int& value, const SDataIra& data, unsigned int rateEffect, unsigned int addEffect);

unsigned int DataObjDriver::getHpMax(bool virtualParam) const {
    if (GfDataDriver::isIra(getBdatId()) && !GfDataDriver::isIraFront(getBdatId())) {
        DataParamAcc acc(3, GfDataDriver::getIraFront(getBdatId()), static_cast<GimmickType>(0));
        return acc.getHpMax(virtualParam);
    }
    const SDataDriver* data = virtualParam ? m_sdata : GfDataDriver::getSDataDriver(getBdatId());
    unsigned int value = data->m_hpMax;
    fn_71002255EC(value, *data, 1, 11);
    if (m_dlc != nullptr) {
        fn_710022571C(value, *m_dlc, 1, 11);
    }
    float rate = GfDataDriver::getHpMaxRev(*data) * 0.01f;
    value += static_cast<unsigned int>(value * rate);
    value = value > 9999 ? 9999 : value;
    return value;
}

// GEN-HPMAX-END
void fn_71002255EC(unsigned int& value, const SDataDriver& data, unsigned int rateEffect, unsigned int addEffect) {
    mm::mtl::FixedVector<unsigned short, 64> enhances;
    GfDataDriver::getValidEnhance(enhances, data);
    float base = value;
    GfBdatBtl* btl = GfBdatBtl::sys();
    for (const unsigned short& enhance : enhances) {
        if (btl->getBTL_EnhanceEnhanceEffect(enhance) == addEffect) {
            base += btl->getBTL_EnhanceParam1(enhance);
        }
    }
    float rate = 0.0f;
    for (const unsigned short& enhance : enhances) {
        if (btl->getBTL_EnhanceEnhanceEffect(enhance) == rateEffect) {
            rate += btl->getBTL_EnhanceParam1(enhance) * 0.01f;
        }
    }
    value = base + base * rate;
}
void fn_710022571C(unsigned int& value, const SDataIra& data, unsigned int rateEffect, unsigned int addEffect) {
    mm::mtl::FixedVector<unsigned short, 64> enhances;
    GfDataDriver::getValidEnhance(enhances, data);
    float base = value;
    GfBdatBtl* btl = GfBdatBtl::sys();
    for (const unsigned short& enhance : enhances) {
        if (btl->getBTL_EnhanceEnhanceEffect(enhance) == addEffect) {
            base += btl->getBTL_EnhanceParam1(enhance);
        }
    }
    float rate = 0.0f;
    for (const unsigned short& enhance : enhances) {
        if (btl->getBTL_EnhanceEnhanceEffect(enhance) == rateEffect) {
            rate += btl->getBTL_EnhanceParam1(enhance) * 0.01f;
        }
    }
    value = base + base * rate;
}

unsigned int DataObjDriver::getLevel(bool virtualParam) const {
    const SDataDriver* data = virtualParam ? m_sdata : GfDataDriver::getSDataDriver(getBdatId());
    unsigned int level = GfDataDriver::getLevel(*data);
    return level > 99 ? 99 : level;
}

unsigned int DataObjDriver::getExp() const {
    return GfDataDriver::getExp(*GfDataDriver::getSDataDriver(getBdatId()));
}

unsigned int DataObjDriver::getBattleExp() const {
    return GfDataDriver::getBattleExp(*GfDataDriver::getSDataDriver(getBdatId()));
}

unsigned int DataObjDriver::getExpNext(bool virtualParam) const {
    const SDataDriver* data = virtualParam ? m_sdata : GfDataDriver::getSDataDriver(getBdatId());
    return GfDataDriver::getExpNextLevel(*data);
}

unsigned int DataObjDriver::getBattleExpNext(bool virtualParam) const {
    const SDataDriver* data = virtualParam ? m_sdata : GfDataDriver::getSDataDriver(getBdatId());
    return GfDataDriver::getBattleExpNextLevel(*data);
}

unsigned int DataObjDriver::getWeaponPoint(unsigned int wpnType) const {
    if (wpnType == 0) {
        unsigned int blade = getBlade(false, -1);
        if (blade == 0) {
            return 0;
        }
        wpnType = GfDataBlade::getSDataBlade(blade)->m_weaponType;
    }
    return GfDataDriverArts::getWp(m_bdatId, wpnType, static_cast<PTPOS>(0));
}

void DataObjDriver::addWeaponPoint(unsigned int wpnType, int point) {
    if (wpnType == 0) {
        unsigned int blade = getBlade(false, -1);
        if (blade == 0) {
            return;
        }
        DataParamAcc acc(4, blade, static_cast<GimmickType>(0));
        wpnType = acc.getWeaponType(-1, false);
    }
    GfDataDriverArts::addWp(getBdatId(), wpnType, point);
}

unsigned int DataObjDriver::getSkillPoint() const {
    return GfDataDriver::getSkillPoint(*GfDataDriver::getSDataDriver(getBdatId()));
}

void DataObjDriver::addSkillPoint(int point) {
    GfDataDriver::addSkillPoint(*GfDataDriver::getSDataDriver(getBdatId()), point);
}

unsigned int DataObjDriver::getBladeArts(bool virtualParam, unsigned int index) const {
    unsigned int blade = getBlade(virtualParam, -1);
    if (blade == 0) {
        return 0;
    }
    DataParamAcc acc(4, blade, static_cast<GimmickType>(0));
    return acc.getBladeArts(index, false);
}

unsigned int DataObjDriver::getBladeArtsEnhance(bool virtualParam, unsigned int index) const {
    unsigned int blade = getBlade(virtualParam, -1);
    if (blade == 0) {
        return 0;
    }
    DataParamAcc acc(4, blade, static_cast<GimmickType>(0));
    return acc.getBladeArtsEnhance(index, false);
}

unsigned int DataObjDriver::getBladeArtsLevel(bool virtualParam, unsigned int index) const {
    unsigned int blade = getBlade(virtualParam, -1);
    if (blade == 0) {
        return 0;
    }
    DataParamAcc acc(4, blade, static_cast<GimmickType>(0));
    return acc.getBladeArtsLevel(index, false);
}

unsigned int DataObjDriver::getBladeArtsH(bool virtualParam, unsigned int index) const {
    unsigned int blade = getBlade(virtualParam, -1);
    if (blade == 0) {
        return 0;
    }
    DataParamAcc acc(4, blade, static_cast<GimmickType>(0));
    return acc.getBladeArtsH(index, false);
}

unsigned int DataObjDriver::getBladeArtsN(bool virtualParam, unsigned int index) const {
    unsigned int blade = getBlade(virtualParam, -1);
    if (blade == 0) {
        return 0;
    }
    DataParamAcc acc(4, blade, static_cast<GimmickType>(0));
    return acc.getBladeArtsN(index, false);
}

unsigned int DataObjDriver::getBladeArtsNH(bool virtualParam, unsigned int index) const {
    unsigned int blade = getBlade(virtualParam, -1);
    if (blade == 0) {
        return 0;
    }
    DataParamAcc acc(4, blade, static_cast<GimmickType>(0));
    return acc.getBladeArtsNH(index, false);
}

unsigned int DataObjDriver::getBladeArtsEx(bool virtualParam) const {
    unsigned int blade = getBlade(virtualParam, -1);
    if (blade == 0) {
        return 0;
    }
    DataParamAcc acc(4, blade, static_cast<GimmickType>(0));
    return acc.getBladeArtsEx(false);
}

unsigned int DataObjDriver::getBladeArtsExH(bool virtualParam) const {
    unsigned int blade = getBlade(virtualParam, -1);
    if (blade == 0) {
        return 0;
    }
    DataParamAcc acc(4, blade, static_cast<GimmickType>(0));
    return acc.getBladeArtsExH(false);
}

unsigned int DataObjDriver::getBladeArtsEx2(bool virtualParam) const {
    unsigned int blade = getBlade(virtualParam, -1);
    if (blade == 0) {
        return 0;
    }
    DataParamAcc acc(4, blade, static_cast<GimmickType>(0));
    return acc.getBladeArtsEx2(false);
}

unsigned int DataObjDriver::getBladeArtsEx2H(bool virtualParam) const {
    unsigned int blade = getBlade(virtualParam, -1);
    if (blade == 0) {
        return 0;
    }
    DataParamAcc acc(4, blade, static_cast<GimmickType>(0));
    return acc.getBladeArtsEx2H(false);
}

unsigned int DataObjDriver::getBladeSkill(bool virtualParam, unsigned int index) const {
    unsigned int blade = getBlade(virtualParam, -1);
    if (blade == 0) {
        return 0;
    }
    DataParamAcc acc(4, blade, static_cast<GimmickType>(0));
    return acc.getBladeSkill(index, false);
}

unsigned int DataObjDriver::getBladeSkillLevel(bool virtualParam, unsigned int index) const {
    unsigned int blade = getBlade(virtualParam, -1);
    if (blade == 0) {
        return 0;
    }
    DataParamAcc acc(4, blade, static_cast<GimmickType>(0));
    return acc.getBladeSkillLevel(index, false);
}

unsigned int DataObjDriver::getDriverArts(unsigned int index, unsigned int slot, PTPOS mode) const {
    unsigned int* arts;
    switch (mode) {
    case 0:
        arts = GfDataDriver::getDriverWeaponType(m_bdatId, index);
        break;
    case 1:
        arts = GfDataDriver::getDriverWeaponTypeIraBack(m_bdatId, index);
        break;
    case 2:
        arts = GfDataDriver::getDriverWeaponTypeIraSwitch(m_bdatId, index);
        break;
    default:
        return 0;
    }
    return arts[slot];
}

unsigned int DataObjDriver::getDriverArtsLevel(unsigned int arts) const {
    return GfDataDriver::getDriverArtsLevel(m_bdatId, arts);
}

void DataObjDriver::setDriverArtsLevel(unsigned int arts, unsigned int level) {
    GfDataDriver::setDriverArtsLevel(m_bdatId, arts, level > 5 ? 5 : level);
}

unsigned int DataObjDriver::getClass(bool virtualParam) const {
    const SDataDriver* data = virtualParam ? m_sdata : GfDataDriver::getSDataDriver(getBdatId());
    return GfDataDriver::getClass(*data);
}

// GEN-STATS-BEGIN
unsigned int DataObjDriver::getStrength(bool virtualParam) const {
    if (GfDataDriver::isIra(getBdatId()) && !GfDataDriver::isIraFront(getBdatId())) {
        DataParamAcc acc(3, GfDataDriver::getIraFront(getBdatId()), static_cast<GimmickType>(0));
        return acc.getStrength(virtualParam);
    }
    const SDataDriver* data = virtualParam ? m_sdata : GfDataDriver::getSDataDriver(getBdatId());
    unsigned int value = (virtualParam ? m_sdata : GfDataDriver::getSDataDriver(getBdatId()))->m_strength;
    fn_71002255EC(value, *data, 2, 12);
    if (m_dlc != nullptr) {
        fn_710022571C(value, *m_dlc, 2, 12);
    }
    float rate = GfDataDriver::getStrengthRev(*data) * 0.01f;
    value += static_cast<unsigned int>(value * rate);
    value = value > 999 ? 999 : value;
    return value;
}

unsigned int DataObjDriver::getPowerEther(bool virtualParam) const {
    if (GfDataDriver::isIra(getBdatId()) && !GfDataDriver::isIraFront(getBdatId())) {
        DataParamAcc acc(3, GfDataDriver::getIraFront(getBdatId()), static_cast<GimmickType>(0));
        return acc.getPowerEther(virtualParam);
    }
    const SDataDriver* data = virtualParam ? m_sdata : GfDataDriver::getSDataDriver(getBdatId());
    unsigned int value = (virtualParam ? m_sdata : GfDataDriver::getSDataDriver(getBdatId()))->m_powEther;
    fn_71002255EC(value, *data, 3, 13);
    if (m_dlc != nullptr) {
        fn_710022571C(value, *m_dlc, 3, 13);
    }
    float rate = GfDataDriver::getPowEtherRev(*data) * 0.01f;
    value += static_cast<unsigned int>(value * rate);
    value = value > 999 ? 999 : value;
    return value;
}

unsigned int DataObjDriver::getDex(bool virtualParam) const {
    if (GfDataDriver::isIra(getBdatId()) && !GfDataDriver::isIraFront(getBdatId())) {
        DataParamAcc acc(3, GfDataDriver::getIraFront(getBdatId()), static_cast<GimmickType>(0));
        return acc.getDex(virtualParam);
    }
    const SDataDriver* data = virtualParam ? m_sdata : GfDataDriver::getSDataDriver(getBdatId());
    unsigned int value = (virtualParam ? m_sdata : GfDataDriver::getSDataDriver(getBdatId()))->m_dex;
    fn_71002255EC(value, *data, 4, 14);
    if (m_dlc != nullptr) {
        fn_710022571C(value, *m_dlc, 4, 14);
    }
    float rate = GfDataDriver::getDexRev(*data) * 0.01f;
    value += static_cast<unsigned int>(value * rate);
    value = value > 999 ? 999 : value;
    return value;
}

unsigned int DataObjDriver::getAgility(bool virtualParam) const {
    if (GfDataDriver::isIra(getBdatId()) && !GfDataDriver::isIraFront(getBdatId())) {
        DataParamAcc acc(3, GfDataDriver::getIraFront(getBdatId()), static_cast<GimmickType>(0));
        return acc.getAgility(virtualParam);
    }
    const SDataDriver* data = virtualParam ? m_sdata : GfDataDriver::getSDataDriver(getBdatId());
    unsigned int value = (virtualParam ? m_sdata : GfDataDriver::getSDataDriver(getBdatId()))->m_agility;
    fn_71002255EC(value, *data, 5, 15);
    if (m_dlc != nullptr) {
        fn_710022571C(value, *m_dlc, 5, 15);
    }
    float rate = GfDataDriver::getAgilityRev(*data) * 0.01f;
    value += static_cast<unsigned int>(value * rate);
    value = value > 999 ? 999 : value;
    return value;
}

unsigned int DataObjDriver::getLuck(bool virtualParam) const {
    if (GfDataDriver::isIra(getBdatId()) && !GfDataDriver::isIraFront(getBdatId())) {
        DataParamAcc acc(3, GfDataDriver::getIraFront(getBdatId()), static_cast<GimmickType>(0));
        return acc.getLuck(virtualParam);
    }
    const SDataDriver* data = virtualParam ? m_sdata : GfDataDriver::getSDataDriver(getBdatId());
    unsigned int value = (virtualParam ? m_sdata : GfDataDriver::getSDataDriver(getBdatId()))->m_luck;
    fn_71002255EC(value, *data, 6, 16);
    if (m_dlc != nullptr) {
        fn_710022571C(value, *m_dlc, 6, 16);
    }
    float rate = GfDataDriver::getLuckRev(*data) * 0.01f;
    value += static_cast<unsigned int>(value * rate);
    value = value > 999 ? 999 : value;
    return value;
}

// GEN-STATS-END
unsigned int DataObjDriver::getPArmor(bool virtualParam) const {
    const SDataDriver* data = virtualParam ? m_sdata : GfDataDriver::getSDataDriver(getBdatId());
    DataObjBlade blade(getBlade(virtualParam, -1));
    if (blade.getBdatId() == 0 || blade.m_sdata->m_bladeId == 0) {
        return data->m_pArmor;
    }
    int slot = getBladeSet(virtualParam);
    if (slot >= 0) {
        blade.setVirtualEquipWpn(m_virtualWeapons[slot], slot);
    }
    unsigned int value = blade.getPArmor(virtualParam);
    data = virtualParam ? m_sdata : GfDataDriver::getSDataDriver(getBdatId());
    value += data->m_pArmor;
    return value > 100 ? 100 : value;
}

bool DataObjBlade::isValid() const {
    if (m_sdata == nullptr) {
        return false;
    }
    return m_sdata->m_bladeId != 0;
}

void DataObjBlade::setVirtualEquipWpn(unsigned int weapon, int) {
    if (weapon == 0) {
        return;
    }
    setupVirtualParam();
    m_virtual->m_equipWeapon = weapon;
}

unsigned int DataObjBlade::getPArmor(bool virtualParam) const {
    unsigned int value = GfDataBlade::getParmor(getBdatId());
    GfBdatItem* item = GfBdatItem::sys();
    unsigned int weapon = getEquipWeapon(virtualParam, -1);
    if (weapon != 0) {
        value += item->getPcWpnPArmor(weapon);
    }
    fn_7100228AA4(value, *(virtualParam ? m_sdata : GfDataBlade::getSDataBlade(getBdatId())), 8, 18,
                  isVirtualSetting() | m_menuParam);
    fn_7100228AA4(value, *(virtualParam ? m_sdata : GfDataBlade::getSDataBlade(getBdatId())), 0, 146,
                  isVirtualSetting() | m_menuParam);
    return value;
}

unsigned int DataObjDriver::getEArmor(bool virtualParam) const {
    const SDataDriver* data = virtualParam ? m_sdata : GfDataDriver::getSDataDriver(getBdatId());
    DataObjBlade blade(getBlade(virtualParam, -1));
    if (blade.getBdatId() == 0 || blade.m_sdata->m_bladeId == 0) {
        return data->m_eArmor;
    }
    int slot = getBladeSet(virtualParam);
    if (slot >= 0) {
        blade.setVirtualEquipWpn(m_virtualWeapons[slot], slot);
    }
    unsigned int value = blade.getEArmor(virtualParam);
    value += data->m_eArmor;
    return value > 100 ? 100 : value;
}

unsigned int DataObjBlade::getEArmor(bool virtualParam) const {
    unsigned int value = GfDataBlade::getEarmor(getBdatId());
    GfBdatItem* item = GfBdatItem::sys();
    unsigned int weapon = getEquipWeapon(virtualParam, -1);
    if (weapon != 0) {
        value += item->getPcWpnEArmor(weapon);
    }
    fn_7100228AA4(value, *(virtualParam ? m_sdata : GfDataBlade::getSDataBlade(getBdatId())), 9, 19,
                  isVirtualSetting() | m_menuParam);
    fn_7100228AA4(value, *(virtualParam ? m_sdata : GfDataBlade::getSDataBlade(getBdatId())), 0, 146,
                  isVirtualSetting() | m_menuParam);
    return value;
}

unsigned int DataObjDriver::getCriticalRate(bool virtualParam) const {
    const SDataDriver* data = virtualParam ? m_sdata : GfDataDriver::getSDataDriver(getBdatId());
    unsigned int value = data->m_criticalRate;
    if (GfDataDriver::isIra(getBdatId())) {
        if (!GfDataDriver::isIraFront(getBdatId())) {
            DataParamAcc acc(4, GfDataDriver::getIraBlade(getBdatId(), -1), static_cast<GimmickType>(0));
            return acc.getCriticalRate(virtualParam);
        }
        value += GfDataWeapon::getCriticalRatioForIra(GfDataDriver::getIraFront(getBdatId()));
        if (m_dlc != nullptr) {
            fn_710022571C(value, *m_dlc, 7, 17);
        }
    } else {
        DataObjBlade blade(getBlade(virtualParam, -1));
        if (blade.getBdatId() == 0 || blade.m_sdata->m_bladeId == 0) {
            return value;
        }
        int slot = getBladeSet(virtualParam);
        if (slot >= 0) {
            blade.setVirtualEquipWpn(m_virtualWeapons[slot], slot);
        }
        value += blade.getCriticalRate(virtualParam);
    }
    if (value > 100) {
        value = 100;
    }
    return value;
}

unsigned int DataObjBlade::getCriticalRate(bool virtualParam) const {
    unsigned int value = 0;
    GfBdatItem* item = GfBdatItem::sys();
    unsigned int weapon = getEquipWeapon(virtualParam, -1);
    if (weapon != 0) {
        value = item->getPcWpnCriRate(weapon);
    }
    fn_7100228AA4(value, *(virtualParam ? m_sdata : GfDataBlade::getSDataBlade(getBdatId())), 7, 17,
                  isVirtualSetting() | m_menuParam);
    return value;
}

unsigned int DataObjDriver::getGuardRate(bool virtualParam) const {
    const SDataDriver* data = virtualParam ? m_sdata : GfDataDriver::getSDataDriver(getBdatId());
    unsigned int value = data->m_guardRate;
    if (GfDataDriver::isIra(getBdatId())) {
        if (!GfDataDriver::isIraFront(getBdatId())) {
            DataParamAcc acc(4, GfDataDriver::getIraBlade(getBdatId(), -1), static_cast<GimmickType>(0));
            return acc.getGuardRate(virtualParam);
        }
        value += GfDataWeapon::getGuardRatioForIra(GfDataDriver::getIraFront(getBdatId()));
        if (m_dlc != nullptr) {
            fn_710022571C(value, *m_dlc, 10, 20);
        }
    } else {
        DataObjBlade blade(getBlade(virtualParam, -1));
        if (blade.getBdatId() == 0 || blade.m_sdata->m_bladeId == 0) {
            return value;
        }
        int slot = getBladeSet(virtualParam);
        if (slot >= 0) {
            blade.setVirtualEquipWpn(m_virtualWeapons[slot], slot);
        }
        value += blade.getGuardRate(virtualParam);
    }
    if (value > 100) {
        value = 100;
    }
    return value;
}

unsigned int DataObjBlade::getGuardRate(bool virtualParam) const {
    unsigned int value = 0;
    GfBdatItem* item = GfBdatItem::sys();
    unsigned int weapon = getEquipWeapon(virtualParam, -1);
    if (weapon != 0) {
        value = item->getPcWpnGuardRate(weapon);
    }
    fn_7100228AA4(value, *(virtualParam ? m_sdata : GfDataBlade::getSDataBlade(getBdatId())), 10, 20,
                  isVirtualSetting() | m_menuParam);
    return value;
}

unsigned int DataObjDriver::getAutoHate(bool virtualParam) const {
    unsigned int blade = getBlade(virtualParam, -1);
    if (blade != 0 && GfDataBlade::getSDataBlade(blade)->m_bladeId != 0 && GfDataHana::isValid(blade)) {
        return GfDataHana::getAutoHate(blade);
    }
    return 0;
}

unsigned int DataObjBlade::getAutoHate(bool) const {
    if (GfDataHana::isValid(getBdatId())) {
        return GfDataHana::getAutoHate(getBdatId());
    }
    return 0;
}

unsigned int DataObjDriver::getArtsHate(bool virtualParam) const {
    unsigned int blade = getBlade(virtualParam, -1);
    if (blade != 0 && GfDataBlade::getSDataBlade(blade)->m_bladeId != 0 && GfDataHana::isValid(blade)) {
        return GfDataHana::getArtsHate(blade);
    }
    return 0;
}

unsigned int DataObjBlade::getArtsHate(bool) const {
    if (GfDataHana::isValid(getBdatId())) {
        return GfDataHana::getArtsHate(getBdatId());
    }
    return 0;
}

unsigned int DataObjBlade::getWeaponDamage(bool virtualParam) const {
    GfBdatItem* item = GfBdatItem::sys();
    unsigned int weapon = getEquipWeapon(virtualParam, -1);
    if (weapon != 0) {
        return item->getPcWpnDamage(weapon);
    }
    return 0;
}

unsigned int DataObjBlade::getWeaponStability(bool virtualParam) const {
    GfBdatItem* item = GfBdatItem::sys();
    unsigned int weapon = getEquipWeapon(virtualParam, -1);
    if (weapon != 0) {
        return item->getPcWpnStability(weapon);
    }
    return 0;
}

unsigned int DataObjDriver::getEquipAcce(unsigned int slot, bool virtualParam) const {
    const SDataDriver* data = virtualParam ? m_sdata : GfDataDriver::getSDataDriver(getBdatId());
    return GfDataDriver::getEquipAcce(*data, slot);
}

unsigned int DataObjDriver::getEquipAcceResult(unsigned int slot, unsigned int accessory, bool virtualParam) const {
    const SDataDriver* data = virtualParam ? m_sdata : GfDataDriver::getSDataDriver(getBdatId());
    return GfEquipUtil::getEquipAcceResult(*data, slot, accessory);
}

int DataObjDriver::getBladeSet(bool virtualParam) const {
    const SDataDriver* data = virtualParam ? m_sdata : GfDataDriver::getSDataDriver(getBdatId());
    return GfDataDriver::getBladeSet(*data);
}

void DataObjDriver::setBladeSet(int slot) {
    if (slot < 0 || DataObjDriver::getBlade(false, slot) == 0) {
        return;
    }
    int current = m_sdata->m_bladeSet;
    if (current >= 0) {
        GfDataDriver::setEquipBlade(m_sdata->m_id, false, current);
    }
    GfDataDriver::setEquipBlade(m_sdata->m_id, true, slot);
    GfEvent::callBladeChange(m_handle, current, slot);
}

unsigned int DataObjDriver::getBlade(bool virtualParam, int slot) const {
    if (GfDataDriver::isIra(getBdatId())) {
        if (slot > 0) {
            return 0;
        }
        return GfDataDriver::getIraBlade(getBdatId(), -1);
    }
    GfObjSetup* setup = GfObjUtil::getObjSetup(m_handle);
    if (setup != nullptr && setup->m_isAllWeapon && setup->pad_58 != 0) {
        return setup->pad_58;
    }
    if (slot >= 0) {
        return m_sdata->m_blades[slot];
    }
    int set = getBladeSet(virtualParam);
    if (set < 0) {
        return 0;
    }
    const SDataDriver* data = virtualParam ? m_sdata : GfDataDriver::getSDataDriver(getBdatId());
    return GfDataDriver::getBlade(*data, set);
}

unsigned int DataObjDriver::getEquipWeapon(bool virtualParam, int slot) const {
    if (slot < 0) {
        slot = getBladeSet(virtualParam);
    }
    unsigned int blade = getBlade(virtualParam, slot);
    if (blade == 0) {
        return 0;
    }
    const SDataBlade* data = GfDataBlade::getSDataBlade(blade);
    if (data->m_bladeId == 0) {
        return 0;
    }
    if (virtualParam) {
        unsigned int weapon = m_virtualWeapons[slot];
        if (weapon != 0) {
            return weapon;
        }
        return data->m_equipWeapon;
    }
    return GfDataBlade::getSDataBlade(blade)->m_equipWeapon;
}

unsigned int DataObjBlade::getEquipWeapon(bool virtualParam, int) const {
    const SDataBlade* data = virtualParam ? m_sdata : GfDataBlade::getSDataBlade(getBdatId());
    return data->m_equipWeapon;
}

unsigned int DataObjDriver::getWeaponType(bool virtualParam, int slot) const {
    unsigned int blade = getBlade(virtualParam, slot);
    GfObjSetup* setup = GfObjUtil::getObjSetup(m_handle);
    if (setup != nullptr) {
        unsigned int other = setup->m_isAllWeapon ? setup->pad_58 : 0;
        if (other != 0) {
            blade = other;
        }
    }
    if (blade == 0) {
        return 0;
    }
    const SDataBlade* data = GfDataBlade::getSDataBlade(blade);
    if (data->m_bladeId == 0) {
        return 0;
    }
    if (!virtualParam) {
        data = GfDataBlade::getSDataBlade(blade);
    }
    return data->m_weaponType;
}

unsigned int DataObjBlade::getWeaponType(bool virtualParam, int) const {
    const SDataBlade* data = virtualParam ? m_sdata : GfDataBlade::getSDataBlade(getBdatId());
    return data->m_weaponType;
}

unsigned int DataObjDriver::getChestHeight() const {
    return GfDataDriver::getChestHeight(getBdatId());
}

unsigned int DataObjDriver::getLandingHeight() const {
    return GfDataDriver::getLandingHeight(getBdatId());
}

unsigned int DataObjDriver::getIconData() const {
    return GfDataDriver::getIconData(getBdatId());
}

unsigned int DataObjDriver::getRace() const {
    return GfDataDriver::getRace(getBdatId());
}

unsigned int DataObjDriver::getFootStep() const {
    return GfDataDriver::getFootStep(getBdatId());
}

unsigned int DataObjDriver::getFootStepEffect() const {
    return GfDataDriver::getFootStepEffect(getBdatId());
}

unsigned int DataObjDriver::getGender() const {
    return GfDataDriver::getGender(getBdatId());
}

unsigned int DataObjDriver::getAttribute(bool virtualParam, int slot) const {
    if (GfDataDriver::isIra(getBdatId())) {
        if (GfDataDriver::isIraFront(getBdatId())) {
            unsigned int item = GfDataDriver::getEquipWpnAcce(getBdatId());
            if (item == 0) {
                return 1;
            }
            return GfBdatItem::sys()->getPcEquipAddAtr(item);
        }
        DataObjBlade data(GfDataDriver::getIraBlade(getBdatId(), -1));
        return data.getAttribute(virtualParam, -1);
    }
    if (slot < 0) {
        slot = getBladeSet(virtualParam);
    }
    unsigned int blade = slot >= 0 ? m_sdata->m_blades[slot] : 0;
    GfObjSetup* setup = GfObjUtil::getObjSetup(m_handle);
    if (setup != nullptr) {
        unsigned int id = setup->m_isAllWeapon ? setup->pad_58 : 0;
        if (id != 0) {
            blade = id;
        }
    }
    DataObjBlade data(blade);
    return data.getAttribute(virtualParam, -1);
}

unsigned int DataObjBlade::getAttribute(bool, int) const {
    return static_cast<unsigned char>(GfDataBlade::getAttribute(getBdatId()));
}

bool DataObjDriver::isScenarioMask() const {
    return GfDataDriver::isScenarioMask(getBdatId());
}

unsigned int DataObjDriver::getRole() const {
    return GfDataBlade::getRole(getBlade(false, -1));
}

const char* DataObjDriver::getVoiceStr() const {
    return GfDataDriver::getVoiceStr(*m_sdata);
}

unsigned int DataObjDriver::getFieldSkill(bool, unsigned int index) const {
    DataObjBlade blade(getBlade(false, -1));
    return blade.getFieldSkill(false, index);
}

unsigned int DataObjBlade::getFieldSkill(bool, unsigned int index) const {
    return GfDataBlade::getSDataBlade(getBdatId())->m_fieldSkills[index].m_id;
}

unsigned int DataObjDriver::getFieldSkillLevel(bool, unsigned int index) const {
    DataObjBlade blade(getBlade(false, -1));
    return blade.getFieldSkillLevel(false, index);
}

unsigned int DataObjBlade::getFieldSkillLevel(bool, unsigned int index) const {
    return GfDataBlade::getSDataBlade(getBdatId())->m_fieldSkills[index].m_level;
}

unsigned int DataObjDriver::getKeyLevel() const {
    DataObjBlade blade(getBlade(false, -1));
    return blade.getKeyLevel();
}

unsigned int DataObjBlade::getKeyLevel() const {
    return GfDataBlade::getSDataBlade(getBdatId())->m_keyLevel;
}

unsigned int DataObjDriver::getFavoriteCategory(FAVORITE favorite) const {
    return GfDataDriver::getFavorite(getBdatId(), favorite);
}

unsigned int DataObjDriver::getFavoriteItem(FAVORITE favorite) const {
    return GfDataDriver::getFavorite(getBdatId(), favorite);
}

DataObjBlade::DataObjBlade(unsigned int id)
    : m_sdata(nullptr), m_handle(reinterpret_cast<GF_OBJ_HANDLE*>(-1)), m_virtual(nullptr), m_menuParam(false) {
    setup(id);
}

inline void DataObjBlade::setup(unsigned int id) {
    m_bdatId = id;
    if (id != 0) {
        m_sdata = GfDataBlade::getSDataBlade(id);
    }
}

DataObjBlade::DataObjBlade(GF_OBJ_HANDLE* handle)
    : m_sdata(nullptr), m_handle(handle), m_virtual(nullptr), m_bdatId(0), m_menuParam(false) {
    GfObjAcc acc(handle);
    setup(acc.getBladeId());
}

DataObjBlade::~DataObjBlade() {
    if (m_virtual != nullptr) {
        delete m_virtual;
        m_virtual = nullptr;
    }
}

inline void DataObjBlade::setupVirtualParam() {
    if (m_virtual == nullptr) {
#line 1568
        m_virtual = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) SDataBlade();
        *m_virtual = *m_sdata;
        m_sdata = m_virtual;
    }
}

const char* DataObjBlade::getModelResourceName() const {
    return GfDataBlade::getSDataBlade(getBdatId())->m_modelName;
}

const char* DataObjBlade::getMotionResourceName() const {
    return GfDataBlade::getSDataBlade(getBdatId())->m_motionName;
}

const char* DataObjBlade::getEffectResourceName() const {
    return GfDataBlade::getSDataBlade(getBdatId())->m_effectName;
}

const char* DataObjBlade::getSeResourceName() const {
    return GfDataBlade::getSDataBlade(getBdatId())->m_seName;
}

const char* DataObjBlade::getName() const {
    return GfDataBlade::getName(getBdatId(), 0);
}

bool DataObjBlade::getName(unsigned char*& bdat, unsigned int& id) const {
    return GfDataBlade::getName(bdat, id, getBdatId());
}

unsigned int DataObjBlade::getBdatId() const {
    return m_bdatId;
}

unsigned short DataObjBlade::getDataType() const {
    return GfDataBlade::getSDataBlade(getBdatId())->m_dataType;
}

const SDataIdea* DataObjBlade::getIdea() const {
    return &GfDataBlade::getSDataBlade(getBdatId())->m_idea;
}

unsigned int DataObjBlade::getHpMax(bool) const {
    return GfDataBlade::getHpMaxRev(getBdatId());
}

unsigned int DataObjBlade::getStrength(bool) const {
    return GfDataBlade::getStrengthRev(getBdatId());
}

unsigned int DataObjBlade::getPowerEther(bool) const {
    return GfDataBlade::getPowerEtherRev(getBdatId());
}

unsigned int DataObjBlade::getDex(bool) const {
    return GfDataBlade::getDexRev(getBdatId());
}

unsigned int DataObjBlade::getAgility(bool) const {
    return GfDataBlade::getAgilityRev(getBdatId());
}

unsigned int DataObjBlade::getLuck(bool) const {
    return GfDataBlade::getLuckRev(getBdatId());
}

void DataObjBlade::fn_7100228AA4(unsigned int& value, SDataBlade& data, unsigned int rateEffect,
                                 unsigned int addEffect, bool flag) {
    mm::mtl::FixedVector<unsigned short, 64> enhances;
    GfDataBlade::getValidEnhance(enhances, data, flag);
    float base = value;
    GfBdatBtl* btl = GfBdatBtl::sys();
    for (const unsigned short& enhance : enhances) {
        if (btl->getBTL_EnhanceEnhanceEffect(enhance) == addEffect) {
            base += btl->getBTL_EnhanceParam1(enhance);
        }
    }
    float rate = 0.0f;
    for (const unsigned short& enhance : enhances) {
        if (btl->getBTL_EnhanceEnhanceEffect(enhance) == rateEffect) {
            rate += btl->getBTL_EnhanceParam1(enhance) * 0.01f;
        }
    }
    value = base + base * rate;
}

bool DataObjBlade::getEquipOrb(mm::mtl::FixedArray<unsigned short, 3ul>& orbs, bool) const {
    return GfDataBlade::getEquipOrb(orbs, getBdatId());
}

unsigned int DataObjBlade::getChestHeight() const {
    return GfDataBlade::getSDataBlade(getBdatId())->m_chestHeight;
}

unsigned int DataObjBlade::getLandingHeight() const {
    return GfDataBlade::getSDataBlade(getBdatId())->m_landingHeight;
}

unsigned int DataObjBlade::getIconData() const {
    return GfDataBlade::getSDataBlade(getBdatId())->m_iconData;
}

unsigned int DataObjBlade::getRace() const {
    return GfDataBlade::getSDataBlade(getBdatId())->m_race;
}

unsigned int DataObjBlade::getQuestRace() const {
    return GfDataBlade::getQuestRace(GfDataBlade::getSDataBlade(getBdatId())->m_bladeId);
}

unsigned int DataObjBlade::getFootStep() const {
    return GfDataBlade::getFootStep(getBdatId());
}

unsigned int DataObjBlade::getFootStepEffect() const {
    return GfDataBlade::getFootStepEffect(getBdatId());
}

unsigned int DataObjBlade::getGender() const {
    return GfDataBlade::getSDataBlade(getBdatId())->m_gender;
}

bool DataObjBlade::isDispInitExtraParts(unsigned int part) const {
    if (part > 3) {
        return false;
    }
    return GfDataBlade::getExtraParts(*GfDataBlade::getSDataBlade(getBdatId()), part);
}

unsigned int DataObjBlade::getRole() const {
    return GfDataBlade::getRole(getBdatId());
}

const char* DataObjBlade::getVoiceStr() const {
    return GfDataBlade::getVoiceStr(getBdatId());
}

int DataObjBlade::getBladeSet(bool) const {
    int driver = GfDataBlade::getCreator(getBdatId());
    if (GfDataParty::getDriverPartyID(driver) == -1) {
        return -1;
    }
    int num = GfDataDriver::getMaxSetBladeNum(driver);
    for (int slot = 0; slot < num; slot++) {
        if (GfDataDriver::getBlade(driver, slot) == getBdatId()) {
            return slot;
        }
    }
    return -1;
}

unsigned int DataObjBlade::getBlade(bool, int) const {
    return getBdatId();
}

unsigned int DataObjBlade::getBladePower(bool virtualParam) const {
    SDataBlade* data = virtualParam ? m_sdata : GfDataBlade::getSDataBlade(getBdatId());
    return GfDataBlade::getBladePower(*data);
}

unsigned int DataObjBlade::getBladeArts(bool, unsigned int index) const {
    return GfDataBlade::getArts(getBdatId(), index)->m_id;
}

unsigned int DataObjBlade::getBladeArtsEnhance(bool, unsigned int index) const {
    return GfDataBlade::getArtsEnhance(getBdatId(), index);
}

unsigned int DataObjBlade::getBladeArtsLevel(bool, unsigned int index) const {
    return GfDataBlade::getArts(getBdatId(), index)->m_level;
}

unsigned int DataObjBlade::getBladeArtsH(bool, unsigned int index) const {
    return GfDataBlade::getArts(getBdatId(), index)->m_h;
}

unsigned int DataObjBlade::getBladeArtsN(bool, unsigned int index) const {
    return GfDataBlade::getNArts(getBdatId(), index)->m_id;
}

unsigned int DataObjBlade::getBladeArtsNH(bool, unsigned int index) const {
    return GfDataBlade::getNArts(getBdatId(), index)->m_h;
}

unsigned int DataObjBlade::getBladeArtsEx(bool virtualParam) const {
    SDataBlade* data = virtualParam ? m_sdata : GfDataBlade::getSDataBlade(getBdatId());
    return data->m_artsEx.m_id;
}

unsigned int DataObjBlade::getBladeArtsExH(bool virtualParam) const {
    SDataBlade* data = virtualParam ? m_sdata : GfDataBlade::getSDataBlade(getBdatId());
    return data->m_artsEx.m_h;
}

unsigned int DataObjBlade::getBladeArtsEx2(bool virtualParam) const {
    SDataBlade* data = virtualParam ? m_sdata : GfDataBlade::getSDataBlade(getBdatId());
    return data->m_artsEx2.m_id;
}

unsigned int DataObjBlade::getBladeArtsEx2H(bool virtualParam) const {
    SDataBlade* data = virtualParam ? m_sdata : GfDataBlade::getSDataBlade(getBdatId());
    return data->m_artsEx2.m_h;
}

unsigned int DataObjBlade::getBladeSkill(bool virtualParam, unsigned int index) const {
    SDataBlade* data = virtualParam ? m_sdata : GfDataBlade::getSDataBlade(getBdatId());
    return data->m_skills[index].m_id;
}

unsigned int DataObjBlade::getBladeSkillLevel(bool virtualParam, unsigned int index) const {
    SDataBlade* data = virtualParam ? m_sdata : GfDataBlade::getSDataBlade(getBdatId());
    return data->m_skills[index].m_level;
}

unsigned int DataObjBlade::getPersonality() const {
    return GfDataBlade::getSDataBlade(getBdatId())->m_personality;
}

unsigned int DataObjBlade::getCoolTime() const {
    return GfDataBlade::getSDataBlade(getBdatId())->m_coolTime;
}

unsigned int DataObjBlade::getFavoriteCategory(FAVORITE favorite) const {
    return GfDataBlade::getFavorite(getBdatId(), favorite);
}

unsigned int DataObjBlade::getFavoriteItem(FAVORITE favorite) const {
    return GfDataBlade::getFavorite(getBdatId(), favorite);
}

unsigned int DataObjBlade::getArtsAchievement(unsigned int line) const {
    return GfDataBlade::getSDataBlade(getBdatId())->m_artsAchievement[line].m_achievementId;
}

unsigned int DataObjBlade::getSkillAchievement(unsigned int line) const {
    return GfDataBlade::getSDataBlade(getBdatId())->m_skillAchievement[line].m_achievementId;
}

unsigned int DataObjBlade::getFieldSkillAchievement(unsigned int line) const {
    return GfDataBlade::getSDataBlade(getBdatId())->m_fieldSkillAchievement[line].m_achievementId;
}

unsigned int DataObjBlade::getKeyAchievement() const {
    return GfDataBlade::getSDataBlade(getBdatId())->m_keyAchievement.m_achievementId;
}

unsigned int DataObjBlade::getLinkNum() const {
    unsigned int link = GfGameUtil::getKizunaLink(getBlade(false, -1));
    return GfBdatBtl::sys()->getBTL_Bl_KizunaLinkLinkNum(link);
}

// 1.0.0's getDeadNum reads the LinkNum column too
unsigned int DataObjBlade::getDeadNum() const {
    unsigned int link = GfGameUtil::getKizunaLink(getBlade(false, -1));
    return GfBdatBtl::sys()->getBTL_Bl_KizunaLinkLinkNum(link);
}

unsigned int DataObjBlade::getAppStNum() const {
    unsigned int link = GfGameUtil::getKizunaLink(getBlade(false, -1));
    return GfBdatBtl::sys()->getBTL_Bl_KizunaLinkAppStNum(link);
}

unsigned int DataObjBlade::getAppEndNum() const {
    unsigned int link = GfGameUtil::getKizunaLink(getBlade(false, -1));
    return GfBdatBtl::sys()->getBTL_Bl_KizunaLinkAppEndNum(link);
}

void DataObjBlade::setVirtualEquipWpnChip(unsigned int chip) {
    if (chip == 0) {
        return;
    }
    setupVirtualParam();
    unsigned int weapon = GfDataBlade::getBladeWeaponByRank(getBdatId(), chip);
    if (weapon != 0) {
        m_virtual->m_equipWeapon = weapon;
    }
}

void DataObjBlade::setVirtualEquipOrb(unsigned int orb, unsigned int slot) {
    setupVirtualParam();
    m_virtual->m_equipOrbs[slot] = orb;
}

bool DataObjBlade::isVirtualSetting() const {
    return m_virtual != nullptr;
}

bool DataObjBlade::isEnbaleTarget() const {
    return false;
}

int DataObjBlade::getMenuOffset() const {
    return GfDataBlade::getOffsetID(getBdatId());
}

const char* DataObjBlade::getCenterBone() const {
    return GfDataBlade::getSDataBlade(getBdatId())->m_centerBone;
}

const char* DataObjBlade::getCamBone() const {
    return GfDataBlade::getSDataBlade(getBdatId())->m_camBone;
}

unsigned int DataObjBlade::getEyeRotControl() const {
    return GfDataBlade::getSDataBlade(getBdatId())->m_eyeRotControl;
}

}  // namespace gf

namespace gf {

DataObjPcWpn::DataObjPcWpn(unsigned int id) : m_handle(reinterpret_cast<GF_OBJ_HANDLE*>(-1)), m_bdatId(id) {}

DataObjPcWpn::DataObjPcWpn(GF_OBJ_HANDLE* handle) : m_handle(handle) {
    GfObjAcc acc(handle);
    m_bdatId = acc.getPcWeaponId();
}

DataObjPcWpn::~DataObjPcWpn() {}

bool DataObjPcWpn::isValid() const {
    return m_bdatId != 0;
}

const char* DataObjPcWpn::getName() const {
    return GfDataItem::getName(getBdatId());
}

bool DataObjPcWpn::getName(unsigned char*& bdat, unsigned int& id) const {
    return GfDataItem::getName(bdat, id, getBdatId());
}

unsigned int DataObjPcWpn::getBdatId() const {
    return m_bdatId;
}

unsigned int DataObjPcWpn::getEquipWeapon(bool, int) const {
    return m_bdatId;
}

unsigned int DataObjPcWpn::getAttribute(bool, int slot) const {
    if (m_handle == reinterpret_cast<GF_OBJ_HANDLE*>(-1)) {
        return 0;
    }
    unsigned int party = GfObjUtil::getObjSetup(m_handle)->m_partyId;
    if (party == static_cast<unsigned int>(-1)) {
        return 0;
    }
    if (GfDataUtil::isIra()) {
        GFOBJ_INFO* info = GfObjManager::getObjInfo(m_handle);
        if (info != nullptr) {
            if (GfObjSetup* setup = info->m_setup) {
                if (setup->m_type == info->m_obj->m_type && info->m_obj->m_type == 10) {
                    if (GfObjSetupWeapon* weapon = mm::mtl::rttiCast<GfObjSetupWeapon>(setup)) {
                        DataParamAcc acc(3, weapon->m_param.pad_128, static_cast<GimmickType>(0));
                        return acc.getAttribute(-1, false);
                    }
                }
            }
        }
    }
    DataParamAcc acc(GfGameParty::getHandleBlade(party, slot));
    return acc.getAttribute(-1, false);
}

unsigned int DataObjPcWpn::getWeaponType(bool, int) const {
    return GfBdatItem::sys()->getPcWpnWpnType(getBdatId());
}

unsigned int DataObjPcWpn::getWeaponDamage(bool) const {
    return GfBdatItem::sys()->getPcWpnDamage(getBdatId());
}

unsigned int DataObjPcWpn::getWeaponStability(bool) const {
    return GfBdatItem::sys()->getPcWpnStability(getBdatId());
}

DataObjEnemy::~DataObjEnemy() {}

bool DataObjEnemy::isValid() const {
    return m_sdata != nullptr;
}

const char* DataObjEnemy::getName() const {
    return GfDataEnemy::getName(getBdatId());
}

bool DataObjEnemy::getName(unsigned char*& bdat, unsigned int& id) const {
    return GfDataEnemy::getName(bdat, id, getBdatId());
}

const char* DataObjEnemy::getModelResourceName() const {
    return GfBdatRsc::sys()->getRscEnModel(m_sdata->m_rscId);
}

const char* DataObjEnemy::getMotionResourceName() const {
    return GfBdatRsc::sys()->getRscEnMotion(m_sdata->m_rscId);
}

const char* DataObjEnemy::getEffectResourceName() const {
    return GfBdatRsc::sys()->getRscEnComp_Eff(m_sdata->m_rscId);
}

unsigned int DataObjEnemy::getBdatId() const {
    return m_sdata->m_id;
}

unsigned int DataObjEnemy::getHpMax(bool) const {
    float value = m_sdata->m_hpMax;
    if (fn_7100229CEC(value, getBdatIdEnArrange(), 1, 11)) {
        float rate = GfDataBlade::getHpMaxRev(GfDataEnemy::getEquipBlade(getBdatIdEnArrange())) * 0.01f;
        value += value * rate;
    }
    if (m_sdata->m_paramId != 0) {
        unsigned int rev = GfBdatChrEnParam::sys()->getChrEnParamRevHpMaxRev(m_sdata->m_paramId);
        if (rev != 0) {
            value = rev * 0.001f * value;
        }
    }
    if (value > 1000000000.0f) {
        value = 1000000000.0f;
    }
    return value;
}

bool DataObjEnemy::fn_7100229CEC(float& value, unsigned int arrange, unsigned int rateEffect, unsigned int addEffect) {
    if (GfDataEnemy::getEquipBlade(arrange) == 0) {
        return false;
    }
    mm::mtl::FixedVector<unsigned short, 64> enhances;
    GfDataEnemy::getValidEnhance(enhances, arrange);
    float base = value;
    GfBdatBtl* btl = GfBdatBtl::sys();
    for (const unsigned short* it = enhances.begin(); it != enhances.end(); ++it) {
        if (btl->getBTL_EnhanceEnhanceEffect(*it) == addEffect) {
            base += btl->getBTL_EnhanceParam1(*it);
        }
    }
    float rate = 0.0f;
    for (const unsigned short* it = enhances.begin(); it != enhances.end(); ++it) {
        if (btl->getBTL_EnhanceEnhanceEffect(*it) == rateEffect) {
            rate += btl->getBTL_EnhanceParam1(*it) * 0.01f;
        }
    }
    value = base + base * rate;
    return true;
}

unsigned int DataObjEnemy::getHp() const {
    if (m_handle != reinterpret_cast<GF_OBJ_HANDLE*>(-1)) {
        return GfObjUtil::getHp(m_handle);
    }
    return getHpMax(false);
}

unsigned int DataObjEnemy::getStrength(bool) const {
    float value = m_sdata->m_strength;
    if (fn_7100229CEC(value, getBdatIdEnArrange(), 2, 12)) {
        float rate = GfDataBlade::getStrengthRev(GfDataEnemy::getEquipBlade(getBdatIdEnArrange())) * 0.01f;
        value += value * rate;
    }
    if (m_sdata->m_paramId != 0) {
        unsigned int rev = GfBdatChrEnParam::sys()->getChrEnParamRevStrengthRev(m_sdata->m_paramId);
        if (rev != 0) {
            value = rev * 0.001f * value;
        }
    }
    if (value > 9999.0f) {
        value = 9999.0f;
    }
    return value;
}

unsigned int DataObjEnemy::getPowerEther(bool) const {
    float value = m_sdata->m_powerEther;
    if (fn_7100229CEC(value, getBdatIdEnArrange(), 3, 13)) {
        float rate = GfDataBlade::getPowerEtherRev(GfDataEnemy::getEquipBlade(getBdatIdEnArrange())) * 0.01f;
        value += value * rate;
    }
    if (m_sdata->m_paramId != 0) {
        unsigned int rev = GfBdatChrEnParam::sys()->getChrEnParamRevPowEtherRev(m_sdata->m_paramId);
        if (rev != 0) {
            value = rev * 0.001f * value;
        }
    }
    if (value > 9999.0f) {
        value = 9999.0f;
    }
    return value;
}

unsigned int DataObjEnemy::getDex(bool) const {
    float value = m_sdata->m_dex;
    if (fn_7100229CEC(value, getBdatIdEnArrange(), 4, 14)) {
        float rate = GfDataBlade::getDexRev(GfDataEnemy::getEquipBlade(getBdatIdEnArrange())) * 0.01f;
        value += value * rate;
    }
    if (m_sdata->m_paramId != 0) {
        unsigned int rev = GfBdatChrEnParam::sys()->getChrEnParamRevDexRev(m_sdata->m_paramId);
        if (rev != 0) {
            value = rev * 0.001f * value;
        }
    }
    if (value > 9999.0f) {
        value = 9999.0f;
    }
    return value;
}

unsigned int DataObjEnemy::getAgility(bool) const {
    float value = m_sdata->m_agility;
    if (fn_7100229CEC(value, getBdatIdEnArrange(), 5, 15)) {
        float rate = GfDataBlade::getAgilityRev(GfDataEnemy::getEquipBlade(getBdatIdEnArrange())) * 0.01f;
        value += value * rate;
    }
    if (m_sdata->m_paramId != 0) {
        unsigned int rev = GfBdatChrEnParam::sys()->getChrEnParamRevAgilityRev(m_sdata->m_paramId);
        if (rev != 0) {
            value = rev * 0.001f * value;
        }
    }
    if (value > 999.0f) {
        value = 999.0f;
    }
    return value;
}

unsigned int DataObjEnemy::getLuck(bool) const {
    float value = m_sdata->m_luck;
    if (fn_7100229CEC(value, getBdatIdEnArrange(), 6, 16)) {
        float rate = GfDataBlade::getLuckRev(GfDataEnemy::getEquipBlade(getBdatIdEnArrange())) * 0.01f;
        value += value * rate;
    }
    if (m_sdata->m_paramId != 0) {
        unsigned int rev = GfBdatChrEnParam::sys()->getChrEnParamRevLuckRev(m_sdata->m_paramId);
        if (rev != 0) {
            value = rev * 0.001f * value;
        }
    }
    if (value > 999.0f) {
        value = 999.0f;
    }
    return value;
}

unsigned int DataObjEnemy::getPArmor(bool) const {
    float value = m_sdata->m_pArmor;
    if (GfDataEnemy::getEquipBlade(getBdatIdEnArrange()) != 0) {
        fn_7100229CEC(value, getBdatIdEnArrange(), 8, 18);
    }
    if (value > 100.0f) {
        value = 100.0f;
    }
    return value;
}

unsigned int DataObjEnemy::getEArmor(bool) const {
    float value = m_sdata->m_eArmor;
    if (GfDataEnemy::getEquipBlade(getBdatIdEnArrange()) != 0) {
        fn_7100229CEC(value, getBdatIdEnArrange(), 9, 19);
    }
    if (value > 100.0f) {
        value = 100.0f;
    }
    return value;
}

unsigned int DataObjEnemy::getCriticalRate(bool) const {
    float value = m_sdata->m_criticalRate;
    if (GfDataEnemy::getEquipBlade(getBdatIdEnArrange()) != 0) {
        fn_7100229CEC(value, getBdatIdEnArrange(), 7, 17);
    }
    if (value > 100.0f) {
        value = 100.0f;
    }
    return value;
}

unsigned int DataObjEnemy::getGuardRate(bool) const {
    float value = m_sdata->m_guardRate;
    if (GfDataEnemy::getEquipBlade(getBdatIdEnArrange()) != 0) {
        fn_7100229CEC(value, getBdatIdEnArrange(), 10, 20);
    }
    if (value > 100.0f) {
        value = 100.0f;
    }
    return value;
}

unsigned int DataObjEnemy::getFootStep() const {
    return GfBdatRsc::sys()->getRscEnFootStep(getBdatId());
}

unsigned int DataObjEnemy::getFootStepEffect() const {
    return GfBdatRsc::sys()->getRscEnFootStepEffect(getBdatId());
}

unsigned int DataObjEnemy::getBlade(bool, int) const {
    return GfDataEnemy::getEquipBlade(getBdatId());
}

unsigned int DataObjEnemy::getEquipWeapon(bool, int index) const {
    return m_sdata->m_equipWeapons[index];
}

unsigned int DataObjEnemy::getWeaponType(bool, int) const {
    unsigned int blade = GfDataEnemy::getEquipBlade(getBdatIdEnArrange());
    if (blade == 0) {
        return 0;
    }
    return GfDataBlade::getBladeWpnType(blade);
}

bool DataObjEnemy::isEnbaleTarget() const {
    if (GfBdatChrEnArrange::sys()->getChrEnArrangeBladeID(getBdatId()) != 0) {
        return false;
    }
    return !GfBdatChrEnArrange::sys()->isChrEnArrangeFlagNoTarget(getBdatId());
}

unsigned int DataObjEnemy::getChestHeight() const {
    return GfBdatRsc::sys()->getRscEnChestHeight(getBdatIdEnRsc());
}

const char* DataObjEnemy::getVoiceStr() const {
    return GfDataEnemy::getVoiceStr(getBdatIdEnArrange());
}

int DataObjEnemy::getMenuOffset() const {
    return GfBdatRsc::sys()->getRscEnoffsetID(getBdatIdEnRsc());
}

unsigned int DataObjEnemy::getBdatIdEnRsc() const {
    return GfBdatChrEnParam::sys()->getChrEnParamResourceID(getBdatIdEnParam());
}

unsigned int DataObjEnemy::getBdatIdEnParam() const {
    return GfBdatChrEnArrange::sys()->getChrEnArrangeParamID(getBdatIdEnArrange());
}

bool DataObjEnemy::isGuardFront() const {
    return m_sdata->m_guardFront;
}

bool DataObjEnemy::isGuardLeft() const {
    return m_sdata->m_guardLeft;
}

bool DataObjEnemy::isGuardRight() const {
    return m_sdata->m_guardRight;
}

bool DataObjEnemy::isGuardBack() const {
    return m_sdata->m_guardBack;
}

bool DataObjEnemy::isFieldDamage() const {
    return m_sdata->m_fieldDamage;
}

unsigned int DataObjEnemy::getResistancePower() const {
    return m_sdata->m_resistancePower;
}

unsigned int DataObjEnemy::getResistanceEther() const {
    return m_sdata->m_resistanceEther;
}

unsigned int DataObjEnemy::getResistanceCombo() const {
    return m_sdata->m_resistanceCombo;
}

unsigned int DataObjEnemy::getInvincibleCombo() const {
    return m_sdata->m_invincibleCombo;
}

unsigned int DataObjEnemy::getLevelGold() const {
    GfBdatBtl* btl = GfBdatBtl::sys();
    unsigned int level = getLevel(false);
    mm::clamp(level, btl->getGrowStart(), btl->getGrowEnd() - 1);
    return btl->getGrowEnemyGold(level) * static_cast<float>(m_sdata->m_goldRev) / 100.0f;
}

unsigned int DataObjEnemy::getLevelExp() const {
    GfBdatBtl* btl = GfBdatBtl::sys();
    unsigned int level = getLevel(false);
    mm::clamp(level, btl->getGrowStart(), btl->getGrowEnd() - 1);
    float value = btl->getGrowEnemyExp(level);
    return value * GfBdatChrEnArrange::sys()->getChrEnArrangeExpRev(getBdatId()) / 100.0f;
}

unsigned int DataObjEnemy::getLevelWp() const {
    GfBdatBtl* btl = GfBdatBtl::sys();
    unsigned int level = getLevel(false);
    mm::clamp(level, btl->getGrowStart(), btl->getGrowEnd() - 1);
    float value = btl->getGrowEnemyWP(level);
    return value * GfBdatChrEnArrange::sys()->getChrEnArrangeWPRev(getBdatId()) / 100.0f;
}

unsigned int DataObjEnemy::getLevelSp() const {
    GfBdatBtl* btl = GfBdatBtl::sys();
    unsigned int level = getLevel(false);
    mm::clamp(level, btl->getGrowStart(), btl->getGrowEnd() - 1);
    float value = btl->getGrowEnemySP(level);
    return value * GfBdatChrEnArrange::sys()->getChrEnArrangeSPRev(getBdatId()) / 100.0f;
}

unsigned int DataObjEnemy::getGenus() const {
    return m_sdata->m_genus;
}

bool DataObjEnemy::isLinkGenus() const {
    return m_sdata->m_linkGenus;
}

float DataObjEnemy::getLinkRadius() const {
    return m_sdata->m_linkRadius;
}

unsigned int DataObjEnemy::getGoldDivide() const {
    return GfBdatBtl::sys()->getGrowGoldDivide(getLevel(false));
}

unsigned int DataObjEnemy::getGoldDivideRev() const {
    return GfBdatRsc::sys()->getRscEnGoldDivideRev(m_sdata->m_rscId);
}

const SDataEnemy* DataObjEnemy::getSDataEnemy() const {
    return m_sdata;
}

bool DataObjEnemy::isDispInitExtraParts(unsigned int part) const {
    if (m_sdata != nullptr && m_sdata->m_extraPartsMask != 0 && (m_sdata->m_extraPartsMask & (1 << part)) != 0) {
        return true;
    }
    return GfDataEnemy::getExtraParts(m_sdata->m_rscId, part);
}

bool DataObjEnemy::isHideInitExtraParts(unsigned int part) const {
    return GfDataEnemy::isHideExtraParts(m_sdata->m_rscId, part);
}

bool DataObjEnemy::isNoCameraFade() const {
    return m_sdata->m_noCameraFade;
}

bool DataObjEnemy::isWeaponDrawDisp() const {
    return m_sdata->m_weaponDrawDisp;
}

const char* DataObjEnemy::getCenterBone() const {
    return GfBdatRsc::sys()->getRscEnCenterBone(getBdatIdEnRsc());
}

const char* DataObjEnemy::getCamBone() const {
    return GfBdatRsc::sys()->getRscEnCamBone(getBdatIdEnRsc());
}

unsigned int DataObjEnemy::getEyeRotControl() const {
    return GfBdatRsc::sys()->getRscEnEyeRot(getBdatIdEnRsc());
}

const char* DataObjEnemy::getRotateBone() const {
    return GfBdatRsc::sys()->getRscEnRotateBone(getBdatIdEnRsc());
}

DataObjEnemyBlade::~DataObjEnemyBlade() {}

const char* DataObjEnemyBlade::getName() const {
    return GfDataBlade::getName(m_setup->m_bladeId, 0);
}

bool DataObjEnemyBlade::getName(unsigned char*& bdat, unsigned int& id) const {
    return GfDataBlade::getName(bdat, id, m_setup->m_bladeId);
}

const char* DataObjEnemyBlade::getModelResourceName() const {
    return m_sdataBlade->m_modelName;
}

const char* DataObjEnemyBlade::getMotionResourceName() const {
    return m_sdataBlade->m_motionName;
}

const char* DataObjEnemyBlade::getEffectResourceName() const {
    return m_sdataBlade->m_effectName;
}

unsigned int DataObjEnemyBlade::getWeaponType(bool, int) const {
    return m_sdataBlade->m_weaponType;
}

unsigned int DataObjEnemyBlade::getPArmor(bool flag) const {
    unsigned int armor = m_sdataBlade->m_pArmor;
    GfBdatItem* item = GfBdatItem::sys();
    unsigned int weapon = getEquipWeapon(flag, -1);
    if (weapon != 0) {
        armor += item->getPcWpnPArmor(weapon);
    }
    return armor;
}

unsigned int DataObjEnemyBlade::getEArmor(bool flag) const {
    unsigned int armor = m_sdataBlade->m_eArmor;
    GfBdatItem* item = GfBdatItem::sys();
    unsigned int weapon = getEquipWeapon(flag, -1);
    if (weapon != 0) {
        armor += item->getPcWpnEArmor(weapon);
    }
    return armor;
}

unsigned int DataObjEnemyBlade::getCriticalRate(bool flag) const {
    GfBdatItem* item = GfBdatItem::sys();
    unsigned int weapon = getEquipWeapon(flag, -1);
    if (weapon != 0) {
        return item->getPcWpnCriRate(weapon);
    }
    return 0;
}

unsigned int DataObjEnemyBlade::getGuardRate(bool flag) const {
    GfBdatItem* item = GfBdatItem::sys();
    unsigned int weapon = getEquipWeapon(flag, -1);
    if (weapon != 0) {
        return item->getPcWpnGuardRate(weapon);
    }
    return 0;
}

unsigned int DataObjEnemyBlade::getWeaponDamage(bool flag) const {
    GfBdatItem* item = GfBdatItem::sys();
    unsigned int weapon = getEquipWeapon(flag, -1);
    if (weapon != 0) {
        return item->getPcWpnDamage(weapon);
    }
    return 0;
}

unsigned int DataObjEnemyBlade::getWeaponStability(bool flag) const {
    GfBdatItem* item = GfBdatItem::sys();
    unsigned int weapon = getEquipWeapon(flag, -1);
    if (weapon != 0) {
        return item->getPcWpnStability(weapon);
    }
    return 0;
}

unsigned int DataObjEnemyBlade::getEquipWeapon(bool, int) const {
    return m_sdataBlade->m_equipWeapon;
}

unsigned int DataObjEnemyBlade::getChestHeight() const {
    return m_sdataBlade->m_chestHeight;
}

unsigned int DataObjEnemyBlade::getLandingHeight() const {
    return m_sdataBlade->m_landingHeight;
}

unsigned int DataObjEnemyBlade::getIconData() const {
    return m_sdataBlade->m_iconData;
}

unsigned int DataObjEnemyBlade::getRace() const {
    return m_sdataBlade->m_race;
}

unsigned int DataObjEnemyBlade::getQuestRace() const {
    return GfDataBlade::getQuestRace(m_sdataBlade->m_bladeId);
}

unsigned int DataObjEnemyBlade::getGender() const {
    return m_sdataBlade->m_gender;
}

bool DataObjEnemyBlade::isDispInitExtraParts(unsigned int part) const {
    if (m_setup != nullptr && m_setup->m_sdata->m_extraPartsMask != 0) {
        return (m_setup->m_sdata->m_extraPartsMask & (1 << part)) != 0;
    }
    return m_sdataBlade->m_extraParts[part] != 0;
}

unsigned int DataObjEnemyBlade::getEyeRotControl() const {
    return m_sdataBlade->m_eyeRotControl;
}

unsigned int DataObjEnemyBlade::getBladeArts(bool, unsigned int index) const {
    return m_sdataBlade->m_arts[index].m_id;
}

unsigned int DataObjEnemyBlade::getBladeArtsLevel(bool, unsigned int index) const {
    return m_sdataBlade->m_arts[index].m_level;
}

unsigned int DataObjEnemyBlade::getBladeArtsH(bool, unsigned int index) const {
    return m_sdataBlade->m_arts[index].m_h;
}

unsigned int DataObjEnemyBlade::getBladeArtsN(bool, unsigned int index) const {
    return m_sdataBlade->m_nArts[index].m_id;
}

unsigned int DataObjEnemyBlade::getBladeArtsNH(bool, unsigned int index) const {
    return m_sdataBlade->m_nArts[index].m_h;
}

unsigned int DataObjEnemyBlade::getBladeArtsEx(bool) const {
    return m_sdataBlade->m_artsEx.m_id;
}

unsigned int DataObjEnemyBlade::getBladeArtsExH(bool) const {
    return m_sdataBlade->m_artsEx.m_h;
}

unsigned int DataObjEnemyBlade::getBladeArtsEx2(bool) const {
    return m_sdataBlade->m_artsEx2.m_id;
}

unsigned int DataObjEnemyBlade::getBladeArtsEx2H(bool) const {
    return m_sdataBlade->m_artsEx2.m_h;
}

unsigned int DataObjEnemyBlade::getPersonality() const {
    return m_sdataBlade->m_personality;
}

unsigned int DataObjEnemyBlade::getCoolTime() const {
    return m_sdataBlade->m_coolTime;
}

DataObjNpc::DataObjNpc(GF_OBJ_HANDLE* handle) : m_handle(handle), m_bdatId(0) {
    m_bdatId = mm::mtl::rttiCast<GfObjSetupNpc>(GfObjManager::getObjInfo(handle)->m_setup)->m_bdatId;
}

DataObjNpc::DataObjNpc(unsigned int id) : m_handle(reinterpret_cast<GF_OBJ_HANDLE*>(-1)), m_bdatId(id) {}

bool DataObjNpc::isValid() const {
    return m_bdatId != 0;
}

const char* DataObjNpc::getName() const {
    return GfDataNpc::getName(getBdatId());
}

bool DataObjNpc::getName(unsigned char*& bdat, unsigned int& id) const {
    return GfDataNpc::getName(bdat, id, getBdatId());
}

const char* DataObjNpc::getModelResourceName() const {
    return GfDataNpc::getModelName(getBdatId());
}

const char* DataObjNpc::getMotionResourceName() const {
    return GfDataNpc::getMotionName(getBdatId());
}

unsigned int DataObjNpc::getBdatId() const {
    return m_bdatId;
}

bool DataObjNpc::isDispInitExtraParts(unsigned int part) const {
    return GfDataNpc::getExtraParts(getBdatId(), part);
}

int DataObjNpc::getMenuOffset() const {
    return GfDataNpc::getOffsetID(getBdatId());
}

unsigned int DataObjNpc::getFootStep() const {
    return GfDataNpc::getFootStep(getBdatId());
}

unsigned int DataObjNpc::getFootStepEffect() const {
    return GfDataNpc::getFootStepEffect(getBdatId());
}

unsigned int DataObjNpc::getEyeRotControl() const {
    return GfDataNpc::getEyeRotControl(getBdatId());
}

DataObjMap::DataObjMap(GF_OBJ_HANDLE* handle) : m_handle(handle), m_bdatId(0) {
    m_bdatId = mm::mtl::rttiCast<GfObjSetupMap>(GfObjManager::getObjInfo(handle)->m_setup)->m_bdatId;
}

DataObjMap::DataObjMap(unsigned int id) : m_handle(reinterpret_cast<GF_OBJ_HANDLE*>(-1)), m_bdatId(id) {}

bool DataObjMap::isValid() const {
    return m_bdatId != 0;
}

const char* DataObjMap::getName() const {
    return GfBdatMaplist::sys()->getMaplistresource(getBdatId());
}

unsigned int DataObjMap::getBdatId() const {
    return m_bdatId;
}

DataObjMob::DataObjMob(GF_OBJ_HANDLE* handle) : m_handle(handle), m_bdatId(0) {
    m_bdatId = mm::mtl::rttiCast<GfObjSetupMob>(GfObjManager::getObjInfo(handle)->m_setup)->m_bdatId;
}

DataObjMob::DataObjMob(unsigned int id) : m_handle(reinterpret_cast<GF_OBJ_HANDLE*>(-1)), m_bdatId(id) {}

bool DataObjMob::isValid() const {
    return m_bdatId != 0;
}

const char* DataObjMob::getName() const {
    return GfDataMob::getName(getBdatId());
}

bool DataObjMob::getName(unsigned char*& bdat, unsigned int& id) const {
    return GfDataMob::getName(bdat, id, getBdatId());
}

const char* DataObjMob::getModelResourceName() const {
    return GfBdatRsc::sys()->getRscMobListModel(getBdatId());
}

const char* DataObjMob::getMotionResourceName() const {
    return GfBdatRsc::sys()->getRscMobListMotion(getBdatId());
}

unsigned int DataObjMob::getBdatId() const {
    return m_bdatId;
}

bool DataObjMob::isDispInitExtraParts(unsigned int part) const {
    return GfBdatRsc::sys()->getRscMobListExtraParts(getBdatId(), part) != 0;
}

int DataObjMob::getMenuOffset() const {
    return GfBdatRsc::sys()->getRscMobListOffsetID(getBdatId());
}

unsigned int DataObjMob::getFootStep() const {
    return GfDataMob::getFootStep(getBdatId());
}

unsigned int DataObjMob::getFootStepEffect() const {
    return GfDataMob::getFootStepEffect(getBdatId());
}

DataObjUiObj::DataObjUiObj(unsigned int id) : m_handle(reinterpret_cast<GF_OBJ_HANDLE*>(-1)), m_bdatId(id) {}

bool DataObjUiObj::isValid() const {
    return m_bdatId != 0;
}

const char* DataObjUiObj::getName() const {
    return GfDataMob::getName(getBdatId());
}

bool DataObjUiObj::getName(unsigned char*& bdat, unsigned int& id) const {
    return GfDataMob::getName(bdat, id, getBdatId());
}

const char* DataObjUiObj::getModelResourceName() const {
    return GfBdatRsc::sys()->getRscMobListModel(getBdatId());
}

const char* DataObjUiObj::getMotionResourceName() const {
    return GfBdatRsc::sys()->getRscMobListMotion(getBdatId());
}

unsigned int DataObjUiObj::getBdatId() const {
    return m_bdatId;
}

bool DataObjUiObj::isDispInitExtraParts(unsigned int) const {
    return false;
}

DataObjGmk::DataObjGmk(GF_OBJ_HANDLE* handle) : m_handle(handle), m_bdatId(0) {
    GfObjSetupGimmick* setup = mm::mtl::rttiCast<GfObjSetupGimmick>(GfObjManager::getObjInfo(handle)->m_setup);
    m_bdatId = setup->m_bdatId;
    m_gimmickType = setup->m_gimmickType;
}

DataObjGmk::DataObjGmk(unsigned int id, GimmickType type)
    : m_handle(reinterpret_cast<GF_OBJ_HANDLE*>(-1)), m_bdatId(id), m_gimmickType(type) {}

bool DataObjGmk::isValid() const {
    return m_bdatId != 0;
}

const char* DataObjGmk::getName() const {
    return "";
}

bool DataObjGmk::getName(unsigned char*&, unsigned int&) const {
    return false;
}

const char* DataObjGmk::getModelResourceName() const {
    if (m_gimmickType == 1) {
        return GfBdatRsc::sys()->getRSC_TboxListModel(getBdatId());
    }
    return GfBdatRsc::sys()->getRSC_MapObjListModel(getBdatId());
}

const char* DataObjGmk::getMotionResourceName() const {
    if (m_gimmickType == 1) {
        return GfBdatRsc::sys()->getRSC_TboxListMotion(getBdatId());
    }
    return GfBdatRsc::sys()->getRSC_MapObjListMotion(getBdatId());
}

unsigned int DataObjGmk::getBdatId() const {
    return m_bdatId;
}

bool DataObjGmk::isDispInitExtraParts(unsigned int) const {
    if (m_gimmickType == 1) {
        return false;
    }
    return GfBdatRsc::sys()->getRSC_MapObjListExtraParts1(getBdatId()) != 0;
}

bool DataObjBelonging::isValid() const {
    return m_handle != reinterpret_cast<GF_OBJ_HANDLE*>(-1);
}

const char* DataObjBelonging::getName() const {
    return "";
}

bool DataObjBelonging::getName(unsigned char*&, unsigned int&) const {
    return false;
}

const char* DataObjBelonging::getModelResourceName() const {
    return "";
}

const char* DataObjBelonging::getMotionResourceName() const {
    return "";
}

unsigned int DataObjBelonging::getBdatId() const {
    return 0;
}

}  // namespace gf

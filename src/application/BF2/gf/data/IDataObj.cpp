#include "classes/gf/IDataObj.h"
#include "classes/gf/DataObjPcWpn.h"
#include "classes/gf/DataObjEnemy.h"
#include "classes/gf/DataObjEnemyBlade.h"
#include "classes/gf/DataObjNpc.h"
#include "classes/gf/DataObjMap.h"
#include "classes/gf/DataObjMob.h"
#include "classes/gf/DataObjUiObj.h"
#include "classes/gf/DataObjGmk.h"
#include "classes/gf/DataObjBelonging.h"
#include "classes/gf/GfObjSetup.h"
#include "classes/gf/GfObjSetupGimmick.h"
#include "classes/gf/GfBdatItem.h"
#include "classes/gf/GfBdatRsc.h"
#include "classes/gf/GfBdatMaplist.h"
#include "gf/GfDataItem.h"
#include "gf/GfDataNpc.h"
#include "gf/GfDataMob.h"
#include "gf/GfDataEnemy.h"
#include "gf/GfDataBlade.h"
#include "gf/SDataEnemy.h"
#include "gf/SDataBlade.h"
#include "classes/gf/GfObjSetupEnemy.h"
#include "classes/gf/GfBdatChrEnParam.h"
#include "classes/gf/GfBdatChrEnArrange.h"
#include "classes/gf/GfBdatBtl.h"
#include "gf/GfObjUtil.h"
#include "classes/gf/GfObjSetup.h"
#include "classes/gf/GfObjSetupNpc.h"
#include "classes/gf/GfObjSetupMap.h"
#include "classes/gf/GfObjSetupMob.h"
#include "classes/gf/GfObjManager.h"
#include "gf/GfObjAcc.h"
#include "gf/GfObjInfo.h"
#include "mm/mtl/FixedVector.h"
#include "mm/Math.h"

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

bool DataObjEnemy::vf42(unsigned int part) const {
    return GfDataEnemy::fn_7100235424(m_sdata->m_rscId, part);
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

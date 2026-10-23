#include "classes/gf/GfAllocator.h"
#include "gf/GfObjAcc.h"
#include "classes/gf/IDataObj.h"
#include "classes/gf/DataObjDriver.h"
#include "classes/gf/DataObjBlade.h"
#include "gf/GfDataBlade.h"
#include "gf/GfDataDriver.h"
#include "gf/SDataBlade.h"
#include "gf/SDataDriver.h"
#include "gf/GfDataHana.h"
#include "gf/GfEquipUtil.h"
#include "classes/gf/GfBdatItem.h"
#include "classes/gf/DataParamAcc.h"
#include "gf/GfDataItem.h"
#include "classes/gf/GfEvent.h"

namespace gf {

inline void DataObjDriver::setup(unsigned int id) {
    m_bdatId = id;
    if (id != 0) {
        m_sdata = GfDataDriver::getSDataDriver(id);
        if (GfDataDriver::fn_710023F9A8(m_bdatId)) {
            m_dlc = GfDataDriver::fn_7100241BB4(m_bdatId);
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

bool DataObjDriver::isVirtualSetting() const {
    return m_virtual != nullptr;
}

int DataObjDriver::getMenuOffset() const {
    return GfDataDriver::fn_7100241CAC(getBdatId());
}

const char* DataObjDriver::getCenterBone() const {
    return GfDataDriver::fn_7100241CC4(getBdatId());
}

const char* DataObjDriver::getCamBone() const {
    return GfDataDriver::fn_7100241CDC(getBdatId());
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

unsigned int DataObjDriver::getClass(bool virtualParam) const {
    const SDataDriver* data = virtualParam ? m_sdata : GfDataDriver::getSDataDriver(getBdatId());
    return GfDataDriver::getClass(*data);
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

unsigned int DataObjBlade::getAutoHate(bool) const {
    if (GfDataHana::isValid(getBdatId())) {
        return GfDataHana::getAutoHate(getBdatId());
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

unsigned int DataObjBlade::getEquipWeapon(bool virtualParam, int) const {
    const SDataBlade* data = virtualParam ? m_sdata : GfDataBlade::getSDataBlade(getBdatId());
    return data->m_equipWeapon;
}

unsigned int DataObjBlade::getWeaponType(bool virtualParam, int) const {
    const SDataBlade* data = virtualParam ? m_sdata : GfDataBlade::getSDataBlade(getBdatId());
    return data->m_weaponType;
}

unsigned int DataObjDriver::getChestHeight() const {
    return GfDataDriver::fn_7100241C04(getBdatId());
}

unsigned int DataObjDriver::getLandingHeight() const {
    return GfDataDriver::fn_7100241C1C(getBdatId());
}

unsigned int DataObjDriver::getIconData() const {
    return GfDataDriver::fn_7100241C34(getBdatId());
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
    return GfDataDriver::fn_7100241C94(getBdatId());
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

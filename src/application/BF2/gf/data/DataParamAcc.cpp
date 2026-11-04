#include "classes/gf/DataParamAcc.h"
#include "classes/gf/IDataObj.h"
#include "classes/gf/DataObjMap.h"
#include "classes/gf/DataObjDriver.h"
#include "classes/gf/DataObjBlade.h"
#include "classes/gf/DataObjEnemy.h"
#include "classes/gf/DataObjEnemyBlade.h"
#include "classes/gf/DataObjNpc.h"
#include "classes/gf/DataObjMob.h"
#include "classes/gf/DataObjGmk.h"
#include "classes/gf/DataObjPcWpn.h"
#include "classes/gf/DataObjUiObj.h"
#include "classes/gf/DataObjBelonging.h"
#include "classes/gf/GfObj.h"
#include "classes/gf/GfObjManager.h"
#include "classes/gf/GfObjSetup.h"
#include "classes/gf/GfObjSetupEnemy.h"
#include "classes/ml/fixed_size_alloc_inside.h"
#include "gf/GfObjInfo.h"
#include "gf/GfObjUtil.h"
#include "gf/ParamObj.h"
#include "gf/SDataBlade.h"
#include "mm/mtl/RTTI.h"
#include <new>

namespace gf {
namespace _gfdac {
// room for any one IDataObj (the largest is 0x90 bytes; the name of the field is not the original's)
struct ACCMEM {
    unsigned long m_mem[0x90 / 8];
};

// the IDataObjs of the DataParamAccs alive at a time
ml::fixed_size_alloc_inside<ACCMEM, 128> s_accbuf;

// an enemy's setup when its info holds one of its own kind (5). setupObjHandle asks it of an enemy blade and keeps
// nothing (1.0.0 does the same); inline, the name is not the original's
inline GfObjSetupEnemy* getEnemySetup(GF_OBJ_HANDLE* handle) {
    GFOBJ_INFO* info = GfObjManager::getObjInfo(handle);
    if (info != nullptr && info->m_setup != nullptr && info->m_setup->m_type == info->m_obj->m_type &&
        info->m_obj->m_type == 5) {
        return mm::mtl::rttiCast<GfObjSetupEnemy>(info->m_setup);
    }
    return nullptr;
}
}  // namespace _gfdac

DataParamAcc::DataParamAcc(const ParamObj& obj) {
    if (obj.m_handle != reinterpret_cast<GF_OBJ_HANDLE*>(-1)) {
        setupObjHandle(obj.m_handle);
    } else {
        setupObjId(obj.m_type, obj.m_id, static_cast<GimmickType>(0));
    }
}

void DataParamAcc::setupObjHandle(GF_OBJ_HANDLE* handle) {
    m_obj = nullptr;
    m_handle = handle;
    _gfdac::ACCMEM* mem = _gfdac::s_accbuf.allocate();
    switch (GfObjUtil::getObjType(handle)) {
    case 1:
        new (mem) DataObjMap(handle);
        break;
    case 3:
        new (mem) DataObjDriver(handle);
        break;
    case 4:
        new (mem) DataObjBlade(handle);
        break;
    case 5:
        if (GfObjUtil::isEnemyBlade(handle)) {
            _gfdac::getEnemySetup(handle);
            new (mem) DataObjEnemyBlade(handle);
        } else {
            new (mem) DataObjEnemy(handle);
        }
        break;
    case 6:
        new (mem) DataObjNpc(handle);
        break;
    case 7:
        new (mem) DataObjMob(handle);
        break;
    case 8:
        new (mem) DataObjGmk(handle);
        break;
    case 10:
        new (mem) DataObjPcWpn(handle);
        break;
    case 13:
        new (mem) DataObjBelonging(handle);
        break;
    default:
        _gfdac::s_accbuf.deallocate(mem);
        return;
    }
    m_obj = reinterpret_cast<IDataObj*>(mem);
}

void DataParamAcc::setupObjId(unsigned int type, unsigned int id, GimmickType gimmick) {
    m_obj = nullptr;
    _gfdac::ACCMEM* mem = _gfdac::s_accbuf.allocate();
    switch (type) {
    case 1:
        new (mem) DataObjMap(id);
        break;
    case 3:
        new (mem) DataObjDriver(id);
        break;
    case 4:
        new (mem) DataObjBlade(id);
        break;
    case 5:
        new (mem) DataObjEnemy(id);
        break;
    case 6:
        new (mem) DataObjNpc(id);
        break;
    case 7:
        new (mem) DataObjMob(id);
        break;
    case 8:
        new (mem) DataObjGmk(id, gimmick);
        break;
    case 10:
        new (mem) DataObjPcWpn(id);
        break;
    case 15:
        new (mem) DataObjUiObj(id);
        break;
    default:
        _gfdac::s_accbuf.deallocate(mem);
        return;
    }
    m_obj = reinterpret_cast<IDataObj*>(mem);
}

DataParamAcc::DataParamAcc(GF_OBJ_HANDLE* handle) {
    setupObjHandle(handle);
}

DataParamAcc::DataParamAcc(unsigned int type, unsigned int id, GimmickType gimmick) {
    setupObjId(type, id, gimmick);
}

DataParamAcc::~DataParamAcc() {
    if (m_obj != nullptr) {
        m_obj->~IDataObj();
        _gfdac::s_accbuf.deallocate(reinterpret_cast<_gfdac::ACCMEM*>(m_obj));
        m_obj = nullptr;
    }
}

bool DataParamAcc::isValid() const {
    if (m_obj != nullptr) {
        return m_obj->isValid();
    }
    return false;
}

unsigned int DataParamAcc::getObjType() const {
    if (isValid()) {
        return m_obj->getObjType();
    }
    return 0;
}

const char* DataParamAcc::getModelResourceName() const {
    if (isValid()) {
        return m_obj->getModelResourceName();
    }
    return nullptr;
}

const char* DataParamAcc::getMotionResourceName() const {
    if (isValid()) {
        return m_obj->getMotionResourceName();
    }
    return nullptr;
}

const char* DataParamAcc::getEffectResourceName() const {
    if (isValid()) {
        return m_obj->getEffectResourceName();
    }
    return nullptr;
}

const char* DataParamAcc::getName() const {
    if (isValid()) {
        const char* name = m_obj->getName();
        return name == nullptr ? "" : name;
    }
    return "";
}

const char* DataParamAcc::getVoiceStr() const {
    if (isValid()) {
        if (const char* voice = m_obj->getVoiceStr()) {
            return voice;
        }
        return "";
    }
    return "";
}

unsigned int DataParamAcc::getBdatId() const {
    if (isValid()) {
        return m_obj->getBdatId();
    }
    return 0;
}

unsigned int DataParamAcc::getHp() const {
    if (isValid()) {
        return m_obj->getHp();
    }
    return 0;
}

unsigned int DataParamAcc::getLevel(bool flag) const {
    if (isValid()) {
        return m_obj->getLevel(flag);
    }
    return 0;
}

unsigned int DataParamAcc::getExp() const {
    if (isValid()) {
        return m_obj->getExp();
    }
    return 0;
}

unsigned int DataParamAcc::getBattleExp() const {
    if (isValid()) {
        return m_obj->getBattleExp();
    }
    return 0;
}

unsigned int DataParamAcc::getExpNext(bool flag) const {
    if (isValid()) {
        return m_obj->getExpNext(flag);
    }
    return 0;
}

unsigned int DataParamAcc::getWeaponPoint(unsigned int index) const {
    if (isValid()) {
        return m_obj->getWeaponPoint(index);
    }
    return 0;
}

void DataParamAcc::addWeaponPoint(unsigned int index, int value) {
    if (isValid()) {
        m_obj->addWeaponPoint(index, value);
    }
}

unsigned int DataParamAcc::getSkillPoint() const {
    if (isValid()) {
        return m_obj->getSkillPoint();
    }
    return 0;
}

unsigned int DataParamAcc::fn_71002208A4(unsigned int index, unsigned int index2, unsigned int index3) const {
    if (isValid()) {
        return m_obj->getDriverArts(index, index2, index3);
    }
    return 0;
}

bool DataParamAcc::setDriverArts(unsigned int index, int value, unsigned int index2) {
    if (isValid()) {
        return m_obj->setDriverArts(index, value, index2);
    }
    return false;
}

unsigned int DataParamAcc::getDriverArtsLevel(unsigned int index) const {
    if (isValid()) {
        return m_obj->getDriverArtsLevel(index);
    }
    return 0;
}

void DataParamAcc::setDriverArtsLevel(unsigned int index, unsigned int index2) {
    if (isValid()) {
        m_obj->setDriverArtsLevel(index, index2);
    }
}

unsigned int DataParamAcc::getHpMax(bool flag) const {
    if (isValid()) {
        return m_obj->getHpMax(flag);
    }
    return 0;
}

unsigned int DataParamAcc::getStrength(bool flag) const {
    if (isValid()) {
        return m_obj->getStrength(flag);
    }
    return 0;
}

unsigned int DataParamAcc::getPowerEther(bool flag) const {
    if (isValid()) {
        return m_obj->getPowerEther(flag);
    }
    return 0;
}

unsigned int DataParamAcc::getDex(bool flag) const {
    if (isValid()) {
        return m_obj->getDex(flag);
    }
    return 0;
}

unsigned int DataParamAcc::getAgility(bool flag) const {
    if (isValid()) {
        return m_obj->getAgility(flag);
    }
    return 0;
}

unsigned int DataParamAcc::getLuck(bool flag) const {
    if (isValid()) {
        return m_obj->getLuck(flag);
    }
    return 0;
}

unsigned int DataParamAcc::getPArmor(bool flag) const {
    if (isValid()) {
        return m_obj->getPArmor(flag);
    }
    return 0;
}

unsigned int DataParamAcc::getEArmor(bool flag) const {
    if (isValid()) {
        return m_obj->getEArmor(flag);
    }
    return 0;
}

unsigned int DataParamAcc::getCriticalRate(bool flag) const {
    if (isValid()) {
        return m_obj->getCriticalRate(flag);
    }
    return 0;
}

unsigned int DataParamAcc::getGuardRate(bool flag) const {
    if (isValid()) {
        return m_obj->getGuardRate(flag);
    }
    return 0;
}

unsigned int DataParamAcc::getAutoHate(bool flag) const {
    if (isValid()) {
        return m_obj->getAutoHate(flag);
    }
    return 0;
}

unsigned int DataParamAcc::getArtsHate(bool flag) const {
    if (isValid()) {
        return m_obj->getArtsHate(flag);
    }
    return 0;
}

unsigned int DataParamAcc::getWeaponDamage(bool flag) const {
    if (isValid()) {
        return m_obj->getWeaponDamage(flag);
    }
    return 0;
}

unsigned int DataParamAcc::getWeaponStability(bool flag) const {
    if (isValid()) {
        return m_obj->getWeaponStability(flag);
    }
    return 0;
}

unsigned int DataParamAcc::getChestHeight() const {
    if (isValid()) {
        return m_obj->getChestHeight();
    }
    return 0;
}

unsigned int DataParamAcc::getLandingHeight() const {
    if (isValid()) {
        return m_obj->getLandingHeight();
    }
    return 0;
}

int DataParamAcc::getIconData() const {
    if (isValid()) {
        return m_obj->getIconData();
    }
    return 0;
}

unsigned int DataParamAcc::getQuestRace() const {
    if (isValid()) {
        return m_obj->getQuestRace();
    }
    return 1;
}

unsigned int DataParamAcc::getGender() const {
    if (isValid()) {
        return m_obj->getGender();
    }
    return 0;
}

unsigned int DataParamAcc::getAttribute(int value, bool flag) const {
    if (isValid()) {
        return m_obj->getAttribute(flag, value);
    }
    return 0;
}

bool DataParamAcc::isDispInitExtraParts(unsigned int index) const {
    if (isValid()) {
        return m_obj->isDispInitExtraParts(index);
    }
    return true;
}

bool DataParamAcc::isHideInitExtraParts(unsigned int index) const {
    if (isValid()) {
        return m_obj->isHideInitExtraParts(index);
    }
    return true;
}

bool DataParamAcc::isScenarioMask() const {
    if (isValid()) {
        return m_obj->isScenarioMask();
    }
    return false;
}

unsigned int DataParamAcc::getRole(bool flag) const {
    if (isValid()) {
        return m_obj->getRole();
    }
    return 0;
}

int DataParamAcc::getMenuOffset() const {
    if (isValid()) {
        return m_obj->getMenuOffset();
    }
    return 0;
}

unsigned int DataParamAcc::getFootStep() const {
    if (isValid()) {
        return m_obj->getFootStep();
    }
    return 0;
}

unsigned int DataParamAcc::getEyeRotControl() const {
    if (isValid()) {
        return m_obj->getEyeRotControl();
    }
    return 0;
}

const char* DataParamAcc::getRotateBone() const {
    if (isValid()) {
        return m_obj->getRotateBone();
    }
    return nullptr;
}

unsigned int DataParamAcc::getPersonality() const {
    if (isValid()) {
        return m_obj->getPersonality();
    }
    return 0;
}

unsigned int DataParamAcc::getCoolTime() const {
    if (isValid()) {
        return m_obj->getCoolTime();
    }
    return 0;
}

unsigned int DataParamAcc::getNorAtkDmgMin(bool flag) const {
    if (isValid()) {
        return m_obj->getNorAtkDmgMin(flag);
    }
    return 0;
}

unsigned int DataParamAcc::getNorAtkDmgMax(bool flag) const {
    if (isValid()) {
        return m_obj->getNorAtkDmgMax(flag);
    }
    return 0;
}

unsigned int DataParamAcc::getEquipAcce(unsigned int index, bool flag) const {
    if (isValid()) {
        return m_obj->getEquipAcce(index, flag);
    }
    return 0;
}

int DataParamAcc::getBladeSet(bool flag) const {
    if (isValid()) {
        return m_obj->getBladeSet(flag);
    }
    return -1;
}

void DataParamAcc::setBladeSet(int value) {
    if (isValid()) {
        m_obj->setBladeSet(value);
    }
}

unsigned int DataParamAcc::getBlade(int value, bool flag) const {
    if (isValid()) {
        return m_obj->getBlade(flag, value);
    }
    return 0;
}

unsigned int DataParamAcc::getClass(bool flag) const {
    if (isValid()) {
        return m_obj->getClass(flag);
    }
    return 0;
}

unsigned int DataParamAcc::getEquipWeapon(int value, bool flag) const {
    if (isValid()) {
        return m_obj->getEquipWeapon(flag, value);
    }
    return 0;
}

unsigned int DataParamAcc::getWeaponType(int value, bool flag) const {
    if (isValid()) {
        return m_obj->getWeaponType(flag, value);
    }
    return 0;
}

unsigned int DataParamAcc::getBladePower(bool flag) const {
    if (isValid()) {
        return m_obj->getBladePower(flag);
    }
    return 0;
}

unsigned int DataParamAcc::getBladeArts(unsigned int index, bool flag) const {
    if (isValid()) {
        return m_obj->getBladeArts(flag, index);
    }
    return 0;
}

unsigned int DataParamAcc::getBladeArtsEnhance(unsigned int index, bool flag) const {
    if (isValid()) {
        return m_obj->getBladeArtsEnhance(flag, index);
    }
    return 0;
}

unsigned int DataParamAcc::getBladeArtsLevel(unsigned int index, bool flag) const {
    if (isValid()) {
        return m_obj->getBladeArtsLevel(flag, index);
    }
    return 0;
}

unsigned int DataParamAcc::getBladeArtsN(unsigned int index, bool flag) const {
    if (isValid()) {
        return m_obj->getBladeArtsN(flag, index);
    }
    return 0;
}

unsigned int DataParamAcc::getBladeArtsNH(unsigned int index, bool flag) const {
    if (isValid()) {
        return m_obj->getBladeArtsNH(flag, index);
    }
    return 100;
}

unsigned int DataParamAcc::getBladeSkill(unsigned int index, bool flag) const {
    if (isValid()) {
        return m_obj->getBladeSkill(flag, index);
    }
    return 0;
}

unsigned int DataParamAcc::getBladeSkillLevel(unsigned int index, bool flag) const {
    if (isValid()) {
        return m_obj->getBladeSkillLevel(flag, index);
    }
    return 0;
}

unsigned int DataParamAcc::getFieldSkill(unsigned int index, bool flag) const {
    if (isValid()) {
        return m_obj->getFieldSkill(flag, index);
    }
    return 0;
}

unsigned int DataParamAcc::getFieldSkillLevel(unsigned int index, bool flag) const {
    if (isValid()) {
        return m_obj->getFieldSkillLevel(flag, index);
    }
    return 0;
}

unsigned int DataParamAcc::getBladeArtsH(unsigned int index, bool flag) const {
    if (isValid()) {
        return m_obj->getBladeArtsH(flag, index);
    }
    return 100;
}

unsigned int DataParamAcc::getBladeArtsEx(bool flag) const {
    if (isValid()) {
        return m_obj->getBladeArtsEx(flag);
    }
    return 0;
}

unsigned int DataParamAcc::getBladeArtsExH(bool flag) const {
    if (isValid()) {
        return m_obj->getBladeArtsExH(flag);
    }
    return 100;
}

unsigned int DataParamAcc::getBladeArtsEx2(bool flag) const {
    if (isValid()) {
        return m_obj->getBladeArtsEx2(flag);
    }
    return 0;
}

unsigned int DataParamAcc::getBladeArtsEx2H(bool flag) const {
    if (isValid()) {
        return m_obj->getBladeArtsEx2H(flag);
    }
    return 100;
}

void DataParamAcc::setVirtualEquipAcc(unsigned int index, unsigned int index2) {
    if (isValid()) {
        m_obj->setVirtualEquipAcc(index, index2);
    }
}

void DataParamAcc::setVirtualSetBlade(unsigned int index, int value) {
    if (isValid()) {
        m_obj->setVirtualSetBlade(index, value);
    }
}

void DataParamAcc::setVirtualEquipWpnChip(unsigned int index) {
    if (isValid()) {
        m_obj->setVirtualEquipWpnChip(index);
    }
}

void DataParamAcc::setVirtualEquipOrb(unsigned int index, unsigned int index2) {
    if (isValid()) {
        m_obj->setVirtualEquipOrb(index, index2);
    }
}

void DataParamAcc::setVirtualEquipWpnAcce(unsigned int index) {
    if (isValid()) {
        m_obj->setVirtualEquipWpnAcce(index);
    }
}

void DataParamAcc::setMenuParam() {
    if (isValid()) {
        m_obj->setMenuParam();
    }
}

unsigned int DataParamAcc::getBdatIdEnParam() const {
    if (isValid()) {
        return m_obj->getBdatIdEnParam();
    }
    return 0;
}

unsigned int DataParamAcc::getResistancePower() const {
    if (isValid()) {
        return m_obj->getResistancePower();
    }
    return 0;
}

unsigned int DataParamAcc::getResistanceEther() const {
    if (isValid()) {
        return m_obj->getResistanceEther();
    }
    return 0;
}

unsigned int DataParamAcc::getLevelGold() const {
    if (isValid()) {
        return m_obj->getLevelGold();
    }
    return 0;
}

unsigned int DataParamAcc::getLevelExp() const {
    if (isValid()) {
        return m_obj->getLevelExp();
    }
    return 0;
}

unsigned int DataParamAcc::getLevelWp() const {
    if (isValid()) {
        return m_obj->getLevelWp();
    }
    return 0;
}

unsigned int DataParamAcc::getLevelSp() const {
    if (isValid()) {
        return m_obj->getLevelSp();
    }
    return 0;
}

unsigned int DataParamAcc::getGenus() const {
    if (isValid()) {
        return m_obj->getGenus();
    }
    return 0;
}

bool DataParamAcc::isLinkGenus() const {
    if (isValid()) {
        return m_obj->isLinkGenus();
    }
    return false;
}

float DataParamAcc::getLinkRadius() const {
    if (isValid()) {
        return m_obj->getLinkRadius();
    }
    return 0.0f;
}

unsigned int DataParamAcc::getGoldDivide() const {
    if (isValid()) {
        return m_obj->getGoldDivide();
    }
    return 0;
}

unsigned int DataParamAcc::getGoldDivideRev() const {
    if (isValid()) {
        return m_obj->getGoldDivideRev();
    }
    return 0;
}

const SDataEnemy* DataParamAcc::getSDataEnemy() const {
    if (isValid()) {
        return m_obj->getSDataEnemy();
    }
    return nullptr;
}

void DataParamAcc::setVirtualLevel(unsigned int index) {
    if (isValid()) {
        m_obj->setVirtualLevel(index);
    }
}

bool DataParamAcc::isEnbaleTarget() const {
    if (isValid()) {
        return m_obj->isEnbaleTarget();
    }
    return true;
}

bool DataParamAcc::isNoCameraFade() const {
    if (isValid()) {
        return m_obj->isNoCameraFade();
    }
    return false;
}

bool DataParamAcc::isWeaponDrawDisp() const {
    if (isValid()) {
        return m_obj->isWeaponDrawDisp();
    }
    return false;
}

const char* DataParamAcc::getCenterBone() const {
    if (isValid()) {
        return m_obj->getCenterBone();
    }
    return nullptr;
}

const char* DataParamAcc::getCamBone() const {
    if (isValid()) {
        return m_obj->getCamBone();
    }
    return nullptr;
}

DataIdeaAcc::DataIdeaAcc(DataParamAcc& acc) {
    m_idea = const_cast<SDataIdea*>(acc.m_obj->getIdea());
    m_isBlade = false;
    if (m_idea != nullptr) {
        m_isBlade = acc.getObjType() == 4;
    }
}

DataIdeaAcc::DataIdeaAcc(SDataIdea& idea, bool isBlade) {
    m_idea = &idea;
    m_isBlade = isBlade;
}

unsigned int DataIdeaAcc::getLevel(unsigned int idea) const {
    if (m_idea != nullptr) {
        return m_idea->m_ideas[idea].m_level;
    }
    return 0;
}

unsigned int DataIdeaAcc::addPoint(unsigned int idea, unsigned int point) {
    if (m_idea != nullptr) {
        m_idea->setPoint(idea, m_idea->m_ideas[idea].m_point + point);
    }
    return 0;
}
}  // namespace gf

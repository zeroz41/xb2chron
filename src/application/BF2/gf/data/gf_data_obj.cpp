#include "classes/gf/IDataObj.h"
#include "classes/gf/DataObjBlade.h"
#include "gf/GfDataBlade.h"
#include "gf/SDataBlade.h"

namespace gf {

bool DataObjBlade::isEnbaleTarget() const {
    return false;
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

unsigned int DataObjBlade::getRole() const {
    return GfDataBlade::getRole(getBdatId());
}

const char* DataObjBlade::getVoiceStr() const {
    return GfDataBlade::getVoiceStr(getBdatId());
}

unsigned int DataObjBlade::getBlade(bool, int) const {
    return getBdatId();
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

bool DataObjBlade::isVirtualSetting() const {
    return m_virtual != nullptr;
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

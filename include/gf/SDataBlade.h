#ifndef GF_SDATABLADE_H
#define GF_SDATABLADE_H

#include "gf/GfDataBlade.h"
#include "gf/GfDataHana.h"
#include "mm/mtl/FixedArray.h"

namespace gf {
// what DataObjBlade::getIdea and DataObjDriver::getIdea point at (an SDataBlade's +0xC, an SDataDriver's start);
// at most 0x20 bytes (SDataDriver's +0x20 is its data type). The type name is not the original's.
struct SDataIdea {
    // one of the four ideas (the struct and field names are not the original's): DataIdeaAcc::getLevel reads the
    // level, addPoint the point
    struct Idea {
        unsigned int m_point;
        unsigned int m_level;
    };
    void setPoint(unsigned int idea, unsigned int point);
    void setLevel(unsigned int idea, int level);  // the point becomes GfBdatBlade's need for levels 0-10, else 0

    Idea m_ideas[4];
};

// one of a blade's arts (the name is not the original's)
struct BladeArtsSlot {
    unsigned short m_id;  // getBladeArts, getBladeArtsN, getBladeArtsEx...
    unsigned short m_h;  // getBladeArtsH, getBladeArtsNH, getBladeArtsExH...
    unsigned char pad_4[0x2];
    unsigned char m_releaseLevel;  // GfDataBlade::getAchievReleaseLevel (named after it; the name is not the original's)
    unsigned char m_level;  // getBladeArtsLevel
    unsigned char pad_8[0x4];
};

// one of a blade's skills (the name is not the original's)
struct BladeSkillSlot {
    unsigned short m_id;  // getBladeSkill, getFieldSkill
    unsigned char m_releaseLevel;  // GfDataBlade::getAchievReleaseLevel (named after it; the name is not the original's)
    unsigned char m_level;  // getBladeSkillLevel, getFieldSkillLevel
    unsigned char pad_4[0x2];
};

// no table: one of a blade's two favorites (GfDataBlade::getFavorite, isUsedFavorite; the names are not the original's)
struct BladeFavorite {
    unsigned short m_category;  // getFavorite for FAVORITE 0 and 1
    unsigned short m_item;  // getFavorite for FAVORITE 2 and 3
    unsigned short m_categoryUsed;  // isUsedFavorite for FAVORITE 0 and 1
    unsigned short m_itemUsed;  // isUsedFavorite for FAVORITE 2 and 3
};

// no table: a blade's data (GfDataBlade::getSDataBlade's). The field names are not the original's: each says what
// the DataObjBlade or DataObjEnemyBlade accessor that reads it returns; the layout past them is not known.
// 0x8A4 bytes (DataObjBlade::setupVirtualParam allocates one)
class SDataBlade {
public:
    SDataBlade();
    SDataBlade& operator=(const SDataBlade& other);

    unsigned short m_dataType;  // DataObjBlade::getDataType
    unsigned short m_creator;  // GfDataBlade::getCreator (named after its accessor; the name is not the original's)
    unsigned short m_setDriver;  // the driver it is set to, 0 for none (GfDataBlade::getSetDriver)
    unsigned short m_bladeId;  // its blade row (GfDataBlade::getQuestRace takes it)
    unsigned int m_bornTime;  // (named after its accessor; the name is not the original's)
    SDataIdea m_idea;  // DataObjBlade::getIdea points at it
    unsigned char pad_2c[0x8];
    unsigned int m_trustPoint;  // (named after its accessor; the name is not the original's)
    unsigned int m_trustRank;  // (named after its accessor; the name is not the original's)
    BladeArtsSlot m_arts[3];  // getBladeArts...
    BladeArtsSlot m_nArts[3];  // getBladeArtsN...
    BladeArtsSlot m_artsEx;  // getBladeArtsEx
    BladeArtsSlot m_artsEx2;  // getBladeArtsEx2
    BladeSkillSlot m_skills[3];  // getBladeSkill...
    BladeSkillSlot m_fieldSkills[3];  // getFieldSkill...
    // DataObjEnemyBlade::isDispInitExtraParts, by part (DataObjBlade::isDispInitExtraParts asks parts 0 to 3)
    unsigned char m_extraParts[4];
    AchievInfo m_artsAchievement[3];  // getArtsAchievement, by line
    AchievInfo m_skillAchievement[3];  // getSkillAchievement, by line
    AchievInfo m_fieldSkillAchievement[3];  // getFieldSkillAchievement, by line
    AchievInfo m_keyAchievement;  // getKeyAchievement
    unsigned short m_keyLevel;  // DataObjDriver::getKeyLevel
    // GfDataBlade::getFavorite / isUsedFavorite: FAVORITE 0 and 1 read entry 0 and 1's category, 2 and 3 entry 0 and
    // 1's item
    BladeFavorite m_favorites[2];
    unsigned char pad_676[0x2];
    mm::mtl::FixedArray<unsigned short, 3> m_equipOrbs;  // DataObjBlade::setVirtualEquipOrb sets one, by slot; three slots (GfDataBlade::getEquipOrb(FixedArray<unsigned short, 3>&) copies them)
    unsigned char pad_67e[0x2];
    // 0x680: the item handles of the equipped orbs, by slot (GfDataBlade::getEquipOrbHandle/setEquipOrbHandle; the name is
    // not the original's)
    unsigned int m_equipOrbHandles[3];
    EquipHana m_equipHana;  // Hana's equipment (GfDataHana::getEquipParts; the name is not the original's)
    // 0x704: Hana's equipment power rank (GfDataHana::getEquipPowerRank/setEquipPowerRank; the name is not the
    // original's)
    unsigned short m_hanaPowerRank;
    unsigned short m_openCircuit;  // Hana's opened circuits, one bit each (GfDataHana::isOpenCircuit; the name is not the original's)
    unsigned char m_race;
    unsigned char m_gender;
    unsigned short m_iconData;
    char m_modelName[0x14];  // getModelResourceName; the length is the distance to the next
    // the model GfGameUtil::getBladeModel gives while isCondBladeModel holds, when m_hasCondModel is set (the names
    // are not the original's; the length is the distance to the next)
    char m_condModelName[0x10];
    int m_hasCondModel;
    char m_motionName[0x14];  // getMotionResourceName; the length is the distance to the next
    // the same for the motion (GfGameUtil::getBladeMotion; the names are not the original's)
    char m_condMotionName[0x10];
    int m_hasCondMotion;
    char m_addMotionName[0x14];  // GfDataBlade::getResourceNameAddMotion; the length is the distance to the next
    char m_voiceStr[0x1C];  // GfDataBlade::getVoiceStr; the length is the distance to the next
    unsigned char m_bladeLock;  // GfDataBlade::isBladeLock/setBladeLock (named after them)
    // a byte only Hana's forms use (GfDataHana::getMercenaryUnuse/setMercenaryUnuse; GfGameMercenaries::addTeamMember sets
    // it). The name is not the original's.
    unsigned char m_hanaTeamFlag;
    unsigned char pad_78e[0x1E];
    char m_effectName[0x28];  // getEffectResourceName; the length is not known
    char m_centerBone[0x14];  // getCenterBone; the length is the distance to the next
    char m_camBone[0x14];  // getCamBone; the length is the distance to the next
    char m_seName[0x24];  // getSeResourceName, GfDataBlade::getSePack; the length is the distance to the next
    unsigned char m_size;  // (named after its accessor; the name is not the original's)
    unsigned char m_weaponType;
    unsigned char m_equipOrbMax;  // (named after its accessor; the name is not the original's)
    // the blade's attribute (element) as the menus show it (GfMenuObjUtil::getBladeAttributeID reads it; the name
    // is not the original's)
    unsigned char m_attribute;
    unsigned char m_personality;
    unsigned char pad_825[0x1];
    unsigned char m_eyeRotControl;
    unsigned char pad_827[0x1];
    unsigned short m_coolTime;
    // the game condition under which the blade shows its alternate model (GfGameUtil::isCondBladeModel; the name
    // is not the original's)
    unsigned short m_modelCondition;
    unsigned short m_equipWeapon;  // its weapon (DataObjPcWpn::getBladeSet compares it with the weapon's row)
    unsigned short m_chestHeight;
    unsigned short m_landingHeight;
    // its name's row: in message table 423 (GfDataBdat::getFP), else m_nameMsgAlt's in table 396 (GfDataBlade::getName;
    // the names are not the original's)
    unsigned short m_nameMsg;
    unsigned short m_nameMsgAlt;
    unsigned short m_scale;  // percent (GfDataBlade::getScale; the name is not the original's)
    unsigned short m_wpnScale;  // percent (GfDataBlade::getWpnScale; the name is not the original's)
    unsigned short m_offsetId;  // (named after its accessor; the name is not the original's)
    unsigned short m_collisionId;  // (named after GfDataNpc::getCollisionId; the name is not the original's)
    unsigned char m_pArmor;  // added to its weapon's (DataObjEnemyBlade::getPArmor)
    unsigned char m_eArmor;  // added to its weapon's (DataObjEnemyBlade::getEArmor)
    unsigned char m_hpMaxRev;  // (named after GfDataBlade::getHpMaxRev; the name is not the original's)
    unsigned char m_strengthRev;  // (named after GfDataBlade::getStrengthRev; the name is not the original's)
    unsigned char m_powerEtherRev;  // (named after GfDataBlade::getPowerEtherRev; the name is not the original's)
    unsigned char m_dexRev;  // (named after GfDataBlade::getDexRev; the name is not the original's)
    unsigned char m_agilityRev;  // (named after GfDataBlade::getAgilityRev; the name is not the original's)
    unsigned char m_luckRev;  // (named after GfDataBlade::getLuckRev; the name is not the original's)
    unsigned char m_questRace;  // GfDataBlade::getQuestRace; 2 for an animal (isAnimal; the name is not the original's)
    unsigned char m_releaseLock;  // (named after its accessor; the name is not the original's)
    unsigned char m_footStep;  // (named after its accessor; the name is not the original's)
    unsigned char m_footStepEffect;  // (named after its accessor; the name is not the original's)
    // its BTL_Bl_KizunaLinkSet row (GfDataBlade::getLinkChNum passes it to GfBdatBtl::getBTL_Bl_KizunaLinkSetLinkChNum;
    // the name is not the original's)
    unsigned short m_kizunaLinkSet;
    unsigned short m_normalTalk;  // (named after its accessor; the name is not the original's)
    unsigned char pad_84e[0x2];
    unsigned int m_createEvent;  // (named after its accessor; the name is not the original's)
    unsigned char pad_854[0x4];
    // the name GfDataBlade::getDebugName returns while m_hasDebugName is set (the names are not the original's)
    char m_debugName[0x40];
    unsigned int m_hasDebugName;
    unsigned char pad_89c[0x2];
    unsigned char m_enableEngageRex;  // (named after its accessor; the name is not the original's)
    // non-zero when attached to the party (isAttachedParty), 2 for a released rare blade (isReleasedRareBlade);
    // the name is not the original's
    unsigned char m_attachedParty;
    unsigned char m_unselect;  // (named after its accessor; the name is not the original's)
    unsigned char m_kizunaringComplete;  // 1 when complete (GfDataBlade::isKizunaringComplete; the name is not the original's)
    unsigned char pad_8a2[0x2];
};
}  // namespace gf

#endif

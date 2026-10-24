#ifndef GF_SDATABLADE_H
#define GF_SDATABLADE_H

#include "gf/GfDataBlade.h"

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

    Idea m_ideas[4];
};

// one of a blade's arts (the name is not the original's)
struct BladeArtsSlot {
    unsigned short m_id;  // getBladeArts, getBladeArtsN, getBladeArtsEx...
    unsigned short m_h;  // getBladeArtsH, getBladeArtsNH, getBladeArtsExH...
    unsigned char pad_4[0x3];
    unsigned char m_level;  // getBladeArtsLevel
    unsigned char pad_8[0x4];
};

// one of a blade's skills (the name is not the original's)
struct BladeSkillSlot {
    unsigned short m_id;  // getBladeSkill, getFieldSkill
    unsigned char pad_2[0x1];
    unsigned char m_level;  // getBladeSkillLevel, getFieldSkillLevel
    unsigned char pad_4[0x2];
};

// no table: a blade's data (GfDataBlade::getSDataBlade's). The field names are not the original's: each says what
// the DataObjBlade or DataObjEnemyBlade accessor that reads it returns; the layout past them is not known.
// 0x8A4 bytes (DataObjBlade::setupVirtualParam allocates one)
class SDataBlade {
public:
    SDataBlade();
    SDataBlade& operator=(const SDataBlade& other);

    unsigned short m_dataType;  // DataObjBlade::getDataType
    unsigned char pad_2[0x2];
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
    unsigned char pad_666[0x12];
    unsigned short m_equipOrbs[3];  // DataObjBlade::setVirtualEquipOrb sets one, by slot; the count is not known
    unsigned char pad_67e[0xE];
    unsigned short m_hanaRoleParts;  // Hana's role part (GfDataBlade::getHpMaxRev reads its row; the name is not the original's)
    unsigned char pad_68e[0x7A];
    unsigned char m_race;
    unsigned char m_gender;
    unsigned short m_iconData;
    char m_modelName[0x28];  // getModelResourceName; the length is the distance to the next
    char m_motionName[0x28];  // getMotionResourceName; the length is the distance to the next
    char m_addMotionName[0x14];  // GfDataBlade::getResourceNameAddMotion; the length is the distance to the next
    char m_voiceStr[0x1C];  // GfDataBlade::getVoiceStr; the length is the distance to the next
    unsigned char pad_78c[0x20];
    char m_effectName[0x28];  // getEffectResourceName; the length is not known
    char m_centerBone[0x14];  // getCenterBone; the length is the distance to the next
    char m_camBone[0x14];  // getCamBone; the length is the distance to the next
    char m_seName[0x24];  // getSeResourceName, GfDataBlade::getSePack; the length is the distance to the next
    unsigned char m_size;  // (named after its accessor; the name is not the original's)
    unsigned char m_weaponType;
    unsigned char m_equipOrbMax;  // (named after its accessor; the name is not the original's)
    unsigned char pad_823[0x1];
    unsigned char m_personality;
    unsigned char pad_825[0x1];
    unsigned char m_eyeRotControl;
    unsigned char pad_827[0x1];
    unsigned short m_coolTime;
    unsigned char pad_82a[0x2];
    unsigned short m_equipWeapon;  // its weapon (DataObjPcWpn::getBladeSet compares it with the weapon's row)
    unsigned short m_chestHeight;
    unsigned short m_landingHeight;
    unsigned char pad_832[0x4];
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
    unsigned char pad_84a[0x2];
    unsigned short m_normalTalk;  // (named after its accessor; the name is not the original's)
    unsigned char pad_84e[0x2];
    unsigned int m_createEvent;  // (named after its accessor; the name is not the original's)
    unsigned char pad_854[0x4A];
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

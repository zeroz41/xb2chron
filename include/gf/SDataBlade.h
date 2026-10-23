#ifndef GF_SDATABLADE_H
#define GF_SDATABLADE_H

#include "gf/GfDataBlade.h"

namespace gf {
// what DataObjBlade::getIdea points at (an SDataBlade's +0xC); the type name is not the original's
struct SDataIdea {
    unsigned char pad_0[0x30];
};

// one of a blade's arts (the name is not the original's)
struct BladeArtsSlot {
    unsigned short m_id;  // getBladeArts, getBladeArtsN, getBladeArtsEx...
    unsigned short m_h;  // getBladeArtsH, getBladeArtsNH, getBladeArtsExH...
    unsigned char pad_4[0x3];
    unsigned char m_level;  // getBladeArtsLevel
    unsigned char pad_8[0x4];
};

// no table: a blade's data (GfDataBlade::getSDataBlade's). The field names are not the original's: each says what
// the DataObjBlade or DataObjEnemyBlade accessor that reads it returns; the layout past them is not known.
class SDataBlade {
public:
    SDataBlade();
    SDataBlade& operator=(const SDataBlade& other);

    unsigned short m_dataType;  // DataObjBlade::getDataType
    unsigned char pad_2[0x4];
    unsigned short m_bladeId;  // its blade row (GfDataBlade::getQuestRace takes it)
    unsigned char pad_8[0x4];
    SDataIdea m_idea;  // DataObjBlade::getIdea points at it; its size is not known
    BladeArtsSlot m_arts[3];  // getBladeArts...
    BladeArtsSlot m_nArts[3];  // getBladeArtsN...
    BladeArtsSlot m_artsEx;  // getBladeArtsEx
    BladeArtsSlot m_artsEx2;  // getBladeArtsEx2
    unsigned char pad_9c[0x24];
    unsigned char m_extraParts[3];  // DataObjEnemyBlade::isDispInitExtraParts, by part; the count is not known
    unsigned char pad_c3[0x1];
    AchievInfo m_artsAchievement[3];  // getArtsAchievement, by line
    AchievInfo m_skillAchievement[3];  // getSkillAchievement, by line
    AchievInfo m_fieldSkillAchievement[3];  // getFieldSkillAchievement, by line
    AchievInfo m_keyAchievement;  // getKeyAchievement
    unsigned short m_keyLevel;  // DataObjDriver::getKeyLevel
    unsigned char pad_666[0xA2];
    unsigned char m_race;
    unsigned char m_gender;
    unsigned short m_iconData;
    char m_modelName[0x28];  // getModelResourceName; the length is the distance to the next
    char m_motionName[0x78];  // getMotionResourceName; the length is the distance to the next
    char m_effectName[0x28];  // getEffectResourceName; the length is not known
    char m_centerBone[0x14];  // getCenterBone; the length is the distance to the next
    char m_camBone[0x14];  // getCamBone; the length is the distance to the next
    char m_seName[0x25];  // getSeResourceName; the length is not known
    unsigned char m_weaponType;
    unsigned char pad_822[0x2];
    unsigned char m_personality;
    unsigned char pad_825[0x1];
    unsigned char m_eyeRotControl;
    unsigned char pad_827[0x1];
    unsigned short m_coolTime;
    unsigned char pad_82a[0x2];
    unsigned short m_equipWeapon;  // its weapon (DataObjPcWpn::getBladeSet compares it with the weapon's row)
    unsigned short m_chestHeight;
    unsigned short m_landingHeight;
    unsigned char pad_832[0xC];
    unsigned char m_pArmor;  // added to its weapon's (DataObjEnemyBlade::getPArmor)
    unsigned char m_eArmor;  // added to its weapon's (DataObjEnemyBlade::getEArmor)
};
}  // namespace gf

#endif

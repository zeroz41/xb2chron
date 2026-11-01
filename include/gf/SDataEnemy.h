#ifndef GF_SDATAENEMY_H
#define GF_SDATAENEMY_H

namespace gf {
// no table: an enemy's data, as GfDataEnemy::setupSDataEnemy fills it in from the enemy's bdat rows. The field
// names are not the original's: each says what the DataObjEnemy accessor that reads it returns.
class SDataEnemy {
public:
    SDataEnemy(unsigned int, unsigned int);

    unsigned short m_id;  // the enemy's GfBdatChrEnArrange row (DataObjEnemy::getBdatId)
    unsigned char pad_2[0x2];
    bool m_named : 1;  // btl::EnemyParameter::IsNamed reads it
    bool m_boss : 1;   // btl::EnemyParameter::IsBoss reads it
    unsigned char m_flags4 : 2;  // unknown
    bool m_linkGenus : 1;
    bool m_guardFront : 1;
    bool m_guardLeft : 1;
    bool m_guardRight : 1;
    bool m_guardBack : 1;
    bool m_fieldDamage : 1;
    bool m_flags5bit2 : 1;  // unknown
    bool m_noCameraFade : 1;
    bool m_weaponDrawDisp : 1;
    unsigned char m_flags5 : 3;  // unknown
    // bits too: the flags at 0x4 are one 32-bit unit (GmkDoorPhantomManager::listenerGfObj keeps the whole word of
    // m_flags5bit2 across a call)
    unsigned short pad_6 : 16;
    // a GfBdatChrEnParam row: ai::AiData::getScoutStartHp passes it to getChrEnParamScoutStartHp (the name is not the
    // original's)
    unsigned short m_scoutParamId;
    unsigned char pad_a[0x8];
    // the percent DataObjEnemy::getLevelGold scales the level's gold by (the name is not the original's; the
    // arrangement bdat has a GoldRev column)
    unsigned short m_goldRev;
    unsigned char pad_14[0xB];
    unsigned char m_linkRadius;  // getLinkRadius
    unsigned char pad_20[0x14];
    unsigned short m_paramId;  // its GfBdatChrEnParam row (the stat getters' revisions)
    unsigned char pad_36[0xB];
    // GfObjSetup::createSetupParam(GfInitParamEnemy) copies it from the enemy's owner's data when set
    unsigned char pad_41;
    unsigned char m_extraPartsMask;  // bits of the extra parts shown at first (isDispInitExtraParts)
    unsigned char pad_43[0x1];
    unsigned short m_rscId;  // its GfBdatRsc enemy row
    unsigned char pad_46[0x3];
    // its field walk and run speeds, km/h (1.0.0's GfBehaviorEnemyField::getWalkSpeed/getRunSpeed read them; the
    // names are not the original's)
    unsigned char m_walkSpeed;
    unsigned char m_runSpeed;
    unsigned char pad_4b[0x11];
    unsigned short m_pArmor;
    unsigned short m_eArmor;
    unsigned char m_resistancePower;
    unsigned char m_resistanceEther;
    unsigned char pad_62[0x1];
    unsigned char m_criticalRate;
    unsigned char m_guardRate;
    unsigned char pad_65[0x1];
    unsigned short m_resistanceCombo;
    unsigned short m_invincibleCombo;
    unsigned char pad_6a[0x2F];
    unsigned char m_genus;
    // GfBdatRsc::getRscEnActType's for the enemy (setupSDataEnemy; the name is not the original's)
    unsigned char m_actType;
    unsigned char pad_9b[0x3];
    unsigned short m_equipWeapons[5];  // getEquipWeapon, by index; the count is not known
    unsigned short m_level;  // 0: level 1; capped at 999 (getLevel)
    unsigned char pad_aa[0x2];
    unsigned int m_hpMax;
    unsigned short m_strength;
    unsigned short m_powerEther;
    unsigned short m_dex;      // getDex
    unsigned short m_agility;  // getAgility
    unsigned short m_luck;     // getLuck
    // sizeof is 0xbc: GfObjSetup::createSetupParam(GfInitParamEnemy) allocates that much
    unsigned char pad_ba[0x2];
};
}  // namespace gf

#endif

#ifndef GF_SDATAENEMY_H
#define GF_SDATAENEMY_H

namespace gf {
// no table: an enemy's data, as GfDataEnemy::setupSDataEnemy fills it in from the enemy's bdat rows. The field
// names are not the original's: each says what the DataObjEnemy accessor that reads it returns, or (fields only
// clear() and setupSDataEnemy touch) the bdat column setupSDataEnemy stores there.
class SDataEnemy {
public:
    // 1.0.0 has SDataEnemy() and clear() as symbols; clear() leaves the flags alone and has no symbol in 3.0.1
    SDataEnemy()
        : m_named(false), m_boss(false), m_flags4(0), m_linkGenus(false), m_guardFront(false), m_guardLeft(false),
          m_guardRight(false), m_guardBack(false), m_fieldDamage(false), m_flags5bit2(false), m_noCameraFade(false),
          m_weaponDrawDisp(false), m_flags5(0), pad_6(0) {
        clear();
    }
    SDataEnemy(unsigned int, unsigned int);
    void clear();

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
    unsigned short m_bladeId;  // BladeID
    unsigned short m_name;     // Name
    unsigned char m_lv;        // Lv
    unsigned char pad_f[0x1];
    unsigned short m_expRev;  // ExpRev
    // the percent DataObjEnemy::getLevelGold scales the level's gold by (the name is not the original's; the
    // arrangement bdat has a GoldRev column)
    unsigned short m_goldRev;
    unsigned short m_dropTableId;   // DropTableID
    unsigned short m_dropTableId2;  // DropTableID2
    unsigned short m_dropTableId3;  // DropTableID3
    unsigned short m_preciousId;    // PreciousID
    unsigned short m_scale;         // Scale
    // 0..3: which of gf::ChainAttackCamera's bdat rows fit it (the EnSize column's bits 1, 2, 4, 8; the name is not
    // the original's)
    unsigned char m_enSize;
    unsigned char m_linkRadius;  // getLinkRadius
    unsigned char m_detects;     // Detects
    unsigned char pad_21[0x1];
    unsigned short m_searchRange;  // SearchRange
    unsigned short m_searchAngle;  // SearchAngle
    unsigned char m_searchRadius;  // SearchRadius
    unsigned char m_batArea;       // BatArea
    unsigned char pad_28;
    unsigned char m_aiGroup;     // AiGroup
    unsigned char m_aiGroupNum;  // AiGroupNum
    unsigned char pad_2b[0x1];
    unsigned short m_bookId;      // BookID
    unsigned short m_enhanceId1;  // EnhanceID1
    unsigned short m_enhanceId2;  // EnhanceID2
    unsigned short m_enhanceId3;  // EnhanceID3
    unsigned short m_paramId;  // its GfBdatChrEnParam row (the stat getters' revisions)
    unsigned short m_rstDebuffRev;    // RstDebuffRev
    unsigned short m_healPotTypeRev;  // HealPotTypeRev
    unsigned short m_summonId;        // SummonID
    unsigned char m_bgmId;            // BGMID
    unsigned char m_seEnvId;          // SeEnvID
    unsigned char m_zoneId;           // ZoneID
    unsigned char pad_3f;
    unsigned char pad_40;
    // GfObjSetup::createSetupParam(GfInitParamEnemy) copies it from the enemy's owner's data when set
    unsigned char pad_41;
    unsigned char m_extraPartsMask;  // bits of the extra parts shown at first (isDispInitExtraParts)
    unsigned char pad_43[0x1];
    unsigned short m_rscId;  // its GfBdatRsc enemy row
    unsigned short m_aiId;       // AiID
    unsigned char m_enemyRole;  // EnemyRole
    // its field walk and run speeds, km/h (1.0.0's GfBehaviorEnemyField::getWalkSpeed/getRunSpeed read them; the
    // names are not the original's)
    unsigned char m_walkSpeed;
    unsigned char m_runSpeed;
    unsigned char m_btlSpeed;        // BtlSpeed
    unsigned char m_hpDefault;       // HpDefault
    unsigned char m_hpLimit;         // HpLimit
    unsigned char m_scoutStartHp;    // ScoutStartHp
    unsigned char m_scoutEndHp;      // ScoutEndHp
    unsigned short m_hpMaxRev;       // HpMaxRev
    unsigned short m_strengthRev;    // StrengthRev
    unsigned short m_powEtherRev;    // PowEtherRev
    unsigned short m_dexRev;         // DexRev
    unsigned short m_agilityRev;     // AgilityRev
    unsigned short m_luckRev;        // LuckRev
    unsigned short m_pArmor;
    unsigned short m_eArmor;
    unsigned char m_resistancePower;
    unsigned char m_resistanceEther;
    // its attribute when the arrangement has no BladeAtr and no blade (DataObjEnemy::getAttribute; the name is not
    // the original's)
    unsigned char m_attribute;
    unsigned char m_criticalRate;
    unsigned char m_guardRate;
    unsigned char m_healPotDrop;  // HealPotDrop
    unsigned short m_resistanceCombo;
    unsigned short m_invincibleCombo;
    unsigned short m_aura;         // Aura
    unsigned char m_dyingHp;       // DyingHP
    unsigned char m_wtNormal;      // WTNormal
    unsigned char m_wtDying;       // WTDying
    unsigned char m_hate0Target;   // Hate0Target
    unsigned short m_deathArts;    // DeathArts
    unsigned char pad_72[0x2];
    unsigned int m_deathArtsStop;  // DeathArtsStop
    // ArtsNum: setupSDataEnemy stores getChrEnParamArtsNum(row, i); clear() zeroes 16
    unsigned short m_artsNum[16];
    unsigned char pad_98;
    unsigned char m_genus;
    // GfBdatRsc::getRscEnActType's for the enemy (setupSDataEnemy; the name is not the original's)
    unsigned char m_actType;
    unsigned char pad_9b;
    unsigned char pad_9c;  // 1 after clear()
    unsigned char pad_9d[0x1];
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

// the order is the one that gives the original's stores (1.0.0's SDataEnemy::clear)
inline void SDataEnemy::clear() {
    m_rscId = 0;
    m_id = 0;
    m_scoutParamId = 0;
    m_bladeId = 0;
    m_name = 0;
    m_lv = 0;
    m_expRev = 0;
    m_goldRev = 0;
    m_dropTableId = 0;
    m_dropTableId2 = 0;
    m_dropTableId3 = 0;
    m_preciousId = 0;
    m_scale = 0;
    m_enSize = 1;
    m_linkRadius = 10;
    m_detects = 0;
    m_searchRange = 10;
    m_bookId = 0;
    m_enhanceId1 = 0;
    m_searchAngle = 0;
    m_searchRadius = 0;
    m_batArea = 0;
    pad_28 = 0;
    m_aiGroup = 0;
    m_aiGroupNum = 0;
    m_paramId = 0;
    m_rstDebuffRev = 0;
    m_healPotTypeRev = 0;
    m_summonId = 0;
    m_bgmId = 0;
    m_seEnvId = 0;
    m_zoneId = 0;
    pad_3f = 0;
    pad_40 = 0;
    pad_41 = 0;
    m_extraPartsMask = 0;
    m_aiId = 0;
    m_enemyRole = 0;
    m_walkSpeed = 0;
    m_runSpeed = 0;
    m_btlSpeed = 0;
    m_hpDefault = 0;
    m_hpLimit = 0;
    m_scoutStartHp = 0;
    m_scoutEndHp = 0;
    m_hpMaxRev = 0;
    m_strengthRev = 0;
    m_powEtherRev = 0;
    m_dexRev = 0;
    m_agilityRev = 0;
    m_luckRev = 0;
    m_pArmor = 0;
    m_eArmor = 0;
    m_resistancePower = 0;
    m_resistanceEther = 0;
    m_attribute = 0;
    m_criticalRate = 0;
    m_guardRate = 0;
    m_healPotDrop = 0;
    m_resistanceCombo = 0;
    m_invincibleCombo = 0;
    m_aura = 0;
    m_dyingHp = 0;
    m_wtNormal = 0;
    m_wtDying = 0;
    m_hate0Target = 0;
    m_deathArts = 0;
    m_deathArtsStop = 0;
    pad_98 = 0;
    m_genus = 0;
    m_actType = 0;
    pad_9b = 0;
    pad_9c = 1;
    m_enhanceId2 = 0;
    m_enhanceId3 = 0;
    m_level = 1;
    m_equipWeapons[0] = 0;
    m_equipWeapons[1] = 0;
    m_equipWeapons[2] = 0;
    m_equipWeapons[3] = 0;
    m_equipWeapons[4] = 0;
    m_hpMax = 0;
    m_strength = 0;
    m_powerEther = 0;
    m_dex = 0;
    m_agility = 0;
    m_luck = 0;
    for (int i = 0; i < 16; i++) {
        m_artsNum[i] = 0;
    }
}
}  // namespace gf

#endif

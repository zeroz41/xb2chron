#ifndef GF_SDATADRIVER_H
#define GF_SDATADRIVER_H

#include "gf/SDataBlade.h"
#include "gf/SDataPouch.h"
#include "gf/GfItemInfo.h"
#include "mm/mtl/Bitflag.h"

namespace gf {
// an accessory slot of a driver (GfDataDriver::getEquipAcce; the names are not the original's)
// (8 bytes at 0x574: the item handle GfDataDriver::getEquipAcceHandle returns, then the item id getEquipAcce reads)
struct SDataDriverAcce {
    GfItemHandle m_handle;
    unsigned short m_item;
    unsigned char pad_6[0x2];
};

// a driver's arts records past the ones its data keeps, 0x324 bytes: 20-byte arts records (five words) for arts slots
// from 0x1C (GfDataDriver::getDriverWeaponType returns record index - 0x1C), then (0x1E0) the level bytes of the arts from
// 0x280 (getDriverArtsLevel, setDriverArtsLevel, GfDataDriverArts::getArtsLevel read byte arts - 0x280), then a word (SDataSave()
// copies 0x320 bytes and the word apart). One per driver: SDataGame keeps 16 at 0x11768C, SDataDlc 16 for the DLC
// drivers. The counts are those that fill 0x320 bytes; the type and field names are not the original's.
struct SDataDriverArtsEx {
    unsigned int m_arts[24][5];
    unsigned char m_artsLevels[0x140];
    // 0x320: the driver's flags 0x1C.. (GfDataDriver::isActivateWeaponType tests and setActivateWeaponType sets flag index - 0x1C,
    // asserting index < 28 at bitflag.h's lines 133 and 77; SDataSave() copies it with copy_n)
    mm::mtl::Bitflag<28> m_flags;
};

// no table: a driver's data, 0x5A0 bytes (DataObjDriver::setupVirtualParam allocates one for its virtual settings;
// GfDataDriver::getSDataDriver returns one). The field names are not the original's.
class SDataDriver {
public:
    SDataIdea m_idea;  // DataObjDriver::getIdea returns the driver's data itself
    unsigned short m_dataType;  // DataObjDriver::getDataType
    unsigned short m_id;  // its row, 0 for none (DataObjDriver::isValid)
    short m_bladeSet;  // the slot of its engaged blade, -1 for none (DataObjDriver::setBladeSet)
    unsigned short m_blades[3];  // the blade in each slot (DataObjDriver::getBlade); the count is not known
    unsigned char pad_2c[0x4];
    // 0x30: the learned skill of each skill tree line's three levels (0x62: the same for round, the tree a second
    // playthrough uses); GfDataDriverSkill::getSkill reads them (the names are not the original's; 5 x 5 halves
    // fill the space up to m_level)
    unsigned short m_skills[5][5];
    unsigned short m_roundSkills[5][5];
    unsigned short m_level;  // 0x94 (GfDataDriver::getLevel; the name is not the original's)
    unsigned short m_hpMax;  // 0x96: DataObjDriver::getHpMax's base (the name is not the original's)
    // 0x98..0xA0: the base stats DataObjDriver's getters read before enhances and GfDataDriver's *Rev corrections
    // (named after those getters; the names are not the original's)
    unsigned short m_strength;
    unsigned short m_powEther;
    unsigned short m_dex;
    unsigned short m_agility;
    unsigned short m_luck;
    // 0xA2..0xA7: the base defenses and rates DataObjDriver's getPArmor/getEArmor/getCriticalRate/getGuardRate read
    // (named after those getters; the names are not the original's)
    unsigned short m_pArmor;
    unsigned short m_eArmor;
    unsigned char m_criticalRate;
    unsigned char m_guardRate;
    unsigned char pad_a8[0x8];
    unsigned int m_exp;  // 0xB0 (GfDataDriver::getExp; the name is not the original's)
    unsigned int m_battleExp;  // 0xB4 (GfDataDriver::getBattleExp; the name is not the original's)
    unsigned int m_skillPoint;  // 0xB8 (GfDataDriver::getSkillPoint; the name is not the original's)
    unsigned int m_totalSkillPoint;  // 0xBC (GfDataDriver::addSkillPoint adds gains, capped at 0x7FFFFFFF; the name is not the original's)
    // 0xC0: 20-byte arts records (five words) for arts slots below 0x1C (GfDataDriver::getDriverWeaponType returns
    // record `index`, DataObjDriver::getDriverArts mode 0 reads its words). Slot 0x1B's record reaches 0x2F0, over
    // m_equipAcceEx: the count of 27 is what fits before it. The name is not the original's.
    unsigned int m_arts[27][5];
    unsigned char pad_2dc[0xC];
    // 0x2E8: its low 16 bits are the accessory of GfDataDriver::getEquipAcce's slots past the first two (setEquipAcce
    // keeps the high 16 bits; the name is not the original's)
    // bit 31: the flag GfDataDriver::isEnableExtendEquipAcce reads and setEnableExtendEquipAcce sets
    unsigned int m_equipAcceEx;
    // 0x2EC: the item handle of that extra slot (GfDataDriver::getEquipAcceHandle's slot 2; the name is not the original's)
    GfItemHandle m_equipAcceHandleEx;
    // 0x2F0: the level byte of each arts below 0x280 (GfDataDriver::getDriverArtsLevel and setDriverArtsLevel,
    // GfDataDriverArts::getArtsLevel; the name is not the original's)
    unsigned char m_artsLevels[0x280];
    unsigned char m_scenarioMask;  // 0x570: 1 when masked (GfDataDriver::isScenarioMask; the name is not the original's)
    // 0x571: GfDataDriver::isAttachedParty returns whether it is nonzero (GfGameUtil::execLevelUp/addWpForObject call
    // it; the name is not the original's)
    unsigned char m_stateFlag;
    // 0x572: the driver's default accessory was handed out (GfGameUtil::execEquipDriverDefaultAcce sets it, its
    // isEquipDefaultAcce check reads it; the name is not the original's)
    bool m_defaultAcceDone;
    // 0x573: bit 0 or 1 (by a flag) set by GfDataDriver::setKizunaringComplete and tested by isKizunaringComplete, whose one caller
    // is GfMenuObjDrKizunaRing::seqComplete (the name is not the original's)
    unsigned char m_kizunaRingFlags;
    SDataDriverAcce m_equipAcce[2];  // 0x574 (GfDataDriver::getEquipAcce's slots 0 and 1)
    SDataPouch m_pouches[3];  // 0x584 (GfDataDriver::getPouchData; the count is not known)
    // 0x59C: the driver's flags 0..0x1B (GfDataDriver::isActivateWeaponType / setActivateWeaponType for indexes below 0x1C; the
    // size of 28 is SDataDriverArtsEx::m_flags's, the name is not the original's)
    mm::mtl::Bitflag<28> m_flags;
};

// a DLC driver's data, 0xDAC bytes: a driver's data and more (GfDataDriver::getSDataIra returns one;
// DataObjDriver::setupVirtualParam allocates one). The type and field names are not the original's.
struct SDataDriverDlc {
    SDataDriver m_driver;
    // 0x5A0: an item handle and (0x5A4) a 16-bit item id, read and set by GfDataDriver::getEquipWpnAcceHandle/setEquipWpnAcceHandle and
    // getEquipWpnAcce/fn_71002474F4 (GfItemUtil::getEquipChar reads the handle; the names are not the original's)
    GfItemHandle m_handle;
    unsigned short m_item;
    unsigned char pad_5a6[0xA];
    // 0x5B0 and 0x9AC: two tables of 20-byte arts records (five words each) of the DLC driver,
    // GfDataDriver::getDriverWeaponTypeIraBack and getDriverWeaponTypeIraSwitch return record `index` (DataObjDriver::getDriverArts modes 1 and
    // 2); the counts fill the record up to 0xDA8 and are not known. The names are not the original's.
    unsigned int m_dlcArts[51][5];
    unsigned int m_dlcArts2[51][5];
    // 0xDA8: GfDataDriver::getPartyPos returns it for a DLC driver; GfObjUtil::getPartyPos passes it on as the
    // driver's party index (GfGameParty's listenerGfObj compares it with 2). The name is not the original's.
    unsigned short m_partyIndex;
    unsigned char pad_daa[0x2];
};
}  // namespace gf

#endif

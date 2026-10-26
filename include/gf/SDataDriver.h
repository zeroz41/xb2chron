#ifndef GF_SDATADRIVER_H
#define GF_SDATADRIVER_H

#include "gf/SDataBlade.h"

namespace gf {
// an accessory slot of a driver (GfDataDriver::getEquipAcce; the names are not the original's)
struct SDataDriverAcce {
    unsigned short m_item;
    unsigned char pad_2[0x6];
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
    unsigned char pad_2c[0x68];
    unsigned short m_level;  // 0x94 (GfDataDriver::getLevel; the name is not the original's)
    unsigned short m_hpMax;  // 0x96: DataObjDriver::getHpMax's base (the name is not the original's)
    // 0x98..0xA0: the base stats DataObjDriver's getters read before enhances and GfDataDriver's *Rev corrections
    // (named after those getters; the names are not the original's)
    unsigned short m_strength;
    unsigned short m_powEther;
    unsigned short m_dex;
    unsigned short m_agility;
    unsigned short m_luck;
    unsigned char pad_a2[0xE];
    unsigned int m_exp;  // 0xB0 (GfDataDriver::getExp; the name is not the original's)
    unsigned int m_battleExp;  // 0xB4 (GfDataDriver::getBattleExp; the name is not the original's)
    unsigned int m_skillPoint;  // 0xB8 (GfDataDriver::getSkillPoint; the name is not the original's)
    unsigned int m_totalSkillPoint;  // 0xBC (GfDataDriver::addSkillPoint adds gains, capped at 0x7FFFFFFF; the name is not the original's)
    unsigned char pad_c0[0x228];
    // 0x2E8: its low 16 bits are the accessory of GfDataDriver::getEquipAcce's slots past the first two (setEquipAcce
    // keeps the high 16 bits; the name is not the original's)
    unsigned int m_equipAcceEx;
    unsigned char pad_2ec[0x284];
    unsigned char m_scenarioMask;  // 0x570: 1 when masked (GfDataDriver::isScenarioMask; the name is not the original's)
    unsigned char pad_571[0x1];
    // 0x572: the driver's default accessory was handed out (GfGameUtil::execEquipDriverDefaultAcce sets it, its
    // fn_71002491D4 check reads it; the name is not the original's)
    bool m_defaultAcceDone;
    unsigned char pad_573[0x5];
    SDataDriverAcce m_equipAcce[2];  // 0x578 (GfDataDriver::getEquipAcce's slots 0 and 1)
    unsigned char pad_588[0x18];
};

// a DLC driver's data, 0xDAC bytes: a driver's data and more (GfDataDriver::fn_7100241BB4 returns one;
// DataObjDriver::setupVirtualParam allocates one). The type and field names are not the original's.
struct SDataDriverDlc {
    SDataDriver m_driver;
    unsigned char pad_5a0[0x80C];
};
}  // namespace gf

#endif

#ifndef GF_SDATADLC_H
#define GF_SDATADLC_H

#include "gf/GfDataParty.h"
#include "gf/SDataDriver.h"

namespace gf {
// the DLC drivers' data a save keeps after the game (SDataSaveIra's from 0x126D90, GfDataStore's from 0x126E28;
// GfDataStore::getDataGameIra and GfDataManager::getDataGameIra return it), 0x10D80 bytes. The type and member names
// are not the original's.
struct SDataDlc {
    SDataIra m_drivers[16];  // GfDataDriver::getSDataDriver reads rows 0x11 to 0x19 from them
    unsigned int m_word;  // 0xDAC0 (SDataSaveIra() clears it)
    // 0xDAC4: the DLC drivers' arts records past the ones their data keeps (GfDataDriver::getDriverWeaponType)
    SDataDriverArtsEx m_driverArtsEx[16];
    // 0x10D04 and 0x10D40: the members of parties 1 and 2 (GfDataParty::getPartyMember, getDriver; party 0 is the
    // game data's SDataParty)
    GfDataParty::PartyMember m_partyMembers[2][10];
    unsigned int m_word2;  // 0x10D7C
};
}  // namespace gf

#endif

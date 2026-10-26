#ifndef GF_SDATASAVE_H
#define GF_SDATASAVE_H

#include "gf/SDataDriver.h"
#include "gf/SDataGame.h"

namespace gf {
// the system part of the data (GfDataStore::getDataSystem returns GfDataStore's, 1.0.0's
// GfGameUtilSaveData::setupGameSaveData copies it to the save's start: a word at 0 and a doubleword at 8)
class SDataSystem {
public:
    // 0x3A15B as made (the save buffer's readers in title_main check it before they read the game; the name is
    // not the original's)
    unsigned int m_version;
    unsigned char pad_4[0x4];
    // a doubleword GfDataStore::clear zeroes and 1.0.0's setGameData copies; what it holds is not known (the name is
    // not the original's)
    unsigned long m_systemValue;
};

// a save: 0x137B10 bytes (createSaveBuffer allocates them). 1.0.0's was the system and the game only (0x1176A0);
// 3.0.1 adds the DLC drivers and a block after them, the same two GfDataStore keeps after its SDataOption
// (fn_710022D440 returns GfDataStore's DLC drivers; GfDataStore::GfDataStore builds both as SDataSave() does).
// The member names are not the original's.
class SDataSave {
public:
    SDataSave();  // fn_710014F8F0

    SDataSystem m_system;
    SDataGame m_game;  // 0x10
    SDataDriverDlc m_dlcDrivers[16];  // 0x126D90; GfDataDriver::getSDataDriver reads rows 0x11 to 0x19 from them
    // 0x134850: a word, 16 0x324-byte records (each 0x320 bytes copied bit for bit and a word copied with
    // algorithm.h's copy_n), 0x78 bytes, a word: SDataSave() clears it all, assigns a cleared record to the 16
    // and clears the 0x78 bytes again
    unsigned char pad_134850[0x32C0];
};
}  // namespace gf

#endif

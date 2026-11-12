#ifndef GF_SDATAOPTION_H
#define GF_SDATAOPTION_H

#include <string.h>

namespace gf {
struct SSoundUiOption;

// the sound and screen part of the option settings, 0x3C bytes at SDataOption+0x4C (1.0.0's
// SSoundUiOption::clear and isDirty)
struct SSoundUiOption {
    void clear();
    // the clear's last part, out of line in 3.0.1 (GfGameLoad::execOptionLoadWithMicroThread calls it).
    // 2.0.0's symbols name it. What it does: stores the 0xED 0xB0 0x1E 0x5F 0x06 bytes at 0x1F, clears 0x24..0x32 and
    // 0x3B, calls GfDataBtlDif::setOptionGameDifficult(this, 0), clears 0x33..0x38.
    void initializeReserverArea();
    // 2.0.0's symbols name it. A member because it reads the bytes clear()
    // stores (GfGameLoad::execOptionLoadWithMicroThread calls it on the loaded option's). What it does: true unless
    // 0x1F..0x22 hold clear()'s 0xED 0xB0 0x1E 0x5F, 0x23 is at most 6 and 0x33..0x36 are at most 1 each.
    bool isUninitializeReserverArea() const;
    // 1.0.0's isDirty (GfMenuObjOption's unit holds it): true when other differs from it
    bool isDirty(const SSoundUiOption& other);

    // the master volumes as 0..255 (GfMasterVolume's thirteen, in its order; the name is not the original's)
    unsigned short m_volume[13];
    // 0..255: GfMenuManager::applyOptionData divides it by 255 for applyGammaCorrectValue (the name is not the original's)
    unsigned short m_gamma;
    // the event subtitles' option: GfMenuObjEventSubtitle shows a first line that is not vertical only when it is
    // set (the name is not the original's)
    bool m_eventSubtitle;
    // fw::LangUtil::getLangType's language as a byte: GfGameUtilSaveData::setupOptionSaveData stores it (the name is
    // not the original's)
    unsigned char m_langType;
    // 0x1E-0x3C: what these hold is not known; the names are not the original's. clear() stores 0 at 0x1E;
    // initializeReserverArea stores the 0x1F-0x22 key with one unaligned 32-bit store (copied as one 4-byte block), 6 at 0x23,
    // clears m_list and 0x3B, and clears the flags after GfDataBtlDif::setOptionGameDifficult. The flags
    // 0x33-0x38 are plain bytes: gf::GfGameUtilDiff::isEnableAutoSave, GfGameUtilDiff::isEnableSpecialBgm..GfGameUtilDiff::isEnableHitonowaSkip load each with one ldrb.
    // The key fields are plain (not a bitfield run): SSoundUiOption::isUninitializeReserverArea loads 0x22-0x23 and 0x34-0x35
    // with one ldrh each (adjacent byte loads widened), which a bitfield run ending at 0x22 does not give
    unsigned char m_byte1E;
    unsigned char m_keyA;
    unsigned short m_keyB;
    unsigned char m_keyC;
    unsigned char m_keyD;
    unsigned char m_list[0xF];
    unsigned char m_flagA;
    unsigned char m_flagB;
    unsigned char m_flagC;
    unsigned char m_flagD;
    unsigned char m_flagE;
    unsigned char m_flagF;
    unsigned char pad_39[0x2];
    unsigned char m_byte3B;
};

// the option settings, as GfDataManager::getDataOption hands them out (1.0.0's GfMenuObjOption::initOptionData
// takes one): 0x88 bytes (GfDataStore::setupOptionData copies them)
class SDataOption {
public:
    // made cleared: GfMenuObjOption's constructor runs clear() between its members' (and GfDataStore's, per the
    // note on clear below)
    SDataOption() { clear(); }
    // GfDataStore's initOptionData (inline in 3.0.1's GfDataStore::clear and constructor) (the name is not the
    // original's)
    void clear();

    // 0x3A15B as made, as SDataSystem's (the name is not the original's)
    unsigned int m_version;
    // 0x4-0x4C: cleared as made, all but 0xB (made 1); what they hold is not known (the names are not the
    // original's). 0x4-0xB are eight byte settings (0xB made 1): GfMenuObjOption::convLevelListToOptionData
    // stores each with one strb and GfMenuObjOption::MainListener compares them in a loop
    unsigned char m_settings[8];
    unsigned char m_optionBlock[0x40];
    SSoundUiOption m_soundUi;  // 0x4C (the name is not the original's)
};

inline void SDataOption::clear() {
    m_version = 0x3A15B;
    m_settings[6] = 0;
    m_settings[4] = 0;
    m_settings[5] = 0;
    m_settings[0] = 0;
    m_settings[1] = 0;
    m_settings[2] = 0;
    m_settings[3] = 0;
    m_settings[7] = true;
    memset(m_optionBlock, 0, sizeof(m_optionBlock));
    m_soundUi.clear();
}
}  // namespace gf

#endif

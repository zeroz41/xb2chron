#ifndef GF_SDATAOPTION_H
#define GF_SDATAOPTION_H

#include <string.h>

namespace gf {
struct SSoundUiOption;
// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A free function because its address sits in
// GfDataBlade.cpp's unit, among no class of its own, and it works on the option it is handed. What it does: stores 6
// at the option's 0x23, then (when GfBdatBtl is up) fills the bytes from 0x24 from GfBdatBtl::fn_71001E9520 for the
// type it is handed (type 4: fn_7100254DF0 instead); SSoundUiOption::clear passes type 0.
void fn_7100254EF0(SSoundUiOption* option, unsigned int type);
// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A free function because its address sits in
// GfDataBlade.cpp's unit next to fn_7100254EF0, among no class of its own. What it does: when GfBdatBtl is up, stores
// 4 at the option's 0x23 and value at 0x24 + index - 1, then calls fn_7100254DF0 on the option;
// GfMenuObjOption::initOptionData passes each difficulty bdat row's default level - 1.
void fn_7100254DC4(SSoundUiOption* option, unsigned int index, unsigned char value);
// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A free function because its address sits in
// GfDataBlade.cpp's unit next to fn_7100254DC4 (its only caller), among no class of its own. What it does: when
// GfBdatBtl is up, stores (GfBdatBtl::fn_71001E9520(11, 0) - fn_71001E91E8(11)) / fn_71001E92F8(11) (0 when that
// divisor is 0) at the option's 0x2E, and the same for row 12 at 0x2F.
void fn_7100254DF0(SSoundUiOption* option);
// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A free function because its address sits in
// GfDataBlade.cpp's unit after fn_7100254EF0 (before GfDataBlade's own functions), among no class of its own, and it
// reads the bytes fn_7100254DC4 stores. What it does: when GfBdatBtl is up, the option's byte at 0x24 + index - 1
// (m_list), else 0.
unsigned char fn_71002550C0(const SSoundUiOption* option, unsigned int index);

// the sound and screen part of the option settings, 0x3C bytes at SDataOption+0x4C (1.0.0's
// SSoundUiOption::clear and isDirty)
struct SSoundUiOption {
    void clear();
    // the clear's last part, out of line in 3.0.1 (GfGameLoad::execOptionLoadWithMicroThread calls it).
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because clear() does the same
    // stores on its own object. What it does: stores the 0xED 0xB0 0x1E 0x5F 0x06 bytes at 0x1F, clears 0x24..0x32
    // and 0x3B, calls fn_7100254EF0(this, 0), clears 0x33..0x38.
    void fn_710022E334();
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because it reads the bytes clear()
    // stores (GfGameLoad::execOptionLoadWithMicroThread calls it on the loaded option's). What it does: true unless
    // 0x1F..0x22 hold clear()'s 0xED 0xB0 0x1E 0x5F, 0x23 is at most 6 and 0x33..0x36 are at most 1 each.
    bool fn_710022E380() const;
    // 1.0.0's isDirty (GfMenuObjOption's unit holds it): true when other differs from it
    bool isDirty(const SSoundUiOption& other);

    // the master volumes as 0..255 (GfMasterVolume's thirteen, in its order; the name is not the original's)
    unsigned short m_volume[13];
    // 0..255: GfMenuManager::applyOptionData divides it by 255 for applyGammaCorrectValue (the name is not the original's)
    unsigned short m_gamma;
    // the event subtitles' option: GfMenuObjEventSubtitle shows a first line that is not vertical only when it is
    // set (the name is not the original's)
    bool m_eventSubtitle;
    unsigned char pad_1D[0x1];
    // 0x1E-0x3C: what these hold is not known; the names are not the original's. clear() stores 0 at 0x1E;
    // fn_710022E334 stores the 0x1F-0x22 key (one 32-bit run of bitfields: a single unaligned store, separate loads in
    // fn_710022E380), 6 at 0x23, clears m_list and 0x3B, and clears the flags after fn_7100254EF0 (one 48-bit run).
    // fn_710022E380 loads 0x22 and 0x23 with one ldrh, as if m_keyD were in the key's run; that layout breaks
    // fn_710022E334's store order, so m_keyD stays a byte here
    unsigned char m_byte1E;
    unsigned int m_keyA : 8;
    unsigned int m_keyB : 16;
    unsigned int m_keyC : 8;
    unsigned char m_keyD;
    unsigned char m_list[0xF];
    unsigned int m_flagA : 8;
    unsigned int m_flagB : 8;
    unsigned int m_flagC : 8;
    unsigned int m_flagD : 8;
    unsigned int m_flagE : 8;
    unsigned int m_flagF : 8;
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
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because it works on its own
    // m_soundUi (its address sits in GfWeapon.cpp's unit next to GfGameUtilSaveData's functions). What it does:
    // calls fn_7100254DF0 on m_soundUi; GfMenuObjOption::MainListener calls it on the option it saves.
    void fn_71002EEB0C();

    // 0x3A15B as made, as SDataSystem's (the name is not the original's)
    unsigned int m_version;
    // 0x4-0x4C: cleared as made, all but 0xB (made 1); what they hold is not known (the names are not the
    // original's)
    unsigned int m_optionWord;
    unsigned short m_optionHalf;
    unsigned char m_optionByte;
    bool m_optionOn;
    unsigned char m_optionBlock[0x40];
    SSoundUiOption m_soundUi;  // 0x4C (the name is not the original's)
};

inline void SDataOption::clear() {
    m_version = 0x3A15B;
    m_optionByte = 0;
    m_optionHalf = 0;
    m_optionWord = 0;
    m_optionOn = true;
    memset(m_optionBlock, 0, sizeof(m_optionBlock));
    m_soundUi.clear();
}
}  // namespace gf

#endif

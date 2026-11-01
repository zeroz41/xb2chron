#ifndef GF_GFGAMEUTILSAVEDATA_H
#define GF_GFGAMEUTILSAVEDATA_H

namespace gf { class SDataOption; }
namespace gf { class SDataSave; }
namespace gf { class SaveMenuInfo; }

namespace gf {
class GfGameUtilSaveData {
public:
    // the option data to compare with: TitleMain's option buffer in the theater or advertise mode (when TitleMain is
    // up), else GfDataManager::getDataOption
    static SDataOption* getValidOptionData();
    // named by the symbols: fills the option data a save writes (GfGameSave::createOptionSaveData)
    static void setupOptionSaveData(SDataOption& option);
    static void flushOptionSaveData();
    // named by the symbols: fills the save menu's summary from TitleMain's save buffer (when its version is
    // 0x3A15B) or else GfGameSave::getGameOptionData
    static void getSaveDataMenuInfo(SaveMenuInfo& info);
    // Placeholder name: the symbols leave it unnamed in 3.0.1 and 1.0.0 (1.0.0's fn_7100355D90, the same tail call
    // of getSaveDataMenuInfo). A member because getSaveDataMenuInfo is its only caller and it sits right after it.
    // What it does: clears the info's 0xF0-byte table, then fills one 16-byte row per u16 id at save+0xE9894
    // (6 bytes apart, while the u16 at save+0x14BD6 is below 10049), each from fn_710024229C's 0x5A0-byte record
    // (u16s at +0x60..+0x66, +0xD0), and sets the byte at info+0x510 from the byte at save+0x1AE91.
    static void fn_71002EAF78(SaveMenuInfo& info, SDataSave* save);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because its address sits among
    // GfGameUtilSaveData's functions (GfWeapon.cpp's unit, after getValidOptionData) and it reads the save data the
    // same way. What it does: takes GfDataManager::getDataGame (TitleMain's save buffer + 0x10 in the theater or
    // advertise mode), and calls fn_7100223650 on its 0xE98D8 and 0x11D27C areas with 0x6398; GfMenuObjOption's
    // difficulty lists use its answer to show all four difficulties.
    static bool fn_71002EDCEC();
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because it is fn_71002EDCEC's
    // twin right before it (same code with item 25495 for 25496). Callers: TitleStateMainScreen::loadSaveDataForTitle,
    // fn_7100154638 and GfMenuObjOption::initialize.
    static bool fn_71002EDC78();
};
}  // namespace gf

#endif

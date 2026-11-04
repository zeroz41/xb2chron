#ifndef GF_GFGAMEUTILSAVEDATA_H
#define GF_GFGAMEUTILSAVEDATA_H

namespace gf { class SDataOption; }
namespace gf { class SDataSaveIra; }
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
    // 0x3A15B) or else GfGameSave::getIraGameSaveData
    static void getSaveDataMenuInfo(SaveMenuInfo& info);
    // Placeholder name: the symbols leave it unnamed in 3.0.1 and 1.0.0 (1.0.0's fn_7100355D90, the same tail call
    // of getSaveDataMenuInfo). A member because getSaveDataMenuInfo is its only caller and it sits right after it.
    // What it does: clears the info's 0xF0-byte table, then fills one 16-byte row per u16 id at save+0xE9894
    // (6 bytes apart, while the u16 at save+0x14BD6 is below 10049), each from GfDataDriver::getDriverRelativeID's 0x5A0-byte record
    // (u16s at +0x60..+0x66, +0xD0), and sets the byte at info+0x510 from the byte at save+0x1AE91.
    static void fn_71002EAF78(SaveMenuInfo& info, SDataSaveIra* save);
};
}  // namespace gf

#endif

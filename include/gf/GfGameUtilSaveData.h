#ifndef GF_GFGAMEUTILSAVEDATA_H
#define GF_GFGAMEUTILSAVEDATA_H

namespace gf { class SDataOption; }

namespace gf {
class GfGameUtilSaveData {
public:
    // the option data to compare with: TitleMain's option buffer in the theater or advertise mode (when TitleMain is
    // up), else GfDataManager::getDataOption
    static SDataOption* getValidOptionData();
    // named by the symbols: fills the option data a save writes (GfGameSave::createOptionSaveData)
    static void setupOptionSaveData(SDataOption& option);
    static void flushOptionSaveData();
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because its address sits among
    // GfGameUtilSaveData's functions (GfWeapon.cpp's unit, after getValidOptionData) and it reads the save data the
    // same way. What it does: takes GfDataManager::getDataGame (TitleMain's save buffer + 0x10 in the theater or
    // advertise mode), and calls fn_7100223650 on its 0xE98D8 and 0x11D27C areas with 0x6398; GfMenuObjOption's
    // difficulty lists use its answer to show all four difficulties.
    static bool fn_71002EDCEC();
};
}  // namespace gf

#endif

#ifndef GF_GFDATASAVE_H
#define GF_GFDATASAVE_H

#include "mm/mtl/FixStr.h"

namespace gf { enum SAVESLOT : int; }

namespace gf {
// the save files' names (functions, by its symbols)
class GfDataSave {
public:
    // "save:/" (1.0.0's symbol; 3.0.1 inlines it everywhere and its linker dropped the copy)
    static void getSaveDataPath(mm::mtl::FixStr<256>& out);
    // "bf2savefile" (1.0.0's symbol; dropped by 3.0.1's linker, its string kept in the unit's .rodata)
    static const char* getSaveDataFileName();
    // 2.0.0's symbols name it. What it does: returns "irasavefile"; LoadIraSaveData::loadData calls it,
    // getFileNameForIraLoad/getFileNameForIraSave inline it.
    static const char* getIraSaveDataFileName();
    // "bf2option" (1.0.0's symbol; dropped by 3.0.1's linker, its string kept)
    static const char* getOptionSaveDataFileName();
    // "bf2chapter" (1.0.0's symbol; dropped by 3.0.1's linker, its string kept)
    static const char* getChapterSaveDataFileName();
    // ".xml" (1.0.0's symbol; dropped by 3.0.1's linker, its string kept)
    static const char* getSaveDataExtNameForXml();
    static void getFileNameForLoad(mm::mtl::FixStr<256>& out, SAVESLOT slot);
    static void getFileNameForSave(mm::mtl::FixStr<256>& out, SAVESLOT slot);
    // 2.0.0's symbols name it. What it does: getFileNameForSave with "irasavefile"/"irachapter" for
    // "bf2savefile"/"bf2chapter".
    static void getFileNameForIraSave(mm::mtl::FixStr<256>& out, SAVESLOT slot);
    // 2.0.0's symbols name it. What it does: getFileNameForIraSave, then ".sav" appended;
    // GfGameSave::createGameSaveData calls it.
    static void getFileNameForIraSaveBin(mm::mtl::FixStr<256>& out, SAVESLOT slot);
    // getFileNameForSave, then ".sav" appended (1.0.0's symbol: the same code, called by createGameSaveData there
    // and in 3.0.1; 2.0.0's symbols name it too)
    static void getFileNameForSaveBin(mm::mtl::FixStr<256>& out, SAVESLOT slot);
    static void getFileNameForOption(mm::mtl::FixStr<256>& out);
    // named by the symbols: GfGameSave::createOptionSaveData's file name, the Ira one when
    // GfGameManager::isGameTypeIra was set
    static void getFileNameForIraOptionBin(mm::mtl::FixStr<256>& out);
    static void getFileNameForOptionBin(mm::mtl::FixStr<256>& out);
    static const char* getSaveDataExtNameForBin();
    // 2.0.0's symbols name it. What it does: out = "save:/" + "irasavefile", then the slot's number formatted after it
    // for slots below 10; slot 0x16 gets no number, -1 an empty name, others a formatted path of slot - 8. GfGameLoad::
    // getGameFileNameBin calls it instead of getFileNameForLoad when GfGameManager::isGameTypeIra was set.
    static void getFileNameForIraLoad(mm::mtl::FixStr<256>& out, SAVESLOT slot);
    // 2.0.0's symbols name it. What it does: out = "save:/" + "iraoption". GfGameLoad::getOptionFileNameBin calls it
    // instead of getFileNameForOption when GfGameManager::isGameTypeIra was set.
    static void getFileNameForIraOption(mm::mtl::FixStr<256>& out);
};
}  // namespace gf

#endif

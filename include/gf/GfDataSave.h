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
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because it sits between
    // GfDataSave's name getters (1.0.0's getSaveDataFileName and getOptionSaveDataFileName strings around its own).
    // What it does: returns "irasavefile"; fn_71002C235C calls it, fn_710022C2B0/fn_710022C63C inline it.
    static const char* fn_710022C0FC();
    // "bf2option" (1.0.0's symbol; dropped by 3.0.1's linker, its string kept)
    static const char* getOptionSaveDataFileName();
    // "bf2chapter" (1.0.0's symbol; dropped by 3.0.1's linker, its string kept)
    static const char* getChapterSaveDataFileName();
    // ".xml" (1.0.0's symbol; dropped by 3.0.1's linker, its string kept)
    static const char* getSaveDataExtNameForXml();
    static void getFileNameForLoad(mm::mtl::FixStr<256>& out, SAVESLOT slot);
    static void getFileNameForSave(mm::mtl::FixStr<256>& out, SAVESLOT slot);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because it sits next to
    // getFileNameForSave and does its work for the other file set. What it does: getFileNameForSave with
    // "irasavefile"/"irachapter" for "bf2savefile"/"bf2chapter".
    static void fn_710022C63C(mm::mtl::FixStr<256>& out, SAVESLOT slot);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member for the same reason (next to
    // getFileNameForSaveBin's 3.0.1 copy fn_710022C8FC). What it does: fn_710022C63C, then ".sav" appended;
    // GfGameSave::createGameSaveData calls it.
    static void fn_710022C96C(mm::mtl::FixStr<256>& out, SAVESLOT slot);
    // getFileNameForSave, then ".sav" appended (1.0.0's symbol: the same code, called by createGameSaveData there
    // and in 3.0.1, where the symbols spell it fn_710022C8FC)
    static void getFileNameForSaveBin(mm::mtl::FixStr<256>& out, SAVESLOT slot);
    static void getFileNameForOption(mm::mtl::FixStr<256>& out);
    // named by the symbols: GfGameSave::createOptionSaveData's file name, the Xml one when
    // GfGameManager::fn_71002A9E68 was set
    static void getFileNameForOptionXml(mm::mtl::FixStr<256>& out);
    static void getFileNameForOptionBin(mm::mtl::FixStr<256>& out);
    static const char* getSaveDataExtNameForBin();
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because it sits among
    // GfDataSave's file-name functions (getFileNameForLoad 0x710022C114, getFileNameForOption 0x710022C82C) and does
    // their work. What it does: out = "save:/" + "irasavefile", then the slot's number formatted after it for slots
    // below 10; slot 0x16 gets no number, -1 an empty name, others a formatted path of slot - 8. GfGameLoad::
    // getGameFileNameBin calls it instead of getFileNameForLoad when GfGameManager::fn_71002A9E68 was set.
    static void fn_710022C2B0(mm::mtl::FixStr<256>& out, SAVESLOT slot);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member for the same reason (next to
    // getFileNameForOption). What it does: out = "save:/" + "iraoption". GfGameLoad::getOptionFileNameBin calls it
    // instead of getFileNameForOption when GfGameManager::fn_71002A9E68 was set.
    static void fn_710022C894(mm::mtl::FixStr<256>& out);
};
}  // namespace gf

#endif

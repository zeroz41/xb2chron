#ifndef GF_GFDATASAVE_H
#define GF_GFDATASAVE_H

#include "mm/mtl/FixStr.h"

namespace gf { enum SAVESLOT : int; }

namespace gf {
// the save files' names (functions, by its symbols)
class GfDataSave {
public:
    static void getFileNameForLoad(mm::mtl::FixStr<256>& out, SAVESLOT slot);
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

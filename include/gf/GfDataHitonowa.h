#ifndef GF_GFDATAHITONOWA_H
#define GF_GFDATAHITONOWA_H

namespace mm { namespace mtl { template <typename, unsigned long> class FixedVector; }}

namespace gf {

// the hitonowa (NPC affinity chart) data's helpers (functions; 2.0.0's symbols name the class)
class GfDataHitonowa {
public:
    static void setHitonowaEntry(unsigned int id, unsigned int mode);
    static unsigned int getFlagLevel();
    // 2.0.0's symbols name it. What it does: local flag 652 (type 4) (GfGameFlag::getLocal(4, 652)).
    static unsigned int getFlag4Level();
    // 2.0.0's symbols name it. What it does: takes nothing; constructs (guarded, __cxa_atexit) two function-static
    // lists (guards 0x7100C339F0/F8) and zeroes their counts (0x7100C33C68, 0x7100C33E70). GfDataManager's constructor
    // calls it.
    static void initialize();
    // 2.0.0's symbols name it. What it does: the same code as GfDataHitonowa::initialize (the same two lists, counts
    // zeroed); GfDataManager::destroy calls it.
    static void finalize();
    // 2.0.0's symbols name it. What it does: walks GfBdatRsc's NPC list (getRscNpcListStart..End,
    // getRscNpcListHitonowaFlag) into the same function-static lists; GfDataManager::setupGame and gevReloadBdat (type
    // 1) call it.
    static void bdatRefresh();
    // 2.0.0's symbols name it. What it does: returns the first function-static list (the NPCs above 2000 with a
    // GfBdatRsc::getRscNpcListHitonowaFlag hitonowa flag, filled by GfDataHitonowa::bdatRefresh); GfMenuObjHitonowa::initialize
    // (hitonowa menu) reads it.
    static mm::mtl::FixedVector<unsigned short, 256>& getList();
    // 2.0.0's symbols name it. What they do: walk the second function-static list (one NPC per hitonowa flag value).
    // GfDataHitonowa::getCompleteNum: total = its count, set = the entries whose flag's local value (type 2) is 1 or 3
    // (GfDataHitonowa::getFlagLevel, GfMenuObjHitonowa::initialize call it); GfDataHitonowa::getMeetsNum: the entries whose
    // GfBdatRsc::getRscNpcListNpcMeetFlag flag is set (type 1); GfDataHitonowa::getHitonowaNum: the entries whose
    // type-2 local value is 1 (both called by GfGameScene::updateAutoFlag).
    static void getCompleteNum(unsigned int& set, unsigned int& total);
    static int getMeetsNum();
    static int getHitonowaNum();
    // 2.0.0's symbols name it. What they do: for an id above 2000 with a GfBdatRsc::getRscNpcListHitonowaFlag value v,
    // the 1-based slot i of the 8-bit local flags 0x10C4 + i (GfDataHitonowa::getEntryOn) or 0x11C5 + i
    // (GfDataHitonowa::getEntryComplete), i < 256, that holds v - 0xED02; 0 when none.
    static unsigned int getEntryOn(unsigned int id);
    static unsigned int getEntryComplete(unsigned int id);
};

}  // namespace gf

#endif

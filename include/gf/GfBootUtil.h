#ifndef GF_GFBOOTUTIL_H
#define GF_GFBOOTUTIL_H

namespace gf {

// the boot helpers (functions; 2.0.0's symbols name the class)
class GfBootUtil {
public:
    // 2.0.0's symbols name it. What it does: when run is set, stores type at .bss 0x7100EA4890
    // (GfBootUtil::getBootType's) and, when GfScriptManager is up, loads the "aoc_boot" script (slot 0x46), waits for
    // it to load (GfSleep(1)), runs it to its end unless its load failed, destroys it and clears that int again.
    // tl::TitleStatePlayGame::enter calls it.
    static void execBootScriptWithMicroThread(unsigned int type, bool run);
    // 2.0.0's symbols name it. What it does: returns the int at .bss 0x7100EA4890, which execBootScriptWithMicroThread
    // (called by tl::TitleStatePlayGame::enter) stores from its first argument before running the "aoc_boot" script
    // (GfScriptManager slot 0x46) and clears afterwards. The sys plugin's getBootType returns it to scripts.
    static int getBootType();
};

}  // namespace gf

#endif

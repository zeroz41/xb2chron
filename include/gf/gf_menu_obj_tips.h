#ifndef GF_GF_MENU_OBJ_TIPS_H
#define GF_GF_MENU_OBJ_TIPS_H

namespace gf {
// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A free function in gf because its unit
// (gf_menu_obj_tips) has no proven class yet. What it does: for a tips id inside BDAT file 0x102's id range (from
// Bdat::getIdTop), works on that tips row; ScriptPlayText's ui unlockTips passes its script argument.
void fn_7100487A90(unsigned int id);
// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A free function in gf for the same reason.
// What it does: for an id at or past BDAT file 0x102's Bdat::getIdTop, clears bit 1 of local game flag 2's entry
// id - top + 0xEF05 (GfGameFlag::getLocal, then setLocal with value & 0xFFFD). GfMenuManager::gevChangeScenarioFlag
// passes 0x92 and 0x93 for scenario flag 0x2B38.
void fn_7100487B08(unsigned int id);
}  // namespace gf

#endif

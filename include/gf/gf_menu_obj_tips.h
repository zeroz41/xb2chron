#ifndef GF_GF_MENU_OBJ_TIPS_H
#define GF_GF_MENU_OBJ_TIPS_H

namespace gf {
// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A free function in gf because its unit
// (gf_menu_obj_tips) has no proven class yet. What it does: for a tips id inside BDAT file 0x102's id range (from
// Bdat::getIdTop), works on that tips row; ScriptPlayText's ui unlockTips passes its script argument.
void fn_7100487A90(unsigned int id);
}  // namespace gf

#endif

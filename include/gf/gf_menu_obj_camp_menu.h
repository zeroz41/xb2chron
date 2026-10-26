#ifndef GF_GF_MENU_OBJ_CAMP_MENU_H
#define GF_GF_MENU_OBJ_CAMP_MENU_H

namespace gf {
// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A free function in gf because its unit
// (gf_menu_obj_camp_menu) has no proven class yet. What it does: GfMenuFlag::set1(0x54, 0); ScriptPlayText's ui
// setCampTalkNew calls it.
void fn_71003BBCDC();
// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A free function in gf for the same reason.
// What it does: returns the 32-bit global at 0x7100EAA1D0 (the camp menu unit's .bss), which fn_71003BBB48 clears.
// Caller: GfMenuManager::fn_710035DCC0 (compares it with 1).
int fn_71003BBB38();
// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A free function in gf for the same reason.
// What it does: takes the attached object 0x8D (GfMenuObject::getAttachedObject), and when its ui::UIObjectAcc is
// valid sends an open event (0, child "LAY_menu", 0.0f) and clears the global fn_71003BBB38 returns.
// Caller: GfMenuManager::fn_710035DC28 when its layer-300 flag is already set.
void fn_71003BBB48();
}  // namespace gf

#endif

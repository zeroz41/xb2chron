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
// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A free function in gf for the same reason.
// What it does: when the attached object 0x8D's ui::UIObjectAcc is valid, sends event 0x101 (parameters zero) to its
// child "LAY_shop" and clears g_campMenuState. Caller: GfMenuObjShop::ExcTaskListListener::reciveEvent.
void fn_71003BBBAC();
// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A free function in gf for the same reason.
// What it does: when the attached object 0x8D's ui::UIObjectAcc is valid, GfMenuObject::enableInput on its child
// "LAY_chr_change". Caller: GfMenuObjShop::ExcTaskListListener::reciveEvent.
void fn_71003BBC1C();
// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A free function in gf for the same reason.
// What it does: the same as fn_71003BBC1C with GfMenuObject::disableInput. Caller: as fn_71003BBC1C.
void fn_71003BBC7C();
// Proposed name, not the original's: the symbols leave it unnamed (lbl_7100EAA1D0). Reached through the GOT, so
// external. fn_71003BBB38 returns it; the camp menu's listeners set it to 1 (and 0), fn_71003BBB48/fn_71003BBBAC
// clear it after sending their event.
extern int g_campMenuState;
}  // namespace gf

#endif

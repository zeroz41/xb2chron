#ifndef GF_GF_MENU_OBJ_CAMP_MENU_H
#define GF_GF_MENU_OBJ_CAMP_MENU_H

namespace gf {
// Proposed name, not the original's: the symbols leave it unnamed (lbl_7100EAA1D0). Reached through the GOT, so
// external. GfMenuObjCampMenu::getSelectResult returns it; the camp menu's listeners set it to 1 (and 0),
// GfMenuObjCampMenu::returnFromEvent/closeShopToTalk clear it after sending their event.
extern int g_campMenuState;
}  // namespace gf

#endif

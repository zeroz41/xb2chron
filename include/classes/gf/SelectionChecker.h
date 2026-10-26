#ifndef CLASSES_GF_SELECTIONCHECKER_H
#define CLASSES_GF_SELECTIONCHECKER_H

#include "classes/ui/IUIInputSelectionChecker.h"

namespace gf {
// table 0x7100B630C8 (gf_menu_obj_mainmenu2's): GfMenuObjMainMenu2's constructor creates one
class SelectionChecker : public ::ui::IUIInputSelectionChecker {
public:
    // the condition (GfMenuObjUtil::getMenuCondition) of the select-th row's useCond in the main menu's BDAT
    virtual bool isEnableSelect(unsigned int id, int select);  // slot 0
};
}  // namespace gf

#endif

#ifndef CLASSES_UI_UIFONTMANAGER_H
#define CLASSES_UI_UIFONTMANAGER_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace ui { class UIFontManager; }

namespace ui {
// table 0x7100B74A90
class UIFontManager : public ::mm::mtl::PtrSingleton< ::ui::UIFontManager> {
public:
    virtual ~UIFontManager();  // slot 0
};
}  // namespace ui

#endif

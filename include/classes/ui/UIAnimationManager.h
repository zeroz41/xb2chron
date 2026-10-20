#ifndef CLASSES_UI_UIANIMATIONMANAGER_H
#define CLASSES_UI_UIANIMATIONMANAGER_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace ui { class UIAnimationManager; }

namespace ui {
// table 0x7100B74320
class UIAnimationManager : public ::mm::mtl::PtrSingleton< ::ui::UIAnimationManager> {
public:
    virtual ~UIAnimationManager();  // slot 0
};
}  // namespace ui

#endif

#ifndef CLASSES_UI_UICTRLMANAGER_H
#define CLASSES_UI_UICTRLMANAGER_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace ui { class UICtrlManager; }

namespace ui {
// table 0x7100B74498
class UICtrlManager : public ::mm::mtl::PtrSingleton< ::ui::UICtrlManager> {
public:
    virtual ~UICtrlManager();  // slot 0
};
}  // namespace ui

#endif

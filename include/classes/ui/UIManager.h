#ifndef CLASSES_UI_UIMANAGER_H
#define CLASSES_UI_UIMANAGER_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace ui { class UIManager; }

namespace ui {
// table 0x7100B75678
class UIManager : public ::mm::mtl::PtrSingleton< ::ui::UIManager> {
public:
    virtual ~UIManager();  // slot 0
};
}  // namespace ui

#endif

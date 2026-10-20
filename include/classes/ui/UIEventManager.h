#ifndef CLASSES_UI_UIEVENTMANAGER_H
#define CLASSES_UI_UIEVENTMANAGER_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace ui { class UIEventManager; }

namespace ui {
// table 0x7100B74668
class UIEventManager : public ::mm::mtl::PtrSingleton< ::ui::UIEventManager> {
public:
    virtual ~UIEventManager();  // slot 0
};
}  // namespace ui

#endif

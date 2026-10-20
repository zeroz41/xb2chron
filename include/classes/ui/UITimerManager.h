#ifndef CLASSES_UI_UITIMERMANAGER_H
#define CLASSES_UI_UITIMERMANAGER_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace ui { class UITimerManager; }

namespace ui {
// table 0x7100B755B8
class UITimerManager : public ::mm::mtl::PtrSingleton< ::ui::UITimerManager> {
public:
    virtual ~UITimerManager();  // slot 0
};
}  // namespace ui

#endif

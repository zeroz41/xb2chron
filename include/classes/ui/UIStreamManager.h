#ifndef CLASSES_UI_UISTREAMMANAGER_H
#define CLASSES_UI_UISTREAMMANAGER_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace ui { class UIStreamManager; }

namespace ui {
// table 0x7100B75460
class UIStreamManager : public ::mm::mtl::PtrSingleton< ::ui::UIStreamManager> {
public:
    virtual ~UIStreamManager();  // slot 0
};
}  // namespace ui

#endif

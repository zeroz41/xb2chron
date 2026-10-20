#ifndef CLASSES_UI_UITEXTMANAGER_H
#define CLASSES_UI_UITEXTMANAGER_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace ui { class UITextManager; }

namespace ui {
// table 0x7100B75558
class UITextManager : public ::mm::mtl::PtrSingleton< ::ui::UITextManager> {
public:
    virtual ~UITextManager();  // slot 0
};
}  // namespace ui

#endif

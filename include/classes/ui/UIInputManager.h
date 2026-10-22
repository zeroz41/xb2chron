#ifndef CLASSES_UI_UIINPUTMANAGER_H
#define CLASSES_UI_UIINPUTMANAGER_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace ui { class UIInputManager; }

namespace ui {
// table 0x7100B74B30
class UIInputManager : public ::mm::mtl::PtrSingleton< ::ui::UIInputManager> {
public:
    virtual ~UIInputManager();  // slot 0
    unsigned int searchInputHandle(unsigned int object);  // the input layer the UI object has, 0 for none
    void enableInput(unsigned int handle);
    void disableInput(unsigned int handle);
};
}  // namespace ui

#endif

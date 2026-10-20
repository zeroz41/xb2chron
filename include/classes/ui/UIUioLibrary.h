#ifndef CLASSES_UI_UIUIOLIBRARY_H
#define CLASSES_UI_UIUIOLIBRARY_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace ui { class UIUioLibrary; }

namespace ui {
// table 0x7100B75838
class UIUioLibrary : public ::mm::mtl::PtrSingleton< ::ui::UIUioLibrary> {
public:
    virtual ~UIUioLibrary();  // slot 0
};
}  // namespace ui

#endif

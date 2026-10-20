#ifndef CLASSES_UI_UIMOTIONLIBRARY_H
#define CLASSES_UI_UIMOTIONLIBRARY_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace ui { class UIMotionLibrary; }

namespace ui {
// table 0x7100B74D90
class UIMotionLibrary : public ::mm::mtl::PtrSingleton< ::ui::UIMotionLibrary> {
public:
    virtual ~UIMotionLibrary();  // slot 0
};
}  // namespace ui

#endif

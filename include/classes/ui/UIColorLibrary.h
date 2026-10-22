#ifndef CLASSES_UI_UICOLORLIBRARY_H
#define CLASSES_UI_UICOLORLIBRARY_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace ui { class UIColorLibrary; }
namespace mm { struct Col4; }

namespace ui {
// table 0x7100B755F8
class UIColorLibrary : public ::mm::mtl::PtrSingleton< ::ui::UIColorLibrary> {
public:
    virtual ~UIColorLibrary();  // slot 0
    bool find(const char* name, mm::Col4& color);  // the colour the library names; false when it has none
};
}  // namespace ui

#endif

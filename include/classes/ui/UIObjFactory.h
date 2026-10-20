#ifndef CLASSES_UI_UIOBJFACTORY_H
#define CLASSES_UI_UIOBJFACTORY_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace ui { class UIObjFactory; }

namespace ui {
// table 0x7100B748B0
class UIObjFactory : public ::mm::mtl::PtrSingleton< ::ui::UIObjFactory> {
public:
    virtual ~UIObjFactory();  // slot 0
};
}  // namespace ui

#endif

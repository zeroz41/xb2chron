#ifndef CLASSES_GMK_GMKANTIBLADEAREAMANAGER_H
#define CLASSES_GMK_GMKANTIBLADEAREAMANAGER_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace gmk { class GmkAntiBladeAreaManager; }

namespace gmk {
// table 0x7100B519B8
class GmkAntiBladeAreaManager : public ::mm::mtl::PtrSingleton< ::gmk::GmkAntiBladeAreaManager> {
public:
    virtual ~GmkAntiBladeAreaManager();  // slot 0
};
}  // namespace gmk

#endif

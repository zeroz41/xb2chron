#ifndef CLASSES_BTL_HATERINGMANAGER_H
#define CLASSES_BTL_HATERINGMANAGER_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace btl { class HateRingManager; }

namespace btl {
// table 0x7100B3BC60
class HateRingManager : public ::mm::mtl::PtrSingleton< ::btl::HateRingManager> {
public:
    virtual ~HateRingManager();  // slot 0
    static void Create();
    static void Destroy();
};
}  // namespace btl

#endif

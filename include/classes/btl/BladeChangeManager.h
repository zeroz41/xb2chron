#ifndef CLASSES_BTL_BLADECHANGEMANAGER_H
#define CLASSES_BTL_BLADECHANGEMANAGER_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace btl { class BladeChangeManager; }

namespace btl {
// table 0x7100B3A8C0
class BladeChangeManager : public ::mm::mtl::PtrSingleton< ::btl::BladeChangeManager> {
public:
    virtual ~BladeChangeManager();  // slot 0
};
}  // namespace btl

#endif

#ifndef CLASSES_BTL_BLADEARTSMANAGER_H
#define CLASSES_BTL_BLADEARTSMANAGER_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace btl { class BladeArtsManager; }

namespace btl {
// table 0x7100B3A880
class BladeArtsManager : public ::mm::mtl::PtrSingleton< ::btl::BladeArtsManager> {
public:
    virtual ~BladeArtsManager();  // slot 0
    static void Create();
    static void Destroy();
};
}  // namespace btl

#endif

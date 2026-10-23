#ifndef CLASSES_BTL_UIMANAGER_H
#define CLASSES_BTL_UIMANAGER_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace btl { class UIManager; }

namespace btl {
// table 0x7100B3BE28
class UIManager : public ::mm::mtl::PtrSingleton< ::btl::UIManager> {
public:
    virtual ~UIManager();  // slot 0
    static void Create();
    static void Destroy();
};
}  // namespace btl

#endif

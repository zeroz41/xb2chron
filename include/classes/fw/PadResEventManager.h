#ifndef CLASSES_FW_PADRESEVENTMANAGER_H
#define CLASSES_FW_PADRESEVENTMANAGER_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace fw { class PadResEventManager; }

namespace fw {
// table 0x7100B42900
class PadResEventManager : public ::mm::mtl::PtrSingleton< ::fw::PadResEventManager> {
public:
    virtual ~PadResEventManager();  // slot 0
};
}  // namespace fw

#endif

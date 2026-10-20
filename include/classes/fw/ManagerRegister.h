#ifndef CLASSES_FW_MANAGERREGISTER_H
#define CLASSES_FW_MANAGERREGISTER_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace fw { class ManagerRegister; }

namespace fw {
// table 0x7100B41E30
class ManagerRegister : public ::mm::mtl::PtrSingleton< ::fw::ManagerRegister> {
public:
    virtual ~ManagerRegister();  // slot 0
};
}  // namespace fw

#endif

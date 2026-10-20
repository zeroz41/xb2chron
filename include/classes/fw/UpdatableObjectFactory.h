#ifndef CLASSES_FW_UPDATABLEOBJECTFACTORY_H
#define CLASSES_FW_UPDATABLEOBJECTFACTORY_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace fw { class UpdatableObjectFactory; }

namespace fw {
// table 0x7100B42590
class UpdatableObjectFactory : public ::mm::mtl::PtrSingleton< ::fw::UpdatableObjectFactory> {
public:
    virtual ~UpdatableObjectFactory();  // slot 0
};
}  // namespace fw

#endif

#ifndef CLASSES_FW_MODELOBJECT_H
#define CLASSES_FW_MODELOBJECT_H

#include "classes/mm/mtl/ReferenceObject.h"

namespace fw {
// table 0x7100B42270; counted: create zeroes the count at 0x8 as ReferenceObject's constructor does, and
// UIScreenObject's destructor releases it with reference_object.h's assertion
class ModelObject : public ::mm::mtl::ReferenceObject {
public:
    virtual ~ModelObject();  // slot 0
    virtual void update();  // slot 2
};
}  // namespace fw

#endif

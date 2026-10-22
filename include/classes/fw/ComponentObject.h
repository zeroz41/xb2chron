#ifndef CLASSES_FW_COMPONENTOBJECT_H
#define CLASSES_FW_COMPONENTOBJECT_H

#include "mm/mtl/RTTI.h"

namespace fw { class UpdatableObject; }

namespace fw {
// table none (its derived classes'): one of an object's components, held in the object's slots
class ComponentObject {
public:
    virtual const mm::mtl::RTTI* getRTTI() const = 0;  // slot 0
    virtual ~ComponentObject() {}  // slot 1
    unsigned int getLayer() const;

    fw::UpdatableObject* m_owner;  // the object holding it (UpdatableObject::registComponentLocal sets it)
};
}  // namespace fw

#endif

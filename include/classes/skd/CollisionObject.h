#ifndef CLASSES_SKD_COLLISIONOBJECT_H
#define CLASSES_SKD_COLLISIONOBJECT_H

#include "classes/anm/ReferenceObject.h"

namespace skd {
// table 0x7100B81648; counted (skd::Factory::createColObject makes one; DynamicsColObjUpdater::bind references it)
class CollisionObject : public anm::ReferenceObject {
public:
    virtual ~CollisionObject();  // slot 0
    void update();
};
}  // namespace skd

#endif

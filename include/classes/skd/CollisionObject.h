#ifndef CLASSES_SKD_COLLISIONOBJECT_H
#define CLASSES_SKD_COLLISIONOBJECT_H

#include "classes/anm/ReferenceObject.h"
#include "classes/anm/Pose.h"
#include "skd/CollisionObj.h"

namespace skd { class ResCollisionArray; }

namespace skd {
// table 0x7100B81648; counted (skd::Factory::createColObject makes one; DynamicsColObjUpdater::bind references it)
class CollisionObject : public anm::ReferenceObject {
public:
    CollisionObject(const ResCollisionArray& res, anm::Pose& pose, mm::mtl::IAllocator* allocator);
    virtual ~CollisionObject();  // slot 0
    void update();

    // the names below are not the original's
    CollionArray m_collisions;  // skd::Dynamics' solvers detect against it
    anm::Pose* m_pPose;         // the pose its shapes follow, referenced
};
}  // namespace skd

#endif

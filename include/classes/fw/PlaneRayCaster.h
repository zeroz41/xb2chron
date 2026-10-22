#ifndef CLASSES_FW_PLANERAYCASTER_H
#define CLASSES_FW_PLANERAYCASTER_H

#include "classes/anm/RaycastInterface.h"

namespace mm { class Vec3; }
namespace fw { class IKFootGroundInterface; }

namespace fw {
// table 0x7100B419C8; casts rays against the plane its ground interface gives
class PlaneRayCaster : public ::anm::RaycastInterface {
public:
    PlaneRayCaster();
    virtual ~PlaneRayCaster() {}  // slot 0 (the table keeps RaycastInterface's)
    virtual bool castRay(const mm::Vec3& from, const mm::Vec3& to, mm::Vec3* pHitPos, mm::Vec3* pNormal);  // slot 2
    void bind(IKFootGroundInterface& ground);

    IKFootGroundInterface* m_ground;  // bind's: castRay's plane comes from it (the name is not the original's)
};
}  // namespace fw

#endif

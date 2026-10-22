#ifndef CLASSES_ANM_RAYCASTINTERFACE_H
#define CLASSES_ANM_RAYCASTINTERFACE_H

namespace mm { class Vec3; }

namespace anm {
// table 0x7100B419A0 (ik_foot_placement_solver.cpp's); fw::PlaneRayCaster's base, whose table keeps this class's
// destructor in its slot 0 (inline and empty: PlaneRayCaster's deleting destructor is a bare operator delete)
class RaycastInterface {
public:
    virtual ~RaycastInterface() {}  // slot 0
    // a ray from `from` to `to`: true when it hits, with the hit's position and the surface normal there
    virtual bool castRay(const mm::Vec3& from, const mm::Vec3& to, mm::Vec3* pHitPos, mm::Vec3* pNormal) = 0;  // slot 2
};
}  // namespace anm

#endif

#ifndef CLASSES_FW_RAYCASTER_H
#define CLASSES_FW_RAYCASTER_H

#include "classes/anm/RaycastInterface.h"

namespace mm { class Vec3; }

namespace fw {
// table 0x7100B419A0 (ik_foot_placement_solver.cpp's); casts rays against the collision (fw::ColiCheck::testLine).
// FootPlacementIKSolver::solve uses one when the solver has no ground interface. Its complete destructor is
// RaycastInterface's (empty), its deleting one a bare operator delete
class Raycaster : public ::anm::RaycastInterface {
public:
    virtual bool castRay(const mm::Vec3& from, const mm::Vec3& to, mm::Vec3* pHitPos, mm::Vec3* pNormal);  // slot 2
};
}  // namespace fw

#endif

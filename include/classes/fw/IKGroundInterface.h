#ifndef CLASSES_FW_IKGROUNDINTERFACE_H
#define CLASSES_FW_IKGROUNDINTERFACE_H

namespace mm { class Plane; }
namespace mm { class Vec3; }
namespace fw { class IKFootGroundInterface; }

namespace fw {
// which foot (passed by value in w1: PlacementGroundSolver hands its solvers' indices); no value has a name yet
enum IKFootIndex {};

// the ground the ground solvers stand on (gf::GfComIK::Ground implements it; the slots' names are its overrides')
class IKGroundInterface {
public:
    virtual IKFootGroundInterface* getFootGround(IKFootIndex index) = 0;  // slot 0: the ground under that foot
    virtual const mm::Plane* getPlane() const = 0;                         // slot 1
    virtual const mm::Vec3* getHitPos() const = 0;                         // slot 2
    virtual const mm::Plane* getPlaneSub() const = 0;                      // slot 3
    virtual const mm::Vec3* getHitPosSub() const = 0;                      // slot 4
};
}  // namespace fw

#endif

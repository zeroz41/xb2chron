#ifndef CLASSES_FW_PLACEMENTGROUNDSOLVER_H
#define CLASSES_FW_PLACEMENTGROUNDSOLVER_H

#include "mm/mtl/RTTI.h"
#include "mm/mtl/IntrusivePtr.h"
#include "mm/mtl/FixedVector.h"
#include "classes/fw/IkSolver.h"
#include "classes/fw/FootPlacementIKSolver.h"
#include "classes/fw/IKGroundInterface.h"

namespace anm { class Pose; }
namespace mm { class Vec3; }
namespace fw { class ParamAdapter; }
namespace fw { class ReferenceFrame; }
namespace fw { class UpdateInfo; }

namespace fw {
// table 0x7100B41A78; an IkSolver (its m_rtti's base): a foot placement solver per foot, and the body lowered to
// the lowest foot's ground
class PlacementGroundSolver : public ::fw::IkSolver {
public:
    // what create sets the solver up with (the field names are not the original's)
    struct Description {
        Description() : maxDown(0.3f), footCount(2) {}

        float maxDown;           // how far solve lowers the body at most
        unsigned int footCount;  // createImpl sizes m_solvers to it
    };

    // 1.0.0 has it out of line; 3.0.1's create inlines it
    PlacementGroundSolver() : m_offset(0.0f), m_enablePlacement(false), m_enableDown(false), m_ground(nullptr) {}
    virtual ~PlacementGroundSolver();  // slot 0
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 2
    virtual void solve(fw::UpdateInfo const&);  // slot 3
    static PlacementGroundSolver* create(const Description& desc, mm::mtl::IntrusivePtr<fw::ReferenceFrame>& frame,
                                         anm::Pose& pose, IKGroundInterface* ground);
    bool createImpl(const Description& desc, mm::mtl::IntrusivePtr<fw::ReferenceFrame>& frame, anm::Pose& pose,
                    IKGroundInterface* ground);
    // a foot placement solver for foot `index` of the bones named, kept in m_solvers; null past the foot count
    FootPlacementIKSolver* createFootPlacementIK(IKFootIndex index, ParamAdapter& param, const char* bone0,
                                                 const char* bone1, const char* bone2, bool flag);
    void setEnablePlacement(bool enable);
    void overwriteRaycastDown(float length);
    void resetRaycastDown();
    void setGroundAngle(const mm::Vec3& angle);
    static mm::mtl::RTTI m_rtti;

    mm::mtl::FixedVector<mm::mtl::IntrusivePtr<FootPlacementIKSolver>, 6> m_solvers;  // one per foot
    Description m_desc;      // createImpl's
    float m_offset;          // the body's height offset solve last applied (the name is not the original's)
    bool m_enablePlacement;  // setEnablePlacement's
    bool m_enableDown;  // FootIkControllerPlugin's down IK (its attribute 0x8 or setEnableDownIK); solve keeps the
                        // root's height when set (the name is not the original's)
    IKGroundInterface* m_ground;  // createImpl's
};
}  // namespace fw

#endif

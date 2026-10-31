#ifndef CLASSES_FW_SLOPEGROUNDSOLVER_H
#define CLASSES_FW_SLOPEGROUNDSOLVER_H

#include "mm/mtl/RTTI.h"
#include "mm/mtl/IntrusivePtr.h"
#include "mm/mtl/FixedVector.h"
#include "mm/Quat.h"
#include "classes/fw/IkSolver.h"
#include "classes/fw/FootPlacementIKSolver.h"
#include "classes/fw/IKGroundInterface.h"

namespace anm { class Pose; }
namespace fw { class ParamAdapter; }
namespace fw { class ReferenceFrame; }
namespace fw { class UpdateInfo; }

namespace fw {
// table 0x7100B41B48; an IkSolver (its m_rtti's base)
class SlopeGroundSolver : public ::fw::IkSolver {
public:
    // what create sets the solver up with (0x20 bytes; the field names are not the original's, the values are its
    // constructor's)
    struct Description {
        Description()
            : pad_0(0.5f), pad_4(0.5f), pad_8(12.0f), pad_c(0.5f), pad_10(8.0f), pad_14(1.57079637f),
              pad_18(1.57079637f), footCount(0) {}

        float pad_0;
        float pad_4;
        float pad_8;
        float pad_c;
        float pad_10;
        float pad_14;  // pi / 2
        float pad_18;  // pi / 2
        unsigned int footCount;  // createImpl sizes m_solvers to it
    };

    // 1.0.0 has it out of line; 3.0.1's create inlines it
    SlopeGroundSolver()
        : m_rotation(mm::Quat::identity), m_enableSlope(true), m_enablePlacement(true), m_ground(nullptr) {}
    virtual ~SlopeGroundSolver();  // slot 0
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 2
    virtual void solve(fw::UpdateInfo const&);  // slot 3
    static SlopeGroundSolver* create(const Description& desc, mm::mtl::IntrusivePtr<fw::ReferenceFrame>& frame,
                                     anm::Pose& pose, IKGroundInterface* ground);
    bool createImpl(const Description& desc, mm::mtl::IntrusivePtr<fw::ReferenceFrame>& frame, anm::Pose& pose,
                    IKGroundInterface* ground);
    // a foot placement solver for foot `index` of the bones named, kept in m_solvers; null past the foot count
    FootPlacementIKSolver* createFootPlacementIK(IKFootIndex index, ParamAdapter& param, const char* bone0,
                                                 const char* bone1, const char* bone2, bool flag);
    void setEnablePlacement(bool enable);
    // tilts the body to the ground (not written yet)
    void slopeBody(fw::UpdateInfo const& info);
    mm::Quat calcRotate(const mm::Quat& from, const mm::Quat& to, float rate);
    // solves every foot's solver
    void solveFoot(fw::UpdateInfo const& info);
    static mm::mtl::RTTI m_rtti;

    // the names of the fields below are not the original's
    Description m_desc;   // createImpl's
    mm::Quat m_rotation;  // identity at first (slopeBody's)
    mm::mtl::FixedVector<mm::mtl::IntrusivePtr<FootPlacementIKSolver>, 6> m_solvers;  // one per foot
    bool m_enableSlope;  // slopeBody tilts the body only when set; FootIkControllerPlugin sets it with the placement
    bool m_enablePlacement;       // setEnablePlacement's
    IKGroundInterface* m_ground;  // createImpl's
};
}  // namespace fw

#endif

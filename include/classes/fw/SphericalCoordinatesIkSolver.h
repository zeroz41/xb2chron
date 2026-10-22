#ifndef CLASSES_FW_SPHERICALCOORDINATESIKSOLVER_H
#define CLASSES_FW_SPHERICALCOORDINATESIKSOLVER_H

#include "mm/mtl/RTTI.h"
#include "mm/mtl/IntrusivePtr.h"
#include "mm/Vec3.h"
#include "anm/SphericalCoordinatesIkSolver.h"
#include "classes/fw/IkSolver.h"
#include "fw/ParamAdapter.h"

namespace anm { class Pose; }
namespace fw { class ReferenceFrame; }
namespace fw { class UpdateInfo; }

namespace fw {
// table 0x7100B41BF8; turns one bone towards m_target within the angles its ParamAdapter holds
class SphericalCoordinatesIkSolver : public ::fw::IkSolver {
public:
    // the parameter block its ParamAdapter holds, in degrees (1.0.0's AngleLimit::createReflection registers the
    // names)
    struct AngleLimit {
        float limitAngleUp;
        float limitAngleDown;
        float limitAngleLeft;
        float limitAngleRight;
    };

    SphericalCoordinatesIkSolver() : m_enable(false) {}
    virtual ~SphericalCoordinatesIkSolver();  // slot 0
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 2
    virtual void solve(fw::UpdateInfo const&);  // slot 3
    virtual bool isEnable() const;  // slot 4
    // a solver turning bone `bone` of the pose within the limits `param` holds; none when the bone is not found
    static SphericalCoordinatesIkSolver* create(const ParamAdapter& param, const char* bone,
                                                mm::mtl::IntrusivePtr<fw::ReferenceFrame>& frame, anm::Pose& pose);
    // binds the solver, finds its bone and sets its limits: false when the bone is not found
    bool setupLimit(const ParamAdapter& param, const char* bone, mm::mtl::IntrusivePtr<fw::ReferenceFrame>& frame,
                    anm::Pose& pose);
    // m_limit from the bone's current turn and the parameter block's angles
    void resetLimit();
    static mm::mtl::RTTI m_rtti;

    anm::SphericalrdinatesIkSolver::Limit m_limit;  // resetLimit's
    mm::Vec3 m_target;     // in world space: solve turns the bone towards it (the name is not the original's)
    unsigned short m_bone;  // setupLimit's: the bone's index
    bool m_enable;          // isEnable's (the name is not the original's)
    ParamAdapter m_param;   // setupLimit's: the AngleLimit block resetLimit reads
};
}  // namespace fw

#endif

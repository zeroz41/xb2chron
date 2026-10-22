#ifndef CLASSES_FW_SPINEROTATEIKSOLVER_H
#define CLASSES_FW_SPINEROTATEIKSOLVER_H

#include "mm/mtl/RTTI.h"
#include "mm/mtl/IntrusivePtr.h"
#include "classes/fw/IkFadeSolver.h"
#include "fw/ParamAdapter.h"

namespace anm { class Pose; }
namespace fw { class ReferenceFrame; }
namespace fw { class UpdateInfo; }

namespace fw {
// table 0x7100B41C30; turns two bones of a spine by m_angleX and m_angleY (degrees), the first bone as far as its
// limits let it and the second the rest
class SpineRotateIKSolver : public ::fw::IkFadeSolver {
public:
    // the parameter block its ParamAdapter holds: each bone's limits in degrees (1.0.0's reflection names the type
    // SpineRotateIKSolver::Param; the field names are not the original's)
    // its parameters (1.0.0's Param::createReflection registers minPitch0/maxPitch0/minPitch1/maxPitch1 and ratio
    // by name at 0x8/0xC/0x18/0x1C/0x20; the four yaw limits it does not register, and their names are not the
    // original's)
    struct Param {
        float firstMinY;
        float firstMaxY;
        float minPitch0;
        float maxPitch0;
        float secondMinY;
        float secondMaxY;
        float minPitch1;
        float maxPitch1;
        float ratio;  // calcIK scales the angles by it before the first bone's limits
    };

    SpineRotateIKSolver() : m_firstBone(0xFFFF), m_secondBone(0xFFFF), m_angleX(0.0f), m_angleY(0.0f) {}
    virtual ~SpineRotateIKSolver();  // slot 0
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 2
    virtual void calcIK(fw::UpdateInfo const&);  // slot 7
    // a solver turning bones `firstBone` and `secondBone` of the pose within the limits `param` holds; none when
    // neither bone is in the pose's skeleton
    static SpineRotateIKSolver* create(const ParamAdapter& param, const char* firstBone, const char* secondBone,
                                       mm::mtl::IntrusivePtr<fw::ReferenceFrame>& frame, anm::Pose& pose);
    // binds the solver and finds its bones: false when neither is found
    bool setupLimit(const ParamAdapter& param, const char* firstBone, const char* secondBone,
                    mm::mtl::IntrusivePtr<fw::ReferenceFrame>& frame, anm::Pose& pose);
    static mm::mtl::RTTI m_rtti;

    ParamAdapter m_param;          // setupLimit's: the Param block calcIK reads
    unsigned short m_firstBone;    // setupLimit's: the first bone's index, 0xFFFF when not found
    unsigned short m_secondBone;   // setupLimit's: the second bone's index, 0xFFFF when not found
    float m_angleX;                // the turn about x in degrees (the names are not the original's)
    float m_angleY;                // the turn about y in degrees
};
}  // namespace fw

#endif

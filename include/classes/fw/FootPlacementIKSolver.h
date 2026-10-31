#ifndef CLASSES_FW_FOOTPLACEMENTIKSOLVER_H
#define CLASSES_FW_FOOTPLACEMENTIKSOLVER_H

#include "mm/mtl/RTTI.h"
#include "mm/mtl/IntrusivePtr.h"
#include "classes/fw/IkSolver.h"
#include "fw/ParamAdapter.h"
#include "anm/QsTransform.h"
#include "mm/Vec3.h"
#include "mm/Quat.h"

namespace anm { class FootPlacementIKSolver; }
namespace anm { class Pose; }
namespace anm { class RaycastInterface; }
namespace fw { class IKFootGroundInterface; }
namespace fw { class ReferenceFrame; }
namespace fw { class UpdateInfo; }

namespace fw {
// table 0x7100B41968; places one foot on the ground its IKFootGroundInterface gives
class FootPlacementIKSolver : public ::fw::IkSolver {
public:
    // what create sets the solver up with (0x30 bytes: createImpl copies it whole); the field names are not the
    // original's
    struct Description {
        Description() : param() {
            boneNames[0] = "";
            boneNames[1] = "";
            boneNames[2] = "";
            pad_18[0] = 180.0f;
            pad_18[1] = 20.0f;
            pad_18[2] = 0.1f;
            pad_24 = false;
            pad_25 = false;
        }

        const char* boneNames[3];  // createImpl finds the three bones by these names
        float pad_18[3];           // two angles (degrees; createImpl hands on their cosines) and the toe's length
                                   // along model z: 180, 20 and 0.1 unless set
        bool pad_24;               // createImpl hands it on to anm::FootPlacementIKSolver::Description
        bool pad_25;               // PlacementGroundSolver::createFootPlacementIK's last argument: createImpl negates
                                   // the foot's forward axis when set
        ParamAdapter param;
    };

    // the parameter block m_desc.param holds (createImpl hands its values on to the anm solver's description; the
    // names are not the original's)
    struct Param {
        float pad_0;
        float pad_4;
        float pad_8;
    };

    // flag bits of m_flags (the names are not the original's)
    enum {
        FLAG_PLACEMENT = 1 << 0,     // PlacementGroundSolver::setEnablePlacement sets or clears it
        FLAG_HIT = 1 << 1,           // solveImpl: the last ray hit the ground
        FLAG_RAYCAST_UP = 1 << 2,    // solveImpl then takes m_raycastUp
        FLAG_RAYCAST_DOWN = 1 << 3,  // overwriteRaycastDown sets it with m_raycastDown, resetRaycastDown clears it
        FLAG_WEIGHT_FULL = 1 << 4,   // solveImpl: the anm solver's weight is at least 1
    };

    virtual ~FootPlacementIKSolver();  // slot 0
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 2
    virtual void solve(fw::UpdateInfo const&);  // slot 3
    // a solver for the foot `desc` names, or null when the pose lacks one of its bones
    static FootPlacementIKSolver* create(const Description& desc, mm::mtl::IntrusivePtr<fw::ReferenceFrame>& frame,
                                         anm::Pose& pose, IKFootGroundInterface* ground);
    // m_groundAngle from Euler angles (radians)
    void setGroundAngle(const mm::Vec3& angle);
    // binds the solver and makes its anm solver from `desc`: false when the pose lacks one of the bones
    bool createImpl(const Description& desc, mm::mtl::IntrusivePtr<fw::ReferenceFrame>& frame, anm::Pose& pose,
                    IKFootGroundInterface* ground);
    // places the foot on the ground `raycaster` finds
    void solveImpl(anm::RaycastInterface& raycaster);
    static mm::mtl::RTTI m_rtti;

    // the names of the fields below m_desc are not the original's
    FootPlacementIKSolver()
        : m_footIk(nullptr), m_footBone(0xFFFF), m_footPos(mm::Vec3::zero), m_flags(0),
          m_groundAngle(mm::Quat::identity), m_groundRotation(mm::Quat::identity), m_ground(nullptr) {}

    anm::FootPlacementIKSolver* m_footIk;  // createImpl's; the destructor releases it
    Description m_desc;  // createImpl's copy
    unsigned short m_footBone;            // the third bone's index
    mm::Vec3 m_footPos;                   // solveImpl's: where the anm solver put the foot
    anm::QsTransform m_footTransform;     // the foot bone's model-space transform when createImpl ran
    unsigned int m_flags;  // FLAG_*
    float m_raycastUp;    // solveImpl's when FLAG_RAYCAST_UP is set
    float m_raycastDown;  // PlacementGroundSolver::overwriteRaycastDown's
    unsigned char pad_ac[0x4];
    mm::Quat m_groundAngle;     // setGroundAngle's; solveImpl turns the up axis by it and m_groundRotation
    mm::Quat m_groundRotation;  // identity unless set
    IKFootGroundInterface* m_ground;  // createImpl's
    unsigned char pad_d8[0x8];
};
}  // namespace fw

#endif

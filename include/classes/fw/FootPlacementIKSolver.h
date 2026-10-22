#ifndef CLASSES_FW_FOOTPLACEMENTIKSOLVER_H
#define CLASSES_FW_FOOTPLACEMENTIKSOLVER_H

#include "mm/mtl/RTTI.h"
#include "mm/mtl/IntrusivePtr.h"
#include "classes/fw/IkSolver.h"
#include "fw/ParamAdapter.h"

namespace anm { class Pose; }
namespace mm { class Vec3; }
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
        float pad_18[3];           // unknown: 180, 20 and 0.1 unless set
        bool pad_24;
        bool pad_25;               // unknown: PlacementGroundSolver::createFootPlacementIK's last argument
        ParamAdapter param;
    };

    // flag bits of m_flags (the names are not the original's)
    enum {
        FLAG_PLACEMENT = 1 << 0,     // PlacementGroundSolver::setEnablePlacement sets or clears it
        FLAG_RAYCAST_DOWN = 1 << 3,  // overwriteRaycastDown sets it with m_raycastDown, resetRaycastDown clears it
    };

    virtual ~FootPlacementIKSolver();  // slot 0
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 2
    virtual void solve(fw::UpdateInfo const&);  // slot 3
    // a solver for the foot `desc` names, or null when the pose lacks one of its bones
    static FootPlacementIKSolver* create(const Description& desc, mm::mtl::IntrusivePtr<fw::ReferenceFrame>& frame,
                                         anm::Pose& pose, IKFootGroundInterface* ground);
    void setGroundAngle(const mm::Vec3& angle);
    static mm::mtl::RTTI m_rtti;

    unsigned char pad_20[0x8];
    Description m_desc;  // createImpl's copy
    unsigned char pad_58[0x48];
    unsigned int m_flags;  // FLAG_*
    unsigned char pad_a4[0x4];
    float m_raycastDown;  // PlacementGroundSolver::overwriteRaycastDown's
    unsigned char pad_ac[0x24];
    IKFootGroundInterface* m_ground;  // createImpl's
    unsigned char pad_d8[0x8];
};
}  // namespace fw

#endif

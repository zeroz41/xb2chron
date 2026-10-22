#ifndef CLASSES_FW_ROTATELOCALIKSOLVER_H
#define CLASSES_FW_ROTATELOCALIKSOLVER_H

#include "mm/mtl/RTTI.h"
#include "mm/mtl/IntrusivePtr.h"
#include "mm/Vec3.h"
#include "classes/fw/IkFadeSolver.h"

namespace anm { class Pose; }
namespace fw { class ReferenceFrame; }

namespace fw { class UpdateInfo; }

namespace fw {
// table 0x7100B41AF8
class RotateLocalIkSolver : public ::fw::IkFadeSolver {
public:
    RotateLocalIkSolver() : m_rotation(mm::Vec3::zero), m_bone(0) {}
    virtual ~RotateLocalIkSolver();  // slot 0
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 2
    virtual void calcIK(fw::UpdateInfo const&);  // slot 7
    // a solver for the bone named `boneName`, or null when the pose has none
    static RotateLocalIkSolver* create(const char* boneName, mm::mtl::IntrusivePtr<fw::ReferenceFrame>& frame, anm::Pose& pose);
    bool setup(const char* boneName, mm::mtl::IntrusivePtr<fw::ReferenceFrame>& frame, anm::Pose& pose);
    static mm::mtl::RTTI m_rtti;

    mm::Vec3 m_rotation;   // calcIK turns the bone's local rotation by these angles (x, y, z), scaled by the weight
    unsigned short m_bone; // setup's: the index of the bone it turns
};
}  // namespace fw

#endif

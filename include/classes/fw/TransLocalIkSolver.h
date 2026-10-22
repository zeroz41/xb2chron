#ifndef CLASSES_FW_TRANSLOCALIKSOLVER_H
#define CLASSES_FW_TRANSLOCALIKSOLVER_H

#include "mm/mtl/RTTI.h"
#include "mm/mtl/IntrusivePtr.h"
#include "mm/Vec3.h"
#include "classes/fw/IkFadeSolver.h"

namespace anm { class Pose; }
namespace fw { class ReferenceFrame; }
namespace fw { class UpdateInfo; }

namespace fw {
// table 0x7100B41CD0
class TransLocalIkSolver : public ::fw::IkFadeSolver {
public:
    TransLocalIkSolver() : m_trans(mm::Vec3::zero), m_bone(0xFFFF) {}
    virtual ~TransLocalIkSolver();  // slot 0
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 2
    virtual void calcIK(fw::UpdateInfo const&);  // slot 7
    // a solver for the bone named `boneName`, or null when the pose has none
    static TransLocalIkSolver* create(const char* boneName, mm::mtl::IntrusivePtr<fw::ReferenceFrame>& frame,
                                      anm::Pose& pose);
    bool setup(const char* boneName, mm::mtl::IntrusivePtr<fw::ReferenceFrame>& frame, anm::Pose& pose);
    static mm::mtl::RTTI m_rtti;

    mm::Vec3 m_trans;      // calcIK adds it, scaled by the weight, to the bone's local translation
    unsigned short m_bone; // setup's: the index of the bone it moves
};
}  // namespace fw

#endif

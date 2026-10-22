#ifndef CLASSES_FW_BLOWROTATEIKSOLVER_H
#define CLASSES_FW_BLOWROTATEIKSOLVER_H

#include "mm/mtl/RTTI.h"
#include "mm/mtl/IntrusivePtr.h"
#include "mm/Quat.h"
#include "classes/fw/IkFadeSolver.h"

namespace anm { class Pose; }
namespace fw { class ReferenceFrame; }
namespace fw { class UpdateInfo; }

namespace fw {
// table 0x7100B41918
class BlowRotateIkSolver : public ::fw::IkFadeSolver {
public:
    BlowRotateIkSolver() : m_rotation(mm::Quat::identity), m_bone(1) {}
    virtual ~BlowRotateIkSolver();  // slot 0
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 2
    virtual void calcIK(fw::UpdateInfo const&);  // slot 7
    // a solver that turns bone `bone` of the pose
    static BlowRotateIkSolver* create(mm::mtl::IntrusivePtr<fw::ReferenceFrame>& frame, anm::Pose& pose,
                                      unsigned int bone);
    static mm::mtl::RTTI m_rtti;

    mm::Quat m_rotation;    // calcIK turns the bone's model-space rotation by it
    unsigned short m_bone;  // create's: the index of the bone it turns
};
}  // namespace fw

#endif

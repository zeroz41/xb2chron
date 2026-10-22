#ifndef CLASSES_FW_IKSOLVER_H
#define CLASSES_FW_IKSOLVER_H

#include "mm/mtl/RTTI.h"
#include "mm/mtl/IntrusivePtr.h"
#include "classes/mm/mtl/ReferenceObject.h"
#include "classes/fw/ReferenceFrame.h"

namespace anm { class Pose; }
namespace fw { class UpdateInfo; }

namespace fw {
// table 0x7100B41B78; counted (the solvers' create adds the first reference)
class IkSolver : public mm::mtl::ReferenceObject {
public:
    virtual ~IkSolver();  // slot 0
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 2
    virtual void solve(fw::UpdateInfo const&) = 0;  // slot 3
    // holds the frame and the pose the solver works on
    void bind(mm::mtl::IntrusivePtr<fw::ReferenceFrame>& frame, anm::Pose& pose);
    void unbind();
    static mm::mtl::RTTI m_rtti;

    mm::mtl::IntrusivePtr<fw::ReferenceFrame> m_frame;  // bind holds it, unbind releases it
    anm::Pose* m_pose;                                  // bind's; calcIK reads and writes its bones
};
}  // namespace fw

#endif

#ifndef CLASSES_FW_SPINEIKSOLVER_H
#define CLASSES_FW_SPINEIKSOLVER_H

#include "mm/mtl/RTTI.h"
#include "mm/mtl/IntrusivePtr.h"
#include "mm/Vec3.h"
#include "classes/fw/IkFadeSolver.h"
#include "fw/ParamAdapter.h"

namespace anm { class Pose; }
namespace fw { class ReferenceFrame; }
namespace fw { class UpdateInfo; }

namespace fw {
// table 0x7100B41C80
class SpineIkSolver : public ::fw::IkFadeSolver {
public:
    virtual ~SpineIkSolver();  // slot 0
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 2
    virtual void onDisable();  // slot 6
    virtual void calcIK(fw::UpdateInfo const&);  // slot 7
    static SpineIkSolver* create(const ParamAdapter& param, const char* firstBone, const char* secondBone,
                                 mm::mtl::IntrusivePtr<fw::ReferenceFrame>& frame, anm::Pose& pose);
    void startTargetFade(float time);
    static mm::mtl::RTTI m_rtti;

    unsigned char pad_38[0x18];
    mm::Vec3 m_target;  // fw::LookIkSolver::setTarget sets it (the names of the fields are not the original's)
    unsigned char pad_60[0x10];
    mm::Vec3 m_frontMS;  // fw::LookIkSolver::setFrontMS sets it
};
}  // namespace fw

#endif

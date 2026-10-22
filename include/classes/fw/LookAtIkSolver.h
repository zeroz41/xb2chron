#ifndef CLASSES_FW_LOOKATIKSOLVER_H
#define CLASSES_FW_LOOKATIKSOLVER_H

#include "mm/mtl/RTTI.h"
#include "mm/mtl/IntrusivePtr.h"
#include "mm/Vec3.h"
#include "classes/fw/IkFadeSolver.h"
#include "fw/ParamAdapter.h"

namespace anm { class Pose; }
namespace fw { class ReferenceFrame; }
namespace fw { class UpdateInfo; }

namespace fw {
// table 0x7100B419F0
class LookAtIkSolver : public ::fw::IkFadeSolver {
public:
    virtual ~LookAtIkSolver();  // slot 0
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 2
    virtual void onDisable();  // slot 6
    virtual void calcIK(fw::UpdateInfo const&);  // slot 7
    static LookAtIkSolver* create(const ParamAdapter& param, const char* bone,
                                  mm::mtl::IntrusivePtr<fw::ReferenceFrame>& frame, anm::Pose& pose);
    void startTargetFade(float time);
    static mm::mtl::RTTI m_rtti;

    unsigned char pad_38[0x28];
    mm::Vec3 m_frontMS;  // fw::LookIkSolver::setFrontMS sets it (the names of the fields are not the original's)
    unsigned char pad_70[0x30];
    mm::Vec3 m_target;  // fw::LookIkSolver::setTarget sets it
    unsigned char pad_b0[0x1C];
    float m_targetUpRatio;    // fw::LookIkSolver::setTargetUpRatio sets it
    float m_targetDownRatio;  // fw::LookIkSolver::setTargetDownRatio sets it
};
}  // namespace fw

#endif

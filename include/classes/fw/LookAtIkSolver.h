#ifndef CLASSES_FW_LOOKATIKSOLVER_H
#define CLASSES_FW_LOOKATIKSOLVER_H

#include "mm/mtl/RTTI.h"
#include "mm/mtl/IntrusivePtr.h"
#include "mm/Vec3.h"
#include "mm/Quat.h"
#include "anm/LookAtIkSolver.h"
#include "classes/fw/IkFadeSolver.h"
#include "fw/ParamAdapter.h"

namespace anm { class Pose; }
namespace fw { class ReferenceFrame; }
namespace fw { class UpdateInfo; }

namespace fw {
// table 0x7100B419F0; turns one bone towards m_target within the angles its ParamAdapter holds
class LookAtIkSolver : public ::fw::IkFadeSolver {
public:
    // the parameter block its ParamAdapter holds, in degrees (1.0.0's BoxLimit::createReflection registers the
    // names)
    struct BoxLimit {
        float limitAngleUp;
        float limitAngleDown;
        float limitAngleLeft;
        float limitAngleRight;
    };

    // 1.0.0 has it out of line; 3.0.1's create inlines it
    LookAtIkSolver()
        : m_target(mm::Vec3::zero), m_localTarget(mm::Vec3::zero), m_bone(0xFFFF), m_targetUpRatio(1.0f),
          m_targetDownRatio(1.0f), m_targetFade(false), m_targetFadeRotation(mm::Quat::identity),
          m_targetFadeElapsed(0.0f), m_targetFadeTime(0.0f) {}
    virtual ~LookAtIkSolver();  // slot 0
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 2
    virtual void onDisable();  // slot 6
    virtual void calcIK(fw::UpdateInfo const&);  // slot 7
    // a solver turning bone `bone` of the pose within the limits `param` holds; none when the bone is not found
    static LookAtIkSolver* create(const ParamAdapter& param, const char* bone,
                                  mm::mtl::IntrusivePtr<fw::ReferenceFrame>& frame, anm::Pose& pose);
    // binds the solver, finds its bone and sets its limits: false when the bone is not found
    bool setupLimit(const ParamAdapter& param, const char* bone, mm::mtl::IntrusivePtr<fw::ReferenceFrame>& frame,
                    anm::Pose& pose);
    // the limits from the bone's current turn and the parameter block's angles
    void resetLimit();
    // the range's angles from the parameter block (1.0.0 has it out of line; 3.0.1's resetLimit inlines it)
    void resetLimitParam() {
        const BoxLimit* limit = m_param.get<BoxLimit>();
        m_range.limitAngleUp = limit->limitAngleUp * 0.0174532924f;
        m_range.limitAngleDown = limit->limitAngleDown * 0.0174532924f;
        m_range.limitAngleLeft = limit->limitAngleLeft * 0.0174532924f;
        m_range.limitAngleRight = limit->limitAngleRight * 0.0174532924f;
    }
    // calcIK eases the bone from its current turn into the solved one over `time`
    void startTargetFade(float time);
    // (inline: the name is not the original's; gf::GfFieldLookIk::updateIkSolver sets the target in place)
    void setTarget(const mm::Vec3& target) { m_target = target; }
    static mm::mtl::RTTI m_rtti;

    // the names of the fields below are not the original's
    anm::LookAtIKSolver::Limit m_limit;       // resetLimit's; fw::LookIkSolver::setFrontMS sets limitAxisMS
    anm::LookAtIKSolver::RangeLimit m_range;  // resetLimit's
    mm::Vec3 m_target;       // in world space: calcIK turns the bone towards it (fw::LookIkSolver::setTarget)
    mm::Vec3 m_localTarget;  // m_target in the frame's space, as calcIK last computed it; kept while fading out
    ParamAdapter m_param;    // setupLimit's: the BoxLimit block resetLimit reads
    unsigned short m_bone;   // setupLimit's: the bone's index
    float m_targetUpRatio;    // fw::LookIkSolver::setTargetUpRatio sets it: scales a target above
    float m_targetDownRatio;  // fw::LookIkSolver::setTargetDownRatio sets it: scales a target below
    bool m_targetFade;               // startTargetFade sets it; calcIK clears it when the fade ends
    mm::Quat m_targetFadeRotation;  // the bone's rotation when the fade started
    float m_targetFadeElapsed;
    float m_targetFadeTime;
};
}  // namespace fw

#endif

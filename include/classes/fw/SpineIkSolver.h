#ifndef CLASSES_FW_SPINEIKSOLVER_H
#define CLASSES_FW_SPINEIKSOLVER_H

#include "mm/mtl/RTTI.h"
#include "mm/mtl/IntrusivePtr.h"
#include "mm/Vec3.h"
#include "mm/Quat.h"
#include "anm/SpineIkSolver.h"
#include "classes/fw/IkFadeSolver.h"
#include "fw/ParamAdapter.h"

namespace anm { class Pose; }
namespace fw { class ReferenceFrame; }
namespace fw { class UpdateInfo; }

namespace fw {
// table 0x7100B41C80; turns two spine bones towards m_target within the angles its ParamAdapter holds
class SpineIkSolver : public ::fw::IkFadeSolver {
public:
    // the parameter block its ParamAdapter holds, angles in degrees (1.0.0's Param::createReflection registers the
    // names)
    struct Param {
        float angleThreasold0;
        float angleThreasold1;
        float response0;
        float response1;
        float limitAngle0;
        float limitAngle1;
    };

    // 1.0.0 has it out of line; 3.0.1's create inlines it
    SpineIkSolver()
        : m_target(mm::Vec3::zero), m_localTarget(mm::Vec3::zero), m_frontMS(mm::Vec3::unitZ), m_targetFade(false),
          m_targetFadeRotation0(mm::Quat::identity), m_targetFadeRotation1(mm::Quat::identity),
          m_targetFadeElapsed(0.0f), m_targetFadeTime(0.0f), pad_b8() {}
    virtual ~SpineIkSolver();  // slot 0
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 2
    virtual void onDisable();  // slot 6
    virtual void calcIK(fw::UpdateInfo const&);  // slot 7
    // a solver turning the two bones named within the limits `param` holds; none when neither bone is found
    static SpineIkSolver* create(const ParamAdapter& param, const char* firstBone, const char* secondBone,
                                 mm::mtl::IntrusivePtr<fw::ReferenceFrame>& frame, anm::Pose& pose);
    // binds the solver, finds its bones and sets its limits: false when neither bone is found
    bool setupLimit(const ParamAdapter& param, const char* firstBone, const char* secondBone,
                    mm::mtl::IntrusivePtr<fw::ReferenceFrame>& frame, anm::Pose& pose);
    // the limits from the parameter block (1.0.0's resetLimit; 3.0.1's setupLimit inlines it)
    void resetLimit() {
        const Param* limit = m_param.get<Param>();
        m_desc.angleThreasold0 = limit->angleThreasold0 * 0.0174532924f;
        m_desc.angleThreasold1 = limit->angleThreasold1 * 0.0174532924f;
        m_desc.response0 = limit->response0;
        m_desc.response1 = limit->response1;
        m_desc.limitAngle0 = limit->limitAngle0 * 0.0174532924f;
        m_desc.limitAngle1 = limit->limitAngle1 * 0.0174532924f;
    }
    // calcIK eases the bones from their current turns into the solved ones over `time`
    void startTargetFade(float time);
    static mm::mtl::RTTI m_rtti;

    // the names of the fields below are not the original's
    anm::SpineIKSolver::Description m_desc;  // setupLimit's
    mm::Vec3 m_target;       // in world space: calcIK turns the bones towards it (fw::LookIkSolver::setTarget)
    mm::Vec3 m_localTarget;  // m_target in the frame's space, as calcIK last computed it; kept while fading out
    mm::Vec3 m_frontMS;      // fw::LookIkSolver::setFrontMS sets it
    ParamAdapter m_param;    // setupLimit's: the Param block it reads
    bool m_targetFade;                // startTargetFade sets it; calcIK clears it when the fade ends
    mm::Quat m_targetFadeRotation0;  // the bones' rotations when the fade started
    mm::Quat m_targetFadeRotation1;
    float m_targetFadeElapsed;
    float m_targetFadeTime;
    float pad_b8[2];  // unknown: the constructor zeroes them
};
}  // namespace fw

#endif

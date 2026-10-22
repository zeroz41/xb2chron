#ifndef CLASSES_FW_LOOKIKSOLVER_H
#define CLASSES_FW_LOOKIKSOLVER_H

#include "mm/mtl/RTTI.h"
#include "mm/mtl/IntrusivePtr.h"
#include "mm/Vec3.h"
#include "classes/fw/IkSolver.h"
#include "classes/fw/LookAtIkSolver.h"
#include "classes/fw/SpineIkSolver.h"
#include "fw/ParamAdapter.h"

namespace anm { class Pose; }
namespace fw { class ReferenceFrame; }
namespace fw { class UpdateInfo; }

namespace fw {
// table 0x7100B41A40; a look: a look-at solver for the head and, while enabled, a spine solver, driven together
class LookIkSolver : public ::fw::IkSolver {
public:
    // create's: how fast setEnableSpine fades the spine solver (the field names are not the original's)
    struct Description {
        Description() : spineFadeOutTime(0.5f), spineFadeInTime(0.5f) {}

        float spineFadeOutTime;
        float spineFadeInTime;
    };

    LookIkSolver() : m_enableSpine(true) {}
    virtual ~LookIkSolver();  // slot 0
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 2
    virtual void solve(fw::UpdateInfo const&);  // slot 3
    virtual bool isEnable() const;  // slot 4
    static LookIkSolver* create(const Description& desc, mm::mtl::IntrusivePtr<fw::ReferenceFrame>& frame,
                                anm::Pose& pose);
    // the look-at solver on bone `bone`, replacing any earlier one
    LookAtIkSolver* createLookAtIK(const ParamAdapter& param, const char* bone);
    // the spine solver on bones `firstBone` and `secondBone`, replacing any earlier one
    SpineIkSolver* createSpineIK(const ParamAdapter& param, const char* firstBone, const char* secondBone);
    void fadeIn(float time);
    void fadeOut(float time);
    void setTarget(const mm::Vec3& target);
    void startTargetFade(float time);
    // fades the spine solver in (with the look-at solver) or out
    void setEnableSpine(bool enable);
    void setFrontMS(const mm::Vec3& front);
    void setTargetUpRatio(float ratio);
    void setTargetDownRatio(float ratio);
    // the fade its look-at solver (else its spine solver) is in, none with neither (inline: the name is not the
    // original's; TargetIKPlugin::update fades in or out only against a fade the other way)
    IkFadeSolver::FadeType getFadeType() const {
        if (m_lookAt.get() != nullptr) {
            return m_lookAt.get()->m_fadeType;
        }
        if (m_spine.get() != nullptr) {
            return m_spine.get()->m_fadeType;
        }
        return IkFadeSolver::FADE_NONE;
    }
    static mm::mtl::RTTI m_rtti;

    mm::mtl::IntrusivePtr<SpineIkSolver> m_spine;    // createSpineIK's
    mm::mtl::IntrusivePtr<LookAtIkSolver> m_lookAt;  // createLookAtIK's
    Description m_desc;
    bool m_enableSpine;  // setEnableSpine's; the spine solver follows the look only while set
};
}  // namespace fw

#endif

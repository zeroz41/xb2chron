#ifndef CLASSES_FW_IKFADESOLVER_H
#define CLASSES_FW_IKFADESOLVER_H

#include "mm/mtl/RTTI.h"
#include "classes/fw/IkSolver.h"
namespace fw { class UpdateInfo; }

namespace fw {
// table 0x7100B41BA8; its destructor adds nothing to IkSolver's, so clang emits IkSolver's in its place (slot 0)
class IkFadeSolver : public ::fw::IkSolver {
public:
    IkFadeSolver();
    virtual ~IkFadeSolver() {}  // slot 0
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 2
    virtual void solve(fw::UpdateInfo const&);  // slot 3
    virtual bool isEnable() const { return m_weight > 0.0f; }  // slot 4
    virtual void onEnable() {}  // slot 5
    virtual void onDisable() {}  // slot 6
    virtual void calcIK(fw::UpdateInfo const&) = 0;  // slot 7
    static mm::mtl::RTTI m_rtti;

    // how solve is moving m_weight; the names are not the original's
    enum FadeType {
        FADE_NONE = 0,
        FADE_IN = 1,   // fadeIn: towards 1
        FADE_OUT = 2,  // fadeOut: towards 0
    };

    // fadeIn's and fadeOut's: m_weight goes from `from` (t 0) to `to` (t 1) along a cubic Bezier curve
    // not static: its callers pass `this` (LookAtIkSolver::calcIK, SpineIkSolver::calcIK)
    float calcBezier(float t, float from, float to);
    void fadeIn(float time);
    void fadeOut(float time);

    float m_weight;         // solve fades it to 1 or to 0; isEnable while above 0; calcIK scales its effect by it
    FadeType m_fadeType;    // the names of the fields below are not the original's
    float m_fadeTime;       // fadeIn's/fadeOut's time: how long the fade takes
    float m_fadeElapsed;    // solve adds each frame's time step
    float m_fadeFromWeight; // m_weight when the fade started
};
}  // namespace fw

#endif

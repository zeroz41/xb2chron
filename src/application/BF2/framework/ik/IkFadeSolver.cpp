#include "classes/anm/Pose.h"
#include "classes/fw/IkSolver.h"
#include "classes/fw/IkFadeSolver.h"
#include "fw/UpdateInfo.h"

namespace fw {

IkSolver::IkSolver() : m_pose(nullptr) {}

void IkSolver::unbind() {
    m_frame = nullptr;
    if (m_pose != nullptr) {
        m_pose->release();
        m_pose = nullptr;
    }
}

IkSolver::~IkSolver() {
    unbind();
}

void IkSolver::bind(mm::mtl::IntrusivePtr<ReferenceFrame>& frame, anm::Pose& pose) {
    m_frame = frame;
    m_pose = &pose;
    pose.addRef();
}

IkFadeSolver::IkFadeSolver() : m_weight(0.0f), m_fadeType(FADE_NONE), m_fadeTime(0.0f), m_fadeElapsed(0.0f),
                               m_fadeFromWeight(0.0f) {}

void IkFadeSolver::solve(UpdateInfo const& info) {
    if (m_fadeType == FADE_IN) {
        m_fadeElapsed = info.m_deltaTime + m_fadeElapsed;
        float t = m_fadeElapsed / m_fadeTime;
        if (t >= 1.0f) {
            m_weight = 1.0f;
            m_fadeType = FADE_NONE;
        } else {
            m_weight = calcBezier(t, m_fadeFromWeight, 1.0f);
        }
    } else if (m_fadeType == FADE_OUT) {
        m_fadeElapsed = info.m_deltaTime + m_fadeElapsed;
        float t = m_fadeElapsed / m_fadeTime;
        if (t >= 1.0f) {
            m_weight = 0.0f;
            m_fadeType = FADE_NONE;
            onDisable();
        } else {
            m_weight = calcBezier(t, m_fadeFromWeight, 0.0f);
        }
    }
    if (isEnable()) {
        calcIK(info);
    }
}

float IkFadeSolver::calcBezier(float t, float from, float to) {
    float u = 1.0f - t;
    float tt = t * t;
    float uu = u * u;
    return (u * uu + 3.0f * uu * t) * from + (3.0f * u * tt + t * tt) * to;
}

void IkFadeSolver::fadeIn(float time) {
    float weight = m_weight;
    if (time > 0.0f) {
        m_fadeTime = time;
        m_fadeFromWeight = m_weight;
        m_fadeType = FADE_IN;
    } else {
        m_weight = 1.0f;
        m_fadeFromWeight = 0.0f;
        m_fadeTime = 0.0f;
        m_fadeType = FADE_NONE;
    }
    m_fadeElapsed = 0.0f;
    if (weight == 0.0f) {
        onEnable();
    }
}

void IkFadeSolver::fadeOut(float time) {
    if (time > 0.0f) {
        m_fadeFromWeight = m_weight;
        m_fadeTime = time;
        m_fadeType = FADE_OUT;
    } else {
        m_fadeTime = 0.0f;
        m_fadeFromWeight = 0.0f;
        m_weight = 0.0f;
        m_fadeType = FADE_NONE;
        onDisable();
    }
    m_fadeElapsed = 0.0f;
}

mm::mtl::RTTI IkSolver::m_rtti("IkSolver", nullptr, nullptr);
mm::mtl::RTTI IkFadeSolver::m_rtti("IkFadeSolver", &IkSolver::m_rtti, nullptr);

}  // namespace fw

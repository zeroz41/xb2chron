#include "classes/fw/LookAtIkSolver.h"
#include "classes/fw/LookIkSolver.h"
#include "classes/fw/SpineIkSolver.h"
#include "classes/fw/IkFadeSolver.h"
#include "classes/fw/IkSolver.h"
#include "classes/anm/Pose.h"
#include "fw/Allocator.h"
#include "classes/mm/mtl/IAllocator.h"

namespace fw {

LookIkSolver* LookIkSolver::create(const Description& desc, mm::mtl::IntrusivePtr<ReferenceFrame>& frame,
                                   anm::Pose& pose) {
#line 26
    LookIkSolver* solver = new (Allocator::getProcAllocator(), 16, __FILE__, __LINE__) LookIkSolver();
    solver->addRef();
    solver->bind(frame, pose);
    solver->m_desc = desc;
    return solver;
}

LookIkSolver::~LookIkSolver() {}

LookAtIkSolver* LookIkSolver::createLookAtIK(const ParamAdapter& param, const char* bone) {
    LookAtIkSolver* solver = LookAtIkSolver::create(param, bone, m_frame, *m_pose);
    m_lookAt = solver;
    if (solver != nullptr) {
        solver->release();
    }
    return m_lookAt.get();
}

SpineIkSolver* LookIkSolver::createSpineIK(const ParamAdapter& param, const char* firstBone,
                                           const char* secondBone) {
    SpineIkSolver* solver = SpineIkSolver::create(param, firstBone, secondBone, m_frame, *m_pose);
    m_spine = solver;
    if (solver != nullptr) {
        solver->release();
    }
    return m_spine.get();
}

void LookIkSolver::fadeIn(float time) {
    if (m_spine && m_enableSpine) {
        m_spine->fadeIn(time);
    }
    if (m_lookAt) {
        m_lookAt->fadeIn(time);
    }
}

void LookIkSolver::fadeOut(float time) {
    if (m_spine && m_enableSpine) {
        m_spine->fadeOut(time);
    }
    if (m_lookAt) {
        m_lookAt->fadeOut(time);
    }
}

void LookIkSolver::setTarget(const mm::Vec3& target) {
    if (m_spine && m_enableSpine) {
        m_spine->m_target = target;
    }
    if (m_lookAt) {
        m_lookAt->m_target = target;
    }
}

void LookIkSolver::startTargetFade(float time) {
    if (m_spine && m_enableSpine) {
        m_spine->startTargetFade(time);
    }
    if (m_lookAt) {
        m_lookAt->startTargetFade(time);
    }
}

void LookIkSolver::setEnableSpine(bool enable) {
    if (!m_spine) {
        return;
    }
    if (m_enableSpine == enable) {
        return;
    }
    if (enable) {
        if (!m_spine->isEnable() && (!m_lookAt || m_lookAt->isEnable())) {
            m_spine->fadeIn(m_desc.spineFadeInTime);
        }
    } else {
        // through the base here: the original's two isEnable calls stay apart (one merged call otherwise)
        IkFadeSolver* spine = m_spine.get();
        if (spine->isEnable() || m_spine->m_fadeType == IkFadeSolver::FADE_IN) {
            m_spine->fadeOut(m_desc.spineFadeOutTime);
        }
    }
    m_enableSpine = enable;
}

void LookIkSolver::setFrontMS(const mm::Vec3& front) {
    if (m_spine) {
        m_spine->m_frontMS = front;
    }
    if (m_lookAt) {
        m_lookAt->m_limit.limitAxisMS = front;
    }
}

void LookIkSolver::setTargetUpRatio(float ratio) {
    if (m_lookAt) {
        m_lookAt->m_targetUpRatio = ratio;
    }
}

void LookIkSolver::setTargetDownRatio(float ratio) {
    if (m_lookAt) {
        m_lookAt->m_targetDownRatio = ratio;
    }
}

void LookIkSolver::solve(UpdateInfo const& info) {
    if (m_spine) {
        m_spine->solve(info);
    }
    if (m_lookAt) {
        m_lookAt->solve(info);
    }
}

bool LookIkSolver::isEnable() const {
    if (m_lookAt && m_lookAt->isEnable()) {
        return true;
    }
    if (m_spine && m_spine->isEnable()) {
        return true;
    }
    return false;
}

mm::mtl::RTTI LookIkSolver::m_rtti("LookIkSolver", &IkSolver::m_rtti, nullptr);

}  // namespace fw

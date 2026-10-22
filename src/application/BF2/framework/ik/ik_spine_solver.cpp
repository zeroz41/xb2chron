#include "anm/SpineIkSolver.h"
#include "classes/fw/IkFadeSolver.h"
#include "classes/fw/SpineIkSolver.h"
#include "classes/fw/IkSolver.h"
#include "classes/anm/Pose.h"
#include "classes/anm/Skeleton.h"
#include "anm/QsTransform.h"
#include "fw/Allocator.h"
#include "classes/mm/mtl/IAllocator.h"

namespace fw {

SpineIkSolver* SpineIkSolver::create(const ParamAdapter& param, const char* firstBone, const char* secondBone,
                                     mm::mtl::IntrusivePtr<ReferenceFrame>& frame, anm::Pose& pose) {
#line 42
    SpineIkSolver* solver = new (Allocator::getProcAllocator(), 16, __FILE__, __LINE__) SpineIkSolver();
    solver->addRef();
    if (!solver->setupLimit(param, firstBone, secondBone, frame, pose)) {
        if (solver != nullptr) {
            solver->release();
        }
        return nullptr;
    }
    return solver;
}

bool SpineIkSolver::setupLimit(const ParamAdapter& param, const char* firstBone, const char* secondBone,
                               mm::mtl::IntrusivePtr<ReferenceFrame>& frame, anm::Pose& pose) {
    bind(frame, pose);
    const anm::Skeleton* skeleton = m_pose->m_pSkeleton;
    if (firstBone != nullptr) {
        m_desc.bones[0] = skeleton->getBoneIndex(firstBone);
    }
    if (secondBone != nullptr) {
        m_desc.bones[1] = skeleton->getBoneIndex(secondBone);
    }
    m_param = param;
    resetLimit();
    return m_desc.bones[0] != 0xFFFF || m_desc.bones[1] != 0xFFFF;
}

SpineIkSolver::~SpineIkSolver() {}

void SpineIkSolver::onDisable() {
    m_targetFade = false;
    m_targetFadeRotation0 = mm::Quat::identity;
    m_targetFadeRotation1 = mm::Quat::identity;
    m_targetFadeElapsed = 0.0f;
    m_targetFadeTime = 0.0f;
}

void SpineIkSolver::startTargetFade(float time) {
    if (time > 0.0f) {
        m_targetFade = true;
        if (m_desc.bones[0] != 0xFFFF) {
            m_targetFadeRotation0 = m_pose->getBoneModelSpace(m_desc.bones[0]).m_rotation;
        }
        if (m_desc.bones[1] != 0xFFFF) {
            m_targetFadeRotation1 = m_pose->getBoneModelSpace(m_desc.bones[1]).m_rotation;
        }
        m_targetFadeElapsed = 0.0f;
        m_targetFadeTime = time;
    }
}

mm::mtl::RTTI SpineIkSolver::m_rtti("SpineIkSolver", &IkFadeSolver::m_rtti, nullptr);

}  // namespace fw

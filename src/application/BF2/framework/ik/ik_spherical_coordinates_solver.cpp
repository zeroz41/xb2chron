#include "classes/fw/SphericalCoordinatesIkSolver.h"
#include "classes/fw/IkSolver.h"
#include "classes/fw/ReferenceFrame.h"
#include "classes/anm/Pose.h"
#include "classes/anm/Skeleton.h"
#include "anm/QsTransform.h"
#include "fw/Allocator.h"
#include "fw/UpdateInfo.h"
#include "classes/mm/mtl/IAllocator.h"
#include "mm/Quat.h"

namespace fw {

SphericalCoordinatesIkSolver* SphericalCoordinatesIkSolver::create(const ParamAdapter& param, const char* bone,
                                                                   mm::mtl::IntrusivePtr<ReferenceFrame>& frame,
                                                                   anm::Pose& pose) {
    SphericalCoordinatesIkSolver* solver =
#line 37
        new (Allocator::getProcAllocator(), 16, __FILE__, __LINE__) SphericalCoordinatesIkSolver();
    if (!solver->setupLimit(param, bone, frame, pose)) {
        if (solver != nullptr) {
            solver->release();
        }
        return nullptr;
    }
    solver->addRef();
    return solver;
}

bool SphericalCoordinatesIkSolver::setupLimit(const ParamAdapter& param, const char* bone,
                                              mm::mtl::IntrusivePtr<ReferenceFrame>& frame, anm::Pose& pose) {
    bind(frame, pose);
    if (bone == nullptr) {
        return false;
    }
    unsigned short index = m_pose->m_pSkeleton->getBoneIndex(bone);
    if (index == 0xFFFF) {
        return false;
    }
    m_bone = index;
    m_param = param;
    resetLimit();
    return true;
}

SphericalCoordinatesIkSolver::~SphericalCoordinatesIkSolver() {}

// solve (0x710018BA18) is not matched yet: written as
//     const mm::Vec3& position = m_frame->m_worldTransform.position;
//     mm::Quat rotation = m_frame->m_worldTransform.rotation;
//     mm::Vec3 target = mm::Quat::inverse(rotation).rotate(m_target - position);
//     anm::QsTransform transform = m_pose->getBoneModelSpace(m_bone);
//     anm::SphericalrdinatesIkSolver::solve(m_limit, target, isEnable() ? 1.0f : 0.0f, &transform);
//     m_pose->setBoneModelSpace(m_bone, transform, anm::Pose::PROPAGATE_TYPE(1));
// (after an isEnable() early return) its data flow is the original's; the original loads the position before
// m_target for the difference, and schedules the rotation differently

void SphericalCoordinatesIkSolver::resetLimit() {
    mm::Quat rotation = m_pose->getBoneModelSpace(m_bone).m_rotation;
    m_limit.fwdLS = mm::Quat::inverse(rotation).rotate(mm::Vec3::unitZ);
    m_limit.upAxisMS = mm::Vec3::unitY;
    m_limit.enableLimit = true;
    const AngleLimit* angle = m_param.get<AngleLimit>();
    m_limit.angleUp = angle->limitAngleUp * 0.0174532924f;
    m_limit.angleDown = angle->limitAngleDown * 0.0174532924f;
    m_limit.angleLeft = angle->limitAngleLeft * 0.0174532924f;
    m_limit.angleRight = angle->limitAngleRight * 0.0174532924f;
}

bool SphericalCoordinatesIkSolver::isEnable() const {
    return m_enable;
}

mm::mtl::RTTI SphericalCoordinatesIkSolver::m_rtti("SphericalCoordinatesIkSolver", &IkSolver::m_rtti, nullptr);

}  // namespace fw

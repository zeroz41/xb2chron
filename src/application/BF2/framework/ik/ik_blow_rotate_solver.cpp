#include "anm/Array.h"
#include "mm/Vec4.h"
#include "mm/Quat.h"
#include "anm/QsTransform.h"
#include "classes/anm/Skeleton.h"
#include "classes/anm/Pose.h"
#include "fw/Allocator.h"
#include "classes/fw/IkSolver.h"
#include "classes/fw/IkFadeSolver.h"
#include "classes/fw/BlowRotateIkSolver.h"
#include "classes/anm/Pose.h"
#include "classes/fw/BlowRotateIkSolver.h"
#include "classes/mm/mtl/IAllocator.h"

namespace fw {

BlowRotateIkSolver* BlowRotateIkSolver::create(mm::mtl::IntrusivePtr<ReferenceFrame>& frame, anm::Pose& pose,
                                               unsigned int bone) {
#line 30
    BlowRotateIkSolver* solver = new (Allocator::getProcAllocator(), 16, __FILE__, __LINE__) BlowRotateIkSolver();
    solver->addRef();
    solver->bind(frame, pose);
    solver->m_bone = bone;
    return solver;
}

BlowRotateIkSolver::~BlowRotateIkSolver() {}

void BlowRotateIkSolver::calcIK(UpdateInfo const&) {
    if (m_pose == nullptr) {
        return;
    }
    anm::QsTransform transform = m_pose->getBoneModelSpace(m_bone);
    transform.m_rotation = m_rotation * transform.m_rotation;
    m_pose->setBoneModelSpace(m_bone, transform, anm::Pose::PROPAGATE_TYPE(1));
}

}  // namespace fw

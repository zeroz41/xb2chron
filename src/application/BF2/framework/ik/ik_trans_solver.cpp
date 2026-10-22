#include "anm/Array.h"
#include "mm/Vec4.h"
#include "mm/Quat.h"
#include "anm/QsTransform.h"
#include "classes/anm/Skeleton.h"
#include "classes/anm/Pose.h"
#include "fw/Allocator.h"
#include "classes/fw/IkSolver.h"
#include "classes/fw/IkFadeSolver.h"
#include "classes/fw/TransLocalIkSolver.h"
#include "classes/anm/Pose.h"
#include "classes/anm/Skeleton.h"
#include "classes/fw/TransLocalIkSolver.h"
#include "classes/mm/mtl/IAllocator.h"

namespace fw {

TransLocalIkSolver* TransLocalIkSolver::create(const char* boneName, mm::mtl::IntrusivePtr<ReferenceFrame>& frame,
                                               anm::Pose& pose) {
#line 31
    TransLocalIkSolver* solver = new (Allocator::getProcAllocator(), 16, __FILE__, __LINE__) TransLocalIkSolver();
    solver->addRef();
    if (!solver->setup(boneName, frame, pose)) {
        if (solver != nullptr) {
            solver->release();
        }
        return nullptr;
    }
    return solver;
}

bool TransLocalIkSolver::setup(const char* boneName, mm::mtl::IntrusivePtr<ReferenceFrame>& frame,
                               anm::Pose& pose) {
    bind(frame, pose);
    if (boneName == nullptr) {
        return false;
    }
    unsigned short bone = pose.m_pSkeleton->getBoneIndex(boneName);
    if (bone == 0xFFFF) {
        return false;
    }
    m_bone = bone;
    return true;
}

TransLocalIkSolver::~TransLocalIkSolver() {}

void TransLocalIkSolver::calcIK(UpdateInfo const&) {
    if (m_pose == nullptr) {
        return;
    }
    anm::QsTransform transform = m_pose->getBoneLocalSpace(m_bone);
    mm::Vec3 trans = m_weight * m_trans;
    transform.m_translation.x = trans.x + transform.m_translation.x;
    transform.m_translation.y = trans.y + transform.m_translation.y;
    transform.m_translation.z = trans.z + transform.m_translation.z;
    transform.m_translation.w = transform.m_translation.w + 1.0f;
    m_pose->setBoneLocalSpace(m_bone, transform);
}

mm::mtl::RTTI TransLocalIkSolver::m_rtti("TransLocalIkSolver", &IkSolver::m_rtti, nullptr);

}  // namespace fw

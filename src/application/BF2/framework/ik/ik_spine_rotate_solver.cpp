#include "classes/fw/SpineRotateIKSolver.h"
#include "classes/anm/Pose.h"
#include "classes/anm/Skeleton.h"
#include "fw/Allocator.h"
#include "classes/fw/IkFadeSolver.h"
#include "classes/mm/mtl/IAllocator.h"

namespace fw {

SpineRotateIKSolver* SpineRotateIKSolver::create(const ParamAdapter& param, const char* firstBone,
                                                 const char* secondBone,
                                                 mm::mtl::IntrusivePtr<ReferenceFrame>& frame, anm::Pose& pose) {
#line 42
    SpineRotateIKSolver* solver = new (Allocator::getProcAllocator(), 16, __FILE__, __LINE__) SpineRotateIKSolver();
    solver->addRef();
    bool ok = solver->setupLimit(param, firstBone, secondBone, frame, pose);
    if (solver != nullptr && !ok) {
        solver->release();
        solver = nullptr;
    }
    return solver;
}

bool SpineRotateIKSolver::setupLimit(const ParamAdapter& param, const char* firstBone, const char* secondBone,
                                     mm::mtl::IntrusivePtr<ReferenceFrame>& frame, anm::Pose& pose) {
    bind(frame, pose);
    m_param = param;
    const anm::Skeleton* skeleton = m_pose->m_pSkeleton;
    if (firstBone != nullptr) {
        m_firstBone = skeleton->getBoneIndex(firstBone);
    }
    if (secondBone != nullptr) {
        m_secondBone = skeleton->getBoneIndex(secondBone);
    }
    return m_firstBone != 0xFFFF || m_secondBone != 0xFFFF;
}

SpineRotateIKSolver::~SpineRotateIKSolver() {}

// calcIK (0x710018C1F4) is not matched yet: its data flow is the original's, its register choice and order not

mm::mtl::RTTI SpineRotateIKSolver::m_rtti("SpineRotateIKSolver", &IkFadeSolver::m_rtti, nullptr);

}  // namespace fw

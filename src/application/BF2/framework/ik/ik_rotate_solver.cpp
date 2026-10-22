#include "classes/fw/RotateIkSolver.h"
#include "classes/fw/RotateLocalIkSolver.h"
#include "mm/Quat.h"
#include "anm/QsTransform.h"
#include "classes/anm/Pose.h"
#include "classes/anm/Skeleton.h"
#include "classes/fw/IkFadeSolver.h"
#include "fw/Allocator.h"
#include "classes/mm/mtl/IAllocator.h"

namespace fw {

RotateIkSolver* RotateIkSolver::create(const char* boneName, mm::mtl::IntrusivePtr<ReferenceFrame>& frame,
                                       anm::Pose& pose) {
#line 31
    RotateIkSolver* solver = new (Allocator::getProcAllocator(), 16, __FILE__, __LINE__) RotateIkSolver();
    solver->addRef();
    if (!solver->setup(boneName, frame, pose)) {
        if (solver != nullptr) {
            solver->release();
        }
        return nullptr;
    }
    return solver;
}

bool RotateIkSolver::setup(const char* boneName, mm::mtl::IntrusivePtr<ReferenceFrame>& frame, anm::Pose& pose) {
    bind(frame, pose);
    if (boneName == nullptr) {
        return false;
    }
    unsigned short bone = m_pose->m_pSkeleton->getBoneIndex(boneName);
    if (bone == 0xFFFF) {
        return false;
    }
    m_bone = bone;
    return true;
}

RotateIkSolver::~RotateIkSolver() {}

RotateLocalIkSolver* RotateLocalIkSolver::create(const char* boneName, mm::mtl::IntrusivePtr<ReferenceFrame>& frame,
                                                 anm::Pose& pose) {
#line 112
    RotateLocalIkSolver* solver = new (Allocator::getProcAllocator(), 16, __FILE__, __LINE__) RotateLocalIkSolver();
    solver->addRef();
    if (!solver->setup(boneName, frame, pose)) {
        if (solver != nullptr) {
            solver->release();
        }
        return nullptr;
    }
    return solver;
}

bool RotateLocalIkSolver::setup(const char* boneName, mm::mtl::IntrusivePtr<ReferenceFrame>& frame,
                                anm::Pose& pose) {
    bind(frame, pose);
    if (boneName == nullptr) {
        return false;
    }
    unsigned short bone = m_pose->m_pSkeleton->getBoneIndex(boneName);
    if (bone == 0xFFFF) {
        return false;
    }
    m_bone = bone;
    return true;
}

RotateLocalIkSolver::~RotateLocalIkSolver() {}

// calcIK (0x7100189048) and RotateLocalIkSolver::calcIK (0x710018955C) are not here yet: written as
//     anm::QsTransform transform = m_pose->getBoneModelSpace(m_bone);   // getBoneLocalSpace for the local one
//     mm::Vec3 half = m_weight * m_rotation * 0.5f;
//     float sx = sinf(half.x), cx = cosf(half.x), sy = sinf(half.y), cy = cosf(half.y), sz = sinf(half.z),
//           cz = cosf(half.z);
//     mm::Quat rotation(sx * cy * cz - cx * sy * sz, sx * cy * sz + cx * sy * cz, cx * cy * sz - sx * sy * cz,
//                       sx * sy * sz + cx * cy * cz);
//     transform.m_rotation = transform.m_rotation * rotation;
//     m_pose->setBoneModelSpace(m_bone, transform, anm::Pose::PROPAGATE_TYPE(1));  // setBoneLocalSpace
// (after an m_pose null check) their data flow is the original's; the original schedules the half angles' products
// and the sine/cosine products differently (20 words)

mm::mtl::RTTI RotateIkSolver::m_rtti("RotateIkSolver", &IkFadeSolver::m_rtti, nullptr);
mm::mtl::RTTI RotateLocalIkSolver::m_rtti("RotateLocalIkSolver", &IkFadeSolver::m_rtti, nullptr);

}  // namespace fw

#include "mm/mtl/FixedVector.h"
#include "classes/fw/IKGroundInterface.h"
#include "classes/fw/IKFootGroundInterface.h"
#include "classes/fw/FootPlacementIKSolver.h"
#include "classes/fw/PlacementGroundSolver.h"
#include "classes/fw/IkSolver.h"
#include "classes/fw/ReferenceFrame.h"
#include "classes/anm/Pose.h"
#include "anm/QsTransform.h"
#include "fw/Allocator.h"
#include "fw/ParamAdapter.h"
#include "fw/UpdateInfo.h"
#include "classes/mm/mtl/IAllocator.h"
#include "mm/Math.h"
#include "mm/Vec3.h"

namespace fw {

namespace {

// The drop towards the lowest foot, clamped to [-maxDown, 0]. Inferred helper (the name is not the original's): the
// original's clamp is inlined into a function of its own before the caller (its selects are formed before the
// caller's join with the target = 0 branch), which mm::clamp written directly in the caller does not reproduce.
inline float clampDown(float down, float maxDown) {
    return mm::clamp(down, -maxDown, 0.0f);
}

}  // namespace

PlacementGroundSolver* PlacementGroundSolver::create(const Description& desc,
                                                     mm::mtl::IntrusivePtr<ReferenceFrame>& frame, anm::Pose& pose,
                                                     IKGroundInterface* ground) {
#line 35
    PlacementGroundSolver* solver = new (Allocator::getProcAllocator(), 16, __FILE__, __LINE__) PlacementGroundSolver();
    solver->addRef();
    solver->createImpl(desc, frame, pose, ground);
    return solver;
}

bool PlacementGroundSolver::createImpl(const Description& desc, mm::mtl::IntrusivePtr<ReferenceFrame>& frame,
                                       anm::Pose& pose, IKGroundInterface* ground) {
    bind(frame, pose);
    m_desc = desc;
    m_ground = ground;
    m_solvers.resize(desc.footCount);
    return true;
}

PlacementGroundSolver::~PlacementGroundSolver() {}

FootPlacementIKSolver* PlacementGroundSolver::createFootPlacementIK(IKFootIndex index, ParamAdapter& param,
                                                                    const char* bone0, const char* bone1,
                                                                    const char* bone2, bool flag) {
    if (index >= m_solvers.size()) {
        return nullptr;
    }
    FootPlacementIKSolver::Description desc;
    desc.boneNames[0] = bone0;
    desc.boneNames[1] = bone1;
    desc.boneNames[2] = bone2;
    desc.pad_25 = flag;
    desc.param = param;
    IKFootGroundInterface* ground = m_ground != nullptr ? m_ground->getFootGround(index) : nullptr;
    FootPlacementIKSolver* solver = FootPlacementIKSolver::create(desc, m_frame, *m_pose, ground);
    m_solvers[index] = solver;
    if (solver != nullptr) {
        solver->release();
    }
    return solver;
}

void PlacementGroundSolver::setEnablePlacement(bool enable) {
    m_enablePlacement = enable;
    if (!m_solvers.empty()) {
        unsigned long i = 0;
        unsigned int next = 1;
        do {
            if (*m_solvers.at(i)) {
                if (enable) {
                    m_solvers[i]->m_flags |= FootPlacementIKSolver::FLAG_PLACEMENT;
                } else {
                    m_solvers[i]->m_flags &= ~FootPlacementIKSolver::FLAG_PLACEMENT;
                }
            }
        } while ((i = next++) < m_solvers.size());
    }
}

void PlacementGroundSolver::solve(UpdateInfo const& info) {
    if (m_ground == nullptr) {
        return;
    }
    bool adjust = m_enableDown || m_offset < 0.0f;
    if (!m_enablePlacement && !adjust) {
        return;
    }
    ReferenceFrame* frame = m_frame.operator->();
    float lowest = frame->m_worldTransform.position.y;
    for (unsigned int i = 0; i < m_solvers.size(); ++i) {
        if (*m_solvers.at(i)) {
            IKFootGroundInterface* foot = m_ground->getFootGround(IKFootIndex(i));
            if (foot != nullptr) {
                const mm::Vec3* hitPos = foot->getHitPos();
                if (hitPos != nullptr) {
                    lowest = lowest < hitPos->y ? lowest : hitPos->y;
                }
            }
        }
    }
    if (adjust) {
        float target;
        if (m_enableDown) {
            float down = lowest - frame->m_worldTransform.position.y;
            target = clampDown(down, m_desc.maxDown);
        } else {
            target = 0.0f;
        }
        // towards the target by at most 0.05 down and 0.03 up per frame
        float offset;
        if (target > m_offset) {
            offset = target < m_offset + 0.05f ? target : m_offset + 0.05f;
        } else {
            offset = target > m_offset + -0.03f ? target : m_offset + -0.03f;
        }
        if (offset < 0.0f) {
            anm::QsTransform transform = m_pose->getBoneModelSpace(0);
            transform.m_translation.y = offset + transform.m_translation.y;
            m_pose->setBoneModelSpace(0, transform, anm::Pose::PROPAGATE_TYPE(1));
        }
        m_offset = offset;
    }
    if (!m_solvers.empty()) {
        unsigned long i = 0;
        unsigned int next = 1;
        do {
            if (*m_solvers.at(i)) {
                m_solvers[i]->solve(info);
            }
        } while ((i = next++) < m_solvers.size());
    }
}

void PlacementGroundSolver::overwriteRaycastDown(float length) {
    if (!m_solvers.empty()) {
        unsigned long i = 0;
        unsigned int next = 1;
        do {
            if (*m_solvers.at(i)) {
                FootPlacementIKSolver* solver = m_solvers[i].operator->();
                solver->m_flags |= FootPlacementIKSolver::FLAG_RAYCAST_DOWN;
                solver->m_raycastDown = length;
            }
        } while ((i = next++) < m_solvers.size());
    }
}

void PlacementGroundSolver::resetRaycastDown() {
    if (!m_solvers.empty()) {
        unsigned long i = 0;
        unsigned int next = 1;
        do {
            if (*m_solvers.at(i)) {
                m_solvers[i]->m_flags &= ~FootPlacementIKSolver::FLAG_RAYCAST_DOWN;
            }
        } while ((i = next++) < m_solvers.size());
    }
}

void PlacementGroundSolver::setGroundAngle(const mm::Vec3& angle) {
    if (!m_solvers.empty()) {
        unsigned long i = 0;
        unsigned int next = 1;
        do {
            if (*m_solvers.at(i)) {
                m_solvers[i]->setGroundAngle(angle);
            }
        } while ((i = next++) < m_solvers.size());
    }
}

mm::mtl::RTTI PlacementGroundSolver::m_rtti("PlacementGroundSolver", &IkSolver::m_rtti, nullptr);

}  // namespace fw

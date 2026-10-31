#include "mm/mtl/FixedVector.h"
#include "classes/fw/IKGroundInterface.h"
#include "classes/fw/IKFootGroundInterface.h"
#include "classes/fw/FootPlacementIKSolver.h"
#include "classes/fw/SlopeGroundSolver.h"
#include "classes/fw/IkSolver.h"
#include "classes/fw/ReferenceFrame.h"
#include "classes/anm/Pose.h"
#include "anm/QsTransform.h"
#include "fw/Allocator.h"
#include "fw/ParamAdapter.h"
#include "fw/UpdateInfo.h"
#include "classes/mm/mtl/IAllocator.h"
#include "mm/Quat.h"
#include "mm/Vec3.h"

namespace fw {

SlopeGroundSolver* SlopeGroundSolver::create(const Description& desc, mm::mtl::IntrusivePtr<ReferenceFrame>& frame,
                                             anm::Pose& pose, IKGroundInterface* ground) {
#line 34
    SlopeGroundSolver* solver = new (Allocator::getProcAllocator(), 16, __FILE__, __LINE__) SlopeGroundSolver();
    solver->addRef();
    solver->createImpl(desc, frame, pose, ground);
    return solver;
}

bool SlopeGroundSolver::createImpl(const Description& desc, mm::mtl::IntrusivePtr<ReferenceFrame>& frame,
                                   anm::Pose& pose, IKGroundInterface* ground) {
    m_desc = desc;
    bind(frame, pose);
    m_ground = ground;
    m_solvers.resize(desc.footCount);
    return true;
}

SlopeGroundSolver::~SlopeGroundSolver() {}

void SlopeGroundSolver::solveFoot(UpdateInfo const& info) {
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

void SlopeGroundSolver::solve(UpdateInfo const& info) {
    if (m_ground == nullptr) {
        return;
    }
    slopeBody(info);
    if (!m_solvers.empty()) {
        solveFoot(info);
    }
}

FootPlacementIKSolver* SlopeGroundSolver::createFootPlacementIK(IKFootIndex index, ParamAdapter& param,
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

void SlopeGroundSolver::setEnablePlacement(bool enable) {
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

mm::mtl::RTTI SlopeGroundSolver::m_rtti("SlopeGroundSolver", &IkSolver::m_rtti, nullptr);

}  // namespace fw

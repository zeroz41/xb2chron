#include "mm/mtl/FixedVector.h"
#include "classes/fw/TwoCharaGroundSolver.h"
#include "fw/TransformUtil.h"
#include "mm/mtl/FixedVector.h"
#include "classes/fw/IKGroundInterface.h"
#include "classes/fw/IKFootGroundInterface.h"
#include "classes/fw/FootPlacementIKSolver.h"
#include "classes/fw/IkSolver.h"
#include "classes/fw/ReferenceFrame.h"
#include "classes/anm/Pose.h"
#include "classes/anm/Skeleton.h"
#include "anm/QsTransform.h"
#include "fw/Allocator.h"
#include "fw/ParamAdapter.h"
#include "fw/Transform.h"
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

TwoCharaGroundSolver* TwoCharaGroundSolver::create(const Description& desc,
                                                   mm::mtl::IntrusivePtr<ReferenceFrame>& frame, anm::Pose& pose,
                                                   IKGroundInterface* ground) {
#line 34
    TwoCharaGroundSolver* solver = new (Allocator::getProcAllocator(), 16, __FILE__, __LINE__) TwoCharaGroundSolver();
    solver->addRef();
    if (!solver->createImpl(desc, frame, pose, ground)) {
        if (solver != nullptr) {
            solver->release();
        }
        solver = nullptr;
    }
    return solver;
}

bool TwoCharaGroundSolver::createImpl(const Description& desc, mm::mtl::IntrusivePtr<ReferenceFrame>& frame,
                                      anm::Pose& pose, IKGroundInterface* ground) {
    bind(frame, pose);
    m_desc = desc;
    m_ground = ground;
    m_mainSolvers.resize(desc.footCount);
    m_subSolvers.resize(desc.footCount);
    const anm::Skeleton* skeleton = pose.m_pSkeleton;
    if (skeleton == nullptr) {
        return false;
    }
    m_mainRoot = desc.mainRootBone != nullptr ? skeleton->getBoneIndex(desc.mainRootBone) : 0xFFFF;
    if (m_mainRoot == 0xFFFF) {
        return false;
    }
    m_subRoot = desc.subRootBone != nullptr ? skeleton->getBoneIndex(desc.subRootBone) : 0xFFFF;
    return m_subRoot != 0xFFFF;
}

TwoCharaGroundSolver::~TwoCharaGroundSolver() {}

FootPlacementIKSolver* TwoCharaGroundSolver::createFootPlacementIKMain(IKFootIndex index, ParamAdapter param,
                                                                       const char* bone0, const char* bone1,
                                                                       const char* bone2, bool flag) {
    if (index >= m_mainSolvers.size()) {
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
    m_mainSolvers[index] = solver;
    if (solver != nullptr) {
        solver->release();
    }
    return solver;
}

FootPlacementIKSolver* TwoCharaGroundSolver::createFootPlacementIKSub(IKFootIndex index, ParamAdapter param,
                                                                      const char* bone0, const char* bone1,
                                                                      const char* bone2, bool flag) {
    if (index >= m_subSolvers.size()) {
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
    m_subSolvers[index] = solver;
    if (solver != nullptr) {
        solver->release();
    }
    return solver;
}

void TwoCharaGroundSolver::setEnablePlacement(bool enable) {
    m_enablePlacement = enable;
    if (!m_mainSolvers.empty()) {
        unsigned long i = 0;
        unsigned int next = 1;
        do {
            if (*m_mainSolvers.at(i)) {
                FootPlacementIKSolver* solver = m_mainSolvers[i].operator->();
                bool on = enable && m_enableMain;
                if (on) {
                    solver->m_flags |= FootPlacementIKSolver::FLAG_PLACEMENT;
                } else {
                    solver->m_flags &= ~FootPlacementIKSolver::FLAG_PLACEMENT;
                }
            }
        } while ((i = next++) < m_mainSolvers.size());
    }
    if (!m_subSolvers.empty()) {
        unsigned long i = 0;
        unsigned int next = 1;
        do {
            if (*m_subSolvers.at(i)) {
                FootPlacementIKSolver* solver = m_subSolvers[i].operator->();
                bool on = enable && m_enableSub;
                if (on) {
                    solver->m_flags |= FootPlacementIKSolver::FLAG_PLACEMENT;
                } else {
                    solver->m_flags &= ~FootPlacementIKSolver::FLAG_PLACEMENT;
                }
            }
        } while ((i = next++) < m_subSolvers.size());
    }
}

void TwoCharaGroundSolver::solve(UpdateInfo const& info) {
    if (m_ground == nullptr) {
        return;
    }
    bool adjust = m_enableDown || m_mainOffset < 0.0f || m_subOffset != 0.0f;
    if (!m_enablePlacement && !adjust) {
        return;
    }
    doPlacementRoot();
    doPlacementFoot(info);
}

void TwoCharaGroundSolver::doPlacementRoot() {
    if (m_syncDown == 0) {
        if ((m_enableDown && m_enableMain) || m_mainOffset < 0.0f) {
            const anm::QsTransform& bone = m_pose->getBoneModelSpace(m_mainRoot);
            Transform root;
            TransformUtil::mul(m_frame->m_worldTransform, bone, 1.0f, &root);
            float lowest = root.position.y;
            for (unsigned int i = 0; i < m_mainSolvers.size(); ++i) {
                if (*m_mainSolvers.at(i)) {
                    IKFootGroundInterface* foot = m_ground->getFootGround(IKFootIndex(i));
                    if (foot != nullptr) {
                        const mm::Vec3* hitPos = foot->getHitPos();
                        if (hitPos != nullptr) {
                            lowest = lowest < hitPos->y ? lowest : hitPos->y;
                        }
                    }
                }
            }
            float target;
            if (m_enableDown) {
                float down = lowest - root.position.y;
                target = clampDown(down, m_desc.maxDown);
            } else {
                target = 0.0f;
            }
            float offset;
            if (target > m_mainOffset) {
                offset = target < m_mainOffset + 0.05f ? target : m_mainOffset + 0.05f;
            } else {
                offset = target > m_mainOffset + -0.03f ? target : m_mainOffset + -0.03f;
            }
            if (offset < 0.0f) {
                anm::QsTransform transform = m_pose->getBoneModelSpace(m_mainRoot);
                transform.m_translation.y = offset + transform.m_translation.y;
                m_pose->setBoneModelSpace(m_mainRoot, transform, anm::Pose::PROPAGATE_TYPE(1));
            }
            m_mainOffset = offset;
        }
        if ((m_enableDown && m_enableSub) || m_subOffset != 0.0f) {
            float lowest;
            const mm::Vec3* hitPos = m_ground->getHitPosSub();
            if (hitPos != nullptr) {
                lowest = hitPos->y;
            } else {
                const anm::QsTransform& bone = m_pose->getBoneModelSpace(m_mainRoot);
                Transform root;
                TransformUtil::mul(m_frame->m_worldTransform, bone, 1.0f, &root);
                lowest = root.position.y;
            }
            for (unsigned int i = 0; i < m_subSolvers.size(); ++i) {
                if (*m_subSolvers.at(i)) {
                    IKFootGroundInterface* foot = m_ground->getFootGround(IKFootIndex(i));
                    if (foot != nullptr) {
                        const mm::Vec3* footHitPos = foot->getHitPos();
                        if (footHitPos != nullptr) {
                            lowest = lowest < footHitPos->y ? lowest : footHitPos->y;
                        }
                    }
                }
            }
            // the main's root's height (its transform's scope ends here: the original reuses its stack for the
            // sub's root's transform below)
            float rootHeight;
            {
                const anm::QsTransform& bone = m_pose->getBoneModelSpace(m_mainRoot);
                Transform root;
                TransformUtil::mul(m_frame->m_worldTransform, bone, 1.0f, &root);
                rootHeight = root.position.y;
            }
            float target = m_enableDown ? lowest - rootHeight : 0.0f;
            // towards the target by at most 1 either way per frame
            float offset;
            if (target > m_subOffset) {
                offset = target < m_subOffset + 1.0f ? target : m_subOffset + 1.0f;
            } else {
                offset = target > m_subOffset + -1.0f ? target : m_subOffset + -1.0f;
            }
            if (offset != 0.0f) {
                anm::QsTransform transform = m_pose->getBoneModelSpace(m_subRoot);
                transform.m_translation.y = offset + transform.m_translation.y;
                m_pose->setBoneModelSpace(m_subRoot, transform, anm::Pose::PROPAGATE_TYPE(1));
            }
            m_subOffset = offset;
        }
    } else if (m_syncDown == 1) {
        if (!m_enableDown && !(m_mainOffset < 0.0f)) {
            return;
        }
        ReferenceFrame* frame = m_frame.operator->();
        float lowest = frame->m_worldTransform.position.y;
        for (unsigned int i = 0; i < m_subSolvers.size(); ++i) {
            if (*m_subSolvers.at(i)) {
                IKFootGroundInterface* foot = m_ground->getFootGround(IKFootIndex(i));
                if (foot != nullptr) {
                    const mm::Vec3* hitPos = foot->getHitPos();
                    if (hitPos != nullptr) {
                        lowest = lowest < hitPos->y ? lowest : hitPos->y;
                    }
                }
            }
        }
        float target;
        if (m_enableDown) {
            float down = lowest - frame->m_worldTransform.position.y;
            target = clampDown(down, m_desc.maxDown);
        } else {
            target = 0.0f;
        }
        float offset;
        if (target > m_mainOffset) {
            offset = target < m_mainOffset + 0.05f ? target : m_mainOffset + 0.05f;
        } else {
            offset = target > m_mainOffset + -0.03f ? target : m_mainOffset + -0.03f;
        }
        if (offset < 0.0f) {
            anm::QsTransform transform = m_pose->getBoneModelSpace(m_mainRoot);
            transform.m_translation.y = offset + transform.m_translation.y;
            m_pose->setBoneModelSpace(m_mainRoot, transform, anm::Pose::PROPAGATE_TYPE(1));
            transform = m_pose->getBoneModelSpace(m_subRoot);
            transform.m_translation.y = offset + transform.m_translation.y;
            m_pose->setBoneModelSpace(m_subRoot, transform, anm::Pose::PROPAGATE_TYPE(1));
        }
        m_mainOffset = offset;
        m_subOffset = offset;
    }
}

void TwoCharaGroundSolver::doPlacementFoot(const UpdateInfo& info) {
    if (!m_mainSolvers.empty()) {
        unsigned long i = 0;
        unsigned int next = 1;
        do {
            if (*m_mainSolvers.at(i)) {
                if (m_syncDown == 1) {
                    m_mainSolvers[i]->m_flags &= ~FootPlacementIKSolver::FLAG_PLACEMENT;
                }
                m_mainSolvers[i]->solve(info);
            }
        } while ((i = next++) < m_mainSolvers.size());
    }
    if (!m_subSolvers.empty()) {
        unsigned long i = 0;
        unsigned int next = 1;
        do {
            if (*m_subSolvers.at(i)) {
                m_subSolvers[i]->solve(info);
            }
        } while ((i = next++) < m_subSolvers.size());
    }
}

mm::mtl::RTTI TwoCharaGroundSolver::m_rtti("TwoCharaGroundSolver", &IkSolver::m_rtti, nullptr);

}  // namespace fw

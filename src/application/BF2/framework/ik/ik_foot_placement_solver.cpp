#include "classes/fw/FootPlacementIKSolver.h"
#include "classes/fw/Raycaster.h"
#include "classes/fw/IKFootGroundInterface.h"
#include "classes/fw/PlaneRayCaster.h"
#include "classes/fw/IkSolver.h"
#include "classes/fw/ReferenceFrame.h"
#include "classes/anm/FootPlacementIKSolver.h"
#include "classes/anm/RaycastInterface.h"
#include "classes/anm/Pose.h"
#include "classes/anm/Skeleton.h"
#include "anm/QsTransform.h"
#include "fw/Allocator.h"
#include "fw/ColiCheck.h"
#include "fw/ParamAdapter.h"
#include "fw/UpdateInfo.h"
#include "classes/mm/mtl/IAllocator.h"
#include "mm/Quat.h"
#include "mm/Vec3.h"
#include "mm/Vec4.h"
#include "math.h"

namespace fw {

FootPlacementIKSolver* FootPlacementIKSolver::create(const Description& desc,
                                                     mm::mtl::IntrusivePtr<ReferenceFrame>& frame, anm::Pose& pose,
                                                     IKFootGroundInterface* ground) {
#line 66
    FootPlacementIKSolver* solver = new (Allocator::getProcAllocator(), 16, __FILE__, __LINE__) FootPlacementIKSolver();
    solver->addRef();
    if (!solver->createImpl(desc, frame, pose, ground)) {
        if (solver != nullptr) {
            solver->release();
        }
        return nullptr;
    }
    return solver;
}

bool FootPlacementIKSolver::createImpl(const Description& desc, mm::mtl::IntrusivePtr<ReferenceFrame>& frame,
                                       anm::Pose& pose, IKFootGroundInterface* ground) {
    m_desc = desc;
    bind(frame, pose);
    m_ground = ground;
    anm::FootPlacementIKSolver::Description ikDesc;
    const anm::Skeleton* skeleton = m_pose->m_pSkeleton;
    ikDesc.skeleton = skeleton;
    ikDesc.boneIndex0 = desc.boneNames[0] != nullptr ? skeleton->getBoneIndex(desc.boneNames[0]) : 0xFFFF;
    if (ikDesc.boneIndex0 == 0xFFFF) {
        return false;
    }
    ikDesc.boneIndex1 = desc.boneNames[1] != nullptr ? skeleton->getBoneIndex(desc.boneNames[1]) : 0xFFFF;
    if (ikDesc.boneIndex1 == 0xFFFF) {
        return false;
    }
    ikDesc.boneIndex2 = desc.boneNames[2] != nullptr ? skeleton->getBoneIndex(desc.boneNames[2]) : 0xFFFF;
    if (ikDesc.boneIndex2 == 0xFFFF) {
        return false;
    }
    m_footBone = ikDesc.boneIndex2;
    m_footTransform = m_pose->getBoneModelSpace(ikDesc.boneIndex2);
    ikDesc.up = mm::Vec3::unitY;
    ikDesc.up2 = mm::Vec3::unitY;
    mm::Quat rotation = m_pose->getBoneModelSpace(ikDesc.boneIndex1).m_rotation;
    mm::Vec3 forward = mm::Quat::inverse(rotation).rotate(mm::Vec3::unitX);
    float length = forward.length();
    if (length <= 1e-6f) {
        forward = mm::Vec3::zero;
    } else {
        float scale = 1.0f / length;
        forward = mm::Vec3(scale * forward.x, scale * forward.y, scale * forward.z);
    }
    ikDesc.forward = forward;
    if (desc.pad_25) {
        ikDesc.forward.setNeg(ikDesc.forward);
    }
    ikDesc.cosAngle0 = cosf(desc.pad_18[0] * 0.0174532924f);
    ikDesc.cosAngle1 = cosf(desc.pad_18[1] * 0.0174532924f);
    const anm::QsTransform& foot = m_pose->getBoneModelSpace(ikDesc.boneIndex2);
    ikDesc.groundHeight = foot.m_translation.y - 0.05f;
    if (const Param* param = m_desc.param.get<Param>()) {
        ikDesc.pad_50 = param->pad_0;
        ikDesc.height0 = ikDesc.groundHeight + param->pad_8;
        ikDesc.height1 = ikDesc.groundHeight + param->pad_4;
    }
    mm::Vec3 toe(foot.m_translation.x, foot.m_translation.y, foot.m_translation.z + desc.pad_18[2]);
    mm::Quat inverse = mm::Quat::inverse(foot.m_rotation);
    ikDesc.toeOffset =
        inverse.rotate(toe - mm::Vec3(foot.m_translation.x, foot.m_translation.y, foot.m_translation.z));
    ikDesc.pad_70 = desc.pad_24;
    m_footIk = anm::FootPlacementIKSolver::create(ikDesc, *Allocator::getProcAllocator());
    return true;
}

FootPlacementIKSolver::~FootPlacementIKSolver() {
    if (m_footIk != nullptr) {
        m_footIk->release();
        m_footIk = nullptr;
    }
}

void FootPlacementIKSolver::solve(UpdateInfo const&) {
    if (m_ground != nullptr) {
        PlaneRayCaster& raycaster = m_ground->m_rayCaster;
        raycaster.bind(*m_ground);
        solveImpl(raycaster);
    } else {
        // Proposed name, not the original's: the symbols leave it unnamed (lbl_7100B41998)
        static Raycaster s_raycaster;
        solveImpl(s_raycaster);
    }
}

void FootPlacementIKSolver::solveImpl(anm::RaycastInterface& raycaster) {
    anm::FootPlacementIKSolver::Input input;
    input.foot = m_pose->getBoneModelSpace(m_footIk->m_footBone);
    const Transform& world = m_frame->m_worldTransform;
    input.frame.m_translation = mm::Vec4(world.position.x, world.position.y, world.position.z, 1.0f);
    input.frame.m_rotation = world.rotation;
    input.frame.m_scale = mm::Vec4(mm::Vec3::unit.x, mm::Vec3::unit.y, mm::Vec3::unit.z, 1.0f);
    mm::Quat rotation = m_groundAngle * m_groundRotation;
    input.up = rotation.rotate(mm::Vec3::unitY);
    input.enable = (m_flags & FLAG_PLACEMENT) != 0;
    input.raycaster = &raycaster;
    float up;
    if (m_flags & FLAG_RAYCAST_UP) {
        up = m_raycastUp;
    } else {
        anm::FootPlacementIKSolver* ik = m_footIk;
        const anm::QsTransform& foot = m_pose->getBoneModelSpace(ik->m_footBone);
        up = ik->m_raycastUp - foot.m_translation.y;
        up = up > 0.0f ? up : 0.0f;
    }
    input.raycastUp = up;
    float down;
    if (m_flags & FLAG_RAYCAST_DOWN) {
        down = m_raycastDown;
    } else {
        anm::FootPlacementIKSolver* ik = m_footIk;
        const anm::QsTransform& foot = m_pose->getBoneModelSpace(ik->m_footBone);
        down = foot.m_translation.y - ik->m_raycastDown;
        down = (down > 0.0f ? down : 0.0f) + 0.1f;
    }
    input.raycastDown = down;
    anm::FootPlacementIKSolver::Output output;
    m_footIk->doFootPlacement(input, &output, m_pose);
    if (output.hit) {
        m_flags |= FLAG_HIT;
    } else {
        m_flags &= ~FLAG_HIT;
    }
    m_footPos = output.position;
    if (m_footIk->m_weight >= 1.0f) {
        m_flags |= FLAG_WEIGHT_FULL;
    } else {
        m_flags &= ~FLAG_WEIGHT_FULL;
    }
}

void FootPlacementIKSolver::setGroundAngle(const mm::Vec3& angle) {
    mm::Vec3 half = angle * 0.5f;
    float sx = sinf(half.x);
    float cx = cosf(half.x);
    float sy = sinf(half.y);
    float cy = cosf(half.y);
    float sz = sinf(half.z);
    float cz = cosf(half.z);
    m_groundAngle.x = sx * cy * cz - cx * sy * sz;
    m_groundAngle.y = cx * sy * cz + sx * cy * sz;
    m_groundAngle.z = cx * cy * sz - sx * sy * cz;
    m_groundAngle.w = sx * sy * sz + cx * cy * cz;
}

bool Raycaster::castRay(const mm::Vec3& from, const mm::Vec3& to, mm::Vec3* pHitPos, mm::Vec3* pNormal) {
    ColiCheckConfig config;
    config.m_option = false;
    config.m_flags = 9;
    config.m_mask = ~5u;
    TColiCheckResult<256> result;
    ColiCheck::testLine(result, from, to, config);
    if (result.getHitNum() != 0) {
        *pHitPos = result.getPosition(0);
        *pNormal = result.getNormal(0);
    }
    return result.m_hit;
}

mm::mtl::RTTI FootPlacementIKSolver::m_rtti("FootPlacementIKSolver", &IkSolver::m_rtti, nullptr);

}  // namespace fw

#include "classes/fw/IkFadeSolver.h"
#include "mm/Plane.h"
#include "anm/LookAtIkSolver.h"
#include "classes/anm/RaycastInterface.h"
#include "classes/fw/IKFootGroundInterface.h"
#include "classes/fw/PlaneRayCaster.h"
#include "classes/fw/LookAtIkSolver.h"
#include "classes/fw/IkFadeSolver.h"
#include "classes/fw/IkSolver.h"
#include "classes/fw/ReferenceFrame.h"
#include "classes/anm/Pose.h"
#include "classes/anm/Skeleton.h"
#include "anm/QsTransform.h"
#include "fw/Allocator.h"
#include "fw/UpdateInfo.h"
#include "classes/mm/mtl/IAllocator.h"
#include "mm/Quat.h"
#include "math.h"

namespace fw {

PlaneRayCaster::PlaneRayCaster() : m_ground(nullptr) {}

void PlaneRayCaster::bind(IKFootGroundInterface& ground) {
    m_ground = &ground;
}

// castRay (0x7100187030) is not here yet: written as
//     if (m_ground == nullptr) return false;
//     const mm::Plane* plane = m_ground->getPlane();
//     if (plane == nullptr) return false;
//     float fromDistance = plane->d + from.dot(plane->normal);
//     if (fromDistance < 0.0f) return false;
//     if (plane->d + plane->normal.dot(to) > 0.0f) return false;
//     mm::Vec3 dir = to - from;
//     float denom = fabsf(dir.dot(plane->normal));
//     float t = denom > 1.1920929e-07f ? fabsf(fromDistance) / denom : 0.0f;
//     *pHitPos = mm::Vec3(dir.x * t + from.x, dir.y * t + from.y, dir.z * t + from.z);
//     *pNormal = plane->normal;
//     return true;
// its data flow is the original's; the original keeps the result in one register for every early return (its
// false set before the plane's check) where this returns each false on its own
// (and multiplies the difference's x by the normal's x, dir first: its normal is loaded after the difference, where
// this reuses the first check's loads and puts the normal first)

LookAtIkSolver* LookAtIkSolver::create(const ParamAdapter& param, const char* bone,
                                       mm::mtl::IntrusivePtr<ReferenceFrame>& frame, anm::Pose& pose) {
#line 42
    LookAtIkSolver* solver = new (Allocator::getProcAllocator(), 16, __FILE__, __LINE__) LookAtIkSolver();
    solver->addRef();
    if (!solver->setupLimit(param, bone, frame, pose)) {
        if (solver != nullptr) {
            solver->release();
        }
        return nullptr;
    }
    return solver;
}

bool LookAtIkSolver::setupLimit(const ParamAdapter& param, const char* bone,
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

LookAtIkSolver::~LookAtIkSolver() {}

void LookAtIkSolver::resetLimit() {
    mm::Quat rotation = m_pose->getBoneModelSpace(m_bone).m_rotation;
    mm::Quat inverse = mm::Quat::inverse(rotation);
    m_limit.pad_10 = mm::Vec3::zero;
    m_limit.fwdLS = inverse.rotate(mm::Vec3::unitZ);
    m_limit.limitAxisMS = mm::Vec3::unitZ;
    m_limit.limitAngle = 3.14159274f;  // PI
    m_range.upAxisMS = mm::Vec3::unitY;
    resetLimitParam();
}

void LookAtIkSolver::calcIK(UpdateInfo const& info) {
    if (m_fadeType != FADE_OUT) {
        const mm::Vec3& position = m_frame->m_worldTransform.position;
        mm::Quat rotation = m_frame->m_worldTransform.rotation;
        mm::Quat inverse = mm::Quat::inverse(rotation);
        // the difference goes into m_localTarget first and is turned there: rotate reads it back z, y, x, the
        // order the original's sums put their products in (straight from the difference they come out x first)
        m_localTarget = m_target - position;
        m_localTarget = inverse.rotate(m_localTarget);
    }
    mm::Vec3 target = m_localTarget;
    target.y = target.y * (!(target.y >= 0.0f) ? m_targetDownRatio : m_targetUpRatio);
    anm::QsTransform transform = m_pose->getBoneModelSpace(m_bone);
    anm::LookAtIKSolver::solve(m_limit, target, m_weight, &transform, &m_range);
    if (m_targetFade) {
        m_targetFadeElapsed = info.m_deltaTime + m_targetFadeElapsed;
        float t;
        if (m_targetFadeElapsed >= m_targetFadeTime) {
            m_targetFade = false;
            t = 1.0f;
        } else {
            t = m_targetFadeElapsed / m_targetFadeTime;
        }
        t = calcBezier(t, 0.0f, 1.0f);
        mm::Quat& to = transform.m_rotation;
        const mm::Quat& from = m_targetFadeRotation;
        float sign = from.x * to.x + from.y * to.y + from.z * to.z + from.w * to.w >= 0.0f ? 1.0f : -1.0f;
        mm::Quat signedTo(to.x * sign, to.y * sign, to.z * sign, to.w * sign);
        float u = 1.0f - t;
        mm::Quat fromPart(u * from.x, u * from.y, u * from.z, u * from.w);
        mm::Quat toPart(t * signedTo.x, t * signedTo.y, t * signedTo.z, t * signedTo.w);
        to = mm::Quat(fromPart.x + toPart.x, fromPart.y + toPart.y, fromPart.z + toPart.z, fromPart.w + toPart.w);
        float lengthSq = to.x * to.x + to.y * to.y;
        lengthSq = to.z * to.z + lengthSq;
        lengthSq = to.w * to.w + lengthSq;
        float scale = 1.0f / sqrtf(lengthSq);
        to.x = to.x * scale;
        to.y = scale * to.y;
        to.z = scale * to.z;
        to.w = scale * to.w;
        lengthSq = to.x * to.x + to.y * to.y;
        lengthSq = lengthSq + to.z * to.z;
        lengthSq = to.w * to.w + lengthSq;
        scale = 1.0f / sqrtf(lengthSq);
        to.x = to.x * scale;
        to.y = scale * to.y;
        to.z = scale * to.z;
        to.w = scale * to.w;
    }
    m_pose->setBoneModelSpace(m_bone, transform, anm::Pose::PROPAGATE_TYPE(1));
}

void LookAtIkSolver::startTargetFade(float time) {
    if (time > 0.0f) {
        m_targetFade = true;
        m_targetFadeRotation = m_pose->getBoneModelSpace(m_bone).m_rotation;
        m_targetFadeElapsed = 0.0f;
        m_targetFadeTime = time;
    }
}

void LookAtIkSolver::onDisable() {
    m_targetFade = false;
    m_targetFadeRotation = mm::Quat::identity;
    m_targetFadeElapsed = 0.0f;
    m_targetFadeTime = 0.0f;
}

mm::mtl::RTTI LookAtIkSolver::m_rtti("LookAtIkSolver", &IkFadeSolver::m_rtti, nullptr);

}  // namespace fw

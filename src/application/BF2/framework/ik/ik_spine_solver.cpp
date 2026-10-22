#include "anm/SpineIkSolver.h"
#include "classes/fw/SpineIkSolver.h"
#include "fw/UpdateInfo.h"
#include "math.h"
#include "classes/fw/IkFadeSolver.h"
#include "classes/fw/SpineIkSolver.h"
#include "classes/fw/IkSolver.h"
#include "classes/anm/Pose.h"
#include "classes/anm/Skeleton.h"
#include "anm/QsTransform.h"
#include "fw/Allocator.h"
#include "classes/mm/mtl/IAllocator.h"

namespace fw {

SpineIkSolver* SpineIkSolver::create(const ParamAdapter& param, const char* firstBone, const char* secondBone,
                                     mm::mtl::IntrusivePtr<ReferenceFrame>& frame, anm::Pose& pose) {
#line 42
    SpineIkSolver* solver = new (Allocator::getProcAllocator(), 16, __FILE__, __LINE__) SpineIkSolver();
    solver->addRef();
    if (!solver->setupLimit(param, firstBone, secondBone, frame, pose)) {
        if (solver != nullptr) {
            solver->release();
        }
        return nullptr;
    }
    return solver;
}

bool SpineIkSolver::setupLimit(const ParamAdapter& param, const char* firstBone, const char* secondBone,
                               mm::mtl::IntrusivePtr<ReferenceFrame>& frame, anm::Pose& pose) {
    bind(frame, pose);
    const anm::Skeleton* skeleton = m_pose->m_pSkeleton;
    if (firstBone != nullptr) {
        m_desc.bones[0] = skeleton->getBoneIndex(firstBone);
    }
    if (secondBone != nullptr) {
        m_desc.bones[1] = skeleton->getBoneIndex(secondBone);
    }
    m_param = param;
    resetLimit();
    return m_desc.bones[0] != 0xFFFF || m_desc.bones[1] != 0xFFFF;
}

SpineIkSolver::~SpineIkSolver() {}

void SpineIkSolver::onDisable() {
    m_targetFade = false;
    m_targetFadeRotation0 = mm::Quat::identity;
    m_targetFadeRotation1 = mm::Quat::identity;
    m_targetFadeElapsed = 0.0f;
    m_targetFadeTime = 0.0f;
}

void SpineIkSolver::startTargetFade(float time) {
    if (time > 0.0f) {
        m_targetFade = true;
        if (m_desc.bones[0] != 0xFFFF) {
            m_targetFadeRotation0 = m_pose->getBoneModelSpace(m_desc.bones[0]).m_rotation;
        }
        if (m_desc.bones[1] != 0xFFFF) {
            m_targetFadeRotation1 = m_pose->getBoneModelSpace(m_desc.bones[1]).m_rotation;
        }
        m_targetFadeElapsed = 0.0f;
        m_targetFadeTime = time;
    }
}

void SpineIkSolver::calcIK(const UpdateInfo& info) {
    anm::SpineIKSolver::Input input;
    if (m_fadeType != FADE_OUT) {
        const mm::Vec3& position = m_frame->m_worldTransform.position;
        mm::Quat rotation = m_frame->m_worldTransform.rotation;
        mm::Quat inverse = mm::Quat::inverse(rotation);
        m_localTarget = m_target - position;
        m_localTarget = inverse.rotate(m_localTarget);
    }
    input.target = m_localTarget;
    input.frontMS = m_frontMS;
    input.weight0 = m_weight;
    input.weight1 = m_weight;
    anm::QsTransform transform0;
    anm::QsTransform transform1;
    if (m_desc.bones[0] != 0xFFFF) {
        transform0 = m_pose->getBoneModelSpace(m_desc.bones[0]);
    }
    if (m_desc.bones[1] != 0xFFFF) {
        transform1 = m_pose->getBoneModelSpace(m_desc.bones[1]);
    }
    anm::SpineIKSolver::Output output;
    anm::SpineIKSolver::solve(m_desc, input, &transform0, &transform1, &output);
    bool solved0 = (output.flags & 1) != 0;
    bool solved1 = (output.flags & 2) != 0;
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
        if (m_desc.bones[0] != 0xFFFF) {
            mm::Quat& to = transform0.m_rotation;
            const mm::Quat& from = m_targetFadeRotation0;
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
            solved0 = true;
        }
        if (m_desc.bones[1] != 0xFFFF) {
            mm::Quat& to = transform1.m_rotation;
            const mm::Quat& from = m_targetFadeRotation1;
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
            solved1 = true;
        }
    }
    if (solved0 && solved1) {
        m_pose->setBoneModelSpace(m_desc.bones[0], transform0, anm::Pose::PROPAGATE_TYPE(0));
        m_pose->setBoneModelSpace(m_desc.bones[1], transform1, anm::Pose::PROPAGATE_TYPE(1));
    } else if (solved0) {
        m_pose->setBoneModelSpace(m_desc.bones[0], transform0, anm::Pose::PROPAGATE_TYPE(1));
    } else if (solved1) {
        m_pose->setBoneModelSpace(m_desc.bones[1], transform1, anm::Pose::PROPAGATE_TYPE(1));
    }
    m_solveValues[0] = output.values[0];
    m_solveValues[1] = output.values[1];
}

mm::mtl::RTTI SpineIkSolver::m_rtti("SpineIkSolver", &IkFadeSolver::m_rtti, nullptr);

}  // namespace fw

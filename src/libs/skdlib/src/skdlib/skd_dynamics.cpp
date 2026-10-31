#include <math.h>
#include <new>
#include "anm/Array.h"
#include "anm/QsTransform.h"
#include "anm/TransformUtil.h"
#include "mm/Math.h"
#include "mm/Quat.h"
#include "mm/Vec3.h"
#include "mm/Vec4.h"
#include "mm/mtl/Vector.h"
#include "classes/anm/Pose.h"
#include "classes/anm/Skeleton.h"
#include "skd/CollisionObj.h"
#include "skd/Factory.h"
#include "skd/Packet.h"
#include "skd/ResSolver.h"
#include "classes/skd/CollisionObject.h"
#include "classes/skd/Dynamics.h"
#include "classes/skd/DynamicsSolver.h"

namespace skd {

CollisionObject::CollisionObject(const ResCollisionArray& res, anm::Pose& pose, mm::mtl::IAllocator* allocator)
    : anm::ReferenceObject(allocator), m_collisions(allocator, res, pose) {
    m_pPose = &pose;
    m_pPose->addRef();
}

CollisionObject::~CollisionObject() {
    if (m_pPose != nullptr) {
        m_pPose->release();
        m_pPose = nullptr;
    }
}

void CollisionObject::update() {
    m_collisions.update(*m_pPose);
}

Dynamics::Dynamics(CollisionObject& colObj, const anm::Array<ResSolver>& solvers, anm::Pose& pose,
                   ForceInterface* force, mm::mtl::IAllocator* allocator)
    : anm::ReferenceObject(allocator), m_pResSolver(&solvers), m_solvers(allocator), m_packet(allocator, pose),
      m_paramA(0.1f), m_paramB(0.0f) {
    m_pColObj = &colObj;
    m_pColObj->addRef();
    m_packet.m_pForce = force;
    createSolver();
}

void Dynamics::createSolver() {
#line 238
    MM_ASSERT(m_pResSolver);
    MM_ASSERT(m_solvers.size() == 0);
    mm::mtl::IAllocator* allocator = m_pAllocator;
    unsigned int count = m_pResSolver->size();
    m_solvers.resize(count);
    for (unsigned int i = 0; i < count; i++) {
        const ResSolver& res = (*m_pResSolver)[i];
        m_solvers[i] = new (allocator->allocate(sizeof(DynamicsSolver), 8)) DynamicsSolver(allocator, res, i);
        m_solvers[i]->init(m_packet);
    }
}

Dynamics::~Dynamics() {
    if (m_pColObj != nullptr) {
        m_pColObj->release();
        m_pColObj = nullptr;
    }
    unsigned int count = m_pResSolver->size();
    for (unsigned int i = 0; i < count; i++) {
        delete m_solvers[i];
    }
    m_solvers.clear();
}

void Dynamics::update(float deltaTime) {
    if (deltaTime < 1.1920928955078125e-07F) {
        return;
    }
    unsigned int count = m_solvers.size();
    for (unsigned int i = 0; i < count; i++) {
#line 67
        MM_ASSERT(m_solvers[i]);
        m_solvers[i]->solve(deltaTime, m_pColObj->m_collisions, m_packet);
    }
}

void Dynamics::notifyMovement(const mm::Vec3& position, const mm::Quat& rotation, const mm::Vec3& moveDelta,
                              const mm::Quat& rotateDelta) {
    anm::QsTransform inverse;
    anm::QsTransform current;
    current.m_translation = mm::Vec4(position.x, position.y, position.z, 1.0f);
    current.m_rotation = rotation;
    if (current.m_rotation.w < 0.0f) {
        current.m_rotation.x = -current.m_rotation.x;
        current.m_rotation.y = -current.m_rotation.y;
        current.m_rotation.z = -current.m_rotation.z;
        current.m_rotation.w = -current.m_rotation.w;
    }
    current.m_scale = mm::Vec4::unit;
    anm::QsTransform delta;
    delta.m_translation = mm::Vec4(moveDelta.x, moveDelta.y, moveDelta.z, 1.0f);
    delta.m_rotation = rotateDelta;
    if (delta.m_rotation.w < 0.0f) {
        delta.m_rotation.x = -delta.m_rotation.x;
        delta.m_rotation.y = -delta.m_rotation.y;
        delta.m_rotation.z = -delta.m_rotation.z;
        delta.m_rotation.w = -delta.m_rotation.w;
    }
    delta.m_scale = mm::Vec4::unit;
    anm::TransformUtil::invert(current, &inverse);
    anm::QsTransform move;
    anm::TransformUtil::mul(inverse, delta, &move);

    float length = ::sqrtf(move.m_translation.x * move.m_translation.x + move.m_translation.y * move.m_translation.y +
                           move.m_translation.z * move.m_translation.z);
    if (length >= m_paramA && m_paramA > 0.0f) {
        float scale = m_paramA / length;
        move.m_translation.x *= scale;
        move.m_translation.y *= scale;
        move.m_translation.z *= scale;
        move.m_translation.w *= scale;
    }
    if (m_paramB > 0.0f) {
        mm::Vec3 axis = move.m_rotation.rotate(mm::Vec3::unitZ);
        float angle = ::acosf(mm::clamp(axis.dot(mm::Vec3::unitZ), -1.0f, 1.0f));
        float ratio = angle / m_paramB;
        if (ratio > 1.0f) {
            float t = 1.0f / ratio;
            mm::Quat q = (1.0f - t) * mm::Quat::identity + t * move.m_rotation;
            float scale = 1.0f / ::sqrtf(q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w);
            move.m_rotation = mm::Quat(scale * q.x, scale * q.y, scale * q.z, scale * q.w);
        }
    }
    unsigned int count = m_pResSolver->size();
    for (unsigned int i = 0; i < count; i++) {
        m_solvers[i]->convertCoordinateSystem(move);
    }
}

void Dynamics::resetDynamics() {
    unsigned int count = m_pResSolver->size();
    for (unsigned int i = 0; i < count; i++) {
        m_solvers[i]->resetNodes(m_packet);
    }
}

void Dynamics::setSolverBlendWeight(unsigned int index, float weight) {
    if (index == 0xFFFFFFFF) {
        return;
    }
    if (m_solvers[index] != nullptr) {
        m_solvers[index]->m_blendWeight = weight;
    }
}

}  // namespace skd

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

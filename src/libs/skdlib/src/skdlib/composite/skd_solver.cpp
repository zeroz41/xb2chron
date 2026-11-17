#include "anm/Array.h"
#include "anm/JobQueue.h"
#include "mm/mtl/FixedVector.h"
#include "mm/mtl/Vector.h"
#include "skd/ResSolver.h"
#include "skd/NodeArray.h"
#include "skd/DetectInfo.h"
#include "skd/CalcUtil.h"
#include "skd/Solver.h"
#include "classes/skd/DynamicsSolver.h"
#include "classes/anm/ThreadPool.h"
#include "classes/fw/ForceCalculator.h"
#include "skd/Packet.h"

namespace skd {

DynamicsSolver::DynamicsSolver(mm::mtl::IAllocator* allocator, const ResSolver& res, unsigned int index)
    : m_pRes(&res), m_nodes(allocator, res.m_nodes, res.m_collisions), m_prevDeltaTime(1.0f / 30.0f),
      m_forces(allocator), m_index(index), m_blendWeight(0.0f), m_initialized(false) {
    m_forces.resize(res.m_nodes.size(), mm::Vec3::zero);
}

void DynamicsSolver::init(const Packet& packet) {
    m_initialized = CalcUtil::initNodes(*packet.m_pBindPose, &m_nodes);
}

void DynamicsSolver::solve(float deltaTime, const CollionArray& collisions, const Packet& packet) {
    if (!m_initialized) {
        return;
    }
#line 64
    MM_ASSERT(deltaTime > 1.1920928955078125e-07F);
    CalcUtil::cacheNode(*packet.m_pBindPose, &m_nodes);
    mm::Vec3* first = m_forces.begin();
    for (long n = m_forces.end() - first; n > 0; --n, ++first) {
        *first = mm::Vec3::zero;
    }
    if (packet.m_pForce != nullptr) {
        packet.m_pForce->calcForce(deltaTime, *this, &m_forces);
    }
    CalcUtil::addForceTransform(m_nodes, &m_forces);
    CalcUtil::addForceSpring(m_nodes, m_pRes->m_springConstraints, &m_forces);
    CalcUtil::applyAccel(m_forces, &m_nodes);
    CalcUtil::integrate(m_prevDeltaTime, deltaTime, &m_nodes);
    for (unsigned int i = 0; i < static_cast<unsigned int>(packet.m_level); ++i) {
        CalcUtil::detectCollision(collisions, &m_nodes);
        CalcUtil::applySpringConstraints(m_pRes->m_springConstraints, &m_nodes);
        CalcUtil::applyHingeConstraints(m_pRes->m_hingeConstraints, &m_nodes);
        CalcUtil::applyStickConstraints(m_pRes->m_stickConstraints, &m_nodes);
    }
    if (fabsf(m_blendWeight) > 1.1920928955078125e-07F) {
        CalcUtil::blendNode(m_blendWeight, &m_nodes);
    }
    CalcUtil::applyPose(m_nodes, packet.m_pBindPose);
    CalcUtil::writeBackNode(*packet.m_pBindPose, &m_nodes);
    m_prevDeltaTime = deltaTime;
}

void DynamicsSolver::solveMT(float deltaTime, const CollionArray& collisions, const Packet& packet,
                             anm::ThreadPool& pool) {
    if (!m_initialized) {
        return;
    }
#line 120
    MM_ASSERT(deltaTime > 1.1920928955078125e-07F);
    CalcUtil::cacheNode(*packet.m_pBindPose, &m_nodes);
    mm::Vec3* first = m_forces.begin();
    for (long n = m_forces.end() - first; n > 0; --n, ++first) {
        *first = mm::Vec3::zero;
    }
    if (packet.m_pForce != nullptr) {
        packet.m_pForce->calcForce(deltaTime, *this, &m_forces);
    }
    CalcUtil::addForceTransform(m_nodes, &m_forces);
    CalcUtil::addForceSpring(m_nodes, m_pRes->m_springConstraints, &m_forces);
    CalcUtil::applyAccel(m_forces, &m_nodes);
    CalcUtil::integrate(m_prevDeltaTime, deltaTime, &m_nodes);
    DetectInfoBuffer buffer;
    anm::JobQueue* queue = const_cast<anm::JobQueue*>(&packet.m_jobQueue);
    for (unsigned int i = 0; i < static_cast<unsigned int>(packet.m_level); ++i) {
        CalcUtil::buildDetectCollisionJobs(collisions, m_nodes, &buffer, queue);
        pool.processAllJob(*queue);
        pool.waitForCompletion();
        addApplyDetectJobs(buffer, &m_nodes, queue);
        pool.processAllJob(*queue);
        pool.waitForCompletion();
        buffer.clear();
        CalcUtil::applySpringConstraints(m_pRes->m_springConstraints, &m_nodes);
        CalcUtil::applyHingeConstraints(m_pRes->m_hingeConstraints, &m_nodes);
        CalcUtil::applyStickConstraints(m_pRes->m_stickConstraints, &m_nodes);
    }
    CalcUtil::applyPose(m_nodes, packet.m_pBindPose);
    CalcUtil::writeBackNode(*packet.m_pBindPose, &m_nodes);
    m_prevDeltaTime = deltaTime;
}

void DynamicsSolver::convertCoordinateSystem(const anm::QsTransform& transform) {
    CalcUtil::convertCoordinateSystem(transform, &m_nodes);
}

void DynamicsSolver::resetNodes(const Packet& packet) {
    CalcUtil::initNodes(*packet.m_pBindPose, &m_nodes);
}

DynamicsSolver::~DynamicsSolver() {}

// addApplyDetectJobs (0x710088C17C) is not identical yet

}  // namespace skd

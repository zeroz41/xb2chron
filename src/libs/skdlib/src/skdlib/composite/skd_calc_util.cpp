#include "anm/Array.h"
#include "anm/JobQueue.h"
#include "anm/QsTransform.h"
#include "classes/anm/Pose.h"
#include "classes/anm/Skeleton.h"
#include "mm/mtl/Vector.h"
#include "skd/CalcUtil.h"
#include "skd/CollisionObj.h"
#include "skd/DetectInfo.h"
#include "skd/DetectJob.h"
#include "skd/ResSolver.h"
#include "skd/NodeArray.h"

namespace skd {

void CalcUtil::addForceTransform(const NodeArray& nodes, mm::mtl::Vector<mm::Vec3>* forces) {
    unsigned int count = nodes.m_nodes.size();
    for (unsigned int i = 0; i < count; i++) {
        const ResNode& res = (*nodes.m_pResNodes)[i];
        const Node& node = nodes.m_nodes[i];
        mm::Vec3 offset = node.m_pos - node.m_parentPos;
        mm::Quat parentRot = node.m_parentRot;
        mm::Vec3 local = mm::Quat::inverse(parentRot).rotate(offset);
        mm::Vec3 force = (node.m_localPos - local) * res.m_localStiffness;
        mm::Vec3 worldForce = node.m_parentRot.rotate(force);
        (*forces)[i] += worldForce;
    }
    for (unsigned int i = 0; i < count; i++) {
        const ResNode& res = (*nodes.m_pResNodes)[i];
        const Node& node = nodes.m_nodes[i];
        mm::Vec3 force = (node.m_animPos - node.m_pos) * res.m_animStiffness;
        (*forces)[i] += force;
    }
}

void CalcUtil::addForceSpring(const NodeArray& nodes, const anm::Array<ResSpringConstraint>& constraints,
                              mm::mtl::Vector<mm::Vec3>* forces) {
    unsigned int count = constraints.size();
    for (unsigned int i = 0; i < count; i++) {
        const ResSpringConstraint& constraint = constraints[i];
        const Node& node0 = nodes.m_nodes[constraint.m_constraint.m_node0];
        const Node& node1 = nodes.m_nodes[constraint.m_constraint.m_node1];
        mm::Vec3 dir = node0.m_pos - node1.m_pos;
        float length = dir.length();
        if (length > 1.1920928955078125e-07F) {
            dir = dir * (1.0f / length);
        }
        mm::Vec3 force = dir * ((length - constraint.m_constraint.m_length) * constraint.m_stretch);
        (*forces)[constraint.m_constraint.m_node0] -= force;
        (*forces)[constraint.m_constraint.m_node1] += force;
    }
}

void CalcUtil::applyAccel(mm::mtl::Vector<mm::Vec3>& forces, NodeArray* nodes) {
    unsigned int count = nodes->m_nodes.size();
    for (unsigned int i = 0; i < count; i++) {
        const ResNode& res = (*nodes->m_pResNodes)[i];
        Node& node = nodes->m_nodes[i];
        node.m_accel = forces[i] * (1.0f / res.m_mass);
    }
}

void CalcUtil::integrate(float prevDeltaTime, float deltaTime, NodeArray* nodes) {
#line 229
    MM_ASSERT(prevDeltaTime > 1.1920928955078125e-07F);
    float deltaTime2 = deltaTime * deltaTime;
    float ratio = deltaTime / prevDeltaTime;
    unsigned int count = nodes->m_nodes.size();
    for (unsigned int i = 0; i < count; i++) {
        const ResNode& res = (*nodes->m_pResNodes)[i];
        Node& node = nodes->m_nodes[i];
        if (!res.isFixed()) {
            mm::Vec3 velocity = (node.m_pos - node.m_prevPos) * (1.0f - res.m_damping);
            node.m_nextPos = node.m_pos + ratio * velocity + deltaTime2 * node.m_accel;
        } else {
            node.m_nextPos = node.m_animPos;
        }
    }
}

void CalcUtil::applyStickConstraints(const anm::Array<ResStickConstraint>& constraints, NodeArray* nodes) {
    unsigned int count = constraints.size();
    for (unsigned int i = 0; i < count; i++) {
        const ResStickConstraint& constraint = constraints[i];
        limitCone(constraint.m_constraint, constraint.m_cone, nodes);
    }
    for (unsigned int i = 0; i < count; i++) {
        limitDistance(constraints[i].m_constraint, nodes);
    }
}

void CalcUtil::applyHingeConstraints(const anm::Array<ResHingeConstraint>& constraints, NodeArray* nodes) {
    unsigned int count = constraints.size();
    for (unsigned int i = 0; i < count; i++) {
        limitHinge(constraints[i], nodes);
    }
    for (unsigned int i = 0; i < count; i++) {
        limitDistance(constraints[i].m_constraint, nodes);
    }
}

void CalcUtil::detectCollision(const CollionArray& collisions, NodeArray* nodes) {
    const anm::Array<ResNodeCollision>& resCollisions = *nodes->m_pResCollisions;
    const ResNodeCollision* end = resCollisions.m_pElements + resCollisions.size();
    for (const ResNodeCollision* it = resCollisions.m_pElements; it != end; ++it) {
        const ResNodeCollision& collision = *it;
        (*nodes->m_pResNodes)[collision.m_node0];
        (*nodes->m_pResNodes)[collision.m_node1];
        detectCollisionSpheres(collision, collisions, 0, nodes);
        detectCollisionCapsules(collision, collisions, 0, nodes);
        detectCollisionPlanes(collision, collisions, 0, nodes);
    }
}

void CalcUtil::buildDetectCollisionJobs(const CollionArray& collisions, const NodeArray& nodes,
                                        DetectInfoBuffer* buffer, anm::JobQueue* queue) {
    const anm::Array<ResNodeCollision>& resCollisions = *nodes.m_pResCollisions;
    anm::ArrayIterartor<const ResNodeCollision> end = resCollisions.end();
    for (anm::ArrayIterartor<const ResNodeCollision> it = resCollisions.begin(); it != end; ++it) {
        const ResNodeCollision& collision = *it;
        const Node& node0 = nodes.m_nodes[collision.m_node0];
        const Node& node1 = nodes.m_nodes[collision.m_node1];
        mm::Vec3 center = (1.0f - collision.m_weight) * node0.m_nextPos + collision.m_weight * node1.m_nextPos;
        for (const ShpereCollObj& sphere : collisions.m_spheres) {
            addDetectSphereJob(&sphere, &*it, &nodes, center, buffer, queue);
        }
        for (const CapsuleCollObj& capsule : collisions.m_capsules) {
            addDetectCapsuleJob(&capsule, &*it, &nodes, center, buffer, queue);
        }
        for (const PlaneCollObj& plane : collisions.m_planes) {
            addDetectPlaneJob(&plane, &*it, &nodes, center, buffer, queue);
        }
    }
}

void CalcUtil::blendNode(float weight, NodeArray* nodes) {
    unsigned int count = nodes->m_nodes.size();
    for (unsigned int i = 0; i < count; i++) {
        Node& node = nodes->m_nodes[i];
        node.m_nextPos = (1.0f - weight) * node.m_nextPos + node.m_animPos * weight;
    }
}

void CalcUtil::writeBackNode(anm::Pose& pose, NodeArray* nodes) {
    unsigned int count = nodes->m_nodes.size();
    const anm::Skeleton* skeleton = pose.m_pSkeleton;
    for (unsigned int i = 0; i < count; i++) {
        Node& node = nodes->m_nodes[i];
        unsigned short bone = node.m_bone;
        node.m_prevPos = node.m_pos;
        node.m_pos = node.m_nextPos;
        unsigned short parent = skeleton->m_parents[bone];
        if (parent != 0xFFFF) {
            const anm::QsTransform& transform = pose.getBoneModelSpace(parent);
            node.m_parentPos = mm::Vec3(transform.m_translation.x, transform.m_translation.y, transform.m_translation.z);
            node.m_parentRot = transform.m_rotation;
        }
    }
}

NodeArray::NodeArray(mm::mtl::IAllocator* allocator, const anm::Array<ResNode>& resNodes,
                     const anm::Array<ResNodeCollision>& resCollisions)
    : m_pResNodes(&resNodes), m_pResCollisions(&resCollisions), m_nodes(allocator) {
    m_nodes.resize(resNodes.size());
}

}  // namespace skd

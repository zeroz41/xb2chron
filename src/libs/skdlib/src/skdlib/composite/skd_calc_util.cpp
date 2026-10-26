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

const char* DetectCapsuleJob::_TYPE_NAME = "DetectCapsuleJob";

void executeDetectCapsuleJob(anm::Job& job) {
    DetectCapsuleJob& capsuleJob = static_cast<DetectCapsuleJob&>(job);
    const ResNodeCollision* collision = capsuleJob.m_pCollision;
    mm::Vec3 push;
    if (capsuleJob.m_pObj->detect(collision->m_radius, capsuleJob.m_pos, &push)) {
        if (capsuleJob.m_pInfo0 != nullptr) {
            capsuleJob.m_pInfo0->m_push = push * (1.0f - collision->m_weight);
            capsuleJob.m_pInfo0->m_hit = true;
        }
        if (capsuleJob.m_pInfo1 != nullptr) {
            capsuleJob.m_pInfo1->m_push = collision->m_weight * push;
            capsuleJob.m_pInfo1->m_hit = true;
        }
    }
}

void registerDetectCapsuleJobExecuter(anm::JobQueue* queue) {
    queue->registerFunc(1, executeDetectCapsuleJob);
}

void addDetectCapsuleJob(const CapsuleCollObj* obj, const ResNodeCollision* collision, const NodeArray* nodes,
                         const mm::Vec3& pos, DetectInfoBuffer* buffer, anm::JobQueue* queue) {
    if (collision->m_groupMask & (1 << obj->m_pRes->m_group)) {
        DetectInfo* info0;
        if ((*nodes->m_pResNodes)[collision->m_node0].isFixed()) {
            info0 = nullptr;
        } else {
            info0 = buffer->alloc();
            info0->m_node = collision->m_node0;
        }
        DetectInfo* info1;
        if ((*nodes->m_pResNodes)[collision->m_node1].isFixed()) {
            info1 = nullptr;
        } else {
            info1 = buffer->alloc();
            info1->m_node = collision->m_node1;
        }
        queue->push(DetectCapsuleJob(obj, collision, pos, info0, info1));
    }
}

const char* DetectPlaneJob::_TYPE_NAME = "DetectPlaneJob";

void executeDetectPlaneJob(anm::Job& job) {
    DetectPlaneJob& planeJob = static_cast<DetectPlaneJob&>(job);
    const ResNodeCollision* collision = planeJob.m_pCollision;
    mm::Vec3 push;
    if (planeJob.m_pObj->detect(collision->m_radius, planeJob.m_pos, &push)) {
        if (planeJob.m_pInfo0 != nullptr) {
            planeJob.m_pInfo0->m_push = push * (1.0f - collision->m_weight);
            planeJob.m_pInfo0->m_hit = true;
        }
        if (planeJob.m_pInfo1 != nullptr) {
            planeJob.m_pInfo1->m_push = collision->m_weight * push;
            planeJob.m_pInfo1->m_hit = true;
        }
    }
}

void registerDetectPlaneJobExecuter(anm::JobQueue* queue) {
    queue->registerFunc(2, executeDetectPlaneJob);
}

void addDetectPlaneJob(const PlaneCollObj* obj, const ResNodeCollision* collision, const NodeArray* nodes,
                       const mm::Vec3& pos, DetectInfoBuffer* buffer, anm::JobQueue* queue) {
    if (collision->m_groupMask & (1 << obj->m_pRes->m_group)) {
        DetectInfo* info0;
        if ((*nodes->m_pResNodes)[collision->m_node0].isFixed()) {
            info0 = nullptr;
        } else {
            info0 = buffer->alloc();
            info0->m_node = collision->m_node0;
        }
        DetectInfo* info1;
        if ((*nodes->m_pResNodes)[collision->m_node1].isFixed()) {
            info1 = nullptr;
        } else {
            info1 = buffer->alloc();
            info1->m_node = collision->m_node1;
        }
        queue->push(DetectPlaneJob(obj, collision, pos, info0, info1));
    }
}

}  // namespace skd

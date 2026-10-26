#include "anm/JobQueue.h"
#include "skd/CollisionObj.h"
#include "skd/DetectInfo.h"
#include "skd/DetectJob.h"
#include "skd/NodeArray.h"

namespace skd {

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

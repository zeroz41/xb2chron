// skdlib's sphere detection jobs and LibMessageStudio's memory functions, as the split places them. Both cite
// skdlib's include paths (SKD_LIB_PROJECT), which a unit outside libs/skdlib does not get from its command.
#define MM_LIB_FROM_LIBS
#define SKD_LIB_PROJECT
#include "anm/Array.h"
#include "anm/JobQueue.h"
#include "skd/CalcUtil.h"
#include "skd/CollisionObj.h"
#include "skd/DetectInfo.h"
#include "skd/DetectJob.h"
#include "skd/ResSolver.h"
#include "skd/NodeArray.h"
#include "lms/libms.h"

namespace skd {

const char* DetectSphereJob::_TYPE_NAME = "DetectSphereJob";

void executeDetectSphereJob(anm::Job& job) {
    DetectSphereJob& sphereJob = static_cast<DetectSphereJob&>(job);
    const ResNodeCollision* collision = sphereJob.m_pCollision;
    mm::Vec3 push;
    if (sphereJob.m_pObj->detect(collision->m_radius, sphereJob.m_pos, &push)) {
        if (sphereJob.m_pInfo0 != nullptr) {
            sphereJob.m_pInfo0->m_push = push * (1.0f - collision->m_weight);
            sphereJob.m_pInfo0->m_hit = true;
        }
        if (sphereJob.m_pInfo1 != nullptr) {
            sphereJob.m_pInfo1->m_push = collision->m_weight * push;
            sphereJob.m_pInfo1->m_hit = true;
        }
    }
}

void registerDetectSphereJobExecuter(anm::JobQueue* queue) {
    queue->registerFunc(0, executeDetectSphereJob);
}

void addDetectSphereJob(const ShpereCollObj* obj, const ResNodeCollision* collision, const NodeArray* nodes,
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
        queue->push(DetectSphereJob(obj, collision, pos, info0, info1));
    }
}

}  // namespace skd

// the functions LMSi_Malloc and LMSi_Free hand on to (the name is not the original's: the symbols leave it unnamed)
static struct {
    LMS_MallocFunc mallocFunc;
    LMS_FreeFunc freeFunc;
} s_memFuncs;

extern "C" {
void LMS_SetMemFuncs(LMS_MallocFunc mallocFunc, LMS_FreeFunc freeFunc) {
    s_memFuncs.mallocFunc = mallocFunc;
    s_memFuncs.freeFunc = freeFunc;
}

void* LMSi_Malloc(size_t size) {
    return s_memFuncs.mallocFunc(size);
}

void LMSi_Free(void* memory) {
    s_memFuncs.freeFunc(memory);
}
}

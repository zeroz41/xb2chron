#include "classes/fw/DynamicsUpdater.h"
#include "classes/fw/EffectPoint.h"
#include "classes/fw/EffectCasterBase.h"
#include "classes/fw/EffectManager.h"
#include "classes/anm/Pose.h"
#include "classes/skd/CollisionObject.h"
#include "classes/skd/Dynamics.h"
#include "classes/fw/DynamicsColObjUpdater.h"
#include "classes/fw/DynamicsUpdater.h"
#include "classes/fw/DyanmicsManager.h"
#include "classes/fw/EffectCasterBase.h"
#include "classes/fw/EffectManager.h"
#include "classes/fw/EffectPoint.h"
#include "mm/mtl/IntrusiveList.h"
#include "mm/mtl/Queue.h"
#include "anm/JobQueue.h"
#include "classes/fw/ManagerObject.h"
#include "classes/fw/AnimationManager.h"
#include "classes/fw/ReferenceFrame.h"
#include "classes/anm/ThreadPool.h"
#include "classes/mm/mtl/IAllocator.h"
#include "classes/mm/mtl/PtrSingleton.h"
#include "fw/Allocator.h"
#include "classes/fw/Framework.h"
#include "fw/UpdateInfo.h"
#include "string.h"

namespace fw {

DyanmicsManager::DyanmicsManager() : m_jobQueue(nullptr) {
    mm::mtl::IAllocator* allocator = Allocator::getProcAllocator();
#line 30
    m_jobQueue = new (allocator, 16, __FILE__, __LINE__) anm::JobQueue(allocator, 128);
    m_jobQueue->registerFunc(0, &DynamicsColUpdateJob::exec);
    m_jobQueue->registerFunc(1, &DynamicsUpdateJob::exec);
}

DyanmicsManager::~DyanmicsManager() {
    mm::mtl::PtrSingleton<AnimationManager>::get()->m_threadPool->waitForCompletion();
    if (m_jobQueue != nullptr) {
        delete m_jobQueue;
        m_jobQueue = nullptr;
    }
}

void DyanmicsManager::addColUpdater(unsigned int layer, DynamicsColObjUpdaterInterface& updater) {
    m_groups[layer].m_colUpdaters.push_back(&updater);
}

void DyanmicsManager::removeColUpdater(unsigned int layer, DynamicsColObjUpdaterInterface& updater) {
    m_groups[layer].m_colUpdaters.remove(&updater);
}

void DyanmicsManager::updateColObjects(unsigned int layerMask) {
    anm::ThreadPool* pool = mm::mtl::PtrSingleton<AnimationManager>::get()->m_threadPool;
    for (unsigned int i = 0; i < 32; i++) {
        if (((1 << i) & layerMask) != 0) {
            mm::mtl::IntrusiveList<DynamicsColObjUpdaterInterface>& list = m_groups[i].m_colUpdaters;
            unsigned int count = list.m_size;
            mm::mtl::IntrusiveList<DynamicsColObjUpdaterInterface>::iterator it = list.begin();
            for (unsigned int k = 0; k < count; k++) {
                DynamicsColUpdateJob job(1);
                job.m_updaters[0] = &*it;
                ++it;
                m_jobQueue->push(job);
            }
        }
    }
    pool->processAllJob(*m_jobQueue);
    pool->waitForCompletion();
}

void DyanmicsManager::addUpdater(unsigned int layer, DynamicsUpdaterInterface& updater) {
    m_groups[layer].m_updaters.push_back(&updater);
}

void DyanmicsManager::removeUpdater(unsigned int layer, DynamicsUpdaterInterface& updater) {
    m_groups[layer].m_updaters.remove(&updater);
}

void DyanmicsManager::updateDynamics(const UpdateInfo& info, unsigned int layerMask) {
    anm::ThreadPool* pool = mm::mtl::PtrSingleton<AnimationManager>::get()->m_threadPool;
    for (unsigned int i = 0; i < 32; i++) {
        if (((1 << i) & layerMask) != 0) {
            DynamicsGroup& group = m_groups[i];
            // the count is the collision list's, as the original's code takes it
            unsigned int count = group.m_colUpdaters.m_size;
            mm::mtl::IntrusiveList<DynamicsUpdaterInterface>::iterator it = group.m_updaters.begin();
            for (unsigned int k = 0; k < count; k++) {
                DynamicsUpdateJob job(1);
                job.m_info = &info;
                job.m_updaters[0] = &*it;
                ++it;
                m_jobQueue->push(job);
            }
        }
    }
    pool->processAllJob(*m_jobQueue);
    pool->waitForCompletion();
}

const char* DyanmicsManager::getName() const {
    return "DyanmicsManager";
}

void DyanmicsManager::update(const UpdateInfo&) {}

}  // namespace fw

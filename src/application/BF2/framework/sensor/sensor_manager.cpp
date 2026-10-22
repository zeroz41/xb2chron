#include "mm/mtl/IntrusiveList.h"
#include "mm/mtl/Queue.h"
#include "anm/JobQueue.h"
#include "classes/fw/ManagerObject.h"
#include "classes/fw/AnimationManager.h"
#include "classes/fw/SensorManager.h"
#include "classes/anm/ThreadPool.h"
#include "classes/mm/mtl/IAllocator.h"
#include "classes/mm/mtl/PtrSingleton.h"
#include "fw/Allocator.h"
#include "fw/UpdateInfo.h"
#include "string.h"

namespace fw {

SensorManager::SensorManager() : m_jobQueue(nullptr) {
    mm::mtl::IAllocator* allocator = Allocator::getProcAllocator();
#line 31
    m_jobQueue = new (allocator, 16, __FILE__, __LINE__) anm::JobQueue(allocator, 128);
    m_jobQueue->registerFunc(0, &SensorUpdateJob::exec);
}

SensorManager::~SensorManager() {
    mm::mtl::PtrSingleton<AnimationManager>::get()->m_threadPool->waitForCompletion();
    if (m_jobQueue != nullptr) {
        delete m_jobQueue;
        m_jobQueue = nullptr;
    }
}

void SensorManager::addUpdaterBeforeGame(unsigned int group, SensorUpdater& updater) {
    m_groups[group].m_beforeGame.push_back(&updater);
    updater.m_registered = true;
}

void SensorManager::removeUpdaterBeforeGame(unsigned int group, SensorUpdater& updater) {
    m_groups[group].m_beforeGame.remove(&updater);
    updater.m_registered = false;
}

void SensorManager::addUpdaterAfterAnimation(unsigned int group, SensorUpdater& updater) {
    m_groups[group].m_afterAnimation.push_back(&updater);
    updater.m_registered = true;
}

void SensorManager::removeUpdaterAfterAnimation(unsigned int group, SensorUpdater& updater) {
    m_groups[group].m_afterAnimation.remove(&updater);
    updater.m_registered = false;
}


void SensorManager::flushBeforeGame(const UpdateInfo&, unsigned int groupMask) {
    anm::ThreadPool* pool = mm::mtl::PtrSingleton<AnimationManager>::get()->m_threadPool;
    for (unsigned int i = 0; i < 32; i++) {
        if (((1 << i) & groupMask) != 0) {
            mm::mtl::IntrusiveList<SensorUpdater>& list = m_groups[i].m_beforeGame;
            unsigned int count = list.m_size;
            mm::mtl::IntrusiveList<SensorUpdater>::iterator it = list.begin();
            unsigned int rest = count & 1;
            for (unsigned int k = 0; k < count / 2; k++) {
                SensorUpdateJob job(2);
                job.m_updaters[0] = &*it;
                ++it;
                job.m_updaters[1] = &*it;
                ++it;
                m_jobQueue->push(job);
            }
            if (rest != 0) {
                SensorUpdateJob job(rest);
                for (unsigned int j = 0; j < rest; j++) {
                    job.m_updaters[j] = &*it;
                    ++it;
                }
                m_jobQueue->push(job);
            }
        }
    }
    pool->processAllJob(*m_jobQueue);
    pool->waitForCompletion();
}

void SensorManager::flushAfterAnimation(const UpdateInfo&, unsigned int groupMask) {
    anm::ThreadPool* pool = mm::mtl::PtrSingleton<AnimationManager>::get()->m_threadPool;
    for (unsigned int i = 0; i < 32; i++) {
        if (((1 << i) & groupMask) != 0) {
            mm::mtl::IntrusiveList<SensorUpdater>& list = m_groups[i].m_afterAnimation;
            unsigned int count = list.m_size;
            mm::mtl::IntrusiveList<SensorUpdater>::iterator it = list.begin();
            unsigned int rest = count & 1;
            for (unsigned int k = 0; k < count / 2; k++) {
                SensorUpdateJob job(2);
                job.m_updaters[0] = &*it;
                ++it;
                job.m_updaters[1] = &*it;
                ++it;
                m_jobQueue->push(job);
            }
            if (rest != 0) {
                SensorUpdateJob job(rest);
                for (unsigned int j = 0; j < rest; j++) {
                    job.m_updaters[j] = &*it;
                    ++it;
                }
                m_jobQueue->push(job);
            }
        }
    }
    pool->processAllJob(*m_jobQueue);
    pool->waitForCompletion();
}

const char* SensorManager::getName() const {
    return "SensorManager";
}

void SensorManager::update(const UpdateInfo&) {}

}  // namespace fw

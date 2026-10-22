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

const char* SensorUpdateJob::_TYPE_NAME = "SensorUpdateJob";

SensorUpdateJob::SensorUpdateJob(unsigned int count) : anm::Job(_TYPE_NAME, sizeof(SensorUpdateJob), 0), m_count(count) {
    m_updaters[0] = nullptr;
    m_updaters[1] = nullptr;
}

void SensorUpdateJob::exec(anm::Job& job) {
    SensorUpdateJob& self = static_cast<SensorUpdateJob&>(job);
    for (int i = 0; i < self.m_count; i++) {
        self.m_updaters[i]->m_delegate();
    }
}

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



// flushBeforeGame (0x710019E7B4) and flushAfterAnimation (0x710019E97C) are not here: the original calls
// SensorUpdateJob's constructor where this file inlines it, as if the job were another file's (its constructor and
// exec, 0x710019E128..0x710019E1A0, with _TYPE_NAME and its string); split that way they are identical (see the
// worker's split/ files)

const char* SensorManager::getName() const {
    return "SensorManager";
}

void SensorManager::update(const UpdateInfo&) {}

}  // namespace fw

#include "classes/fw/ManagerObject.h"
#include "classes/fw/AnimControlUpdater.h"
#include "classes/fw/AnimSinglePoseSamper.h"
#include "classes/fw/AnimationManager.h"
#include "mm/mtl/IntrusiveList.h"
#include "anm/JobQueue.h"
#include "classes/anm/ThreadPool.h"
#include "classes/mm/mtl/IAllocator.h"
#include "classes/mm/mtl/PtrSingleton.h"
#include "fw/Allocator.h"
#include "fw/UpdateInfo.h"
#include "string.h"

namespace fw {

AnimationManager::AnimationManager() : m_threadPool(nullptr), m_jobQueue(nullptr) {
    mm::mtl::IAllocator* allocator = Allocator::getProcAllocator();
    anm::TreadPoolInfo info;
    info.m_threadMask = 3;
    info.m_priority = 2;
    info.m_maxJobs = 2;
#line 40
    m_threadPool = new (allocator, 16, __FILE__, __LINE__) anm::ThreadPool(info, *allocator);
#line 43
    m_jobQueue = new (allocator, 16, __FILE__, __LINE__) anm::JobQueue(allocator, 128);
    m_jobQueue->registerFunc(0, &AnimSamplePoseJob::exec);
    m_jobQueue->registerFunc(1, &AnimModifyPoseJob::exec);
    m_jobQueue->registerFunc(2, &AnimAfterModifyJob::exec);
    m_jobQueue->registerFunc(3, &AnimIkResolveJob::exec);
}

AnimationManager::~AnimationManager() {
    m_threadPool->waitForCompletion();
    if (m_jobQueue != nullptr) {
        delete m_jobQueue;
        m_jobQueue = nullptr;
    }
    if (m_threadPool != nullptr) {
        delete m_threadPool;
        m_threadPool = nullptr;
    }
}

void AnimationManager::addControlUpdater(unsigned int layer, AnimControlUpdaterInterface& item) {
    m_groups[layer].m_controls.push_back(&item);
}

void AnimationManager::removeControlUpdater(unsigned int layer, AnimControlUpdaterInterface& item) {
    m_groups[layer].m_controls.remove(&item);
}

// updateControls (0x7100159564) is not written yet: the closest attempt is 2 words off, one csel scheduled before the end
// iterator's address where the original computes that address first (cached list, uncached list, while and
// cached-end forms and zkit sweep tried).

void AnimationManager::addPoseSampler(unsigned int layer, AnimPoseSamplerInterface& item) {
    m_groups[layer].m_samplers.push_back(&item);
}

void AnimationManager::removePoseSampler(unsigned int layer, AnimPoseSamplerInterface& item) {
    m_groups[layer].m_samplers.remove(&item);
}

void AnimationManager::samplePose(unsigned int layerMask) {
    for (unsigned int i = 0; i < 32; i++) {
        if (((1 << i) & layerMask) != 0) {
            mm::mtl::IntrusiveList<AnimPoseSamplerInterface>& list = m_groups[i].m_samplers;
            unsigned int count = list.m_size;
            unsigned int rest = count & 3;
            unsigned int num = count / 4;
            mm::mtl::IntrusiveList<AnimPoseSamplerInterface>::iterator it = list.begin();
            for (unsigned int k = 0; k < num; k++) {
                AnimSamplePoseJob job(4);
                job.m_samplers[0] = &*it;
                ++it;
                job.m_samplers[1] = &*it;
                ++it;
                job.m_samplers[2] = &*it;
                ++it;
                job.m_samplers[3] = &*it;
                ++it;
                m_jobQueue->push(job);
            }
            if (rest != 0) {
                AnimSamplePoseJob job(rest);
                for (unsigned int j = 0; j < rest; j++) {
                    job.m_samplers[j] = &*it;
                    ++it;
                }
                m_jobQueue->push(job);
            }
        }
    }
    m_threadPool->processAllJob(*m_jobQueue);
    m_threadPool->waitForCompletion();
}

void AnimationManager::addPoseModifier(unsigned int layer, AnimPoseModifierInterface& item) {
    m_groups[layer].m_modifiers.push_back(&item);
}

void AnimationManager::removePoseModifier(unsigned int layer, AnimPoseModifierInterface& item) {
    m_groups[layer].m_modifiers.remove(&item);
}

void AnimationManager::applyPose(unsigned int layerMask) {
    for (unsigned int i = 0; i < 32; i++) {
        if (((1 << i) & layerMask) != 0) {
            mm::mtl::IntrusiveList<AnimPoseModifierInterface>& list = m_groups[i].m_modifiers;
            unsigned int count = list.m_size;
            unsigned int rest = count & 3;
            unsigned int num = count / 4;
            mm::mtl::IntrusiveList<AnimPoseModifierInterface>::iterator it = list.begin();
            for (unsigned int k = 0; k < num; k++) {
                AnimModifyPoseJob job(4);
                job.m_modifiers[0] = &*it;
                ++it;
                job.m_modifiers[1] = &*it;
                ++it;
                job.m_modifiers[2] = &*it;
                ++it;
                job.m_modifiers[3] = &*it;
                ++it;
                m_jobQueue->push(job);
            }
            if (rest != 0) {
                AnimModifyPoseJob job(rest);
                for (unsigned int j = 0; j < rest; j++) {
                    job.m_modifiers[j] = &*it;
                    ++it;
                }
                m_jobQueue->push(job);
            }
        }
    }
    m_threadPool->processAllJob(*m_jobQueue);
    m_threadPool->waitForCompletion();
}

void AnimationManager::addAfterModifier(unsigned int layer, AnimAfterModifierInterface& item) {
    m_groups[layer].m_afterModifiers.push_back(&item);
}

void AnimationManager::removeAfterModifier(unsigned int layer, AnimAfterModifierInterface& item) {
    m_groups[layer].m_afterModifiers.remove(&item);
}

void AnimationManager::applyAfterModifyPose(unsigned int layerMask) {
    for (unsigned int i = 0; i < 32; i++) {
        if (((1 << i) & layerMask) != 0) {
            mm::mtl::IntrusiveList<AnimAfterModifierInterface>& list = m_groups[i].m_afterModifiers;
            unsigned int count = list.m_size;
            unsigned int rest = count & 3;
            unsigned int num = count / 4;
            mm::mtl::IntrusiveList<AnimAfterModifierInterface>::iterator it = list.begin();
            for (unsigned int k = 0; k < num; k++) {
                AnimAfterModifyJob job(4);
                job.m_modifiers[0] = &*it;
                ++it;
                job.m_modifiers[1] = &*it;
                ++it;
                job.m_modifiers[2] = &*it;
                ++it;
                job.m_modifiers[3] = &*it;
                ++it;
                m_jobQueue->push(job);
            }
            if (rest != 0) {
                AnimAfterModifyJob job(rest);
                for (unsigned int j = 0; j < rest; j++) {
                    job.m_modifiers[j] = &*it;
                    ++it;
                }
                m_jobQueue->push(job);
            }
        }
    }
    m_threadPool->processAllJob(*m_jobQueue);
    m_threadPool->waitForCompletion();
}

void AnimationManager::addIkResolver(unsigned int layer, IkResolver& item) {
    m_groups[layer].m_ikResolvers.push_back(&item);
}

void AnimationManager::removeIkResolver(unsigned int layer, IkResolver& item) {
    m_groups[layer].m_ikResolvers.remove(&item);
}

void AnimationManager::solveIK(const UpdateInfo& info, unsigned int layerMask) {
    for (unsigned int i = 0; i < 32; i++) {
        if (((1 << i) & layerMask) != 0) {
            mm::mtl::IntrusiveList<IkResolver>& list = m_groups[i].m_ikResolvers;
            unsigned int count = list.m_size;
            if (count != 0) {
                mm::mtl::IntrusiveList<IkResolver>::iterator it = list.begin();
                do {
                    AnimIkResolveJob job(1);
                    job.m_info = &info;
                    job.m_resolvers[0] = &*it;
                    ++it;
                    m_jobQueue->push(job);
                } while (--count != 0);
            }
        }
    }
    m_threadPool->processAllJob(*m_jobQueue);
    m_threadPool->waitForCompletion();
}

const char* AnimationManager::getName() const {
    return "AnimObjectManager";
}

void AnimationManager::update(const UpdateInfo&) {}

}  // namespace fw

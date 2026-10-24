#ifndef CLASSES_FW_ANIMATIONMANAGER_H
#define CLASSES_FW_ANIMATIONMANAGER_H

#include "classes/fw/ManagerObject.h"
#include "classes/fw/AnimControlUpdater.h"
#include "classes/fw/AnimSinglePoseSamper.h"
#include "classes/mm/mtl/PtrSingleton.h"
#include "mm/mtl/FixedArray.h"
#include "mm/mtl/IntrusiveList.h"
#include "anm/JobQueue.h"
#include "classes/fw/AnimAfterModifierInterface.h"
#include "fw/IkResolver.h"

namespace fw { class AnimControlUpdaterInterface; }
namespace fw { class AnimPoseSamplerInterface; }
namespace fw { class UpdateInfo; }
namespace anm { class ThreadPool; }

namespace fw {
// what AnimationManager::addPoseModifier keeps: its links in a group's list follow its table, as
// AnimControlUpdaterInterface's. Its virtual functions are not known yet.
class AnimPoseModifierInterface : public mm::mtl::IntrusiveListNodeBase {
public:
    virtual ~AnimPoseModifierInterface() {}
    virtual void apply() = 0;  // slot 2: AnimModifyPoseJob::exec calls it
};

// the jobs AnimationManager queues on its thread pool, up to four samplers (modifiers) or one resolver each
// (JobQueue functions 0 to 3; the field names are not the original's)
class AnimSamplePoseJob : public anm::Job {
public:
    explicit AnimSamplePoseJob(unsigned int count);
    static const char* _TYPE_NAME;  // "AnimSamplePoseJob"
    static void exec(anm::Job& job);
    AnimPoseSamplerInterface* m_samplers[4];
    unsigned int m_count;
};
class AnimModifyPoseJob : public anm::Job {
public:
    explicit AnimModifyPoseJob(unsigned int count);
    static const char* _TYPE_NAME;  // "AnimModifyPoseJob"
    static void exec(anm::Job& job);
    AnimPoseModifierInterface* m_modifiers[4];
    unsigned int m_count;
};
class AnimAfterModifyJob : public anm::Job {
public:
    explicit AnimAfterModifyJob(unsigned int count);
    static const char* _TYPE_NAME;  // "AnimAfterModifyJob"
    static void exec(anm::Job& job);
    AnimAfterModifierInterface* m_modifiers[4];
    unsigned int m_count;
};
class AnimIkResolveJob : public anm::Job {
public:
    explicit AnimIkResolveJob(unsigned int count);
    static const char* _TYPE_NAME;  // "AnimIkResolveJob"
    static void exec(anm::Job& job);
    IkResolver* m_resolvers[1];
    unsigned int m_count;
    const UpdateInfo* m_info;  // solveIK's
};

// table 0x7100B40BE8; its base at 0x10 is its singleton (its constructor and destructor inline
// PtrSingleton<fw::AnimationManager>'s)
class AnimationManager : public ::fw::ManagerObject, public ::mm::mtl::PtrSingleton< ::fw::AnimationManager> {
public:
    // per group (layer), what it runs (the names are not the original's)
    struct Group {
        mm::mtl::IntrusiveList<AnimControlUpdaterInterface> m_controls;
        mm::mtl::IntrusiveList<AnimPoseSamplerInterface> m_samplers;
        mm::mtl::IntrusiveList<AnimPoseModifierInterface> m_modifiers;
        mm::mtl::IntrusiveList<AnimAfterModifierInterface> m_afterModifiers;
        mm::mtl::IntrusiveList<IkResolver> m_ikResolvers;
    };

    AnimationManager();
    virtual ~AnimationManager();  // slot 0
    virtual const char* getName() const;  // slot 5
    virtual void update(fw::UpdateInfo const&);  // slot 8
    // the updaters and samplers it runs, by layer
    void addControlUpdater(unsigned int layer, fw::AnimControlUpdaterInterface& updater);
    void removeControlUpdater(unsigned int layer, fw::AnimControlUpdaterInterface& updater);
    void updateControls(const fw::UpdateInfo& info, unsigned int layerMask);
    void addPoseSampler(unsigned int layer, fw::AnimPoseSamplerInterface& sampler);
    void removePoseSampler(unsigned int layer, fw::AnimPoseSamplerInterface& sampler);
    void samplePose(unsigned int layerMask);
    void addPoseModifier(unsigned int layer, AnimPoseModifierInterface& modifier);
    void removePoseModifier(unsigned int layer, AnimPoseModifierInterface& modifier);
    void applyPose(unsigned int layerMask);
    void addAfterModifier(unsigned int layer, AnimAfterModifierInterface& modifier);
    void removeAfterModifier(unsigned int layer, AnimAfterModifierInterface& modifier);
    void applyAfterModifyPose(unsigned int layerMask);
    void addIkResolver(unsigned int layer, IkResolver& resolver);
    void removeIkResolver(unsigned int layer, IkResolver& resolver);
    void solveIK(const fw::UpdateInfo& info, unsigned int layerMask);

    mm::mtl::FixedArray<Group, 32> m_groups;
    // runs the managers' job queues (SensorManager's flushes hand theirs to it; the name is not the original's)
    anm::ThreadPool* m_threadPool;
    anm::JobQueue* m_jobQueue;  // the constructor's (the name is not the original's)
};
}  // namespace fw

#endif

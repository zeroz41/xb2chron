#ifndef CLASSES_FW_SENSORMANAGER_H
#define CLASSES_FW_SENSORMANAGER_H

#include "anm/JobQueue.h"
#include "classes/fw/ManagerObject.h"
#include "classes/mm/mtl/PtrSingleton.h"
#include "mm/mtl/Delegate.h"
#include "mm/mtl/FixedArray.h"
#include "mm/mtl/IntrusiveList.h"

namespace fw { class SensorManager; }
namespace fw { class UpdateInfo; }

namespace fw {
// what SensorManager's groups keep: a call its jobs make (the names are not the original's)
class SensorUpdater : public mm::mtl::IntrusiveListNodeBase {
public:
    mm::mtl::Delegate<void()> m_delegate;  // SensorUpdateJob::exec calls it
    bool m_registered;                     // the add functions set it, the remove functions clear it
};

// a job running up to two updaters (SensorManager's flushes queue one per pair)
class SensorUpdateJob : public anm::Job {
public:
    explicit SensorUpdateJob(unsigned int count);
    // runs the updaters (JobQueue function 0)
    static void exec(anm::Job& job);
    static const char* _TYPE_NAME;  // "SensorUpdateJob"

    SensorUpdater* m_updaters[2];
    unsigned int m_count;
};

// table 0x7100B42CB8; the base at 0x10 is mm::mtl::PtrSingleton<fw::SensorManager> (its constructor stores that
// table there and asserts singleton.h's get()==0)
class SensorManager : public ::fw::ManagerObject, public ::mm::mtl::PtrSingleton< ::fw::SensorManager> {
public:
    // per group, the updaters run before the game's update and after the animation's (the names are not the
    // original's)
    struct Group {
        mm::mtl::IntrusiveList<SensorUpdater> m_beforeGame;
        mm::mtl::IntrusiveList<SensorUpdater> m_afterAnimation;
    };

    SensorManager();
    virtual ~SensorManager();  // slot 0
    virtual const char* getName() const;  // slot 5
    virtual void update(fw::UpdateInfo const&);  // slot 8
    void addUpdaterBeforeGame(unsigned int group, SensorUpdater& updater);
    void removeUpdaterBeforeGame(unsigned int group, SensorUpdater& updater);
    void addUpdaterAfterAnimation(unsigned int group, SensorUpdater& updater);
    void removeUpdaterAfterAnimation(unsigned int group, SensorUpdater& updater);
    // runs the updaters of the groups whose bits groupMask sets, on AnimationManager's thread pool
    void flushBeforeGame(const fw::UpdateInfo& info, unsigned int groupMask);
    void flushAfterAnimation(const fw::UpdateInfo& info, unsigned int groupMask);

    mm::mtl::FixedArray<Group, 32> m_groups;
    anm::JobQueue* m_jobQueue;  // the constructor's (the name is not the original's)
};
}  // namespace fw

#endif

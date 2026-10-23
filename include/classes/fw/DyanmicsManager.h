#ifndef CLASSES_FW_DYANMICSMANAGER_H
#define CLASSES_FW_DYANMICSMANAGER_H

#include "classes/fw/ManagerObject.h"
#include "classes/mm/mtl/PtrSingleton.h"
#include "anm/JobQueue.h"
#include "mm/mtl/FixedArray.h"
#include "mm/mtl/IntrusiveList.h"

#include "classes/fw/DynamicsColObjUpdater.h"
#include "classes/fw/DynamicsUpdater.h"

namespace fw { class UpdateInfo; }

namespace fw {
// a job updating a collision updater (JobQueue function 0; the names of its fields are not the original's)
class DynamicsColUpdateJob : public anm::Job {
public:
    explicit DynamicsColUpdateJob(unsigned int count);
    // runs the updaters
    static void exec(anm::Job& job);
    static const char* _TYPE_NAME;  // "DynamicsColUpdateJob"

    DynamicsColObjUpdaterInterface* m_updaters[1];
    unsigned int m_count;
};

// a job updating a dynamics updater with a frame's update information (JobQueue function 1; the names of its
// fields are not the original's)
class DynamicsUpdateJob : public anm::Job {
public:
    explicit DynamicsUpdateJob(unsigned int count);
    // runs the updaters with m_info
    static void exec(anm::Job& job);
    static const char* _TYPE_NAME;  // "DynamicsUpdateJob"

    DynamicsUpdaterInterface* m_updaters[1];
    unsigned int m_count;
    const UpdateInfo* m_info;  // the constructor clears it
};

// one layer of DyanmicsManager's: the updaters updateDynamics runs and the collision updaters updateColObjects runs
// (the names of its fields are not the original's)
struct DynamicsGroup {
    mm::mtl::IntrusiveList<DynamicsUpdaterInterface> m_updaters;
    mm::mtl::IntrusiveList<DynamicsColObjUpdaterInterface> m_colUpdaters;
};

// table 0x7100B41230; its base at 0x10 is its singleton (1.0.0 names PtrSingleton<fw::DyanmicsManager>'s
// destructors)
class DyanmicsManager : public ::fw::ManagerObject, public ::mm::mtl::PtrSingleton< ::fw::DyanmicsManager> {
public:
    DyanmicsManager();
    virtual ~DyanmicsManager();  // slot 0
    virtual const char* getName() const;  // slot 5
    virtual void update(fw::UpdateInfo const&);  // slot 8
    void addUpdater(unsigned int layer, DynamicsUpdaterInterface& updater);
    void removeUpdater(unsigned int layer, DynamicsUpdaterInterface& updater);
    void addColUpdater(unsigned int layer, DynamicsColObjUpdaterInterface& updater);
    void removeColUpdater(unsigned int layer, DynamicsColObjUpdaterInterface& updater);
    // runs the collision updaters of the layers whose bits layerMask sets, on AnimationManager's thread pool
    void updateColObjects(unsigned int layerMask);
    // runs the updaters of the layers whose bits layerMask sets with info, on AnimationManager's thread pool
    void updateDynamics(const fw::UpdateInfo& info, unsigned int layerMask);

    mm::mtl::FixedArray<DynamicsGroup, 32> m_groups;
    anm::JobQueue* m_jobQueue;  // the constructor's (the name is not the original's)
};
}  // namespace fw

#endif

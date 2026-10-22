#ifndef CLASSES_FW_ANIMATIONMANAGER_H
#define CLASSES_FW_ANIMATIONMANAGER_H

#include "classes/fw/ManagerObject.h"

namespace fw { class AnimControlUpdaterInterface; }
namespace fw { class AnimPoseSamplerInterface; }
namespace fw { class UpdateInfo; }
namespace anm { class ThreadPool; }

namespace fw {
// a base of fw::AnimationManager no evidence names yet
class TUnk_B40C40 {
public:
    virtual ~TUnk_B40C40();
};
// table 0x7100B40BE8; base at 0x10 unknown (TUnk_B40C40)
class AnimationManager : public ::fw::ManagerObject, public TUnk_B40C40 {
public:
    virtual ~AnimationManager();  // slot 0
    virtual const char* getName() const;  // slot 5
    virtual void update(fw::UpdateInfo const&);  // slot 8
    // the updaters and samplers it runs, by layer
    void addControlUpdater(unsigned int layer, fw::AnimControlUpdaterInterface& updater);
    void removeControlUpdater(unsigned int layer, fw::AnimControlUpdaterInterface& updater);
    void addPoseSampler(unsigned int layer, fw::AnimPoseSamplerInterface& sampler);
    void removePoseSampler(unsigned int layer, fw::AnimPoseSamplerInterface& sampler);

    unsigned char pad_18[0xF00];
    // runs the managers' job queues (SensorManager's flushes hand theirs to it; the name is not the original's)
    anm::ThreadPool* m_threadPool;
};
}  // namespace fw

#endif

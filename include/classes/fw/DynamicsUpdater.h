#ifndef CLASSES_FW_DYNAMICSUPDATER_H
#define CLASSES_FW_DYNAMICSUPDATER_H

#include "fw/Transform.h"
#include "mm/mtl/Delegate.h"
#include "mm/mtl/IntrusiveList.h"
#include "mm/mtl/IntrusivePtr.h"

namespace fw { class DynamicsDrawer; }
namespace fw { class ReferenceFrame; }
namespace fw { class UpdateInfo; }
namespace skd { class Dynamics; }

namespace fw {
// what DyanmicsManager's per-layer lists hold (addUpdater/removeUpdater take one): it carries the list's links as
// its IntrusiveListNodeBase base (DyanmicsManager::updateDynamics finds it 8 bytes before its node)
class DynamicsUpdaterInterface : public mm::mtl::IntrusiveListNodeBase {
public:
    virtual ~DynamicsUpdaterInterface() {}
    virtual void update(fw::UpdateInfo const&) = 0;
    virtual void drawDebug() = 0;
};

// table 0x7100B412C8; steps a dynamics (skd::Dynamics) with a reference frame's movement
class DynamicsUpdater : public DynamicsUpdaterInterface {
public:
    DynamicsUpdater();
    virtual ~DynamicsUpdater();  // slot 0
    virtual void update(fw::UpdateInfo const&);  // slot 2
    virtual void drawDebug();  // slot 3
    void bind(skd::Dynamics* dynamics, mm::mtl::IntrusivePtr<ReferenceFrame> frame);
    void unbind();
    void setEnableMovement(bool enable);

    skd::Dynamics* m_pDynamics;  // bind's, referenced; unbind releases it (the name is not the original's)
    mm::mtl::IntrusivePtr<ReferenceFrame> m_frame;  // bind's (the name is not the original's)
    unsigned char pad_28[0x8];
    // the frame's world transform as bind and setEnableMovement(true) last took it, and the one before (the
    // names are not the original's)
    Transform m_transform;
    Transform m_prevTransform;
    bool m_enable;  // the constructor's is true (the name is not the original's)
    bool m_enableMovement;  // setEnableMovement's (the name is not the original's)
    // update resets the dynamics and clears it while it is set (the name is not the original's)
    bool m_resetRequest;
    // GfComDynamics::setup sets it to its applyAttribute, cleanup clears it (the name is not the original's)
    mm::mtl::Delegate<void()> m_callback;
    float m_timeScale;  // update scales the frame's time step by it; the constructor's is 1 (the name is not the original's)
    unsigned char pad_9c[0x4];
    DynamicsDrawer* m_pDrawer;  // drawDebug draws with it when set (the name is not the original's)
    unsigned char pad_a8[0x8];
};
}  // namespace fw

#endif

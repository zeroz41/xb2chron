#ifndef CLASSES_FW_DYNAMICSUPDATER_H
#define CLASSES_FW_DYNAMICSUPDATER_H

#include "fw/Transform.h"
#include "mm/mtl/Delegate.h"
#include "mm/mtl/IntrusivePtr.h"

namespace fw { class ReferenceFrame; }
namespace fw { class UpdateInfo; }
namespace skd { class Dynamics; }

namespace fw {
// what DyanmicsManager's per-layer lists hold (addUpdater/removeUpdater take one)
class DynamicsUpdaterInterface {
public:
    virtual ~DynamicsUpdaterInterface() {}
    virtual void update(fw::UpdateInfo const&) = 0;
    virtual void drawDebug() = 0;

    unsigned char pad_8[0x10];  // a list node: addUpdater links it into the layer's list
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
    bool pad_72;
    // GfComDynamics::setup sets it to its applyAttribute, cleanup clears it (the name is not the original's)
    mm::mtl::Delegate<void()> m_callback;
    unsigned char pad_98[0x18];
};
}  // namespace fw

#endif

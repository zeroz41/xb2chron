#ifndef CLASSES_GF_GFCOMTRANSFORM_H
#define CLASSES_GF_GFCOMTRANSFORM_H

#include "mm/Quat.h"
#include "mm/Vec3.h"
#include "mm/mtl/RTTI.h"
#include "mm/mtl/IntrusivePtr.h"
#include "classes/fw/ReferenceFrame.h"
#include "classes/fw/TransformUpdater.h"
#include "classes/gf/GfComponent.h"
namespace fw { class Message; }
namespace fw { class MessageObject; }
namespace fw { class ReferenceFrame; }

namespace gf {
// table 0x7100B663E8; one of an object's components (slot 0), with no constructor of a base it calls
class GfComTransform : public ::gf::GfComponent {
public:
    // table 0x7100B66420
    class Listener {
    public:
        explicit Listener(GfComTransform* owner) : m_pOwner(owner) {}
        virtual void onWkStandbyLogout();  // slot 0

        GfComTransform* m_pOwner;  // the constructor's this (the name is not the original's)
    };
    // what setup builds the frames from (setup's assertion names frame_max; the other names are not the
    // original's)
    struct SetupInfo {
        mm::Vec3 position;  // m_frame's world position
        mm::Quat rotation;  // m_frame's world rotation
        unsigned int frame_max;  // the room each of the updater's frame lists gets
        bool childFrame;  // whether setup makes m_childFrame
    };

    GfComTransform();
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~GfComTransform();  // slot 1
    virtual void changeLayer(unsigned int, unsigned int);  // slot 3
    virtual bool recieveMessage(fw::MessageObject*, fw::Message&);  // slot 4
    void setup(const SetupInfo& setup_info);
    void cleanup();
    void addReferenceFrame(mm::mtl::IntrusivePtr<fw::ReferenceFrame>& frame);
    void removeReferenceFrame(mm::mtl::IntrusivePtr<fw::ReferenceFrame>& frame);
    void addAfterReferenceFrame(mm::mtl::IntrusivePtr<fw::ReferenceFrame>& frame);
    void removeAfterReferenceFrame(mm::mtl::IntrusivePtr<fw::ReferenceFrame>& frame);
    void setPosition(const mm::Vec3& position);
    const mm::Vec3& getPosition() const;
    void setRotation(const mm::Quat& rotation);
    const mm::Quat& getRotation() const;
    void syncFrame();
    // the frame that places the object: m_childFrame while it is set, else m_frame (inline: the name is not
    // the original's)
    const mm::mtl::IntrusivePtr<fw::ReferenceFrame>& getFrame() const {
        return m_childFrame.get() == nullptr ? m_frame : m_childFrame;
    }
    static mm::mtl::RTTI m_rtti;

    // the object's frame: setup makes it, getPosition and getRotation read its world transform
    mm::mtl::IntrusivePtr<fw::ReferenceFrame> m_frame;
    // setup makes it on request, a child of m_frame; used in m_frame's place while set (getFrame), and syncFrame
    // syncs its world transform
    mm::mtl::IntrusivePtr<fw::ReferenceFrame> m_childFrame;
    // linked into TransformManager's list for the object's layer from setup to cleanup (the name is not the
    // original's)
    fw::TransformUpdater m_updater;
    void* m_pViewer;  // the listener's onWkStandbyLogout clears it (as GfComIK's does its m_pViewer)
    Listener m_listener;  // (the name is not the original's)
};
}  // namespace gf

#endif

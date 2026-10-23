#ifndef CLASSES_GF_GFCOMTRANSFORM_H
#define CLASSES_GF_GFCOMTRANSFORM_H

#include "mm/mtl/RTTI.h"
#include "mm/mtl/IntrusivePtr.h"
#include "classes/fw/ReferenceFrame.h"
#include "classes/gf/GfComponent.h"
namespace fw { class Message; }
namespace fw { class MessageObject; }
namespace fw { class ReferenceFrame; }
namespace mm { class Quat; }

namespace gf {
// table 0x7100B663E8; one of an object's components (slot 0), with no constructor of a base it calls
class GfComTransform : public ::gf::GfComponent {
public:
    class Listener;
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~GfComTransform();  // slot 1
    virtual void changeLayer(unsigned int, unsigned int);  // slot 3
    virtual bool recieveMessage(fw::MessageObject*, fw::Message&);  // slot 4
    const mm::Quat& getRotation() const;
    // the frame that places the object: m_childFrame while it is set, else m_frame (inline: the name is not
    // the original's)
    const mm::Vec3& getPosition() const;
    const mm::mtl::IntrusivePtr<fw::ReferenceFrame>& getFrame() const {
        return m_childFrame.get() == nullptr ? m_frame : m_childFrame;
    }
    static mm::mtl::RTTI m_rtti;

    // the object's frame: setup makes it, getPosition and getRotation read its world transform
    mm::mtl::IntrusivePtr<fw::ReferenceFrame> m_frame;
    // setup makes it on request, a child of m_frame; used in m_frame's place while set (getFrame), and syncFrame
    // syncs its world transform
    mm::mtl::IntrusivePtr<fw::ReferenceFrame> m_childFrame;
};
}  // namespace gf

#endif

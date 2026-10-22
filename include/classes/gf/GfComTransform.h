#ifndef CLASSES_GF_GFCOMTRANSFORM_H
#define CLASSES_GF_GFCOMTRANSFORM_H

#include "mm/mtl/RTTI.h"
#include "mm/mtl/IntrusivePtr.h"
#include "classes/gf/GfComponent.h"
namespace fw { class Message; }
namespace fw { class MessageObject; }
namespace fw { class ReferenceFrame; }
namespace mm { class Quat; }

namespace gf {
// table 0x7100B663E8
class GfComTransform : public ::gf::GfComponent {
public:
    class Listener;
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~GfComTransform();  // slot 1
    virtual void changeLayer(unsigned int, unsigned int);  // slot 3
    virtual bool recieveMessage(fw::MessageObject*, fw::Message&);  // slot 4
    const mm::Quat& getRotation() const;
    static mm::mtl::RTTI m_rtti;

    // the object's frame: setup makes it, getPosition reads its world position, syncFrame syncs it
    mm::mtl::IntrusivePtr<fw::ReferenceFrame> m_frame;
    mm::mtl::IntrusivePtr<fw::ReferenceFrame> m_childFrame;  // setup makes it on request, a child of m_frame
};
}  // namespace gf

#endif

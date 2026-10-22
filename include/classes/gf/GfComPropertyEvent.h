#ifndef CLASSES_GF_GFCOMPROPERTYEVENT_H
#define CLASSES_GF_GFCOMPROPERTYEVENT_H

#include "mm/mtl/RTTI.h"
#include "classes/gf/GfComProperty.h"

namespace fw { class Message; }
namespace fw { class MessageObject; }
namespace gf { class MsgObjectGetVelocity; }

namespace gf {
// table 0x7100B661A0
class GfComPropertyEvent : public ::gf::GfComProperty {
public:
    struct SetupInfo {};
    GfComPropertyEvent();
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~GfComPropertyEvent() {}  // slot 1: inline, so its D1 slot is the base's destructor
    virtual bool recieveMessage(fw::MessageObject*, fw::Message&);  // slot 4
    void setup(const SetupInfo& info);
    void cleanup();
    void setMoveSpeed(float speed);
    void procMsgObjectGetVelocity(fw::MessageObject* sender, MsgObjectGetVelocity& msg);
    static mm::mtl::RTTI m_rtti;

    float m_moveSpeed;  // setMoveSpeed sets it; the velocity it answers is this along the object's facing
};
}  // namespace gf

#endif

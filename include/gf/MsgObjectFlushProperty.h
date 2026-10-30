#ifndef GF_MSGOBJECTFLUSHPROPERTY_H
#define GF_MSGOBJECTFLUSHPROPERTY_H

#include "fw/Message.h"

namespace gf {
// message 0x100003E (1.0.0's GfComPropertyPc::procMsgObjectFlushProperty takes a gf::MsgObjectFlushProperty):
// GfComProperty::flush sends it to its own component once it has copied the object's hit points and target to the
// character property, so a derived property fills the rest; it carries nothing
class MsgObjectFlushProperty : public ::fw::Message {
public:
    MsgObjectFlushProperty() : fw::Message(0x100003E, 0x20) {}
};
}  // namespace gf

#endif

#ifndef GF_MSGUNK_1000007_H
#define GF_MSGUNK_1000007_H

#include "fw/Message.h"

namespace gf {

// message 0x1000007 (no name for it survives, 1.0.0 inlines its constructor too): GfObjUtil::setWarpTransform
// sends it to the object before it moves the object's transform when asked to
class MsgUnk_1000007 : public ::fw::Message {
public:
    MsgUnk_1000007() : fw::Message(0x1000007, 0x40) {}
};

}  // namespace gf

#endif

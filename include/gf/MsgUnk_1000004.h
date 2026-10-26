#ifndef GF_MSGUNK_1000004_H
#define GF_MSGUNK_1000004_H

#include "fw/Message.h"

namespace gf {

// message 0x1000004 (no name for it survives, 1.0.0 sends the same): GfBdatLookAt::bdatRefresh sends it to every
// party member once it has rebuilt the look-at tables
class MsgUnk_1000004 : public ::fw::Message {
public:
    MsgUnk_1000004() : fw::Message(0x1000004, 0x40) {}
};

}  // namespace gf

#endif

#ifndef GF_MSGGAMEDEBUGTARGET_H
#define GF_MSGGAMEDEBUGTARGET_H

#include "fw/Message.h"

namespace gf {

// message 0x100002D: GfGameTarget::procMsgGameDebugTarget draws its searches for it (its contents are not known yet)
class MsgGameDebugTarget : public ::fw::Message {
public:
    static const unsigned int ID = 0x100002D;
};

}  // namespace gf

#endif

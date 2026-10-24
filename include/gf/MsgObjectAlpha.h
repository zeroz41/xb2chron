#ifndef GF_MSGOBJECTALPHA_H
#define GF_MSGOBJECTALPHA_H

#include "fw/Message.h"
#include "gf/GfAlphaProperty.h"

namespace gf {

// message 0x100003D: sets one of an object's alphas (GfComProperty::procMsgObjectAlpha takes it in 1.0.0)
class MsgObjectAlpha : public ::fw::Message {
public:
    MsgObjectAlpha(OBJ_ALPHA kind, float alpha) : ::fw::Message(0x100003D, 0x20), m_kind(kind), m_alpha(alpha) {}
    OBJ_ALPHA m_kind;
    float m_alpha;
};

}  // namespace gf

#endif

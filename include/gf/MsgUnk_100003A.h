#ifndef GF_MSGUNK_100003A_H
#define GF_MSGUNK_100003A_H

#include "fw/Message.h"
namespace gf { class MsgObjectDamage; }

namespace gf {

// message 0x100003A (no name for it survives): carries a damage (its type at 0x10 and the battle start bytes at 0x2A are
// MsgObjectDamage's fields); StateField starts a battle from it
class MsgUnk_100003A : public ::fw::Message {
public:
    const gf::MsgObjectDamage* m_damage;  // the damage (none: nothing; the name is not the original's)
};

}  // namespace gf

#endif

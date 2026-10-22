#ifndef FW_MESSAGE_H
#define FW_MESSAGE_H

namespace fw {

// what a MessageObject receives (built on the stack, no table): which message it is, and a second word whose
// meaning is not known yet (0x20 in MsgObjectDamage and 0x1000046, 0x40 in MsgObjectNotifyDead); each message
// adds its contents after them
class Message {
public:
    Message(unsigned int id, unsigned int category) : m_id(id), m_category(category) {}

    unsigned int m_id;
    unsigned int m_category;
};

}  // namespace fw

#endif

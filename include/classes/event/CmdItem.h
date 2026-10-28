#ifndef CLASSES_EVENT_CMDITEM_H
#define CLASSES_EVENT_CMDITEM_H

#include "classes/event/CmdParam.h"

namespace event { class ICmd; }
namespace event {
// table 0x7100B3FCE8
class CmdItem {
public:
    virtual ~CmdItem() {}  // slot 0
    // the command the item runs (CmdQueue::erase is passed it); the name is not the original's
    ICmd* m_cmd;  // 0x8
    // CmdQueue::push_back builds an item from the command and its parameters, the two counters zeroed
    CmdItem(ICmd* cmd, const CmdParam& param) : m_cmd(cmd), m_param(param), m_count(0), m_wait(0) {}
    CmdParam m_param;  // 0x10 (push_back copies it in; the name is not the original's)
    // CmdQueue::update compares and stores it after the command's update; the name is not the original's
    int m_count;  // 0x120
    // CmdQueue::update skips the item while it is above 0; the name is not the original's
    short m_wait;  // 0x124
};
}  // namespace event

#endif

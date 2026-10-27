#ifndef CLASSES_EVENT_CMDITEM_H
#define CLASSES_EVENT_CMDITEM_H

namespace event { class ICmd; }
namespace event {
// table 0x7100B3FCE8
class CmdItem {
public:
    virtual ~CmdItem() {}  // slot 0
    // the command the item runs (CmdQueue::erase is passed it); the name is not the original's
    ICmd* m_cmd;  // 0x8
    unsigned char pad_10[0x118];  // CmdQueue steps through its items 0x128 bytes apart
};
}  // namespace event

#endif

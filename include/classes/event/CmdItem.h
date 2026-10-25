#ifndef CLASSES_EVENT_CMDITEM_H
#define CLASSES_EVENT_CMDITEM_H

namespace event {
// table 0x7100B3FCE8
class CmdItem {
public:
    virtual ~CmdItem() {}  // slot 0
    unsigned char pad_8[0x120];  // CmdQueue steps through its items 0x128 bytes apart
};
}  // namespace event

#endif

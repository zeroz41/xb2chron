#ifndef CLASSES_FW_MESSAGEOBJECT_H
#define CLASSES_FW_MESSAGEOBJECT_H

namespace fw { class Message; }
namespace fw { class MessageObject; }

namespace fw {
// table none (its derived classes')
class MessageObject {
public:
    virtual void getRTTI() const;  // slot 0
    virtual ~MessageObject();  // slot 1
    virtual void recieveMessage(fw::MessageObject*, fw::Message&);  // slot 3
    unsigned char pad_8[0x10];  // fields: size from its derived classes
};
}  // namespace fw

#endif

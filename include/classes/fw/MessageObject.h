#ifndef CLASSES_FW_MESSAGEOBJECT_H
#define CLASSES_FW_MESSAGEOBJECT_H

#include "mm/mtl/RTTI.h"
namespace fw { class Message; }
namespace fw { class MessageObject; }

namespace fw {
// table none (its derived classes')
class MessageObject {
public:
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~MessageObject();  // slot 1
    virtual void recieveMessage(fw::MessageObject*, fw::Message&);  // slot 3
    static mm::mtl::RTTI m_rtti;
    unsigned char pad_8[0x10];  // fields: size from its derived classes
};
}  // namespace fw

#endif

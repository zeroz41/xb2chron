#ifndef CLASSES_FW_MESSAGEOBJECT_H
#define CLASSES_FW_MESSAGEOBJECT_H

#include "mm/mtl/RTTI.h"
namespace fw { class Message; }
namespace fw { class MessageObject; }
namespace fw { class PointerMap; }

namespace fw {
// table 0x7100B421C8 (unnamed in the symbols: lbl_7100B421C8)
class MessageObject {
public:
    MessageObject();  // out of line (GfGamePlayerFormation::build and GfGamePlayerCamera::build call it)
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~MessageObject();  // slot 1
    // whether the message was handled (the base's returns false; GfGamePlayerCamera's true for the one it takes)
    virtual bool recieveMessage(fw::MessageObject*, fw::Message&) { return false; }  // slot 3
    // hands msg to another object, from this one: whether it was handled (inline: the name is not the original's;
    // TargetIKPlugin::update uses the answer)
    bool sendMessage(fw::MessageObject* to, fw::Message& msg) {
        return to->recieveMessage(this, msg);
    }
    static mm::mtl::RTTI m_rtti;
    // the constructor registers the object with MessageManager: its PointerMap's id for it, and that map (the
    // destructor removes it; the names are not the original's)
    unsigned int m_registId;
    fw::PointerMap* m_pointerMap;
};
}  // namespace fw

#endif

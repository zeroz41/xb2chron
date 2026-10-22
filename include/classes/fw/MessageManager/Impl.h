#ifndef CLASSES_FW_MESSAGEMANAGER_IMPL_H
#define CLASSES_FW_MESSAGEMANAGER_IMPL_H

#include "classes/fw/MessageManager.h"
#include "classes/fw/MessageObject.h"
#include "classes/fw/PointerMap.h"
#include "classes/mm/mtl/List.h"
#include "classes/mm/mtl/ReferenceObject.h"
#include "fw/HandlePtr.h"
#include "mm/mtl/IntrusivePtr.h"

namespace fw { class Message; }
namespace fw { class MessageObject; }
namespace fw { class UpdateInfo; }

namespace fw {
// a class with no table (0xC0 bytes, the constructor's allocation): the map of the objects' handles and the
// messages queued for them. The field names are not the original's.
class MessageManager::Impl {
public:
    // table 0x7100B42148: a queued message, counted (its holders are the queue's entries); it deletes the message
    class MessageHolder : public ::mm::mtl::ReferenceObject {
    public:
        explicit MessageHolder(fw::Message* message) : m_message(message) {}
        virtual ~MessageHolder();  // slot 0

        fw::Message* m_message;  // push's
    };
    // one queued message (0x38 bytes: the list's node is 0x48)
    class MessageInfo {
    public:
        mm::mtl::IntrusivePtr<MessageHolder> m_holder;
        float m_delay;  // what is left of push's delay: update takes each frame's time step off it
        fw::HandlePtr<fw::MessageObject> m_from;  // the sender, handed to the receiver's recieveMessage
        fw::HandlePtr<fw::MessageObject> m_to;  // the receiver
        unsigned int m_id;  // push's answer
    };

    // inline, as registObject and removeObject are: 3.0.1 has no out-of-line copy of them
    explicit Impl(mm::mtl::IAllocator* allocator)
        : m_allocator(allocator), m_lastId(0), m_firstId(1), m_lastIdMax(0xFFFFFFFF), m_messages(allocator) {
        m_pointerMap.reserve(allocator, 0x600);
        m_messages.reserve(0x800);
    }
    ~Impl();
    // the queue emptied and the map's room given back (1.0.0's; inline: 3.0.1 has no out-of-line copy)
    void destroy() {
        m_messages.clear();
        m_pointerMap.destroy();
    }
    void update(fw::UpdateInfo const& info);
    // its handle from the map, kept in the object
    void registObject(fw::MessageObject* object) {
        object->m_registId = m_pointerMap.regist(object);
        object->m_pointerMap = &m_pointerMap;
    }
    // its handle back to the map
    void removeObject(fw::MessageObject* object) {
        if (object->m_registId != 0 && object->m_pointerMap != nullptr) {
            object->m_pointerMap->remove(object->m_registId);
        }
    }
    unsigned int push(fw::MessageObject* from, fw::MessageObject* to, fw::Message* msg, float delay);

    mm::mtl::IAllocator* m_allocator;  // the constructor's
    fw::PointerMap m_pointerMap;  // the objects' handles (registObject)
    // the messages' ids: the last one given and the range they run in (push wraps to the first)
    unsigned int m_lastId;
    unsigned int m_firstId;
    unsigned int m_lastIdMax;
    mm::mtl::List<MessageInfo> m_messages;  // the queue
};
}  // namespace fw

#endif

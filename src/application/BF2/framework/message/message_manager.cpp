#include "classes/fw/PointerMap.h"
#include "fw/HandlePtr.h"
#include "mm/mtl/UniquePtr.h"
#include "classes/mm/mtl/_ReslistBase.h"
#include "classes/mm/mtl/List.h"
#include "classes/fw/MessageManager.h"
#include "classes/fw/MessageManager/Impl.h"
#include "classes/fw/Framework.h"
#include "classes/fw/MessageObject.h"
#include "classes/mm/mtl/IAllocator.h"
#include "fw/Message.h"
#include "fw/UpdateInfo.h"

namespace fw {

void MessageManager::Impl::update(const UpdateInfo& info) {
    mm::mtl::List<MessageInfo>::iterator it = m_messages.begin();
    while (it != m_messages.end()) {
        MessageInfo& message = *it;
        message.m_delay -= info.m_deltaTime;
        if (message.m_delay <= 0.0f) {
            MessageObject* to = message.m_to.get();
            MessageObject* from = message.m_from.get();
            if (to != nullptr) {
                to->recieveMessage(from, *message.m_holder->m_message);
            }
            it = m_messages.erase(it);
        } else {
            ++it;
        }
    }
}

// push (0x710019094C) is 16 words off as written below: the original stores the incremented id, then branches to
// store the first id when it left the range (cmp/b.hi, cmp/b.hs, mov+str); this form folds the two tests into
// ccmp/csinc and stores the select (zkit sweep found no rewrite). Everything else in it is identical.
// unsigned int MessageManager::Impl::push(MessageObject* from, MessageObject* to, Message* msg, float delay) {
//     MessageInfo message;
// #line 210
//     message.m_holder = new (Framework::getAllocator(), 8, __FILE__, __LINE__) MessageHolder(msg);
//     if (++m_lastId > m_lastIdMax || m_lastId < m_firstId) {
//         m_lastId = m_firstId;
//     }
//     unsigned int id = m_lastId;
//     message.m_delay = delay;
//     message.m_from = from != nullptr ? HandlePtr<MessageObject>(from->m_registId, from->m_pointerMap)
//                                      : HandlePtr<MessageObject>();
//     message.m_to = to != nullptr ? HandlePtr<MessageObject>(to->m_registId, to->m_pointerMap)
//                                  : HandlePtr<MessageObject>();
//     message.m_id = id;
//     m_messages.push_back(message);
//     return id;
// }

MessageManager::MessageManager(mm::mtl::IAllocator* allocator)
#line 248
    : m_impl(new (allocator, 8, __FILE__, __LINE__) Impl(allocator)) {}

MessageManager::~MessageManager() {}

bool MessageManager::initialize() {
    return true;
}

bool MessageManager::finalize() {
    m_impl.reset();
    return true;
}

void MessageManager::update(const UpdateInfo& info) {
    if (isFinalized()) {
        return;
    }
    m_impl->update(info);
}

void MessageManager::tail(const UpdateInfo& info) {
    if (isFinalized()) {
        return;
    }
}

void MessageManager::registObject(MessageObject* object) {
    m_impl->registObject(object);
}

void MessageManager::removeObject(MessageObject* object) {
    m_impl->removeObject(object);
}

unsigned int MessageManager::push(MessageObject* from, MessageObject* to, Message* msg, float delay) {
    return m_impl->push(from, to, msg, delay);
}

const char* MessageManager::getName() const {
    return "MessageManager";
}

MessageManager::Impl::MessageHolder::~MessageHolder() {
    if (m_message != nullptr) {
        delete m_message;
        m_message = nullptr;
    }
}

MessageManager::Impl::~Impl() {
    destroy();
}

}  // namespace fw

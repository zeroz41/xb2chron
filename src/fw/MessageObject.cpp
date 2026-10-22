#include "classes/fw/MessageObject.h"
#include "classes/fw/MessageManager.h"
#include "classes/mm/mtl/PtrSingleton.h"

namespace fw {

MessageObject::MessageObject() : m_registId(0), m_pointerMap(nullptr) {
    mm::mtl::PtrSingleton<MessageManager>::get()->registObject(this);
}

MessageObject::~MessageObject() {
    mm::mtl::PtrSingleton<MessageManager>::get()->removeObject(this);
}

mm::mtl::RTTI MessageObject::m_rtti("MessageObject", nullptr, nullptr);

}  // namespace fw

#ifndef FW_MESSAGEOBJECTPOST_H
#define FW_MESSAGEOBJECTPOST_H
#include "classes/fw/MessageObject.h"
#include "classes/fw/MessageManager.h"
#include "classes/fw/Framework.h"
#include "classes/mm/mtl/IAllocator.h"

namespace fw {
// MessageObject::postMessage (declared in classes/fw/MessageObject.h; the original's body sits in
// framework/message/message_object.h, whose path and line its allocation cites)
template <typename T>
void MessageObject::postMessage(fw::MessageObject* to, const T& msg, float delay) {
    if (to != nullptr && MessageManager::sys() != nullptr) {
#line 61 "D:/Monolithsoft/BF2/prog/application/BF2\\framework/message/message_object.h"
        T* copy = new (Framework::getAllocator(), 4, __FILE__, __LINE__) T(msg);
        MessageManager::sys()->push(this, to, copy, delay);
    }
}
}  // namespace fw

#endif

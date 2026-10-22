#ifndef CLASSES_FW_MESSAGEMANAGER_H
#define CLASSES_FW_MESSAGEMANAGER_H

#include "classes/fw/ManagerObject.h"
#include "classes/mm/mtl/PtrSingleton.h"
#include "mm/mtl/UniquePtr.h"

namespace fw { class Message; }
namespace fw { class MessageManager; }
namespace fw { class MessageObject; }
namespace fw { class UpdateInfo; }
namespace mm { namespace mtl { class IAllocator; } }

namespace fw {
// table 0x7100B420C8; the base at 0x10 is mm::mtl::PtrSingleton<fw::MessageManager> (the constructor installs its
// table there and stores this in its s_instance)
class MessageManager : public ::fw::ManagerObject, public ::mm::mtl::PtrSingleton< ::fw::MessageManager> {
public:
    class Impl;  // 1.0.0's fw::MessageManager::Impl: the objects' map and the queued messages

    explicit MessageManager(mm::mtl::IAllocator* allocator);
    virtual ~MessageManager();  // slot 0
    virtual bool initialize();  // slot 2
    virtual bool finalize();  // slot 3
    virtual const char* getName() const;  // slot 5
    virtual void update(fw::UpdateInfo const& info);  // slot 8: hands out the messages whose delay ran out
    virtual void tail(fw::UpdateInfo const& info);  // slot 9
    void registObject(fw::MessageObject* object);  // MessageObject's constructor
    void removeObject(fw::MessageObject* object);  // MessageObject's destructor
    // queues msg from one object to another for delay (seconds of update time): the message's id
    unsigned int push(fw::MessageObject* from, fw::MessageObject* to, fw::Message* msg, float delay);

    mm::mtl::UniquePtr<Impl> m_impl;
};
}  // namespace fw

#endif

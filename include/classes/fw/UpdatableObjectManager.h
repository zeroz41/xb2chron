#ifndef CLASSES_FW_UPDATABLEOBJECTMANAGER_H
#define CLASSES_FW_UPDATABLEOBJECTMANAGER_H

#include "classes/fw/ManagerObject.h"
#include "classes/mm/mtl/PtrSingleton.h"
#include "fw/HandlePtr.h"
#include "mm/mtl/UniquePtr.h"

namespace fw { class ObjectEvent; }
namespace fw { class UpdateInfo; }
namespace fw { class UpdatableObject; }
namespace fw { class UpdatableObjectManager; }
namespace mm { namespace mtl { class IAllocator; } }

namespace fw {
// table 0x7100B42510; the base at 0x10 is mm::mtl::PtrSingleton<fw::UpdatableObjectManager> (the constructor
// installs its table there and stores this in its s_instance)
class UpdatableObjectManager : public ::fw::ManagerObject,
                               public ::mm::mtl::PtrSingleton< ::fw::UpdatableObjectManager> {
public:
    class Impl;  // 1.0.0's fw::UpdatableObjectManager::Impl: the groups and the pointers' map

    UpdatableObjectManager(mm::mtl::IAllocator* allocator, unsigned long count);
    virtual ~UpdatableObjectManager();  // slot 0
    virtual bool initialize();  // slot 2
    virtual bool finalize();  // slot 3
    virtual const char* getName() const;  // slot 5
    virtual void update(fw::UpdateInfo const& info, unsigned int mask);  // slot 8
    virtual void tail(fw::UpdateInfo const& info);  // slot 9
    void execEvent(fw::ObjectEvent const& event, unsigned int mask);
    // a handle for ptr from the pointers' map (the first parameter is unused)
    fw::HandlePtr<fw::UpdatableObject> registPointer(unsigned int type, const void* ptr);
    void registObject(unsigned int group, fw::UpdatableObject* object);

    mm::mtl::UniquePtr<Impl> m_impl;
};
}  // namespace fw

#endif

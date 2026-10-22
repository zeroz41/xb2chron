#ifndef CLASSES_FW_UPDATABLEOBJECTFACTORY_H
#define CLASSES_FW_UPDATABLEOBJECTFACTORY_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace fw { class UpdatableObjectFactory; }
namespace fw { class UpdatableObjectManager; }
namespace mm { namespace mtl { class IAllocator; } }

namespace fw {
// table 0x7100B42590; 0x18 bytes (UpdatableObjectManager::initialize makes it)
class UpdatableObjectFactory : public ::mm::mtl::PtrSingleton< ::fw::UpdatableObjectFactory> {
public:
    // inline: 3.0.1 has no out-of-line copy (UpdatableObjectManager::initialize holds its stores)
    UpdatableObjectFactory(mm::mtl::IAllocator* allocator, fw::UpdatableObjectManager* manager)
        : m_allocator(allocator), m_manager(manager) {}
    virtual ~UpdatableObjectFactory();  // slot 0

    // initialize's allocator and manager (the names are not the original's)
    mm::mtl::IAllocator* m_allocator;
    fw::UpdatableObjectManager* m_manager;
};
}  // namespace fw

#endif

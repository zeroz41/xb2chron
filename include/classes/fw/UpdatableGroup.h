#ifndef CLASSES_FW_UPDATABLEGROUP_H
#define CLASSES_FW_UPDATABLEGROUP_H

#include "classes/mm/mtl/List.h"

namespace fw { class ObjectEvent; }
namespace fw { class UpdateInfo; }
namespace fw { class UpdatableObject; }
namespace mm { namespace mtl { class IAllocator; } }

namespace fw {
// table 0x7100B424A0; UpdatableObjectManager::initialize makes 32 (0x60 bytes each) and registObject hands one an
// object
class UpdatableGroup {
public:
    UpdatableGroup(mm::mtl::IAllocator* allocator, unsigned int index);
    virtual ~UpdatableGroup();  // slot 0
    // updates the objects whose m_updateBit is in mask and that are not terminated
    virtual void update(fw::UpdateInfo const& info, unsigned int mask);  // slot 2
    // deletes the terminated objects
    virtual void tail(fw::UpdateInfo const& info);  // slot 3
    void execEvent(fw::ObjectEvent const& event, unsigned int mask);
    void registObject(fw::UpdatableObject* object);
    void destroyAllObject();
    // deletes the object and hands its handle back to its map (1.0.0's; 3.0.1 has no out-of-line copy)
    void destroyObject(fw::UpdatableObject* object);

    mm::mtl::List<fw::UpdatableObject*> m_objects;
    unsigned char pad_48[0x4];  // cleared by the constructor
    mm::mtl::IAllocator* m_allocator;  // the constructor's (the name is not the original's)
    // the constructor's: UpdatableObjectManager::initialize passes the group's index (the name is not the original's)
    unsigned int m_index;
};
}  // namespace fw

#endif

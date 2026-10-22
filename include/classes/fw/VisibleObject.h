#ifndef CLASSES_FW_VISIBLEOBJECT_H
#define CLASSES_FW_VISIBLEOBJECT_H

#include "classes/mm/mtl/ReferenceObject.h"
#include "mm/mtl/IntrusivePtr.h"

namespace fw { class ReferenceFrame; }
namespace mm { namespace mtl { class IAllocator; } }

namespace fw {
// table 0x7100B42298; counted (create returns it with one reference; its destructor releases m_frame)
class VisibleObject : public mm::mtl::ReferenceObject {
public:
    struct SetupInfo {
        unsigned int layer;  // create copies it to the object's layer
    };
    static VisibleObject* create(const SetupInfo& info, mm::mtl::IAllocator* allocator);
    virtual ~VisibleObject();  // slot 0
    virtual void update();  // slot 2
    void changeLayer(unsigned int layer);
    bool isRender() const;

    unsigned char pad_10[0x18];
    mm::mtl::IntrusivePtr<ReferenceFrame> m_frame;  // update places the object at its world position
    unsigned char pad_30[0x20];
};
}  // namespace fw

#endif

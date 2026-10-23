#ifndef CLASSES_FW_VISIBLEOBJECT_H
#define CLASSES_FW_VISIBLEOBJECT_H

#include "classes/fw/ModelManager.h"
#include "mm/Vec3.h"
#include "mm/mtl/IntrusivePtr.h"

namespace fw { class ReferenceFrame; }
namespace ml { class DrGpuCheckBase; }
namespace mm { namespace mtl { class IAllocator; } }

namespace fw {
// table 0x7100B42298; counted (create returns it with one reference; its destructor releases m_frame); it is
// listed in its layer's ModelManager group
class VisibleObject : public ::fw::ModelManager::Element {
public:
    struct SetupInfo {
        unsigned int layer;  // create copies it to the object's layer
    };
    // inline: 3.0.1 has no copy (1.0.0's is out of line beside create)
    VisibleObject() : m_layer(0), m_gpuCheck(nullptr), m_offset(0.0f, 0.5f, 0.0f) {}
    static VisibleObject* create(const SetupInfo& info, mm::mtl::IAllocator* allocator);
    virtual ~VisibleObject();  // slot 0
    virtual void update();  // slot 2
    void changeLayer(unsigned int layer);
    bool isRender() const;
    unsigned int m_layer;  // the ModelManager group it is listed in
    unsigned char pad_24[0x4];
    mm::mtl::IntrusivePtr<ReferenceFrame> m_frame;  // update places the object at its world position
    // the GPU visibility check create makes (ScnObjAccGpuCheck::create); the destructor releases it
    ml::DrGpuCheckBase* m_gpuCheck;
    unsigned char pad_38[0x8];
    mm::Vec3 m_offset;  // added to the frame's world position (the name is not the original's)
};
}  // namespace fw

#endif

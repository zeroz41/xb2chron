#ifndef CLASSES_FW_MODELOBJECT_H
#define CLASSES_FW_MODELOBJECT_H

#include "classes/fw/ModelManager.h"
#include "classes/fw/ReferenceFrame.h"
#include "mm/Vec3.h"
#include "mm/mtl/IntrusivePtr.h"

namespace ml { class Scn; }
namespace ml { class ScnObjModel; }
namespace mm { namespace mtl { class IAllocator; } }

namespace fw {
// table 0x7100B42270; counted: create returns it with one reference, and UIScreenObject's destructor releases it
// with reference_object.h's assertion; it is listed in its layer's ModelManager group
class ModelObject : public ::fw::ModelManager::Element {
public:
    struct ModelSetup {
        ml::Scn* scn;  // the scene the model is made in
        const void* resource;  // createMdl's resource
        const char* name;  // createMdl's name when altName is null
        const char* altName;
        int arg;  // createMdl's last argument
        unsigned char pad_24[0x2];
        bool keepScale;  // true: the model is not scaled by scale on creation (the name is not the original's)
        unsigned char pad_27[0x5];
        unsigned int layer;
        float scale;
    };
    // inline: 3.0.1 has no copy (1.0.0's is out of line beside create)
    ModelObject()
        : m_allocator(nullptr), m_scn(nullptr), m_model(nullptr), m_layer(0), m_active(true),
          m_addOffsetEnabled(false), m_addOffsetPos(0.0f, 0.0f, 0.0f), m_scale(1.0f) {}
    static ModelObject* create(mm::mtl::IAllocator* allocator, const ModelSetup& setup);
    virtual ~ModelObject();  // slot 0
    virtual void update();  // slot 2
    // 1.0.0's: clears m_addOffsetEnabled (create inlines it)
    void setup() { m_addOffsetEnabled = false; }
    ml::ScnObjModel* getInterface();
    void changeLayer(unsigned int layer);
    bool isRender() const;
    void setScale(float scale);
    mm::mtl::IAllocator* m_allocator;  // create's
    ml::Scn* m_scn;  // the setup's scene: the destructor gives m_model back to it
    ml::ScnObjModel* m_model;  // getInterface returns it
    unsigned int m_layer;  // the ModelManager group it is listed in
    bool m_active;  // 1.0.0's setActive and isActive: update moves the model only while it is set
    // update copies m_addOffsetPos to the model's offset while it is set (1.0.0's setup clears it; the name is
    // not the original's)
    bool m_addOffsetEnabled;
    unsigned char pad_3e[0x2];
    mm::mtl::IntrusivePtr<ReferenceFrame> m_frame;  // update places the model at its world matrix
    unsigned char pad_48[0x8];
    mm::Vec3 m_addOffsetPos;  // 1.0.0's setAddOffsetPos sets it
    float m_scale;  // setScale's
    unsigned char pad_64[0xc];
};
}  // namespace fw

#endif

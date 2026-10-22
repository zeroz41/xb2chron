#ifndef CLASSES_UI_UIPOLYGONOBJECT_H
#define CLASSES_UI_UIPOLYGONOBJECT_H

#include "mm/mtl/RTTI.h"
#include "mm/mtl/FixStr.h"
#include "classes/ui/UIObject.h"

namespace ui { class UILayoutObject; }
namespace ui { class UIShape; }
namespace mm { namespace mtl { class IAllocator; } }
namespace layer { class LayerBase; }
namespace ml { class ScnRenderDrCapture; }

namespace ui {
// table 0x7100B74E98; a polygon layer object drawing a shape (createShape makes it from the info)
class UIPolygonObject : public ::ui::UIObject {
public:
    // what create makes (the names are not the original's)
    struct PolygonInfo {
        unsigned int m_width;
        unsigned int m_height;
        unsigned int m_shapeType;  // 1: UIShapeSimpleFace, 2: UIShapeRing, 3: UIShapeParticle
        unsigned char pad_C[0x4];
        union {
            unsigned int m_count;  // 1: the face's corners
            struct {
                unsigned int m_division;  // 2: the ring's
                float m_weight;
            };
            struct {
                void* m_data;  // 3: the particle data
                unsigned int m_dataSize;
            };
        };
    };
    UIPolygonObject(layer::LayerBase* layer, const mm::mtl::FixStr<32>& name)
        : UIObject(layer, name, 5), m_shape(nullptr), m_textureSize(0), pad_134(0) {
        m_capture = nullptr;
    }
    virtual ~UIPolygonObject();  // slot 0
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 5
    virtual void apply();  // slot 6
    virtual unsigned int duplicateImpl(unsigned int);  // slot 9
    // a polygon object under the parent (or none) drawing the info's shape with the texture resource (or none)
    static UIPolygonObject* create(UILayoutObject* parent, const PolygonInfo& info, const void* texture,
                                   unsigned int textureSize, const mm::mtl::FixStr<32>& name,
                                   mm::mtl::IAllocator* allocator);
    // a polygon object under the parent drawing the capture's texture (1.0.0's is 0x71006E142C; 3.0.1's linker
    // drops it, duplicateImpl inlines it)
    static UIPolygonObject* create(UILayoutObject* parent, const PolygonInfo& info, ml::ScnRenderDrCapture* capture,
                                   const mm::mtl::FixStr<32>& name, mm::mtl::IAllocator* allocator);
    static UIPolygonObject* createObject(UILayoutObject* parent, const PolygonInfo& info,
                                         const mm::mtl::FixStr<32>& name, mm::mtl::IAllocator* allocator);
    static UIShape* createShape(const PolygonInfo& info, mm::mtl::IAllocator* allocator);
    static mm::mtl::RTTI m_rtti;
    UIShape* m_shape;  // the destructor deletes it
    PolygonInfo m_info;
    unsigned int m_textureSize;  // create's (duplicateImpl passes it on with the texture)
    unsigned short pad_134;  // the constructor clears it
    unsigned char pad_136[0x2];
    ml::ScnRenderDrCapture* m_capture;  // the capture it draws instead of a texture resource
};
}  // namespace ui

#endif

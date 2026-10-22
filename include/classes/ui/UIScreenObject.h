#ifndef CLASSES_UI_UISCREENOBJECT_H
#define CLASSES_UI_UISCREENOBJECT_H

#include "mm/mtl/RTTI.h"
#include "classes/ui/UIObject.h"
#include "mm/mtl/FixStr.h"

namespace mm { namespace mtl { class IAllocator; } }
namespace ml { class ScnRenderDrViewCtrl; }
namespace fw { class ModelObject; }
namespace layer { class LayerBase; }

namespace ui {
class UILayoutObject;
// table 0x7100B74EF8; a screen under a layout: a view control's texture (create) or a layer object made in memory
// (createOnMemory). The field names are not the original's.
class UIScreenObject : public ::ui::UIObject {
public:
    struct OnMemoryInfo {
        unsigned char m_modelTexture;  // 1-4: the scene's model texture (slot one less) it is drawn into; 0: none
        unsigned char m_memType;       // the layer memory type its object is made in (layer::LayerMemType)
    };
    // 1.0.0's is out of line (0x71006E1968)
    UIScreenObject(layer::LayerBase* layer, const mm::mtl::FixStr<32>& name)
        : UIObject(layer, name, 4), m_onMemory(0), m_raw(0), m_model(nullptr) {}
    virtual ~UIScreenObject();  // slot 0
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 5
    virtual unsigned int duplicateImpl(unsigned int);  // slot 9
    // a screen object, under the parent layout, drawing the view control's texture; it holds the model
    static UIScreenObject* create(UILayoutObject* parent, ml::ScnRenderDrViewCtrl* view, fw::ModelObject* model,
                                  const mm::mtl::FixStr<32>& name, mm::mtl::IAllocator* allocator);
    // a screen object, under the parent layout, whose layer object is made in memory
    static UIScreenObject* createOnMemory(UILayoutObject* parent, unsigned int width, unsigned int height,
                                          const mm::mtl::FixStr<32>& name, mm::mtl::IAllocator* allocator,
                                          const OnMemoryInfo& info);
    unsigned int getOnMemoryPixelSize() const;  // 3, 2 or 1 for memory types 1, 2 and 3; 0 otherwise
    void* getOnMemoryBuffer() const;            // the memory object's buffer (null unless made in memory)
    void swapOnMemoryBuffer();
    static mm::mtl::RTTI m_rtti;
    int m_onMemory;  // 1: made by createOnMemory; 0: by create
    unsigned char pad_10C[0x4];
    union {
        unsigned int m_viewIndex;    // create's: its view control's
        OnMemoryInfo m_onMemoryInfo; // createOnMemory's
        unsigned long m_raw;          // the constructor clears the union's 8 bytes as one store
    };
    fw::ModelObject* m_model;  // create's; the destructor releases it
};
}  // namespace ui

#endif

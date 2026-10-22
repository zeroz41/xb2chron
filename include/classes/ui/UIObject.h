#ifndef CLASSES_UI_UIOBJECT_H
#define CLASSES_UI_UIOBJECT_H

#include "mm/mtl/RTTI.h"
#include "classes/ui/UIObjectBase.h"
#include "layer/LayerAccObjBase.h"

namespace layer { class LayerBase; }
namespace ui { class UIObjectPlugin; }
namespace mm { class Vec2; }
namespace mm { template <typename> class Pnt; }
namespace mm { namespace mtl { template <int> class FixStr; } }

namespace ui {
// table 0x7100B756B8
class UIObject : public ::ui::UIObjectBase {
public:
    UIObject(layer::LayerBase* layer, const mm::mtl::FixStr<32>& name, unsigned int type);
    virtual ~UIObject();  // slot 0
    virtual void update();  // slot 2
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 5
    virtual void apply();  // slot 6
    virtual void getDisplayOffset(unsigned short, mm::Pnt<short>&) const;  // slot 7
    virtual void getTransformPosOffs(mm::Vec2&);  // slot 8
    // slot 9; a handle: UIPolygonObject's returns one, UIScreenObject's 0
    virtual unsigned int duplicateImpl(unsigned int) = 0;
    void attachPlugin(UIObjectPlugin* plugin);
    void setPos(const mm::Pnt<short>& pos);
    void setPosCenter(const mm::Pnt<short>& pos);
    static void importTransform(UITransform& transform, layer::LayerBase* layer);
    static void importDisplayInfo(UIDisplayInfo& info, layer::LayerBase* layer);
    static mm::mtl::RTTI m_rtti;
    layer::LayerBase* m_layer;  // the constructor's; its display information comes from it
    layer::LayerAccObjBase m_layerAcc;  // the constructor's, on m_layer
    unsigned short m_type;      // the constructor's (3: placed from a layout's position, without a layer object)
    unsigned char pad_DA[0x2E];  // the constructor's fields up to 0x108
};
}  // namespace ui

#endif

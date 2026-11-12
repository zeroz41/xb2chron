#ifndef CLASSES_UI_UIOBJECT_H
#define CLASSES_UI_UIOBJECT_H

#include "mm/mtl/RTTI.h"
#include "classes/ui/UIObjectBase.h"
#include "layer/LayerAccObjBase.h"
#include "mm/Vec2.h"
#include "mm/mtl/IntrusiveList.h"
#include "classes/ui/UIObjectParam.h"

namespace layer { class LayerBase; }
namespace ui { class UIObjectPlugin; }
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
    // slot 8; inline: its one copy is UIImageObject's unit's (1.0.0's too), next to that class's getRTTI
    virtual void getTransformPosOffs(mm::Vec2& offs) { offs = mm::Vec2(0.0f, 0.0f); }
    // slot 9; a handle: UIPolygonObject's returns one, UIScreenObject's 0
    virtual unsigned int duplicateImpl(unsigned int) = 0;
    void attachPlugin(UIObjectPlugin* plugin);
    void updatePlugin();
    void registAdditionalParam(UIObjectParam* param);
    void switchDisplayMode(unsigned short mode);
    void setBlendType(unsigned short type);
    void getPos(mm::Pnt<short>& pos) const;
    void getPosCenter(mm::Pnt<short>& pos) const;
    bool isDebugDraw() const;
    void setAddColor(const mm::Col3& color);
    void setPriority(unsigned short priority);
    void setPos(const mm::Pnt<short>& pos);
    void setPosCenter(const mm::Pnt<short>& pos);
    void setParent(unsigned int handle);
    UIObject* getParentPtr() const;  // the object its parent handle names (none for 0)
    void resetDirty();  // clears its transform's and display information's changed flags
    // its layer object's position, scale and rotation from its transform (the parameter is not read)
    void applyTransform(const UIObjectParam::AdditionalParam& param);
    unsigned int duplicate(unsigned int parent);  // a copy under the parent's handle (its handle; 0 when it fails)
    static void importTransform(UITransform& transform, layer::LayerBase* layer);
    static void importDisplaySize(UIDisplayInfo& info, layer::LayerBase* layer);
    static void importDisplayInfo(UIDisplayInfo& info, layer::LayerBase* layer);
    static mm::mtl::RTTI m_rtti;
    layer::LayerBase* m_layer;  // the constructor's; its display information comes from it
    layer::LayerAccObjBase m_layerAcc;  // the constructor's, on m_layer
    // the constructor's (3: placed from a layout's position, without a layer object); the derived constructors pass
    // their kind: 1 UITextObject, 2 UIImageObject, 3 UILayoutObject, 4 UIScreenObject, 5 UIPolygonObject
    unsigned short m_type;
    // the index duplicate gives its next copy (0 from the constructor; it wraps after 998; the name is not the
    // original's)
    unsigned short m_duplicateCount;
    unsigned int m_parent;      // its parent's handle (setParent's; 0: none)
    UIObjectPlugin* m_plugins;  // the last plugin attachPlugin gave it, each linking the one before (m_next)
    unsigned int m_handle;  // its handle (UIPolygonObject::apply hands it to its shape's update)
    unsigned int m_nameHash;  // mm::mtl::hashStrCrc of m_name (the constructor's; the name is not the original's)
    // its parameters (registAdditionalParam links them; the destructor clears each one's handle; the name is not
    // the original's)
    mm::mtl::IntrusiveList<UIObjectParam> m_params;
};
}  // namespace ui

#include "classes/ui/UIObjectAcc.h"

inline ui::UIObjectAcc::UIObjectAcc(UIObject* object) : m_object(object), m_handle(object->m_handle) {}

#endif

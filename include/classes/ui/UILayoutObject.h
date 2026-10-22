#ifndef CLASSES_UI_UILAYOUTOBJECT_H
#define CLASSES_UI_UILAYOUTOBJECT_H

#include "mm/mtl/RTTI.h"
#include "mm/Pnt.h"
#include "classes/ui/UIObject.h"

namespace mm { template <typename> class Rect; }
namespace mm { namespace mtl { class IAllocator; } }
namespace layer { class LayerBase; }
namespace ui { class UIObjectList; }
namespace ui { class UILayoutData; }

namespace ui {
// table 0x7100B74E38; a layout layer object holding its children in a UIObjectList
class UILayoutObject : public ::ui::UIObject {
public:
    // 1.0.0's is out of line (0x71006E046C); 3.0.1's create inlines it
    UILayoutObject(layer::LayerBase* layer, const mm::mtl::FixStr<32>& name);
    virtual ~UILayoutObject();  // slot 0
    virtual void update();  // slot 2
    virtual void setInitialize();  // slot 3
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 5
    virtual void apply();  // slot 6
    virtual void getDisplayOffset(unsigned short, mm::Pnt<short>&) const;  // slot 7
    virtual unsigned int duplicateImpl(unsigned int);  // slot 9
    // a layout object under the parent (or none); with a priority table when asked
    static UILayoutObject* create(UILayoutObject* parent, const mm::mtl::FixStr<32>& name, bool priorityTable,
                                  mm::mtl::IAllocator* allocator);
    // the child's handle in its list (0 when it does not take it); on success sets the child's parent
    unsigned int addChild(unsigned int handle, UIObject* child);
    unsigned int countChild(const char* name, unsigned int) const;  // in its list and its layouts' lists
    unsigned int searchChild(const char* name) const;  // its child's handle, or a child layout's child's
    unsigned int searchDuplicatedChild(const char* name, unsigned short) const;
    void setViewport(const mm::Rect<short>& rect);
    void setLayoutData(UILayoutData* data);  // it holds a reference to it
    void setLayoutData(UILayoutObject* other);  // the other's, referenced
    bool isTermWithChild() const;  // terminated, and so is every child (when it has a list)
    void reloadText();
    void updateSize();  // its size and offset from its children's rectangles
    static mm::mtl::RTTI m_rtti;
    UIObjectList* m_list;  // the constructor's; the destructor deletes it
    UILayoutData* m_layoutData;  // setLayoutData's; the destructor releases it
    // updateSize's: the top left of its children's rectangles less its scaling's share of its size
    // (getDisplayOffset's; the name is not the original's)
    mm::Pnt<short> m_offset;
    unsigned char pad_11C[0x4];
};
}  // namespace ui

#endif

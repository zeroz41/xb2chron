#ifndef CLASSES_UI_UISCREENOBJECT_H
#define CLASSES_UI_UISCREENOBJECT_H

#include "mm/mtl/RTTI.h"
#include "classes/ui/UIObject.h"
#include "mm/mtl/FixStr.h"

namespace mm { namespace mtl { class IAllocator; } }

namespace ui {
class UILayoutObject;
// table 0x7100B74EF8
class UIScreenObject : public ::ui::UIObject {
public:
    struct OnMemoryInfo;  // the second byte is the layer memory type its object is made in
    virtual ~UIScreenObject();  // slot 0
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 5
    virtual void duplicateImpl(unsigned int);  // slot 9
    // a screen object, under the parent layout, whose layer object is made in memory
    static UIScreenObject* createOnMemory(UILayoutObject* parent, unsigned int width, unsigned int height,
                                          const mm::mtl::FixStr<32>& name, mm::mtl::IAllocator* allocator,
                                          const OnMemoryInfo& info);
    static mm::mtl::RTTI m_rtti;
};
}  // namespace ui

#endif

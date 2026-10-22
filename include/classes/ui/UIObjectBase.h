#ifndef CLASSES_UI_UIOBJECTBASE_H
#define CLASSES_UI_UIOBJECTBASE_H

#include "classes/ui/UIDisplayInfo.h"
#include "classes/ui/UITransform.h"
#include "classes/mm/mtl/ReferenceObject.h"
#include "mm/mtl/FixStr.h"

namespace ui {
// table 0x7100B75738; a reference object (UIPolygonObject::duplicateImpl holds a reference to its copy while its
// parent adds it)
class UIObjectBase : public ::mm::mtl::ReferenceObject {
public:
    virtual ~UIObjectBase();  // slot 0
    virtual void update();  // slot 2
    virtual void setInitialize();  // slot 3
    virtual void setTerm();  // slot 4
    unsigned char pad_C[0x14];
    UITransform m_transform;  // the constructor builds it; UIObject::importTransform fills it from the layer
    unsigned char pad_48[0x8];
    UIDisplayInfo m_displayInfo;  // what UIObject::importDisplayInfo fills from the object's layer
    unsigned int m_flags;         // bit 3: terminated (UIObjectAcc::isTerm reads it)
    unsigned char pad_9C[0x4];
    mm::mtl::FixStr<32> m_name;  // UILayoutObject::addChild registers the child under it
    unsigned char pad_C4[0x4];
};
}  // namespace ui

#endif

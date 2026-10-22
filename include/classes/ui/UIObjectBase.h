#ifndef CLASSES_UI_UIOBJECTBASE_H
#define CLASSES_UI_UIOBJECTBASE_H

#include "classes/ui/UIDisplayInfo.h"
#include "classes/ui/UITransform.h"

namespace ui {
// table 0x7100B75738
class UIObjectBase {
public:
    virtual ~UIObjectBase();  // slot 0
    virtual void update();  // slot 2
    virtual void setInitialize();  // slot 3
    virtual void setTerm();  // slot 4
    unsigned char pad_8[0x18];
    UITransform m_transform;  // the constructor builds it; UIObject::importTransform fills it from the layer
    unsigned char pad_48[0x8];
    UIDisplayInfo m_displayInfo;  // what UIObject::importDisplayInfo fills from the object's layer
    unsigned int m_flags;         // bit 3: terminated (UIObjectAcc::isTerm reads it)
    unsigned char pad_9C[0x2C];
};
}  // namespace ui

#endif

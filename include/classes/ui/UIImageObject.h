#ifndef CLASSES_UI_UIIMAGEOBJECT_H
#define CLASSES_UI_UIIMAGEOBJECT_H

#include "classes/ui/UIObject.h"

namespace ui {
// table 0x7100B74DD0
class UIImageObject : public ::ui::UIObject {
public:
    virtual ~UIImageObject();  // slot 0
    virtual void getRTTI() const;  // slot 5
    virtual void duplicateImpl(unsigned int);  // slot 9
    virtual void changeBin(void const*);  // slot 10
};
}  // namespace ui

#endif

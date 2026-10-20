#ifndef CLASSES_UI_UISCREENOBJECT_H
#define CLASSES_UI_UISCREENOBJECT_H

#include "classes/ui/UIObject.h"

namespace ui {
// table 0x7100B74EF8
class UIScreenObject : public ::ui::UIObject {
public:
    virtual ~UIScreenObject();  // slot 0
    virtual void getRTTI() const;  // slot 5
    virtual void duplicateImpl(unsigned int);  // slot 9
};
}  // namespace ui

#endif

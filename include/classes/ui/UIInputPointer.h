#ifndef CLASSES_UI_UIINPUTPOINTER_H
#define CLASSES_UI_UIINPUTPOINTER_H

#include "classes/ui/UIInputLayer.h"

namespace ui {
// table 0x7100B74BD0
class UIInputPointer : public ::ui::UIInputLayer {
public:
    virtual ~UIInputPointer();  // slot 0
    virtual void getInputEventExt();  // slot 2
    virtual void hasEventExt() const;  // slot 3
    virtual void clearExt();  // slot 5
    virtual void castUIInputPointer();  // slot 8
    virtual void updateImpl();  // slot 9
};
}  // namespace ui

#endif

#ifndef CLASSES_UI_UIINPUTPAD_H
#define CLASSES_UI_UIINPUTPAD_H

#include "classes/ui/UIInputLayer.h"

namespace ui {
// table 0x7100B74B70
class UIInputPad : public ::ui::UIInputLayer {
public:
    virtual ~UIInputPad();  // slot 0
    virtual void getInputEventExt();  // slot 2
    virtual bool hasEventExt() const;  // slot 3
    virtual void clearExt();  // slot 5
    virtual void castUIInputPad();  // slot 6
    virtual void updateImpl();  // slot 9
};
}  // namespace ui

#endif

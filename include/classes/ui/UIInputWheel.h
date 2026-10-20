#ifndef CLASSES_UI_UIINPUTWHEEL_H
#define CLASSES_UI_UIINPUTWHEEL_H

#include "classes/ui/UIInputLayer.h"

namespace ui {
// table 0x7100B74C50
class UIInputWheel : public ::ui::UIInputLayer {
public:
    virtual ~UIInputWheel();  // slot 0
    virtual void getInputEventExt();  // slot 2
    virtual void castUIInputWheel();  // slot 7
    virtual void updateImpl();  // slot 9
};
}  // namespace ui

#endif

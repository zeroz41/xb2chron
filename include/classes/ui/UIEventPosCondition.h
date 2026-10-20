#ifndef CLASSES_UI_UIEVENTPOSCONDITION_H
#define CLASSES_UI_UIEVENTPOSCONDITION_H

#include "classes/ui/UIEventCondition.h"

namespace ui {
// table 0x7100B746D8
class UIEventPosCondition : public ::ui::UIEventCondition {
public:
    virtual ~UIEventPosCondition();  // slot 0
    virtual void update();  // slot 2
};
}  // namespace ui

#endif

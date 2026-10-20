#ifndef CLASSES_UI_UIEVENTDISPCONDITION_H
#define CLASSES_UI_UIEVENTDISPCONDITION_H

#include "classes/ui/UIEventCondition.h"

namespace ui {
// table 0x7100B74638
class UIEventDispCondition : public ::ui::UIEventCondition {
public:
    virtual ~UIEventDispCondition();  // slot 0
    virtual void update();  // slot 2
};
}  // namespace ui

#endif

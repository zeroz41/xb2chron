#ifndef CLASSES_UI_UIEVENTCONDITION_H
#define CLASSES_UI_UIEVENTCONDITION_H

namespace ui {
// table none (its derived classes')
class UIEventCondition {
public:
    virtual ~UIEventCondition();  // slot 0
    virtual void update() = 0;  // slot 2
    virtual void getArg() const;  // slot 3
};
}  // namespace ui

#endif

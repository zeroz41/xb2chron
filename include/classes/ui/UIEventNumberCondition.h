#ifndef CLASSES_UI_UIEVENTNUMBERCONDITION_H
#define CLASSES_UI_UIEVENTNUMBERCONDITION_H

namespace ui {
// table 0x7100B746A8
class UIEventNumberCondition {
public:
    virtual ~UIEventNumberCondition();  // slot 0
    virtual void update();  // slot 2
    virtual void getArg() const;  // slot 3
};
}  // namespace ui

#endif

#ifndef CLASSES_UI_UICTRLMETHOD_H
#define CLASSES_UI_UICTRLMETHOD_H

namespace ui { class UIObject; }

namespace ui {
// what a UICtrl runs on its object each frame: UICtrlMethodAlpha, UICtrlMethodPos, ... (1.0.0's execute takes a
// ui::UICtrlMethod::TimeInfo; their tables hold execute alone, no destructor)
class UICtrlMethod {
public:
    // UICtrl::update's time of the run (the field names are not the original's)
    struct TimeInfo {
        float m_time;      // UICtrl::m_time
        float m_step;      // the frame's step times UICtrl::m_speed
        float m_duration;  // UICtrl::m_duration
    };
    // rate: 0 to 1 over the run, along the method's curve
    virtual void execute(UIObject* object, float rate, const TimeInfo& info) = 0;  // slot 0
};
}  // namespace ui

#endif

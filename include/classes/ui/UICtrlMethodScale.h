#ifndef CLASSES_UI_UICTRLMETHODSCALE_H
#define CLASSES_UI_UICTRLMETHODSCALE_H

namespace ui { class UIObject; }
namespace ui { namespace UICtrlMethod { class TimeInfo; }}

namespace ui {
// table 0x7100B74520
class UICtrlMethodScale {
public:
    virtual void execute(ui::UIObject*, float, ui::UICtrlMethod::TimeInfo const&);  // slot 0
};
}  // namespace ui

#endif

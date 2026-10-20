#ifndef CLASSES_UI_UICTRLMETHODROT_H
#define CLASSES_UI_UICTRLMETHODROT_H

namespace ui { class UIObject; }
namespace ui { namespace UICtrlMethod { class TimeInfo; }}

namespace ui {
// table 0x7100B74538
class UICtrlMethodRot {
public:
    virtual void execute(ui::UIObject*, float, ui::UICtrlMethod::TimeInfo const&);  // slot 0
};
}  // namespace ui

#endif

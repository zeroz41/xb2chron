#ifndef CLASSES_UI_UICTRLSIMPLEUPDATER_H
#define CLASSES_UI_UICTRLSIMPLEUPDATER_H

#include "classes/ui/IUICtrlUpdater.h"
#include "fw/UpdateInfo.h"

namespace fw { class UpdateInfo; }

namespace ui {
// a template: 1 instances in the module (UICtrlSimple<1>, its table in gf_menu_obj_button_challenge2's unit);
// UICtrlManager runs the control it points at while it is added
template <typename T0>
class UICtrlSimpleUpdater : public ::ui::IUICtrlUpdater {
public:
    UICtrlSimpleUpdater() : m_ctrl(nullptr) {}
    virtual bool updateCtrl(fw::UpdateInfo const&);  // slot 0
    T0* m_ctrl;  // the control it runs; null while it runs none
};

// runs the control a frame; true while it is still moving (gf_menu_obj_button_challenge2's unit holds the only copy)
template <typename T0>
bool UICtrlSimpleUpdater<T0>::updateCtrl(const fw::UpdateInfo& info) {
    if (m_ctrl == nullptr) {
        return false;
    }
    m_ctrl->update(info.m_deltaTime);
    return m_ctrl->isBusy();
}
}  // namespace ui

#endif

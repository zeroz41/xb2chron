#ifndef CLASSES_UI_UICTRLSIMPLEUPDATER_H
#define CLASSES_UI_UICTRLSIMPLEUPDATER_H

#include "classes/ui/IUICtrlUpdater.h"

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
}  // namespace ui

#endif

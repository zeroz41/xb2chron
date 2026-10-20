// not proven yet: does not compile: no member named 'UICtrlSimple' in namespace 'ui'
#ifndef CLASSES_UI_UICTRLSIMPLEUPDATER_H
#define CLASSES_UI_UICTRLSIMPLEUPDATER_H

namespace fw { class UpdateInfo; }

namespace ui {
// a template: 1 instances in the module
template <typename T0>
class UICtrlSimpleUpdater {
public:
    virtual void updateCtrl(fw::UpdateInfo const&);  // slot 0
};
}  // namespace ui

#endif

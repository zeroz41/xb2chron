#ifndef CLASSES_UI_UICTRLREVOLVESELECT_H
#define CLASSES_UI_UICTRLREVOLVESELECT_H

namespace fw { class UpdateInfo; }

namespace ui {
// table 0x7100B745E8
class UICtrlRevolveSelect {
public:
    virtual ~UICtrlRevolveSelect();  // slot 0
    virtual void update(fw::UpdateInfo const&);  // slot 2
};
}  // namespace ui

#endif

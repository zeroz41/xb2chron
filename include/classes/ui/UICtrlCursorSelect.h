#ifndef CLASSES_UI_UICTRLCURSORSELECT_H
#define CLASSES_UI_UICTRLCURSORSELECT_H

namespace fw { class UpdateInfo; }

namespace ui {
// table 0x7100B74448
class UICtrlCursorSelect {
public:
    virtual ~UICtrlCursorSelect();  // slot 0
    virtual void update(fw::UpdateInfo const&);  // slot 2
};
}  // namespace ui

#endif

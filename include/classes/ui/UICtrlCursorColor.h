#ifndef CLASSES_UI_UICTRLCURSORCOLOR_H
#define CLASSES_UI_UICTRLCURSORCOLOR_H

namespace fw { class UpdateInfo; }

namespace ui {
// table 0x7100B74420
class UICtrlCursorColor {
public:
    virtual ~UICtrlCursorColor();  // slot 0
    virtual void update(fw::UpdateInfo const&);  // slot 2
};
}  // namespace ui

#endif

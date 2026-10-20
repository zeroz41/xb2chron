#ifndef CLASSES_UI_UICTRLFRAME_H
#define CLASSES_UI_UICTRLFRAME_H

namespace fw { class UpdateInfo; }

namespace ui {
// table 0x7100B74470
class UICtrlFrame {
public:
    virtual ~UICtrlFrame();  // slot 0
    virtual void update(fw::UpdateInfo const&);  // slot 2
};
}  // namespace ui

#endif

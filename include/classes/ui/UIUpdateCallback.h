#ifndef CLASSES_UI_UIUPDATECALLBACK_H
#define CLASSES_UI_UIUPDATECALLBACK_H

namespace fw { class UpdateInfo; }

namespace ui {
// table none (its derived classes')
class UIUpdateCallback {
public:
    virtual void beginUpdate(fw::UpdateInfo const&) = 0;  // slot 0
    virtual void endUpdate(fw::UpdateInfo const&);  // slot 1
    virtual void beginApply();  // slot 2
    virtual void endApply();  // slot 3
};
}  // namespace ui

#endif

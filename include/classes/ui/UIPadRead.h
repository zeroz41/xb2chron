#ifndef CLASSES_UI_UIPADREAD_H
#define CLASSES_UI_UIPADREAD_H

namespace fw { struct PadData; }

namespace ui {
// table none (its derived classes'): what ui::UIManager's constructor takes to read the controlling pad
// (GfMenuManager's constructor passes a gf::GfMenuMnagerPadRead). Its destructor is the one the derived table holds.
class UIPadRead {
public:
    virtual ~UIPadRead() {}  // slot 0
    virtual const fw::PadData& uiGetControlPad() const = 0;  // slot 2
};
}  // namespace ui

#endif

#ifndef CLASSES_UI_IUIINPUTSELECTIONCHECKER_H
#define CLASSES_UI_IUIINPUTSELECTIONCHECKER_H

namespace ui {
// what ui::UIInputLayer asks whether a selection can be chosen (1.0.0's UIInputManager::setSelectionChecker takes
// one); no table of its own in the module: its instances are gf::SelectionChecker and gf::GfMenuObjChainAttack's
// base at 0x28, whose slot 0 is isEnableSelect(unsigned int, int)
class IUIInputSelectionChecker {
public:
    // true when the layer id's selection select can be chosen (UIInputLayer::isEnableSelect passes its id)
    virtual bool isEnableSelect(unsigned int id, int select) = 0;  // slot 0
};
}  // namespace ui

#endif

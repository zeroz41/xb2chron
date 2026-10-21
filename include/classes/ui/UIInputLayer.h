#ifndef CLASSES_UI_UIINPUTLAYER_H
#define CLASSES_UI_UIINPUTLAYER_H

namespace ui {
// table 0x7100B74AD0
class UIInputLayer {
public:
    virtual ~UIInputLayer();  // slot 0
    virtual void getInputEventExt() = 0;  // slot 2
    virtual bool hasEventExt() const { return false; }  // slot 3
    virtual void clear();  // slot 4
    virtual void clearExt();  // slot 5
    virtual void castUIInputPad();  // slot 6
    virtual void castUIInputWheel();  // slot 7
    virtual void castUIInputPointer();  // slot 8
    virtual void updateImpl() = 0;  // slot 9
};
}  // namespace ui

#endif

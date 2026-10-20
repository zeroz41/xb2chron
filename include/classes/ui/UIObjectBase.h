#ifndef CLASSES_UI_UIOBJECTBASE_H
#define CLASSES_UI_UIOBJECTBASE_H

namespace ui {
// table 0x7100B75738
class UIObjectBase {
public:
    virtual ~UIObjectBase();  // slot 0
    virtual void update();  // slot 2
    virtual void setInitialize();  // slot 3
    virtual void setTerm();  // slot 4
};
}  // namespace ui

#endif

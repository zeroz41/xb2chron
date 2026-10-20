#ifndef CLASSES_UI_UIOBJECTPARAM_H
#define CLASSES_UI_UIOBJECTPARAM_H

namespace ui {
// table 0x7100B75790
class UIObjectParam {
public:
    class AdditionalParam;
    virtual ~UIObjectParam();  // slot 0
    virtual void apply(ui::UIObjectParam::AdditionalParam&) const = 0;  // slot 2
};
}  // namespace ui

#endif

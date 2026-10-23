#ifndef CLASSES_UI_UIOBJECTPARAM_H
#define CLASSES_UI_UIOBJECTPARAM_H

#include "mm/mtl/IntrusiveList.h"

namespace ui {
// table 0x7100B75790; the constructor links it into its object's list of parameters (UIObject's list at 0xF0)
class UIObjectParam : public ::mm::mtl::IntrusiveListNodeBase {
public:
    // what an object's parameters adjust as each one applies; the name of its field is not the original's
    class AdditionalParam {
    public:
        float m_alpha;  // UIObjectAlphaParam multiplies it by its own
    };
    UIObjectParam(unsigned int handle);
    virtual ~UIObjectParam();  // slot 0
    virtual void apply(ui::UIObjectParam::AdditionalParam&) const = 0;  // slot 2
    unsigned int m_handle;                  // the object's handle
};
}  // namespace ui

#endif

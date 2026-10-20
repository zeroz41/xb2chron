#ifndef CLASSES_UI_UIOBJECTALPHAPARAM_H
#define CLASSES_UI_UIOBJECTALPHAPARAM_H

#include "classes/ui/UIObjectParam.h"

namespace ui {
// table 0x7100B750B8
class UIObjectAlphaParam {
public:
    virtual ~UIObjectAlphaParam();  // slot 0
    virtual void apply(ui::UIObjectParam::AdditionalParam&) const;  // slot 2
};
}  // namespace ui

#endif

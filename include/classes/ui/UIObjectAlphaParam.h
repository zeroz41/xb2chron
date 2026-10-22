#ifndef CLASSES_UI_UIOBJECTALPHAPARAM_H
#define CLASSES_UI_UIOBJECTALPHAPARAM_H

#include "classes/ui/UIObjectParam.h"

namespace ui {
// table 0x7100B750B8; UIObjectDispPlugin's execute creates one for its object as it fades
class UIObjectAlphaParam : public ::ui::UIObjectParam {
public:
    // inline: 3.0.1 has no out-of-line copy (UIObjectDispPlugin::execute holds its stores)
    UIObjectAlphaParam(unsigned int handle) : UIObjectParam(handle) {}
    virtual ~UIObjectAlphaParam() {}  // slot 0; inline: the table's complete destructor is UIObjectParam's
    virtual void apply(ui::UIObjectParam::AdditionalParam&) const;  // slot 2
    float m_alpha;  // what apply multiplies the object's alpha by; UIObjectDispPlugin's fade sets it
};
}  // namespace ui

#endif

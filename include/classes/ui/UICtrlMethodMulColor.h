#ifndef CLASSES_UI_UICTRLMETHODMULCOLOR_H
#define CLASSES_UI_UICTRLMETHODMULCOLOR_H

#include "classes/ui/UICtrlMethod.h"
#include "mm/Col3.h"

namespace ui {
// table 0x7100B74550; the multiply colour of an object, from the one it shows to setup's (its alpha stays the shown one) (UICtrlManager holds one in each control slot; the field names are not the original's)
class UICtrlMethodMulColor : public UICtrlMethod {
public:
    void setup(const UIObject* object, const mm::Col3& color);
    virtual void execute(UIObject* object, float rate, const TimeInfo& info);  // slot 0
    mm::Col3 m_from;
    mm::Col3 m_to;
};
}  // namespace ui

#endif

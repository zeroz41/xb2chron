#ifndef CLASSES_UI_UICTRLMETHODADDCOLOR_H
#define CLASSES_UI_UICTRLMETHODADDCOLOR_H

#include "classes/ui/UICtrlMethod.h"
#include "mm/Col3.h"

namespace ui {
// table 0x7100B74568; the add colour of an object, from the one it shows to setup's (UICtrlManager holds one in each control slot; the field names are not the original's)
class UICtrlMethodAddColor : public UICtrlMethod {
public:
    void setup(const UIObject* object, const mm::Col3& color);
    virtual void execute(UIObject* object, float rate, const TimeInfo& info);  // slot 0
    mm::Col3 m_from;
    mm::Col3 m_to;
};
}  // namespace ui

#endif

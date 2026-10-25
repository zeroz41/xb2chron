#ifndef CLASSES_UI_UICTRLMETHODPOS_H
#define CLASSES_UI_UICTRLMETHODPOS_H

#include "classes/ui/UICtrlMethod.h"
#include "mm/Pnt.h"

namespace ui {
// table 0x7100B74508; the position of an object, from its current one to setup's, both kept without its display offset (UICtrlManager holds one in each control slot; the field names are not the original's)
class UICtrlMethodPos : public UICtrlMethod {
public:
    void setup(const UIObject* object, const mm::Pnt<short>& pos);
    virtual void execute(UIObject* object, float rate, const TimeInfo& info);  // slot 0
    mm::Pnt<short> m_from;
    mm::Pnt<short> m_to;
};
}  // namespace ui

#endif

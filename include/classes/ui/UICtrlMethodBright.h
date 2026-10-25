#ifndef CLASSES_UI_UICTRLMETHODBRIGHT_H
#define CLASSES_UI_UICTRLMETHODBRIGHT_H

#include "classes/ui/UICtrlMethod.h"

namespace ui {
// table 0x7100B744F0; the brightness of an object (its add colour, the same in each component), from its red to setup's (UICtrlManager holds one in each control slot; the field names are not the original's)
class UICtrlMethodBright : public UICtrlMethod {
public:
    void setup(const UIObject* object, float bright);
    virtual void execute(UIObject* object, float rate, const TimeInfo& info);  // slot 0
    float m_from;
    float m_to;
};
}  // namespace ui

#endif

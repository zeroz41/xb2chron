#ifndef CLASSES_UI_UICTRLMETHODALPHA_H
#define CLASSES_UI_UICTRLMETHODALPHA_H

#include "classes/ui/UICtrlMethod.h"

namespace ui {
// table 0x7100B744D8; the multiply colour's alpha of an object, from the one it shows (its display information's colour source) to setup's (UICtrlManager holds one in each control slot; the field names are not the original's)
class UICtrlMethodAlpha : public UICtrlMethod {
public:
    void setup(const UIObject* object, float alpha);
    virtual void execute(UIObject* object, float rate, const TimeInfo& info);  // slot 0
    float m_from;
    float m_to;
};
}  // namespace ui

#endif

#ifndef CLASSES_UI_UICTRLMETHODROT_H
#define CLASSES_UI_UICTRLMETHODROT_H

#include "classes/ui/UICtrlMethod.h"

namespace ui {
// table 0x7100B74538; the rotation of an object's transform, from its current one to setup's (UICtrlManager holds one in each control slot; the field names are not the original's)
class UICtrlMethodRot : public UICtrlMethod {
public:
    void setup(const UIObject* object, float rot);
    virtual void execute(UIObject* object, float rate, const TimeInfo& info);  // slot 0
    float m_from;
    float m_to;
};
}  // namespace ui

#endif

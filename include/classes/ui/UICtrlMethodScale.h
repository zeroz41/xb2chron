#ifndef CLASSES_UI_UICTRLMETHODSCALE_H
#define CLASSES_UI_UICTRLMETHODSCALE_H

#include "classes/ui/UICtrlMethod.h"
#include "mm/Vec2.h"

namespace ui {
// table 0x7100B74520; the scale of an object's transform, from its current one to setup's (UICtrlManager holds one in each control slot; the field names are not the original's)
class UICtrlMethodScale : public UICtrlMethod {
public:
    void setup(const UIObject* object, const mm::Vec2& scale);
    virtual void execute(UIObject* object, float rate, const TimeInfo& info);  // slot 0
    // both on 16-byte boundaries (setup and execute address them at 0x10 and 0x20; the slot array of
    // UICtrlManager, which holds one, starts at 0x10 after the table)
    alignas(16) mm::Vec2 m_from;
    alignas(16) mm::Vec2 m_to;
};
}  // namespace ui

#endif

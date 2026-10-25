#ifndef CLASSES_UI_UICTRLMETHODMOTION_H
#define CLASSES_UI_UICTRLMETHODMOTION_H

#include "classes/ui/UICtrlMethod.h"
#include "mm/Vec2.h"

namespace ui { class UIMotionData; }

namespace ui {
// table 0x7100B74580; a motion of a UIMotionData run on an object from where setup found it (UICtrlManager holds one
// in each control slot; the field names are not the original's)
class UICtrlMethodMotion : public UICtrlMethod {
public:
    void setup(const UIObject* object, const UIMotionData* data, const char* name);
    virtual void execute(UIObject* object, float rate, const TimeInfo& info);  // slot 0
    const UIMotionData* m_data;  // setup's
    int m_motion;                // the data's index of setup's name (UIMotionData::searchMotion)
    int m_frame;                 // setup zeroes it
    // on 16-byte boundaries (setup stores them at 0x20 and 0x30)
    alignas(16) mm::Vec2 m_basePos;    // the object's position without its display offset, at setup
    alignas(16) mm::Vec2 m_baseScale;  // its transform's scale at setup
};
}  // namespace ui

#endif

#ifndef CLASSES_UI_UIOBJECTDOCKPLUGIN_H
#define CLASSES_UI_UIOBJECTDOCKPLUGIN_H

#include "mm/mtl/RTTI.h"
#include "mm/Pnt.h"
#include "mm/Rect.h"
#include "classes/ui/UIObjectPlugin.h"
#include "ui/UIUtil.h"

namespace ui { class UIObjectAcc; }

namespace ui {
// table 0x7100B750E0; places its object beside another one (the target) and gives it the target's matrix. The
// field names are not the original's: they say what execute does with them.
class UIObjectDockPlugin : public ::ui::UIObjectPlugin {
public:
    // 1.0.0's is out of line (0x71006E6694); 3.0.1 has it only inside create. It asks UIUtil::isValid about the
    // target and drops the answer.
    UIObjectDockPlugin(unsigned int target)
        : m_target(target), m_offset(0, 0), m_side(0), m_align(0), m_inside(0) {
        m_area.x = 0;
        m_area.y = 0;
        m_area.w = 0;
        m_area.h = 0;
        UIUtil::isValid(target);
    }
    virtual ~UIObjectDockPlugin();  // slot 0
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 2
    virtual void execute(ui::UIObjectAcc&);  // slot 4
    virtual bool isNeedUpdate(ui::UIObjectAcc&);  // slot 5
    static UIObjectDockPlugin* create(unsigned int handle, short x, short y, unsigned int target);
    static mm::mtl::RTTI m_rtti;
    unsigned int m_target;     // the object docked to
    mm::Pnt<short> m_offset;   // create's x and y: added to the docked position (per m_align)
    int m_side;                // 0-7: left, right, above, below, then the four corners (above/below left/right)
    int m_align;               // 0: m_offset added; 1, 2: top or bottom edges lined up; 3, 4: left or right ones
    int m_inside;              // non-zero: the object goes inside the target's edge instead of outside it
    mm::Rect<short> m_area;    // when its size is positive, UIUtil::adjustRect keeps the object inside it
};
}  // namespace ui

#endif

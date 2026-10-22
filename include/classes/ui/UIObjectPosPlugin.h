#ifndef CLASSES_UI_UIOBJECTPOSPLUGIN_H
#define CLASSES_UI_UIOBJECTPOSPLUGIN_H

#include "mm/mtl/RTTI.h"
#include "mm/Pnt.h"
#include "classes/ui/UIObjectDispPlugin.h"

namespace ui { class UIObjectAcc; }

namespace ui {
// table 0x7100B75220; its constructor and execute call UIObjectDispPlugin's
class UIObjectPosPlugin : public ::ui::UIObjectDispPlugin {
public:
    UIObjectPosPlugin();
    virtual ~UIObjectPosPlugin();  // slot 0
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 2
    virtual void execute(ui::UIObjectAcc&);  // slot 4
    virtual bool isNeedUpdate(ui::UIObjectAcc&) { return true; }  // slot 5
    static UIObjectPosPlugin* create(unsigned int handle, short x, short y);
    static mm::mtl::RTTI m_rtti;
    mm::Pnt<short> m_pos;            // create's; execute centers the object on it
    bool m_screenAdjust;             // execute keeps the object on screen (UIUtil::adjustScreen) when set
    unsigned short m_adjustWidth;    // the area kept on screen, centered on the object (0 by 0: the object's
    unsigned short m_adjustHeight;   //   own rectangle grown by the margin below)
    short m_adjustMarginWidth;
    short m_adjustMarginHeight;
    int m_anchor;                    // 1-4: m_pos is the object's top, bottom, left or right edge, not its center
    bool m_screenAdjusting;  // what execute passes to UIObjectAcc::setScreenAdjusting
};
}  // namespace ui

#endif

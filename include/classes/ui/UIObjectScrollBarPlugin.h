#ifndef CLASSES_UI_UIOBJECTSCROLLBARPLUGIN_H
#define CLASSES_UI_UIOBJECTSCROLLBARPLUGIN_H

#include "mm/mtl/RTTI.h"
#include "mm/Pnt.h"
#include "mm/Vec2.h"
#include "classes/ui/UIObjectPlugin.h"

namespace ui { class UIObjectAcc; }
namespace ui { class UIListInfoBase; }

namespace ui {
// table 0x7100B75260; its object is a list's scroll bar thumb: execute shows it while the list has more rows than a
// page and moves (or scales) it along its track, a sibling object, by the list's row offset
class UIObjectScrollBarPlugin : public ::ui::UIObjectPlugin {
public:
    UIObjectScrollBarPlugin()
        : m_listInfo(nullptr), m_track(0), m_direction(0), m_pos(0, 0), m_scaleEnable(true) {}
    virtual ~UIObjectScrollBarPlugin();  // slot 0
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 2
    virtual void execute(ui::UIObjectAcc&);  // slot 4
    virtual bool isNeedUpdate(ui::UIObjectAcc&) { return true; }  // slot 5
    static UIObjectScrollBarPlugin* create(unsigned int handle, unsigned int direction,
                                           const UIListInfoBase* listInfo, const char* track);
    void setScaleEnable(bool enable);
    static mm::mtl::RTTI m_rtti;
    const UIListInfoBase* m_listInfo;  // create's: the list it follows
    unsigned int m_track;              // the sibling create finds by the name it is given
    unsigned int m_direction;          // create's; execute works only for 0 (GfMenuObjUtil::createVScrollBarPlugin's)
    mm::Pnt<short> m_pos;              // the object's position at create
    mm::Vec2 m_scale;                  // the object's scale at create
    bool m_scaleEnable;                // setScaleEnable: execute scales the thumb to the page's share of the rows
};
}  // namespace ui

#endif

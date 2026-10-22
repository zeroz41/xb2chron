#ifndef CLASSES_UI_UIOBJECTOFFSETPLUGIN_H
#define CLASSES_UI_UIOBJECTOFFSETPLUGIN_H

#include "mm/mtl/RTTI.h"
#include "classes/ui/UIObjectDispPlugin.h"
#include "mm/Pnt.h"

namespace ui { class UIObjectAcc; }

namespace ui {
// table 0x7100B751A0; create constructs and destroys it as a UIObjectDispPlugin
class UIObjectOffsetPlugin : public ::ui::UIObjectDispPlugin {
public:
    UIObjectOffsetPlugin() {
        m_target.x = 0;
        m_target.y = 0;
        m_limit.x = 0xFFFF;
        m_limit.y = 0xFFFF;
    }
    virtual ~UIObjectOffsetPlugin();  // slot 0
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 2
    virtual void execute(ui::UIObjectAcc&);  // slot 4
    virtual bool isNeedUpdate(ui::UIObjectAcc&) { return true; }  // slot 5
    static UIObjectOffsetPlugin* create(unsigned int handle);
    static mm::mtl::RTTI m_rtti;
    mm::Pnt<short> m_target;           // execute moves the object's center toward it
    mm::Pnt<unsigned short> m_limit;   // how far execute moves it on each axis (0: not at all on that axis)
};
}  // namespace ui

#endif

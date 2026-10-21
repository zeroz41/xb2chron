#ifndef CLASSES_UI_UIOBJECTOFFSETPLUGIN_H
#define CLASSES_UI_UIOBJECTOFFSETPLUGIN_H

#include "mm/mtl/RTTI.h"
#include "classes/ui/UIObjectPlugin.h"

namespace ui { class UIObjectAcc; }

namespace ui {
// table 0x7100B751A0
class UIObjectOffsetPlugin : public ::ui::UIObjectPlugin {
public:
    virtual ~UIObjectOffsetPlugin();  // slot 0
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 2
    virtual void execute(ui::UIObjectAcc&);  // slot 4
    virtual bool isNeedUpdate(ui::UIObjectAcc&) { return true; }  // slot 5
    static mm::mtl::RTTI m_rtti;
};
}  // namespace ui

#endif

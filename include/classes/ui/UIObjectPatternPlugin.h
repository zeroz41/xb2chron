#ifndef CLASSES_UI_UIOBJECTPATTERNPLUGIN_H
#define CLASSES_UI_UIOBJECTPATTERNPLUGIN_H

#include "mm/mtl/RTTI.h"
#include "classes/ui/UIObjectPlugin.h"

namespace ui { class UIObjectAcc; }

namespace ui {
// table 0x7100B751E0
class UIObjectPatternPlugin : public ::ui::UIObjectPlugin {
public:
    virtual ~UIObjectPatternPlugin();  // slot 0
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 2
    virtual void execute(ui::UIObjectAcc&);  // slot 4
    virtual bool isNeedUpdate(ui::UIObjectAcc&);  // slot 5
    static mm::mtl::RTTI m_rtti;
};
}  // namespace ui

#endif

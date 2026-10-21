#ifndef CLASSES_UI_UIOBJECTFITPLUGIN_H
#define CLASSES_UI_UIOBJECTFITPLUGIN_H

#include "mm/mtl/RTTI.h"
#include "classes/ui/UIObjectPlugin.h"

namespace ui { class UIObjectAcc; }

namespace ui {
// table 0x7100B75120
class UIObjectFitPlugin : public ::ui::UIObjectPlugin {
public:
    virtual ~UIObjectFitPlugin();  // slot 0
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 2
    virtual void execute(ui::UIObjectAcc&);  // slot 4
    virtual bool isNeedUpdate(ui::UIObjectAcc&);  // slot 5
    static mm::mtl::RTTI m_rtti;
};
}  // namespace ui

#endif

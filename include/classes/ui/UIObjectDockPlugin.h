#ifndef CLASSES_UI_UIOBJECTDOCKPLUGIN_H
#define CLASSES_UI_UIOBJECTDOCKPLUGIN_H

#include "classes/ui/UIObjectPlugin.h"

namespace ui { class UIObjectAcc; }

namespace ui {
// table 0x7100B750E0
class UIObjectDockPlugin : public ::ui::UIObjectPlugin {
public:
    virtual ~UIObjectDockPlugin();  // slot 0
    virtual void getRTTI() const;  // slot 2
    virtual void execute(ui::UIObjectAcc&);  // slot 4
    virtual bool isNeedUpdate(ui::UIObjectAcc&);  // slot 5
};
}  // namespace ui

#endif

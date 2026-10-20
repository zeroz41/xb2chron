#ifndef CLASSES_UI_UIOBJECTPATTERNPLUGIN_H
#define CLASSES_UI_UIOBJECTPATTERNPLUGIN_H

#include "classes/ui/UIObjectPlugin.h"

namespace ui { class UIObjectAcc; }

namespace ui {
// table 0x7100B751E0
class UIObjectPatternPlugin : public ::ui::UIObjectPlugin {
public:
    virtual ~UIObjectPatternPlugin();  // slot 0
    virtual void getRTTI() const;  // slot 2
    virtual void execute(ui::UIObjectAcc&);  // slot 4
    virtual void isNeedUpdate(ui::UIObjectAcc&);  // slot 5
};
}  // namespace ui

#endif

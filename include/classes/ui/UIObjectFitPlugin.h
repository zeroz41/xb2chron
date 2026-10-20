#ifndef CLASSES_UI_UIOBJECTFITPLUGIN_H
#define CLASSES_UI_UIOBJECTFITPLUGIN_H

#include "classes/ui/UIObjectPlugin.h"

namespace ui { class UIObjectAcc; }

namespace ui {
// table 0x7100B75120
class UIObjectFitPlugin : public ::ui::UIObjectPlugin {
public:
    virtual ~UIObjectFitPlugin();  // slot 0
    virtual void getRTTI() const;  // slot 2
    virtual void execute(ui::UIObjectAcc&);  // slot 4
    virtual void isNeedUpdate(ui::UIObjectAcc&);  // slot 5
};
}  // namespace ui

#endif

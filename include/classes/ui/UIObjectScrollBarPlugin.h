#ifndef CLASSES_UI_UIOBJECTSCROLLBARPLUGIN_H
#define CLASSES_UI_UIOBJECTSCROLLBARPLUGIN_H

#include "classes/ui/UIObjectPlugin.h"

namespace ui { class UIObjectAcc; }

namespace ui {
// table 0x7100B75260
class UIObjectScrollBarPlugin : public ::ui::UIObjectPlugin {
public:
    virtual ~UIObjectScrollBarPlugin();  // slot 0
    virtual void getRTTI() const;  // slot 2
    virtual void execute(ui::UIObjectAcc&);  // slot 4
    virtual bool isNeedUpdate(ui::UIObjectAcc&) { return true; }  // slot 5
};
}  // namespace ui

#endif

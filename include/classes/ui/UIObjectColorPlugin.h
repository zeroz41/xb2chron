#ifndef CLASSES_UI_UIOBJECTCOLORPLUGIN_H
#define CLASSES_UI_UIOBJECTCOLORPLUGIN_H

#include "classes/ui/UIObjectPlugin.h"

namespace ui { class UIObjectAcc; }

namespace ui {
// table 0x7100B75038
class UIObjectColorPlugin : public ::ui::UIObjectPlugin {
public:
    virtual ~UIObjectColorPlugin();  // slot 0
    virtual void getRTTI() const;  // slot 2
    virtual void execute(ui::UIObjectAcc&);  // slot 4
    virtual void isNeedUpdate(ui::UIObjectAcc&);  // slot 5
};
}  // namespace ui

#endif

#ifndef CLASSES_UI_UIOBJECTTIMEPLUGIN_H
#define CLASSES_UI_UIOBJECTTIMEPLUGIN_H

#include "classes/ui/UIObjectDispPlugin.h"

namespace ui { class UIObjectAcc; }

namespace ui {
// table 0x7100B75320
class UIObjectTimePlugin : public ::ui::UIObjectDispPlugin {
public:
    virtual ~UIObjectTimePlugin();  // slot 0
    virtual void getRTTI() const;  // slot 2
    virtual void reload(ui::UIObjectAcc&);  // slot 3
    virtual void execute(ui::UIObjectAcc&);  // slot 4
};
}  // namespace ui

#endif

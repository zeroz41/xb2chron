#ifndef CLASSES_UI_UIOBJECTWORLDPOSPLUGIN_H
#define CLASSES_UI_UIOBJECTWORLDPOSPLUGIN_H

#include "classes/ui/UIObjectPosPlugin.h"

namespace ui { class UIObjectAcc; }

namespace ui {
// table 0x7100B75360
class UIObjectWorldPosPlugin : public ::ui::UIObjectPosPlugin {
public:
    virtual ~UIObjectWorldPosPlugin();  // slot 0
    virtual void getRTTI() const;  // slot 2
    virtual void execute(ui::UIObjectAcc&);  // slot 4
};
}  // namespace ui

#endif

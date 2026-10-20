#ifndef CLASSES_UI_UIOBJECTPOSPLUGIN_H
#define CLASSES_UI_UIOBJECTPOSPLUGIN_H

#include "classes/ui/UIObjectDispPlugin.h"

namespace ui { class UIObjectAcc; }

namespace ui {
// table 0x7100B75220; its constructor and execute call UIObjectDispPlugin's
class UIObjectPosPlugin : public ::ui::UIObjectDispPlugin {
public:
    virtual ~UIObjectPosPlugin();  // slot 0
    virtual void getRTTI() const;  // slot 2
    virtual void execute(ui::UIObjectAcc&);  // slot 4
    virtual void isNeedUpdate(ui::UIObjectAcc&);  // slot 5
    unsigned char pad_7C[0x14];
    bool m_screenAdjusting;  // what execute passes to UIObjectAcc::setScreenAdjusting
};
}  // namespace ui

#endif

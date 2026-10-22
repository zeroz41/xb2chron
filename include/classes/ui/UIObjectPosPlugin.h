#ifndef CLASSES_UI_UIOBJECTPOSPLUGIN_H
#define CLASSES_UI_UIOBJECTPOSPLUGIN_H

#include "mm/mtl/RTTI.h"
#include "classes/ui/UIObjectDispPlugin.h"

namespace ui { class UIObjectAcc; }

namespace ui {
// table 0x7100B75220; its constructor and execute call UIObjectDispPlugin's
class UIObjectPosPlugin : public ::ui::UIObjectDispPlugin {
public:
    UIObjectPosPlugin();
    virtual ~UIObjectPosPlugin();  // slot 0
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 2
    virtual void execute(ui::UIObjectAcc&);  // slot 4
    virtual bool isNeedUpdate(ui::UIObjectAcc&) { return true; }  // slot 5
    static mm::mtl::RTTI m_rtti;
    unsigned char pad_7C[0x14];
    bool m_screenAdjusting;  // what execute passes to UIObjectAcc::setScreenAdjusting
};
}  // namespace ui

#endif

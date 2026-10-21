#ifndef CLASSES_UI_UIOBJECTDISPPLUGIN_H
#define CLASSES_UI_UIOBJECTDISPPLUGIN_H

#include "mm/mtl/RTTI.h"
#include "classes/ui/UIObjectPlugin.h"

namespace ui { class UIObjectAcc; }

namespace ui {
// table 0x7100B75078
class UIObjectDispPlugin : public ::ui::UIObjectPlugin {
public:
    virtual ~UIObjectDispPlugin();  // slot 0
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 2
    virtual void execute(ui::UIObjectAcc&);  // slot 4
    virtual bool isNeedUpdate(ui::UIObjectAcc&);  // slot 5
    static mm::mtl::RTTI m_rtti;
    bool m_dispControl;  // setDispControl
    bool m_disp;         // setDisp
    unsigned char pad_1E[0x5E];  // the constructor's fields up to 0x7C
};
}  // namespace ui

#endif

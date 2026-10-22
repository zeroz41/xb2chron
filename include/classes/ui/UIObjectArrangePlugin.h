#ifndef CLASSES_UI_UIOBJECTARRANGEPLUGIN_H
#define CLASSES_UI_UIOBJECTARRANGEPLUGIN_H

#include "mm/mtl/RTTI.h"
#include "classes/ui/UIObjectDispPlugin.h"

namespace ui { class UIObjectAcc; }

namespace ui {
// 1.0.0's table 0x71011AA678; 3.0.1 keeps only its RTTI (the linker drops the class's code and table)
class UIObjectArrangePlugin : public ::ui::UIObjectDispPlugin {
public:
    UIObjectArrangePlugin();
    virtual ~UIObjectArrangePlugin();  // slot 0
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 2
    virtual void execute(ui::UIObjectAcc&);  // slot 4
    virtual bool isNeedUpdate(ui::UIObjectAcc&) { return true; }  // slot 5
    static UIObjectArrangePlugin* create(unsigned int handle);
    static mm::mtl::RTTI m_rtti;
    bool pad_7C;  // 1.0.0's constructor sets it to 1
};
}  // namespace ui

#endif

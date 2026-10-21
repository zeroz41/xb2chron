#ifndef CLASSES_UI_UIOBJECTNUMBERPLUGIN_H
#define CLASSES_UI_UIOBJECTNUMBERPLUGIN_H

#include "mm/mtl/RTTI.h"
#include "classes/ui/UIObjectDispPlugin.h"

namespace ui { class UIObjectAcc; }

namespace ui {
// table 0x7100B75160; its destructor ends in UIObjectDispPlugin's
class UIObjectNumberPlugin : public ::ui::UIObjectDispPlugin {
public:
    virtual ~UIObjectNumberPlugin();  // slot 0
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 2
    virtual void reload(ui::UIObjectAcc&);  // slot 3
    virtual void execute(ui::UIObjectAcc&);  // slot 4
    virtual bool isNeedUpdate(ui::UIObjectAcc&);  // slot 5
    static mm::mtl::RTTI m_rtti;
    int m_number;  // setNumber
    int m_min;     // setMin
    int m_max;     // setMax
};
}  // namespace ui

#endif

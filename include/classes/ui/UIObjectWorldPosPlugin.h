#ifndef CLASSES_UI_UIOBJECTWORLDPOSPLUGIN_H
#define CLASSES_UI_UIOBJECTWORLDPOSPLUGIN_H

#include "mm/mtl/RTTI.h"
#include "classes/ui/UIObjectPosPlugin.h"

namespace ui { class UIObjectAcc; }

namespace ui {
// table 0x7100B75360
class UIObjectWorldPosPlugin : public ::ui::UIObjectPosPlugin {
public:
    virtual ~UIObjectWorldPosPlugin();  // slot 0
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 2
    virtual void execute(ui::UIObjectAcc&);  // slot 4
    static mm::mtl::RTTI m_rtti;
};
}  // namespace ui

#endif

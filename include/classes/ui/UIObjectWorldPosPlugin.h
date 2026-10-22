#ifndef CLASSES_UI_UIOBJECTWORLDPOSPLUGIN_H
#define CLASSES_UI_UIOBJECTWORLDPOSPLUGIN_H

#include "mm/mtl/RTTI.h"
#include "classes/ui/UIObjectPosPlugin.h"
#include "mm/Vec3.h"

namespace ui { class UIObjectAcc; }

namespace ui {
// table 0x7100B75360
class UIObjectWorldPosPlugin : public ::ui::UIObjectPosPlugin {
public:
    UIObjectWorldPosPlugin() : m_worldPos(0.0f, 0.0f, 0.0f) {}
    virtual ~UIObjectWorldPosPlugin();  // slot 0
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 2
    virtual void execute(ui::UIObjectAcc&);  // slot 4
    static UIObjectWorldPosPlugin* create(unsigned int handle);
    static mm::mtl::RTTI m_rtti;
    mm::Vec3 m_worldPos;  // execute puts the object there (its matrix's translation)
};
}  // namespace ui

#endif

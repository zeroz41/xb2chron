#ifndef CLASSES_UI_UIOBJECTPATTERNPLUGIN_H
#define CLASSES_UI_UIOBJECTPATTERNPLUGIN_H

#include "mm/mtl/RTTI.h"
#include "classes/ui/UIObjectDispPlugin.h"

namespace ui { class UIObjectAcc; }

namespace ui {
// table 0x7100B751E0; create constructs and destroys it as a UIObjectDispPlugin
class UIObjectPatternPlugin : public ::ui::UIObjectDispPlugin {
public:
    UIObjectPatternPlugin() : m_facePattern(0) {}
    virtual ~UIObjectPatternPlugin();  // slot 0
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 2
    virtual void execute(ui::UIObjectAcc&);  // slot 4
    virtual bool isNeedUpdate(ui::UIObjectAcc&);  // slot 5
    static UIObjectPatternPlugin* create(unsigned int handle);
    void setFacePattern(const char* name);
    static mm::mtl::RTTI m_rtti;
    unsigned int m_facePattern;  // the text face pattern's index: execute gives it to the object
};
}  // namespace ui

#endif

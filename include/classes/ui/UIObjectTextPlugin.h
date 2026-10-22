#ifndef CLASSES_UI_UIOBJECTTEXTPLUGIN_H
#define CLASSES_UI_UIOBJECTTEXTPLUGIN_H

#include "mm/mtl/RTTI.h"
#include "classes/ui/UIObjectDispPlugin.h"
#include "ui/UIStr.h"

namespace ui { class UIObjectAcc; }

namespace ui {
// table 0x7100B752E0; create constructs and destroys it as a UIObjectDispPlugin
class UIObjectTextPlugin : public ::ui::UIObjectDispPlugin {
public:
    UIObjectTextPlugin() {}
    virtual ~UIObjectTextPlugin();  // slot 0
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 2
    virtual void execute(ui::UIObjectAcc&);  // slot 4
    virtual bool isNeedUpdate(ui::UIObjectAcc&);  // slot 5
    static UIObjectTextPlugin* create(unsigned int handle);
    void setText(const UIStr& text);
    static mm::mtl::RTTI m_rtti;
    unsigned char pad_7C[0x4];
    UIStr m_text;  // setText: execute gives it to the object
};
}  // namespace ui

#endif

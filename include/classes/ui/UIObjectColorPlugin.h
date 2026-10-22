#ifndef CLASSES_UI_UIOBJECTCOLORPLUGIN_H
#define CLASSES_UI_UIOBJECTCOLORPLUGIN_H

#include "mm/mtl/RTTI.h"
#include "mm/Col3.h"
#include "classes/ui/UIObjectDispPlugin.h"

namespace ui { class UIObjectAcc; }

namespace ui {
// table 0x7100B75038; create calls UIObjectDispPlugin's constructor and execute ends in its execute
class UIObjectColorPlugin : public ::ui::UIObjectDispPlugin {
public:
    // inline: 3.0.1 has no out-of-line copy (create holds its stores)
    UIObjectColorPlugin() : m_color(1.0f, 1.0f, 1.0f), m_colorMode(0) {}
    virtual ~UIObjectColorPlugin();  // slot 0
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 2
    virtual void execute(ui::UIObjectAcc&);  // slot 4
    virtual bool isNeedUpdate(ui::UIObjectAcc&);  // slot 5
    static UIObjectColorPlugin* create(unsigned int handle);
    void setMulColor(const mm::Col3& color);
    // inline: 3.0.1 has no out-of-line copy (1.0.0's is 0x71006E5C4C); setAddColor(const char*) holds it
    void setAddColor(const mm::Col3& color) {
        m_colorMode = 1;
        if (!m_color.isEqual(color)) {
            m_color = color;
            m_updateFlags |= 1;
        }
    }
    void setMulColor(const char* name);
    void setAddColor(const char* name);
    void setColorMode(unsigned int mode);
    void setColor(const char* name);
    static mm::mtl::RTTI m_rtti;
    mm::Col3 m_color;           // what execute gives the object, as its multiplied or added colour
    unsigned int m_colorMode;   // 0: execute sets m_color as the multiplied colour, 1: as the added one
    unsigned char pad_8C[0x4];
};
}  // namespace ui

#endif

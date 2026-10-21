#ifndef CLASSES_UI_UIOBJECTPLUGIN_H
#define CLASSES_UI_UIOBJECTPLUGIN_H

#include "mm/mtl/RTTI.h"
namespace ui { class UIObjectAcc; }

namespace ui {
// table 0x7100B757B8
class UIObjectPlugin {
public:
    virtual ~UIObjectPlugin();  // slot 0
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 2
    virtual void reload(ui::UIObjectAcc&);  // slot 3
    virtual void execute(ui::UIObjectAcc&);  // slot 4
    virtual bool isNeedUpdate(ui::UIObjectAcc&);  // slot 5
    static mm::mtl::RTTI m_rtti;
    unsigned char pad_08[0x14];  // derived plugins' fields start at 0x1C, in this class's tail padding
};
}  // namespace ui

#endif

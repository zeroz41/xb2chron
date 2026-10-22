#ifndef CLASSES_UI_UIOBJECTPLUGIN_H
#define CLASSES_UI_UIOBJECTPLUGIN_H

#include "classes/mm/mtl/ReferenceObject.h"
#include "mm/mtl/RTTI.h"
namespace ui { class UIObjectAcc; }

namespace ui {
// table 0x7100B757B8; GfMenuAdapter takes a reference to its plugin and its creators release theirs
class UIObjectPlugin : public ::mm::mtl::ReferenceObject {
public:
    UIObjectPlugin();
    virtual ~UIObjectPlugin() {}  // slot 0; inline: a derived destructor calls no base one (its D1 folds into ReferenceObject's)
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 2
    virtual void reload(ui::UIObjectAcc&);  // slot 3
    virtual void execute(ui::UIObjectAcc&);  // slot 4
    virtual bool isNeedUpdate(ui::UIObjectAcc&);  // slot 5
    static mm::mtl::RTTI m_rtti;
    unsigned char pad_0C[0xC];
    // bit 0 asks for an update: the constructor sets it, the setters set it when they change something, and
    // isNeedUpdate answers true while it is set
    unsigned int m_updateFlags;
    // derived plugins' fields start at 0x1C, in this class's tail padding
};
}  // namespace ui

#endif

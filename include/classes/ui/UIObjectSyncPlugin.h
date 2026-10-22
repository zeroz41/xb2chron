#ifndef CLASSES_UI_UIOBJECTSYNCPLUGIN_H
#define CLASSES_UI_UIOBJECTSYNCPLUGIN_H

#include "mm/mtl/RTTI.h"
#include "classes/ui/UIObjectPlugin.h"

namespace ui { class UIObjectAcc; }

namespace ui {
// table 0x7100B752A0
class UIObjectSyncPlugin : public ::ui::UIObjectPlugin {
public:
    // what execute copies from the target object (setTargetFlag)
    enum {
        SYNC_POS = 1 << 0,
        SYNC_POS_CENTER = 1 << 1,  // when SYNC_POS is not set
        SYNC_SCALE = 1 << 2,
        SYNC_ROT = 1 << 3,
        SYNC_ALPHA = 1 << 4,
        SYNC_DISP = 1 << 5,
        SYNC_DISP_INVERSE = 1 << 6,
    };
    UIObjectSyncPlugin() : m_targetObject(0), m_targetFlag(0) {}
    virtual ~UIObjectSyncPlugin();  // slot 0
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 2
    virtual void execute(ui::UIObjectAcc&);  // slot 4
    virtual bool isNeedUpdate(ui::UIObjectAcc&) { return true; }  // slot 5
    static UIObjectSyncPlugin* create(unsigned int handle);
    void setTargetObject(unsigned int handle);
    void setTargetFlag(unsigned int flag);
    static mm::mtl::RTTI m_rtti;
    unsigned int m_targetObject;  // setTargetObject: the object execute copies from
    unsigned int m_targetFlag;    // setTargetFlag: what it copies
};
}  // namespace ui

#endif

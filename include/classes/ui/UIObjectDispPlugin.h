#ifndef CLASSES_UI_UIOBJECTDISPPLUGIN_H
#define CLASSES_UI_UIOBJECTDISPPLUGIN_H

#include "mm/mtl/RTTI.h"
#include "classes/ui/UIObjectPlugin.h"

namespace ui { template <int> class UICtrlSimple; }

namespace ui { class UIObjectAcc; }

namespace ui {
// table 0x7100B75078
class UIObjectDispPlugin : public ::ui::UIObjectPlugin {
public:
    UIObjectDispPlugin();
    virtual ~UIObjectDispPlugin();  // slot 0
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 2
    virtual void execute(ui::UIObjectAcc&);  // slot 4
    virtual bool isNeedUpdate(ui::UIObjectAcc&);  // slot 5
    void init(unsigned int handle);  // takes the object's display state
    static mm::mtl::RTTI m_rtti;
    bool m_dispControl;  // setDispControl
    bool m_disp;         // setDisp
    unsigned char pad_1E[0x6];
    unsigned int m_followObjHandle;  // setFollowObjHandle
    unsigned char pad_28[0x48];
    // the fade's control while UICtrlManager runs it: setDisp sets it as it adds the updater at 0x58, and the
    // destructor removes that updater while it is set
    UICtrlSimple<1>* m_fadeCtrl;
    unsigned char pad_78[0x4];  // the constructor's fields up to 0x7C
};
}  // namespace ui

#endif

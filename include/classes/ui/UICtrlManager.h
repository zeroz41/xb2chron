#ifndef CLASSES_UI_UICTRLMANAGER_H
#define CLASSES_UI_UICTRLMANAGER_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace ui { class UICtrlManager; }
namespace ui { class IUICtrlUpdater; }
namespace ui { class UICtrlObject; }

namespace ui {
// table 0x7100B74498
class UICtrlManager : public ::mm::mtl::PtrSingleton< ::ui::UICtrlManager> {
public:
    virtual ~UICtrlManager();  // slot 0
    void addCtrlObject(UICtrlObject* object);  // takes a reference to it and runs it
    void addUpdater(IUICtrlUpdater& updater);  // links it into the updaters it runs each frame, unless linked
    void delUpdater(IUICtrlUpdater& updater);  // unlinks it, if linked
    // the object told when that control (what startCtrl returned) ends
    void changeEventHandleObject(int ctrl, unsigned int handle);
    int getCtrlSlot(unsigned int handle);  // the slot of the control running on the handle, -1 for none
    void stopCtrl(int slot, bool, bool);
    void releaseCtrlSlot(int slot);
    bool isBusyCtrl(int slot);
    void setDefault(int slot);
    void setSpeedFactor(int slot, float factor);
};
}  // namespace ui

#endif

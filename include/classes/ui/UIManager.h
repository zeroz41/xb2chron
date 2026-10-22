#ifndef CLASSES_UI_UIMANAGER_H
#define CLASSES_UI_UIMANAGER_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace ui { class UIManager; }
namespace ui { struct EventData; }

namespace ui {
// table 0x7100B75678
class UIManager : public ::mm::mtl::PtrSingleton< ::ui::UIManager> {
public:
    virtual ~UIManager();  // slot 0
    // 1.0.0's symbol (same callers): in 3.0.1 (0x710068F188) a layer id of 100 or more is DLC id / 100's
    // (MNU_Layer_Dlc%02d) and goes to an overload (0x710068F208) only while that DLC is enabled
    void createLayer(unsigned int id);
    void requestObjectEvent(unsigned int handle, const EventData& event, float delay);
};
}  // namespace ui

#endif

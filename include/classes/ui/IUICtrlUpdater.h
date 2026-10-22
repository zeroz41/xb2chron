#ifndef CLASSES_UI_IUICTRLUPDATER_H
#define CLASSES_UI_IUICTRLUPDATER_H

#include "mm/mtl/IntrusiveList.h"

namespace fw { class UpdateInfo; }

namespace ui {
// what UICtrlManager::addUpdater links into its list of updaters (delUpdater unlinks it); no destructor in the
// table of its one instance, UICtrlSimpleUpdater<UICtrlSimple<1>>
class IUICtrlUpdater {
public:
    // true while the control it runs is still moving
    virtual bool updateCtrl(const fw::UpdateInfo& info) = 0;  // slot 0
    mm::mtl::IntrusiveListNodeBase m_node;  // its link in UICtrlManager's list; linked while m_next != itself
};
}  // namespace ui

#endif

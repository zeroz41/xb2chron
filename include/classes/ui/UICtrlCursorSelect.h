#ifndef CLASSES_UI_UICTRLCURSORSELECT_H
#define CLASSES_UI_UICTRLCURSORSELECT_H

#include "classes/mm/mtl/ReferenceObject.h"

namespace fw { class UpdateInfo; }

namespace ui {
// table 0x7100B74448; counted (GfMenuObjAnnounce's destructor releases one with reference_object.h's assertion on
// the count at 0x8 and slot 1)
class UICtrlCursorSelect : public ::mm::mtl::ReferenceObject {
public:
    virtual ~UICtrlCursorSelect();  // slot 0
    virtual void update(fw::UpdateInfo const&);  // slot 2
};
}  // namespace ui

#endif

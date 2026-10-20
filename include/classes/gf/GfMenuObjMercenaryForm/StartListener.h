#ifndef CLASSES_GF_GFMENUOBJMERCENARYFORM_STARTLISTENER_H
#define CLASSES_GF_GFMENUOBJMERCENARYFORM_STARTLISTENER_H

#include "classes/gf/GfMenuObjMercenaryForm.h"

namespace ui { class EventData; }

namespace gf {
// table 0x7100B634B0
class GfMenuObjMercenaryForm::StartListener {
public:
    virtual ~StartListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}  // namespace gf

#endif

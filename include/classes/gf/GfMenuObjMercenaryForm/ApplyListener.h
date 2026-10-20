#ifndef CLASSES_GF_GFMENUOBJMERCENARYFORM_APPLYLISTENER_H
#define CLASSES_GF_GFMENUOBJMERCENARYFORM_APPLYLISTENER_H

#include "classes/gf/GfMenuObjMercenaryForm.h"

namespace ui { class EventData; }

namespace gf {
// table 0x7100B63410
class GfMenuObjMercenaryForm::ApplyListener {
public:
    virtual ~ApplyListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}  // namespace gf

#endif

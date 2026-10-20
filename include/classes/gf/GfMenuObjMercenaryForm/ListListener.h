#ifndef CLASSES_GF_GFMENUOBJMERCENARYFORM_LISTLISTENER_H
#define CLASSES_GF_GFMENUOBJMERCENARYFORM_LISTLISTENER_H

#include "classes/gf/GfMenuObjMercenaryForm.h"

namespace ui { class EventData; }

namespace gf {
// table 0x7100B63438
class GfMenuObjMercenaryForm::ListListener {
public:
    virtual ~ListListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}  // namespace gf

#endif

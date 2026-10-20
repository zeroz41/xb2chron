#ifndef CLASSES_GF_GFMENUOBJMERCENARYFORM_FORMLISTENER_H
#define CLASSES_GF_GFMENUOBJMERCENARYFORM_FORMLISTENER_H

#include "classes/gf/GfMenuObjMercenaryForm.h"

namespace ui { class EventData; }

namespace gf {
// table 0x7100B633C0
class GfMenuObjMercenaryForm::FormListener {
public:
    virtual ~FormListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}  // namespace gf

#endif

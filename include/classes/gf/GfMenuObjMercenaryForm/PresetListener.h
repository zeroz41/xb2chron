#ifndef CLASSES_GF_GFMENUOBJMERCENARYFORM_PRESETLISTENER_H
#define CLASSES_GF_GFMENUOBJMERCENARYFORM_PRESETLISTENER_H

#include "classes/gf/GfMenuObjMercenaryForm.h"

namespace ui { class EventData; }

namespace gf {
// table 0x7100B63460
class GfMenuObjMercenaryForm::PresetListener {
public:
    virtual ~PresetListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}  // namespace gf

#endif

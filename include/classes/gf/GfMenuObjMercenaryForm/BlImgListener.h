#ifndef CLASSES_GF_GFMENUOBJMERCENARYFORM_BLIMGLISTENER_H
#define CLASSES_GF_GFMENUOBJMERCENARYFORM_BLIMGLISTENER_H

#include "classes/gf/GfMenuObjMercenaryForm.h"

namespace ui { class EventData; }

namespace gf {
// table 0x7100B634D8
class GfMenuObjMercenaryForm::BlImgListener {
public:
    virtual ~BlImgListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}  // namespace gf

#endif

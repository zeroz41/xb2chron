#ifndef CLASSES_GF_GFMENUOBJMERCENARYFORM_LEADERLISTENER_H
#define CLASSES_GF_GFMENUOBJMERCENARYFORM_LEADERLISTENER_H

#include "classes/gf/GfMenuObjMercenaryForm.h"

namespace ui { class EventData; }

namespace gf {
// table 0x7100B63488
class GfMenuObjMercenaryForm::LeaderListener {
public:
    virtual ~LeaderListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}  // namespace gf

#endif

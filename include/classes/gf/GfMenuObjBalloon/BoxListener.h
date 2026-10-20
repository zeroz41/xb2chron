#ifndef CLASSES_GF_GFMENUOBJBALLOON_BOXLISTENER_H
#define CLASSES_GF_GFMENUOBJBALLOON_BOXLISTENER_H

#include "classes/gf/GfMenuObjBalloon.h"

namespace ui { class EventData; }

namespace gf {
// table 0x7100B5FBF8
class GfMenuObjBalloon::BoxListener {
public:
    virtual ~BoxListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}  // namespace gf

#endif

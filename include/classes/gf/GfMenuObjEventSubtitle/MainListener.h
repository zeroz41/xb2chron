#ifndef CLASSES_GF_GFMENUOBJEVENTSUBTITLE_MAINLISTENER_H
#define CLASSES_GF_GFMENUOBJEVENTSUBTITLE_MAINLISTENER_H

#include "classes/gf/GfMenuObjEventSubtitle.h"

namespace ui { class EventData; }

namespace gf {
// table 0x7100B62018
class GfMenuObjEventSubtitle::MainListener {
public:
    virtual ~MainListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}  // namespace gf

#endif

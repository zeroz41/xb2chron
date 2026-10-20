#ifndef CLASSES_GF_GFMENUOBJEVTHEATER_HEADERLISTENER_H
#define CLASSES_GF_GFMENUOBJEVTHEATER_HEADERLISTENER_H

#include "classes/gf/GfMenuObjEvTheater.h"

namespace ui { class EventData; }

namespace gf {
// table 0x7100B62128
class GfMenuObjEvTheater::HeaderListener {
public:
    virtual ~HeaderListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}  // namespace gf

#endif

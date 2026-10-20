#ifndef CLASSES_GF_GFMENUOBJDRARTSSET2_WPNTYPELISTENER_H
#define CLASSES_GF_GFMENUOBJDRARTSSET2_WPNTYPELISTENER_H

#include "classes/gf/GfMenuObjDrArtsSet2.h"

namespace ui { class EventData; }

namespace gf {
// table 0x7100B619E8
class GfMenuObjDrArtsSet2::WpnTypeListener {
public:
    virtual ~WpnTypeListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}  // namespace gf

#endif

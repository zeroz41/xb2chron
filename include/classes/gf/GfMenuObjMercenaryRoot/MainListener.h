#ifndef CLASSES_GF_GFMENUOBJMERCENARYROOT_MAINLISTENER_H
#define CLASSES_GF_GFMENUOBJMERCENARYROOT_MAINLISTENER_H

#include "classes/gf/GfMenuObjMercenaryRoot.h"

namespace ui { class EventData; }

namespace gf {
// table 0x7100B635E0
class GfMenuObjMercenaryRoot::MainListener {
public:
    virtual ~MainListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}  // namespace gf

#endif

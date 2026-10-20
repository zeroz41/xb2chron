#ifndef CLASSES_GF_GFMENUOBJDRKIZUNARING_MAINLISTENER_H
#define CLASSES_GF_GFMENUOBJDRKIZUNARING_MAINLISTENER_H

#include "classes/gf/GfMenuObjDrKizunaRing.h"

namespace ui { class EventData; }

namespace gf {
// table 0x7100B61B98
class GfMenuObjDrKizunaRing::MainListener {
public:
    virtual ~MainListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}  // namespace gf

#endif

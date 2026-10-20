#ifndef CLASSES_GF_GFMENUOBJSHOP_MAINLISTENER_H
#define CLASSES_GF_GFMENUOBJSHOP_MAINLISTENER_H

#include "classes/gf/GfMenuObjShop.h"

namespace ui { class EventData; }

namespace gf {
// table 0x7100B64780
class GfMenuObjShop::MainListener {
public:
    virtual ~MainListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}  // namespace gf

#endif

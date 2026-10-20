#ifndef CLASSES_GF_GFMENUOBJSHOP_ORBRECIPELISTENER_H
#define CLASSES_GF_GFMENUOBJSHOP_ORBRECIPELISTENER_H

#include "classes/gf/GfMenuObjShop.h"

namespace ui { class EventData; }

namespace gf {
// table 0x7100B64910
class GfMenuObjShop::OrbRecipeListener {
public:
    virtual ~OrbRecipeListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}  // namespace gf

#endif

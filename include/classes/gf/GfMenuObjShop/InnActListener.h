#ifndef CLASSES_GF_GFMENUOBJSHOP_INNACTLISTENER_H
#define CLASSES_GF_GFMENUOBJSHOP_INNACTLISTENER_H

#include "classes/gf/GfMenuObjShop.h"

namespace ui { class EventData; }

namespace gf {
// table 0x7100B64898
class GfMenuObjShop::InnActListener {
public:
    virtual ~InnActListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}  // namespace gf

#endif

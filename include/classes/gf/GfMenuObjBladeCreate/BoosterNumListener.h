#ifndef CLASSES_GF_GFMENUOBJBLADECREATE_BOOSTERNUMLISTENER_H
#define CLASSES_GF_GFMENUOBJBLADECREATE_BOOSTERNUMLISTENER_H

#include "classes/gf/GfMenuObjBladeCreate.h"

namespace ui { class EventData; }

namespace gf {
// table 0x7100B60188
class GfMenuObjBladeCreate::BoosterNumListener {
public:
    virtual ~BoosterNumListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}  // namespace gf

#endif

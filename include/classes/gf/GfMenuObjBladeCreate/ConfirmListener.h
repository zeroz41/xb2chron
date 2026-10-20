#ifndef CLASSES_GF_GFMENUOBJBLADECREATE_CONFIRMLISTENER_H
#define CLASSES_GF_GFMENUOBJBLADECREATE_CONFIRMLISTENER_H

#include "classes/gf/GfMenuObjBladeCreate.h"

namespace ui { class EventData; }

namespace gf {
// table 0x7100B600E8
class GfMenuObjBladeCreate::ConfirmListener {
public:
    virtual ~ConfirmListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}  // namespace gf

#endif

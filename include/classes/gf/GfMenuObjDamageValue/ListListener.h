#ifndef CLASSES_GF_GFMENUOBJDAMAGEVALUE_LISTLISTENER_H
#define CLASSES_GF_GFMENUOBJDAMAGEVALUE_LISTLISTENER_H

#include "classes/gf/GfMenuObjDamageValue.h"

namespace ui { class EventData; }

namespace gf {
// table 0x7100B61850
class GfMenuObjDamageValue::ListListener {
public:
    virtual ~ListListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}  // namespace gf

#endif

#ifndef CLASSES_GF_GFMENUOBJCOMMONTEXT_DRCHANGELISTENER_H
#define CLASSES_GF_GFMENUOBJCOMMONTEXT_DRCHANGELISTENER_H

#include "classes/gf/GfMenuObjCommonText.h"

namespace ui { class EventData; }

namespace gf {
// table 0x7100B615D8
class GfMenuObjCommonText::DrChangeListener {
public:
    virtual ~DrChangeListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}  // namespace gf

#endif

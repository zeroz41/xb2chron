#ifndef CLASSES_GF_GFMENUOBJCOMMONTEXT_OWNERCHANGELISTENER_H
#define CLASSES_GF_GFMENUOBJCOMMONTEXT_OWNERCHANGELISTENER_H

#include "classes/gf/GfMenuObjCommonText.h"

namespace ui { class EventData; }

namespace gf {
// table 0x7100B61600
class GfMenuObjCommonText::OwnerChangeListener {
public:
    virtual ~OwnerChangeListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}  // namespace gf

#endif

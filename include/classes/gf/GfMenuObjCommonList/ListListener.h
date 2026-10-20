#ifndef CLASSES_GF_GFMENUOBJCOMMONLIST_LISTLISTENER_H
#define CLASSES_GF_GFMENUOBJCOMMONLIST_LISTLISTENER_H

#include "classes/gf/GfMenuObjCommonList.h"

namespace ui { class EventData; }

namespace gf {
// table 0x7100B61450
class GfMenuObjCommonList::ListListener {
public:
    virtual ~ListListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}  // namespace gf

#endif

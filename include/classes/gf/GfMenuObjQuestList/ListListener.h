#ifndef CLASSES_GF_GFMENUOBJQUESTLIST_LISTLISTENER_H
#define CLASSES_GF_GFMENUOBJQUESTLIST_LISTLISTENER_H

#include "classes/gf/GfMenuObjQuestList.h"

namespace ui { class EventData; }

namespace gf {
// table 0x7100B64400
class GfMenuObjQuestList::ListListener {
public:
    virtual ~ListListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}  // namespace gf

#endif

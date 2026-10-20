#ifndef CLASSES_GF_GFMENUOBJQUESTLIST_TABLISTENER_H
#define CLASSES_GF_GFMENUOBJQUESTLIST_TABLISTENER_H

#include "classes/gf/GfMenuObjQuestList.h"

namespace ui { class EventData; }

namespace gf {
// table 0x7100B64388
class GfMenuObjQuestList::TabListener {
public:
    virtual ~TabListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}  // namespace gf

#endif

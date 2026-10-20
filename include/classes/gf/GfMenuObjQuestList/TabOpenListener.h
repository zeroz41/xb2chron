#ifndef CLASSES_GF_GFMENUOBJQUESTLIST_TABOPENLISTENER_H
#define CLASSES_GF_GFMENUOBJQUESTLIST_TABOPENLISTENER_H

#include "classes/gf/GfMenuObjQuestList.h"

namespace ui { class EventData; }

namespace gf {
// table 0x7100B643B0
class GfMenuObjQuestList::TabOpenListener {
public:
    virtual ~TabOpenListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}  // namespace gf

#endif

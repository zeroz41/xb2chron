#ifndef CLASSES_GF_GFMENUOBJQUESTLIST_TASKLISTENER_H
#define CLASSES_GF_GFMENUOBJQUESTLIST_TASKLISTENER_H

#include "classes/gf/GfMenuObjQuestList.h"

namespace ui { class EventData; }

namespace gf {
// table 0x7100B64478
class GfMenuObjQuestList::TaskListener {
public:
    virtual ~TaskListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}  // namespace gf

#endif

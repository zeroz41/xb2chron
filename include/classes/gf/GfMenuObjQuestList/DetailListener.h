#ifndef CLASSES_GF_GFMENUOBJQUESTLIST_DETAILLISTENER_H
#define CLASSES_GF_GFMENUOBJQUESTLIST_DETAILLISTENER_H

#include "classes/gf/GfMenuObjQuestList.h"

namespace ui { class EventData; }

namespace gf {
// table 0x7100B64450
class GfMenuObjQuestList::DetailListener {
public:
    virtual ~DetailListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}  // namespace gf

#endif

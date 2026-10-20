#ifndef CLASSES_GF_GFMENUOBJQUESTLIST_TABSELECTLISTENER_H
#define CLASSES_GF_GFMENUOBJQUESTLIST_TABSELECTLISTENER_H

#include "classes/gf/GfMenuObjQuestList.h"

namespace ui { class EventData; }

namespace gf {
// table 0x7100B643D8
class GfMenuObjQuestList::TabSelectListener {
public:
    virtual ~TabSelectListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}  // namespace gf

#endif

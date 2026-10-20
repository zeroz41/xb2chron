#ifndef CLASSES_GF_GFMENUOBJLVUPSELECT_MAINLISTENER_H
#define CLASSES_GF_GFMENUOBJLVUPSELECT_MAINLISTENER_H

#include "classes/gf/GfMenuObjLvupSelect.h"

namespace ui { class EventData; }

namespace gf {
// table 0x7100B62F40
class GfMenuObjLvupSelect::MainListener {
public:
    virtual ~MainListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}  // namespace gf

#endif

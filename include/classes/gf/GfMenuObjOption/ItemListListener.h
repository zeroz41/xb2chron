#ifndef CLASSES_GF_GFMENUOBJOPTION_ITEMLISTLISTENER_H
#define CLASSES_GF_GFMENUOBJOPTION_ITEMLISTLISTENER_H

#include "classes/gf/GfMenuObjOption.h"

namespace ui { class EventData; }

namespace gf {
// table 0x7100B63D40
class GfMenuObjOption::ItemListListener {
public:
    virtual ~ItemListListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}  // namespace gf

#endif

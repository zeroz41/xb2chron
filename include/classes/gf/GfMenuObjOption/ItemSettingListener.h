#ifndef CLASSES_GF_GFMENUOBJOPTION_ITEMSETTINGLISTENER_H
#define CLASSES_GF_GFMENUOBJOPTION_ITEMSETTINGLISTENER_H

#include "classes/gf/GfMenuObjOption.h"

namespace ui { class EventData; }

namespace gf {
// table 0x7100B63D68
class GfMenuObjOption::ItemSettingListener {
public:
    virtual ~ItemSettingListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}  // namespace gf

#endif

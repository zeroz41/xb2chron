#ifndef CLASSES_GF_GFMENUOBJENEMYSTATUS_ELEMLISTENER_H
#define CLASSES_GF_GFMENUOBJENEMYSTATUS_ELEMLISTENER_H

#include "classes/gf/GfMenuObjEnemyStatus.h"

namespace ui { class EventData; }

namespace gf {
// table 0x7100B61D40
class GfMenuObjEnemyStatus::ElemListener {
public:
    virtual ~ElemListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}  // namespace gf

#endif

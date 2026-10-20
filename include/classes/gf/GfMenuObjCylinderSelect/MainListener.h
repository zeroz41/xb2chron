#ifndef CLASSES_GF_GFMENUOBJCYLINDERSELECT_MAINLISTENER_H
#define CLASSES_GF_GFMENUOBJCYLINDERSELECT_MAINLISTENER_H

#include "classes/gf/GfMenuObjCylinderSelect.h"

namespace ui { class EventData; }

namespace gf {
// table 0x7100B61738
class GfMenuObjCylinderSelect::MainListener {
public:
    virtual ~MainListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}  // namespace gf

#endif

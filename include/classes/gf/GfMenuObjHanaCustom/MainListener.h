#ifndef CLASSES_GF_GFMENUOBJHANACUSTOM_MAINLISTENER_H
#define CLASSES_GF_GFMENUOBJHANACUSTOM_MAINLISTENER_H

#include "classes/gf/GfMenuObjHanaCustom.h"

namespace ui { class EventData; }

namespace gf {
// table 0x7100B626E8
class GfMenuObjHanaCustom::MainListener {
public:
    virtual ~MainListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}  // namespace gf

#endif

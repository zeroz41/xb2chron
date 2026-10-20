#ifndef CLASSES_GF_GFMENUOBJMAINROOT_MAINLISTENER_H
#define CLASSES_GF_GFMENUOBJMAINROOT_MAINLISTENER_H

#include "classes/gf/GfMenuObjMainRoot.h"

namespace ui { class EventData; }

namespace gf {
// table 0x7100B63290
class GfMenuObjMainRoot::MainListener {
public:
    virtual ~MainListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}  // namespace gf

#endif

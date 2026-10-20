#ifndef CLASSES_GF_GFMENUOBJFADE_FADELISTENER_H
#define CLASSES_GF_GFMENUOBJFADE_FADELISTENER_H

#include "classes/gf/GfMenuObjFade.h"

namespace ui { class EventData; }

namespace gf {
// table 0x7100B622E0
class GfMenuObjFade::FadeListener {
public:
    virtual ~FadeListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}  // namespace gf

#endif

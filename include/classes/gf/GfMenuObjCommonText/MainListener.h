#ifndef CLASSES_GF_GFMENUOBJCOMMONTEXT_MAINLISTENER_H
#define CLASSES_GF_GFMENUOBJCOMMONTEXT_MAINLISTENER_H

#include "classes/gf/GfMenuObjCommonText.h"

namespace ui { class EventData; }

namespace gf {
// table 0x7100B614C0
class GfMenuObjCommonText::MainListener {
public:
    virtual ~MainListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}  // namespace gf

#endif

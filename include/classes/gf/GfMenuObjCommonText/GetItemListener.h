#ifndef CLASSES_GF_GFMENUOBJCOMMONTEXT_GETITEMLISTENER_H
#define CLASSES_GF_GFMENUOBJCOMMONTEXT_GETITEMLISTENER_H

#include "classes/gf/GfMenuObjCommonText.h"

namespace ui { class EventData; }

namespace gf {
// table 0x7100B61588
class GfMenuObjCommonText::GetItemListener {
public:
    virtual ~GetItemListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}  // namespace gf

#endif

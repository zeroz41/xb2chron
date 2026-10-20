#ifndef CLASSES_GF_GFMENUOBJCOMMONTEXT_KIZUNALISTENER_H
#define CLASSES_GF_GFMENUOBJCOMMONTEXT_KIZUNALISTENER_H

#include "classes/gf/GfMenuObjCommonText.h"

namespace ui { class EventData; }

namespace gf {
// table 0x7100B61560
class GfMenuObjCommonText::KizunaListener {
public:
    virtual ~KizunaListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}  // namespace gf

#endif

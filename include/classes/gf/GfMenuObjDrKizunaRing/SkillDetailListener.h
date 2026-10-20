#ifndef CLASSES_GF_GFMENUOBJDRKIZUNARING_SKILLDETAILLISTENER_H
#define CLASSES_GF_GFMENUOBJDRKIZUNARING_SKILLDETAILLISTENER_H

#include "classes/gf/GfMenuObjDrKizunaRing.h"

namespace ui { class EventData; }

namespace gf {
// table 0x7100B61C10
class GfMenuObjDrKizunaRing::SkillDetailListener {
public:
    virtual ~SkillDetailListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}  // namespace gf

#endif

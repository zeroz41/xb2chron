#ifndef CLASSES_GF_GFMENUOBJBLKIZUNARING_SKILLDETAILLISTENER_H
#define CLASSES_GF_GFMENUOBJBLKIZUNARING_SKILLDETAILLISTENER_H

#include "classes/gf/GfMenuObjBlKizunaRing.h"

namespace ui { class EventData; }

namespace gf {
// table 0x7100B605B8
class GfMenuObjBlKizunaRing::SkillDetailListener {
public:
    virtual ~SkillDetailListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}  // namespace gf

#endif

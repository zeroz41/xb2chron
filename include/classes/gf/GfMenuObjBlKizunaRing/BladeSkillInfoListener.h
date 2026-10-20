#ifndef CLASSES_GF_GFMENUOBJBLKIZUNARING_BLADESKILLINFOLISTENER_H
#define CLASSES_GF_GFMENUOBJBLKIZUNARING_BLADESKILLINFOLISTENER_H

#include "classes/gf/GfMenuObjBlKizunaRing.h"

namespace ui { class EventData; }

namespace gf {
// table 0x7100B605E0
class GfMenuObjBlKizunaRing::BladeSkillInfoListener {
public:
    virtual ~BladeSkillInfoListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}  // namespace gf

#endif

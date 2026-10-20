#ifndef CLASSES_GF_GFMENUOBJBLKIZUNARING_MAINLISTENER_H
#define CLASSES_GF_GFMENUOBJBLKIZUNARING_MAINLISTENER_H

#include "classes/gf/GfMenuObjBlKizunaRing.h"

namespace ui { class EventData; }

namespace gf {
// table 0x7100B60540
class GfMenuObjBlKizunaRing::MainListener {
public:
    virtual ~MainListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}  // namespace gf

#endif

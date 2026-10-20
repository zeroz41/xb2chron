#ifndef CLASSES_GF_GFMENUOBJCHAINATTACK_STARTLISTENER_H
#define CLASSES_GF_GFMENUOBJCHAINATTACK_STARTLISTENER_H

#include "classes/gf/GfMenuObjChainAttack.h"

namespace ui { class EventData; }

namespace gf {
// table 0x7100B60C28
class GfMenuObjChainAttack::StartListener {
public:
    virtual ~StartListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}  // namespace gf

#endif

#ifndef CLASSES_GF_GFMENUOBJCHAINATTACK_STATUSLISTENER_H
#define CLASSES_GF_GFMENUOBJCHAINATTACK_STATUSLISTENER_H

#include "classes/gf/GfMenuObjChainAttack.h"

namespace ui { class EventData; }

namespace gf {
// table 0x7100B60C50
class GfMenuObjChainAttack::StatusListener {
public:
    virtual ~StatusListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}  // namespace gf

#endif

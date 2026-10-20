#ifndef CLASSES_GF_GFMENUOBJCHAINATTACK_EXTENDLISTENER_H
#define CLASSES_GF_GFMENUOBJCHAINATTACK_EXTENDLISTENER_H

#include "classes/gf/GfMenuObjChainAttack.h"

namespace ui { class EventData; }

namespace gf {
// table 0x7100B60CC8
class GfMenuObjChainAttack::ExtendListener {
public:
    virtual ~ExtendListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}  // namespace gf

#endif

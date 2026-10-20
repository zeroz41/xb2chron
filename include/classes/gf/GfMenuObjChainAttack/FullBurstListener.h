#ifndef CLASSES_GF_GFMENUOBJCHAINATTACK_FULLBURSTLISTENER_H
#define CLASSES_GF_GFMENUOBJCHAINATTACK_FULLBURSTLISTENER_H

#include "classes/gf/GfMenuObjChainAttack.h"

namespace ui { class EventData; }

namespace gf {
// table 0x7100B60CA0
class GfMenuObjChainAttack::FullBurstListener {
public:
    virtual ~FullBurstListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}  // namespace gf

#endif

#ifndef CLASSES_GF_GFMENUOBJDRARTSSET2_LEVELUPLISTENER_H
#define CLASSES_GF_GFMENUOBJDRARTSSET2_LEVELUPLISTENER_H

#include "classes/gf/GfMenuObjDrArtsSet2.h"

namespace ui { class EventData; }

namespace gf {
// table 0x7100B61A38
class GfMenuObjDrArtsSet2::LevelupListener {
public:
    virtual ~LevelupListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}  // namespace gf

#endif

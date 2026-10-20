#ifndef CLASSES_GF_GFMENUOBJBLWEAPON2_CHRCHANGELISTENER_H
#define CLASSES_GF_GFMENUOBJBLWEAPON2_CHRCHANGELISTENER_H

#include "classes/gf/GfMenuObjBlWeapon2.h"

namespace ui { class EventData; }

namespace gf {
// table 0x7100B606C8
class GfMenuObjBlWeapon2::ChrChangeListener {
public:
    virtual ~ChrChangeListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}  // namespace gf

#endif

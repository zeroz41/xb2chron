#ifndef CLASSES_GF_GFMENUOBJBLWEAPON2_MAINLISTENER_H
#define CLASSES_GF_GFMENUOBJBLWEAPON2_MAINLISTENER_H

#include "classes/gf/GfMenuObjBlWeapon2.h"

namespace ui { class EventData; }

namespace gf {
// table 0x7100B60650
class GfMenuObjBlWeapon2::MainListener {
public:
    virtual ~MainListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}  // namespace gf

#endif

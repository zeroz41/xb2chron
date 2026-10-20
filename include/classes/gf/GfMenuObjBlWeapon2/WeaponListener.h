#ifndef CLASSES_GF_GFMENUOBJBLWEAPON2_WEAPONLISTENER_H
#define CLASSES_GF_GFMENUOBJBLWEAPON2_WEAPONLISTENER_H

#include "classes/gf/GfMenuObjBlWeapon2.h"

namespace ui { class EventData; }

namespace gf {
// table 0x7100B606A0
class GfMenuObjBlWeapon2::WeaponListener {
public:
    virtual ~WeaponListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}  // namespace gf

#endif

#ifndef CLASSES_GF_GFMENUOBJFIELDSKILL_BLADELISTENER_H
#define CLASSES_GF_GFMENUOBJFIELDSKILL_BLADELISTENER_H

#include "classes/gf/GfMenuObjFieldSkill.h"

namespace ui { class EventData; }

namespace gf {
// table 0x7100B624B0
class GfMenuObjFieldSkill::BladeListener {
public:
    virtual ~BladeListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}  // namespace gf

#endif

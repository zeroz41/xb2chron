#ifndef CLASSES_GF_GFMENUOBJFIELDSKILL_INPUTLISTENER_H
#define CLASSES_GF_GFMENUOBJFIELDSKILL_INPUTLISTENER_H

#include "classes/gf/GfMenuObjFieldSkill.h"

namespace ui { class EventData; }

namespace gf {
// table 0x7100B62550
class GfMenuObjFieldSkill::InputListener {
public:
    virtual ~InputListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}  // namespace gf

#endif

#ifndef CLASSES_GF_GFMENUOBJFIELDSKILL_BASELISTENER_H
#define CLASSES_GF_GFMENUOBJFIELDSKILL_BASELISTENER_H

#include "classes/gf/GfMenuObjFieldSkill.h"

namespace ui { class EventData; }

namespace gf {
// table 0x7100B62528
class GfMenuObjFieldSkill::BaseListener {
public:
    virtual ~BaseListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}  // namespace gf

#endif

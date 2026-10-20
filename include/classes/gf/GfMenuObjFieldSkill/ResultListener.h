#ifndef CLASSES_GF_GFMENUOBJFIELDSKILL_RESULTLISTENER_H
#define CLASSES_GF_GFMENUOBJFIELDSKILL_RESULTLISTENER_H

#include "classes/gf/GfMenuObjFieldSkill.h"

namespace ui { class EventData; }

namespace gf {
// table 0x7100B624D8
class GfMenuObjFieldSkill::ResultListener {
public:
    virtual ~ResultListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}  // namespace gf

#endif

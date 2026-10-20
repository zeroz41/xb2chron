#ifndef CLASSES_GF_GFMENUOBJFIELDSKILL_SKILLINFOLISTENER_H
#define CLASSES_GF_GFMENUOBJFIELDSKILL_SKILLINFOLISTENER_H

#include "classes/gf/GfMenuObjFieldSkill.h"

namespace ui { class EventData; }

namespace gf {
// table 0x7100B62488
class GfMenuObjFieldSkill::SkillInfoListener {
public:
    virtual ~SkillInfoListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}  // namespace gf

#endif

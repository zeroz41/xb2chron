#ifndef CLASSES_GF_GFMENUOBJFIELDSKILL_INPUTLISTENER_H
#define CLASSES_GF_GFMENUOBJFIELDSKILL_INPUTLISTENER_H

#include "classes/gf/GfMenuObjFieldSkill.h"
#include "classes/ui/UIObjectListener.h"

namespace ui { struct EventData; }

namespace gf {
// table 0x7100B62550
class GfMenuObjFieldSkill::InputListener : public ::ui::UIObjectListener {
public:
    virtual ~InputListener() {}  // slot 0: weak in the original (its D0 is a plain operator delete)
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}  // namespace gf

#endif

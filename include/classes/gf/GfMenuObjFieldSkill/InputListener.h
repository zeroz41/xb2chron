#ifndef CLASSES_GF_GFMENUOBJFIELDSKILL_INPUTLISTENER_H
#define CLASSES_GF_GFMENUOBJFIELDSKILL_INPUTLISTENER_H

#include "classes/gf/GfMenuObjFieldSkill.h"
#include "classes/ui/UIObjectListener.h"

namespace ui { struct EventData; }

namespace gf {
// table 0x7100B62550
class GfMenuObjFieldSkill::InputListener : public ::ui::UIObjectListener {
public:
    // initialize's: 0x28 bytes, 0xC-0x1B zeroed (0x1C-0x1F is not), the owner at 0x20
    InputListener(GfMenuObjFieldSkill* owner) : pad_C(), m_owner(owner) {}
    virtual ~InputListener() {}  // slot 0: weak in the original (its D0 is a plain operator delete)
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
    unsigned char pad_C[0x10];
    GfMenuObjFieldSkill* m_owner;  // what initialize makes it for (the name is not the original's)
};
}  // namespace gf

#endif

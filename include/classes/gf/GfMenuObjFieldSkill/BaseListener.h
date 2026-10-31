#ifndef CLASSES_GF_GFMENUOBJFIELDSKILL_BASELISTENER_H
#define CLASSES_GF_GFMENUOBJFIELDSKILL_BASELISTENER_H

#include "classes/gf/GfMenuObjFieldSkill.h"
#include "classes/ui/UIObjectListener.h"

namespace ui { struct EventData; }

namespace gf {
// table 0x7100B62528
class GfMenuObjFieldSkill::BaseListener : public ::ui::UIObjectListener {
public:
    // initialize's: 0x28 bytes, 0xC-0x1B zeroed (0x1C-0x1F is not), the owner at 0x20
    BaseListener(GfMenuObjFieldSkill* owner) : m_type(0), m_shown(0), pad_14(), m_owner(owner) {}
    virtual ~BaseListener() {}  // slot 0: weak in the original (its D0 is a plain operator delete)
    virtual void reciveEvent(ui::EventData const& event, unsigned int handle);  // slot 2
    // the open event (0x21) picks the animation row: 0 treasure, 1/2 non_one/non_two, 3/4 obj_one/obj_two (the
    // name is not the original's)
    int m_type;
    int m_shown;  // 1 once the open event (1) has played the first animations (the name is not the original's)
    unsigned char pad_14[0x8];
    GfMenuObjFieldSkill* m_owner;  // what initialize makes it for (the name is not the original's)
};
}  // namespace gf

#endif

#ifndef CLASSES_GF_GFMENUOBJFIELDSKILL_RESULTLISTENER_H
#define CLASSES_GF_GFMENUOBJFIELDSKILL_RESULTLISTENER_H

#include "classes/gf/GfMenuObjFieldSkill.h"
#include "classes/ui/UIObjectListener.h"

namespace ui { struct EventData; }

namespace gf {
// table 0x7100B624D8
class GfMenuObjFieldSkill::ResultListener : public ::ui::UIObjectListener {
public:
    // initialize's: 0x28 bytes, 0xC-0x1B zeroed (0x1C-0x1F is not), the owner at 0x20
    ResultListener(GfMenuObjFieldSkill* owner) : m_state(0), m_result(0), pad_14(), m_owner(owner) {}
    virtual ~ResultListener() {}  // slot 0: weak in the original (its D0 is a plain operator delete)
    virtual void reciveEvent(ui::EventData const& event, unsigned int handle);  // slot 2
    int m_state;  // the name is not the original's
    int m_result;  // the open event's m_param0: 0 success (the name is not the original's)
    unsigned char pad_14[0x8];
    GfMenuObjFieldSkill* m_owner;  // what initialize makes it for (the name is not the original's)
};
}  // namespace gf

#endif

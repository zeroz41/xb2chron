#ifndef CLASSES_GF_GFMENUOBJFIELDSKILL_TOTALLISTENER_H
#define CLASSES_GF_GFMENUOBJFIELDSKILL_TOTALLISTENER_H

#include "classes/gf/GfMenuObjFieldSkill.h"
#include "classes/ui/UIObjectListener.h"

namespace ui { struct EventData; }

namespace gf {
// table 0x7100B62500
class GfMenuObjFieldSkill::TotalListener : public ::ui::UIObjectListener {
public:
    // initialize's: 0x28 bytes, 0xC-0x1B zeroed (0x1C-0x1F is not), the owner at 0x20
    TotalListener(GfMenuObjFieldSkill* owner) : m_state(0), pad_10(), m_owner(owner) {}
    virtual ~TotalListener() {}  // slot 0: weak in the original (its D0 is a plain operator delete)
    virtual void reciveEvent(ui::EventData const& event, unsigned int handle);  // slot 2
    int m_state;  // the name is not the original's
    unsigned char pad_10[0xC];
    GfMenuObjFieldSkill* m_owner;  // what initialize makes it for (the name is not the original's)
};
}  // namespace gf

#endif

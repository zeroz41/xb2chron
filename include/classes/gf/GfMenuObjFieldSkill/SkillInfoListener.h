#ifndef CLASSES_GF_GFMENUOBJFIELDSKILL_SKILLINFOLISTENER_H
#define CLASSES_GF_GFMENUOBJFIELDSKILL_SKILLINFOLISTENER_H

#include "classes/gf/GfMenuObjFieldSkill.h"
#include "classes/ui/UIObjectListener.h"

namespace ui { struct EventData; }

namespace gf {
// table 0x7100B62488
class GfMenuObjFieldSkill::SkillInfoListener : public ::ui::UIObjectListener {
public:
    // initialize's: 0x28 bytes, 0xC-0x1B zeroed (0x1C-0x1F is not), the owner at 0x20
    SkillInfoListener(GfMenuObjFieldSkill* owner) : m_state(0), m_open(), pad_18(), m_owner(owner) {}
    virtual ~SkillInfoListener() {}  // slot 0: weak in the original (its D0 is a plain operator delete)
    virtual void reciveEvent(ui::EventData const& event, unsigned int handle);  // slot 2
    int m_state;  // the name is not the original's
    // what the open event (0x21) leaves for the skill's display; one aggregate: event 1 resets both with one 8-byte
    // store (the names are not the original's)
    struct Open {
        // 1 after the open shows the name first: event 0x10D then shows the skill
        int m_waitSkill;
        unsigned int m_blade;  // the open event's blade (m_param1)
    };
    Open m_open;
    unsigned char pad_18[0x4];
    GfMenuObjFieldSkill* m_owner;  // what initialize makes it for (the name is not the original's)
};
}  // namespace gf

#endif

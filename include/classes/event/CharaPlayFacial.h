#ifndef CLASSES_EVENT_CHARAPLAYFACIAL_H
#define CLASSES_EVENT_CHARAPLAYFACIAL_H

#include "classes/event/ICmd.h"

namespace event {
// table 0x7100B3E610
class CharaPlayFacial : public ::event::ICmd {
public:
    virtual ~CharaPlayFacial() {}  // slot 0 (inline: its D0 is in the unit's inline tail)
    virtual void init();  // slot 2
    virtual bool update(event::ICmd::Param const&);  // slot 3
    virtual void term();  // slot 4
    void idle();  // out of line (0x71000EBAB8); term calls it
    // set to 0 by init (the command's step; the name is not the original's)
    int m_step;  // 0x8
    unsigned char pad_c[0x14];
    // the facial id the running command plays (ScriptCharaFacial::doit saves it for undo); the name is not the original's
    int m_id;  // 0x20
    unsigned char pad_24[0x4c];  // CharaObj holds one at 0x9a0, the next command at +0x70
};
}  // namespace event

#endif

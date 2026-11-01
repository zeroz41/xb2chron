#ifndef CLASSES_EVENT_CHARAPLAYHEAD_H
#define CLASSES_EVENT_CHARAPLAYHEAD_H

#include "classes/event/ICmd.h"

namespace event {
// table 0x7100B3E5A0
class CharaPlayHead : public ::event::ICmd {
public:
    virtual ~CharaPlayHead() {}  // slot 0 (inline: its D0 is in the unit's inline tail)
    virtual void init();  // slot 2
    virtual int update(event::ICmd::Param const&);  // slot 3
    virtual void term();  // slot 4
    void idle();  // out of line (0x71000EB3D0); term calls it
    // set to 0 by init (the command's step; the name is not the original's)
    int m_step;  // 0x8
    unsigned char pad_c[0x14];
    // the head id the running command plays (ScriptCharaHead::doit saves it for undo); the name is not the original's
    int m_id;  // 0x20
    unsigned char pad_24[0x14];  // CharaObj holds one at 0x950, the next command at +0x38
};
}  // namespace event

#endif

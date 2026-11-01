#ifndef CLASSES_EVENT_CHARAPLAYACTION_H
#define CLASSES_EVENT_CHARAPLAYACTION_H

#include "classes/event/ICmd.h"

namespace event {
// table 0x7100B3E530
class CharaPlayAction : public ::event::ICmd {
public:
    virtual ~CharaPlayAction() {}  // slot 0 (inline: its D0 is in the unit's inline tail)
    virtual void init();  // slot 2
    virtual int update(event::ICmd::Param const&);  // slot 3
    virtual void term();  // slot 4
    void idle();  // out of line (0x71000E7D04); term calls it unless bit 1 is set
    // bit 1: term clears it instead of calling idle; the name is not the original's
    unsigned int m_flags;  // 0x8
    unsigned char pad_c[0x34];  // CharaObj holds one, the next command at +0x40
};
}  // namespace event

#endif

#ifndef CLASSES_EVENT_CHARAPLAYTALK_H
#define CLASSES_EVENT_CHARAPLAYTALK_H

#include "classes/event/ICmd.h"

namespace event {
// table 0x7100B3E648
class CharaPlayTalk : public ::event::ICmd {
public:
    virtual ~CharaPlayTalk() {}  // slot 0 (inline: its D0 is in the unit's inline tail)
    virtual void init();  // slot 2
    virtual bool update(event::ICmd::Param const&);  // slot 3
    virtual void term();  // slot 4
    void idle();  // out of line (0x71000EC400); term calls it
    // bit 3: playTalk with its first argument false does not requeue a running talk; the name is not the original's
    unsigned int m_flags;  // 0x8 (init zeroes it)
    unsigned char pad_c[0x5c];  // CharaObj holds one at 0xa38, the next command at +0x78
    float pad_68;  // init: 1
    float pad_6c;  // init: 1
    float pad_70;  // init: 0
    float pad_74;  // init: 0
};
}  // namespace event

#endif

#ifndef CLASSES_EVENT_CHARAPLAYTALK_H
#define CLASSES_EVENT_CHARAPLAYTALK_H

#include "classes/event/ICmd.h"

namespace event {
// table 0x7100B3E648
class CharaPlayTalk : public ::event::ICmd {
public:
    virtual ~CharaPlayTalk();  // slot 0
    virtual void init();  // slot 2
    virtual bool update(event::ICmd::Param const&);  // slot 3
    virtual void term();  // slot 4
    // bit 3: playTalk with its first argument false does not requeue a running talk; the name is not the original's
    unsigned int m_flags;  // 0x8 (init zeroes it)
    unsigned char pad_c[0x6c];  // CharaObj holds one at 0xa38, the next command at +0x78
};
}  // namespace event

#endif

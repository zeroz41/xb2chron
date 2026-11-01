#ifndef CLASSES_EVENT_CHARAPLAYMOTION_H
#define CLASSES_EVENT_CHARAPLAYMOTION_H

#include "classes/event/ICmd.h"

namespace event {
// table 0x7100B3CC68
class CharaPlayMotion : public ::event::ICmd {
public:
    virtual ~CharaPlayMotion();  // slot 0
    virtual int update(event::ICmd::Param const&);  // slot 3
    virtual void term();  // slot 4
    unsigned char pad_8[0x48];  // CharaObj holds one at 0x680, the next command at +0x50
};
}  // namespace event

#endif

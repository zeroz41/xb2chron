#ifndef CLASSES_EVENT_CHARAPLAYACTION_H
#define CLASSES_EVENT_CHARAPLAYACTION_H

#include "classes/event/ICmd.h"

namespace event {
// table 0x7100B3E530
class CharaPlayAction : public ::event::ICmd {
public:
    virtual ~CharaPlayAction();  // slot 0
    virtual void init();  // slot 2
    virtual bool update(event::ICmd::Param const&);  // slot 3
    virtual void term();  // slot 4
    unsigned char pad_8[0x38];  // CharaObj holds one, the next command at +0x40
};
}  // namespace event

#endif

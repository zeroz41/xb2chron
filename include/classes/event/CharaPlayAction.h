#ifndef CLASSES_EVENT_CHARAPLAYACTION_H
#define CLASSES_EVENT_CHARAPLAYACTION_H

#include "classes/event/ICmd.h"

namespace event {
// table 0x7100B3E530
class CharaPlayAction {
public:
    virtual ~CharaPlayAction();  // slot 0
    virtual void init();  // slot 2
    virtual void update(event::ICmd::Param const&);  // slot 3
    virtual void term();  // slot 4
};
}  // namespace event

#endif

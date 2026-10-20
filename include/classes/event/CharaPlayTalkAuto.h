#ifndef CLASSES_EVENT_CHARAPLAYTALKAUTO_H
#define CLASSES_EVENT_CHARAPLAYTALKAUTO_H

#include "classes/event/ICmd.h"

namespace event {
// table 0x7100B3CCD8
class CharaPlayTalkAuto {
public:
    virtual ~CharaPlayTalkAuto();  // slot 0
    virtual void init();  // slot 2
    virtual void update(event::ICmd::Param const&);  // slot 3
    virtual void term();  // slot 4
};
}  // namespace event

#endif

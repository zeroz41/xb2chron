#ifndef CLASSES_EVENT_CHARASTOPACTION_H
#define CLASSES_EVENT_CHARASTOPACTION_H

#include "classes/event/ICmd.h"

namespace event {
// table 0x7100B3E568
class CharaStopAction : public ::event::ICmd {
public:
    virtual ~CharaStopAction();  // slot 0
    virtual void update(event::ICmd::Param const&);  // slot 3
};
}  // namespace event

#endif

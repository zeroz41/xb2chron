#ifndef CLASSES_EVENT_CHARASTOPHEAD_H
#define CLASSES_EVENT_CHARASTOPHEAD_H

#include "classes/event/ICmd.h"

namespace event {
// table 0x7100B3E5D8
class CharaStopHead : public ::event::ICmd {
public:
    virtual ~CharaStopHead();  // slot 0
    virtual void update(event::ICmd::Param const&);  // slot 3
};
}  // namespace event

#endif

#ifndef CLASSES_EVENT_CHARAWALKPOS_H
#define CLASSES_EVENT_CHARAWALKPOS_H

#include "classes/event/ICmd.h"

namespace event {
// table 0x7100B3E418
class CharaWalkPos : public ::event::ICmd {
public:
    virtual ~CharaWalkPos();  // slot 0
    virtual void update(event::ICmd::Param const&);  // slot 3
    virtual void term();  // slot 4
};
}  // namespace event

#endif

#ifndef CLASSES_EVENT_CHARALINERPOS_H
#define CLASSES_EVENT_CHARALINERPOS_H

#include "classes/event/ICmd.h"

namespace event {
// table 0x7100B3E488
class CharaLinerPos : public ::event::ICmd {
public:
    virtual ~CharaLinerPos();  // slot 0
    virtual void update(event::ICmd::Param const&);  // slot 3
};
}  // namespace event

#endif
